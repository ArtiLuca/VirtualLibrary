#include "Library.h"
#include "Model/Loggers/IFileLogger.h"
#include "Model/Visitors/ConcisePrinter.h"
#include "Model/Visitors/DetailedPrinter.h"
#include "Model/Visitors/MediaValidator.h"
#include "Model/Visitors/MediaEditor.h"
#include "Model/Visitors/SearchVisitor.h"
#include "Model/Visitors/ScoreVisitor.h"
#include "Model/Library/MediaFactory.h"

#include <string>
#include <vector>

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>


namespace Model {
namespace Library {


// === COSTRUTTORE ===

Library::Library(Loggers::IMediaLogger* logger)
    : libraryLogger(logger),
    logLevel(Model::Loggers::LogLevel::Info)
{}


// === LOGGER ===

void Library::setLibraryLogger(Loggers::IMediaLogger* log) {

    if (libraryLogger) {
        if (auto log = dynamic_cast<Model::Loggers::IFileLogger*>(libraryLogger)) {
            logLibraryMessage("Closing FileLogger.\n", Model::Loggers::LogLevel::Info);
            log->flush();
        }
    }
    libraryLogger = log;
}

void Library::setLibraryLogLevel(Loggers::LogLevel lvl) { logLevel = lvl; }

Loggers::LogLevel Library::getLibraryLogLevel() const { return logLevel; }

Loggers::IMediaLogger* Library::getLibraryLogger() const { return libraryLogger; }

void Library::logLibraryMessage(const std::string& msg, Loggers::LogLevel lvl) const {

    // log del messaggio se logger impostato e livello di severita' piu' alto
    if (libraryLogger && static_cast<int>(logLevel) >= static_cast<int>(lvl)) {
        libraryLogger->logMessage(msg);
    }
}


// === HELPER ===

bool Library::libraryIsEmpty() const { return libraryMedia.empty();  }

unsigned int Library::getLibrarySize() const { return libraryMedia.size(); }

const std::vector<std::shared_ptr<Media::AbstractMedia>>& Library::getAllLibraryMedia() const {

    if (libraryIsEmpty()) {
        logLibraryMessage("[LIBRARY - GET ALL MEDIA] Library is empty.\n", Loggers::LogLevel::Debug);
    }
    return libraryMedia;

}


// === INSERIMENTO ===

void Library::insertLibraryMedia(const std::shared_ptr<Media::AbstractMedia> media) {

    if (!media) {
        logLibraryMessage("[LIBRARY - INSERT MEDIA] Media is not valid.\n", Loggers::LogLevel::Debug);
        return;
    }

    if (checkDuplicateID(media->getUniqueID())) {
        logLibraryMessage("LIBRARY - INSERT MEDIA] Inserting duplicate ID media.\n", Loggers::LogLevel::Error);
        return;
    }

    try {

        Visitors::MediaValidator validator;
        media->accept(validator);
        libraryMedia.push_back(media);
        logLibraryMessage("[LIBRARY - INSERT MEDIA] Inserted media '" + media->getMediaName() + "' with ID=" +
            std::to_string(media->getUniqueID()) + " successfully!\n", Loggers::LogLevel::Info);

    }
    catch (const Visitors::MediaValidatorException& e) {
        logLibraryMessage("[LIBRARY - INSERT MEDIA] Could not add media '" + media->getMediaName() + "' with ID=" +
            std::to_string(media->getUniqueID()) + ": " + std::string(e.what()), Loggers::LogLevel::Error);
    }
    catch (const std::runtime_error& e) {
        logLibraryMessage("[LIBRARY - INSERT MEDIA] Could not insert media '" + media->getMediaName() + "' with ID=" +
            std::to_string(media->getUniqueID()) + ": " + std::string(e.what()), Loggers::LogLevel::Error);
    }
}


// === RIMOZIONE ===

bool Library::removeLibraryMediaByID(unsigned int id) {

    if (libraryIsEmpty()) {
        logLibraryMessage("[LIBRARY - REMOVE MEDIA] Library is empty\n", Loggers::LogLevel::Debug);
        return false;
    }

    for (auto it = libraryMedia.begin(); it != libraryMedia.end(); ++it) {
        if (*it && (*it)->getUniqueID() == id) {
            std::string removed = (*it)->getMediaName();
            libraryMedia.erase(it);
            logLibraryMessage("[LIBRARY - REMOVE MEDIA] Successfully removed media '" + removed + "' with ID=" +
                std::to_string(id) + "\n", Loggers::LogLevel::Info);
            return true;
        }
    }
    logLibraryMessage("[LIBRARY - REMOVE MEDIA] Could not remove media with ID=" +
        std::to_string(id) + " from library\n", Loggers::LogLevel::Error);
    return false;
}

void Library::clearLibrary() {

    if (!libraryIsEmpty()) {
        libraryMedia.clear();
        logLibraryMessage("[LIBRARY - CLEAR LIBRARY] Cleared all library contents\n", Loggers::LogLevel::Info);
    }
}


// === MODIFICA ===

bool Library::editLibraryMediaByID(
    unsigned int id,
    const std::unordered_map<std::string, std::string>& mediaEdits)
{
    if (libraryIsEmpty()) {
        logLibraryMessage("[LIBRARY - EDIT MEDIA] Library is empty\n", Loggers::LogLevel::Debug);
        return false;
    }

    auto media = getMediaByID(id);
    if (!media) {
        logLibraryMessage("[LIBRARY - EDIT MEDIA] No media with ID=" + std::to_string(id) + "\n", Loggers::LogLevel::Error);
        return false;
    }

    try {

        Visitors::MediaEditor editor(mediaEdits);
        media->accept(editor);
        logLibraryMessage("[LIBRARY - EDIT] Successfully edited media with ID=" + std::to_string(id) + "\n", Loggers::LogLevel::Info);
        return true;
    }
    catch (const Visitors::MediaValidatorException& e) {
        logLibraryMessage("[LIBRARY - EDIT MEDIA] Failed to edit media with ID=" + std::to_string(id) + ", " +
            std::string(e.what()), Loggers::LogLevel::Error);
        throw Visitors::MediaValidatorException(std::string(e.what()));
    }
    catch (const std::exception& e) {
        logLibraryMessage("[LIBRARY - EDIT MEDIA] Failed to edit media with ID=" + std::to_string(id) + ", " +
            std::string(e.what()), Loggers::LogLevel::Error);
        return false;
    }
}


// === VISUALIZZAZIONE (Usati per debugging) ===

std::string Library::viewConciseMediaInfoByID(unsigned int id) const {

    std::string concise = "";
    if (libraryIsEmpty()) {
        logLibraryMessage("[LIBRARY - VIEW CONCISE INFO] Library is empty\n", Loggers::LogLevel::Debug);
        concise = "[LIBRARY - VIEW CONCISE INFO] Library is empty\n";
    }
    try {
        Visitors::ConcisePrinter printer;
        getMediaByID(id)->accept(printer);
        concise = printer.getConcisePreview();
    }
    catch (const Visitors::MediaValidatorException& e) {
        concise = "[LIBRARY - VIEW CONCISE INFO] Validation error: " + std::string(e.what());
        logLibraryMessage("[LIBRARY - VIEW CONCISE INFO] Validation error: " + std::string(e.what()) + "\n", Loggers::LogLevel::Error);
    }
    logLibraryMessage("[LIBRARY - VIEW CONCISE INFO] Concise info for media with ID=" + std::to_string(id) + "\n" + concise + "\n", Loggers::LogLevel::Info);
    return concise;
}

std::string Library::viewDetailedMediaInfoByID(unsigned int id) const {

    std::string detailed = "";
    if (libraryIsEmpty()) {
        logLibraryMessage("[LIBRARY - VIEW DETAILED INFO] Library is empty\n", Loggers::LogLevel::Debug);
        detailed = "[LIBRARY - VIEW DETAILED INFO] Library is empty\n";
    }
    try {
        Visitors::DetailedPrinter printer;
        getMediaByID(id)->accept(printer);
        detailed = printer.getDetailedPreview();
    }
    catch (const Visitors::MediaValidatorException& e) {
        detailed = "[LIBRARY - VIEW DETAILED INFO] Validation error: " + std::string(e.what());
        logLibraryMessage("[LIBRARY - VIEW DETAILED INFO] Validation error: " + std::string(e.what()) + "\n", Loggers::LogLevel::Error);
    }
    logLibraryMessage("[LIBRARY - VIEW DETAILED INFO] Detailed info for media with ID=" + std::to_string(id) + "\n" + detailed + "\n", Loggers::LogLevel::Info);
    return detailed;
}

std::string Library::viewMediaInfoByID(unsigned int id, bool detail) const {

    if (detail) return viewDetailedMediaInfoByID(id);
    else return viewConciseMediaInfoByID(id);
}

std::string Library::viewAllLibraryMedia() const {

    std::string library = "";
    int count = 0;
    if (!libraryIsEmpty()) {
        Visitors::ConcisePrinter printer;
        for (auto& media : libraryMedia) {
            media->accept(printer);
            library += "\nMedia " + std::to_string(count) + ") " + printer.getConcisePreview();
            count++;
        }
    }
    return library;
}


// === RICERCA ===

std::vector<unsigned int> Library::searchLibrary(const SearchQuery& query) const {

    std::vector<unsigned int> results;
    if (libraryIsEmpty()) {
        logLibraryMessage("[LIBRARY - SEARCH LIBRARY] Library is empty\n", Loggers::LogLevel::Debug);
        return results;
    }

    Visitors::SearchVisitor search(query);

    for (const auto& media : libraryMedia) {
        if (media) {
            media.get()->accept(search);
        }
    }

    results = search.getMatches();
    return results;
}


// === FETCH ===

std::shared_ptr<Media::AbstractMedia> Library::getMediaByID(unsigned int id) const {

    if (libraryIsEmpty()) {
        logLibraryMessage("[LIBRARY - GET MEDIA] Library is empty.\n", Loggers::LogLevel::Debug);
        return nullptr;
    }

    for (auto& media : libraryMedia) {
        if (media && media->getUniqueID() == id) {

            logLibraryMessage("[LIBRARY - GET MEDIA] Successfully fetched media '" + media->getMediaName() + "' with ID=" +
                std::to_string(media->getUniqueID()) + "\n", Loggers::LogLevel::Debug);

            return media;
        }
    }
    logLibraryMessage("[LIBRARY - GET MEDIA] Failed to fetch media with ID=" + std::to_string(id) + "\n", Loggers::LogLevel::Debug);
    return nullptr;
}


// === SCORING VISITOR ===

float Library::getMediaScoreValueByID(unsigned int id) const {

    auto media = getMediaByID(id);
    if (!media) {
        logLibraryMessage("[LIBRARY - GET SCORE VALUE] Error: Could not fetch media with ID= " + std::to_string(id) + "\n", Loggers::LogLevel::Error);
        return 0.0f;
    }
    Visitors::ScoreVisitor scoring;
    media->accept(scoring);
    logLibraryMessage("[LIBRARY - GET SCORE VALUE] Media with ID=" + std::to_string(id) + " has score: " +
        std::to_string(scoring.getScoreValue()).substr(0, 4) + "/100\n", Loggers::LogLevel::Info);
    return scoring.getScoreValue();
}

std::string Library::getMediaScoreLabelByID(unsigned int id) const {

    auto media = getMediaByID(id);
    if (!media) {
        logLibraryMessage("[LIBRARY - GET SCORE LABEL] Error: Could not fetch media with ID= " + std::to_string(id) + "\n", Loggers::LogLevel::Error);
        return "Unknown Quality";
    }
    Visitors::ScoreVisitor scoring;
    media->accept(scoring);
    logLibraryMessage("[LIBRARY - GET SCORE LABEL] Media with ID=" + std::to_string(id) + " has quality label: " + scoring.getScoreLabel() + "\n", Loggers::LogLevel::Info);
    return scoring.getScoreLabel();
}

std::string Library::getMediaScoreInfoByID(unsigned int id) const {

    auto media = getMediaByID(id);
    if (!media) {
        logLibraryMessage("[LIBRARY - GET SCORE INFO] Error: Could not fetch media with ID= " + std::to_string(id) + "\n", Loggers::LogLevel::Error);
        return "Unknown Info";
    }
    Visitors::ScoreVisitor scoring;
    media->accept(scoring);
    logLibraryMessage("[LIBRARY - GET SCORE INFO] Media with ID=" + std::to_string(id) + " scoring info: " + scoring.getScoreInfo() + "\n", Loggers::LogLevel::Info);
    return scoring.getScoreInfo();
}


// === JSON ===

QJsonObject Library::toJson() const {

    // oggetto JSON principale per contenere tutti i media attualmente in libreria
    QJsonObject rootObject;

    // array JSON per contenere tutti i media serializzati
    QJsonArray mediaArray;

    // scorre tutti i media
    for (const auto& media : libraryMedia) {
        if (media) {

            // serializza in formato JSON ciascun media (virtuale puro 'toJson')
            QJsonObject mediaObject = media->toJson();
            // e lo aggiunge all'array JSON
            mediaArray.append(mediaObject);
        }
    }

    // inserisce l'array di media nel JSON principale con chiave ("media")
    rootObject["media"] = mediaArray;

    logLibraryMessage("[LIBRARY - SAVE LIBRARY] Successfully saved library contents to JSON object\n", Loggers::LogLevel::Info);

    // restituisce il JSON finale della libreria
    return rootObject;

}

void Library::fromJson(const QJsonObject& obj) {

    // svuota la libreria attuale
    libraryMedia.clear();

    logLibraryMessage("[LIBRARY - LOAD LIBRARY] Attempting to read library contents from file...\n", Loggers::LogLevel::Debug);

    // verifica la presenza della chiave "media" e che l'oggetto JSON sia effettivamente un array
    if (!(obj.contains("media") && obj["media"].isArray())) {
        logLibraryMessage("[LIBRARY - LOAD LIBRARY] JSON file does not contain a library!", Loggers::LogLevel::Error);
    }
    else if (obj.contains("media") && obj["media"].isArray()) {

        QJsonArray mediaArray = obj["media"].toArray();
        unsigned int mediaCount = 0;

        // scorre ogni media nell'array
        for (const auto& mediaValue : mediaArray) {

            // prende l'oggetto JSON del media
            QJsonObject mediaObject = mediaValue.toObject();
            // prende il tipo del media salvato
            QString mediaType = mediaObject["mediaType"].toString();
            Model::Library::MediaFactory factory;

            try {

                // tenta di ricreare il tipo trovato utilizzando MediaFactory, usando mappa di attributi vuota
                auto mediaPtr = factory.createMedia(mediaType.toStdString(), {});
                if (mediaPtr) {

                    // se questo ha successo, si usa il virtuale puro 'fromJson' per settare gli attributi
                    mediaPtr->fromJson(mediaObject);
                    // e si aggiunge il media alla fine della libreria
                    libraryMedia.push_back(mediaPtr);
                    ++mediaCount;
                }
                // altrimenti, errre
                else {
                    logLibraryMessage("[LIBRARY - LOAD LIBRARY Error: MediaFactory error for media type '" + mediaType.toStdString() + "'\n", Loggers::LogLevel::Error);
                }
            }
            catch (const Model::Visitors::MediaValidatorException& e) {
                logLibraryMessage("[LIBRARY - LOAD LIBRARY] Error: MediaValidator could not validate media of type '" + mediaType.toStdString() + "', " + std::string(e.what()), Loggers::LogLevel::Error);
            }
            catch (const std::exception& e) {
                logLibraryMessage("[LIBRARY - LOAD LIBRARY] Error: MediaFactory could not create media of type '" + mediaType.toStdString() + "', " + std::string(e.what()), Loggers::LogLevel::Error);
            }
        }
        logLibraryMessage("[LIBRARY - LOAD LIBRARY] Successfully read " + std::to_string(mediaCount) + " media from JSON object into library\n", Loggers::LogLevel::Info);
    }
    else {
        logLibraryMessage("[LIBRARY - LOAD LIBRARY] Error: Could not load library contents file!\n", Loggers::LogLevel::Error);
    }
}

bool Library::saveToFile(const QString& filename) const {

    logLibraryMessage("[LIBRARY - SAVE TO FILE] Saving library contents to file '" + filename.toStdString() + "'\n", Loggers::LogLevel::Info);

    // serializza l'intera libreria in un oggetto JSON
    QJsonObject rootObject = toJson();

    // crea un QJsonDocument da questo in modo da poterci scrivere
    QJsonDocument doc(rootObject);

    // crea e apre il file di salvataggio in modalita' scrittura
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        // errore di apertura file
        logLibraryMessage("[LIBRARY - SAVE TO FILE] Error: Could not open open file '" + filename.toStdString() + "'\n", Loggers::LogLevel::Error);
        return false;
    }

    // scrive su file l'oggetto JSON, con indentazione per maggior leggibilita'
    file.write(doc.toJson(QJsonDocument::Indented));

    // chiusura del file
    file.close();

    // logga  il successo
    logLibraryMessage("[LIBRARY - SAVE TO FILE] Successfully saved library contents to file '" + filename.toStdString() + "'\n", Loggers::LogLevel::Info);
    return true;
}

bool Library::loadFromFile(const QString& filename) {

    logLibraryMessage("[LIBARY - LOAD FROM FILE] Attempting to read contents into library from file '" + filename.toStdString() + "'\n", Loggers::LogLevel::Info);

    // tenta l'apertura del file di caricamento in modalita' lettura
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        // errore di apertura file
        logLibraryMessage("[LIBRARY - LOAD FROM FILE] Error: Could not open file '" + filename.toStdString() + "'\n", Loggers::LogLevel::Error);
        return false;
    }

    // legge tutti i contenuti del file in un QByteArray
    QByteArray fileContents = file.readAll();
    // chiude il file
    file.close();

    // crea un QJsonDocument con il contenuto letto
    QJsonDocument doc = QJsonDocument::fromJson(fileContents);
    if (!doc.isObject()) {
        // segnala se il file non contiene un oggetto JSON valido
        logLibraryMessage("[LIBRARY - LOAD FROM FILE] Error: File '" + filename.toStdString() + "' does not contain a valid JSON object\n", Loggers::LogLevel::Error);
        return false;
    }

    // recupera l'oggetto JSON principale
    QJsonObject rootObject = doc.object();

    // carica i media in libreria utilizzando il metodo 'fromJson'
    fromJson(rootObject);

    logLibraryMessage("[LIBRARY - LOAD FROM FILE] Successfully loaded library contents from file '" + filename.toStdString() + "\n", Loggers::LogLevel::Debug);
    return true;
}


// === HELPER PRIVATI ===

bool Library::checkDuplicateID(unsigned int id) const {

    for (const auto& media : libraryMedia) {
        if (media) {
            if (media->getUniqueID() == id) {
                return true;
            }
        }
    }
    return false;

}

}
}

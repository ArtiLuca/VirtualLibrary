#include "Manager.h"
#include "Model/Visitors/MediaValidator.h"
#include "Model/Library/MediaFactory.h"

#include "Model/Library/Command/InsertCommand.h"
#include "Model/Library/Command/RemoveCommand.h"
#include "Model/Library/Command/EditCommand.h"

#include <string>
#include <vector>
#include <unordered_map>

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

namespace Model {
namespace Library {

Manager::Manager(Loggers::IMediaLogger* log)
    : mediaLibrary(log),
    currentIndex(0),
    lastUndoDescription(""),
    lastRedoDescription("")
{
    mediaLibrary.setLibraryLogLevel(Loggers::LogLevel::Info);
}

// === GETTER/SETTER/GENERALE ===

bool Manager::isEmpty() const { return mediaLibrary.libraryIsEmpty(); }

unsigned int Manager::getSize() const { return mediaLibrary.getLibrarySize(); }

bool Manager::isValidIndex(unsigned int ind) const { return ind < getSize(); }

unsigned int Manager::getCurrentIndex() const { return currentIndex; }

void Manager::setCurrentIndex(unsigned int ind) {
    if (isValidIndex(ind))
        currentIndex = ind;
}

const std::string& Manager::getLastUndoInfo() const { return lastUndoDescription; }

const std::string& Manager::getLastRedoInfo() const { return lastRedoDescription; }


// === OPERAZIONI INDICE ===

bool Manager::goToNextIndex() {

    if (isEmpty() || currentIndex + 1 > getSize()) {
        mediaLibrary.logLibraryMessage("[MANAGER - NEXT INDEX] Index '" + std::to_string(currentIndex + 1) + "' is out-of-range\n", Loggers::LogLevel::Debug);
        return false;
    }
    ++currentIndex;
    return true;
}

bool Manager::goToPreviousIndex() {

    if (isEmpty() || currentIndex == 0) {
        mediaLibrary.logLibraryMessage("[MANAGER - PREVIOUS INDEX] Index '" + std::to_string(currentIndex - 1) + "' is out-of-range\n", Loggers::LogLevel::Debug);
        return false;
    }
    --currentIndex;
    return true;
}

bool Manager::goToFirstIndex() {

    if (!isEmpty()) {
        currentIndex = 0;
        return true;
    }
    return false;
}

bool Manager::goToLastIndex() {

    if (!isEmpty()) {
        currentIndex = getSize() - 1;
        return true;
    }
    return false;
}

unsigned int Manager::getMediaIndexByID(unsigned int id) const {

    if (isEmpty()) {
        mediaLibrary.logLibraryMessage("[MANAGER - GET MEDIA INDEX BY ID] Library is empty\n", Loggers::LogLevel::Debug);
        return getSize();
    }

    const auto& media = mediaLibrary.getAllLibraryMedia();
    for (unsigned int i = 0; i < media.size(); ++i) {
        if (media[i] && media[i]->getUniqueID() == id) {
            return i;
        }
    }

    mediaLibrary.logLibraryMessage("[MANAGER GET MEDIA BY ID] No media with ID=" + std::to_string(id) + " was found, returning library size\n", Loggers::LogLevel::Debug);
    return media.size();
}


// === FETCH ===

std::shared_ptr<Media::AbstractMedia> Manager::getMediaAtIndex(unsigned int ind) const {

    if (!isValidIndex(ind)) {
        mediaLibrary.logLibraryMessage("[MANAGER - GET MEDIA AT] Index '" + std::to_string(ind) + "' is not a valid index\n", Loggers::LogLevel::Debug);
        return nullptr;
    }
    return mediaLibrary.getAllLibraryMedia().at(ind);
}

std::shared_ptr<Media::AbstractMedia> Manager::getCurrentMedia() const {

    return getMediaAtIndex(currentIndex);
}

std::shared_ptr<Media::AbstractMedia> Manager::getMediaByID(unsigned int id) const {
    return mediaLibrary.getMediaByID(id);
}


// === INSERIMENTO ===

bool Manager::insertMediaAtIndex(
    const std::shared_ptr<Media::AbstractMedia>& media,
    unsigned int ind)
{
    unsigned int currSize = getSize();
    unsigned int insertInd = ind;
    if (!isValidIndex(ind)) insertInd = currSize;

    if (!isValidIndex(ind) && ind != currSize) {
        mediaLibrary.logLibraryMessage("[MANAGER - INSERT MEDIA AT] Index '" + std::to_string(ind) + "' is out of range, inserting at end of library\n",
            Loggers::LogLevel::Info);
    }

    auto command = std::make_shared<Command::InsertCommand>(Command::InsertCommand(&mediaLibrary, media));
    executeCommand(command);

    if (isEmpty()) currentIndex = 0;
    else currentIndex = insertInd;

    return true;
}

bool Manager::insertMediaAtCurrentIndex(const std::shared_ptr<Media::AbstractMedia>& media) {
    return insertMediaAtIndex(media, currentIndex);
}


// === RIMOZIONE ===

bool Manager::removeMediaAtIndex(unsigned int ind) {

    if (isEmpty()) {
        mediaLibrary.logLibraryMessage("[MANAGER - REMOVE MEDIA AT] Library is empty\n", Loggers::LogLevel::Debug);
        return false;
    }

    if (!isValidIndex(ind)) {
        mediaLibrary.logLibraryMessage("[MANAGER - REMOVE MEDIA AT] Index '" + std::to_string(ind) + "' is not a valid index\n", Loggers::LogLevel::Debug);
        return false;
    }

    auto media = getMediaAtIndex(ind);
    if (!media) {
        mediaLibrary.logLibraryMessage("[MANAGER - REMOVE MEDIA AT] Media at index '" + std::to_string(ind) + "' is not valid\n", Loggers::LogLevel::Debug);
        return false;
    }

    auto command = std::make_shared<Command::RemoveCommand>(Command::RemoveCommand(&mediaLibrary, media->getUniqueID()));
    executeCommand(command);

    if (!isEmpty()) currentIndex = getSize() - 1;
    else currentIndex = 0;

    return true;
}

bool Manager::removeMediaAtCurrentIndex() {

    return removeMediaAtIndex(currentIndex);
}

bool Manager::removeAllMedia() {

    if (!isEmpty()) {
        mediaLibrary.clearLibrary();
        clearCommandOperations();
        goToFirstIndex();
        lastUndoDescription = "";
        lastRedoDescription = "";
        return true;
    }
    return false;
}


// === MODIFICA ===

bool Manager::editMediaAtIndex(
    unsigned int ind,
    const std::unordered_map<std::string, std::string>& mediaEdits)
{
    if (isEmpty()) {
        mediaLibrary.logLibraryMessage("[MANAGER - EDIT MEDIA AT] Library is empty\n", Loggers::LogLevel::Debug);
        return false;
    }

    if (!isValidIndex(ind)) {
        mediaLibrary.logLibraryMessage("[MANAGER- EDIT MEDIA AT] Index '" + std::to_string(ind) + "' is not a valid index\n", Loggers::LogLevel::Debug);
        return false;
    }

    auto media = getMediaAtIndex(ind);
    if (!media) {
        mediaLibrary.logLibraryMessage("[MANAGER - EDIT MEDIA AT] No media found at index '" + std::to_string(ind) + "'\n", Loggers::LogLevel::Debug);
        return false;
    }

    try {

        auto command = std::make_shared<Command::EditCommand>(Command::EditCommand(&mediaLibrary, media->getUniqueID(), mediaEdits));
        executeCommand(command);
        return true;
    }
    catch (const Visitors::MediaValidatorException& e) {
        mediaLibrary.logLibraryMessage("[MANAGER - EDIT MEDIA AT] Errow: Validation failed: " + std::string(e.what()), Loggers::LogLevel::Error);
        throw Visitors::MediaValidatorException(std::string(e.what()));
    }

    return false;
}

bool Manager::editMediaAtCurrentIndex(const std::unordered_map<std::string, std::string>& mediaEdits) {

    return editMediaAtIndex(currentIndex, mediaEdits);
}


// === CREAZIONE ===

std::shared_ptr<Media::AbstractMedia> Manager::createNewMedia(
    const std::string& type,
    const std::unordered_map<std::string, std::string>& attr)
{
    try {

        Model::Library::MediaFactory factory;
        auto newMedia = factory.createMedia(type, attr);
        if (!newMedia) {
            mediaLibrary.logLibraryMessage("[MANAGER - CREATE NEW MEDIA] Error creating media of type '" + type + "', returning null-value\n",
                Loggers::LogLevel::Error);
            return nullptr;
        }
        else {

            goToLastIndex();

            if (!insertMediaAtCurrentIndex(newMedia)) {

                mediaLibrary.logLibraryMessage("[MANAGER - CREATE NEW MEDIA] Error creating media of type '" + type + "'\n", Loggers::LogLevel::Error);
                return nullptr;
            }

            mediaLibrary.logLibraryMessage("[MANAGER - CREATE NEW MEDIA] Successfully created media '" + newMedia->getMediaName() + "' of type '"
                + type + "', inserting at end of library\n", Loggers::LogLevel::Info);
            return newMedia;
        }
    }
    catch (const Visitors::MediaValidatorException& e) {
        mediaLibrary.logLibraryMessage("[MANAGER - CREATE NEW MEDIA] Error creating media of type '" + type + "', " + std::string(e.what()), Loggers::LogLevel::Error);
        throw Visitors::MediaValidatorException("Error creating media of type '" + type + "', " + std::string(e.what()));
    }

}


// === RICERCA ===

std::vector<unsigned int> Manager::searchMedia(const SearchQuery& query) const {

    if (isEmpty()) {
        mediaLibrary.logLibraryMessage("[MANAGER - SEARCH MEDIA] Library is empty, returning empty result vector\n", Loggers::LogLevel::Debug);
        return {};
    }

    std::vector<unsigned int> searchResults = mediaLibrary.searchLibrary(query);
    if (searchResults.empty()) {
        mediaLibrary.logLibraryMessage("[MANAGER - SEARCH MEDIA] Search found no matching media, returning empty result vector\n", Loggers::LogLevel::Info);
        return searchResults;
    }
    else {
        mediaLibrary.logLibraryMessage("[MANAGER - SEARCH MEDIA] Search found " + std::to_string(searchResults.size()) + " media\n", Loggers::LogLevel::Info);
    }
    return searchResults;
}

std::vector<unsigned int> Manager::getSearchResultIndexesByID(const std::vector<unsigned int>& mediaIDs) const {

    if (mediaIDs.empty()) {
        mediaLibrary.logLibraryMessage("[MANAGER - GET SEARCH RESULT INDEXES] Search result vector is empty\n", Loggers::LogLevel::Debug);
        return {};
    }

    std::vector<unsigned int> mediaIndexes;
    for (auto id : mediaIDs) {
        unsigned int ind = getMediaIndexByID(id);
        if (isValidIndex(ind)) {
            mediaIndexes.push_back(ind);
        }
    }
    return mediaIndexes;
}


// === SCORING ===

float Manager::getMediaScoreAtIndex(unsigned int ind) const {

    if (!isValidIndex(ind)) {
        mediaLibrary.logLibraryMessage("[MANAGER - GET MEDIA SCORE] Index '" + std::to_string(ind) + "' is not a valid index\n", Loggers::LogLevel::Debug);
        return 0.0f;
    }

    auto media = getMediaAtIndex(ind);
    return mediaLibrary.getMediaScoreValueByID(media->getUniqueID());
}

std::string Manager::getMediaScoreLabelAtIndex(unsigned int ind) const {

    if (!isValidIndex(ind)) {
        mediaLibrary.logLibraryMessage("[MANAGER - GET MEDIA LABEL] Index '" + std::to_string(ind) + "' is not a valid index\n", Loggers::LogLevel::Debug);
        return "Unknown Quality";
    }

    auto media = getMediaAtIndex(ind);
    return mediaLibrary.getMediaScoreLabelByID(media->getUniqueID());
}

std::string Manager::getMediaScoreInfoAtIndex(unsigned int ind) const {

    if (!isValidIndex(ind)) {
        mediaLibrary.logLibraryMessage("[MANAGER - GET MEDIA SCORING INFO] Index '" + std::to_string(ind) + "' is not a valid index\n", Loggers::LogLevel::Debug);
        return "Unknown Info";
    }

    auto media = getMediaAtIndex(ind);
    return mediaLibrary.getMediaScoreInfoByID(media->getUniqueID());
}


// === JSON ===

bool Manager::saveContentsToFile(const QString& filename) const {

    return mediaLibrary.saveToFile(filename);

}

bool Manager::loadContentsFromFile(const QString& filename) {

    bool readSuccess = mediaLibrary.loadFromFile(filename);
    if (readSuccess) currentIndex = 0;
    return readSuccess;
}


// === LOGGERS ===

void Manager::setLibraryLogger(Model::Loggers::IMediaLogger* newLogger) {
    mediaLibrary.setLibraryLogger(newLogger);
}

Model::Loggers::LogLevel Manager::getLogLevel() const {
    return mediaLibrary.getLibraryLogLevel();
}

void Manager::setLogLevel(Model::Loggers::LogLevel level) {
    mediaLibrary.setLibraryLogLevel(level);
}

// === COMMAND ===

void Manager::executeCommand(const std::shared_ptr<Command::IAbstractCommand>& cmd) {

    // se comando valido
    if (cmd) {
        // eseguilo
        cmd->execute();
        // inserisci nel vettore dei Undo
        undoCommands.push_back(cmd);
        // svuota vettore dei Redo
        redoCommands.clear();
    }
}

void Manager::undoCommand() {

    // se ci sono comandi Undo
    if (!undoCommands.empty()) {
        // prendi l'ultimo eseguito
        auto command = undoCommands.back();
        // e togli dal vettore
        undoCommands.pop_back();
        if (command) {
            // esegui il comando
            command->undo();
            // aggiorna info ultimo comando annullato
            lastUndoDescription = command->getCommandInfo();
            // inserisci nel vettore dei Redo
            redoCommands.push_back(command);
        }
    }
}

void Manager::redoCommand() {

    // se ci sono comandi Redo
    if (!redoCommands.empty()) {
        // prendi l'ultimo eseguito
        auto command = redoCommands.back();
        // e togli dal vettore dei Redo
        redoCommands.pop_back();
        if (command) {
            // esegui il comando
            command->execute();
            // aggiorna info ultimo comando eseguito (ripristinato)
            lastRedoDescription = command->getCommandInfo();
            // inserisci comando nel vettori dei Undo
            undoCommands.push_back(command);
        }
    }
}

bool Manager::canUndoCommand() const {
    return !undoCommands.empty();
}

bool Manager::canRedoCommand() const {
    return !redoCommands.empty();
}

void Manager::clearCommandOperations() {
    undoCommands.clear();
    redoCommands.clear();
}


}
}

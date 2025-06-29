#include "Controller.h"

#include "Model/Media/AbstractMedia.h"
#include "Model/Visitors/ScoreVisitor.h"
#include "Model/Visitors/MediaValidator.h"
#include "Model/Library/Manager.h"

#include "View/Viewer/AudioViewer.h"
#include "View/Viewer/VideoViewer.h"
#include "View/Viewer/EBookViewer.h"
#include "View/Viewer/ImageViewer.h"

#include <QMessageBox>
#include <QString>
#include <QMap>

#include <stdexcept>
#include <string>
#include <unordered_map>

namespace Controller {


// === COSTRUTTORE ===

Controller::Controller(Model::Library::Manager* manager, QObject* parent)
    : QObject(parent),
    manager(manager)
{
    if (!manager) throw std::runtime_error("Manager is 'nullptr'");
}


// === GENERALE ===

void Controller::initializeCommandSignals() {

    emit undoPossible(manager->canUndoCommand());
    emit redoPossible(manager->canRedoCommand());
}

bool Controller::managerIsEmpty() const {

    return(!manager || manager->isEmpty());
}

int Controller::getManagerSize() const {

    return (manager ? manager->getSize() : 0);
}

int Controller::getCurrentManagerIndex() const {

    return (manager ? manager->getCurrentIndex() : -1);
}

void Controller::setCurrentManagerIndex(unsigned int ind) {

    if (!manager || !validIndex(ind)) {
        emit errorOccurred(QString::number(ind) + " is not a valid index");
        return;
    }
    else manager->setCurrentIndex(ind);
}


// === OPERAZIONI INDICE ===

bool Controller::validIndex(unsigned int ind) const {

    return (manager && manager->isValidIndex(ind));
}

int Controller::getNextIndex() {

    if (!manager) return -1;

    unsigned int currInd = manager->getCurrentIndex();
    if (!validIndex(currInd + 1)) {
        emit errorOccurred("Next index is out-of-range");
        return -1;
    }

    if (!manager->goToNextIndex()) {
        emit errorOccurred("Could not go to next index");
        return -1;
    }

    return manager->getCurrentIndex();

}

int Controller::getPreviousIndex() {

    if (!manager) return -1;

    unsigned int currInd = manager->getCurrentIndex();
    if (currInd == 0 || !validIndex(currInd -1 )) {
        emit errorOccurred("Previous index is out-of-range");
        return -1;
    }

    if (!manager->goToPreviousIndex()) {
        emit errorOccurred("Could not go to previous index");
        return -1;
    }

    return manager->getCurrentIndex();

}

int Controller::getFirstIndex() {

    if (!manager) return -1;

    if (managerIsEmpty()) {
        emit errorOccurred("Library is empty");
        return -1;
    }

    manager->goToFirstIndex();
    return manager->getCurrentIndex();
}

int Controller::getLastIndex() {

    if (!manager || managerIsEmpty()) return -1;

    if (managerIsEmpty()) {
        emit errorOccurred("Library is empty");
        return -1;
    }

    manager->goToLastIndex();
    return manager->getCurrentIndex();
}

int Controller::getIndexByMediaID(unsigned int mediaID) {

    if (!manager || managerIsEmpty()) return -1;
    return manager->getMediaIndexByID(mediaID);
}


// ===  FETCH ===

std::shared_ptr<Model::Media::AbstractMedia> Controller::getMediaAtIndex(unsigned int ind) const {

    if (manager) {
        return manager->getMediaAtIndex(ind);
    }
    else return nullptr;
}

std::shared_ptr<Model::Media::AbstractMedia> Controller::getMediaByID(unsigned int mediaID) const {

    if (manager) {
        return manager->getMediaByID(mediaID);
    }
    else return nullptr;
}

std::shared_ptr<Model::Media::AbstractMedia> Controller::getCurrentMedia() const {

    if (manager) {
        return manager->getCurrentMedia();
    }
    else return nullptr;
}


// === RICERCA ===

std::vector<unsigned int> Controller::getSearchResultIndexes(const std::vector<unsigned int>& mediaIDs) const {
    return manager->getSearchResultIndexesByID(mediaIDs);

}


// === HELPER TIPI Qt ===

std::unordered_map<std::string, std::string> Controller::QMapToUnorderedMap(const QMap<QString, QString>& attributeMapQt) {

    std::unordered_map<std::string, std::string> resultMap;
    for (auto it = attributeMapQt.begin(); it != attributeMapQt.end(); ++it) {
        resultMap[it.key().toStdString()] = it.value().toStdString();
    }
    return resultMap;
}

QMap<QString, QString> Controller::UnorderedMapToQMap(const std::unordered_map<std::string, std::string>& attributeMapStd) {

    QMap<QString, QString> resultMap;
    for (const auto& attr : attributeMapStd) {
        resultMap[QString::fromStdString(attr.first)] = QString::fromStdString(attr.second);
    }
    return resultMap;
}


// === OPERAZIONI INDICE (SLOT) ===

bool Controller::onSetIndexRequest(int ind) {

    if (!manager || !validIndex(ind)) {
        emit errorOccurred("Could not set current index to index " + QString::number(ind));
        return false;
    }

    manager->setCurrentIndex(ind);
    emit currentIndexChanged(ind);
    return true;
}

bool Controller::onGoToNextIndexRequest() {

    int nextInd = getNextIndex();
    if (nextInd < 0) return false;
    emit currentIndexChanged(nextInd);
    return true;
}

bool Controller::onGoToPreviousIndexRequest() {

    int prevInd = getPreviousIndex();
    if (prevInd < 0) return false;
    emit currentIndexChanged(prevInd);
    return true;
}

bool Controller::onGoToFirstIndexRequest() {

    int firstInd = getFirstIndex();
    if (firstInd < 0) return false;
    emit currentIndexChanged(firstInd);
    return true;
}

bool Controller::onGoToLastIndexRequest() {

    int lastInd = getLastIndex();
    if (lastInd < 0) return false;
    emit currentIndexChanged(lastInd);
    return true;
}


// === MODIFICA (SLOT) ===

void Controller::onEditMediaRequest(unsigned int ind, QMap<QString, QString> mediaEdits) {

    if (!manager || !validIndex(ind)) {
        emit editFailure(ind, "No media was found at index " + QString::number(ind));
        return;
    }

    std::unordered_map<std::string, std::string> edits = QMapToUnorderedMap(mediaEdits);

    try {
        bool edited = manager->editMediaAtIndex(ind, edits);
        if (edited) emit editSuccess(ind);
        else emit editFailure(ind, "Unknown error while editing media at index " + QString::number(ind));
    }
    catch (const Model::Visitors::MediaValidatorException& e) {
        emit editFailure(ind, QString::fromStdString(std::string(e.what())));
    }
}


// === CREAZIONE (SLOT) ===

void Controller::onCreateMediaRequest(
    unsigned int ind,
    const std::string& type,
    const std::unordered_map<std::string, std::string>& attributes)
{
    try {

        auto newMedia = manager->createNewMedia(type, attributes);
        if (!newMedia) {
            emit createFailure("MediaFactory error while creating media of type " + QString::fromStdString(type));
            return;
        }

        emit createSuccess("Successfully created media " + QString::fromStdString(newMedia->getMediaName()) + " of type " +
            QString::fromStdString(type) + " at index " + QString::number(ind));
    }
    catch (const Model::Visitors::MediaValidatorException& e) {
        emit createFailure(QString::fromStdString(e.what()));
    }
}


// === RIMOZIONE (SLOT) ===

int Controller::onRemoveMediaAtIndexRequest(unsigned int ind) {

    if (!manager || !validIndex(ind)) {
        emit errorOccurred("Failed, as index " + QString::number(ind) + " is not valid");
        return false;
    }

    bool removed = manager->removeMediaAtIndex(ind);
    if (removed) emit removedMedia(ind);
    return removed;
}

void Controller::onDeleteLibraryRequest() {

    if (!manager || managerIsEmpty()) {
        emit errorOccurred("Could not delete library (not valid or empty)");
        return;
    }

    if (manager->removeAllMedia()) {
        emit libraryDeleted();
    }
}


// UNDO/REDO (SLOT) ===

void Controller::onUndoRequest() {

    if (!manager) return;
    manager->undoCommand();

    QString info = QString::fromStdString(manager->getLastUndoInfo());
    if (!info.isEmpty()) emit lastCommandInfo("Undo: " + info);

    emit undoPossible(manager->canUndoCommand());
    emit redoPossible(manager->canRedoCommand());
}

void Controller::onRedoRequest() {

    if (!manager) return;
    manager->redoCommand();

    QString info = QString::fromStdString(manager->getLastRedoInfo());
    if (!info.isEmpty()) emit lastCommandInfo("Redo: " + info);

    emit undoPossible(manager->canUndoCommand());
    emit redoPossible(manager->canRedoCommand());
}


// === RICERCA (SLOT) ===

void Controller::onSearchRequest(Model::Library::SearchQuery query) {

    if (!manager) {
        emit errorOccurred("Failed, as manager is 'nullptr'");
        return;
    }

    std::vector<unsigned int> results = manager->searchMedia(query);
    emit searchResults(results);
}

void Controller::onSearchMediaByNameRequest(const QString& mediaName) {

    Model::Library::SearchQuery query;
    query.setMediaName(mediaName.toStdString());
    onSearchRequest(query);
}


// === JSON (SLOT) ===

bool Controller::onSaveLibraryRequest(const QString& filename) {

    if (!manager) return false;
    return manager->saveContentsToFile(filename);
}

bool Controller::onLoadLibraryRequest(const QString& filename) {

    if (!manager) return false;
    return manager->loadContentsFromFile(filename);
}


// === WIDGET PERSONALIZZATI (SLOT) ===

void Controller::onScoreRequested(unsigned int ind, QWidget* viewer) {

    auto mediaPtr = manager->getMediaAtIndex(ind);
    if (!mediaPtr) {
        emit errorOccurred("No media was fonud at index " + QString::number(ind));
        return;
    }

    Model::Visitors::ScoreVisitor scoring;
    mediaPtr->accept(scoring);

    float scoreValue = scoring.getScoreValue();
    QString scoreLabel = QString::fromStdString(scoring.getScoreLabel());
    QString scoreInfo = QString::fromStdString(scoring.getScoreInfo());

    if (auto audioViewer = dynamic_cast<View::Viewer::AudioViewer*>(viewer)) {
        audioViewer->setScore(scoreValue, scoreLabel, scoreInfo);
    }
    if (auto videoViewer = dynamic_cast<View::Viewer::VideoViewer*>(viewer)) {
        videoViewer->setScore(scoreValue, scoreLabel, scoreInfo);
    }
    if (auto ebookViewer = dynamic_cast<View::Viewer::EBookViewer*>(viewer)) {
        ebookViewer->setScore(scoreValue, scoreLabel, scoreInfo);
    }
    if (auto imageViewer = dynamic_cast<View::Viewer::ImageViewer*>(viewer)) {
        imageViewer->setScore(scoreValue, scoreLabel, scoreInfo);
    }
}

void Controller::onValidateISBNRequested(unsigned int ind, QWidget* viewer) {

    auto mediaPtr = manager->getMediaAtIndex(ind);
    if (!mediaPtr) {
        emit errorOccurred("No media was found at index " + QString::number(ind));
        return;
    }

    auto* ebookPtr = dynamic_cast<Model::Media::EBook*>(mediaPtr.get());
    if (!ebookPtr) {
        emit errorOccurred("Media at index " + QString::number(ind) + " is not EBook media");
        return;
    }

    bool valid = ebookPtr->validISBN();
    if (auto ebookViewer = dynamic_cast<View::Viewer::EBookViewer*>(viewer)) {
        if (valid) {
            ebookViewer->setEBookISBNValidation("EBook ISBN '" + QString::fromStdString(ebookPtr->getISBN()) + "' is valid.");
        }
        else {
            ebookViewer->setEBookISBNValidation("EBook ISBN '" + QString::fromStdString(ebookPtr->getISBN()) + "' is not valid.");
        }
    }
    else {
        emit errorOccurred("Could not cast viewer to EBookViewer");
    }
}

void Controller::onVideoDurationRequested(unsigned int ind, QWidget* viewer) {

    auto mediaPtr = manager->getMediaAtIndex(ind);
    if (!mediaPtr) {
        emit errorOccurred("No media was found at index " + QString::number(ind));
        return;
    }

    auto* videoPtr = dynamic_cast<Model::Media::Video*>(mediaPtr.get());
    if (!videoPtr) {
        emit errorOccurred("Media at index " + QString::number(ind) + " is not Video media");
        return;
    }

    QString dur = QString::fromStdString(videoPtr->getVideoDuration());
    if (auto videoViewer = dynamic_cast<View::Viewer::VideoViewer*>(viewer)) {
        videoViewer->setVideoDuration(dur);
    }
    else {
        emit errorOccurred("Could not vast viewer to VideoViewer");
    }
}

}


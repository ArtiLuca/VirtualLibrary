#include "AbstractFile.h"

#include <string>

namespace Model {
namespace Media {

const unsigned int AbstractFile::INVALID_UNIQUE_ID = 0;
const float AbstractFile::MIN_FILE_SIZE = 0.0001;
const float AbstractFile::MAX_FILE_SIZE = 12000.000;

unsigned int AbstractFile::uniqueIDCounter = 1;
const std::string AbstractFile::defaultPath = "Home";
const float AbstractFile::defaultSize = 5.0;

unsigned int AbstractFile::incrementUniqueIDCounter() { return uniqueIDCounter++; }

void AbstractFile::setCurrentUniqueID(unsigned int currID) {
    if (currID > uniqueIDCounter) {
        uniqueIDCounter = currID;
    }
}

AbstractFile::AbstractFile()
    : uniqueID(incrementUniqueIDCounter()),
    filePath(defaultPath),
    fileSize(defaultSize)
{}

AbstractFile::AbstractFile(
    const std::string& path,
    float size)
    : uniqueID(incrementUniqueIDCounter()),
    filePath(path),
    fileSize(size)
{}

AbstractFile::AbstractFile(const AbstractFile& file)
    : uniqueID(file.uniqueID),
    filePath(file.filePath),
    fileSize(file.fileSize)
{}

AbstractFile& AbstractFile::operator=(const AbstractFile& file) {

    if (this != &file) {
        filePath = file.filePath;
        fileSize = file.fileSize;
    }
    return *this;
}


unsigned int AbstractFile::getUniqueID() const { return uniqueID; }
const std::string& AbstractFile::getFilePath() const { return filePath; }
float AbstractFile::getFileSize() const { return fileSize; }

void AbstractFile::setFilePath(const std::string& path) { filePath = path; }
void AbstractFile::setFileSize(float size) { fileSize = size; }

}
}

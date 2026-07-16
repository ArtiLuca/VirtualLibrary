#include "RemoveCommand.h"

namespace Model {
namespace Library {
namespace Command {

RemoveCommand::RemoveCommand(
    Library* lib,
    unsigned int id)
    : libraryPtr(lib),
    removedID(id),
    removed(false)
{
    if (libraryPtr) {
        // fetch puntatore al media da rimuovere
        auto media = libraryPtr->getMediaByID(removedID);
        if (media) {
            // crea un backup del media da rimuovere con 'clone'
            backupMedia.reset(dynamic_cast<Media::AbstractMedia*>(media->clone()));
        }
    }
}

void RemoveCommand::execute() {

    if (libraryPtr && !removed) {
        // rimuovi il media dalla libreria
        removed = libraryPtr->removeLibraryMediaByID(removedID);
    }
}

void RemoveCommand::undo() {

    if (libraryPtr && removed && backupMedia) {
        // reinserisci il media utilizzando il backup
        libraryPtr->insertLibraryMedia(backupMedia);
        removed = false;
    }
}

std::string RemoveCommand::getCommandInfo() const {

    if (backupMedia) {
        return "Removed media '" + backupMedia->getMediaName() + "' with ID=" + std::to_string(removedID);
    }
    else return "";

}

}
}
}

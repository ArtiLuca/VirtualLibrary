#include "EditCommand.h"
#include "Model/Visitors/MediaValidator.h"

#include <string>

namespace Model {
namespace Library {
namespace Command {

EditCommand::EditCommand(
    Library* lib,
    unsigned int id,
    const std::unordered_map<std::string, std::string>& mediaEdits)
    : libraryPtr(lib),
    editedID(id),
    edits(mediaEdits),
    edited(false)
{
    if (libraryPtr) {
        // fetch del media
        auto media = libraryPtr->getMediaByID(editedID);
        if (media) {
            // trasferisce ownership del media gestito ad una copia del media originale
            originalMedia.reset(dynamic_cast<Media::AbstractMedia*>(media->clone()));
        }
    }
}

void EditCommand::execute() {

    if (libraryPtr && !edited) {
        try {
            // tenta la modifica
            edited = libraryPtr->editLibraryMediaByID(editedID, edits);
        }
        catch (const Visitors::MediaValidatorException& e) {
            throw Visitors::MediaValidatorException(std::string(e.what()));
        }
    }
}

void EditCommand::undo() {

    if (libraryPtr && edited) {
        // rimuovi media modificato
        libraryPtr->removeLibraryMediaByID(editedID);
        // reinserisci il media originale salvato precedetemente
        libraryPtr->insertLibraryMedia(originalMedia);
        edited = false;
    }
}

std::string EditCommand::getCommandInfo() const {

    if (originalMedia) {
        return "Edited media '" + originalMedia->getMediaName() + "' with ID=" + std::to_string(editedID);
    }
    else return "";
}


}
}
}

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
        // fetch puntatore al media da modificare
        auto media = libraryPtr->getMediaByID(editedID);
        if (media) {
            // crea nuova copia polimorfa (usando 'clone') e sostiuisci il media puntato
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
            // notifica se ci sono errori di validazione
            throw Visitors::MediaValidatorException(std::string(e.what()));
        }
    }
}

void EditCommand::undo() {

    if (libraryPtr && edited) {
        // rimuovi media modificato
        libraryPtr->removeLibraryMediaByID(editedID);
        // reinserisci il media originale utilizzando la copia
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

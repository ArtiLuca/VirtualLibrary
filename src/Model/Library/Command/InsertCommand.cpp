#include "InsertCommand.h"

namespace Model {
namespace Library {
namespace Command {

InsertCommand::InsertCommand(
    Library* lib,
    std::shared_ptr<Media::AbstractMedia> media)
    : libraryPtr(lib),
    mediaPtr(media),
    inserted(false)
{}

void InsertCommand::execute() {

    if (libraryPtr && mediaPtr && !inserted) {
        // inserisce il media
        libraryPtr->insertLibraryMedia(mediaPtr);
        inserted = true;
    }
}

void InsertCommand::undo() {

    if (libraryPtr && inserted) {
        // rimuovi ultimo media inserito
        libraryPtr->removeLibraryMediaByID(mediaPtr->getUniqueID());
        inserted = false;
    }
}

std::string InsertCommand::getCommandInfo() const {

    if (mediaPtr) {
        return "Inserted media '" + mediaPtr->getMediaName() + "' with ID=" + std::to_string(mediaPtr->getUniqueID());
    }
    else return "";

}


}
}
}

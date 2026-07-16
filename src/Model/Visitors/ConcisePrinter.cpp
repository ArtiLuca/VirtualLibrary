#include "ConcisePrinter.h"
#include "MediaValidator.h"

#include <string>

namespace Model {
namespace Visitors {

ConcisePrinter::ConcisePrinter() : concisePreview("") {}

void ConcisePrinter::resetPrinter() { concisePreview.clear(); }

const std::string& ConcisePrinter::getConcisePreview() const { return concisePreview; }


void ConcisePrinter::visit(const Media::Audio& audio) const {

    const_cast<ConcisePrinter*>(this)->resetPrinter();

    MediaValidator validator;
    audio.accept(validator);

    if (validator.isValidMedia()) {

        concisePreview += "[AUDIO] (ID: " + std::to_string(audio.getUniqueID()) + "), ("
                          + audio.getMediaName() + ", " + audio.getArtist() + " - "
                          + std::to_string(audio.getMediaLength()) + " min)\n";
    }
    else {
        throw MediaValidatorException(validator.getErrorMessage());
    }
}

void ConcisePrinter::visit(const Media::Video& video) const {

    const_cast<ConcisePrinter*>(this)->resetPrinter();

    MediaValidator validator;
    video.accept(validator);

    if (validator.isValidMedia()) {

        concisePreview += "[VIDEO] (ID: " + std::to_string(video.getUniqueID()) + "), ("
                          + video.getMediaName() + ", " + video.getDirector() + " - "
                          + std::to_string(video.getMediaLength()) + " min)\n";
    }
    else {
        throw MediaValidatorException(validator.getErrorMessage());
    }
}

void ConcisePrinter::visit(const Media::EBook& ebook) const {

    const_cast<ConcisePrinter*>(this)->resetPrinter();

    MediaValidator validator;
    ebook.accept(validator);

    if (validator.isValidMedia()) {

        concisePreview += "[E-BOOK] (ID: " + std::to_string(ebook.getUniqueID()) + "), ("
                          + ebook.getMediaName() + ", " + ebook.getAuthor() + " - "
                          + std::to_string(ebook.getMediaLength()) + " pages)\n";
    }
    else {
        throw MediaValidatorException(validator.getErrorMessage());
    }
}

void ConcisePrinter::visit(const Media::Image& image) const {

    const_cast<ConcisePrinter*>(this)->resetPrinter();

    MediaValidator validator;
    image.accept(validator);

    if (validator.isValidMedia()) {
        concisePreview += "[IMAGE] (ID: " + std::to_string(image.getUniqueID()) + "), ("
                          + image.getMediaName() + ", " + image.getImageCreator() + " - "
                          + std::to_string(image.getResolution().first) + 'x' + std::to_string(image.getResolution().second) + ")\n";
    }
    else {
        throw MediaValidatorException(validator.getErrorMessage());
    }
}

}
}

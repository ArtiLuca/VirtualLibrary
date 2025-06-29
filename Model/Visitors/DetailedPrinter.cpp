#include "DetailedPrinter.h"
#include "MediaValidator.h"

#include <string>
#include <cmath>

namespace Model {
namespace Visitors {

DetailedPrinter::DetailedPrinter() : detailedPreview("") {}


const std::string& DetailedPrinter::getDetailedPreview() const { return detailedPreview; }

void DetailedPrinter::resetPrinter() { detailedPreview.clear(); }


void DetailedPrinter::printCommonAttributes(const Media::AbstractMedia &media) const {

    int roundedSize = std::ceil(media.getFileSize());
    detailedPreview += "\n[ID=" + std::to_string(media.getUniqueID()) + "]"
                       + "\n[Path] " + media.getFilePath()
                       + "\n[Size] " + std::to_string(roundedSize) + " MB"
                       + "\n[Name] " + media.getMediaName()
                       + "\n[Uploader] " + media.getMediaUploader()
                       + "\n[Format] " + media.getMediaFormat()
                       + "\n[Rating] " + std::to_string(media.getMediaRating()) + "/100 ";
}


void DetailedPrinter::visit(const Media::Audio& audio) const {

    const_cast<DetailedPrinter*>(this)->resetPrinter();

    MediaValidator validator;
    audio.accept(validator);

    if (validator.isValidMedia()) {

        detailedPreview += "{AUDIO MEDIA}";
        printCommonAttributes(audio);

        int roundedSampleRate = std::ceil(audio.getSampleRate());
        detailedPreview += "\n[Artist] " + audio.getArtist()
                           + "\n[Genre] " + audio.getGenre()
                           + "\n[Album] " + audio.getAlbum()
                           + "\n[Release Year] " + std::to_string(audio.getReleaseYear())
                           + "\n[Length] " + std::to_string(audio.getMediaLength())+ " minutes"
                           + "\n[Bitrate] " + std::to_string(audio.getBitRate()) + " kbps"
                           + "\n[Samplerate] " + std::to_string(roundedSampleRate) + " kHz"
                           + "\n[Bit Depth] " + std::to_string(audio.getBitDepth()) + "-bit"
                           + "\n[Audio Channels] " + std::to_string(audio.getAudioChannels()) + " channels"
                           + "\n[Collaborators] " + (audio.getCollaborators().empty() ? "No Collaborators" : audio.getCollaborators()) + "\n";
    }
    else {
        throw MediaValidatorException(validator.getErrorMessage());
    }

}

void DetailedPrinter::visit(const Media::Video& video) const {

    const_cast<DetailedPrinter*>(this)->resetPrinter();

    MediaValidator validator;
    video.accept(validator);

    if (validator.isValidMedia()) {

        detailedPreview += "{VIDEO MEDIA}";
        printCommonAttributes(video);
        detailedPreview += "\n[Director] " + video.getDirector()
                           + "\n[Genre] " + video.getGenre()
                           + "\n[Release Year] " + std::to_string(video.getCreationYear())
                           + "\n[Length] " + std::to_string(video.getMediaLength()) + " total minutes"
                           + "\n[Framerate] " + std::to_string(video.getFrameRate()) + " fps"
                           + "\n[Resolution] " + std::to_string(video.getResolution().first) + 'x' + std::to_string(video.getResolution().second) + " (16:9)"
                           + "\n[Video Quality] " + std::to_string(video.getMediaLength()) + " min"
                           + "\n[Color Depth] " + std::to_string(video.getVideoColorDepth()) + "-bit"
                           + "\n[Language] " + video.getLanguage()
                           + "\n[Subtitles] " + (video.getSubtitles().empty() ? "No Subtitles" : video.getSubtitles()) + "\n";
    }
    else {
        throw MediaValidatorException(validator.getErrorMessage());
    }

}

void DetailedPrinter::visit(const Media::EBook& ebook) const {

    const_cast<DetailedPrinter*>(this)->resetPrinter();

    MediaValidator validator;
    ebook.accept(validator);

    if (validator.isValidMedia()) {

        detailedPreview += "{E-BOOK MEDIA}";
        printCommonAttributes(ebook);
        detailedPreview += "\n[Author] " + ebook.getAuthor()
                           + "\n[Publisher] " + ebook.getPublisher()
                           + "\n[Publication Date] " + std::to_string(ebook.getReleaseYear())
                           + "\n[ISBN] " + ebook.getISBN()
                           + "\n[Length] " + std::to_string(ebook.getMediaLength()) + "  pages"
                           + "\n[Category] " + (ebook.getCategory().empty() ? "No Category" : ebook.getCategory())
                           + "\n[Language] " + ebook.getLanguage() +
                           + "\n[Cover Path] " + ebook.getCoverImagePath()
                           + "\n[Illustrated?] " + (ebook.hasImages() ? "Has Images" : "No Images") + "\n";
    }
    else {
        throw MediaValidatorException(validator.getErrorMessage());
    }

}

void DetailedPrinter::visit(const Media::Image& image) const {

    const_cast<DetailedPrinter*>(this)->resetPrinter();

    MediaValidator validator;
    image.accept(validator);

    if (validator.isValidMedia()) {

        std::pair<int, int> res = image.getResolution();
        std::pair<int, int> asp = image.getImageAspectRatio();

        detailedPreview += "{IMAGE MEDIA}";
        printCommonAttributes(image);
        detailedPreview += "\n[Created] " + image.getDateCreated()
                           + "\n[Creator] " + image.getImageCreator()
                           + "\n[Category] " + image.getImageCategory()
                           + "\n[Resolution] " + std::to_string(res.first) + "x" + std::to_string(res.second)
                           + "\n[Aspect Ratio] " + std::to_string(asp.first) + ":" + std::to_string(asp.second)
                           + "\n[Bitdepth] " + std::to_string(image.getImageBitDepth()) + "-bit"
                           + "\n[Compression] " + (image.isCompressed() ? "Yes" : "No")
                           + "\n[Location Taken] " + (image.getLocationTaken().empty() ? "Not Given" : image.getLocationTaken()) + "\n";
    }
    else {
        throw MediaValidatorException(validator.getErrorMessage());
    }

}

}
}



#include "MediaValidator.h"
#include "Model/Loggers/IConsoleLogger.h"

#include <string>
#include <vector>

namespace Model {
namespace Visitors {


MediaValidator::MediaValidator()
    : validMedia(true),
    errorMessage("")
{}


bool MediaValidator::isValidMedia() const { return validMedia; }

const std::string& MediaValidator::getErrorMessage() const { return errorMessage; }


void MediaValidator::resetValidator() {
    validMedia = true;
    errorMessage.clear();
}


bool MediaValidator::isValidFormat(const std::string& fmt, const std::vector<std::string>& formats) const {

    for (const std::string& f : formats) {
        if (f == fmt) return true;
    }
    return false;
}


void MediaValidator::visit(const Media::Audio& audio) const {

    const_cast<MediaValidator*>(this)->resetValidator();

    validateCommonAttributes(audio);

    if (audio.measuredInPages()) {
        errorMessage += "Audio length must be measured in minutes.\n";
        validMedia = false;
    }
    if (audio.hasResolution()) {
        errorMessage += "Audio may not have a resolution!\n";
        validMedia = false;
    }
    if (!isValidFormat(audio.getMediaFormat(), Media::Audio::AUDIO_FORMATS)) {
        errorMessage += "Not a valid Audio format (" + audio.getMediaFormat() + ").\n";
        validMedia = false;
    }
    if (audio.getArtist().empty()) {
        errorMessage += "Missing artist field.\n";
        validMedia = false;
    }
    if (audio.getGenre().empty()) {
        errorMessage += "Missing genre field.\n";
        validMedia = false;
    }
    if (audio.getAlbum().empty()) {
        errorMessage += "Missing album field.\n";
        validMedia = false;
    }
    if (!isWithinRange(audio.getReleaseYear(), Media::AbstractMedia::MIN_RELEASE_YEAR, Media::AbstractMedia::MAX_RELEASE_YEAR)) {
        errorMessage += "Not a valid release year: (" + std::to_string(audio.getReleaseYear()) + ").\n";
        validMedia = false;
    }
    if (!isWithinRange(audio.getMediaLength(), Media::Audio::MIN_AUDIO_LENGTH, Media::Audio::MAX_AUDIO_LENGTH)) {
        errorMessage += "Not a valid Audio length: (" + std::to_string(audio.getMediaLength()) + " min).\n";
        validMedia = false;
    }
    if (!isWithinRange(audio.getBitRate(), Media::Audio::MIN_AUDIO_BIT_RATE, Media::Audio::MAX_AUDIO_BITRATE)) {
        errorMessage += "Not a valid Audio bitrate: (" + std::to_string(audio.getBitRate()) + " kbps).\n";
        validMedia = false;
    }
    if (!isWithinRange(audio.getSampleRate(), Media::Audio::MIN_AUDIO_SAMPLE_RATE, Media::Audio::MAX_AUDIO_SAMPLE_RATE)) {
        errorMessage += "Not a valid Audio samplerate: (" + std::to_string(audio.getSampleRate()) + " kHz).\n";
        validMedia = false;
    }
    if (!isWithinRange(audio.getBitDepth(), Media::Audio::MIN_AUDIO_BIT_DEPTH, Media::Audio::MAX_AUDIO_BIT_DEPTH)) {
        errorMessage += "Not a valid Audio bitdepth: (" + std::to_string(audio.getBitDepth()) + "-bit).\n";
        validMedia = false;
    }

    if (!isWithinRange(audio.getAudioChannels(), Media::Audio::MIN_AUDIO_CHANNELS, Media::Audio::MAX_AUDIO_CHANNELS)) {
        errorMessage += "Not a valid number of audio channels: (" + std::to_string(audio.getAudioChannels()) + ".\n";
        validMedia = false;
    }

    if (!errorMessage.empty()) {
        Model::Loggers::IConsoleLogger consoleLogger;
        consoleLogger.logMessage(errorMessage);
        throw MediaValidatorException(getErrorMessage());
    }
}

void MediaValidator::visit(const Media::Video& video) const {

    const_cast<MediaValidator*>(this)->resetValidator();

    validateCommonAttributes(video);

    if (!video.hasLength() || !video.hasResolution()) {
        errorMessage += "Video must have both length and resolution fields set.\n";
        validMedia = false;
    }
    if (video.measuredInPages()) {
        errorMessage += "Video length must be measured in minutes.\n";
        validMedia = false;
    }
    if (!isValidFormat(video.getMediaFormat(), Media::Video::VIDEO_FORMATS)) {
        errorMessage += "Not a valid Video format (" + video.getMediaFormat() + ").\n";
        validMedia = false;
    }
    if (video.getDirector().empty()) {
        errorMessage += "Missing director field.\n";
        validMedia = false;
    }
    if (video.getGenre().empty()) {
        errorMessage += "Missing genre field.\n";
        validMedia = false;
    }
    if (!isWithinRange(video.getCreationYear(), Media::AbstractMedia::MIN_RELEASE_YEAR, Media::Video::MAX_RELEASE_YEAR)) {
        errorMessage += "Not a valid release year: (" + std::to_string(video.getCreationYear()) + ").\n";
        validMedia = false;
    }
    if (!isWithinRange(video.getMediaLength(), Media::Video::MIN_VIDEO_LENGTH, Media::Video::MAX_VIDEO_LENGTH)) {
        errorMessage += "Video length is not valid: (" + std::to_string(video.getMediaLength()) + " min).\n";
        validMedia = false;
    }
    if (!video.matchesAspectRatio()) {
        errorMessage += "Video resolution must match 16:9 aspect ratio.\n";
        validMedia = false;
    }
    if (!isWithinRange(video.getFrameRate(), Media::Video::MIN_VIDEO_FRAME_RATE, Media::Video::MAX_VIDEO_FRAME_RATE)) {
        errorMessage += "Not a valid Video framerate: (" + std::to_string(video.getFrameRate()) + " fps).\n";
        validMedia = false;
    }

    if (!isWithinRange(video.getVideoColorDepth(), Media::Video::MIN_VIDEO_COLOR_DEPTH, Media::Video::MAX_VIDEO_COLOR_DEPTH)) {
        errorMessage += "Not a valid Video color depth: " + std::to_string(video.getVideoColorDepth()) + "-bit).\n";
        validMedia = false;
    }

    if (!errorMessage.empty()) {
        Model::Loggers::IConsoleLogger consoleLogger;
        consoleLogger.logMessage(errorMessage);
        throw MediaValidatorException(getErrorMessage());
    }
}

void MediaValidator::visit(const Media::EBook& ebook) const {

    const_cast<MediaValidator*>(this)->resetValidator();

    validateCommonAttributes(ebook);

    if (ebook.hasResolution()) {
        errorMessage += "EBook may not have a resolution.\n";
        validMedia = false;
    }
    if (!ebook.hasLength() || !ebook.measuredInPages()) {
        errorMessage += "EBook must have length set and must be measured in pages.\n";
        validMedia = false;
    }
    if (!isValidFormat(ebook.getMediaFormat(), Media::EBook::EBOOK_FORMATS)) {
        errorMessage += "Not a valid EBook format (" + ebook.getMediaFormat() + ").\n";
        validMedia = false;
    }
    if (ebook.getAuthor().empty()) {
        errorMessage += "Missing author field.\n";
        validMedia = false;
    }
    if (ebook.getPublisher().empty()) {
        errorMessage += "Missing publisher field.\n";
        validMedia = false;
    }
    if (!isWithinRange(ebook.getReleaseYear(), Media::AbstractMedia::MIN_RELEASE_YEAR, Media::AbstractMedia::MAX_RELEASE_YEAR)) {
        errorMessage += "Not a valid release year: (" + std::to_string(ebook.getReleaseYear()) + ").\n";
        validMedia = false;
    }
    if (!isWithinRange(ebook.getMediaLength(), Media::EBook::MIN_EBOOK_LENGTH, Media::EBook::MAX_EBOOK_LENGTH)) {
        errorMessage += "Not a valid EBook length: (" + std::to_string(ebook.getMediaLength()) + " pages).\n";
        validMedia = false;
    }
    if (ebook.getLanguage().empty()) {
        errorMessage += "Missing language field.\n";
        validMedia = false;
    }

    if (!errorMessage.empty()) {
        Model::Loggers::IConsoleLogger consoleLogger;
        consoleLogger.logMessage(errorMessage);
        throw MediaValidatorException(getErrorMessage());
    }


}

void MediaValidator::visit(const Media::Image& image) const {

    const_cast<MediaValidator*>(this)->resetValidator();

    validateCommonAttributes(image);

    if (!image.hasResolution()) {
        errorMessage += "Image must have a resolution.\n";
        validMedia = false;
    }
    if (image.hasLength()) {
        errorMessage += "Image cannot have a length.\n";
        validMedia = false;
    }
    if (!isValidFormat(image.getMediaFormat(), Media::Image::IMAGE_FORMATS)) {
        errorMessage += "Not a valid Image format (" + image.getMediaFormat() + ").\n";
        validMedia = false;
    }
    if (image.getDateCreated().empty()) {
        errorMessage += "Image must have creation date set.\n";
        validMedia = false;
    }
    if (image.getImageCreator().empty()) {
        errorMessage += "Image must have creator set.\n";
        validMedia = false;
    }
    if (image.getImageCategory().empty()) {
        errorMessage += "Image must have category set.\n";
        validMedia = false;
    }
    if (!isWithinRange(image.getImageBitDepth(), Media::Image::MIN_IMAGE_BITDEPTH, Media::Image::MAX_IMAGE_BITDEPTH)) {
        errorMessage += "Invalid Image bitdepth: " + std::to_string(image.getImageBitDepth()) + ".\n";
        validMedia = false;
    }
    if (!image.matchesAspectRatio()) {
        errorMessage += "Image resolution must match aspect ratio.\n";
        validMedia = false;
    }

    if (!errorMessage.empty()) {
        Model::Loggers::IConsoleLogger consoleLogger;
        consoleLogger.logMessage(errorMessage);
        throw MediaValidatorException(getErrorMessage());
    }
}

}
}

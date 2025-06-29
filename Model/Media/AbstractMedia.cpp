#include "AbstractMedia.h"

#include <string>

namespace Model {
namespace Media {

const unsigned int AbstractMedia::MIN_MEDIA_RATING = 1;
const unsigned int AbstractMedia::MAX_MEDIA_RATING = 100;
const unsigned int AbstractMedia::MIN_RELEASE_YEAR = 1950;
const unsigned int AbstractMedia::MAX_RELEASE_YEAR = 2030;

const std::string AbstractMedia::defaultName = "Unknown Name";
const std::string AbstractMedia::defaultUploader = "Unknown Uploader";
const std::string AbstractMedia::defaultFormat = "*.*";
const unsigned int AbstractMedia::defaultRating = 65;


AbstractMedia::AbstractMedia()
    : AbstractFile(),
    mediaName(defaultName),
    mediaUploader(defaultUploader),
    mediaFormat(defaultFormat),
    mediaRating(defaultRating)
{}


AbstractMedia::AbstractMedia(
    const std::string& path,
    float size,
    const std::string& name,
    const std::string& uploader,
    const std::string& format,
    unsigned int rating)
    : AbstractFile(path, size),
    mediaName(name),
    mediaUploader(uploader),
    mediaFormat(format),
    mediaRating(rating)
{}

AbstractMedia::AbstractMedia(const AbstractMedia& media)
    : AbstractFile(media),
    mediaName(media.mediaName),
    mediaUploader(media.mediaUploader),
    mediaFormat(media.mediaFormat),
    mediaRating(media.mediaRating)
{}

AbstractMedia& AbstractMedia::operator=(const AbstractMedia& media) {

    if (this != &media) {
        AbstractFile::operator=(media);
        mediaName = media.mediaName;
        mediaUploader = media.mediaUploader;
        mediaFormat = media.mediaFormat;
        mediaRating = media.mediaRating;
    }
    return *this;
}

const std::string& AbstractMedia::getMediaName() const { return mediaName; }
const std::string& AbstractMedia::getMediaUploader() const { return mediaUploader; }
const std::string& AbstractMedia::getMediaFormat() const { return mediaFormat; }
unsigned int AbstractMedia::getMediaRating() const { return mediaRating; }

void AbstractMedia::setMediaName(const std::string& name) { mediaName = name; }
void AbstractMedia::setMediaUploader(const std::string& uploader) { mediaUploader = uploader; }
void AbstractMedia::setMediaFormat(const std::string& format) { mediaFormat = format; }
void AbstractMedia::setMediaRating(unsigned int rating) { mediaRating = rating; }

}
}

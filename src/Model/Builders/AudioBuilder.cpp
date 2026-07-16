#include "AudioBuilder.h"
#include "Model/Media/Audio.h"
#include "Model/Visitors/MediaValidator.h"

#include <string>
#include <vector>
#include <cstdlib>

namespace Model {
namespace Builders {


const std::vector<std::string> AudioBuilder::AUDIO_ATTRIBUTES = {
    "path", "size", "name", "uploader", "format", "rating",
    "artist", "genre", "album", "releaseYear", "length", "bitrate",
    "samplerate", "bitdepth", "channels", "collaborators"
};


AudioBuilder::AudioBuilder()
    : audioPointer(new Model::Media::Audio()) {}


AudioBuilder::AudioBuilder(const Model::Media::Audio& audio)
    : audioPointer(audio.clone()) {}



AudioBuilder& AudioBuilder::setPath(const std::string& path) {
    editsToApply["path"] = path;
    return *this;
}
AudioBuilder& AudioBuilder::setSize(float size) {
    editsToApply["size"] = std::to_string(size);
    return *this;
}
AudioBuilder& AudioBuilder::setName(const std::string& name) {
    editsToApply["name"] = name;
    return *this;
}
AudioBuilder& AudioBuilder::setUploader(const std::string& uploader) {
    editsToApply["uploader"] = uploader;
    return *this;
}
AudioBuilder& AudioBuilder::setFormat(const std::string& format) {
    editsToApply["format"] = format;
    return *this;
}
AudioBuilder& AudioBuilder::setRating(unsigned int rating) {
    editsToApply["rating"] = std::to_string(rating);
    return *this;
}


AudioBuilder& AudioBuilder::setArtist(const std::string& art) {
    editsToApply["artist"] = art;
    return *this;
}
AudioBuilder& AudioBuilder::setGenre(const std::string& gnr) {
    editsToApply["genre"] = gnr;
    return *this;
}
AudioBuilder& AudioBuilder::setAlbum(const std::string& alb) {
    editsToApply["album"] = alb;
    return *this;
}
AudioBuilder& AudioBuilder::setReleaseYear(unsigned int year) {
    editsToApply["releaseYear"] = std::to_string(year);
    return *this;
}
AudioBuilder& AudioBuilder::setLengthInMinutes(unsigned int length) {
    editsToApply["length"] = std::to_string(length);
    return *this;
}
AudioBuilder& AudioBuilder::setBitRate(unsigned int br) {
    editsToApply["bitrate"] = std::to_string(br);
    return *this;
}
AudioBuilder& AudioBuilder::setSampleRate(float sr) {
    editsToApply["samplerate"] = std::to_string(sr);
    return *this;
}
AudioBuilder& AudioBuilder::setBitDepth(unsigned int bd) {
    editsToApply["bitdepth"] = std::to_string(bd);
    return *this;
}
AudioBuilder& AudioBuilder::setChannels(unsigned int ch) {
    editsToApply["channels"] = std::to_string(ch);
    return *this;
}
AudioBuilder& AudioBuilder::setCollaborators(const std::string& clb) {
    editsToApply["collaborators"] = clb;
    return *this;
}


Media::Audio* AudioBuilder::applyEdits() const {

    Media::Audio* edited = audioPointer->clone();

    if (editsToApply.find("path") != editsToApply.end()) {
        edited->setFilePath(editsToApply.at("path"));
    }
    if (editsToApply.find("size") != editsToApply.end()) {
        edited->setFileSize(std::stof(editsToApply.at("size")));
    }
    if (editsToApply.find("name") != editsToApply.end()) {
        edited->setMediaName(editsToApply.at("name"));
    }
    if (editsToApply.find("uploader") != editsToApply.end()) {
        edited->setMediaUploader(editsToApply.at("uploader"));
    }
    if (editsToApply.find("format") != editsToApply.end()) {
        edited->setMediaFormat(editsToApply.at("format"));
    }
    if (editsToApply.find("rating") != editsToApply.end()) {
        edited->setMediaRating(std::stoi(editsToApply.at("rating")));
    }

    if (editsToApply.find("artist") != editsToApply.end()) {
        edited->setArtist(editsToApply.at("artist"));
    }
    if (editsToApply.find("genre") != editsToApply.end()) {
        edited->setGenre(editsToApply.at("genre"));
    }
    if (editsToApply.find("album") != editsToApply.end()) {
        edited->setAlbum(editsToApply.at("album"));
    }

    if (editsToApply.find("releaseYear") != editsToApply.end()) {
        edited->setReleaseYear(std::stoi(editsToApply.at("releaseYear")));
    }
    if (editsToApply.find("length") != editsToApply.end()) {
        edited->setMediaLength(std::stoi(editsToApply.at("length")));
    }
    if (editsToApply.find("bitrate") != editsToApply.end()) {
        edited->setBitRate(std::stoi(editsToApply.at("bitrate")));
    }

    if (editsToApply.find("samplerate") != editsToApply.end()) {
        edited->setSampleRate(std::stof(editsToApply.at("samplerate")));
    }

    if (editsToApply.find("bitdepth") != editsToApply.end()) {
        edited->setBitDepth(std::stoi(editsToApply.at("bitdepth")));
    }
    if (editsToApply.find("channels") != editsToApply.end()) {
        edited->setAudioChannels(std::stoi(editsToApply.at("channels")));
    }

    if (editsToApply.find("collaborators") != editsToApply.end()) {
        edited->setCollaborators(editsToApply.at("collaborators"));
    }

    return edited;
}



std::shared_ptr<Model::Media::AbstractMedia> AudioBuilder::buildMedia() const {

    Media::Audio* edited = applyEdits();

    Visitors::MediaValidator editedValidator;
    try {
        edited->accept(editedValidator);
    }
    catch (const Visitors::MediaValidatorException& e) {
        delete edited;
        throw;
    }

    return std::shared_ptr<Model::Media::AbstractMedia>(edited);
}

}
}

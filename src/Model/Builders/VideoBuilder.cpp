#include "VideoBuilder.h"
#include "Model/Media/Video.h"
#include "Model/Visitors/MediaValidator.h"

#include <string>
#include <vector>
#include <cstdlib>

namespace Model {
namespace Builders {

const std::vector<std::string> VideoBuilder::VIDEO_ATTRIBUTES = {
    "path", "size", "name", "uploader", "format", "rating",
    "director", "genre", "releaseYear", "length", "framerate",
    "width", "height", "colordepth", "subtitles", "language"
};

VideoBuilder::VideoBuilder()
    : videoPointer(new Model::Media::Video()) {}

VideoBuilder::VideoBuilder(const Model::Media::Video& video)
    : videoPointer(video.clone()) {}



VideoBuilder& VideoBuilder::setPath(const std::string& path) {
    editsToApply["path"] = path;
    return *this;
}
VideoBuilder& VideoBuilder::setSize(float size) {
    editsToApply["size"] = std::to_string(size);
    return *this;
}
VideoBuilder& VideoBuilder::setName(const std::string& name) {
    editsToApply["name"] = name;
    return *this;
}
VideoBuilder& VideoBuilder::setUploader(const std::string& uploader) {
    editsToApply["uploader"] = uploader;
    return *this;
}
VideoBuilder& VideoBuilder::setFormat(const std::string& format) {
    editsToApply["format"] = format;
    return *this;
}
VideoBuilder& VideoBuilder::setRating(unsigned int rating) {
    editsToApply["rating"] = std::to_string(rating);
    return *this;
}


VideoBuilder& VideoBuilder::setDirector(const std::string& dir) {
    editsToApply["director"] = dir;
    return *this;
}
VideoBuilder& VideoBuilder::setGenre(const std::string& gnr) {
    editsToApply["genre"] = gnr;
    return *this;
}
VideoBuilder& VideoBuilder::setReleaseYear(unsigned int year) {
    editsToApply["releaseYear"] = std::to_string(year);
    return *this;
}
VideoBuilder& VideoBuilder::setLength(unsigned int length) {
    editsToApply["length"] = std::to_string(length);
    return *this;
}
VideoBuilder& VideoBuilder::setFrameRate(unsigned int fr) {
    editsToApply["framerate"] = std::to_string(fr);
    return *this;
}
VideoBuilder& VideoBuilder::setResolutionWidth(unsigned int width) {
    editsToApply["width"] = std::to_string(width);
    return *this;
}
VideoBuilder& VideoBuilder::setResolutionHeight(unsigned int height) {
    editsToApply["height"] = std::to_string(height);
    return *this;
}
VideoBuilder& VideoBuilder::setColorDepth(unsigned int depth) {
    editsToApply["colordepth"] = std::to_string(depth);
    return *this;
}
VideoBuilder& VideoBuilder::setSubtitles(const std::string& subs) {
    editsToApply["subtitles"] = subs;
    return *this;
}
VideoBuilder& VideoBuilder::setLanguage(const std::string& lang) {
    editsToApply["language"] = lang;
    return *this;
}


Media::Video* VideoBuilder::applyEdits() const {

    Media::Video* edited = videoPointer->clone();

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

    if (editsToApply.find("director") != editsToApply.end()) {
        edited->setDirector(editsToApply.at("director"));
    }
    if (editsToApply.find("genre") != editsToApply.end()) {
        edited->setGenre(editsToApply.at("genre"));
    }
    if (editsToApply.find("releaseYear") != editsToApply.end()) {
        edited->setCreationYear(std::stoi(editsToApply.at("releaseYear")));
    }
    if (editsToApply.find("length") != editsToApply.end()) {
        edited->setMediaLength(std::stoi(editsToApply.at("length")));
    }
    if (editsToApply.find("framerate") != editsToApply.end()) {
        edited->setFrameRate(std::stoi(editsToApply.at("framerate")));
    }
    if (editsToApply.find("width") != editsToApply.end()) {
        edited->setResolution( { std::stoi(editsToApply.at("width")), edited->getResolution().second} );
    }
    if (editsToApply.find("height") != editsToApply.end()) {
        edited->setResolution( { edited->getResolution().first, std::stoi(editsToApply.at("height")) } );
    }
    if (editsToApply.find("colordepth") != editsToApply.end()) {
        edited->setVideoColorDepth(std::stoi(editsToApply.at("colordepth")));
    }
    if (editsToApply.find("subtitles") != editsToApply.end()) {
        edited->setSubtitles(editsToApply.at("subtitles"));
    }
    if (editsToApply.find("language") != editsToApply.end()) {
        edited->setLanguage(editsToApply.at("language"));
    }

    return edited;
}

std::shared_ptr<Model::Media::AbstractMedia> VideoBuilder::buildMedia() const {

    Media::Video* edited = applyEdits();

    Visitors::MediaValidator editedValidator;
    try {
        edited->accept(editedValidator);
    }
    catch (const Visitors::MediaValidatorException& e) {
        delete edited;
        throw;
    }

    return std::shared_ptr
        <Model::Media::AbstractMedia>(edited);
}

}
}

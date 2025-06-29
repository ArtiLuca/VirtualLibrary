#include "ImageBuilder.h"
#include "Model/Media/Image.h"
#include "Model/Visitors/MediaValidator.h"

#include <string>
#include <vector>
#include <cstdlib>

namespace Model {
namespace Builders {

const std::vector<std::string> ImageBuilder::IMAGE_ATTRIBUTES = {
    "path", "size", "name", "uploader", "format", "rating",
    "dateCreated", "imageCreator", "imageCategory", "resolutionWidth",
    "resolutionHeight", "aspectWidth", "aspectHeight", "bitdepth",
    "compressed", "location"
};


ImageBuilder::ImageBuilder()
    : imagePointer(new Model::Media::Image()) {}

ImageBuilder::ImageBuilder(const Model::Media::Image& image)
    : imagePointer(image.clone()) {}



ImageBuilder& ImageBuilder::setPath(const std::string& path) {
    editsToApply["path"] = path;
    return *this;
}
ImageBuilder& ImageBuilder::setSize(float size) {
    editsToApply["size"] = std::to_string(size);
    return *this;
}
ImageBuilder& ImageBuilder::setName(const std::string& name) {
    editsToApply["name"] = name;
    return *this;
}
ImageBuilder& ImageBuilder::setUploader(const std::string& uploader) {
    editsToApply["uploader"] = uploader;
    return *this;
}
ImageBuilder& ImageBuilder::setFormat(const std::string& format) {
    editsToApply["format"] = format;
    return *this;
}
ImageBuilder& ImageBuilder::setRating(unsigned int rating) {
    editsToApply["rating"] = std::to_string(rating);
    return *this;
}


ImageBuilder& ImageBuilder::setDateCreated(const std::string& created) {
    editsToApply["dateCreated"] = created;
    return *this;
}
ImageBuilder& ImageBuilder::setCreator(const std::string& creator) {
    editsToApply["imageCreator"] = creator;
    return *this;
}
ImageBuilder& ImageBuilder::setCategory(const std::string& category) {
    editsToApply["imageCategory"] = category;
    return *this;
}
ImageBuilder& ImageBuilder::setResolutionWidth(unsigned int resW) {
    editsToApply["resolutionWidth"] = std::to_string(resW);
    return *this;
}
ImageBuilder& ImageBuilder::setResolutionHeight(unsigned int resH) {
    editsToApply["resolutionHeight"] = std::to_string(resH);
    return *this;
}
ImageBuilder& ImageBuilder::setAspectRatioWidth(unsigned int aspW) {
    editsToApply["aspectWidth"] = std::to_string(aspW);
    return *this;
}
ImageBuilder& ImageBuilder::setAspectRatioHeight(unsigned int aspH) {
    editsToApply["aspectHeight"] = std::to_string(aspH);
    return *this;
}
ImageBuilder& ImageBuilder::setImageBitdepth(unsigned int bd) {
    editsToApply["bitdepth"] = std::to_string(bd);
    return *this;
}
ImageBuilder& ImageBuilder::setCompression(bool cmpr) {
    editsToApply["compressed"] = (cmpr ? "true" : "false");
    return *this;
}
ImageBuilder& ImageBuilder::setLocationTaken(const std::string& location) {
    editsToApply["location"] = location;
    return *this;
}

Media::Image* ImageBuilder::applyEdits() const {

    Media::Image* edited = imagePointer->clone();

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

    if (editsToApply.find("dateCreated") != editsToApply.end()) {
        edited->setDateCreated(editsToApply.at("dateCreated"));
    }
    if (editsToApply.find("imageCreator") != editsToApply.end()) {
        edited->setImageCreator(editsToApply.at("imageCreator"));
    }
    if (editsToApply.find("imageCategory") != editsToApply.end()) {
        edited->setImageCategory(editsToApply.at("imageCategory"));
    }
    if (editsToApply.find("resolutionWidth") != editsToApply.end()) {
        edited->setResolution( { std::stoi(editsToApply.at("resolutionWidth")), edited->getResolution().second } );
    }
    if (editsToApply.find("resolutionHeight") != editsToApply.end()) {
        edited->setResolution( {edited->getResolution().first, std::stoi(editsToApply.at("resolutionHeight")) } );
    }
    if (editsToApply.find("aspectWidth") != editsToApply.end()) {
        edited->setImageAspectRatio( { std::stoi(editsToApply.at("aspectWidth")), edited->getImageAspectRatio().second } );
    }
    if (editsToApply.find("aspectHeight") != editsToApply.end()) {
        edited->setImageAspectRatio( { edited->getImageAspectRatio().first, std::stoi(editsToApply.at("aspectHeight")) } );
    }
    if (editsToApply.find("bitdepth") != editsToApply.end()) {
        edited->setImageBitDepth(std::stoi(editsToApply.at("bitdepth")));
    }
    if (editsToApply.find("compressed") != editsToApply.end()) {
        bool cmpr = (editsToApply.at("compressed") == "true") ? "true" : "false";
        edited->setImageCompression(cmpr);
    }
    if (editsToApply.find("location") != editsToApply.end()) {
        edited->setImageLocationTaken(editsToApply.at("location"));
    }

    return edited;
}


std::shared_ptr<Model::Media::AbstractMedia> ImageBuilder::buildMedia() const {

    Media::Image* edited = applyEdits();

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



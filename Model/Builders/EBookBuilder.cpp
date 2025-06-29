#include "EBookBuilder.h"
#include "Model/Media/EBook.h"
#include "Model/Visitors/MediaValidator.h"

#include <string>
#include <vector>
#include <cstdlib>

namespace Model {
namespace Builders {


const std::vector<std::string> EBookBuilder::EBOOK_ATTRIBUTES = {
    "path", "size", "name", "uploader", "format", "rating",
    "author", "publisher", "releaseYear", "isbn", "length",
    "category", "language", "coverPath", "hasImages"
};


EBookBuilder::EBookBuilder()
    : ebookPointer(new Model::Media::EBook()) {}


EBookBuilder::EBookBuilder(const Model::Media::EBook& ebook)
    : ebookPointer(ebook.clone()) {}



EBookBuilder& EBookBuilder::setPath(const std::string& path) {
    editsToApply["path"] = path;
    return *this;
}
EBookBuilder& EBookBuilder::setSize(float size) {
    editsToApply["size"] = std::to_string(size);
    return *this;
}
EBookBuilder& EBookBuilder::setName(const std::string& name) {
    editsToApply["name"] = name;
    return *this;
}
EBookBuilder& EBookBuilder::setUploader(const std::string& uploader) {
    editsToApply["uploader"] = uploader;
    return *this;
}
EBookBuilder& EBookBuilder::setFormat(const std::string& format) {
    editsToApply["format"] = format;
    return *this;
}
EBookBuilder& EBookBuilder::setRating(unsigned int rating) {
    editsToApply["rating"] = std::to_string(rating);
    return *this;
}


EBookBuilder& EBookBuilder::setAuthor(const std::string& auth) {
    editsToApply["author"] = auth;
    return *this;
}
EBookBuilder& EBookBuilder::setPublisher(const std::string& pbl) {
    editsToApply["publisher"] = pbl;
    return *this;
}
EBookBuilder& EBookBuilder::setReleaseYear(unsigned int year) {
    editsToApply["releaseYear"] = std::to_string(year);
    return *this;
}
EBookBuilder& EBookBuilder::setISBN(const std::string& isbn) {
    editsToApply["isbn"] = isbn;
    return *this;
}
EBookBuilder& EBookBuilder::setLengthInPages(unsigned int length) {
    editsToApply["length"] = std::to_string(length);
    return *this;
}
EBookBuilder& EBookBuilder::setCategory(const std::string& ctg) {
    editsToApply["category"] = ctg;
    return *this;
}
EBookBuilder& EBookBuilder::setLanguage(const std::string& lang) {
    editsToApply["language"] = lang;
    return *this;
}
EBookBuilder& EBookBuilder::setCoverImagePath(const std::string& cp) {
    editsToApply["coverPath"] = cp;
    return *this;
}
EBookBuilder& EBookBuilder::setHasImages(bool img) {
    editsToApply["hasImages"] = (img ? "true" : "false");
    return *this;
}



Media::EBook* EBookBuilder::applyEdits() const {

    Media::EBook* edited = ebookPointer->clone();

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

    if (editsToApply.find("author") != editsToApply.end()) {
        edited->setAuthor(editsToApply.at("author"));
    }
    if (editsToApply.find("publisher") != editsToApply.end()) {
        edited->setPublisher(editsToApply.at("publisher"));
    }
    if (editsToApply.find("releaseYear") != editsToApply.end()) {
        edited->setReleaseYear(std::stoi(editsToApply.at("releaseYear")));
    }
    if (editsToApply.find("isbn") != editsToApply.end()) {
        edited->setISBN(editsToApply.at("isbn"));
    }
    if (editsToApply.find("length") != editsToApply.end()) {
        edited->setMediaLength(std::stoi(editsToApply.at("length")));
    }
    if (editsToApply.find("category") != editsToApply.end()) {
        edited->setCategory(editsToApply.at("category"));
    }
    if (editsToApply.find("language") != editsToApply.end()) {
        edited->setLanguage(editsToApply.at("language"));
    }
    if (editsToApply.find("coverPath") != editsToApply.end()) {
        edited->setCoverImagePath(editsToApply.at("coverPath"));
    }
    if (editsToApply.find("hasImages") != editsToApply.end()) {
        bool img = (editsToApply.at("hasImages") == "true") ? true : false;
        edited->setImages(img);
    }
    return edited;
}

std::shared_ptr<Model::Media::AbstractMedia> EBookBuilder::buildMedia() const {

    Media::EBook* edited = applyEdits();

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





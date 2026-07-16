#include "Image.h"
#include "Model/Visitors/IVisitor.h"
#include "Model/Visitors/IConstVisitor.h"

#include <string>
#include <vector>
#include <utility>

namespace Model {
namespace Media {

const unsigned int Image::MIN_IMAGE_RESOLUTION_WIDTH = 200;
const unsigned int Image::MAX_IMAGE_RESOLUTION_WIDTH = 8000;
const unsigned int Image::MIN_IMAGE_RESOLUTION_HEIGHT = 200;
const unsigned int Image::MAX_IMAGE_RESOLUTION_HEIGHT = 8000;
const unsigned int Image::MIN_ASPECT_RATIO_VALUE = 1;
const unsigned int Image::MIN_IMAGE_BITDEPTH = 8;
const unsigned int Image::MAX_IMAGE_BITDEPTH = 32;
const std::vector<std::string> Image::IMAGE_FORMATS = { "JPEG", "PNG", "WebP", "TIFF", "AVIF", "BMP" };

const std::string Image::defaultImageFormat = "JPEG";
const float Image::defaultImageSize = 1.5;
const std::string Image::defaultImageCreationDate = "21-12-1997";
const std::string Image::defaultImageCreator = "Unknown Creator";
const std::string Image::defaultImageCategory = "Unknown Category";
const std::pair<int, int> Image::defaultImageResolution = { 1920, 1080 };
const std::pair<int, int> Image::defaultImageAspectRatio = { 16, 9 };
const unsigned int Image::defaultImageBitDepth = 16;
const bool Image::defaultImageCompression = true;
const std::string Image::defaultImageLocation = "Unknown Location";


Image::Image()
    : AbstractFile(AbstractFile::defaultPath, defaultImageSize),
    AbstractMedia(AbstractFile::defaultPath, defaultImageSize, AbstractMedia::defaultName, AbstractMedia::defaultUploader, defaultImageFormat, AbstractMedia::defaultRating),
    dateCreated(defaultImageCreationDate),
    imageCreator(defaultImageCreator),
    imageCategory(defaultImageCategory),
    imageResolution(defaultImageResolution),
    imageAspectRatio(defaultImageAspectRatio),
    imageBitDepth(defaultImageBitDepth),
    compression(defaultImageCompression),
    locationTaken(defaultImageLocation)
{}


Image::Image(const Image& image)
    : AbstractFile(image),
    AbstractMedia(image),
    dateCreated(image.dateCreated),
    imageCreator(image.imageCreator),
    imageCategory(image.imageCategory),
    imageResolution(image.imageResolution),
    imageAspectRatio(image.imageAspectRatio),
    imageBitDepth(image.imageBitDepth),
    compression(image.compression),
    locationTaken(image.locationTaken)
{}


Image& Image::operator=(const Image& image) {

    if (this != &image) {
        AbstractMedia::operator=(image);
        this->dateCreated = image.dateCreated;
        this->imageCreator = image.imageCreator;
        this->imageCategory = image.imageCategory;
        this->imageResolution = image.imageResolution;
        this->imageAspectRatio = image.imageAspectRatio;
        this->imageBitDepth = image.imageBitDepth;
        this->compression = image.compression;
        this->locationTaken = image.locationTaken;
    }
    return *this;
}


const std::string& Image::getDateCreated() const { return dateCreated; }
const std::string& Image::getImageCreator() const { return imageCreator; }
const std::string& Image::getImageCategory() const { return imageCategory; }
std::pair<int, int> Image::getImageAspectRatio() const { return imageAspectRatio; }
unsigned int Image::getImageBitDepth() const { return imageBitDepth; }
bool Image::isCompressed() const { return compression; }
const std::string& Image::getLocationTaken() const { return locationTaken; }
std::pair<int, int> Image::getResolution() const { return imageResolution; }


void Image::setDateCreated(const std::string& created) { dateCreated = created; }
void Image::setImageCreator(const std::string& creator) { imageCreator = creator; }
void Image::setImageCategory(const std::string& ctg) { imageCategory = ctg; }
void Image::setImageAspectRatio(std::pair<int, int> ar) { imageAspectRatio = ar; }
void Image::setImageBitDepth(unsigned int bd) { imageBitDepth = bd; }
void Image::setImageCompression(bool cmpr) { compression = cmpr; }
void Image::setImageLocationTaken(const std::string& loc) { locationTaken = loc; }
void Image::setResolution(std::pair<int, int> resolution) { imageResolution = resolution; }



float Image::getAspectAsFloat() const {

    float ratioAsFloat = static_cast<float>(imageAspectRatio.first) / imageAspectRatio.second;
    return ratioAsFloat;
}

float Image::getMegaPixels() const {

    int w = imageResolution.first;
    int h = imageResolution.second;
    return static_cast<float>(w * h) / 1000000.f;
}



bool Image::matchesAspectRatio() const {

    if (imageResolution.first * imageAspectRatio.second == imageResolution.second * imageAspectRatio.first)
        return true;
    else
        return false;
}


bool Image::hasLength() const { return false; }

bool Image::hasResolution() const { return true; }

std::string Image::displayStringType() const { return "Image"; }


Image* Image::clone() const {
    return new Image(*this);
}

void Image::accept(Visitors::IVisitor& visitor) { visitor.visit(*this); }

void Image::accept(Visitors::IConstVisitor& visitor) const { visitor.visit(*this); }


QJsonObject Image::toJson() const {

    // creo un oggeto QJsonObject vuoto, visto come una mappa di coppie ("chiave", "valore")
    // (visto internamente come QMap<QString, QJsonValue>)
    QJsonObject json;

    // inserisco il tipo del media
    json["mediaType"] = "IMAGE";

    // per ciascun attributo del media salvo nel campo "chiave" dell'oggetto QJsonObject il nome dell'attributo
    // mentre salvo nel campo "valore" il valore dell'attributo, convertito in un tipo che puo' essere gestito da QJsonValue
    // I tipi 'float' e 'double' possono essere assegnati direttamente, in quando QJsonValue puo' gestirli direttamente

    json["name"] = QString::fromStdString(getMediaName());
    json["uploader"] = QString::fromStdString(getMediaUploader());
    json["format"] = QString::fromStdString(getMediaFormat());
    json["rating"] = static_cast<int>(getMediaRating());

    json["path"] = QString::fromStdString(getFilePath());
    json["size"] = getFileSize();

    json["dateCreated"] = QString::fromStdString(getDateCreated());
    json["imageCreator"] = QString::fromStdString(getImageCreator());
    json["imageCategory"] = QString::fromStdString(getImageCategory());
    json["resolutionWidth"] = imageResolution.first;
    json["resolutionHeight"] = imageResolution.second;
    json["aspectWidth"] = imageAspectRatio.first;
    json["aspectHeight"] = imageAspectRatio.second;
    json["bitdepth"] = static_cast<int>(imageBitDepth);
    json["compressed"] = compression;
    json["location"] = QString::fromStdString(getLocationTaken());

    return json; // oggetto QJsonObject con attributi del media
}


void Image::fromJson(const QJsonObject& obj) {

    // si assume che 'obj' sia un oggetto QJsonObject valido che contiene i dati di un media
    // Per ciascun campo verifico se la chiave e' presente e se ha il tipo corrispondente corretto
    // poi faccio la conversione del tipo trovato (QJsonValue) al tipo dell'attributo prima dell'assegnazione

    // campi ereditati da AbstractFile
    if (obj.contains("path") && obj["path"].isString()) {
        setFilePath(obj["path"].toString().toStdString());
    }
    if (obj.contains("size") && obj["size"].isDouble()) {
        setFileSize(static_cast<float>(obj["size"].toDouble()));
    }

    // campi ereditati da AbstractMedia
    if (obj.contains("name") && obj["name"].isString()) {
        setMediaName(obj["name"].toString().toStdString());
    }
    if (obj.contains("uploader") && obj["uploader"].isString()) {
        setMediaUploader(obj["uploader"].toString().toStdString());
    }
    if (obj.contains("format") && obj["format"].isString()) {
        setMediaFormat(obj["format"].toString().toStdString());
    }
    if (obj.contains("rating") && obj["rating"].isDouble()) {
        setMediaRating(static_cast<unsigned int>(obj["rating"].toInt()));
    }

    // campi di Image
    if (obj.contains("dateCreated") && obj["dateCreated"].isString()) {
        dateCreated = obj["dateCreated"].toString().toStdString();
    }
    if (obj.contains("imageCreator") && obj["imageCreator"].isString()) {
        imageCreator = obj["imageCreator"].toString().toStdString();
    }
    if (obj.contains("imageCategory") && obj["imageCategory"].isString()) {
        imageCategory = obj["imageCategory"].toString().toStdString();
    }
    if ( (obj.contains("resolutionWidth") && obj["resolutionWidth"].isDouble())
        && (obj.contains("resolutionHeight") && obj["resolutionHeight"].isDouble()) ) {
        int resW = obj["resolutionWidth"].toInt();
        int resH = obj["resolutionHeight"].toInt();
        imageResolution = std::make_pair(resW, resH);
    }
    if ( (obj.contains("aspectWidth") && obj["aspectWidth"].isDouble())
        && (obj.contains("aspectHeight") && obj["aspectHeight"].isDouble()) ) {
        int aspW = obj["aspectWidth"].toInt();
        int aspH = obj["aspectHeight"].toInt();
        imageAspectRatio = std::make_pair(aspW, aspH);
    }
    if (obj.contains("bitdepth") && obj["bitdepth"].isDouble()) {
        imageBitDepth = static_cast<unsigned int>(obj["bitdepth"].toInt());
    }
    if (obj.contains("compressed") && obj["compressed"].isBool()) {
        compression = obj["compressed"].toBool();
    }
    if (obj.contains("location") && obj["location"].isString()) {
        locationTaken = obj["location"].toString().toStdString();
    }
}


}
}

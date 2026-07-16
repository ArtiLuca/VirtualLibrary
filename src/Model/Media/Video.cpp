#include "Video.h"
#include "Model/Visitors/IVisitor.h"
#include "Model/Visitors/IConstVisitor.h"

#include <string>
#include <vector>
#include <utility>

namespace Model {
namespace Media {

const unsigned int Video::MIN_VIDEO_LENGTH = 45;
const unsigned int Video::MAX_VIDEO_LENGTH = 220;
const unsigned int Video::MIN_VIDEO_RESOLUTION_WIDTH = 640;
const unsigned int Video::MAX_VIDEO_RESOLUTION_WIDTH = 7680;
const unsigned int Video::MIN_VIDEO_RESOLUTION_HEIGHT = 360;
const unsigned int Video::MAX_VIDEO_RESOLUTION_HEIGHT = 4320;
const unsigned int Video::MIN_VIDEO_FRAME_RATE = 24;
const unsigned int Video::MAX_VIDEO_FRAME_RATE = 120;
const std::pair<int, int> Video::VIDEO_ASPECT_RATIO = { 16, 9 };
const unsigned int Video::MIN_VIDEO_COLOR_DEPTH = 8;
const unsigned int Video::MAX_VIDEO_COLOR_DEPTH = 16;
const unsigned int Video::MIN_COLOR_DEPTH_HDR = 12;
const std::vector<std::string> Video::VIDEO_FORMATS = { "AVI", "WMV", "FLV", "WebM", "MP4", "MOV", "MKV", "M4V" };

const std::string Video::defaultVideoFormat = "MP4";
const float Video::defaultVideoSize = 800.0;
const std::string Video::defaultVideoDirector = "Director Uknown";
const std::string Video::defaultVideoGenre = "Genre Uknown";
const unsigned int Video::defaultVideoReleaseYear = 1997;
const unsigned int Video::defaultVideoLength = 90;
const unsigned int Video::defaultVideoFrameRate = 60;
const std::pair<int, int> Video::defaultVideoResolution = { 1920, 1080 };
const unsigned int Video::defaultVideoColorDepth = 8;
const std::string Video::defaultSubtitles = "No Subtitles";
const std::string Video::defaultVideoLanguage = "Language Unknown";


Video::Video()
    : AbstractFile(AbstractFile::defaultPath, defaultVideoSize),
    AbstractMedia(AbstractFile::defaultPath, defaultVideoSize, AbstractMedia::defaultName, AbstractMedia::defaultUploader, defaultVideoFormat, AbstractMedia::defaultRating),
    director(defaultVideoDirector),
    genre(defaultVideoGenre),
    creationYear(defaultVideoReleaseYear),
    lengthInMinutes(defaultVideoLength),
    frameRate(defaultVideoFrameRate),
    videoResolution(defaultVideoResolution),
    videoColorDepth(defaultVideoColorDepth),
    subtitles(defaultSubtitles),
    language(defaultVideoLanguage)
{}


Video::Video(const Video& video)
    : AbstractFile(video),
    AbstractMedia(video),
    director(video.director),
    genre(video.genre),
    creationYear(video.creationYear),
    lengthInMinutes(video.lengthInMinutes),
    frameRate(video.frameRate),
    videoResolution(video.videoResolution),
    videoColorDepth(video.videoColorDepth),
    subtitles(video.subtitles),
    language(video.language)
{}


Video& Video::operator=(const Video& video) {
    if (this != &video) {
        AbstractMedia::operator=(video);
        this->director = video.director;
        this->genre = video.genre;
        this->creationYear = video.creationYear;
        this->lengthInMinutes = video.lengthInMinutes;
        this->frameRate = video.frameRate;
        this->videoResolution = video.videoResolution;
        this->videoColorDepth = video.videoColorDepth;
        this->subtitles = video.subtitles;
        this->language = video.language;
    }
    return *this;
}


const std::string& Video::getDirector() const { return director; }
const std::string& Video::getGenre() const { return genre; }
unsigned int Video::getCreationYear() const { return creationYear; }
unsigned int Video::getFrameRate() const { return frameRate; }
const std::string& Video::getLanguage() const { return language; }
unsigned int Video::getVideoColorDepth() const { return videoColorDepth; }
const std::string& Video::getSubtitles() const { return subtitles; }
unsigned int Video::getMediaLength() const { return lengthInMinutes; }
std::pair<int, int> Video::getResolution() const { return videoResolution; }


void Video::setDirector(const std::string& dir) { director = dir; }
void Video::setGenre(const std::string& gnr) { genre = gnr; }
void Video::setCreationYear(unsigned int year) { creationYear = year; }
void Video::setFrameRate(unsigned int fr) { frameRate = fr; }
void Video::setLanguage(const std::string& lang) { language = lang; }
void Video::setVideoColorDepth(unsigned int depth) { videoColorDepth = depth; }
void Video::setSubtitles(const std::string& subs) { subtitles = subs; }
void Video::setMediaLength(unsigned int length) { lengthInMinutes = length; }
void Video::setResolution(std::pair<int, int> res) { videoResolution = res; }

bool Video::supportsHDR() const { return videoColorDepth >= MIN_COLOR_DEPTH_HDR; }

std::string Video::getVideoDuration() const {

    std::string dur = "Video Duration: ";
    if (lengthInMinutes > 60) {
        dur += std::to_string(lengthInMinutes / 60) + " hours, " + std::to_string(lengthInMinutes % 60) + " min.";
    }
    else {
        dur += std::to_string(lengthInMinutes % 60) + " minutes";
    }
    return dur;
}

bool Video::matchesAspectRatio() const {
    return (videoResolution.first * VIDEO_ASPECT_RATIO.second == videoResolution.second * VIDEO_ASPECT_RATIO.first);
}

bool Video::hasResolution() const { return true; }

bool Video::measuredInPages() const { return false; }

bool Video::hasLength() const { return true; }

std::string Video::displayStringType() const { return "Video"; }


Video* Video::clone() const {
    return new Video(*this);
}

void Video::accept(Visitors::IVisitor& visitor) {
    visitor.visit(*this);
}

void Video::accept(Visitors::IConstVisitor& visitor) const {
    visitor.visit(*this);
}


QJsonObject Video::toJson() const {

    // creo un oggeto QJsonObject vuoto, visto come una mappa di coppie ("chiave", "valore")
    // (visto internamente come QMap<QString, QJsonValue>)
    QJsonObject json;

    // inserisco il tipo del media
    json["mediaType"] = "VIDEO";

    // per ciascun attributo del media salvo nel campo "chiave" dell'oggetto QJsonObject il nome dell'attributo
    // mentre salvo nel campo "valore" il valore dell'attributo, convertito in un tipo che puo' essere gestito da QJsonValue
    // I tipi 'float' e 'double' possono essere assegnati direttamente, in quando QJsonValue puo' gestirli direttamente

    json["name"] = QString::fromStdString(getMediaName());
    json["uploader"] = QString::fromStdString(getMediaUploader());
    json["format"] = QString::fromStdString(getMediaFormat());
    json["rating"] = static_cast<int>(getMediaRating());

    json["path"] = QString::fromStdString(getFilePath());
    json["size"] = getFileSize();

    json["director"] = QString::fromStdString(getDirector());
    json["genre"] = QString::fromStdString(getGenre());
    json["releaseYear"] = static_cast<int>(creationYear);
    json["length"] = static_cast<int>(lengthInMinutes);
    json["framerate"] = static_cast<int>(frameRate);
    json["width"] = videoResolution.first;
    json["height"] = videoResolution.second;
    json["colordepth"] = static_cast<int>(videoColorDepth);
    json["subtitles"] = QString::fromStdString(subtitles);
    json["language"] = QString::fromStdString(language);

    return json; // oggetto QJsonObject con attributi del media

}


void Video::fromJson(const QJsonObject& obj)  {

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

    // campi di Video
    if (obj.contains("director") && obj["director"].isString()) {
        director = obj["director"].toString().toStdString();
    }
    if (obj.contains("genre") && obj["genre"].isString()) {
        genre = obj["genre"].toString().toStdString();
    }
    if (obj.contains("releaseYear") && obj["releaseYear"].isDouble()) {
        creationYear = static_cast<unsigned int>(obj["releaseYear"].toInt());
    }
    if (obj.contains("length") && obj["length"].isDouble()) {
        lengthInMinutes = static_cast<unsigned int>(obj["length"].toInt());
    }
    if (obj.contains("framerate") && obj["framerate"].isDouble()) {
        frameRate = static_cast<unsigned int>(obj["framerate"].toInt());
    }
    if ( (obj.contains("width") && obj["width"].isDouble())
        && (obj.contains("height") && obj["height"].isDouble()) ) {
        int w = obj["width"].toInt();
        int h = obj["height"].toInt();
        videoResolution = std::make_pair(w, h);
    }
    if (obj.contains("colordepth") && obj["colordepth"].isDouble()) {
        videoColorDepth = static_cast<unsigned int>(obj["colordepth"].toInt());
    }
    if (obj.contains("subtitles") && obj["subtitles"].isString()) {
        subtitles = obj["subtitles"].toString().toStdString();
    }
    if (obj.contains("language") && obj["language"].isString()) {
        language = obj["language"].toString().toStdString();
    }
}

}
}

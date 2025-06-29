#include "Audio.h"
#include "Model/Visitors/IVisitor.h"
#include "Model/Visitors/IConstVisitor.h"

#include <string>
#include <vector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>


namespace Model {
namespace Media {

const unsigned int Audio::MIN_AUDIO_LENGTH = 1;
const unsigned int Audio::MAX_AUDIO_LENGTH = 15;
const unsigned int Audio::MIN_AUDIO_BIT_RATE = 32;
const unsigned int Audio::MAX_AUDIO_BITRATE = 320;
const float Audio::MIN_AUDIO_SAMPLE_RATE = 22.0;
const float Audio::MAX_AUDIO_SAMPLE_RATE = 192.0;
const unsigned int Audio::MIN_AUDIO_BIT_DEPTH = 8;
const unsigned int Audio::MAX_AUDIO_BIT_DEPTH = 32;
const unsigned int Audio::MIN_AUDIO_CHANNELS = 1;
const unsigned int Audio::MAX_AUDIO_CHANNELS = 8;
const std::vector<std::string> Audio::AUDIO_FORMATS = { "MP3", "AAC", "M4a", "WAV", "FLAC", "ALAC", "PCM", "OPUS", "WMA" };


const std::string Audio::defaultAudioFormat = "MP3";
const float Audio::defaultAudioSize = 5.0;
const std::string Audio::defaultAudioArtist = "Artist Uknown";
const std::string Audio::defaultAudioGenre = "Genre Uknown";
const std::string Audio::defaultAudioAlbum = "Album Uknown";
const unsigned int Audio::defaultAudioReleaseYear = 1969;
const unsigned int Audio::defaultAudioLength = 3;
const unsigned int Audio::defaultAudioBitRate = 128;
const float Audio::defaultAudioSampleRate = 44.1;
const unsigned int Audio::defaultAudioBitDepth = 16;
const unsigned int Audio::defaultAudioChannels = 2;
const std::string Audio::defaultAudioCollaborators = "None";


Audio::Audio()
    : AbstractFile(AbstractFile::defaultPath, defaultAudioSize),
    AbstractMedia(AbstractFile::defaultPath, defaultAudioSize, AbstractMedia::defaultName, AbstractMedia::defaultUploader, defaultAudioFormat, AbstractMedia::defaultRating),
    artist(defaultAudioArtist),
    genre(defaultAudioGenre),
    album(defaultAudioAlbum),
    releaseYear(defaultAudioReleaseYear),
    lengthInMinutes(defaultAudioLength),
    bitRate(defaultAudioBitRate),
    sampleRate(defaultAudioSampleRate),
    bitDepth(defaultAudioBitDepth),
    numberOfChannels(defaultAudioChannels),
    collaborators(defaultAudioCollaborators)
{}

Audio::Audio(const Audio& audio)
    : AbstractFile(audio),
    AbstractMedia(audio),
    artist(audio.artist),
    genre(audio.genre),
    album(audio.album),
    releaseYear(audio.releaseYear),
    lengthInMinutes(audio.lengthInMinutes),
    bitRate(audio.bitRate),
    sampleRate(audio.sampleRate),
    bitDepth(audio.bitDepth),
    numberOfChannels(audio.numberOfChannels),
    collaborators(audio.collaborators)
{}


Audio& Audio::operator=(const Audio& audio) {
    if (this != &audio) {
        AbstractMedia::operator=(audio);
        this->artist = audio.artist;
        this->genre = audio.genre;
        this->releaseYear = audio.releaseYear;
        this->lengthInMinutes = audio.lengthInMinutes;
        this->bitRate = audio.bitRate;
        this->sampleRate = audio.sampleRate;
        this->bitDepth = audio.bitDepth;
        this->numberOfChannels = audio.numberOfChannels;
        this->collaborators = audio.collaborators;
    }
    return *this;
}


const std::string& Audio::getArtist() const { return artist; }
const std::string& Audio::getGenre() const { return genre; }
const std::string& Audio::getAlbum() const { return album; }
unsigned int Audio::getReleaseYear() const { return releaseYear; }
unsigned int Audio::getBitRate() const { return bitRate; }
float Audio::getSampleRate() const { return sampleRate; }
unsigned int Audio::getBitDepth() const { return bitDepth; }
unsigned int Audio::getAudioChannels() const { return numberOfChannels; }
const std::string& Audio::getCollaborators() const { return collaborators; }
unsigned int Audio::getMediaLength() const { return lengthInMinutes; }

void Audio::setArtist(const std::string art) { artist = art; }
void Audio::setGenre(const std::string& gnr) { genre = gnr; }
void Audio::setAlbum(const std::string& alb) { album = alb; }
void Audio::setReleaseYear(unsigned int year) { releaseYear = year; }
void Audio::setBitRate(unsigned int br) { bitRate = br; }
void Audio::setSampleRate(float sr) { sampleRate = sr; }
void Audio::setBitDepth(unsigned int bd) { bitDepth = bd; }
void Audio::setAudioChannels(unsigned int ch) { numberOfChannels = ch; }
void Audio::setCollaborators(const std::string& clb) { collaborators = clb; }
void Audio::setMediaLength(unsigned int length) { lengthInMinutes = length; }

bool Audio::measuredInPages() const { return false; }

bool Audio::hasLength() const { return true; }

bool Audio::hasResolution() const { return false; }

std::string Audio::displayStringType() const { return "Audio"; }


Audio* Audio::clone() const {
    return new Audio(*this);
}

void Audio::accept(Visitors::IVisitor& visitor) {
    visitor.visit(*this);
}

void Audio::accept(Visitors::IConstVisitor& visitor) const {
    visitor.visit(*this);
}


QJsonObject Audio::toJson() const {

    // creo un oggeto QJsonObject vuoto, visto come una mappa di coppie ("chiave", "valore")
    // (visto internamente come QMap<QString, QJsonValue>)
    QJsonObject json;

    // inserisco il tipo del media
    json["mediaType"] = "AUDIO";

    // per ciascun attributo del media salvo nel campo "chiave" dell'oggetto QJsonObject il nome dell'attributo
    // mentre salvo nel campo "valore" il valore dell'attributo, convertito in un tipo che puo' essere gestito da QJsonValue
    // I tipi 'float' e 'double' possono essere assegnati direttamente, in quando QJsonValue puo' gestirli direttamente

    json["name"] = QString::fromStdString(getMediaName());
    json["uploader"] = QString::fromStdString(getMediaUploader());
    json["format"] = QString::fromStdString(getMediaFormat());
    json["rating"] = static_cast<int>(getMediaRating());

    json["path"] = QString::fromStdString(getFilePath());
    json["size"] = getFileSize();

    json["artist"] = QString::fromStdString(artist);
    json["genre"] = QString::fromStdString(genre);
    json["album"] = QString::fromStdString(album);
    json["releaseYear"] = static_cast<int>(releaseYear);
    json["length"] = static_cast<int>(lengthInMinutes);
    json["bitrate"] = static_cast<int>(bitRate);
    json["samplerate"] = sampleRate;
    json["bitdepth"] = static_cast<int>(bitDepth);
    json["channels"] = static_cast<int>(numberOfChannels);
    json["collaborators"] = QString::fromStdString(collaborators);

    return json; // oggetto QJsonObject con attributi del media
}


void Audio::fromJson(const QJsonObject& obj) {

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

    // campi di Audio
    if (obj.contains("artist") && obj["artist"].isString()) {
        artist = obj["artist"].toString().toStdString();
    }
    if (obj.contains("genre") && obj["genre"].isString()) {
        genre = obj["genre"].toString().toStdString();
    }
    if (obj.contains("album") && obj["album"].isString()) {
        album = obj["album"].toString().toStdString();
    }
    if (obj.contains("releaseYear") && obj["releaseYear"].isDouble()) {
        releaseYear = static_cast<unsigned int>(obj["releaseYear"].toInt());
    }
    if (obj.contains("length") && obj["length"].isDouble()) {
        lengthInMinutes = static_cast<unsigned int>(obj["length"].toInt());
    }
    if (obj.contains("bitrate") && obj["bitrate"].isDouble()) {
        bitRate = static_cast<unsigned int>(obj["bitrate"].toInt());
    }
    if (obj.contains("samplerate") && obj["samplerate"].isDouble()) {
        sampleRate = static_cast<float>(obj["samplerate"].toDouble());
    }
    if (obj.contains("bitdepth") && obj["bitdepth"].isDouble()) {
        bitDepth = static_cast<unsigned int>(obj["bitdepth"].toInt());
    }
    if (obj.contains("channels") && obj["channels"].isDouble()) {
        numberOfChannels = static_cast<unsigned int>(obj["channels"].toInt());
    }
    if (obj.contains("collaborators") && obj["collaborators"].isString()) {
        collaborators = obj["collaborators"].toString().toStdString();
    }
}

}
}

#include "EBook.h"
#include "Model/Visitors/IVisitor.h"
#include "Model/Visitors/IConstVisitor.h"

#include <string>
#include <vector>
#include <cctype>

namespace Model {
namespace Media {

const unsigned int EBook::MIN_EBOOK_LENGTH = 1;
const unsigned int EBook::MAX_EBOOK_LENGTH = 10000;
const unsigned int EBook::VALID_ISBN_LENGTH = 13;
const std::vector<std::string> EBook::EBOOK_FORMATS = { "EPUB", "PDF", "HTML", "DOC", "DOCX", "Kindle", "Plucker", "Apple Books" };

const float EBook::defaultEBookSize = 2.0;
const std::string EBook::defaultEBookFormat = "EPUB";
const std::string EBook::defaultEBookAuthor = "Author Uknown";
const std::string EBook::defaultEBookPublisher = "Publisher Uknown";
const unsigned int EBook::defaultEBookReleaseYear = 1998;
const std::string EBook::defaultEBookISBN = "9788887331943";
const unsigned int EBook::defaultEBookLength = 100;
const std::string EBook::defaultEBookCategory = "Category Uknown";
const std::string EBook::defaultEBookLanguage = "Language Uknown";


EBook::EBook()
    : AbstractFile(AbstractFile::defaultPath, defaultEBookSize),
    AbstractMedia(AbstractFile::defaultPath, defaultEBookSize, AbstractMedia::defaultName, AbstractMedia::defaultUploader, defaultEBookFormat, AbstractMedia::defaultRating),
    author(defaultEBookAuthor),
    publisher(defaultEBookPublisher),
    releaseYear(defaultEBookReleaseYear),
    ISBN(defaultEBookISBN),
    lengthInPages(defaultEBookLength),
    category(defaultEBookCategory),
    language(defaultEBookLanguage),
    coverImage(AbstractFile::defaultPath),
    images(false)
{}


EBook::EBook(const EBook& ebook)
    : AbstractFile(ebook),
    AbstractMedia(ebook),
    author(ebook.author),
    publisher(ebook.publisher),
    releaseYear(ebook.releaseYear),
    ISBN(ebook.ISBN),
    lengthInPages(ebook.lengthInPages),
    category(ebook.category),
    language(ebook.language),
    coverImage(ebook.coverImage),
    images(ebook.images)
{}

EBook& EBook::operator=(const EBook& ebook) {
    if (this != &ebook) {
        AbstractMedia::operator=(ebook);
        this->author = ebook.author;
        this->publisher = ebook.publisher;
        this->releaseYear = ebook.releaseYear;
        this->ISBN = ebook.ISBN;
        this->lengthInPages = ebook.lengthInPages;
        this->category = ebook.category;
        this->language = ebook.language;
        this->coverImage = ebook.coverImage;
        this->images = ebook.images;
    }
    return *this;
}


const std::string& EBook::getAuthor() const { return author; }
const std::string& EBook::getPublisher() const { return publisher; }
unsigned int EBook::getReleaseYear() const { return releaseYear; }
const std::string& EBook::getISBN() const { return ISBN; }
const std::string& EBook::getCategory() const { return category; }
const std::string& EBook::getLanguage() const { return language; }
const std::string& EBook::getCoverImagePath() const { return coverImage; }
bool EBook::hasImages() const { return images; }
unsigned int EBook::getMediaLength() const { return lengthInPages; }


void EBook::setAuthor(const std::string& auth) { author = auth; }
void EBook::setPublisher(const std::string& pbl) { publisher = pbl; }
void EBook::setReleaseYear(unsigned int year) { releaseYear = year; }
void EBook::setISBN(const std::string& isbn) { ISBN = isbn; }
void EBook::setCategory(const std::string& ctg) { category = ctg; }
void EBook::setLanguage(const std::string& lang) { language = lang; }
void EBook::setCoverImagePath(const std::string& cp) { coverImage = cp; }
void EBook::setImages(bool img) { images = img; }
void EBook::setMediaLength(unsigned int length) { lengthInPages = length; }


/* Metodo per verificare la validita' dell'isbn di un media EBook.
 * Un media EBook di Virtual Library ha un ISBN valido secondo l'algoritmo checksum ISBN-13.
 *
 * L'algoritmo checksum ISBN-13 ha il seguente comportamento:
 *  - Si assume che l'ISBN sia composto da esattamente 13 caratteri numerici (senza spazi)
    - Le prime 12 cifre corrispondono ad una somma pesata (pari= x1, dispari= x3)
    - La cifra di controllo ("check digit") corrisponde a (10 - (somma % 10)) % 10
    - L'ultima cifra deve corrispondere alla cifra di controllo
*/
bool EBook::validISBN() const {

    if (ISBN.empty() || ISBN.length() != VALID_ISBN_LENGTH) {
        return false;
    }
    int tempSum = 0;
    for (int i = 0; i < 12; ++i) {
        if (!std::isdigit(ISBN[i])) {
            return false;
        }
        int digit = ISBN[i] - '0';
        tempSum += (i % 2 == 0) ? digit : 3 * digit;
    }
    int checkSum = (10 - (tempSum% 10)) % 10;
    return (std::isdigit(ISBN[12]) && (ISBN[12] - '0') == checkSum);
}


bool EBook::hasCoverPath() const {

    return (!coverImage.empty());
}


bool EBook::measuredInPages() const { return true; }

bool EBook::hasLength() const { return true; }

bool EBook::hasResolution() const { return false; }


std::string EBook::displayStringType() const { return "EBook"; }


EBook* EBook::clone() const {
    return new EBook(*this);
}

void EBook::accept(Visitors::IVisitor& visitor) {
    visitor.visit(*this);
}

void EBook::accept(Visitors::IConstVisitor& visitor) const {
    visitor.visit(*this);
}


QJsonObject EBook::toJson() const {

    // creo un oggeto QJsonObject vuoto, visto come una mappa di coppie ("chiave", "valore")
    // (visto internamente come QMap<QString, QJsonValue>)
    QJsonObject json;

    // inserisco il tipo del media
    json["mediaType"] = "EBOOK";

    // per ciascun attributo del media salvo nel campo "chiave" dell'oggetto QJsonObject il nome dell'attributo
    // mentre salvo nel campo "valore" il valore dell'attributo, convertito in un tipo che puo' essere gestito da QJsonValue
    // I tipi 'float' e 'double' possono essere assegnati direttamente, in quando QJsonValue puo' gestirli direttamente

    json["name"] = QString::fromStdString(getMediaName());
    json["uploader"] = QString::fromStdString(getMediaUploader());
    json["format"] = QString::fromStdString(getMediaFormat());
    json["rating"] = static_cast<int>(getMediaRating());

    json["path"] = QString::fromStdString(getFilePath());
    json["size"] = getFileSize();

    json["author"] = QString::fromStdString(author);
    json["publisher"] = QString::fromStdString(publisher);
    json["releaseYear"] = static_cast<int>(releaseYear);
    json["isbn"] = QString::fromStdString(ISBN);
    json["length"] = static_cast<int>(lengthInPages);
    json["category"] = QString::fromStdString(category);
    json["language"] = QString::fromStdString(language);
    json["coverPath"] = QString::fromStdString(coverImage);
    json["hasImages"] = images;

    return json; // oggetto QJsonObject con attributi del media

}

void EBook::fromJson(const QJsonObject& obj) {

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

    // campi EBook
    if (obj.contains("author") && obj["author"].isString()) {
        author = obj["author"].toString().toStdString();
    }
    if (obj.contains("publisher") && obj["publisher"].isString()) {
        publisher = obj["publisher"].toString().toStdString();
    }
    if (obj.contains("releaseYear") && obj["releaseYear"].isDouble()) {
        releaseYear = static_cast<unsigned int>(obj["releaseYear"].toInt());
    }
    if (obj.contains("isbn") && obj["isbn"].isString()) {
        ISBN = obj["isbn"].toString().toStdString();
    }
    if (obj.contains("length") && obj["length"].isDouble()) {
        lengthInPages = static_cast<unsigned int>(obj["length"].toInt());
    }
    if (obj.contains("category") && obj["category"].isString()) {
        category = obj["category"].toString().toStdString();
    }
    if (obj.contains("language") && obj["language"].isString()) {
        language = obj["language"].toString().toStdString();
    }
    if (obj.contains("coverPath") && obj["coverPath"].isString()) {
        coverImage = obj["coverPath"].toString().toStdString();
    }
    if (obj.contains("hasImages") && obj["hasImages"].isBool()) {
        images = obj["hasImages"].toBool();
    }
}



}
}

#include "MediaEditor.h"
#include "Model/Builders/AudioBuilder.h"
#include "Model/Builders/EBookBuilder.h"
#include "Model/Builders/VideoBuilder.h"
#include "Model/Builders/ImageBuilder.h"

namespace Model {
namespace Visitors {


MediaEditor::MediaEditor(const std::unordered_map<std::string, std::string>& edits)
    : mediaEdits(edits) {}


void MediaEditor::visit(Media::Audio& audio) {

    using namespace Model::Builders;
    AudioBuilder builder(audio);

    if (mediaEdits.find("path") != mediaEdits.end()) {
        builder.setPath(mediaEdits["path"]);
    }
    if (mediaEdits.find("size") != mediaEdits.end()) {
        builder.setSize(std::stof(mediaEdits["size"]));
    }
    if (mediaEdits.find("name") != mediaEdits.end()) {
        builder.setName(mediaEdits["name"]);
    }
    if (mediaEdits.find("uploader") != mediaEdits.end()) {
        builder.setUploader(mediaEdits["uploader"]);
    }
    if (mediaEdits.find("format") != mediaEdits.end()) {
        builder.setFormat(mediaEdits["format"]);
    }
    if (mediaEdits.find("rating") != mediaEdits.end()) {
        builder.setRating(std::stoi(mediaEdits["rating"]));
    }

    // Relativi al tipo Audio

    if (mediaEdits.find("artist") != mediaEdits.end()) {
        builder.setArtist(mediaEdits["artist"]);
    }
    if (mediaEdits.find("genre") != mediaEdits.end()) {
        builder.setGenre(mediaEdits["genre"]);
    }
    if (mediaEdits.find("album") != mediaEdits.end()) {
        builder.setAlbum(mediaEdits["album"]);
    }
    if (mediaEdits.find("releaseYear") != mediaEdits.end()) {
        builder.setReleaseYear(std::stoi(mediaEdits["releaseYear"]));
    }
    if (mediaEdits.find("length") != mediaEdits.end()) {
        builder.setLengthInMinutes(std::stoi(mediaEdits["length"]));
    }
    if (mediaEdits.find("bitrate") != mediaEdits.end()) {
        builder.setBitRate(std::stoi(mediaEdits["bitrate"]));
    }
    if (mediaEdits.find("samplerate") != mediaEdits.end()) {
        builder.setSampleRate(std::stof(mediaEdits["samplerate"]));
    }
    if (mediaEdits.find("bitdepth") != mediaEdits.end()) {
        builder.setBitDepth(std::stoi(mediaEdits["bitdepth"]));
    }
    if (mediaEdits.find("channels") != mediaEdits.end()) {
        builder.setChannels(std::stoi(mediaEdits["channels"]));
    }
    if (mediaEdits.find("collaborators") != mediaEdits.end()) {
        builder.setCollaborators(mediaEdits["collaborators"]);
    }

    auto editedAudio = builder.buildMedia();
    auto audioPtr = dynamic_cast<Model::Media::Audio*>(editedAudio.get());
    if (!audioPtr) {
        throw std::runtime_error("Audio Editor Error!\n");
    }
    audio = *audioPtr;
}

void MediaEditor::visit(Media::Video& video) {

    using namespace Model::Builders;
    VideoBuilder builder(video);

    if (mediaEdits.find("path") != mediaEdits.end()) {
        builder.setPath(mediaEdits["path"]);
    }
    if (mediaEdits.find("size") != mediaEdits.end()) {
        builder.setSize(std::stof(mediaEdits["size"]));
    }
    if (mediaEdits.find("name") != mediaEdits.end()) {
        builder.setName(mediaEdits["name"]);
    }
    if (mediaEdits.find("uploader") != mediaEdits.end()) {
        builder.setUploader(mediaEdits["uploader"]);
    }
    if (mediaEdits.find("format") != mediaEdits.end()) {
        builder.setFormat(mediaEdits["format"]);
    }
    if (mediaEdits.find("rating") != mediaEdits.end()) {
        builder.setRating(std::stoi(mediaEdits["rating"]));
    }

    // Relativi al tipo Video

    if (mediaEdits.find("director") != mediaEdits.end()) {
        builder.setDirector(mediaEdits["director"]);
    }
    if (mediaEdits.find("genre") != mediaEdits.end()) {
        builder.setGenre(mediaEdits["genre"]);
    }
    if (mediaEdits.find("releaseYear") != mediaEdits.end()) {
        builder.setReleaseYear(std::stoi(mediaEdits["releaseYear"]));
    }
    if (mediaEdits.find("length") != mediaEdits.end()) {
        builder.setLength(std::stoi(mediaEdits["length"]));
    }
    if (mediaEdits.find("framerate") != mediaEdits.end()) {
        builder.setFrameRate(std::stoi(mediaEdits["framerate"]));
    }
    if (mediaEdits.find("width") != mediaEdits.end()) {
        builder.setResolutionWidth(std::stoi(mediaEdits["width"]));
    }
    if (mediaEdits.find("height") != mediaEdits.end()) {
        builder.setResolutionHeight(std::stoi(mediaEdits["height"]));
    }
    if (mediaEdits.find("colordepth") != mediaEdits.end()) {
        builder.setColorDepth(std::stoi(mediaEdits["colordepth"]));
    }
    if (mediaEdits.find("subtitles") != mediaEdits.end()) {
        builder.setSubtitles(mediaEdits["subtitles"]);
    }
    if (mediaEdits.find("language") != mediaEdits.end()) {
        builder.setLanguage(mediaEdits["language"]);
    }

    auto editedVideo = builder.buildMedia();
    auto videoPtr = dynamic_cast<Model::Media::Video*>(editedVideo.get());
    if (!videoPtr) {
        throw std::runtime_error("Video Editor Error!\n");
    }
    video = *videoPtr;
}

void MediaEditor::visit(Media::EBook& ebook) {

    using namespace Model::Builders;
    EBookBuilder builder(ebook);

    if (mediaEdits.find("path") != mediaEdits.end()) {
        builder.setPath(mediaEdits["path"]);
    }
    if (mediaEdits.find("size") != mediaEdits.end()) {
        builder.setSize(std::stof(mediaEdits["size"]));
    }
    if (mediaEdits.find("name") != mediaEdits.end()) {
        builder.setName(mediaEdits["name"]);
    }
    if (mediaEdits.find("uploader") != mediaEdits.end()) {
        builder.setUploader(mediaEdits["uploader"]);
    }
    if (mediaEdits.find("format") != mediaEdits.end()) {
        builder.setFormat(mediaEdits["format"]);
    }
    if (mediaEdits.find("rating") != mediaEdits.end()) {
        builder.setRating(std::stoi(mediaEdits["rating"]));
    }

    // Relativi al tipo EBook

    if (mediaEdits.find("author") != mediaEdits.end()) {
        builder.setAuthor(mediaEdits["author"]);
    }
    if (mediaEdits.find("publisher") != mediaEdits.end()) {
        builder.setPublisher(mediaEdits["publisher"]);
    }
    if (mediaEdits.find("releaseYear") != mediaEdits.end()) {
        builder.setReleaseYear(std::stoi(mediaEdits["releaseYear"]));
    }
    if (mediaEdits.find("isbn") != mediaEdits.end()) {
        builder.setISBN(mediaEdits["isbn"]);
    }
    if (mediaEdits.find("length") != mediaEdits.end()) {
        builder.setLengthInPages(std::stoi(mediaEdits["length"]));
    }
    if (mediaEdits.find("category") != mediaEdits.end()) {
        builder.setCategory(mediaEdits["category"]);
    }
    if (mediaEdits.find("language") != mediaEdits.end()) {
        builder.setLanguage(mediaEdits["language"]);
    }
    if (mediaEdits.find("coverPath") != mediaEdits.end()) {
        builder.setCoverImagePath(mediaEdits["coverPath"]);
    }
    if (mediaEdits.find("hasImages") != mediaEdits.end()) {
        bool img = (mediaEdits["hasImages"] == "true");
        builder.setHasImages(img);
    }

    auto editedEBook = builder.buildMedia();
    auto ebookPtr = dynamic_cast<Model::Media::EBook*>(editedEBook.get());
    if (!ebookPtr) {
        throw std::runtime_error("EBook Editor Error!\n");
    }
    ebook = *ebookPtr;

}

void MediaEditor::visit(Media::Image& image) {

    using namespace Model::Builders;
    ImageBuilder builder(image);

    if (mediaEdits.find("path") != mediaEdits.end()) {
        builder.setPath(mediaEdits["path"]);
    }
    if (mediaEdits.find("size") != mediaEdits.end()) {
        builder.setSize(std::stof(mediaEdits["size"]));
    }
    if (mediaEdits.find("name") != mediaEdits.end()) {
        builder.setName(mediaEdits["name"]);
    }
    if (mediaEdits.find("uploader") != mediaEdits.end()) {
        builder.setUploader(mediaEdits["uploader"]);
    }
    if (mediaEdits.find("format") != mediaEdits.end()) {
        builder.setFormat(mediaEdits["format"]);
    }
    if (mediaEdits.find("rating") != mediaEdits.end()) {
        builder.setRating(std::stoi(mediaEdits["rating"]));
    }

    // Relativi al tipo Image

    if (mediaEdits.find("dateCreated") != mediaEdits.end()) {
        builder.setDateCreated(mediaEdits["dateCreated"]);
    }
    if (mediaEdits.find("imageCreator") != mediaEdits.end()) {
        builder.setCreator(mediaEdits["imageCreator"]);
    }
    if (mediaEdits.find("imageCategory") != mediaEdits.end()) {
        builder.setCategory(mediaEdits["imageCategory"]);
    }
    if (mediaEdits.find("resolutionWidth") != mediaEdits.end()) {
        builder.setResolutionWidth(std::stoi(mediaEdits["resolutionWidth"]));
    }
    if (mediaEdits.find("resolutionHeight") != mediaEdits.end()) {
        builder.setResolutionHeight(std::stoi(mediaEdits["resolutionHeight"]));
    }
    if (mediaEdits.find("aspectWidth") != mediaEdits.end()) {
        builder.setAspectRatioWidth(std::stoi(mediaEdits["aspectWidth"]));
    }
    if (mediaEdits.find("aspectHeight") != mediaEdits.end()) {
        builder.setAspectRatioHeight(std::stoi(mediaEdits["aspectHeight"]));
    }
    if (mediaEdits.find("bitdepth") != mediaEdits.end()) {
        builder.setImageBitdepth(std::stoi(mediaEdits["bitdepth"]));
    }
    if (mediaEdits.find("compressed") != mediaEdits.end()) {
        bool cmpr = mediaEdits["compressed"] == "true";
        builder.setCompression(cmpr);
    }
    if (mediaEdits.find("location") != mediaEdits.end()) {
        builder.setLocationTaken(mediaEdits["location"]);
    }

    auto editedImage = builder.buildMedia();
    auto imagePtr = dynamic_cast<Model::Media::Image*>(editedImage.get()); {
        if (!imagePtr) {
            throw std::runtime_error("Image Editor Error!\n");
        }
    }
    image = *imagePtr;
}


}
}



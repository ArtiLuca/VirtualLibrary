#include "Model/Library/MediaFactory.h"
#include "Model/Media/AbstractMedia.h"
#include "Model/Builders/AudioBuilder.h"
#include "Model/Builders/VideoBuilder.h"
#include "Model/Builders/EBookBuilder.h"
#include "Model/Builders/ImageBuilder.h"
#include "Model/Visitors/MediaValidator.h"

#include <string>
#include <unordered_map>


namespace Model {
namespace Library {

std::shared_ptr<Media::AbstractMedia> MediaFactory::createMedia(
    const std::string& mediaType,
    const std::unordered_map<std::string, std::string>& mediaAttributes)
{
    try {

        if (mediaType == "AUDIO")
            return createAudio(mediaAttributes);
        else if (mediaType == "EBOOK")
            return createEBook(mediaAttributes);
        else if (mediaType == "VIDEO")
            return createVideo(mediaAttributes);
        else if (mediaType == "IMAGE")
            return createImage(mediaAttributes);
        else
            throw std::runtime_error("Unknown Media Type: " + mediaType + "\n");
    }
    catch (const Model::Visitors::MediaValidatorException& e) {
        throw Model::Visitors::MediaValidatorException("Failed to create media of type: " + mediaType + ": " + std::string(e.what()));
    }
}


std::shared_ptr<Media::AbstractMedia> MediaFactory::createAudio
    (const std::unordered_map<std::string, std::string>& audioAttributes)
{
    Model::Builders::AudioBuilder audioBuilder;

    // attributi comuni
    auto it = audioAttributes.find("path");
    if (it != audioAttributes.end())
        audioBuilder.setPath(it->second);
    it = audioAttributes.find("size");
    if (it != audioAttributes.end())
        audioBuilder.setSize(std::stof(it->second));
    it = audioAttributes.find("name");
    if (it != audioAttributes.end())
        audioBuilder.setName(it->second);
    it = audioAttributes.find("uploader");
    if (it != audioAttributes.end())
        audioBuilder.setUploader(it->second);
    it = audioAttributes.find("format");
    if (it != audioAttributes.end())
        audioBuilder.setFormat(it->second);
    it = audioAttributes.find("rating");
    if (it != audioAttributes.end())
        audioBuilder.setRating(std::stoi(it->second));

    // attributi informativi Audio
    it = audioAttributes.find("artist");
    if (it != audioAttributes.end())
        audioBuilder.setArtist(it->second);
    it = audioAttributes.find("genre");
    if (it != audioAttributes.end())
        audioBuilder.setGenre(it->second);
    it = audioAttributes.find("album");
    if (it != audioAttributes.end())
        audioBuilder.setAlbum(it->second);
    it = audioAttributes.find("releaseYear");
    if (it != audioAttributes.end())
        audioBuilder.setReleaseYear(std::stoi(it->second));
    it = audioAttributes.find("length");
    if (it != audioAttributes.end())
        audioBuilder.setLengthInMinutes(std::stoi(it->second));

    // attributi tecnici Audio
    it = audioAttributes.find("bitrate");
    if (it != audioAttributes.end())
        audioBuilder.setBitRate(std::stoi(it->second));
    it = audioAttributes.find("samplerate");
    if (it != audioAttributes.end())
        audioBuilder.setSampleRate(std::stof(it->second));
    it = audioAttributes.find("bitdepth");
    if (it != audioAttributes.end())
        audioBuilder.setBitDepth(std::stoi(it->second));
    it = audioAttributes.find("channels");
    if (it != audioAttributes.end())
        audioBuilder.setChannels(std::stoi(it->second));
    it = audioAttributes.find("collaborators");
    if (it != audioAttributes.end())
        audioBuilder.setCollaborators(it->second);

    auto audio = audioBuilder.buildMedia();
    return audio;
}


std::shared_ptr<Media::AbstractMedia> MediaFactory::createVideo
    (const std::unordered_map<std::string, std::string>& videoAttributes)
{
    Model::Builders::VideoBuilder videoBuilder;

    // attributi comuni
    auto it = videoAttributes.find("path");
    if (it != videoAttributes.end())
        videoBuilder.setPath(it->second);
    it = videoAttributes.find("size");
    if (it != videoAttributes.end())
        videoBuilder.setSize(std::stof(it->second));
    it = videoAttributes.find("name");
    if (it != videoAttributes.end())
        videoBuilder.setName(it->second);
    it = videoAttributes.find("uploader");
    if (it != videoAttributes.end())
        videoBuilder.setUploader(it->second);
    it = videoAttributes.find("format");
    if (it != videoAttributes.end())
        videoBuilder.setFormat(it->second);
    it = videoAttributes.find("rating");
    if (it != videoAttributes.end())
        videoBuilder.setRating(std::stoi(it->second));

    // attributi informativi Video
    it = videoAttributes.find("director");
    if (it != videoAttributes.end())
        videoBuilder.setDirector(it->second);
    it = videoAttributes.find("genre");
    if (it != videoAttributes.end())
        videoBuilder.setGenre(it->second);
    it = videoAttributes.find("releaseYear");
    if (it != videoAttributes.end())
        videoBuilder.setReleaseYear(std::stoi(it->second));
    it = videoAttributes.find("length");
    if (it != videoAttributes.end())
        videoBuilder.setLength(std::stoi(it->second));

    // attributi tecnici Video
    it = videoAttributes.find("framerate");
    if (it != videoAttributes.end())
        videoBuilder.setFrameRate(std::stoi(it->second));
    it = videoAttributes.find("width");
    if (it != videoAttributes.end())
        videoBuilder.setResolutionWidth(std::stoi(it->second));
    it = videoAttributes.find("height");
    if (it != videoAttributes.end())
        videoBuilder.setResolutionHeight(std::stoi(it->second));
    it = videoAttributes.find("colordepth");
    if (it != videoAttributes.end())
        videoBuilder.setColorDepth(std::stoi(it->second));
    it = videoAttributes.find("subtitles");
    if (it != videoAttributes.end())
        videoBuilder.setSubtitles(it->second);
    it = videoAttributes.find("language");
    if (it != videoAttributes.end())
        videoBuilder.setLanguage(it->second);

    auto video = videoBuilder.buildMedia();
    return video;

}


std::shared_ptr<Media::AbstractMedia> MediaFactory::createImage(
    const std::unordered_map<std::string, std::string>& imageAttributes)
{
    Model::Builders::ImageBuilder imageBuilder;

    // attributi comuni
    auto it = imageAttributes.find("path");
    if (it != imageAttributes.end())
        imageBuilder.setPath(it->second);
    it = imageAttributes.find("size");
    if (it != imageAttributes.end())
        imageBuilder.setSize(std::stof(it->second));
    it = imageAttributes.find("name");
    if (it != imageAttributes.end())
        imageBuilder.setName(it->second);
    it = imageAttributes.find("uploader");
    if (it != imageAttributes.end())
        imageBuilder.setUploader(it->second);
    it = imageAttributes.find("format");
    if (it != imageAttributes.end())
        imageBuilder.setFormat(it->second);
    it = imageAttributes.find("rating");
    if (it != imageAttributes.end())
        imageBuilder.setRating(std::stoi(it->second));

    // attributi informativi Image
    it = imageAttributes.find("dateCreated");
    if (it != imageAttributes.end())
        imageBuilder.setDateCreated(it->second);
    it = imageAttributes.find("imageCreator");
    if (it != imageAttributes.end())
        imageBuilder.setCreator(it->second);
    it = imageAttributes.find("imageCategory");
    if (it != imageAttributes.end())
        imageBuilder.setCategory(it->second);

    // attributi tecnici Image
    it = imageAttributes.find("resolutionWidth");
    if (it != imageAttributes.end())
        imageBuilder.setResolutionWidth(std::stoi(it->second));
    it = imageAttributes.find("resolutionHeight");
    if (it != imageAttributes.end())
        imageBuilder.setResolutionHeight(std::stoi(it->second));
    it = imageAttributes.find("aspectWidth");
    if (it != imageAttributes.end())
        imageBuilder.setAspectRatioWidth(std::stoi(it->second));
    it = imageAttributes.find("aspectHeight");
    if (it != imageAttributes.end())
        imageBuilder.setAspectRatioHeight(std::stoi(it->second));
    it = imageAttributes.find("bitdepth");
    if (it != imageAttributes.end())
        imageBuilder.setImageBitdepth(std::stoi(it->second));
    it = imageAttributes.find("compressed");
    if (it != imageAttributes.end()) {
        if (imageAttributes.at("compressed") == "true") imageBuilder.setCompression(true);
        else imageBuilder.setCompression(false);
    }
    it = imageAttributes.find("location");
    if (it != imageAttributes.end())
        imageBuilder.setLocationTaken(it->second);

    auto image = imageBuilder.buildMedia();
    return image;


}


std::shared_ptr<Media::AbstractMedia> MediaFactory::createEBook
    (const std::unordered_map<std::string, std::string>& ebookAttributes)
{
    Model::Builders::EBookBuilder ebookBuilder;

    // attributi comuni
    auto it = ebookAttributes.find("path");
    if (it != ebookAttributes.end())
        ebookBuilder.setPath(it->second);
    it = ebookAttributes.find("size");
    if (it != ebookAttributes.end())
        ebookBuilder.setSize(std::stof(it->second));
    it = ebookAttributes.find("name");
    if (it != ebookAttributes.end())
        ebookBuilder.setName(it->second);
    it = ebookAttributes.find("uploader");
    if (it != ebookAttributes.end())
        ebookBuilder.setUploader(it->second);
    it = ebookAttributes.find("format");
    if (it != ebookAttributes.end())
        ebookBuilder.setFormat(it->second);
    it = ebookAttributes.find("rating");
    if (it != ebookAttributes.end())
        ebookBuilder.setRating(std::stoi(it->second));

    // attributi informativi EBook
    it = ebookAttributes.find("author");
    if (it != ebookAttributes.end())
        ebookBuilder.setAuthor(it->second);
    it = ebookAttributes.find("publisher");
    if (it != ebookAttributes.end())
        ebookBuilder.setPublisher(it->second);
    it = ebookAttributes.find("releaseYear");
    if (it != ebookAttributes.end())
        ebookBuilder.setReleaseYear(std::stoi(it->second));
    it = ebookAttributes.find("length");
    if (it != ebookAttributes.end())
        ebookBuilder.setLengthInPages(std::stoi(it->second));
    it = ebookAttributes.find("category");
    if (it != ebookAttributes.end())
        ebookBuilder.setCategory(it->second);
    it = ebookAttributes.find("language");
    if (it != ebookAttributes.end())
        ebookBuilder.setLanguage(it->second);
    it = ebookAttributes.find("coverPath");
    if (it != ebookAttributes.end())
        ebookBuilder.setCoverImagePath(it->second);

    // attributi tecnici EBook
    it = ebookAttributes.find("isbn");
    if (it != ebookAttributes.end())
        ebookBuilder.setISBN(it->second);
    it = ebookAttributes.find("hasImages");
    if (it != ebookAttributes.end()) {
        if (ebookAttributes.at("hasImages") == "true")
            ebookBuilder.setHasImages(true);
        else
            ebookBuilder.setHasImages(false);
    }

    auto ebook = ebookBuilder.buildMedia();
    return ebook;

}


}
}


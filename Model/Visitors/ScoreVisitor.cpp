#include "ScoreVisitor.h"
#include "Model/Media/Audio.h"
#include "Model/Media/Video.h"
#include "Model/Media/EBook.h"
#include "Model/Media/Image.h"

#include <string>

namespace Model {
namespace Visitors {

const std::string ScoreVisitor::LABEL_UKNOWN = "Uknown Quality";
const std::string ScoreVisitor::LABEL_LOW = "Low Quality";
const std::string ScoreVisitor::LABEL_AVERAGE = "Average Quality";
const std::string ScoreVisitor::LABEL_HIGH = "High Quality";
const std::string ScoreVisitor::LABEL_VERY_HIGH = "Very High Quality";

const float ScoreVisitor::SCORE_UNKNOWN = 0.0f;
const float ScoreVisitor::SCORE_LOW = 50.0f;
const float ScoreVisitor::SCORE_AVERAGE = 65.0f;
const float ScoreVisitor::SCORE_HIGH = 80.0f;
const float ScoreVisitor::SCORE_VERY_HIGH = 90.0f;


ScoreVisitor::ScoreVisitor()
    : scoreValue(SCORE_UNKNOWN),
    scoreLabel(LABEL_UKNOWN),
    scoreInfo("")
{}


float ScoreVisitor::getScoreValue() const { return scoreValue; }
const std::string& ScoreVisitor::getScoreLabel() const { return scoreLabel; }
const std::string& ScoreVisitor::getScoreInfo() const { return scoreInfo; }


void ScoreVisitor::resetScoreVisitor() {

    const_cast<ScoreVisitor*>(this)->scoreValue = SCORE_UNKNOWN;
    const_cast<ScoreVisitor*>(this)->scoreLabel = LABEL_UKNOWN;
    const_cast<ScoreVisitor*>(this)->scoreInfo = "";

}

std::string ScoreVisitor::assignScoreLabel(float score) const {

    if (score < SCORE_AVERAGE) return LABEL_LOW;
    if (score < SCORE_HIGH) return LABEL_AVERAGE;
    if (score < SCORE_VERY_HIGH) return LABEL_HIGH;
    return LABEL_VERY_HIGH;
}


float ScoreVisitor::normalizeValue(float val, float min, float max) const {

    if (val <= min) return 0.f;
    if (val >= max) return 1.f;
    return (val - min) / (max - min);

}



/* CALCOLO SCORE AUDIO
 *  - Audio: rating(40%), qualita' audio (50%), format (10%)
 *  - Qualita' audio data da media ponderata dei attributi bitrate, samplerate, bitdepth e channels.
 */

float ScoreVisitor::calculateAudioScore(const Media::Audio& audio, std::string& info) const {

    const_cast<ScoreVisitor*>(this)->resetScoreVisitor();

    info = "Audio Scoring Criteria = Rating (40%), Audio Quality (50%)\nNormalized Values:\n";

    float weightRating = 0.4f;
    float weightAudioQuality = 0.60f;

    float valueRating = normalizeValue(
        audio.getMediaRating(),
        Model::Media::AbstractMedia::MIN_MEDIA_RATING,
        Model::Media::AbstractMedia::MAX_MEDIA_RATING);
    info += "Rating = " + std::to_string(valueRating * 100).substr(0, 5) + " (40%)\n";

    float valueAudioQuality = normalizeAudioQuality(audio);
    info += "Audio Quality " + std::to_string(valueAudioQuality * 100).substr(0, 5) + " (50%)\n";

    float weightedAudioScore = (weightRating * valueRating) + (weightAudioQuality * valueAudioQuality);
    info += "Audio Score = " + std::to_string(weightedAudioScore * 100).substr(0, 5) + "/100";

    return weightedAudioScore * 100.0f;
}

float ScoreVisitor::normalizeAudioQuality(const Media::Audio& audio) const {

    float weightBitrate = 0.5f;
    float weightSamplerate = 0.30f;
    float weightBitdepth = 0.10f;
    float weightAudioChannels = 0.10f;

    float valueBitrate = normalizeValue(audio.getBitRate(), 96.0f, 256.0f);
    if (audio.getBitRate() < 96) valueBitrate = 0.0f;
    if (audio.getBitRate() >= 256) valueBitrate = 1.0f;

    float valueSamplerate = normalizeValue(audio.getSampleRate(), 22.0f, 44.1f);
    if (audio.getSampleRate() < 22.0f) valueSamplerate = 0.0f;
    if (audio.getSampleRate() >= 44.1f) valueSamplerate = 1.0f;

    float valueBitdepth = normalizeValue(audio.getBitDepth(), 8.0f, 16.0f);
    if (audio.getBitDepth() < 8) valueBitdepth = 0.0f;
    if (audio.getBitDepth() >= 16) valueBitdepth = 1.0f;

    float valueAudioChannels;
    if (audio.getAudioChannels() >= 2) valueAudioChannels = 1.0f;
    else valueAudioChannels = 0.0f;

    float valueAudioQuality = (weightBitrate * valueBitrate) +
                              (weightSamplerate * valueSamplerate) +
                              (weightBitdepth * valueBitdepth) +
                              (weightAudioChannels * valueAudioChannels);

    return valueAudioQuality;
}


/* CALCOLO SCORE VIDEO
 *  - Video: rating (35%), risoluzione video (45&), framerate (10%), supporto HDR (10%)
 *  - Risoluzione data da normalizzazione non lineare
 */

float ScoreVisitor::calculateVideoScore(const Media::Video& video, std::string& info) const {

    const_cast<ScoreVisitor*>(this)->resetScoreVisitor();

    info = "Video Scoring Criteria = Rating (35%), Resolution (45%), Framerate (5%), HDR Support(15%)\nNormalized Values:\n";

    float weightRating = 0.35f;
    float weightResolution = 0.45f;
    float weightFramerate = 0.05f;
    float weightHDRSupport = 0.15f;

    float valueRating = normalizeValue(
        video.getMediaRating(),
        Model::Media::AbstractMedia::MIN_MEDIA_RATING,
        Model::Media::AbstractMedia::MAX_MEDIA_RATING);
    info += "Rating = " + std::to_string(valueRating * 100).substr(0, 5) + " (35%)\n";

    float valueResolution = normalizeVideoResolution(video.getResolution().second);
    info += "Resolution = " + std::to_string(valueResolution * 100).substr(0, 5) + " (45%)\n";

    float valueFramerate = 0.0f;
    if (video.getFrameRate() < 24) valueFramerate = 0.0f;
    else if (video.getFrameRate() < 30) valueFramerate = 0.8f;
    else valueFramerate = 1.0f;
    info += "Framerate = " + std::to_string(valueFramerate * 100).substr(0, 5) + " (5%)\n";

    float valueHDRSupport = video.supportsHDR() ? 1.0f : 0.5f;
    info += "HDR Support = " + std::to_string(valueHDRSupport * 100).substr(0, 5) + " (15%)\n";

    float weightedVideoScore = (weightRating * valueRating) +
                          (weightResolution * valueResolution) +
                          (weightFramerate * valueFramerate) +
                          (weightHDRSupport * valueHDRSupport);

    info += "Video Score = " + std::to_string(weightedVideoScore * 100).substr(0, 5) + "/100";

    return weightedVideoScore * 100.f;
}

float ScoreVisitor::normalizeVideoResolution(int videoRes) const {

    if (videoRes < 480) return 0.0f;
    else if (videoRes < 720) return 0.4f;
    else if (videoRes < 1080) return 0.7f;
    else if (videoRes < 1440) return 0.9f;
    else return 1.0f;
}


/* CALCOLO SCORE IMAGE
 *  - Image: rating (30%), megapixel immagine (40%), compressione (20%), bitdepth (10%)
 *  - Megapixel data da normalizzazione non lineare
 */


float ScoreVisitor::calculateImageScore(const Media::Image& image, std::string& info) const {

    const_cast<ScoreVisitor*>(this)->resetScoreVisitor();

    info = "Image Scoring Criteria = Rating (30%), Megapixels (40%), Compression (15%), Bitdepth (15%)\nNormalized Values:\n";

    float weightRating = 0.3f;
    float weightMegaPixels = 0.4f;
    float weightCompressed = 0.15f;
    float weightBitdepth = 0.15f;

    float valueRating = normalizeValue(image.getMediaRating(),
                                       Model::Media::AbstractMedia::MIN_MEDIA_RATING,
                                       Model::Media::AbstractMedia::MAX_MEDIA_RATING);
    info += "Rating = " + std::to_string(valueRating * 100).substr(0, 5) + " (30%)\n";

    float imageMegaPixels = image.getMegaPixels();
    float valueMegaPixels = normalizeImageQuality(imageMegaPixels);
    info += "Megapixels = " + std::to_string(valueMegaPixels * 100).substr(0, 5) + " (40%)\n";

    float valueCompressed = image.isCompressed() ? 0.5f : 1.0f;
    info += "Compression = " + std::to_string(valueCompressed * 100).substr(0, 5) + " (15%)\n";

    float valueBitdepth = normalizeValue(image.getImageBitDepth(), 8.0f, 16.0f);
    if (image.getImageBitDepth() <= 8) valueBitdepth = 0.6f;
    if (image.getImageBitDepth() >= 16) valueBitdepth = 1.0f;
    info += "Bitdepth = " + std::to_string(valueBitdepth * 100).substr(0, 5) + " (15%)\n";

    float weightedImageScore = (weightRating * valueRating) +
                               (weightMegaPixels * valueMegaPixels) +
                               (weightCompressed * valueCompressed) +
                               (weightBitdepth * valueBitdepth);

    info += "Image Score = " + std::to_string(weightedImageScore * 100).substr(0, 5) + "/100";

    return weightedImageScore * 100.f;
}

float ScoreVisitor::normalizeImageQuality(float imageMP) const {

    if (imageMP < 6.0f) return 0.6f;
    else if (imageMP < 12.0f) return 0.8f;
    else if (imageMP < 24.0f) return 1.0f;
    else return 1.0f;
}


void ScoreVisitor::visit(const Media::Audio& audio) const {

    scoreInfo.clear();
    scoreValue = calculateAudioScore(audio, scoreInfo);
    scoreLabel = assignScoreLabel(scoreValue);

}

void ScoreVisitor::visit(const Media::Video& video) const {

    scoreInfo.clear();
    scoreValue = calculateVideoScore(video, scoreInfo);
    scoreLabel = assignScoreLabel(scoreValue);
}

void ScoreVisitor::visit(const Media::EBook& ebook) const {

    const_cast<ScoreVisitor*>(this)->resetScoreVisitor();
    scoreInfo.clear();
    scoreValue = ebook.getMediaRating();
    scoreInfo = "EBook Scoring Criteria = Rating (100%)\n";
    scoreInfo += "EBook Score = " + std::to_string(ebook.getMediaRating()) + "/100";
    scoreLabel = assignScoreLabel(scoreValue);
}

void ScoreVisitor::visit(const Media::Image& image) const {

    scoreInfo.clear();
    scoreValue = calculateImageScore(image, scoreInfo);
    scoreLabel = assignScoreLabel(scoreValue);
}


}
}


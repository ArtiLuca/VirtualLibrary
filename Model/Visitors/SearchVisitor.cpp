#include "SearchVisitor.h"
#include "Model/Media/Audio.h"
#include "Model/Media/EBook.h"
#include "Model/Media/Video.h"
#include "Model/Library/SearchQuery.h"

#include <string>
#include <vector>


namespace Model {
namespace Visitors {

SearchVisitor::SearchVisitor(const Model::Library::SearchQuery& query)
    : searchQuery(query)
{}

std::vector<unsigned int> SearchVisitor::getMatches() const { return matches; }


void SearchVisitor::visit(const Media::Audio& audio) const {

    if (!checkCommonMatches(audio))
        return;
    if (!checkAudioMatches(audio))
        return;

    matches.push_back(audio.getUniqueID());
}

void SearchVisitor::visit(const Media::Video& video) const {

    if (!checkCommonMatches(video))
        return;
    if (!checkVideoMatches(video))
        return;

    else matches.push_back(video.getUniqueID());
}

void SearchVisitor::visit(const Media::EBook& ebook) const {

    if (!checkCommonMatches(ebook))
        return;
    if (!checkEBookMatches(ebook))
        return;

    matches.push_back(ebook.getUniqueID());
}

void SearchVisitor::visit(const Media::Image& image) const {

    if (!checkCommonMatches(image))
        return;
    if (!checkImageMatches(image))
        return;

    else matches.push_back(image.getUniqueID());
}


bool SearchVisitor::checkCommonMatches(const Media::AbstractMedia& media) const {

    if (searchQuery.getMediaID() != 0 && media.getUniqueID() != searchQuery.getMediaID()) {
        return false;
    }

    if (!searchQuery.getMediaName().empty()
        && !Library::SearchQuery::checkPartialMatch(
            media.getMediaName(), searchQuery.getMediaName())) {
        return false;
    }

    if (!searchQuery.getMediaUploader().empty()
        && !Library::SearchQuery::checkPartialMatch(
            media.getMediaUploader(), searchQuery.getMediaUploader())) {
        return false;
    }

    if (!searchQuery.getMediaFormat().empty()
        && !Library::SearchQuery::checkPartialMatch(
            media.getMediaFormat(), searchQuery.getMediaFormat())) {
        return false;
    }

    if (searchQuery.getMinimumMediaRating() != 0) {
        unsigned int rating = media.getMediaRating();
        if (rating < searchQuery.getMinimumMediaRating()) {
            return false;
        }
    }

    if (searchQuery.getMaximumMediaRating() != 0) {
        unsigned int rating = media.getMediaRating();
        if (rating > searchQuery.getMaximumMediaRating()) {
            return false;
        }
    }

    return true;
}


bool SearchVisitor::checkAudioMatches(const Media::Audio& audio) const {

    // per il tipo serve match esatto
    if (!searchQuery.getMediaType().empty()
        && !Library::SearchQuery::checkExactMatch(
            searchQuery.getMediaType(), "AUDIO")) {
        return false;
    }

    if (!searchQuery.getAudioArtist().empty()
        && !Library::SearchQuery::checkPartialMatch(
            audio.getArtist(), searchQuery.getAudioArtist())) {
        return false;
    }

    if (!searchQuery.getMediaGenre().empty()
        && !Library::SearchQuery::checkPartialMatch(
            audio.getGenre(), searchQuery.getMediaGenre())) {
        return false;
    }

    return true;
}

bool SearchVisitor::checkVideoMatches(const Media::Video& video) const {

    // per il tipo serve match esatto
    if (!searchQuery.getMediaType().empty()
        && !Library::SearchQuery::checkExactMatch(
            searchQuery.getMediaType(), "VIDEO")) {
        return false;
    }

    if (!searchQuery.getVideoDirector().empty()
        && !Library::SearchQuery::checkPartialMatch(
            video.getDirector(), searchQuery.getVideoDirector())) {
        return false;
    }

    if (!searchQuery.getMediaGenre().empty()
        && !Library::SearchQuery::checkPartialMatch(
            video.getGenre(), searchQuery.getMediaGenre())) {
        return false;
    }

    return true;
}

bool SearchVisitor::checkEBookMatches(const Media::EBook& ebook) const {

    // per il tipo serve match esatto
    if (!searchQuery.getMediaType().empty()
        && !Library::SearchQuery::checkExactMatch(
            searchQuery.getMediaType(), "EBOOK")) {
        return false;
    }

    if (!searchQuery.getEBookAuthor().empty()
        && !Library::SearchQuery::checkPartialMatch(
            ebook.getAuthor(), searchQuery.getEBookAuthor())) {
        return false;
    }

    if (!searchQuery.getEBookPublisher().empty()
        && !Library::SearchQuery::checkPartialMatch(
            ebook.getPublisher(), searchQuery.getEBookPublisher())) {
        return false;
    }

    return true;
}

bool SearchVisitor::checkImageMatches(const Media::Image& image) const {

    // per il tipo serve match esatto
    if (!searchQuery.getMediaType().empty()
        && !Library::SearchQuery::checkExactMatch(
            searchQuery.getMediaType(), "IMAGE")) {
        return false;
    }

    if (!searchQuery.getImageCreator().empty()
        && !Library::SearchQuery::checkPartialMatch(
            image.getImageCreator(), searchQuery.getImageCreator())) {
        return false;
    }

    if (!searchQuery.getImageLocation().empty()
        && !Library::SearchQuery::checkPartialMatch(
            image.getLocationTaken(), searchQuery.getImageLocation())) {
        return false;
    }

    return true;
}

}
}

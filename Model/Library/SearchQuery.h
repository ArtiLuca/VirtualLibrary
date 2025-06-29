#ifndef MODEL_LIBRARY_SEARCH_QUERY_H
#define MODEL_LIBRARY_SEARCH_QUERY_H

#include <string>
#include <vector>
#include <cctype> // per helper statici

/** @brief SearchQuery
 *
 *  SearchQuery e' rappresenta uno 'struct' utilizzato per facilitare l'operazione di ricerca dei media.
 *  Viene utilizzata dalla classe MediaLibrary, e poi estesa in MediaManager, con la possibilita' di applicare piu' filtri per la ricerca.
 *
 *  Una operazione di ricerca nella libreria avviene tramite SearchQuery, passato per riferimento costante, con uno o piu' filtri impostati.
 *  SearchQuery contiene come campi dati privati i vari filtri per la ricerca e un vettore 'searchResults' utilizzato per salvare gli identificatori dei
 *  media trovati durante la ricerca. Questo vettore viene "svuotato" con il metodo 'clearSearchResults' ad ogni nuova operazione di ricerca.
 * *
 *  Il filtro 'mediaType' corrisponde ad una stringa contenente il nome del tipo del media.
 *  Questo e' semplicemente fatto per comodita' in quanto corrisponde ad una scelta fatta dal user nella GUI (come ad esempio la scelta fatta in una QComboBox).
 *  La determinazione del tipo e' effettivamente poi fatta a runtime, e quindi 'mediaType' non rappresenta un polimorfismo banale del tipo "getType".
 *
 *  In particolare, il campo 'searchQuery' e' dichiarato 'mutable' in modo da poter aggiornarlo (specificamente il campo 'searchResults') anche quando SearchQuery viene
 *  passato per riferimento costante, o quando viene usato dal visitor concreto SearchVisitor (che deriva da IConstVisitor).
 *
 *  UPDATED (4/6/25) - Included header <cctype>
 *  Ho definito i due metodi statici 'checkExactMatchCaseInsensitive' e 'checkPartialMatchCaseInsensitive' per fare il check per un match esatto oppure parziale.
 *  Entrambi trattano il possibile match come "case-insensitive". Ad esempio, il match esatto e' solitamente fatto per 'mediaType', mentre il match parziale e' applicato ad esempio per 'mediaName'.
 *
 */

namespace Model {
namespace Library {

struct SearchQuery {

public:

    // === HELPER STATICI PER RICERCA ===

    /**
     * @brief checkExactMatchCaseInsensitive : metodo helper statico, verifica se due stringhe sono esattamente uguali, ignorando maiuscole/minuscole (case-insensitive)
     * @param searchField : stringa rappresentante il campo di un media in cui cercare il match esatto
     * @param queryValue : stringa rappresentante il valore o filtro con cui verificare il match
     * @return bool : true se le due stringhe hanno stessa lunghezza e stessi caratteri, false altrimenti
     */
    static bool checkExactMatch(const std::string& searchField, const std::string& queryValue) {

        if (searchField.size() != queryValue.size()) return false;

        for (unsigned int i = 0; i < searchField.size(); ++i) {

            if (std::tolower(searchField[i]) != std::tolower(queryValue[i])) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief checkPartialMatchCaseInsensitive : metodo helper statico, verifica se una stringa e' sottostringa di un'altra, ignorando maiuscole/minuscole (case-insensitive)
     * @param searchField : stringa rappresentante il campo di un media in cui cercare il match parziale
     * @param queryValue : stringa rappresentante il valore o filtro con cui verificare il match parziale
     * @return bool : true se 'queryValue' e' sottostringa di 'searchField', false altrimenti
     */
    static bool checkPartialMatch(const std::string& searchField, const std::string& queryValue) {

        if (queryValue.empty()) return true;
        if (queryValue.size() > searchField.size()) return false;

        for (unsigned int i = 0; i <= searchField.size() - queryValue.size(); ++i) {
            unsigned int count = 0;
            for (unsigned int j = 0; j < queryValue.size(); ++j) {
                if (std::tolower(searchField[i+j]) == std::tolower(queryValue[j])) {
                    ++count;
                }
            }
            if (count == queryValue.size()) {
                return true;
            }
        }
        return false;
    }


    // === GETTER FILTRI RICERCA ===

    // filtri comuni
    unsigned int getMediaID() const { return mediaID; }
    const std::string& getMediaName() const { return mediaName; }
    const std::string& getMediaUploader() const { return mediaUploader; }
    const std::string& getMediaFormat() const { return mediaFormat; }
    const std::string& getMediaType() const { return mediaType; }
    const std::string& getMediaGenre() const { return mediaGenre; }
    const std::string& getMediaCategory() const { return mediaCategory; }
    unsigned int getMinimumMediaRating() const { return minimumMediaRating; }
    unsigned int getMaximumMediaRating() const { return maximumMediaRating; }

    // filtri Audio
    const std::string& getAudioArtist() const { return audioArtist; }
    const std::string& getAudioAlbum() const { return audioAlbum; }

    // filtri Video
    const std::string& getVideoDirector() const { return videoDirector; }
    const std::string& getVideoQuality() const { return videoQuality; }

    // filtri EBook
    const std::string& getEBookAuthor() const { return ebookAuthor; }
    const std::string& getEBookPublisher() const { return ebooPublisher; }

    // filtri Image
    const std::string& getImageCreator() const { return imageCreator; }
    const std::string& getImageLocation() const { return imageLocation; }


    // === SETTER FILTRI RICERCA ===

    // filtri comuni
    void setMediaID(unsigned int id) { mediaID = id; }
    void setMediaName(const std::string& name) { mediaName = name; }
    void setMediaUploader(const std::string& upl) { mediaUploader = upl;}
    void setMediaFormat(const std::string& fmt) { mediaFormat = fmt; }
    void setMediaType(const std::string& type) { mediaType = type; }
    void setMediaGenre(const std::string gnr) { mediaGenre = gnr; }
    void setMediaCategory(const std::string& ctg) { mediaCategory = ctg; }
    void setMinimumMediaRating(unsigned int minRtg) { minimumMediaRating = minRtg; }
    void setMaximumMediaRating(unsigned int maxRtg) { maximumMediaRating = maxRtg; }

    // filtri Audio
    void setAudioArtist(const std::string& art) { audioArtist = art; }
    void setAudioAlbum(const std::string& alb) { audioAlbum = alb; }

    // filtri Video
    void setVideoDirector(const std::string& dir) { videoDirector = dir; }
    void setVideoQuality(const std::string& qual) { videoQuality = qual; }

    // filtri EBook
    void setEBookAuthor(const std::string& auth) { ebookAuthor = auth; }
    void setEBookPublisher(const std::string& pbl) { ebooPublisher = pbl; }

    // filtri Image
    void setImageCreator(const std::string& imgCrt) { imageCreator = imgCrt; }
    void setImageLocation(const std::string& loc) { imageLocation = loc; }


    // === METODI HELPER RICERCA ===

    /** @brief clearSearchResults : svuota il vettore di risultati ricerca */
    void clearSearchResults() { searchResults.clear(); }

    /** @brief getSearchResults : getter dei media trovati (ovvero, dei loro identificatori univoci) */
    std::vector<unsigned int> getSearchResults() const { return searchResults; }

    /** @brief resetSearchQuery : reimposta il query allo stato iniziale */
    void resetSearchQuery() {
        mediaID = 0;
        mediaName = "", mediaUploader = "", mediaFormat = "", mediaType = "", mediaGenre = "", mediaCategory = "";
        minimumMediaRating = 0, maximumMediaRating = 0;
        audioArtist = "", audioAlbum = "", videoDirector = ""; videoQuality = "";
        ebookAuthor = "", ebooPublisher = "", imageCreator = "", imageLocation = "";
        const_cast<SearchQuery*>(this)->searchResults.clear(); }


    // === METODI HELPER FILTRI ===

    bool searchResultIsEmpty() const { return searchResults.empty(); }
    bool hasMediaTypeSet() const { return !mediaType.empty(); }


    // === HELPER PER MOSTRARE FILTRI RICERCA ===

    /**
     * @brief getSearchQueryFilters : getter dei filtri applicati al query
     * @return std::string : stringa contenente i filtri applicati al query
     */
    std::string getSearchQueryFilters() const {

        std::string filters = "";
        if (getMediaID() != 0) filters += "ID: " + std::to_string(getMediaID()) + " | ";
        if (!getMediaName().empty()) filters += "Name: " + getMediaName() + " | ";
        if (!getMediaUploader().empty()) filters += "Uploader: " + getMediaUploader() + " | ";
        if (!getMediaFormat().empty()) filters += "Format: " + getMediaFormat() + " | ";
        if (!getMediaType().empty()) filters += "Type: " + getMediaType() + " | ";
        if (!getMediaGenre().empty()) filters += "Genre: " + getMediaGenre() + " | ";
        if (!getMediaCategory().empty()) filters += "Category: " + getMediaCategory() + " | ";
        if (getMinimumMediaRating() != 0) filters += "Min Rating: " + std::to_string(getMinimumMediaRating()) + "/100 | ";
        if (!getAudioArtist().empty()) filters += "Artist: " + getAudioArtist() + " | ";
        if (!getAudioAlbum().empty()) filters += "Album: " + getAudioAlbum() + " | ";
        if (!getVideoDirector().empty()) filters += "Director: " + getVideoDirector() + " | ";
        if (!getVideoQuality().empty()) filters += "Quality: " + getVideoQuality() + " | ";
        if (!getEBookAuthor().empty()) filters += "Author: " + getEBookAuthor() + " | ";
        if (!getEBookPublisher().empty()) filters += "Publisher: " + getEBookPublisher() + " | ";
        if (!getImageCreator().empty()) filters += "Creator: " + getImageCreator() + " | ";
        if (!getImageLocation().empty()) filters += "Location: " + getImageCreator() + " | ";


        if (filters.empty()) filters = "Filters: None";

        return filters;
    }

private:

    // === FILTRI COMUNI ===

    unsigned int mediaID = 0;
    std::string mediaName = "";
    std::string mediaUploader = "";
    std::string mediaFormat = "";
    std::string mediaType = "";
    unsigned int minimumMediaRating = 0;
    unsigned int maximumMediaRating = 0;
    std::string mediaGenre = "";
    std::string mediaCategory = "";

    // === FILTRI SPECIFICI ===

    // filtri Audio
    std::string audioArtist = "";
    std::string audioAlbum = "";

    // filtri Video
    std::string videoDirector = "";
    std::string videoQuality = "";

    // filtri EBook
    std::string ebookAuthor = "";
    std::string ebooPublisher = "";

    // filtri Image
    std::string imageCreator = "";
    std::string imageLocation = "";


    // vettore con id dei media trovati
    mutable std::vector<unsigned int> searchResults;
};

}
}

#endif // MODEL_LIBRARY_SEARCH_QUERY_H

#ifndef MODEL_VISITORS_SEARCH_VISITOR_H
#define MODEL_VISITORS_SEARCH_VISITOR_H

#include "Model/Visitors/IConstVisitor.h"
#include "Model/Library/SearchQuery.h"

#include <vector>

/** @brief SearchVisitor
 *
 *  SearchVisitor e' una sottoclasse concreta che deriva pubblicamente da IConstVisitor.
 *  La classe SearchVisitor implementa l'operazione di ricerca dei media tramite il design pattern Visitor.
 *
 *  Utilizza un oggetto 'SearchQuery', passato per riferimento costante, contenente i filtri di ricerca.
 *  SearchQuery viene utilizzato per impostare i vari parametri di ricerca e contiene due metodi statici helper per verificare se una stringa
 *  e' un match esatto con un'altra oppure solo un match parziale (case-insensitive).
 *
 *  Durante l'operazione di ricerca, i media trovati in base ai parametri di ricerca impostati vengono registrati nel campo 'matches', un vettore
 *  contenente gli identificatori univoci dei media trovati. Questo è marcato 'mutable' per poter essere aggiornato/resettato.
 *
 *  SearchVisitor e' concreta in quanto va a ridefinire i virtuali puri erediati da IConstVisitor.
 *  Inoltre, per facilitare la ricerca, dispone di metodi helper privati per effettuare la ricerca sui campi comuni a tutti i media, oppure specifici
 *  ai tipi di media.
 *
 */


namespace Model {
namespace Visitors {

class SearchVisitor : public IConstVisitor {


public:

    // === COSTRUTTORE ===

    /**
     * @brief SearchVisitor : costruttore, imposta campi dati privati
     * @param query : SearchQuery passato per riferimento costant
     */
    SearchVisitor(const Model::Library::SearchQuery& query);


    // === RIDEFINIZIONE VIRTUALI PURI IConstVisitor

    /** @brief visit : applica l'operazione di ricerca specifica al tipo Audio */
    void visit(const Media::Audio& audio) const override;
    /** @brief visit : applica l'operazione di ricerca specifica al tipo EBook */
    void visit(const Media::EBook& ebook) const override;
    /** @brief visit : applica l'operazione di ricerca specifica al tipo Video */
    void visit(const Media::Video& video) const override;
    /** @brief visit : applica l'operazione di ricerca specifica al tipo Image */
    void visit(const Media::Image& image) const override;


    // === METODO HELPER PER CHECK COMUNI ===

    /**
     * @brief checkCommonMatches : helper per verificare match di campi comuni a tutti i tipi di media
     * @param media : riferimento costante a AbstractMedia
     * @return bool : true se match esatto o parziale trovato, false altrimenti
     */
    bool checkCommonMatches(const Media::AbstractMedia& media) const;


    // === METODI HELPER PER CHECK SPECIFICI ===

    /**
     * @brief checkAudioMatches : helper per verificare i match specifici al tipo Audio
     * @param audio : riferimento costante a Audio
     * @return bool : true se match esatto o parziale trovato, false altrimenti
     */
    bool checkAudioMatches(const Media::Audio& audio) const;

    /**
     * @brief checkEBookMatches : helper per verificare i match specifici al tipo EBook
     * @param ebook : riferimento costante a EBook
     * @return bool : true se match esatto o parziale trovato, false altrimenti
     */
    bool checkEBookMatches(const Media::EBook& ebook) const;

    /**
     * @brief checkVideoMatches : helper per verificare i match specifici al tipo Video
     * @param video : riferimento costante a Video
     * @return bool : true se match esatto o parziale trovato, false altrimenti
     */
    bool checkVideoMatches(const Media::Video& video) const;

    /**
     * @brief checkImageMatches : helper per verificare i match specifici al tipo Video
     * @param image : riferimento costante a Video
     * @return bool : true se match esatto o parziale trovato, false altrimenti
     */
    bool checkImageMatches(const Media::Image& image) const;


    /**
     * @brief getMatches : restituisce vettore con identificatori univoci dei media trovati nella ricerca
     * @return std::vector<unsigned int> : vettore di identificatori univoci dei media trovati
     */
    std::vector<unsigned int> getMatches() const;


private:

    const Model::Library::SearchQuery& searchQuery;  // filtri per la ricerca
    mutable std::vector<unsigned int> matches;       // identificatori dei media trovati
};


}
}

#endif // MODEL_VISITORS_SEARCH_VISITOR_H

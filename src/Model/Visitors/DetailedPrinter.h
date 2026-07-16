#ifndef MODEL_VISITORS_DETAILED_PRINTER_H
#define MODEL_VISITORS_DETAILED_PRINTER_H

#include "IConstVisitor.h"

#include <string>


/** @brief DetailedPrinter - NON UTILIZZATA
 *
 *  DetailedPrinter e' una sottoclasse concreta che deriva pubblicamente da IConstVisitor.
 *  Questa classe e' stata creata principalmente durante l'implementazione iniziale del modello dei dati ed e' stata utilizzata principalmente per debugging/test.
 *  Ho deciso comunque di tenerla per mostrare un'utilizzo semplice del design pattern Visitor.
 *
 *  Viene utilizzata per stampare/memorizzare le informazioni sui media, utilizzando un formato dettagliato.
 *
 *  Utilizza un singolo campo dati privato 'detailedPreview' per memorizzare le informazione del media.
 *  Questo viene inizializzato alla stringa vuota dal costruttore di default, e puo' essere reimpostato
 *  a questo valore originale mediante il metodo 'resetPrinter'.
 *
 *  DetailedPrinter utilizza un metodo helper 'printCommonAttributes' per facilitare la stampa/memorizzazione degli attributi comuni a tutti i media.
 *
 *  La classe DetailedPrinter e' concreta in quanto va a ridefinire i metodi virtuali puri ereditati da IConstVisito.r
 */


namespace Model {
namespace Visitors {

class DetailedPrinter : public IConstVisitor {

public:


    // === COSTRUTTORE DI DEFAULT ===

    /**
     * @brief DetailedPrinter : costruttore di default, inizializza campo privato
     */
    DetailedPrinter();


    // === GETTER & RESET ===

    /**
     * @brief getDetailedPreview : restituisce le informazioni dettagliate di un media
     * @return std::string : informazioni dettagliate sul media
     */
    const std::string& getDetailedPreview() const;

    /**
     * @brief resetPrinter : reimposta il visitor (serve const_cast) con i suoi valori iniziali
     */
    void resetPrinter();


    // === RIDEFINIZIONE VIRTUALI PURI IConstVisitor ===

    /** @brief mostra le informazioni dettagliate di un media Audio */
    void visit(const Media::Audio& audio) const override;
    /** @brief mostra le informazioni dettagliate di un media EBook */
    void visit(const Media::EBook& ebook) const override;
    /** @brief mostra le informazioni dettagliate di un media Video */
    void visit(const Media::Video& video) const override;
    /** @brief mostra le informazioni dettagliate di un media Image */
    void visit(const Media::Image& image) const override;


    // === HELPER PER CAMPI COMUNI ===

    /**
     * @brief printCommonAttributes : helper per stampare i campi attributi comuni a tutti i media
     * @param media : riferimento costante al media
     */
    void printCommonAttributes(const Media::AbstractMedia& media) const;

private:

    mutable std::string detailedPreview; // info dettagliate sul media


};

}
}


#endif // MODEL_VISITORS_DETAILED_PRINTER_H

#ifndef MODEL_VISITORS_CONCISE_PRINTER_H
#define MODEL_VISITORS_CONCISE_PRINTER_H

#include "IConstVisitor.h"

#include <string>

/** @brief ConcisePrinter - NOT UTILIZZATA
 *
 *  ConcisePrinter e' una sottoclasse concreta che deriva pubblicamente da IConstVisitor.
 *  Questa classe e' stata creata principalmente durante l'implementazione iniziale del modello dei dati ed e' stata utilizzata principalmente per debugging/test.
 *  Ho deciso comunque di tenerla per mostrare un'utilizzo semplice del design pattern Visitor.
 *
 *  Viene utilizzata per stampare/memorizzare le informazioni sui media, utilizzando un formato conciso.
 *
 *  Utilizza un singolo campo dati privato 'concisePreview' per memorizzare le informazione del media.
 *  Questo viene inizializzato alla stringa vuota dal costruttore di default, e puo' essere reimpostato a questo valore originale mediante il metodo 'resetPrinter'.
 *
 *  La classe ConcisePrinter e' concreta in quanto va a ridefinire i metodi virtuali puri ereditati da IConstVisitor.
 */

namespace Model {
namespace Visitors {

class ConcisePrinter : public IConstVisitor {

public:

    // === COSTRUTTORE DI DEFAULT ===

    /**
     * @brief ConcisePrinter : costruttore di default, inizializza campo privato
     */
    ConcisePrinter();


    // === GETTER & RESET ===

    /**
     * @brief getConcisePreview : restituisce informazioni base del media
     * @return std::string : info base del media
     */
    const std::string& getConcisePreview() const;

    /**
     * @brief resetPrinter : reimposta il visitor (serve const_cast) con i suoi valori iniziali
     */
    void resetPrinter();


    // === RIDEFINIZIONE VIRTUALI PURI IConstVisitor ===

    /** @brief mostra le informazioni base di un media Audio */
    void visit(const Media::Audio& audio) const override;
    /** @brief mostra le informazioni base di un media EBook */
    void visit(const Media::EBook& ebook) const override;
    /** @brief mostra le informazioni base di un media Video */
    void visit(const Media::Video& video) const override;
    /** @brief mostra le informazioni base di un media Image */
    void visit(const Media::Image& image) const override;

private:

    mutable std::string concisePreview; // info sintetiche (concise) del media

};

}
}

#endif // MODEL_VISITORS_CONCISE_PRINTER_H

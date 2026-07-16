#ifndef MODEL_VISITORS_MEDIA_EDITOR_H
#define MODEL_VISITORS_MEDIA_EDITOR_H

#include "IVisitor.h"

#include <unordered_map>
#include <string>


/** @brief MediaEditor
 *
 *  MediaEditor e' una sottoclasse concreta che deriva pubblicamente da IVisitor. Implementa il design pattern "Visitor" per l'operazione di modifica dei media.
 *
 *  MediaEditor contiene un singolo campo dati privato 'mediaEdits' del tipo std::unordered_map<std::string, std::string> che corrisponde
 *  alle coppie (nome attributo, valore attributo) delle modifiche da effettuare sul media.
 *
 *  MediaEditor utilizza i vari builder concreti del namespace Model::Builders. In particolare, i nomi degli attributi sono presi dai vettori
 *  costanti statici di stringhe definiti nei corrispondenti builder di ciasun media.
 *
 *  MediaEditor dispone di un singolo costruttore, che prende come unico parametro la mappa di modifiche da effettuare, passato come riferimento costante.
 *
 *  MediaEditor e' concreta in quanto ridefinisce i metodi virtuali puri ereditati da IVisitor, in modo specifico per ciascun tipo.
 *
 */

namespace Model {
namespace Visitors {

class MediaEditor : public IVisitor {

public:

    // === COSTRUTTORE ===

    /**
     * @brief MediaEditor : costruttore, imposta la mappa delle modifiche da effettuare
     * @param edits : mappa delle modifiche da effettuare
     */
    MediaEditor(const std::unordered_map<std::string, std::string>& edits);


    // === RIDEFINIZIONE VIRTUALI PURI IVistor ===

    /** @brief visit : applica le modifiche al media Audio utilizzando AudioBuilder */
    void visit(Media::Audio& audio) override;
    /** @brief visit : applica le modifiche al media EBook utilizzando EBookBuilder */
    void visit(Media::EBook& ebook) override;
    /** @brief visit : applica le modifiche al media Video utilizzando VideoBuilder */
    void visit(Media::Video& video) override;
    /** @brief visit : applica le modifiche al media Image utilizzando ImageBuilder */
    void visit(Media::Image& image) override;


private:

    // === MAPPA DI MODIFICHE ===

    // corrisponde agli attributi del media, come coppie stringhe (nome attributo, valore attributo)
    std::unordered_map<std::string, std::string> mediaEdits;

};

}
}

#endif // MODEL_VISITORS_MEDIA_EDITOR_H

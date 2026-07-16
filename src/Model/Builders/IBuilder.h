#ifndef MODEL_BUILDERS_I_BUILDER_H
#define MODEL_BUILDERS_I_BUILDER_H

#include "Model/Media/AbstractMedia.h"

#include <memory>

/** @brief IBuilder
 *
 *  IBuilder rappresenta l'interfaccia base astratta per l'implementazione del design pattern "Builder" per le operazioni di creazione/modifica dei media.
 *
 *  I media sono costruiti con i loro corrispondenti costruttori di default, che inizializzano i loro attributi con valori di default.
 *  Questi poi vengono modificati dai vari builder concreti.
 *
 *  Il metodo virtuale puro 'buildMedia' viene ridefinito in ciascun builder per restituire un puntatore (del tipo std::shared_ptr) al media creato.


 *  NOTA PER BUILDER CONCRETI:
 *
 *  Ciascun builder concreto definisce un vettore costante statico di stringhe, corrispondente ai nomi degli attributi del media.
 *  Questo vettore viene utilizzato anche per operazioni come validazione e persistenza dati, e anche per facilitare la creazione dei custom widgets dell'interfaccia grafica.
 *
 *  Le modifiche da applicare sono salvate in un'oggetto del tipo std::unordered_map<std::string, std::string>, contenente le coppie di attributi (nome, valore) del media.
 *  Questo e' solitamente marcato come 'mutable' in modo da poter essere utilizzato in metodi marcati 'const', come ad esempio 'buildMedia()'.
 *
 *  Ciasun builder definisce il metodo 'applyEdits' che applica le modifiche su una copia temporanea del media, ottenuta tramite il costruttore polimorfo 'clone' (definito in AbstractFile).
 *  Le modifiche vengono poi "validate" utilizzando il visitor concreto Model::Visitors::MediaValidator. Se il media modificato risulta valido, viene restituito.
 *  Altrimenti, viene sollevata una eccezione del tipo Model::Visitors::MediaValidatorException (con un messaggio descrittivo sui possibili errori trovati).
 *
 *  Ogni sottoclasse di IBuilder definisce un vettore statico di stringhe, contenente i nomi degli attributi specifici del tipo di media.
 *  Ho deciso di renderlo pubblico per facilitare altre operazioni parti del proggetto, come validazione, persistenza dati e per facilitare la creazione dei custom widget dell'interfaccia grafica.
 *
 */

namespace Model {
namespace Builders {

class IBuilder {

public:

    /** @brief ~IBuilder : distruttore virtuale */
    virtual ~IBuilder() = default;

    /**
     * @brief buildMedia : metodo virtuale puro per l'implementazione del design pattern "Builder"
     * @return std::shared_ptr<AbstractMedia> : smart pointer a AbstractMedia
     */
    virtual std::shared_ptr<Media::AbstractMedia> buildMedia() const = 0;
};

}
}

#endif // MODEL_BUILDERS_I_BUILDER_H

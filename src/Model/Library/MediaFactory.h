#ifndef MODEL_LIBRARY_MEDIA_FACTORY_H
#define MODEL_LIBRARY_MEDIA_FACTORY_H

#include "Model/Media/AbstractMedia.h"

#include <string>
#include <unordered_map>
#include <memory>

/** @brief MediaFactory
 *
 *  MediaFactory implementa il design pattern "Factory"
 *  Viene utilizzata per implementare l'operazione di creazione dei vari tipi di media supportati dalla libreria virtuale.
 *
 *  MediaFactory dispone di un metodo pubblico 'createMedia' che prende come parametri una stringa 'mediaType', che indica il tipo di media da costruire, e una mappa 'mediaAttributes'
 *  del tipo std::unordered_map<std::string, std::string>, che associa i nomi degli attributi ai rispettivi valori (che variano in base al tipo da creare).
 *  La costruzione poi avviene mediante metodi helper privati, che si occupano della creazione dei tipi specifici di media, utilizzando i loro builder corrispondenti.
 *
 *  Il metodo 'buildMedia' restituisce uno smart pointer del tipo std::shared_ptr al media creato.
 *  Se si verifica un'errore durante la fase di costruzione, questo viene segnalato mediante il lancio di eccezioni del tipo std::runtime_error (tipo di media non valido) oppure
 *  del tipo MediaValidatorException (che contiene un messaggio descrittivo con gli errori rilevati).
 *
 */


namespace Model {
namespace Library {

class MediaFactory {

public:

    /**
     * @brief createMedia : crea un nuovo media, lo inserisce in libreria, e restituisce un puntatore a esso
     * @param type : tipo di media costruire ("AUDIO", "VIDEO", "IMAGE", ...)
     * @param attr : mappa con gli attributi (nome/valore) per la costruzione
     * @return std::shared_ptr<AbstractMedia> : smart pointer al media creato
     *
     * @throws std::runtime_error se il tipo 'mediaType' non e' valido
     * @throws MediaValidatorException se la costruzione fallisce (con messaggio con l'errore passato dal builder specifico)
     */
    std::shared_ptr<Model::Media::AbstractMedia> createMedia(const std::string& type, const std::unordered_map<std::string, std::string>& attr);


private:


    // === HELPER PER COSTRUZIONE TIPO SPECIFICI ===

    /**
     * @brief createAudio : helper privato per la costruzione di un media Audio
     * @param attr : attributi del media Audio
     * @return std::shared_ptr<AbstractMedia> : smart pointer al media Audio creato
     */
    std::shared_ptr<Model::Media::AbstractMedia> createAudio(const std::unordered_map<std::string, std::string>& attr);

    /**
     * @brief createVideo : helper privato per la costruzione di un media Video
     * @param attr : attributi del media Video
     * @return std::shared_ptr<AbstractMedia> : smart pointer al media Video creato
     */
    std::shared_ptr<Model::Media::AbstractMedia> createVideo(const std::unordered_map<std::string, std::string>& attr);

    /**
     * @brief createEBook : helper privato per la costruzione di un media EBook
     * @param attr : attributi del media EBook
     * @return std::shared_ptr<AbstractMedia> : smart pointer al media EBook creato
     */
    std::shared_ptr<Model::Media::AbstractMedia> createEBook(const std::unordered_map<std::string, std::string>& attr);

    /**
     * @brief createImage : helper privato per la costruzione di un media Image
     * @param attr : attributi del media Image
     * @return std::shared_ptr<AbstractMedia> : smart pointer al media Image creato
     */
    std::shared_ptr<Model::Media::AbstractMedia> createImage(const std::unordered_map<std::string, std::string>& attr);

};

}
}

#endif // MODEL_LIBRARY_MEDIA_FACTORY_H

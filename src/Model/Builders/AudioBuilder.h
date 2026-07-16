#ifndef MODEL_BUILDERS_AUDIO_BUILDER_H
#define MODEL_BUILDERS_AUDIO_BUILDER_H

#include "IBuilder.h"
#include "Model/Media/Audio.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

/** @brief AudioBuilder
 *
 *  AudioBuilder e' una sottoclasse concreta di IBuilder che implementa il design pattern "Builder" per i media di tipo Audio.

 *  AudioBuilder dispone di un costruttore di default, un costruttore di copia e i setter per i vari attributi specifici al tipo Audio.
 *  Contiene come campi dati privati uno smart pointer 'audioPointer' del tipo std::shared_ptr e una mappa 'editsToApply' delle modifiche da applicare.
 *  Il vettore costante statico 'AUDIO_ATTRIBUTES' contiene i nomi degli attributi per i media di tipo Audio.
 */

namespace Model {
namespace Builders {

class AudioBuilder : public IBuilder {

public:

    // vettore statico costante con nomi attributi del tipo Audio
    static const std::vector<std::string> AUDIO_ATTRIBUTES;


    // === COSTRUTTORI ===

    /** @brief AudioBuilder : costruttore di default AudioBuilder, inizializza 'audioPointer' con il costruttore di default di Audio */
    AudioBuilder();

    /**
     * @brief AudioBuilder : costruttore di copia, inzializza 'audioPointer' con una copia di un oggetto Audio, ottenuta mediante il costruttore di copia polimorfo di Audio 'clone'
     * @param audio : riferimento costante a Audio
     */
    AudioBuilder(const Model::Media::Audio& audio);


    // === SETTER CAMPI COMUNI ===

    AudioBuilder& setPath(const std::string& path);
    AudioBuilder& setSize(float size);
    AudioBuilder& setName(const std::string& name);
    AudioBuilder& setUploader(const std::string& uploader);
    AudioBuilder& setFormat(const std::string& format);
    AudioBuilder& setRating(unsigned rating);

    // === SETTER CAMPI AUDIO ===

    AudioBuilder& setArtist(const std::string& art);
    AudioBuilder& setGenre(const std::string& gnr);
    AudioBuilder& setAlbum(const std::string& alb);
    AudioBuilder& setReleaseYear(unsigned int year);
    AudioBuilder& setLengthInMinutes(unsigned int length);
    AudioBuilder& setBitRate(unsigned int br);
    AudioBuilder& setSampleRate(float sr);
    AudioBuilder& setBitDepth(unsigned int bd);
    AudioBuilder& setChannels(unsigned int ch);
    AudioBuilder& setCollaborators(const std::string& clb);


    /**
     * @brief buildMedia : applica le modifiche contenute in 'editsToApply' a una copia del media Audio e verifica la validita' mediante il MediaValidator
     * @throws MediaValidatorException se le modifiche applicate portano ad un media Audio non valido
     * @return std::shared_ptr: smart pointer al media Audio dopo aver applicato le modifiche
     */
    std::shared_ptr<Model::Media::AbstractMedia> buildMedia() const override;

private:

    std::shared_ptr<Model::Media::Audio> audioPointer;                 // smart pointer al media Audio
    mutable std::unordered_map<std::string, std::string> editsToApply; // mappa di modifiche da effettuare


    /**
     * @brief applyEdits : applica le modifiche contenute in 'editsToApply' ad una copia del media Audio
     * @return Audio* : puntatore a un nuovo media Audio con le modifiche
     */
    Media::Audio* applyEdits() const;

};

}
}

#endif // MODEL_BUILDERS_AUDIO_BUILDER_H

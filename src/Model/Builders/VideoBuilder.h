#ifndef MODEL_BUILDERS_VIDEO_BUILDER_H
#define MODEL_BUILDERS_VIDEO_BUILDER_H

#include "IBuilder.h"
#include "Model/Media/Video.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>


/** @brief VideoBuilder
 *
 *  VideoBuilder e' una sottoclasse concreta di IBuilder che implementa il design pattern "Builder" per i media di tipo Video.

 *  VideoBuilder dispone di un costruttore di default, un costruttore di copia e i setter per i vari attributi specifici al tipo Video.
 *  Contiene come campi dati privati uno smart pointer 'videoPointer' del tipo std::shared_ptr e una mappa 'editsToApply' delle modifiche da applicare.
 *  Il vettore costante statico 'VIDEO_ATTRIBUTES' contiene i nomi degli attributi per i media di tipo Video.
 */

namespace Model {
namespace Builders {

class VideoBuilder : public IBuilder {

public:

    // vettore statico costante con nomi attributi del tipo Video
    static const std::vector<std::string> VIDEO_ATTRIBUTES;


    // === COSTRUTTORI ===

    /** @brief VideoBuilder : costruttore di default VideoBuilder, inizializza 'videoPointer' con il costruttore di default di Video */
    VideoBuilder();


    /**
     * @brief VideoBuilder : costruttore di copia, inzializza 'videoPointer' con una copia di un oggetto Video, ottenuta mediante il costruttore di copia polimorfo di Video 'clone'
     * @param video : riferimento costante a Video
     */
    VideoBuilder(const Model::Media::Video& video);


    // === SETTER CAMPI COMUNI ===

    VideoBuilder& setPath(const std::string& path);
    VideoBuilder& setSize(float size);
    VideoBuilder& setName(const std::string& name);
    VideoBuilder& setUploader(const std::string& uploader);
    VideoBuilder& setFormat(const std::string& format);
    VideoBuilder& setRating(unsigned rating);

    // === SETTER CAMPI VIDEO ===

    VideoBuilder& setDirector(const std::string& dir);
    VideoBuilder& setGenre(const std::string& gnr);
    VideoBuilder& setReleaseYear(unsigned int year);
    VideoBuilder& setLength(unsigned int length);
    VideoBuilder& setFrameRate(unsigned int fr);
    VideoBuilder& setResolutionWidth(unsigned int width);
    VideoBuilder& setResolutionHeight(unsigned int height);
    VideoBuilder& setColorDepth(unsigned int depth);
    VideoBuilder& setSubtitles(const std::string& subs);
    VideoBuilder& setLanguage(const std::string& lang);



    /**
     * @brief buildMedia : applica le modifiche contenute in 'editsToApply' a una copia del media Video e verifica la validita' mediante il MediaValidator
     * @throws MediaValidatorException se le modifiche applicate portano ad un media Video non valido
     * @return std::shared_ptr: smart pointer al media Video dopo aver applicato le modifiche
     */
    std::shared_ptr<Model::Media::AbstractMedia> buildMedia() const override;

private:

    std::shared_ptr<Model::Media::Video> videoPointer;                 // smart pointer al media Video
    mutable std::unordered_map<std::string, std::string> editsToApply; // mappa di modifiche da effettuare


    /**
     * @brief applyEdits : applica le modifiche contenute in 'editsToApply' ad una copia del media Video
     * @return Video* : puntatore a un nuovo media Video con le modifiche
     */
    Media::Video* applyEdits() const;

};

}
}

#endif // MODEL_BUILDERS_VIDEO_BUILDER_H

#ifndef MODEL_BUILDERS_IMAGE_BUILDER_H
#define MODEL_BUILDERS_IMAGE_BUILDER_H

#include "IBuilder.h"
#include "Model/Media/Image.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>


/** @brief ImageBuilder
 *
 *  ImageBuilder e' una sottoclasse concreta di IBuilder che implementa il design pattern "Builder" per i media di tipo Image.

 *  ImageBuilder dispone di un costruttore di default, un costruttore di copia e i setter per i vari attributi specifici al tipo Image.
 *  Contiene come campi dati privati uno smart pointer 'imagePointer' del tipo std::shared_ptr e una mappa 'editsToApply' delle modifiche da applicare.
 *  Il vettore costante statico 'IMAGE_ATTRIBUTES' contiene i nomi degli attributi per i media di tipo Image.
 */

namespace Model {
namespace Builders {

class ImageBuilder : public IBuilder {

public:

    // vettore statico costante con nomi attributi del tipo Image
    static const std::vector<std::string> IMAGE_ATTRIBUTES;


    // === COSTRUTTORI ===

    /** @brief ImageBuilder : costruttore di default ImageBuilder, inizializza 'imagePointer' con il costruttore di default di Image */
    ImageBuilder();

    /**
     * @brief ImageBuilder : costruttore di copia, inzializza 'imagePointer' con una copia di un oggetto Image, ottenuta mediante il costruttore di copia polimorfo di Image 'clone'
     * @param image : riferimento costante a Image
     */
    ImageBuilder(const Model::Media::Image& image);


    // === SETTER CAMPI COMUNI ===

    ImageBuilder& setPath(const std::string& path);
    ImageBuilder& setSize(float size);
    ImageBuilder& setName(const std::string& name);
    ImageBuilder& setUploader(const std::string& uploader);
    ImageBuilder& setFormat(const std::string& format);
    ImageBuilder& setRating(unsigned rating);

    // === SETTER CAMPI IMAGE ===

    ImageBuilder& setDateCreated(const std::string& created);
    ImageBuilder& setCreator(const std::string& creator);
    ImageBuilder& setCategory(const std::string& category);
    ImageBuilder& setResolutionWidth(unsigned int resW);
    ImageBuilder& setResolutionHeight(unsigned int resH);
    ImageBuilder& setAspectRatioWidth(unsigned int aspW);
    ImageBuilder& setAspectRatioHeight(unsigned int aspH);
    ImageBuilder& setImageBitdepth(unsigned int bd);
    ImageBuilder& setCompression(bool cmpr);
    ImageBuilder& setLocationTaken(const std::string& location);

    /**
     * @brief buildMedia : applica le modifiche contenute in 'editsToApply' a una copia del media Image e verifica la validita' mediante il MediaValidator
     * @throws MediaValidatorException se le modifiche applicate portano ad un media Image non valido
     * @return std::shared_ptr: smart pointer al media Image dopo aver applicato le modifiche
     */
    std::shared_ptr<Model::Media::AbstractMedia> buildMedia() const override;

private:

    std::shared_ptr<Model::Media::Image> imagePointer;                 // smart pointer al media Image
    mutable std::unordered_map<std::string, std::string> editsToApply; // mappa di modifiche da effettuare

    Media::Image* applyEdits() const;
};

}
}

#endif // MODEL_BUILDERS_IMAGE_BUILDER_H

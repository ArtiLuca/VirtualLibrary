#ifndef MODEL_BUILDERS_EBOOK_BUILDER_H
#define MODEL_BUILDERS_EBOOK_BUILDER_H

#include "IBuilder.h"
#include "Model/Media/EBook.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

/** @brief EBookBuilder
 *
 *  EBookBuilder e' una sottoclasse concreta di IBuilder che implementa il design pattern "Builder" per i media di tipo EBook.

 *  EBookBuilder dispone di un costruttore di default, un costruttore di copia e i setter per i vari attributi specifici al tipo EBook.
 *  Contiene come campi dati privati uno smart pointer 'ebookPointer' del tipo std::shared_ptr e una mappa 'editsToApply' delle modifiche da applicare.
 *  Il vettore costante statico 'EBOOK_ATTRIBUTES' contiene i nomi degli attributi per i media di tipo EBook.
 */



namespace Model {
namespace Builders {

class EBookBuilder : public IBuilder {

public:

    // vettore statico costante con nomi attributi del tipo EBook
    static const std::vector<std::string> EBOOK_ATTRIBUTES;


    // === COSTRUTTORI ===

    /** @brief EBookBuilder : costruttore di default EBookBuilder, inizializza 'ebookPointer' con il costruttore di default di EBook */
    EBookBuilder();

    /**
     * @brief EBookBuilder : costruttore di copia, inzializza 'ebookPointer' con una copia di un oggetto EBook, ottenuta mediante il costruttore di copia polimorfo di EBook 'clone'
     * @param ebook : riferimento costante a EBook
     */
    EBookBuilder(const Model::Media::EBook& ebook);


    // === SETTER CAMPI COMUNI ===

    EBookBuilder& setPath(const std::string& path);
    EBookBuilder& setSize(float size);
    EBookBuilder& setName(const std::string& name);
    EBookBuilder& setUploader(const std::string& uploader);
    EBookBuilder& setFormat(const std::string& format);
    EBookBuilder& setRating(unsigned rating);

    // === SETTER CAMPI EBOOK

    EBookBuilder& setAuthor(const std::string& auth);
    EBookBuilder& setPublisher(const std::string& pbl);
    EBookBuilder& setReleaseYear(unsigned int year);
    EBookBuilder& setISBN(const std::string& isbn);
    EBookBuilder& setLengthInPages(unsigned int length);
    EBookBuilder& setCategory(const std::string& ctg);
    EBookBuilder& setLanguage(const std::string& lang);
    EBookBuilder& setCoverImagePath(const std::string& cp);
    EBookBuilder& setHasImages(bool img);


    /**
     * @brief buildMedia : applica le modifiche contenute in 'editsToApply' a una copia del media EBook e verifica la validita' mediante il MediaValidator
     * @throws MediaValidatorException se le modifiche applicate portano ad un media EBook non valido
     * @return std::shared_ptr: smart pointer al media EBook dopo aver applicato le modifiche
     */
    std::shared_ptr<Model::Media::AbstractMedia> buildMedia() const override;


private:

    std::shared_ptr<Model::Media::EBook> ebookPointer;                 // smart pointer al media EBook
    mutable std::unordered_map<std::string, std::string> editsToApply; // mappa di modifiche da effettuare

    /**
     * @brief applyEdits : applica le modifiche contenute in 'editsToApply' ad una copia del media EBook
     * @return EBook* : puntatore a un nuovo media EBook con le modifiche
     */
    Media::EBook* applyEdits() const;
};

}
}

#endif // MODEL_BUILDERS_EBOOK_BUILDER_H


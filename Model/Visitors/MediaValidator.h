#ifndef MODEL_VISITORS_MEDIA_VALIDATOR_H
#define MODEL_VISITORS_MEDIA_VALIDATOR_H

#include "IConstVisitor.h"
#include "Model/Media/Audio.h"
#include "Model/Media/EBook.h"
#include "Model/Media/Video.h"

#include <string>
#include <vector>
#include <stdexcept>


namespace Model {
namespace Visitors {


/** @brief MediaValidatorException
 *
 *  MediaValidatorException deriva da std::runtime_error e rappresenta una custom exception usata per gli eventuali errori durante la validazione.
 *  Una eccezione del tipo MediaValidatorException viene lanciata quando uno o piu' controlli sulla validita' di un media fallisce.
 */

class MediaValidatorException : public std::runtime_error {

public:

    /**
     * @brief MediaValidatorException : costruttore, prende come riferimento costante il messaggio d'errore
     * @param msg : messaggio d'errore descrittivo
     */
    explicit MediaValidatorException(const std::string& msg)
        : std::runtime_error(msg)
    {}
};


/** @brief MediaValidator
 *
 *  MediaValidator deriva da IConstVisitor e implementa il design pattern "Visitor" per effettuare i controlli di validazione sui vari tipi di media.
 *
 *  MediaValidator dispone di un campo dati privato 'validMedia' per indicare la validita' del media e del campo dati privato 'errorMessage' che agisce da messaggio cumulativo
 *  di tutti gli (eventuali) errori trovati durante il controllo di validazione del media (marcato 'mutable' per rendere possibile la sua modifica).
 *  Questi campi privati sono inizializzati dal costruttore di default, e possono essere reimpostati ai loro valori iniziali tramite 'resetValidator'.
 *
 *  MediaValidator dispone di metodi "helper" per facilitare il controllo della validita', come ad esempio il metodo 'isValidFormat' per verificare la validita' del formato del media,
 *  e dei due template di funzione 'isWithinRange' e 'validateCommonAttributes' usati per controllare limiti numerici imposti ai media e per facilitare le verifiche comuni.
 *
 *  MediaValidator e' concreta in quanto va a ridefinire i metodi virtuali puri ereditati da IConstVisitor, in modo specifico per ciascun tipo di media.
 */

class MediaValidator : public IConstVisitor {

public:

    // === COSTRUTTORE ===

    /** @brief MediaValidator : costruttore di default di MediaValidator, inizializza 'validMedia' a true, e 'errorMessage' alla stringa vuota. */
    MediaValidator();


    // === GETTER CAMPI DATI PRIVATI ===

    /**
     * @brief isValidMedia : verifica se l'ultimo media controllato e' valido ("getter" di 'validMedia')
     * @return bool : true se il media e' valido, false altrimenti
     */
    bool isValidMedia() const;

    /**
     * @brief getErrorMessage : restituisce il messaggio contenente gli errori trovati (se presenti)
     * @return const std::string& : riferimento costante al messaggio contentente gli errori
     */
    const std::string& getErrorMessage() const;


    // === METODO PER RESET ===

    /**
     * @brief resetValidator : reimposta i campi privati ai valori iniziali
     * @details serve fare un 'const_cast' in quanto MediaValidator deriva da IConstVisitor
    */
    void resetValidator();


    // === METODI "HELPER" AUSILIARI ===

    /**
     * @brief isWithinRange : template di funzione per verificare se il valore di un attributo numerico rientra in un dato intervallo
     * @param T : tipo del valore
     * @param val : valore da verificare
     * @param min : valore minimo permissibile
     * @param max : valore massimo permissibile
     * @return : true se il valore rientra nell'intervallo, false altrimenti
     */
    template <typename T>
    bool isWithinRange(T val, T min, T max) const {
        return (val >= min && val <= max);
    }

    /**
     * @brief validateCommonAttributes : template di funzione per controllare la validita' degli attributi comuni a tutti i media
     * @param T : tipo del media (che deriva necessariamente da AbstractMedia)
     * @param media : riferimento costante al media da controllare
     */
    template <typename T>
    void validateCommonAttributes(const T& media) const {

        if (media.getUniqueID() == Media::AbstractFile::INVALID_UNIQUE_ID) {
            errorMessage += "Unique identifier cannot be 0.\n";
            validMedia = false;
        }
        if (media.getFilePath().empty()) {
            errorMessage += "File path is empty.\n";
            validMedia = false;
        }
        if (!isWithinRange(media.getFileSize(), Media::AbstractFile::MIN_FILE_SIZE, Media::AbstractFile::MAX_FILE_SIZE)) {
            errorMessage += "File size is not a valid value (" + std::to_string(media.getFileSize()) + " MB).\n";
        }
        if (media.getMediaName().empty()) {
            errorMessage += "File name is empty.\n";
            validMedia = false;
        }
        if (media.getMediaUploader().empty()) {
            errorMessage += "File uploader is empty.\n";
            validMedia = false;
        }
        if (media.getMediaFormat().empty()) {
            errorMessage += "File format is empty.\n";
        }
        if (media.getMediaRating() != Media::AbstractMedia::defaultRating) {
            if (!isWithinRange(media.getMediaRating(), Media::AbstractMedia::MIN_MEDIA_RATING, Media::AbstractMedia::MAX_MEDIA_RATING)) {
                errorMessage += "Media rating is not valid (" + std::to_string(media.getMediaRating()) + ").\n";
                validMedia = false;
            }
        }
    }

    /**
     * @brief isValidFormat : controlla se il formato usato e' ammesso per il dato tipo di media
     * @param fmt : formato del media da controllare
     * @param formats : vettore dei formati ammessi al media
     * @return bool : true se il formato e' ammesso al media, false altrimenti
     */
    bool isValidFormat(const std::string& fmt, const std::vector<std::string>& formats) const;


    // === RIDEFINIZIONE VIRTUALI PURI IConstVisitor ===

    /** @brief visit : verifica la validita' di un media di tipo Audio */
    void visit(const Media::Audio& audio) const override;
    /** @brief visit : verifica la validita' di un media di tipo EBook */
    void visit(const Media::EBook& ebook) const override;
    /** @brief visit : verifica la validita' di un media di tipo Video */
    void visit(const Media::Video& video) const override;
    /** @brief visit : verifica la validita' di un media di tipo Image */
    void visit(const Media::Image& image) const override;

private:

    mutable bool validMedia;           // booleano per indicare se media valido
    mutable std::string errorMessage;  // lista di eventuali errori trovati
};

}
}

#endif // MODEL_VISITORS_MEDIA_VALIDATOR_H

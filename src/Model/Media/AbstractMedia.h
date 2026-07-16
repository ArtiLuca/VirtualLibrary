#ifndef MODEL_MEDIA_ABSTRACT_MEDIA_H
#define MODEL_MEDIA_ABSTRACT_MEDIA_H

#include "AbstractFile.h"
#include <QJsonObject>

#include <string>

/** @brief AbstractMedia
 *
 *  AbstractMedia deriva virtualmente e pubblicamente da AbstractFile e rappresenta un'ulteriore astrazione del concetto di "file multimediale".
 *  Oltre agli attributi ereditati ad AbstractFile, definisce altri attributi ritenuti comuni a tutti i media, tra cui il nome, l'uploader, il format, e un campo rating.
 *
 *  AbstractMedia dispone di un costruttore di default , un costruttore di copia, la ridefinizione dell'operatore di assegnazione, un distruttore virtuale e vari getter/setter per i campi dati.
 *
 *  AbstractMedia e' astratta in quanto non va a ridefinire i metodi virtuali puri 'accept' e 'clone' ereditati da AbstractFile e ne aggiunge altri suoi nuovi.
 *  I metodi virtuali puri 'hasLength' e 'hasResolution' vengono ridefiniti nelle varie classi concrete per ritornare true nei media in cui questi attributi sono logicamente applicabili.
 *
 *  I metodi virtuali puri 'fromJson' e 'toJson' vengono ridefiniti per implementare la persistenza dei dati (in formato JSON) e sono gli unici metodi del modello in cui vengono usati elementi Qt.
 *
 *  NOTA: il metodo virtuale puro 'displayStringType' viene ridefinito per restituire una stringa con il nome del tipo e viene utilizzato solo per le stampe e non come sostituzione al polimorfismo.
 */

namespace Model {
namespace Media {


class AbstractMedia : virtual public AbstractFile {

public:

    // === COSTANTI STATICHE ===

    static const unsigned int MIN_MEDIA_RATING;
    static const unsigned int MAX_MEDIA_RATING;
    static const unsigned int MIN_RELEASE_YEAR;
    static const unsigned int MAX_RELEASE_YEAR;
    static const std::string defaultName;
    static const std::string defaultUploader;
    static const std::string defaultFormat;
    static const unsigned int defaultRating;


    // === DISTRUTTORE ===

    /** @brief ~AbstractMedia : distruttore virtuale */
    virtual ~AbstractMedia() = default;


    // === GETTER ===

    const std::string& getMediaName() const;
    const std::string& getMediaUploader() const;
    const std::string& getMediaFormat() const;
    unsigned int getMediaRating() const;


    // === SETTER  ===

    void setMediaName(const std::string& name);
    void setMediaUploader(const std::string& uploader);
    void setMediaFormat(const std::string& format);
    void setMediaRating(unsigned int rating);


    // === METODI VIRTUALI PURI ===

    /**
     * @brief hasLength : virtuale puro per verificare la presenza/assenza di una durata
     * @return bool : true se il media dispone di una durata, false altrimenti
     */
    virtual bool hasLength() const = 0;

    /**
     * @brief hasResolution : virtuale puro per verificare la presenza/assenza di una risoluzione
     * @return bool : true se il media dispone di una risoluzione, false altrimenti
     */
    virtual bool hasResolution() const = 0;


    // === PERSISTENZA DEI DATI (JSON) ===

    /** @brief toJson : virtuale puro per la persistenza dati con JSON (serializzazione) */
    virtual QJsonObject toJson() const = 0;

    /** @brief fromJson : virtuale puro per la persistenza dati con JSON (deserializzazione) */
    virtual void fromJson(const QJsonObject& obj) = 0;


    /** @brief displayStringType : virtuale puro usato solamente per mostrare il nome del tipo del media */
    virtual std::string displayStringType() const = 0;


protected:

    // === CAMPI DATI ===

    std::string mediaName;     // nome del media
    std::string mediaUploader; // uploader il media
    std::string mediaFormat;   // formato del media
    unsigned int mediaRating;  // recensione (opzionale)


    // === COSTRUTTORI, ASSEGNAZIONE ===

    /** @brief AbstractMedia : costruttore di default di AbstractMedia, imposta campi dati con valori di default */
    AbstractMedia();

    /**
     * @brief AbstractMedia : costruttore parametrizzato
     * @param filePath : path del media
     * @param size : dimensione del media
     * @param name : nome del media
     * @param uploader : uploader del media
     * @param format : formato del media
     */
    AbstractMedia(const std::string& path, float size, const std::string& name, const std::string& uploader, const std::string& format, unsigned int rating);

    /** @brief AbstractMedia : costruttore di copia di AbstractMedia */
    AbstractMedia(const AbstractMedia& media);

    /**
     * @brief operator= : operatore di assegnazione */
    AbstractMedia& operator=(const AbstractMedia& media);
};

}
}

#endif // MODEL_MEDIA_ABSTRACT_MEDIA_H

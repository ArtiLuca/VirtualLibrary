#ifndef MODEL_MEDIA_EBOOK_H
#define MODEL_MEDIA_EBOOK_H

#include "AbstractMedia.h"
#include "Model/Utilities/IMediaLength.h"

#include <string>
#include <vector>
#include <QJsonObject>

/** @brief EBook
 *
 *  EBook e' una sottoclasse concreta derivata pubblicamente da AbstractMedia e IMediaLength.
 *  Un oggetto della classe EBook rappresenta un e-book, cioe' con durata espressa per numero di pagine e senza una risoluzione.
 *
 *  Un oggetto EBook rappresenta un e-book tramite il suo autore, casa editrice ("publisher"), anno di pubblicazione, il suo ISBN-13, la sua "durata" (in pagine),
 *  la sua categoria, la lingua del testo, il path della copertina (se presente) e dal fatto di avere al suo interno immagini oppure no.
 *
 *  La classe EBook dispone di un costruttore di default, un costruttore di copia, la ridefinizione dell'operatore di assegnazione e dei getter/setter dei campi dati privati.
 *  Il costruttore di default di EBook inizializza i campi dati ai valori di default definiti dalle costanti statiche nella parte pubblica della classe.
 *
 *  Un media EBook di Virtual Library e' considerato valido se:
 *
 *       - ha una durata espressa in pagine e non dispone di una risoluzione
 *       - contiene tutti i campi definiti (con l'eccezione del campo 'category')
 *       - ha un ISBN composto da esattamente 13 caratteri, tutti numerici, senza whitespaces
 *       - ha una durata in pagine definita nell'intervallo (0-10000]
 *       - ha un formato ammesso al tipo EBook
 *
 *  La classe EBook e' concreta in quanto va a ridefinire i metodi virtuali puri ereditati da IMediaLength e AbstractMedia (e quindi anche AbstractFile) in modo specifico per il tipo EBook.
 *
 */

namespace Model {
namespace Media {

class EBook : public AbstractMedia, public Utilities::IMediaLength {

public:

    // === COSTANTI STATICHE ===

    static const unsigned int MIN_EBOOK_LENGTH;
    static const unsigned int MAX_EBOOK_LENGTH;
    static const unsigned int VALID_ISBN_LENGTH;
    static const std::vector<std::string> EBOOK_FORMATS;

    static const float defaultEBookSize;
    static const std::string defaultEBookFormat;
    static const std::string defaultEBookAuthor;
    static const std::string defaultEBookPublisher;
    static const unsigned int defaultEBookReleaseYear;
    static const std::string defaultEBookISBN;
    static const unsigned int defaultEBookLength;
    static const std::string defaultEBookCategory;
    static const std::string defaultEBookLanguage;


    // === COSTRUTTORI, ASSEGNAZIONE ===

    /**
     * @brief EBook : costruttore di default, inizializza i campi dati con valori di default */
    EBook();

    /** @brief EBook : costruttore di copia */
    EBook(const EBook& ebook);

    /** @brief operator= : operatore di assegnazione*/
    EBook& operator=(const EBook& ebook);


    // === GETTER ===

    const std::string& getAuthor() const;
    const std::string& getPublisher() const;
    unsigned int getReleaseYear() const;
    const std::string& getISBN() const;
    const std::string& getCategory() const;
    const std::string& getLanguage() const;
    const std::string& getCoverImagePath() const;


    // === SETTER ===

    void setAuthor(const std::string& auth);
    void setPublisher(const std::string& pbl);
    void setReleaseYear(unsigned int year);
    void setISBN(const std::string& isbn);
    void setCategory(const std::string& ctg);
    void setLanguage(const std::string& lang);
    void setCoverImagePath(const std::string& cp);
    void setImages(bool img);


    // === METODI SPECIFICI EBook ===

    /** @brief hasImages : restituisce true se il media EBook ha immagini ('hasImages' vale true), false altrimenti */
    bool hasImages() const;

    /**
     * @brief validISBN : verifica se il media EBook ha un ISBN valido, usando il checksum ISBN-13
     * @return bool : true se l'ISBN e' valido, false altrimenti
     * @details Ho fatto riferimento al noto algoritmo checksum ISBN-13
     */
    bool validISBN() const;

    /** @brief hasCoverPath : restituisce true se il media EBook ha un'immagine di copertina settata (true se 'coverImage' non e' vuota) */
    bool hasCoverPath() const;


    // === RIDEFINIZIONE VIRTUALI PURI IMediaLength ===

    /** @brief measuredInPages : ridefinizione virtuale puro ereditato da Utilities::IMediaLength, ritorna sempre true */
    bool measuredInPages() const override;

    /** @brief getMediaLength : ridefinizione virtuale puro ereditato da Utilities::IMediaLength, restituisce la durata espressa come numero di pagine */
    unsigned int getMediaLength() const override;

    /** @brief setMediaLength : ridefinizione virtuale puro ereditato da Utilities::IMediaLength, imposta la durata espressa per numero di pagine */
    void setMediaLength(unsigned int length) override;


    // === RIDEFINIZIONE VIRTUALI PURI AbstractMedia ===

    /** @brief hasLength : ridefinizione virtuale puro ereditato da AbstractMedia, ritorna sempre true */
    bool hasLength() const override;

    /** @brief hasResolution : ridefinizione virtuale puro ereditato da AbstractMedia, ritorna sempre false */
    bool hasResolution() const override;


    // === RIDEFINIZIONE VIRTUALI PURI AbstractFile ===

    /**
     * @brief clone : ridefinizione del metodo di clonazione ereditato da AbstractFile
     * @return EBook* : puntatore a EBook, tipo di ritorno covariante
     */
    EBook* clone() const override;

    /** @brief accept : ridefinizione virtuale puro ereditato da AbstractFile per l'implementazione non-const del design pattern Visitor per il tipo EBook */
    void accept(Visitors::IVisitor& visitor) override;

    /** @brief accept : ridefinizione virtuale puro ereditato da AbstractFile per l'implementazione const del design pattern Visitor per il tipo EBook */
    void accept(Visitors::IConstVisitor& visitor) const override;

    /**
     * @brief displayStringType : ridefinizione virtuale puro ereditato da AbstractFile
     * @return std::string : stringa usata solamente per stampare/mostrare il tipo del media (e non come sostituzione al polimorfismo)
     */
    std::string displayStringType() const override;


    // === PERSISTENZA DATI JSON ===

    /** @brief toJson : ridefinizione virtuale puro ereditato da AbstractMedia per la persistenza dei dati in fromato JSON, in modo specifico al tipo EBook (commentato nella definizione) */
    QJsonObject toJson() const override;

    /** @brief fromJson :  ridefinizione virtuale puro ereditato da AbstractMedia per la persistenza dei dati, in modo specifico al tipo EBook (commentato nella definizione) */
    void fromJson(const QJsonObject& obj) override;


private:

    // == CAMPI DATI ===

    std::string author;          // autore del media ebook
    std::string publisher;       // casa editrice del media ebook
    unsigned int releaseYear;    // anno di pubblicazione del media ebook
    std::string ISBN;            // codice ISBN (da 13 cifre) del media ebook
    unsigned int lengthInPages;  // numero di pagine del media ebook
    std::string category;        // categoria del media ebook
    std::string language;        // lingua testo del media ebook
    std::string coverImage;      // path alla copertina del media ebook (se presente)
    bool images;                 // presenza/assenza immagini all'interno del media ebook

};

}
}

#endif // MODEL_MEDIA_EBOOK_H

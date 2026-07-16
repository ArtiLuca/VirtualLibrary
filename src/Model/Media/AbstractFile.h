#ifndef MODEL_MEDIA_ABSTRACT_FILE_H
#define MODEL_MEDIA_ABSTRACT_FILE_H

#include <string>

/** @brief AbstractFile
 *
 *  AbstractFile e' la classe base astratta per tutti i media.
 *  Contiene gli attributi ritenuti comuni a tutti i media, come ad esempio l'identificatore (ID), il path e la dimensione (in MB).
 *
 *  I valori di default dei campi dati sono salvati in delle variabili statiche, rese pubbliche in quanto necessarie ad altri parti del programma.
 *  AbstractFile dispone di un costruttore di default, un costruttore di copia, un distruttore virtuale, ridefinizione dell'operatore di assegnazione
 *  e vari getter/setter per i campi dati privati.
 *
 *  L'identificatore di ciascun media e' considerato univoco e immutabile per la sessione corrente e viene salvato in un contatore statico 'uniqueIDCounter'
 *  che viene incrementato ad ogni invocazione del costruttore di AbstractFile. Inoltre, e' possible "settarlo" tramite il metodo statico 'setCurrentUniqueID'.
 *  Questo torna utile, ad esempio, per impostarlo in base all'ultimo valore usato in una esecuzione precedente della libreria virtuale.
 *
 *  NOTA: L'identificatore del media e' considerato univoco per ogni sessione di esecuzione. Quando viene salvato su file un media, non viene salvato il suo
 *  identificatore. Quindi, quando viene nuovamente caricato da file il media in una nuova sessione, gli viene dato un nuovo identificatore pur avendo gli
 *  attributi immutati.
 *
 *  AbstractFile e' astratta in quanto dispone dei due metodi virtuali 'accept' per l'implementazione (const e non-const) del design pattern visitor
 *  e del metodo virtuale puro 'clone' per la clonazione dei media.
 *
 */


// foward-declared
namespace Model::Visitors {
class IVisitor;
class IConstVisitor;
}


namespace Model {
namespace Media {

class AbstractFile {

public:

    // === COSTANTI STATICHE ===

    static const unsigned int INVALID_UNIQUE_ID;
    static const float MIN_FILE_SIZE;
    static const float MAX_FILE_SIZE;
    static const std::string defaultPath;
    static const float defaultSize;

    static unsigned int uniqueIDCounter;


    // === DISTRUTTORE ===

    /** @brief ~AbstractFile : distruttore virtuale di AbstractFile */
    virtual ~AbstractFile() = default;


    // === GETTER ===

    unsigned int getUniqueID() const;
    const std::string& getFilePath() const;
    float getFileSize() const;


    // === SETTER ===

    void setFilePath(const std::string& path);
    void setFileSize(float size);

    /**
     * @brief setCurrentUniqueID : metodo statico per impostare identificatore univoco
     * @param currID : identificatore univoco da impostare
     */
    static void setCurrentUniqueID(unsigned int currID);


    // === METODI VIRTUALI PURI ===

    /**
     * @brief clone : metodo virtuale puro per la clonazione dei media (costruttore di copia polimorfo)
     * @return AbstractFile* : puntatore alla base polimorfa AbstractFile
     */
    virtual AbstractFile* clone() const = 0;

    /** @brief accept : metodo virtuale puro per implementare design pattern "Visitor", versione non-const */
    virtual void accept(Visitors::IVisitor& visitor) = 0;

    /** @brief accept : metodo virtuale puro per implementare design pattern "Visitor", versione const */
    virtual void accept(Visitors::IConstVisitor& visitor) const = 0;


protected:

    // === CAMPI DATI ===

    const unsigned int uniqueID; // identificatore univoco, immutabile per la sessione
    std::string filePath;        // path
    float fileSize;              // dimensione (in MB)


    // === COSTRUTTORI, ASSEGNAZIONE ===

    /** @brief AbstractFile : costruttore, imposta campi dati con valori di default */
    AbstractFile();

    /**
     * @brief AbstractFile : costruttore parametrizzato
     * @param filePath : path
     * @param size : dimensione (in MB)
     */
    AbstractFile(const std::string& path, float size);

    /** @brief AbstractFile : costruttore di copia */
    AbstractFile(const AbstractFile& file);

    /** @brief operator= : operatore assegnazione, ignora il campo 'uniqueID' in quanto immutabile */
    AbstractFile& operator=(const AbstractFile& file);


    /**
     * @brief incrementUniqueIDCounter : incrementa il contatore statico 'uniqueIDCounter'
     * @return unsigned int : contatore dell'identificatore univoco, incrementato di 1
     */
    static unsigned int incrementUniqueIDCounter();
};

}
}

#endif // MODEL_MEDIA_ABSTRACT_FILE_H

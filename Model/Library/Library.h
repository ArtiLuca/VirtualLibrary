#ifndef MODEL_LIBRARY_H
#define MODEL_LIBRARY_H

#include "Model/Media/AbstractMedia.h"
#include "Model/Loggers/IMediaLogger.h"
#include "Model/Loggers/LogLevel.h"
#include "Model/Library/SearchQuery.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>

/** @brief Library
 *
 *  La classe Library rappresenta la classe contenitrice dei media in libreria, che vengono memorizzati in un vettore di smart pointer del tipo std::shared_ptr<AbstractMedia>.
 *
 *  Library definisce le operazioni per l'inserimento, la rimozione, la modifica, lo scoring e il fetch dei media in base al loro identificatore univoco.
 *
 *  Il costruttore di Library implementa un sistema di logging per ogni operazioni significativa effettuata nella libreria, tramite un logger concreto (derivato da IMediaLogger).
 *  Questo logger concreto viene associato alla libreria nel costruttore di Library (che ha valore di default 'nullptr') e vengono definiti metodi in Library per associare un nuovo
 *  logger concreto, effettuare il logging, impostare un grado di severita' per il Logging (definito nel enum LogLevel), e getter per il logger/severita'.
 *  Il logger concreto associato e la corrispondente severita' sono salvati come campi dati privati di Library.
 *
 *  Inoltre, library dispone dei metodi per implementare la persitenza dei dati in formato JSON, utlizzando i metodi virtuali puri 'toJson' e 'fromJson' di AbstractMedia, che vengono
 *  poi ridefiniti in modo specifico per ciasun media concreto.
 *  Vengono inoltre definiti i metodi 'saveToFile' e 'loadFromFile' per eseguire il salvataggio/caricamento in formato JSON da un file ad un dato cammino (tipicamente preso da user input nella UI).
 *  Library fronisce anche le basi per le operazioni piu' complesse, ad esempio la ricerca avanzata utilizzando parametri di ricerca, per poi essere estesa nella classe Manager.
 *
 */

namespace Model {
namespace Library {


class Library {

public:

    // === COSTRUTTORE ===

    /**
     * @brief Library : costruttore, imposta il logger della libreria (opzionale)
     * @param logger : logger concreto derivato da IMediaLogger da associare alla libreria (con valore di default 'nullptr')
     */
    explicit Library(Loggers::IMediaLogger* log = nullptr);


    // === LOGGER ===

    /**
     * @brief setLibraryLogger : setter per il logger della libreria
     * @param log : logger concreto derivato da IMediaLogger da associare alla libreria
     */
    void setLibraryLogger(Loggers::IMediaLogger* log);

    /**
     * @brief setLibraryLogLevel : imposta il livello di severita' del logging
     * @param lvl : livello di severita' (definito in Loggers::LogLevel)
     */
    void setLibraryLogLevel(Loggers::LogLevel lvl);

    /**
     * @brief getLibraryLogLevel : restituisce il livello di severita' del logging
     * @return LogLevel : livello di severita' attuale
     */
    Loggers::LogLevel getLibraryLogLevel() const;

    /**
     * @brief getLibraryLogger : restituisce il logger associato alla libreria
     * @return Loggers::IMediaLogger* : puntatore al logger associato
     */
    Loggers::IMediaLogger* getLibraryLogger() const;

    /**
     * @brief logLibraryMessage : effettua il logging di un messaggio se la libreria ha un logger concreto impostato
     * @param msg : messaggio da "loggare"
     * @param lvl : livello di severita' del logging (definito in Loggers::LogLevel)
     */
    void logLibraryMessage(const std::string& msg, Loggers::LogLevel lvl = Loggers::LogLevel::Info) const;


    // === HELPER ===

    /**
     * @brief libraryIsEmpty : verifica se la libreria e' vuota
     * @return bool : true se la libreria e' vuota, false altrimenti
     */
    bool libraryIsEmpty() const;

    /**
     * @brief getLibrarySize : restituisce il numero di media attualmente in libreria
     * @return unsigned int : numero di media nella libreria
     */
    unsigned int getLibrarySize() const;

    /**
     * @brief getAllLibraryMedia : restituisce tutti i media attualmente presenti nella libreria
     * @return const std::vector& : vettore di smart pointer di tipo std::shared_ptr ai media attualmente in libreria
     */
    const std::vector<std::shared_ptr<Media::AbstractMedia>>& getAllLibraryMedia() const;


    // === INSERIMENTO ===

    /**
     * @brief insertLibraryMedia : inserisce un media gia' esistente nella libreria, in coda
     * @param media : smart pointer al media da aggiungere
     */
    void insertLibraryMedia(const std::shared_ptr<Media::AbstractMedia> media);


    // === RIMOZIONE ===

    /**
     * @brief removeLibraryMedia : rimuove un media in base al suo identificatore univoco
     * @param id : identificatore univoco del media da rimuovere
     * @return bool : true se il media viene rimosso con successo, false altrimenti
     */
    bool removeLibraryMediaByID(unsigned int id);

    /**
     * @brief clearLibrary : rimuove tutti i media della libreria
     */
    void clearLibrary();


    // === MODIFICA ===

    /**
     * @brief editLibraryMedia : modifica un media in base al suo identificatore univoco, usando il visitor concreto MediaEditor
     * @param id : identificatore univoco del media da modificare
     * @param mediaEdits : mappa delle modifiche da effettuare
     * @throws MediaValidatorException se la modifica non ha successo
     * @return bool : true se il media viene modificato con successo, false altrimenti
     */
    bool editLibraryMediaByID(unsigned int id, const std::unordered_map<std::string, std::string>& mediaEdits);


    // === VISUALIZZAZIONE (Utilizzati per debugging) ===

    /**
     * @brief viewConciseMediaInfo : restituisce informazioni sintetiche (concise) su un media tramite il visitor ConcisePrinter
     * @param id : identificatore univoco del media
     * @return std::string : informazioni base (concise) del media
     */
    std::string viewConciseMediaInfoByID(unsigned int id) const;

    /**
     * @brief viewDetailedMediaInfo :  restituisce informazioni dettagliate su un media tramite il visitor DetailedPrinter
     * @param id : identificatore univoco del media
     * @return std::string : informazioni dettagliate del media
     */
    std::string viewDetailedMediaInfoByID(unsigned int id) const;

    /**
     * @brief viewMediaInfo : restituisce informazioni su un media, in base al livello di dettaglio richiesto, tramite il visitor corrispondente
     * @param id : identificatore univoco del media
     * @param detail : true per info dettagliate, false per info sintetiche (concise)
     * @return std::string  : informazioni del media
     */
    std::string viewMediaInfoByID(unsigned int id, bool detail = false) const;

    /**
     * @brief viewAllLibraryMedia : restituisce una lista di tutti i media attualmente nella libreria in formato sintetico (visitor ConcisePrinter)
     * @return std::string : lista dei media attualmente in libreria
     */
    std::string viewAllLibraryMedia() const;


    // ===  RICERCA ===

    /**
     * @brief searchLibrary : effettua una ricerca con filtri (tramite lo struct SearchQuery) sui media attualmente in libreria
     * @param query : filtri con cui effettuare la ricerca
     * @return std::vector : vettore contenente gli identificatori univoci dei media trovati nella ricerca (puo' essere vuoto)
     */
    std::vector<unsigned int> searchLibrary(const SearchQuery& query) const;


    // === FETCH ===

    /**
     * @brief getMediaByID : restituisce un media in base al suo identificatore univoco
     * @param id : identificatore univoco del media
     * @return std::shared_ptr<AbstractMedia> : smart pointer al media trovato, altrimenti nullptr'
     */
    std::shared_ptr<Media::AbstractMedia> getMediaByID(unsigned int id) const;


    // === SCORING VISITOR ===

    /**
     * @brief getMediaScoreValueByID : restituisce lo score numerico del media in base al suo identificatore univoco
     * @param id : identificatore univoco del media
     * @return float : score numerico (0-100)
     */
    float getMediaScoreValueByID(unsigned int id) const;

    /**
     * @brief getMediaScoreLabelByID : restituisce il label qualitativo per lo score di un media in base al suo identificatore univoco
     * @param id : identificatore univoco del media
     * @return std::string : label qualitativo per lo score
     */
    std::string getMediaScoreLabelByID(unsigned int id) const;

    /**
     * @brief getMediaScoreInfoByID : restituisce informazioni sul calcolo per lo score di un media in base al suo identificatore univoco
     * @param id : identificatore univoco del media
     * @return std::string : stringa con informazioni sul calcolo per lo score
     */
    std::string getMediaScoreInfoByID(unsigned int id) const;


    // === JSON ===

    /**
     * @brief toJson : serializza i media della libreria in un oggetto JSON
     * @return QJSonObject : oggetto JSON rappresentante tutti i media attualmente presenti in libreria (salvati come un QJsonArray)
     */
    QJsonObject toJson() const;

    /**
     * @brief fromJson : riempie la libreria leggendo i media da un oggetto JSON, ricostruendo ciascun media utilizzando la classe MediaFactory
     * @param obj : oggetto QJsonObject con la rappresentazione serializzata dei media della libreria
     * @details la libreria viene "svuotata" dei suoi contenuti attuali prima della lettura
     */
    void fromJson(const QJsonObject& obj);

    /**
     * @brief saveToFile : salva i media della libreria in formato JSON su file
     * @param filename : file su cui scrivere i dati dei media in libreria
     * @return bool : true se il salvataggio ha successo, false altrimenti
     */
    bool saveToFile(const QString& filename) const;

    /**
     * @brief loadFromFile : carica i media della libreria da un file JSON, ricostruendo i media tramite il metodo 'fromJson'
     * @param filename : file da cui leggere i media da caricare in liberia
     * @return bool : true se la lettura ha successo, false altrimenti
     */
    bool loadFromFile(const QString& filename);


private:

    std::vector<std::shared_ptr<Media::AbstractMedia>> libraryMedia;             //  media della libreria
    Loggers::IMediaLogger* libraryLogger;                                        // logger associato
    Loggers::LogLevel logLevel;                                                  // livello severita' del logging

    // === CHECK DUPLICATE ID ===   added 4/6/25

    /**
     * @brief checkDuplicateID : verifica se la libreria contiene un dato identificatore, per evirare il caso di identificatori duplicati
     * @param id : identificatore di cui fare la verifica
     * @return bool : true se l'identificatore univoco viene trovato, false altrimenti
     */
    bool checkDuplicateID(unsigned int id) const;
};

}
}

#endif // MODEL_LIBRARY_H

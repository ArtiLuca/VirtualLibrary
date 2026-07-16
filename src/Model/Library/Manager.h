#ifndef MODEL_LIBRARY_MANAGER_H
#define MODEL_LIBRARY_MANAGER_H

#include "Model/Library/Library.h"
#include "Model/Library/Command/IAbstractCommand.h"
#include "Model/Loggers/IMediaLogger.h"
#include "Model/Loggers/LogLevel.h"
#include "Model/Library/SearchQuery.h"
#include "Model/Media/AbstractMedia.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include <QString>

/** @brief
 *
 *  La classe Manager rappresenta un'ulteriore astrazione della classe Library.
 *  Viene utilizzata come "ponte" tra il modello logico e la vista, comunicando con il Controller.
 *
 *  Contiene come campi dati privati un'istanza di Library e un contatore per l'indice corrente.
 *  Inoltre, contiene come campi dati privati due vettori 'undoCommands' e 'redoCommands' di smart pointer del tipo std::shared_ptr<IAbstractCommand> per implementare il design pattern Command
 *  e due stringhe 'lastUndoDescription' e 'lastRedoDescription' per contenere informazioni sull'ultimo comando eseguito oppure ripristinato.
 *
 *  Manager estende le funzionalita' di Library e aggiunge altre nuove. Le funzionalita' base di Library (inserimento, rimozione, modifica, fetch, caricamento/salvataggio) vengono estese in Manager in modo da agire
 *  in base all'indice corrente. Manager aggiunge funzionalita' per la gestione dell'indice corrente, la creazione di nuovi media e per la ricerca dei media utilizzando uno o piu' parametri di ricerca.
 *  La creazione dei media utilizza la classe MediaFactory, che implementa il design pattern Factory, per la creazione dei nuovi media, mentre l'operazione di ricerca utilizza uno struct ausiliario SearchQuery assieme
 *  al visitor concreto SearchVisitor per implementare la ricerca 'case-insensitive' dei media utilizzando uno o piu' filtri di ricerca.
 *
 */

namespace Model {
namespace Library {

class Manager {

public:

    // === COSTRUTTORE ===

    /**
     * @brief Manager : costruttore, imposta l'indice corrente a 0, e inizializza la libreria, associandogli un logger (se fornito)
     * @param log : puntatore a logger concreto (che ha valore di default 'nullptr')
     */
    explicit Manager(Loggers::IMediaLogger* log = nullptr);


    // === GETTER/SETTER/GENERALE ===

    /**
     * @brief isEmpty : verifica se la libreria gestita dal manager e' vuota
     * @return bool : true se non ci sono media nella libreria, false altrimenti
     */
    bool isEmpty() const;

    /**
     * @brief getSize : restituisce il numero di media attualemente in libreria
     * @return unsigned int : numero di media attualmente in libreria
     */
    unsigned int getSize() const;

    /**
     * @brief isValidIndex : verifica se un dato indice e' valido nella libreria
     * @param ind : indice da verificare
     * @return bool : true se l'indice e' valido, false altrimenti
     */
    bool isValidIndex(unsigned int ind) const;

    /**
     * @brief getCurrentIndex : restituisce l'indice corrente della libreria
     * @return unsigned int : indice corrente
     */
    unsigned int getCurrentIndex() const;

    /**
     * @brief setCurrentIndex : imposta l'indice corrente ad un dato indice
     * @param ind : nuovo indice da impostare
     */
    void setCurrentIndex(unsigned int ind);

    /**
     * @brief getLastUndoInfo : restituisce informazioni sull'ultima operazione Undo effettuata
     * @return const std::string& : informazioni ultima operazione Undo
     */
    const std::string& getLastUndoInfo() const;

    /**
     * @brief getLastRedoInfo : restituisce informazioni sull'ultima operazione Redo effettuata
     * @return const std::string& : informazioni ultima operazione Redo
     */
    const std::string& getLastRedoInfo() const;


    // === OPERAZIONI INDICE ===

    /**
     * @brief goToNextIndex : sposta l'indice corrente al media successivo, se possibile
     * @return bool : true se successo, false altrimenti
     */
    bool goToNextIndex();

    /**
     * @brief goToPreviousIndex : sposta l'indice corrente al media precedente, se possibile
     * @return bool : true se successo, false altrimenti
     */
    bool goToPreviousIndex();

    /**
     * @brief goToFirstIndex : sposta l'indice corrente al primo elemento della libreria
     * @return bool : true se successo, false altrimenti
     */
    bool goToFirstIndex();

    /**
     * @brief goToLastIndex : sposta l'indice corrente all'ultimo elemento della libreria
     * @return bool : true se successo, false altrimenti
     */
    bool goToLastIndex();

    /**
     * @brief getMediaIndexByID : restituisce l'indice di un media in libreria, in base al suo identificatore univoco
     * @param id : identificatore univoco del media
     * @return unsigned int : indice del media trovato, altrimenti il numero di media attualmente in libreria
     */
    unsigned int getMediaIndexByID(unsigned int id) const;


    // === FETCH ===

    /**
     * @brief getMediaAtIndex : restituisce un smart pointer ad un media, in base suo indice nella libreria
     * @param ind : indice del media
     * @return std::shared_ptr<AbstractMedia> : smart pointer al media, oppure nullptr se l'indice non e' valido
     */
    std::shared_ptr<Media::AbstractMedia> getMediaAtIndex(unsigned int ind) const;

    /**
     * @brief getCurrentMedia : restituisce smart pointer al media dell'indice corrente
     * @return std::shared_ptr<AbstractMedia> : smart pointer al media corrente, oppure nullptr se la libreria e' vuota
     */
    std::shared_ptr<Media::AbstractMedia> getCurrentMedia() const;

    /**
     * @brief getMediaByID : restituisce smart pointer ad un media, in base al suo identificatore univoco
     * @param id : identificatore univoco del media
     * @return std::shared_ptr<AbstractMedia> : smart pointer al media, oppure nullptr se il media non viene trovato
     */
    std::shared_ptr<Media::AbstractMedia> getMediaByID(unsigned int id) const;


    // === INSERIMENTO ===

    /**
     * @brief insertMediaAtIndex : inserisce media (gia' esistente) in una posizione arbitraria della libreria
     * @param media : smart pointer al media da inserire
     * @param ind : indice in cui inserire il media
     * @return bool : true se l'inserimento ha avuto successo, false altrimenti
     */
    bool insertMediaAtIndex(const std::shared_ptr<Media::AbstractMedia>& media, unsigned int ind);

    /**
     * @brief insertMediaAtCurrentIndex : inserisce media (gia' esistente) all'indice corrente della libreria
     * @param media : smart pointer al media da inserire
     * @return bool : true se l'inserimento ha avuto successo, false altrimenti
     */
    bool insertMediaAtCurrentIndex(const std::shared_ptr<Media::AbstractMedia>& media);


    // === RIMOZIONE ===

    /**
     * @brief removeMediaAtIndex : rimuove media da una posizione arbitraria della liberia
     * @param ind : indice del media da rimuovere
     * @return bool : true se la rimozione ha avuto successo, false altrimenti
     */
    bool removeMediaAtIndex(unsigned int ind);

    /**
     * @brief removeMediaAtCurrentIndex : rimuove il media all'indice corrente
     * @return bool : true se la rimozione ha avuto successo, false altrimenti
     */
    bool removeMediaAtCurrentIndex();

    /**
     * @brief removeAllMedia : rimuove tutti i media dalla libreria, chiama 'clearCommandOperations' e imposta l'indice corrente a 0
     * @return bool : true se l'operazione ha successo, false altrimenti
     */
    bool removeAllMedia();


    // === MODIFICA ===

    /**
     * @brief editMediaAtIndex : modifica media in posizione arbitraria della libreria
     * @param ind : indice del media da modificare
     * @param mediaEdits : mappa delle modifiche da applicare al media
     * @return bool : true se la modifica ha avuto successo, false altrimenti
     * @throws MediaValidatorException se la modifica non e' valida
     */
    bool editMediaAtIndex(unsigned int ind, const std::unordered_map<std::string, std::string>& mediaEdits);

    /**
     * @brief editMediaAtCurrentIndex : modifica il media all'indice corrente
     * @param mediaEdits : mappa di modifiche da applicare al media
     * @return bool : true se la modifica ha avuto successo, false altrimenti
     * @throws MediaValidatorException se la modifica non era valida
     */
    bool editMediaAtCurrentIndex(const std::unordered_map<std::string, std::string>& mediaEdits);


    // === CREAZIONE ===

    /**
     * @brief createNewMedia : crea un nuovo media tramite MediaFactory e lo inserisce all'indice corrente, se valido
     * @param type : tipo del media creare
     * @param attr : mappa con attributi del nuovo media
     * @return std::shared_ptr<AbstractMedia> : smart pointer al nuovo media, oppure 'nullptr' in caso di errore in creazione
     * @throws MediaValidatorException se la creazione o l'inserimento falliscono
     */
    std::shared_ptr<Media::AbstractMedia> createNewMedia(const std::string& type, const std::unordered_map<std::string, std::string>& attr);


    // === RICERCA ===

    /**
     * @brief searchMedia : ricerca dei media in base a filtri (impostati da SearchQuery)
     * @param query : filtri da applicare nell'operazione di ricerca
     * @return std::vector<unsigned int> : vettore contenente gli identificatori univoci dei media trovati
     */
    std::vector<unsigned int> searchMedia(const SearchQuery& query) const;

    /**
     * @brief getSearchResultIndexesByID : restituisce i corrispondenti indici in libreria a partire dai identificatori dei media trovati nella ricerca
     * @param mediaIDs : vettore contenente identificatori dei media trovati
     * @return std::vector<unsigned ind> : indici dei media nella libreria
     */
    std::vector<unsigned int> getSearchResultIndexesByID(const std::vector<unsigned int>& mediaIDs) const;


    // === JSON ===

    /**
     * @brief saveContentsToFile : salva la i contenuti correnti della libreria su file in formato JSON
     * @param filename : path del file a cui salvare i contenuti
     * @return bool : true se l'operazione ha successo, false altrimenti
     */
    bool saveContentsToFile(const QString& filename) const;

    /**
     * @brief loadContentsFromFile : carica media nella libreria da file in formato JSON
     * @param filename : path del file da cui caricare
     * @return  bool : true se l'operazione ha successo, false altrimenti
     */
    bool loadContentsFromFile(const QString& filename);


    // === SCORING ===

    /**
     * @brief getMediaScoreAtIndex : restituisce lo score numerico del media ad un dato indice (utilizza Visitors::ScoreVisitor)
     * @param ind : indice del media
     * @return float : score numerico del media
     */
    float getMediaScoreAtIndex(unsigned int ind) const;

    /**
     * @brief getMediaScoreLabelAtIndex : restituisce label qualitativa
     * @param ind : indice del media
     * @return std::string : label qualitativa basato su score numerio del media
     */
    std::string getMediaScoreLabelAtIndex(unsigned int ind) const;

    /**
     * @brief getMediaScoreInfoAtIndex : restituisce info aggiuntive sul calcolo dello score per un media ad un dato indice
     * @param ind : indice del media
     * @return std::string : info aggiuntive su calcolo score del media
     */
    std::string getMediaScoreInfoAtIndex(unsigned int ind) const;


    // === COMMAND ===

    /**
     * @brief executeCommand : esegue un command (operazione) e lo memorizza nei stack ('undoStack' o 'redoStack')
     * @param command : smart pointer del tipo std::shared_ptr al command da eseguire
     */
    void executeCommand(const std::shared_ptr<Command::IAbstractCommand>& cmd);

    /**
     * @brief undoCommand : annulla l'ultima operazione eseguita (se presente nello stack 'undoStack')
     */
    void undoCommand();

    /**
     * @brief redoCommand : ripristina l'ultima operazione annullata (se presente nello stack 'redoStack')
     */
    void redoCommand();

    /**
     * @brief canUndoCommand : verifica se e' possibile annullare l'ultima operazione ('undo')
     * @return bool : true se possibile fare 'undo', false altrimenti
     */
    bool canUndoCommand() const;

    /**
     * @brief canRedoCommand : verifica se e' possibile ripetere l'ultima operazione annullata ('redo')
     * @return bool : true se possibile fare 'redo', false altrimenti
     */
    bool canRedoCommand() const;

    /**
     * @brief clearCommandStack : svuota entrambi gli stack delle operazioni Undo e Redo
     */
    void clearCommandOperations();


    // == LOGGING ===

    /**
     * @brief setLibraryLogger : associa un logger alla libreria
     * @param newLogger : puntatore al logger da associare alla libreria
     */
    void setLibraryLogger(Model::Loggers::IMediaLogger* newLogger);

    /**
     * @brief getLogLevel : restituisce il livello di severita' logging della liberia
     * @return LogLevel : livello di severita' logging (definito in Loggers::LogLevel)
     */
    Model::Loggers::LogLevel getLogLevel() const;

    /**
     * @brief setLogLevel : imposta il livello di severita' logging della libreria
     * @param level : livello di severita' da impostare (definito in Loggers::LogLevel)
     */
    void setLogLevel(Model::Loggers::LogLevel level);

private:

    Library mediaLibrary;                                                   // libreria dei media
    unsigned int currentIndex;                                              // indice di media corrente
    std::vector<std::shared_ptr<Command::IAbstractCommand>> undoCommands;   // vettore di smart pointer di command Undo
    std::vector<std::shared_ptr<Command::IAbstractCommand>> redoCommands;   // vettore di smart pointer di command Redo
    std::string lastUndoDescription;                                        // dettagli ultimo Undo
    std::string lastRedoDescription;                                        // dettagli ultimo Redo
};

}
}


#endif // MODEL_LIBRARY_MANAGER_H


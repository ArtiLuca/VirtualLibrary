#ifndef CONTROLLER_CONTROLLER_H
#define CONTROLLER_CONTROLLER_H

#include "Model/Library/Manager.h"
#include "Model/Library/SearchQuery.h"

#include <QObject>
#include <QString>
#include <QMap>

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

/** @brief Controller
 *
 *  Controller agisce da "ponte" tra il modello logico e la vista, coordinando la logica relativa alla loro comunicazione.
 *
 *  Estende i metodi del manager in modo da facilitare l'implementazione delle operazioni essenziali (visualizzazione, inserimento, rimozione, creazione, ricerca e scoring).
 *  Utilizza il sistema di segnali e slot di Qt in modo da poter ricevere richieste fatte dallo user nella vista, delegare l'operazione al modello e poi notificare la vista
 *  con il risultato o azione da eseguire.
 *
 *  Per avere un corretto funzionamento del sistema di segnali slot dovuto creare due metodi helper per la conversione tra QMap<QString,QString> e std::::unordered_map<std::string,std::string>.
 *
 */

namespace Controller {

class Controller : public QObject {

    Q_OBJECT

public:

    // === COSTRUTTORE ===

    /**
     * @brief Controller : costruttore, imposta campi privati
     * @param manager : puntatore a Manager
     * @param parent : parent widget
     * @throws runtime_error se il manager e' 'nullptr'
     */
    explicit Controller(Model::Library::Manager* manager, QObject* parent = nullptr);


    // === GENERALE ===

    /**
     * @brief managerIsEmpty : verifica se il manager e' vuoto
     * @return bool : true se il manager non contiene media, false altrimenti
     */
    bool managerIsEmpty() const;

    /**
     * @brief getManagerSize : restituisce il numero attuale di media gestiti dal manager
     * @return int : numero attuale di media gestiti dal manager, 0 altrimenti
     */
    int getManagerSize() const;

    /**
     * @brief initializeCommandSignals : manda segnali 'undoPossible' e 'redoPossible' dopo avere impostato il Controller nella Window
     */
    void initializeCommandSignals();


    // === OPERAZIONI INDICE ===

    /**
     * @brief getCurrentManagerIndex : restituisce l'indice corrente del manager
     * @return int : indice corrente
     */
    int getCurrentManagerIndex() const;

    /**
     * @brief setCurrentManagerIndex : imposta l'indice corrente del manager
     * @param ind : nuovo indice da impostare
     */
    void setCurrentManagerIndex(unsigned int ind);

    /**
     * @brief validIndex : verifica se un dato indice e' valido
     * @param ind : indice da verificare
     * @return bool : true se valido, false altrimenti
     */
    bool validIndex(unsigned int ind) const;

    /**
     * @brief getNextIndex : restituisce l'indice successivo, se possibile
     * @return int : indice successivo o -1 se non possibile
     */
    int getNextIndex();

    /**
     * @brief getPreviousIndex : restituisce l'indice precedente, se possibile
     * @return int : indice precedente o -1 se non possibile
     */
    int getPreviousIndex();

    /**
     * @brief getFirstIndex : restituisce il primo indice (cioe' 0)
     * @return int : primo indice
     */
    int getFirstIndex();

    /**
     * @brief getLastIndex : restituisce l'ultimo indice disponibile
     * @return int : ultimo indice o -1 se la lista e' vuota
     */
    int getLastIndex();

    /**
     * @brief getIndexByMediaID : restituisce l'indice di un media in base al suo identificatore univoco
     * @param mediaID : identificatore univoco del media
     * @return int : indice del media trovato, -1 altrimenti
     */
    int getIndexByMediaID(unsigned int mediaID);


    // ===  FETCH ===

    /**
     * @brief getMediaAtIndex : restituisce smart pointer ad un media in base ad un dato indice
     * @param ind : indice del media
     * @return std::shared_ptr<AbstractMedia> : smart pointer al media trovato, nullptr altrimenti
     */
    std::shared_ptr<Model::Media::AbstractMedia> getMediaAtIndex(unsigned int ind) const;

    /**
     * @brief getMediaByID : restituisce smart pointer ad un media in base al suo identificatore univoco
     * @param mediaID : identificatore univoco del media
     * @return std::shared_ptr<AbstractMedia> : smart pointer al media trovato, nullptr altrimenti
     */
    std::shared_ptr<Model::Media::AbstractMedia> getMediaByID(unsigned int mediaID) const;

    /**
     * @brief getCurrentMedia : restituisce smart pointer al media all'indice corrente
     * @return std::shared_ptr<AbstractMedia> : smart pointer al media trovato, nullptr altrimenti
     */
    std::shared_ptr<Model::Media::AbstractMedia> getCurrentMedia() const;


    // === RICERCA ===

    /**
     * @brief getSearchResultIndexes : restituisce vettore di indici corrispondenti, partendo dai loro identificatori univoci
     * @param mediaIDs : vettore di identificatori univoci
     * @return std::vector<unsigned int> : vettore di indici corrispondenti
     */
    std::vector<unsigned int> getSearchResultIndexes(const std::vector<unsigned int>& mediaIDs) const;

    // === SCORING ===

    /**
     * @brief getScoreValueAtIndex : restituisce score numerico di un media ad un dato indice
     * @param ind : indice del media
     * @return float : score numerico
     */
    float getScoreValueAtIndex(unsigned int ind) const;

    /**
     * @brief getScoreLabelAtIndex : restituisce label qualitativo dello score di un media ad un dato indice
     * @param ind : indice del media
     * @return QString : label qualitativo
     */
    QString getScoreLabelAtIndex(unsigned int ind) const;

    /**
     * @brief getScoreInfoAtIndex : restituisce informazioni calcolo score di un media ad un dato indice
     * @param ind : indice del media
     * @return QString : info calcolo score
     */
    QString getScoreInfoAtIndex(unsigned int ind) const;


    // === HELPER TIPI QT ===

    /**
     * @brief QMapToUnorderedMap : helper per conversione QMap a std::unordered_map
     * @param attributeMapQt : mappa di attributi che utilizza elementi Qt
     * @return std::unordered_map<std::string, std::string> : mappa convertita in elementi STL
     */
    std::unordered_map<std::string, std::string> QMapToUnorderedMap(const QMap<QString, QString>& attributeMapQt);

    /**
     * @brief UnorderedMapToQMap : helper per conversione std::unoredered_map a QMap
     * @param attributeMapStd : mappa di attributi che utilizza elementi della STL
     * @return QMap<QString, QString> : mappa convertita in elementi Qt
     */
    QMap<QString, QString> UnorderedMapToQMap(const std::unordered_map<std::string, std::string>& attributeMapStd);


    // === VIEWER WIDGET ===

    //QWidget* createViewerForIndex(unsigned int ind, QWidget* parent);


signals:

    /**
     * @brief currentIndexChanged : segnale emesso quando l'indice corrente viene modificato
     * @param ind : nuovo indice corrente
     */
    void currentIndexChanged(int ind);

    /**
     * @brief editSuccess : segnale emesso quando la modifica di un media ha successo
     * @param ind : indice del media modificato
     */
    void editSuccess(unsigned int ind);

    /**
     * @brief editFailure : segnale emesso quando la modifica di un media e' fallita
     * @param ind : indice del media modificato
     * @param errorMsg : messaggio d'errore
     */
    void editFailure(unsigned int ind, const QString& errorMsg);

    /**
     * @brief createSuccess : segnale emesso quando la creazione di un nuovo media ha successo
     */
    void createSuccess(const QString& msg);

    /**
     * @brief createFailure : segnale emesso quando la creazione di un nuovo media e' fallita
     * @param errorMsg : messaggio d'errore
     */
    void createFailure(const QString& errorMsg);

    /**
     * @brief searchResults : segnale emesso quando un'operazione di ricerca ha trovato dei risultati
     * @param mediaIDs : vettore con gli identificatori univoci dei risultati della ricerca
     */
    void searchResults(const std::vector<unsigned int>& mediaIDs);

    /**
     * @brief removedMedia : segnale emesso quando un media viene rimosso dalla libreria
     * @param ind : indice del media rimosso
     */
    void removedMedia(unsigned int ind);

    /**
     * @brief libraryDeleted : segnale emesso quando viene eliminata l'intera libreria
     */
    void libraryDeleted();

    /**
     * @brief errorOccurred : segnale emesso quando si verifica un errore in una delle operazioni del Controller
     * @param errorMsg : messaggio d'errore
     */
    void errorOccurred(const QString& errorMsg);

    /**
     * @brief undoPossible : segnale emesso per richiesta operazione Undo
     * @param undo : true se Undo possibile, false altrimenti
     */
    void undoPossible(bool undo);

    /**
     * @brief redoPossible : segnale emesso per richiesta operazione Redo
     * @param redo : true se Redo possibile, false altrimenti
     */
    void redoPossible(bool redo);

    /**
     * @brief commandDescription : segnale emesso per richiesta informazioni aggiuntive sull'ultima operazione ripristinata/annullata
     * @param info : informazioni aggiuntive di ultimo redo/undo
     */
    void lastCommandInfo(const QString& info);


public slots:


    // === OPERAZIONI INDICE (SLOT) ===

    /**
     * @brief onSetIndexRequest : gestisce richiesta di impostare nuovo indice corrente
     * @param ind : nuovo indice da impostare
     * @return bool : true se l'operazione ha successo, false altrimenti
     */
    bool onSetIndexRequest(int ind);

    /**
     * @brief onGoToNextIndexRequest : gestisce richiesta di avanzare l'indice corrente di 1
     * @return bool : true se l'operazione ha successo, false altrimenti
     */
    bool onGoToNextIndexRequest();

    /**
     * @brief onGoToPreviousIndexRequest : gestisce richiesta di retrocedere l'indice corrente di 1
     * @return bool : true se l'operazione ha successo, false altrimenti
     */
    bool onGoToPreviousIndexRequest();

    /**
     * @brief onGoToFirstIndexRequest : gestisce richiesta di impostare l'indice corrente al primo media in libreria
     * @return bool : true se l'operazione ha successo, false altrimenti
     */
    bool onGoToFirstIndexRequest();

    /**
     * @brief onGoToLastIndexRequest : gestisce richiesta di impostrare l'indice corrente all'ultimo elemento in libreria
     * @return bool : true se l'operazione ha successo, false altrimenti
     */
    bool onGoToLastIndexRequest();


    // === MODIFICA (SLOT) ===

    /**
     * @brief onEditMediaRequest : gestisce richiesta di modifica media ad un dato indice
     * @param ind : indice del media da modificare
     * @param mediaEdits : mappa delle modifiche da applicare al media
     */
    void onEditMediaRequest(unsigned int ind, QMap<QString, QString> mediaEdits);


    // === CREAZIONE (SLOT) ===

    /**
     * @brief onCreateMediaRequest : gestisce richiesta di creazione di un nuovo media
     * @param ind : indice in cui inserire il media (o posizione di riferimento)
     * @param type : tipo del media da creare
     * @param attributes : mappa degli attributi del media da creare
     */
    void onCreateMediaRequest(unsigned int ind, const std::string& type, const std::unordered_map<std::string, std::string>& attributes);


    // === RIMOZIONE (SLOT) ===

    /**
     * @brief onRemoveMediaAtIndexRequest : gestisce richiesta di rimozione di un media ad un dato indice
     * @param ind : indice del media da rimuovere
     * @return int : 1 se la rimozione ha successo, 0 altrimenti
     */
    int onRemoveMediaAtIndexRequest(unsigned int ind);

    /**
     * @brief onDeleteLibraryRequest : gestisce richiesta di eliminare l'intera libreria. Elimina tutti i media, svuota i vettori dei comandi Undo/Redo e imposta l'indice corrente a 0
     */
    void onDeleteLibraryRequest();


    // === UNDO/REDO (SLOT) ===

    /**
     * @brief onUndoRequest : gestisce richiesta di operazione Undo (se possibile)
     * @details emette il segnale 'lastCommandInfo' per mandare informazioni aggiuntive sull'ultimo Undo
     */
    void onUndoRequest();

    /**
     * @brief onRedoRequest : gestisce richiesta di operazione Redo (se possibile)
     * @details emette il segnale 'lastCommandInfo' per mandare informazioni aggiuntive sull'ultimo Redo
     */
    void onRedoRequest();


    // == JSON (SLOT) ===

    /**
     * @brief onSaveLibraryRequest : gestisce richista di salvataggio della libreria a file (in formato JSON)
     * @param filename : path del file a cui salvare la libreria
     * @return bool : true se il salvataggio ha successo, false altrimenti
     */
    bool onSaveLibraryRequest(const QString& filename);

    /**
     * @brief onLoadLibraryRequest : gestisce richiesta di caricamento libreria da file (in formato JSON)
     * @param filename : path del file da cui caricare la libreria
     * @return bool : true se il caricamento ha successo, false altrimenti
     */
    bool onLoadLibraryRequest(const QString& filename);


    // === RICERCA (SLOT) ===

    /**
     * @brief onSearchRequest : gestisce richiesta di risultati trovati in un'operazione di ricerca
     * @param query : filtri per l'operazione di ricerca
     */
    void onSearchRequest(Model::Library::SearchQuery query);

    /**
     * @brief onSearchMediaByNameRequest : gestisce richiesta di ricerca dei media per nome (anche con match parziali)
     * @param mediaName : nome del media da cercare
     * @details crea il SearchQuery impostando il nome e emette il sengale 'onSearchRequest'
     */
    void onSearchMediaByNameRequest(const QString& mediaName);


    // === CUSTOM WIDGETS (SLOT) ===

    /**
     * @brief onScoreRequested : gestisce richiesta di calcolo score di un media, tramite il relativo Viewer widget
     * @param ind : indice del media
     * @param viewer : puntatore a custom widget con tipo corrispondente al media (del tipo View::Viewer)
     */
    void onScoreRequested(unsigned int ind, QWidget* viewer);

    /**
     * @brief onValidateISBNRequested : gestisce richiesta di validazione ISBN di un media EBook (utilizzando algoritmo ISBN-13 checksum)
     * @param ind : indice del media EBook
     * @param viewer : puntatore al custom widget (del tipo Viewer::EBookViewer)
     */
    void onValidateISBNRequested(unsigned int ind, QWidget* viewer);

    /**
     * @brief onVideoDurationRequested : gestisce richiesta di durata media Video in ore,min
     * @param ind : indice del media Video
     * @param viewer : puntatore al custom widget (del tipo View::Viewer::VideoViewer)
     */
    void onVideoDurationRequested(unsigned int ind, QWidget* viewer);


private:

    Model::Library::Manager* manager; // puntatore al Manager

};

}

#endif // CONTROLLER_CONTROLLER_H

#ifndef VIEW_WINDOW_H
#define VIEW WINDOW_H

#include "Controller/Controller.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QSplitter>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QListWidget>
#include <QMap>
#include <QComboBox>
#include <QSpinBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QLineEdit>

/** @brief Window
 *
 *  Window e' la classe principale della GUI di Virtual Library.
 *  Deriva pubblicamente da QMainWindow e viene utilizzata per gestire la user interface, utilizzando uno splitter per suddividere la finistra principale
 *  in due pannelli: il pannello sinistro (per l'area di ricerca e la lista dei media), e il pannello destro (per i vari custom widget definiti nel namespace View).
 *
 *  La classe Windoe ermette la visualizzazione, modifica, ricerca e creazione dei media tramite custom widget inseriti nel pannello destro.
 *  La gestione dell'interazione tra utente e Controller avviene attravereso il sistema di segnali/slot di Qt, delegando tutte le operazioni logiche e di dati al Controller.
 *
 *  Utilizza i vari custom widget definiti nei namespace Creator, Editor, Viewer e Search per implementare le operazioni sui media, in base al loro tipo.
 *  In particolare, la lista dei media viene rappresentata come un QListWidget dei media, mostrati tramite il custom widget ConciseViewer. Ciascuno contiene un radio
 *  button per essere selezionato come media corrente, e tutti i media nella lista sono trattati come un button group esclusivo, permettendo solamente ad uno di essere selezionato.
 *  Entrambi questi pannelli sono vengono aggiornati dinamicamente in risposta alle azioni dello user.
 *
 *  Ho deciso di centralizzare tutta logica relativa all'interfaccia in Window, cosi' mantenendo una separazione netta tra il modello logico e la vista (MVC).
 *
 *  Inolte, dispone di keyboard shortcuts e tooltip per rendere la UI piu' facile da utilizzare.
 */

namespace View {

class Window : public QMainWindow {

    Q_OBJECT

public:

    // === COSTRUTTORE ===

    /**
     * @brief Window : costruttore, imposta menu, toolbar, pannelli e mostra completamento con status bar
     * @param parent : parent widget
     */
    explicit Window(QWidget* parent = nullptr);


    // === SETUP & GENERALE

    /**
     * @brief setController : imposta il controller, collega segnali/slot
     * @param c : puntatore a Controller
     */
    void setController(Controller::Controller* c);

    /**
     * @brief showStatusBarMessage : helper per mostrare messaggio sulla status bar
     * @param msg : messaggio da mostrare
     */
    void showStatusBarMessage(const QString& msg);



    // === CUSTOM WIDGETS - Pannello Sinistro ===

    /**
     * @brief showAllLibraryMedia : svuota la lista dei media e ricrea il gruppo esclusivo di radio button per la selezione dei media.
     *                              Per ogni media attualmente in libreria crea e mostra un ConcicseViewer nella lista, rendendo come
     *                              selezionabile solo uno alla volta
     */
    void showAllLibraryMedia();

    /**
     * @brief showSearchResults : mostra i media trovati in un'operazione di ricerca. Analogo a 'showAllLibraryMedia', ma usa gli indici corrispondenti
     *                            dei media trovati (mediaIDs) nella creazione dei ConciseViewer da mostrare nella lista.
     * @param mediaIDs : identificatori univoci dei media trovati
     */
    void showSearchResults(const std::vector<unsigned int>& mediaIDs);



    // == CUSTOM WIDGETS - Pannello Desto ===

    /**
     * @brief showViewerWidget : inserisce nel pannello destro il custom viewer widget, collegando i segnali/slot
     * @param viewerWidget : puntatore a viewer widget (del tipo View::Viewer)
     */
    void showViewerWidget(QWidget* viewerWidget);

    /**
     * @brief showEditorWidget : inserisce nel pannello destro il custom editor widget, collegando i segnali/slot
     * @param editorWidget : puntatore a editor widget (del tipo View::Editor)
     */
    void showEditorWidget(QWidget* editorWidget);

    /**
     * @brief showCreatorWidget : inserisce nel pannello destro il custom creator widget, collegando i segnali/slot
     * @param creatorWidget : puntatore a creator widget (del tipo View::Creator)
     */
    void showCreatorWidget(QWidget* creatorWidget);

    /**
     * @brief showTypeSelectorWidget : inserisce nel pannello destro custom widget per selezione tipo da creare, eliminando quello corrente (se necessario).
     *                                 Disabilita il pannello destro e la toolbare e collega i segnali/slot
     */
    void showTypeSelectorWidget();

    /**
     * @brief showSearchWidget : inserisce nel pannello destro il custom search widget
     * @param searchWidget : puntatore a search widhet (del tipo View::Search::SearchWidget)
     */
    void showSearchWidget(QWidget* searchWidget);


signals:

    /**
     * @brief undoRequested : segnala al Controller richiesta di un'operazione Undo
     */
    void undoRequested();

    /**
     * @brief redoRequested : segnala al Controller richiesta di un'operazione Redo
     */
    void redoRequested();

    /**
     * @brief onSearchMediaByNameRequest : segnala al Controller richiesta di ricerca solamente per nome
     * @param mediaName : nome del media con cui effettuare la ricerca
     */
    void onSearchMediaByNameRequest(const QString& mediaName);


public slots:


    // === OPERAZIONI INDICE (SLOT) ===

    /**
     * @brief onConciseViewerSelected : gestisce richiesta di impostare come indice corrente il media selezionato nella lista dei media (lista di ConciseViewer)
     * @param ind : indice del media da impostare come indice corrente
     * @param select : true se il media e' selezionato, false altrimenti
     */
    void onConciseViewerSelected(int ind, bool select);



    // === VISUALIZZAZIONE (SLOT) ===

    /**
     * @brief onViewActionTriggered : gestisce richiesta di visualizzare con custom viewer widget per il media all'indice corrente.
     *                                Utilizza MediaViewerFactory per creare e mostrare il viewer widget corretto
     */
    void onViewActionTriggered();

    /**
     * @brief onViewLibraryMediaList : gestisce richiesta di visualizzare la lista dei media attualmente in libreria
     */
    void onViewLibraryMediaList();

    /**
     * @brief onRefreshLibraryMediaList : gestisce richiesta di aggiornare la lista dei media
     */
    void onRefreshLibraryMediaList();

    /**
     * @brief onClearLibraryMediaList : gestisce richiesta di svuotare la lista dei media. Svuota la lista e elimina (se necessario) il gruppo
     *                                  di radio button, impostandolo a nullptr
     */
    void onClearLibraryMediaList();



    // === MODIFICA (SLOT) ===

    /**
     * @brief onEditActionTriggered : gestisce richiesta di visualizzare custom editor widget per il media all'indice corrente.
     *                                Utilizza MediaEditorFactory per creare e mostrare l'editor widget corretto
     */
    void onEditActionTriggered();

    /**
     * @brief onEditMediaSuccess : gestisce successo di un'operazione di modifica.
     *                             Elimina il custom editor widget, e aggiorna la lista dei media
     * @param ind : indice del media modificato con successo
     */
    void onEditMediaSuccess(unsigned int ind);

    /**
     * @brief onEditMediaFailure : gestisce fallimento di un'operazione di modifica, mostrando un QMessageBox di warning, con un messaggio sul possibile errore rilevato
     * @param ind : indice del media in cui e' fallita la modifica
     * @param errorMsg : messaggio con informazioni aggiuntive sul possibile errore rilevato
     */
    void onEditMediaFailure(unsigned int ind, const QString& errorMsg);



    // === RIMOZIONE (SLOT) ===

    /**
     * @brief onRemoveMedia : gestisce richiesta di rimozione del media all'indice corrente
     */
    void onRemoveMedia();



    // === UNDO/REDO (SLOT) ===

    /**
     * @brief onUndoActionTriggered : gestisce richiesta di operazione Undo, segnalandolo al Controller e aggiornando la lista dei media
     */
    void onUndoActionTriggered();

    /**
     * @brief onRedoActionTriggered : gestisce richiesta di operazione Redo, segnalandolo al Controller e aggiornando la lista dei media
     */
    void onRedoActionTriggered();

    /**
     * @brief onShowLastCommandInfo : gestisce richiesta di mostrare informazione relative all'ultimo Redo/Undo
     * @param info : informazione relative all'ultimo Undo/Redo
     */
    void onShowLastCommandInfo(const QString& info);



    // === CREAZIONE (SLOT) ===

    /**
     * @brief onCreateActionTriggered : gestisce richiesta di creazione media, inserendo TypeSelectorWidget nel pannello destro
     */
    void onCreateActionTriggered();

    /**
     * @brief onCreateTypeSelected : gestisce richiesta di creazione nuovo media, utilizzando MediaCreatorFactory per creare e inserire
     *                               nel pannello destro il custom creator widget corretto
     * @param mediaType : tipo di media da creare, salvato come campo dati privato per semplicita' (aggiornato con TypeSelectorWidget)
     */
    void onCreateTypeSelected(const QString& mediaType);

    /**
     * @brief onCreateMediaRequested : gestisce richiesta di creazione nuovo media, delegando l'operazione al Controller
     * @param mediaAttributes : mappa di attributi con cui creare il media (convertita in std::unoredered_map dal Controller)
     */
    void onCreateMediaRequested(QMap<QString, QString> mediaAttributes);

    /**
     * @brief onCreateMediaSuccess : gestisce successo di un'operazione di creazione, eliminando il custom creator widget dal pannello destro
     *                               e aggiornando la lista dei media
     * @param msg : messaggio di successo
     */
    void onCreateMediaSuccess(const QString& msg);

    /**
     * @brief onCreateMediaFailure : gestisce fallimento di un'operazione di creazione, mostrando una QMessageBox di warning con un messaggio sul possibile errore rilevato
     * @param errorMsg : messaggio con possibili errori rilevati durante la creazione
     */
    void onCreateMediaFailure(const QString& errorMsg);



    // === RICERCA (SLOT) ===

    /**
     * @brief onSearchMedia : gestisce richiesta di operazione di ricerca, creando e inserendo nel pannello destro il custom widget (SearchWidget)
     */
    void onSearchMedia();

    /**
     * @brief onSearchAction : gestisce richiesta di effettuare operazione di ricerca, delegando l'operazione al Controller
     * @param query : filtri da applicare nell'operazione di ricerca
     */
    void onSearchAction(const Model::Library::SearchQuery& query);

    /**
     * @brief onSearchMediaByName : gestisce richiesta di ricerca solo per nome, prendendo la stringa dalla barra di ricerca e delegando il resto al Controller
     */
    void onSearchMediaByName();



    // === JSON (SLOT) ===

    /**
     * @brief onSaveLibraryToFile : gestisce richiesta di salvataggio libreria a file in formato JSON, aprendo un dialog per la scelta del file di salvataggio,
     *                              e delegando poi al Controller
     */
    void onSaveLibraryToFile();

    /**
     * @brief onLoadLibraryFromFile : gestisce richiesta di caricamento libreria da file in formato JSON, aprendo un dialog per la scelta del file da cui caricare,
     *                                e delegando poi al Controller
     */
    void onLoadLibraryFromFile();


private:

    Controller::Controller* controller; // puntatore al controller

    QSplitter* mainWindowSplitter; // splitter per separare in due pannelli

    QMenu* fileMenu;             // menu "File"
    QMenu* operationsMenu;       // menu "Operations"
    QMenu* libraryMenu;          // menu "Library"
    QMenu* settingsMenu;         // menu "Settings"
    QToolBar* mainWindowToolBar; // toolbar

    QWidget* leftPanel;            // pannello sinistro
    QVBoxLayout* leftPanelLayout;  // layout pannello sinistro
    QWidget* searchBarContainer;   // contenitore barra di ricerca
    QHBoxLayout* searchBarLayout;  // layout barra di ricerca
    QLineEdit* searchBar;          // barra di ricerca
    QPushButton* searchButton;     // bottone ricerca
    QListWidget* mediaLibraryList; // lista dei media in libraria (lista di ConciseViewer widget)

    // utilizzato per selezionare media dalla lista
    QButtonGroup* mediaListButtonGroup;

    QWidget* rightPanel;       // pannello sinistro
    QVBoxLayout* rightPanelLayout;   // layout pannello sinistro

    // custom widget del pannello sinistro, inizialmente nullptr
    QWidget* rightPanelWidget;

    // per tenere traccia dell'indice corrente
    QSpinBox* currentIndex;

    // azioni principali
    QAction* actionCreate;
    QAction* actionEdit;
    QAction* actionRemove;
    QAction* actionView;
    QAction* actionSearch;
    QAction* actionSearchFilters;
    QAction* actionUndo;
    QAction* actionRedo;

    // azioni salvataggio e caricamento
    QAction* actionSaveLibrary;
    QAction* actionLoadLibrary;

    // azioni lista dei media
    QAction* actionViewMediaList;
    QAction* actionClearMediaList;
    QAction* actionRefreshMediaList;
    QAction* actionExit;

    // salva il tipo di media da creare (fatto per semplicita')
    QString mediaTypeToCreate;

    /**
     * @brief setupMenus : setup dei menu "File", "Operations" e "Settings", aggiunge le azioni e le collega ai slot corrispondenti
     */
    void setupMenus();

    /**
     * @brief setupToolBar : setup del toolbar con azioni principale e aggiunge spinbox per indice corrente
     */
    void setupToolBar();

    /**
     * @brief setupLeftPanel : setup del pannello sinistro, imposta layout sinistro, barra di ricerca e bottone per ricerca per solo nome,
     *                         collega bottone allo slot 'searchMediaByName' e imposta a nullptr 'mediaListButtonGroup' utilizzato poi per
     *                         selezionare un media dalla lista.
     */
    void setupLeftPanel();

    /**
     * @brief setupRightPanel : setup del pannello destro per i custom widget, imposta layout destro, inserendo un QLabel come placeholder
     *                          e imposta il custom widget 'rightPanelWidget' come inizialmente nullptr
     */
    void setupRightPanel();

    /**
     * @brief setupPanels : setup pannello desto/sinistro, imposta splitter principale
     */
    void setupPanels();

    /**
     * @brief setShortcutsAndToolTips : imposta shortcut di tastiera e tooltip utili all'utente
     */
    void setShortcutsAndToolTips();

    /**
     * @brief setRightPanelWidget : helper privato per mostrare un custom widget nel pannello destro, eliminando quello corrente (se presente)
     * @param widget : puntatore a custom widget da inserire nel pannello destro
     * @param disable : se true disabilita pannello destro e toolbar, se false inveve li riabilita
     */
    void setRightPanelWidget(QWidget* widget, bool disable = true);

    /**
     * @brief removeRightPanelWidget
     */
    void removeRightPanelWidget();

};

}

#endif // VIEW_WINDOW_H

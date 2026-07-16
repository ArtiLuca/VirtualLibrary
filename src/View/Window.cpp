#include "Window.h"

#include "View/Viewer/MediaViewerFactory.h"
#include "View/Viewer/AudioViewer.h"
#include "View/Viewer/VideoViewer.h"
#include "View/Viewer/EBookViewer.h"
#include "View/Viewer/ImageViewer.h"
#include "View/Viewer/ConciseViewer.h"

#include "View/Creator/TypeSelectorWidget.h"
#include "View/Creator/MediaCreatorFactory.h"
#include "View/Creator/AudioCreator.h"
#include "View/Creator/VideoCreator.h"
#include "View/Creator/EBookCreator.h"
#include "View/Creator/ImageCreator.h"

#include "View/Editor/MediaEditorFactory.h"
#include "View/Editor/AudioEditor.h"
#include "View/Editor/VideoEditor.h"
#include "View/Editor/EBookEditor.h"
#include "View/Editor/ImageEditor.h"

#include "View/Search/SearchWidget.h"

#include <QAction>
#include <QLabel>
#include <QMessageBox>
#include <QSizePolicy>
#include <QFileDialog>
#include <QFile>
#include <QKeySequence>

namespace View {


// === COSTRUTTORE & SETUP GENERALE ===

Window::Window(QWidget* parent)
    : QMainWindow(parent)
{
    // setup dei menu
    setupMenus();
    // setup toolbar
    setupToolBar();
    // setup pannello destro e sinistro
    setupPanels();
    // setup dei keyboard shortcut e tooltip
    setShortcutsAndToolTips();

    statusBar()->showMessage("Setup completed", 3000);
}

void Window::setupMenus() {

    // menu "File"
    fileMenu = menuBar()->addMenu("File");
    actionLoadLibrary = new QAction("Load Library", this);
    actionSaveLibrary = new QAction("Save Library", this);
    actionExit = new QAction("Exit", this);

    // aggiunta azioni
    fileMenu->addAction(actionLoadLibrary);
    fileMenu->addAction(actionSaveLibrary);
    fileMenu->addSeparator();
    fileMenu->addAction(actionExit);

    // connect azioni
    connect(actionLoadLibrary, &QAction::triggered,
            this, &Window::onLoadLibraryFromFile);
    connect(actionSaveLibrary, &QAction::triggered,
            this, &Window::onSaveLibraryToFile);

    // menu "Operations"
    operationsMenu = menuBar()->addMenu("Operations");
    actionCreate = new QAction("Create", this);
    actionView = new QAction("View", this);
    actionEdit = new QAction("Edit", this);
    actionRemove = new QAction("Remove", this);
    actionSearch = new QAction("Search", this);
    actionUndo = new QAction("Undo", this);
    actionRedo = new QAction("Redo", this);

    // aggiunta azioni
    operationsMenu->addAction(actionCreate);
    operationsMenu->addAction(actionView);
    operationsMenu->addAction(actionEdit);
    operationsMenu->addAction(actionRemove);
    operationsMenu->addAction(actionSearch);
    operationsMenu->addSeparator();
    operationsMenu->addAction(actionUndo);
    operationsMenu->addAction(actionRedo);

    connect(actionCreate, &QAction::triggered,
            this, &Window::onCreateActionTriggered);
    connect(actionView, &QAction::triggered,
            this, &Window::onViewActionTriggered);
    connect(actionEdit, &QAction::triggered,
            this, &Window::onEditActionTriggered);
    connect(actionRemove, &QAction::triggered,
            this, &Window::onRemoveMedia);
    connect(actionSearch, &QAction::triggered,
            this, &Window::onSearchMedia);
    connect(actionUndo, &QAction::triggered,
            this, &Window::onUndoActionTriggered);
    connect(actionRedo, &QAction::triggered,
            this, &Window::onRedoActionTriggered);

    libraryMenu = menuBar()->addMenu("Library");
    actionViewMediaList = new QAction("View Library", this);
    actionRefreshMediaList = new QAction("Refresh", this);
    actionClearMediaList = new QAction("Clear", this);
    actionExit = new QAction("Exit", this);

    libraryMenu->addAction(actionViewMediaList);
    libraryMenu->addAction(actionRefreshMediaList);
    libraryMenu->addAction(actionClearMediaList);
    libraryMenu->addAction(actionExit);

    connect(actionViewMediaList, &QAction::triggered,
            this, &Window::onViewLibraryMediaList);
    connect(actionRefreshMediaList, &QAction::triggered,
            this, &Window::onRefreshLibraryMediaList);
    connect(actionClearMediaList, &QAction::triggered,
             this, &Window::onClearLibraryMediaList);
    connect(actionExit, &QAction::triggered,
            this, &QWidget::close);
}

void Window::setupToolBar() {

    mainWindowToolBar = addToolBar("Main ToolBar");

    mainWindowToolBar->addAction(actionCreate);
    mainWindowToolBar->addAction(actionEdit);
    mainWindowToolBar->addAction(actionRemove);
    mainWindowToolBar->addAction(actionView);
    mainWindowToolBar->addAction(actionSearch);
    mainWindowToolBar->addSeparator();
    mainWindowToolBar->addAction(actionLoadLibrary);
    mainWindowToolBar->addAction(actionSaveLibrary);
    mainWindowToolBar->addSeparator();
    mainWindowToolBar->addAction(actionViewMediaList);
    mainWindowToolBar->addAction(actionRefreshMediaList);
    mainWindowToolBar->addAction(actionClearMediaList);
    mainWindowToolBar->addSeparator();
    mainWindowToolBar->addAction(actionUndo);
    mainWindowToolBar->addAction(actionRedo);

    currentIndex = new QSpinBox(this);
    currentIndex->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    currentIndex->setMinimum(0);
    currentIndex->setMaximum(1000);
    mainWindowToolBar->addWidget(currentIndex);
    mainWindowToolBar->addAction(actionExit);

}

void Window::setupLeftPanel() {

    // setup pannello sinistro
    leftPanel = new QWidget;
    leftPanelLayout = new QVBoxLayout(leftPanel);

    // setup zona di ricerca
    searchBarContainer = new QWidget(this);
    searchBarContainer->setContentsMargins(0, 0, 0, 0);
    searchBarLayout = new QHBoxLayout(searchBarContainer);
    searchBar = new QLineEdit;
    searchBar->setPlaceholderText("Search media name...");
    searchButton = new QPushButton("Search By Name");
    searchButton->setToolTip("Ricerca media solamente per nome");
    searchBarLayout->addWidget(searchBar);
    searchBarLayout->addWidget(searchButton);
    leftPanelLayout->addWidget(searchBarContainer);

    // setup zona lista dei media
    mediaLibraryList = new QListWidget(leftPanel);
    mediaLibraryList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    leftPanelLayout->addWidget(mediaLibraryList);

    connect(searchButton, &QPushButton::clicked,
            this, &Window::onSearchMediaByName);

    mediaListButtonGroup = nullptr;

    leftPanel->setLayout(leftPanelLayout);
}

void Window::setupRightPanel() {

    // setup pannello destro
    rightPanel = new QWidget;
    rightPanelLayout = new QVBoxLayout(rightPanel);
    QLabel* tempLabel = new QLabel("Virtual Library (CTRL+O to select JSON file)", rightPanel);
    tempLabel->setStyleSheet("font-size: 12px; font-weight: bold;");
    rightPanelLayout->addWidget(tempLabel);
    rightPanelLayout->setAlignment(tempLabel, Qt::AlignHCenter);

    rightPanelWidget = nullptr;

    rightPanel->setLayout(rightPanelLayout);
}

void Window::setupPanels() {

    setupLeftPanel();
    setupRightPanel();

    // splitter pannelli
    mainWindowSplitter = new QSplitter(this);
    mainWindowSplitter->setStyleSheet("QSplitter::handle { background-color: #ededed; }");
    mainWindowSplitter->addWidget(leftPanel);
    mainWindowSplitter->addWidget(rightPanel);
    mainWindowSplitter->setStretchFactor(0, 1);
    mainWindowSplitter->setStretchFactor(1, 2);
    setCentralWidget(mainWindowSplitter);

}

void Window::setController(Controller::Controller* c) {

    controller = c;

    // emetti segnali per Undo/Redo
    controller->initializeCommandSignals();

    // connect per mostrare errori/messaggi
    connect(controller, &Controller::Controller::errorOccurred,
            this, &Window::showStatusBarMessage);

    // connect per indice
    connect(currentIndex, &QSpinBox::valueChanged,
            controller, &Controller::Controller::onSetIndexRequest);
    connect(controller, &Controller::Controller::currentIndexChanged,
            currentIndex, &QSpinBox::setValue);

    // connect per operazione modifica
    connect(controller, &Controller::Controller::editSuccess,
            this, &Window::onEditMediaSuccess);
    connect(controller, &Controller::Controller::editFailure,
            this, &Window::onEditMediaFailure);

    // connect per operazione creazione
    connect(controller, &Controller::Controller::createSuccess,
            this, &Window::onCreateMediaSuccess);
    connect(controller, &Controller::Controller::createFailure,
            this, &Window::onCreateMediaFailure);

    // connect per operazione undo/redo
    connect(this, &Window::undoRequested,
            controller, &Controller::Controller::onUndoRequest);
    connect(this, &Window::redoRequested,
            controller, &Controller::Controller::onRedoRequest);
    connect(controller, &Controller::Controller::undoPossible,
            actionUndo, &QAction::setEnabled);
    connect(controller, &Controller::Controller::redoPossible,
            actionRedo, &QAction::setEnabled);
    connect(controller, &Controller::Controller::lastCommandInfo,
            this, &Window::onShowLastCommandInfo);

    // connect per operazione ricerca
    connect(this, &Window::onSearchMediaByNameRequest, controller,
            &Controller::Controller::onSearchMediaByNameRequest);
    connect(controller, &Controller::Controller::searchResults,
            this, &Window::showSearchResults);
}


void Window::setShortcutsAndToolTips() {

    // caricamento e salvataggio libreria
    actionLoadLibrary->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    actionLoadLibrary->setToolTip("Carica la libreria da file (CTRL + O)");
    actionSaveLibrary->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    actionSaveLibrary->setToolTip("Salva la libreria (CTRL + S)");

    // operazioni fondamentali
    actionCreate->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    actionCreate->setToolTip("Crea un nuovo media (CTRL + V))");
    actionView->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_V));
    actionView->setToolTip("Visualizza media indice corrente (CTRL + V)");
    actionEdit->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_E));
    actionEdit->setToolTip("Modifica media indice corrente (CTRL + E)");
    actionRemove->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_R));
    actionRemove->setToolTip("Rimuovi media indice corrente (CTRL + R)");
    actionSearch->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_F));
    actionSearch->setToolTip("Ricerca media con filtri (CTRL + F)");
    actionUndo->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z));
    actionUndo->setToolTip("Undo ultima operazione (CTRL + Z)");
    actionRedo->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y));
    actionRedo->setToolTip("Redo ultima operazione (CTRL + Y)");
    actionExit->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
    actionExit->setToolTip("Chiudi Virtual Library");

    // tooltip lista dei media
    actionViewMediaList->setToolTip("Visualizza lista di tutti i media in libraria");
    actionRefreshMediaList->setToolTip("Aggiorna lista dei media");
    actionClearMediaList->setToolTip("Svuota la lista dei media");

}


void Window::showStatusBarMessage(const QString& msg) {
    statusBar()->showMessage(msg, 3000);
}


// === CUSTOM WIDGETS - Pannello Sinistro ===

void Window::showAllLibraryMedia() {

    // svuota lista corrente
    onClearLibraryMediaList();

    // crea nuovo button group, con eslusivita'
    mediaListButtonGroup = new QButtonGroup(this);
    // solamente un media selezionabile
    mediaListButtonGroup->setExclusive(true);

    // prendi il numero di media attuali
    int mediaCount = controller->getManagerSize();

    // per ognuno
    for (int i = 0; i < mediaCount; ++i) {

        // crea un ConciseViewer per mostrarlo
        auto media = controller->getMediaAtIndex(i);
        int mediaID = media->getUniqueID();
        QString mediaType = QString::fromStdString(media->displayStringType());
        QString mediaName = QString::fromStdString(media->getMediaName());

        View::Viewer::ConciseViewer* conciseViewer = new View::Viewer::ConciseViewer(
            i, mediaID, mediaType, mediaName, this
        );

        connect(conciseViewer, &View::Viewer::ConciseViewer::selectedMediaChanged,
                this, &Window::onConciseViewerSelected);

        // trova il QRadiButton del ConciseViewer e aggiungi al gruppo esclusivo
        QRadioButton* mediaRadioButton = conciseViewer->findChild<QRadioButton*>();
        if (mediaRadioButton) {
            mediaListButtonGroup->addButton(mediaRadioButton, i);
        }

        // inserisci custom viewer widget alla lista
        QListWidgetItem* mediaListItem = new QListWidgetItem(mediaLibraryList);
        mediaListItem->setSizeHint(conciseViewer->sizeHint());
        mediaLibraryList->addItem(mediaListItem);
        mediaLibraryList->setItemWidget(mediaListItem, conciseViewer);
    }
}

void Window::showSearchResults(const std::vector<unsigned int>& mediaIDs) {

    // svuota lista corrente
    onClearLibraryMediaList();

    // crea nuovo button group, con eslusivita'
    mediaListButtonGroup = new QButtonGroup(this);
    // solamente un media selezionabile
    mediaListButtonGroup->setExclusive(true);

    // prendi gli indici corrispondenti dei media trovati
    std::vector<unsigned int> resultIndexes = controller->getSearchResultIndexes(mediaIDs);

    // per ognuno
    for (unsigned int i = 0; i < mediaIDs.size(); ++i) {

        // crea un ConciseViewer per mostrarlo
        auto media = controller->getMediaByID(mediaIDs[i]);
        if (!media) continue;
        int mediaId = media->getUniqueID();
        QString mediaType = QString::fromStdString(media->displayStringType());
        QString mediaName = QString::fromStdString(media->getMediaName());

        // utilizzando l'indice corrispondente trovato
        View::Viewer::ConciseViewer* conciseViewer = new View::Viewer::ConciseViewer(
            resultIndexes[i], mediaId, mediaType, mediaName, this
        );

        connect(conciseViewer, &View::Viewer::ConciseViewer::selectedMediaChanged,
                this, &Window::onConciseViewerSelected);

        // trova il QRadiButton del ConciseViewer e aggiungi al gruppo esclusivo
        QRadioButton* mediaRadioButton = conciseViewer->findChild<QRadioButton*>();
        if (mediaRadioButton) {
            mediaListButtonGroup->addButton(mediaRadioButton, i);
        }

        // inserisci custom viewer widget alla lista
        QListWidgetItem* mediaListItem = new QListWidgetItem(mediaLibraryList);
        mediaListItem->setSizeHint(conciseViewer->sizeHint());
        mediaLibraryList->addItem(mediaListItem);
        mediaLibraryList->setItemWidget(mediaListItem, conciseViewer);
    }

}


// == CUSTOM WIDGETS - Pannello Desto ===

void Window::setRightPanelWidget(QWidget* widget, bool disable) {

    QLayoutItem* rightPanelItem;
    while ((rightPanelItem = rightPanelLayout->takeAt(0)) != nullptr) {
        if (rightPanelItem->widget()) {
            rightPanelItem->widget()->deleteLater();
        }
        delete rightPanelItem;
    }

    if (widget) {
        rightPanelLayout->addWidget(widget);
    }

    if (disable) {
        leftPanel->setEnabled(false);
        mainWindowToolBar->setEnabled(false);
    }
    else {
        leftPanel->setEnabled(true);
        mainWindowToolBar->setEnabled(true);
    }
}

void Window::removeRightPanelWidget() {

    QLayoutItem* rightPanelItem;
    while ((rightPanelItem = rightPanelLayout->takeAt(0)) != nullptr) {
        if (rightPanelItem->widget()) {
            rightPanelItem->widget()->deleteLater();
        }
        delete rightPanelItem;
    }

    leftPanel->setEnabled(true);
    mainWindowToolBar->setEnabled(true);
}

void Window::showViewerWidget(QWidget* viewerWidget) {

    setRightPanelWidget(viewerWidget, true);

    if (auto audioViewer = dynamic_cast<View::Viewer::AudioViewer*>(viewerWidget)) {

        connect(audioViewer, &View::Viewer::AudioViewer::closed,
                this, &Window::removeRightPanelWidget);
        connect(audioViewer, &View::Viewer::AudioViewer::scoreRequested,
                controller, &Controller::Controller::onScoreRequested);
    }
    if (auto videoViewer = dynamic_cast<View::Viewer::VideoViewer*>(viewerWidget)) {

        connect(videoViewer, &View::Viewer::VideoViewer::closed,
                this, &Window::removeRightPanelWidget);
        connect(videoViewer, &View::Viewer::VideoViewer::scoreRequested,
                controller, &Controller::Controller::onScoreRequested);
        connect(videoViewer, &View::Viewer::VideoViewer::videoDurationRequested,
                controller, &Controller::Controller::onVideoDurationRequested);
    }
    if (auto ebookViewer = dynamic_cast<View::Viewer::EBookViewer*>(viewerWidget)) {

        connect(ebookViewer, &View::Viewer::EBookViewer::closed,
                this, &Window::removeRightPanelWidget);
        connect(ebookViewer, &View::Viewer::EBookViewer::scoreRequested,
                controller, &Controller::Controller::onScoreRequested);
        connect(ebookViewer, &View::Viewer::EBookViewer::isbnValidateRequest,
                controller, &Controller::Controller::onValidateISBNRequested);
    }
    if (auto imageViewer = dynamic_cast<View::Viewer::ImageViewer*>(viewerWidget)) {

        connect(imageViewer, &View::Viewer::ImageViewer::closed,
                this, &Window::removeRightPanelWidget);
        connect(imageViewer, &View::Viewer::ImageViewer::scoreRequested,
                controller, &Controller::Controller::onScoreRequested);
    }
}

void Window::showCreatorWidget(QWidget* creatorWidget) {

    setRightPanelWidget(creatorWidget, true);

    if (auto audio = dynamic_cast<View::Creator::AudioCreator*>(creatorWidget)) {
        connect(audio, &View::Creator::AudioCreator::createCancelled,
                this, &Window::removeRightPanelWidget);
        connect(audio, &View::Creator::AudioCreator::createRequested,
                this, &Window::onCreateMediaRequested);
    }
    if (auto video = dynamic_cast<View::Creator::VideoCreator*>(creatorWidget)) {
        connect(video, &View::Creator::VideoCreator::createCancelled,
                this, &Window::removeRightPanelWidget);
        connect(video, &View::Creator::VideoCreator::createRequested,
                this, &Window::onCreateMediaRequested);
    }
    if (auto ebook = dynamic_cast<View::Creator::EBookCreator*>(creatorWidget)) {
        connect(ebook, &View::Creator::EBookCreator::createCancelled,
                this, &Window::removeRightPanelWidget);
        connect(ebook, &View::Creator::EBookCreator::createRequested,
                this, &Window::onCreateMediaRequested);
    }
    if (auto image = dynamic_cast<View::Creator::ImageCreator*>(creatorWidget)) {
        connect(image, &View::Creator::ImageCreator::createCancelled,
                this, &Window::removeRightPanelWidget);
        connect(image, &View::Creator::ImageCreator::createRequested,
                this, &Window::onCreateMediaRequested);
    }
}

void Window::showTypeSelectorWidget() {

    QLayoutItem* item;
    while ((item = rightPanelLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }

    View::Creator::TypeSelectorWidget* selector = new View::Creator::TypeSelectorWidget(this);

    rightPanelLayout->addWidget(selector);

    leftPanel->setEnabled(false);
    mainWindowToolBar->setEnabled(false);

    connect(selector, &View::Creator::TypeSelectorWidget::mediaTypeSelected,
            this, &Window::onCreateTypeSelected);
    connect(selector, &View::Creator::TypeSelectorWidget::closed,
            this, &Window::removeRightPanelWidget);

    statusBar()->showMessage("TypeSelectorWidget inserted into right panel", 3000);

}

void Window::showEditorWidget(QWidget* editorWidget) {

    setRightPanelWidget(editorWidget, true);

    if (auto audioEditor = dynamic_cast<View::Editor::AudioEditor*>(editorWidget)) {
        connect(audioEditor, &View::Editor::AudioEditor::closed,
                this, &Window::removeRightPanelWidget);
        connect(audioEditor, &View::Editor::AudioEditor::mediaEditsConfirmed,
                controller, &Controller::Controller::onEditMediaRequest);
    }
    if (auto videoEditor = dynamic_cast<View::Editor::VideoEditor*>(editorWidget)) {
        connect(videoEditor, &View::Editor::VideoEditor::closed,
                this, &Window::removeRightPanelWidget);
        connect(videoEditor, &View::Editor::VideoEditor::mediaEditsConfirmed,
                controller, &Controller::Controller::onEditMediaRequest);
    }
    if (auto ebookEditor = dynamic_cast<View::Editor::EBookEditor*>(editorWidget)) {
        connect(ebookEditor, &View::Editor::EBookEditor::closed,
                this, &Window::removeRightPanelWidget);
        connect(ebookEditor, &View::Editor::EBookEditor::mediaEditsConfirmed,
                controller, &Controller::Controller::onEditMediaRequest);
    }
    if (auto imageEditor = dynamic_cast<View::Editor::ImageEditor*>(editorWidget)) {
        connect(imageEditor, &View::Editor::ImageEditor::closed,
                this, &Window::removeRightPanelWidget);
        connect(imageEditor, &View::Editor::ImageEditor::mediaEditsConfirmed,
                controller, &Controller::Controller::onEditMediaRequest);
    }
}

void Window::showSearchWidget(QWidget* searchWidget) {

    setRightPanelWidget(searchWidget, true);

    if (auto search = dynamic_cast<View::Search::SearchWidget*>(searchWidget)) {

        connect(search, &View::Search::SearchWidget::confirmSearchFilters,
                this, &Window::onSearchAction);
        connect(search, &View::Search::SearchWidget::closed,
                this, &Window::removeRightPanelWidget);
    }
}


// === OPERAZIONI INDICE (SLOT) ===

void Window::onConciseViewerSelected(int ind, bool select) {

    // se il media e' selezionato
    if (select) {
        // prendi l'indice corrente
        currentIndex->setValue(ind);
        // richiesta al Controller di impostare come indice corrente
        controller->onSetIndexRequest(ind);
        showStatusBarMessage("User selected media at index " + QString::number(ind));
    }
}


// === VISUALIZZAZIONE & MEDIA LIST (SLOT) ===


void Window::onViewActionTriggered() {

    // prendi il media all'indice corrente
    int currInd = currentIndex->value();
    auto mediaPtr = controller->getMediaAtIndex(currInd);

    // check che il media sia valido
    if (!mediaPtr) {
        showStatusBarMessage("No media was found at index " + QString::number(currInd));
        return;
    }

    statusBar()->showMessage("Viewing media at index " + QString::number(currInd), 3000);

    // utilizza MediaViewerFactory per creare il widget corretto
    View::Viewer::MediaViewerFactory viewerFactory{controller, currInd, this};
    mediaPtr->accept(viewerFactory);
    QWidget* viewerWidget = viewerFactory.fetchAndReset();
    if (!viewerWidget) {
        showStatusBarMessage("Could not create Viewer widget for media at index " + QString::number(currInd));
        return;
    }

    // inserisci nel pannello destro
    showViewerWidget(viewerWidget);
}

void Window::onViewLibraryMediaList() {
    showAllLibraryMedia();
}

void Window::onRefreshLibraryMediaList() {

    onClearLibraryMediaList();
    onViewLibraryMediaList();
}

void Window::onClearLibraryMediaList() {

    mediaLibraryList->clear();
    if (mediaListButtonGroup) {
        delete mediaListButtonGroup;
        mediaListButtonGroup = nullptr;
    }
}



// === MODIFICA (SLOT) ===

void Window::onEditActionTriggered() {

    // prendi il media all'indice corrente
    int currInd = currentIndex->value();
    auto mediaPtr = controller->getMediaAtIndex(currInd);

    // check che il media sia valido
    if (!mediaPtr) {
        showStatusBarMessage("No media was found at index " + QString::number(currInd));
        return;
    }

    statusBar()->showMessage("Editing media at index " + QString::number(currInd), 3000);

    // utilizza MediaEditorFactory per creare il widget corretto
    View::Editor::MediaEditorFactory editorFactory{controller, currInd, this};
    mediaPtr->accept(editorFactory);
    QWidget* editorWidget = editorFactory.fetchAndReset();

    if (!editorWidget) {
        showStatusBarMessage("Could not create Editor widget for media at index " + QString::number(currInd));
        return;
    }

    // inserisci nel pannello destro
    showEditorWidget(editorWidget);

}

void Window::onEditMediaSuccess(unsigned int ind) {

    removeRightPanelWidget();
    statusBar()->showMessage("Successfully edited media at index " + QString::number(ind), 3000);
    onRefreshLibraryMediaList();
}

void Window::onEditMediaFailure(unsigned int ind, const QString& errorMsg) {

    QMessageBox::critical(this, "Edit Failed",
                          "Failed to edit media at index " + QString::number(ind) + ", " + errorMsg);
}


// === RIMOZIONE (SLOT) ===

void Window::onRemoveMedia() {

    int currInd = currentIndex->value();

    if (controller->onRemoveMediaAtIndexRequest(currInd)) {
        showStatusBarMessage("Removed media at index " + QString::number(currInd));
        onRefreshLibraryMediaList();
    }
    else {
        showStatusBarMessage("Could not remove media at index " + QString::number(currInd));
    }
}


// === UNDO/REDO (SLOT) ===

void Window::onUndoActionTriggered() {

    emit undoRequested();
    onRefreshLibraryMediaList();

}

void Window::onRedoActionTriggered() {

    emit redoRequested();
    onRefreshLibraryMediaList();
}

void Window::onShowLastCommandInfo(const QString& info) {

    showStatusBarMessage(info);
}


// === CREAZIONE (SLOT) ===


void Window::onCreateActionTriggered() {
    showTypeSelectorWidget();
}

void Window::onCreateTypeSelected(const QString& mediaType) {

    mediaTypeToCreate = mediaType;

    View::Creator::MediaCreatorFactory creatorFactory{mediaType, controller};
    QWidget* creatorWidget = creatorFactory.fetchAndReset();
    if (!creatorWidget) {
        showStatusBarMessage("Could not create Creator widget");
        return;
    }

    showCreatorWidget(creatorWidget);
}

void Window::onCreateMediaRequested(QMap<QString, QString> mediaAttributes) {

    int ind = controller->getManagerSize();
    controller->onCreateMediaRequest(ind, mediaTypeToCreate.toUpper().toStdString(), controller->QMapToUnorderedMap(mediaAttributes));
    return;
}

void Window::onCreateMediaSuccess(const QString &msg) {

    removeRightPanelWidget();
    showStatusBarMessage("Creation Success: " + msg);
    onRefreshLibraryMediaList();
}

void Window::onCreateMediaFailure(const QString& errorMsg) {

    QMessageBox::warning(this, "Create Failed", "Failed to create media: " + errorMsg);
}


// === RICERCA (SLOT) ===

void Window::onSearchMedia() {
    QWidget* searchWidget = new View::Search::SearchWidget(controller, true);
    showSearchWidget(searchWidget);
}

void Window::onSearchAction(const Model::Library::SearchQuery& query) {
    controller->onSearchRequest(query);
}

void Window::onSearchMediaByName() {

    if (searchBar->text().isEmpty()) {
        showStatusBarMessage("Please input media name to search");
        return;
    }

    QString mediaName = searchBar->text();
    emit onSearchMediaByNameRequest(mediaName);
}


// === JSON (SLOT) ===

void Window::onSaveLibraryToFile() {

    // apri dialog per selezionare file per il salvataggio
    QString outputFile = QFileDialog::getSaveFileName(this, "Save Library", QDir::homePath(), "JSON Files (*.json)");
    if (outputFile.isEmpty()) return;

    if (controller->onSaveLibraryRequest(outputFile)) {
        showStatusBarMessage("Library saved to file: " + outputFile);
    }
    else {
        QMessageBox::warning(this, "Error", "Coult not save library to file: " + outputFile);
    }
}

void Window::onLoadLibraryFromFile() {

    // apri dialog per selezionare file da cui caricare libreria
    QString inputFile = QFileDialog::getOpenFileName(this, "Load Library", QDir::homePath(), "JSON Files (*.json)");
    if (inputFile.isEmpty()) return;

    if (controller->onLoadLibraryRequest(inputFile)) {
        onRefreshLibraryMediaList();
        onViewLibraryMediaList();
        showStatusBarMessage("Successfully loaded library from file: " + inputFile);
    }
    else {
        QMessageBox::warning(this, "Error", "Could not load library from file: " + inputFile);
    }

}

}

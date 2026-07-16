#ifndef VIEW_SEARCH_SEARCH_WIDGET_H
#define VIEW_SEARCH_SEARCH_WIDGET_H

#include "Controller/Controller.h"
#include "Model/Library/SearchQuery.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QDoubleSpinBox>


/** @brief SearchWidget
 *
 *  SearchWidget e' un custom widget utilizzato per la ricerca con filtri per i media attualmente in libreria.
 *  SearchWidget permette la ricerca dei media, utilizzando un QFormLayout permettendo la scelta di vari parametri di ricerca.
 *
 *  Ho disposto in un QButtonGroup la scelta del tipo di media, con il quale vengono aggiornati dinamicamente i parametri specifici
 *  al tipo selezionato per impostare ulteriori parametri di ricerca.
 *  La ricerca avviene mediante lo struct SearchQuery di Model::Library. Quando viene cliccato il bottone "Search", viene chiamato
 *  il metodo 'buildSearchQuery' per costruire il SearchQuery con i filtri impostati.
 *
 *  Dopodiche', viene emesso il segnale 'mediaEditsConfirmed' e l'operazione e' delegata al Controller.
 *
 */

namespace View {
namespace Search {

class SearchWidget : public QWidget {

    Q_OBJECT

public:

    // costruttore

    /**
     * @brief SearchWidget : costruttorie
     * @param c : puntatore al Controller
     * @param filters : abilita/disabilita filtri avanzati
     * @param name : nome del media
     * @param parent : parent widget
     */
    SearchWidget(Controller::Controller* c, bool filters, QString name = "", QWidget* parent = nullptr);

signals:

    /**
     * @brief confirmSearchFilters : segnala la richiesta di effettuare operazione di ricerca
     * @param query : filtri da applicare nella ricerca
     */
    void confirmSearchFilters(const Model::Library::SearchQuery& query);

    /**
     * @brief closed : segnala chiusura del widget
     */
    void closed();

private slots:

    /**
     * @brief onConfirmButtonClicked : gestisce richiesta di conferma filtri e inizio operazione ricerca
     */
    void onConfirmButtonClicked();

    /**
     * @brief onCancelButtonClicked : gestisce richiesta di annullamento operazione
     */
    void onCancelButtonClicked();

    void onTypeButtonSelected();

    /** @brief onAudioTypeSelected : gestisce richiesta di mostrare filti di ricerca Audio */
    void onAudioTypeSelected();
    /** @brief onVideoTypeSelected : gestisce richiesta di mostrare filti di ricerca Video */
    void onVideoTypeSelected();
    /** @brief onEBookTypeSelected : gestisce richiesta di mostrare filti di ricerca EBook */
    void onEBookTypeSelected();
    /** @brief onImageTypeSelected : gestisce richiesta di mostrare filti di ricerca Image */
    void onImageTypeSelected();

private:

    Controller::Controller* controller;
    bool allFiltersEnabled;
    Model::Library::SearchQuery query;
    QString mediaName;

    // layout principali
    QVBoxLayout* searchWidgetMainLayout;
    QFormLayout* searchWidgetFormLayout;
    QDialogButtonBox* searchWidgetButtonBox;

    // filtri di base
    QSpinBox* idFilter;
    QLineEdit* nameFilter;
    QLineEdit* formatFilter;
    QLineEdit* uploaderFilter;
    QSpinBox* minRatingFilter;
    QSpinBox* maxRatingFilter;

    // button group per il tipo
    QWidget* typeRadioButtonContainer;
    QHBoxLayout* typeRadioButtonLayout;
    QButtonGroup* typeRadioButtonGroup;
    QRadioButton* audioTypeButton;
    QRadioButton* videoTypeButton;
    QRadioButton* ebookTypeButton;
    QRadioButton* imageTypeButton;

    // attributi specifici di Audio
    QLineEdit* audioArtistFilter;
    QLineEdit* audioGenreFilter;

    // attributi specifici di Video
    QLineEdit* videoDirectorFilter;
    QLineEdit* videoGenreFilter;

    // attributi specifici di EBook
    QLineEdit* ebookAuthorFilter;
    QLineEdit* ebookPublisherFilter;

    // attributi specifici di Image
    QLineEdit* imageCreatorFilter;
    QLineEdit* imageLocationFilter;

    /** @brief setter per i filtri di ricerca comuni e specifici al tipo */
    void setupCommonFilters();
    void setupAudioFilters();
    void setupVideoFilters();
    void setupEBookFilters();
    void setupImageFilters();

    /** @brief disableSearchFilters : disabilita (reimpasta ai valori iniziali) i filtri avanzati */
    void disableSearchFilters();

    /**
     * @brief getSelectedRadioText : restituisce il tipo selezionato nel button group relativo al tipo di media
     * @return QString : nome del tipo di media
     */
    QString getSelectedRadioText() const;


    /**
     * @brief buildSearchQuery : costruisce il SearchQuery utilizzando i filtri applicati e delega l'operazione di ricerca al Controller
     */
    void buildSearchQuery();

};

}
}

#endif // VIEW_SEARCH_SEARCH_WIDGET_H

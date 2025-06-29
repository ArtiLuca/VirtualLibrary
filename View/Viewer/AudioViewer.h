#ifndef VIEW_VIEWER_AUDIO_VIEWER
#define VIEW_VIEWER_AUDIO_VIEWER

#include "Model/Media/Audio.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>
#include <QString>
#include <QMessageBox>

/** @brief AudioViewer
 *
 *  AudioViewer e' un custom widget utilizzato principalmente per la visualizzazione dei media di tipo Audio.
 *  Il suo costruttore prende come parametri un riferimento costante al media Audio da mostrare e il suo indice nella libreria.
 *
 *  Gli attributi del media Audio vengono mostrati tramite delle QLabel disposte in un QFormLayout.
 *  Oltre a mostrare gli attributi/valori del dato media Audio, AudioViewer dispone dei tre QPushButton 'scoreButton', 'scoreInfoButton' e 'closeButton'.
 *  I primi due sono emettono segnali al Controller per lo scoring del media Audio (che utilizza il visitor concreto Model::Visitors::ScoreVisitor)
 *  Il terzo emette il segnale 'closed' al Controller per chiudere il Viewer widget.
 */

namespace View {
namespace Viewer {

class AudioViewer : public QWidget {

    Q_OBJECT

public:

    /**
     * @brief AudioViewer : costruttore
     * @param audio : riferimento costante a media Audio
     * @param ind : indice del media Audio
     * @param parent : parent widget (con valore di default 'nullptr')
     */
    AudioViewer(const Model::Media::Audio& audio, unsigned int ind, QWidget* parent = nullptr);

    /**
     * @brief setScore : imposta lo score del media Audio (ottenuto tramite Model::Visitors::ScoreVisitor)
     * @param scoreValue : score numerico
     * @param scoreLabel : label qualitativo
     * @param scoreInfo : info su calcolo score
     */
    void setScore(float scoreValue, const QString& scoreLabel, const QString& scoreInfo);

signals:

    /**
     * @brief scoreRequested : segnale emesso quando e' richiesto il calcolo score del media
     * @param mediaIndex : indice del media
     * @param viewer : puntatore al viewer widget
     */
    void scoreRequested(unsigned int mediaIndex, QWidget* viewer);

    /**
     * @brief closed : segnale emesso quando viene chiuso il viewer widget
     */
    void closed();

private slots:

    /**
     * @brief onAudioScoreButtonClicked : gestisce richiesta di calcolo score per il media Audio
     */
    void onAudioScoreButtonClicked();

    /**
     * @brief onAudioScoreInfoButtonClicked : gestisce richiesta di mostrare info relative allo scoring del media Audio
     * @details button e' disabilitato finche' non viene prima calcolato lo score
     */
    void onAudioScoreInfoButtonClicked();

    /**
     * @brief onCloseClicked : gestisce richiesta di chiusura del viewer widget
     */
    void onCloseClicked();

private:

    unsigned int audioIndex;
    Model::Media::Audio audioCopy;

    // layout
    QVBoxLayout* audioViewerLayout;
    QHBoxLayout* audioButtonLayout;
    QFormLayout* audioFormLayout;

    // attibuti comuni
    QLabel* idLabel;
    QLabel* nameLabel;
    QLabel* ratingLabel;
    QLabel* pathLabel;
    QLabel* sizeLabel;
    QLabel* uploaderLabel;
    QLabel* formatLabel;

    // attributi specifici di Audio
    QLabel* artistLabel;
    QLabel* releaseYearLabel;
    QLabel* genreLabel;
    QLabel* albumLabel;
    QLabel* lengthLabel;
    QLabel* bitRateLabel;
    QLabel* sampleRateLabel;
    QLabel* bitDepthLabel;
    QLabel* channelsLabel;
    QLabel* collaboratorsLabel;

    // icona media Audio
    QLabel* audioIconLabel;
    QLabel* audioIconLabelText;

    // score del media Audio
    QLabel* audioScoreValue;
    QLabel* audioScoreLabel;
    QLabel* audioScoreInfo;

    // bottoni per operazioni media Audio
    QPushButton* scoreButton;
    QPushButton* scoreInfoButton;
    QPushButton* closeButton;


    /**
     * @brief setCommonAttributes : helper privato per impostare campi attributi comuni a tutti i tipi di media
     */
    void setCommonAttributes();

    /**
     * @brief setAudioAttributes : helper privato per impostare campi attributi specifici al tipo di media Audio
     */
    void setAudioAttributes();

};

}
}

#endif // VIEW_VIEWER_AUDIO_VIEWER

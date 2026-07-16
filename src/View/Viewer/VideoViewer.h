#ifndef VIEW_VIEWER_VIDEO_VIEWER_H
#define VIEW_VIEWER_VIDEO_VIEWER_H

#include "Model/Media/Video.h"

#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QPixmap>
#include <QString>

/** @brief VideoViewer
 *
 *  VideoViewer e' un custom widget utilizzato principalmente per la visualizzazione dei media di tipo Video.
 *  Il suo costruttore prende come parametri un riferimento costante al media Video da mostrare e il suo indice nella libreria.
 *
 *  Gli attributi del media Video vengono mostrati tramite delle QLabel disposte in un QFormLayout.
 *  Oltre a mostrare gli attributi/valori del dato media Video, VideoViewer dispone dei tre QPushButton 'scoreButton', 'scoreInfoButton' e 'closeButton'.
 *  I primi due sono emettono segnali al Controller per lo scoring del media Video (che utilizza il visitor concreto Model::Visitors::ScoreVisitor)
 *  Il terzo emette il segnale 'closed' al Controller per chiudere il Viewer widget.
 *
 *  Inoltre, VideoViewer dispone di un'ulteriore QPushButton 'videoDurationButton' che manda un segnale 'videoDurationRequested' al Controller per ottenere
 *  la durata del video (inizialmente espresse come totale in minuti) nel formato "x hours, y minutes".
 *
 */

namespace View {
namespace Viewer {

class VideoViewer : public QWidget {

    Q_OBJECT

public:

    /**
     * @brief VideoViewer : costruttore
     * @param video : riferimento costante a media Video
     * @param ind : indice del media Video
     * @param parent : parent widget (con valore di default 'nullptr')
     */
    VideoViewer(const Model::Media::Video& video, unsigned int ind, QWidget* parent = nullptr);

    /**
     * @brief setScore : imposta lo score del media Video (ottenuto tramite Model::Visitors::ScoreVisitor)
     * @param scoreValue : score numerico
     * @param scoreLabel : label qualitativo
     * @param scoreInfo : info su calcolo score
     */
    void setScore(float scoreValue, const QString& scoreLabel, const QString& scoreInfo);

    /**
     * @brief setVideoDuration : imposta la durata del film espressa in ore,min
     * @param duration : durata del film espressa in ore,min
     */
    void setVideoDuration(const QString& duration);

signals:

    /**
     * @brief scoreRequested : segnale emesso quando e' richiesto il calcolo score del media
     * @param mediaIndex : indice del media
     * @param viewer : puntatore al viewer widget
     */
    void scoreRequested(unsigned int mediaIndex, QWidget* viewer);

    /**
     * @brief videoDurationRequested : segnale emesso quando e' richiesta la durata in ore,min del video
     * @param mediaIndex : indice del media video
     * @param viewer : puntatore al viewer widget
     */
    void videoDurationRequested(unsigned int mediaIndex, QWidget* viewer);

    /**
     * @brief closed : segnale emesso quando viene chiuso il viewer widget
     */
    void closed();

private slots:

    /**
     * @brief onVideoScoreButtonClicked : gestisce richiesta di calcolo score per il media Video
     */
    void onVideoScoreButtonClicked();

    /**
     * @brief onVideoScoreInfoButtonClicked : gestisce richiesta di mostrare info relative allo scoring del media Video
     * @details button e' disabilitato finche' non viene prima calcolato lo score
     */
    void onVideoScoreInfoButtonClicked();

    /**
     * @brief onVideoDurationButtonClicked : gestisce richiesta di esprimere durata totale del media Video in ore, min
     */
    void onVideoDurationButtonClicked();

    /**
     * @brief onCloseClicked : gestisce richiesta di chiusura del viewer widget
     */
    void onCloseClicked();

private:

    unsigned int videoIndex;
    Model::Media::Video videoCopy;

    // layout
    QVBoxLayout* videoViewerLayout;
    QHBoxLayout* videoButtonLayout;
    QFormLayout* videoFormLayout;

    QWidget* resolutionContainer;
    QHBoxLayout* resolutionLayout;

    // attributi comuni
    QLabel* idLabel;
    QLabel* nameLabel;
    QLabel* ratingLabel;
    QLabel* pathLabel;
    QLabel* sizeLabel;
    QLabel* uploaderLabel;
    QLabel* formatLabel;

    // attributi specifici di Video
    QLabel* directorLabel;
    QLabel* genreLabel;
    QLabel* releaseYearLabel;
    QLabel* lengthLabel;
    QLabel* framerateLabel;
    QLabel* resolutionWidthLabel;
    QLabel* resolutionHeightLabel;
    QLabel* colordepthLabel;
    QLabel* languagesLabel;
    QLabel* subtitlesLabel;

    // icona media Video
    QLabel* videoIconLabel;
    QLabel* videoIconTextLabel;


    // durate del media Video
    QLabel* videoDurationLabel;

    // score del media Video
    QLabel* videoScoreValue;
    QLabel* videoScoreLabel;
    QLabel* videoScoreInfo;

    QPushButton* scoreButton;
    QPushButton* scoreInfoButton;
    QPushButton* videoDurationButton;
    QPushButton* closeButton;

    /**
     * @brief setCommonAttributes : helper privato per impostare campi attributi comuni a tutti i tipi di media
     */
    void setCommonAttributes();

    /**
     * @brief setVideoAttributes : helper privato per impostare campi attributi specifici al tipo di media Video
     */
    void setVideoAttributes();

};

}
}

#endif // VIEW_VIEWER_VIDEO_VIEWER_H

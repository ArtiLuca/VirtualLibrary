#ifndef VIEW_VIEWER_IMAGE_VIEWER_H
#define VIEW_VIEWER_IMAGE_VIEWER_H

#include "Model/Media/Image.h"

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


/** @brief ImageViewer
 *
 *  ImageViewer e' un custom widget utilizzato principalmente per la visualizzazione dei media di tipo Image.
 *  Il suo costruttore prende come parametri un riferimento costante al media Image da mostrare e il suo indice nella libreria.
 *
 *  Gli attributi del media Image vengono mostrati tramite delle QLabel disposte in un QFormLayout.
 *  Oltre a mostrare gli attributi/valori del dato media Image, ImageViewer dispone dei tre QPushButton 'scoreButton', 'scoreInfoButton' e 'closeButton'.
 *  I primi due sono emettono segnali al Controller per lo scoring del media Image (che utilizza il visitor concreto Model::Visitors::ScoreVisitor)
 *  Il terzo emette il segnale 'closed' al Controller per chiudere il Viewer widget.
 *
 */

namespace View {
namespace Viewer {

class ImageViewer : public QWidget {

    Q_OBJECT

public:

    /**
     * @brief ImageViewer : costruttore, inizializza i campi dati privati
     * @param image : riferimento costante al media Image
     * @param ind : indice del media image
     * @param parent : parent widget (con valore di default 'nullptr')
     */
    ImageViewer(const Model::Media::Image& image, unsigned int ind, QWidget* parent = nullptr);

    /**
     * @brief setScore : imposta lo score del media EBook (ottenuto tramite Model::Visitors::ScoreVisitor)
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
     * @brief onImageScoreButtonClicked : gestisce richiesta di calcolo score per il media Image
     */
    void onImageScoreButtonClicked();

    /**
     * @brief onImageScoreInfoButtonClicked : gestisce richiesta di mostrare info relative allo scoring del media Image
     * @details button e' disabilitato finche' non viene prima calcolato lo score
     */
    void onImageScoreInfoButtonClicked();

    /**
     * @brief onCloseClicked : gestisce richiesta di chiusura del viewer widget
     */
    void onCloseClicked();

private:

    unsigned int imageIndex;
    Model::Media::Image imageCopy;

    // layout
    QVBoxLayout* imageViewerLayout;
    QHBoxLayout* imageButtonLayout;
    QFormLayout* imageFormLayout;

    QWidget* resolutionContainer;
    QHBoxLayout* resolutionLayout;

    QWidget* aspectRatioContainer;
    QHBoxLayout* aspectRatioLayout;

    // attibuti comuni
    QLabel* idLabel;
    QLabel* nameLabel;
    QLabel* ratingLabel;
    QLabel* pathLabel;
    QLabel* sizeLabel;
    QLabel* uploaderLabel;
    QLabel* formatLabel;

    // attributi specifici di Image
    QLabel* dateCreatedLabel;
    QLabel* creatorLabel;
    QLabel* categoryLabel;
    QLabel* resolutionWidthLabel;
    QLabel* resolutionHeightLabel;
    QLabel* aspectWidthLabel;
    QLabel* aspectHeightLabel;
    QLabel* bitdepthLabel;
    QLabel* compressionLabel;
    QLabel* locationTakenLabel;

    // icona media Image
    QLabel* imageIconLabel;
    QLabel* imageIconLabelText;

    // score del media Image
    QLabel* imageScoreValue;
    QLabel* imageScoreLabel;
    QLabel* imageScoreInfo;

    // bottoni per operazioni media Image
    QPushButton* scoreButton;
    QPushButton* scoreInfoButton;
    QPushButton* closeButton;

    /**
     * @brief setCommonAttributes : helper privato per impostare campi attributi comuni a tutti i tipi di media
     */
    void setCommonAttributes();

    /**
     * @brief setImageAttributes : helper privato per impostare campi attributi specifici al tipo di media Image
     */
    void setImageAttributes();
};

}
}



#endif // VIEW_VIEWER_IMAGE_VIEWER_H


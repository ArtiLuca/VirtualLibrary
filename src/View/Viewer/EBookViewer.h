#ifndef VIEW_VIEWER_EBOOK_VIEWER_H
#define VIEW_VIEWER_EBOOK_VIEWER_H

#include "Model/Media/EBook.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QPixmap>
#include <QString>


/** @brief EBookViewer
 *
 *  EBookViewer e' un custom widget utilizzato principalmente per la visualizzazione dei media di tipo EBook.
 *  Il suo costruttore prende come parametri un riferimento costante al media EBook da mostrare e il suo indice nella libreria.
 *
 *  Gli attributi del media EBook vengono mostrati tramite delle QLabel disposte in un QFormLayout.
 *  Oltre a mostrare gli attributi/valori del dato media EBook, EBookViewer dispone dei tre QPushButton 'scoreButton', 'scoreInfoButton' e 'closeButton'.
 *  I primi due sono emettono segnali al Controller per lo scoring del media EBook (che utilizza il visitor concreto Model::Visitors::ScoreVisitor)
 *  Il terzo emette il segnale 'closed' al Controller per chiudere il Viewer widget.
 *
 *  Inoltre, EBookViewer dispone di un'ulteriore QPushButton 'isbnCheckButton' che manda il segnale 'isbnValidateRequest' al Controller per verificare la validita'
 *  dell'ISBN del media EBook, utilizzando l'algoritmo ISBN-13 checksum definito nella classe EBook.
 */

namespace View {
namespace Viewer {

class EBookViewer : public QWidget {

    Q_OBJECT

public:

    /**
     * @brief EBookViewer : costruttore
     * @param ebook : riferimento costante a media EBook
     * @param ind : indice del media EBook
     * @param parent : parent widget (con valore di default 'nullptr')
     */
    EBookViewer(const Model::Media::EBook& ebook, unsigned int ind, QWidget* parent = nullptr);

    /**
     * @brief setScore : imposta lo score del media EBook (ottenuto tramite Model::Visitors::ScoreVisitor)
     * @param scoreValue : score numerico
     * @param scoreLabel : label qualitativo
     * @param scoreInfo : info su calcolo score
     */
    void setScore(float scoreValue, const QString& scoreLabel, const QString& scoreInfo);

    /**
     * @brief setEBookISBNValidation : imposta label 'ebookValidISBN' in base a ISBN valido o non valido
     * @param checkISBN : stringa contenente ISBN e se e' valido o non valido
     */
    void setEBookISBNValidation(const QString& checkISBN);

signals:

    /**
     * @brief scoreRequested : segnale emesso quando e' richiesto il calcolo score del media
     * @param mediaIndex : indice del media
     * @param viewer : puntatore al viewer widget
     */
    void scoreRequested(unsigned int mediaIndex, QWidget* viewer);

    /**
     * @brief isbnValidateRequest : segnale emesso quando si vuole verificare validita' ISBN del media EBook
     * @param mediaIndex : indice del media EBook
     * @param viewer : puntatore al viewer widget
     */
    void isbnValidateRequest(unsigned int mediaIndex, QWidget* viewer);

    /**
     * @brief closed : segnale emesso quando viene chiuso il viewer widget
     */
    void closed();

private slots:

    /**
     * @brief onEBookScoreButtonClicked : gestisce richiesta di calcolo score per il media EBook
     */
    void onEBookScoreButtonClicked();

    /**
     * @brief onEBookScoreInfoButtonClicked : gestisce richiesta di mostrare info relative allo scoring del media EBook
     * @details button e' disabilitato finche' non viene prima calcolato lo score
     */
    void onEBookScoreInfoButtonClicked();

    /**
     * @brief onCheckISBNButtonClicked : gestisce richiesta di check validita' dell'ISBN del media EBook
     */
    void onCheckISBNButtonClicked();

    /**
     * @brief onCloseClicked : gestisce richiesta di chiusura del viewer widget
     */
    void oncloseButtonClicked();

private:

    unsigned int ebookIndex;
    Model::Media::EBook ebookCopy;

    // layout
    QVBoxLayout* ebookViewerLayout;
    QHBoxLayout* ebookButtonLayout;
    QFormLayout* ebookFormLayout;

    // attributi comuni
    QLabel* idLabel;
    QLabel* nameLabel;
    QLabel* ratingLabel;
    QLabel* pathLabel;
    QLabel* sizeLabel;
    QLabel* uploaderLabel;
    QLabel* formatLabel;

    // attributi specifici di EBook
    QLabel* authorLabel;
    QLabel* publisherLabel;
    QLabel* releaseYearLabel;
    QLabel* isbnLabel;
    QLabel* lengthLabel;
    QLabel* categoryLabel;
    QLabel* languageLabel;
    QLabel* coverPathLabel;
    QLabel* hasImagesLabel;

    // icona media EBook
    QLabel* ebookIconLabel;
    QLabel* ebookIconTextLabel;

    // score del media EBook
    QLabel* ebookScoreValue;
    QLabel* ebookScoreLabel;
    QLabel* ebookScoreInfo;

    // check validita' ISBN
    QLabel* ebookValidISBN;

    QPushButton* scoreButton;
    QPushButton* scoreInfoButton;
    QPushButton* isbnCheckButton;
    QPushButton* closeButton;

    /**
     * @brief setCommonAttributes : helper privato per impostare campi attributi comuni a tutti i tipi di media
     */
    void setCommonAttributes();

    /**
     * @brief setEBookAttributes : helper privato per impostare campi attributi specifici al tipo di media EBook
     */
    void setEBookAttributes();


};

}
}

#endif // VIEW_VIEWER_EBOOK_VIEWER_H

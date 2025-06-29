#ifndef VIEW_EDITOR_EBOOK_EDITOR_H
#define VIEW_EDITOR_EBOOK_EDITOR_H

#include "Model/Media/EBook.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QMap>

/** @brief EBookEditor
 *
 *  EBookEditor e' un custom widget utilizzato per la modifica dei media di tipo EBook.
 *  EBookEditor mostra gli attributi del media EBook in un QFormLayout, permettendo la loro modifica tramite QLineEdit, QSpinBox, QDoubleSpinBox e QCheckBox.
 *
 *  Dispone di due pulsanti: "Confirm" per confermare le modifiche, e "Cancel" per annullare l'operazione.
 *  Quando viene cliccato il pulsante "Confirm", gli attributi vengono raccolti in un oggetto del tipo QMap<QString, QString> e poi viene emesso al Controller il segnale 'mediaEditsConfirmed'.
 *  EBookEditor non gestisce direttamente la modifica/validazione degli attributi, ma si limita a rappresentare l'interfaccia per la modifica.
 *  Delega l'operazione di modifica e la conversione (QMap -> std::undordered_map) al Controller, e quindi al moodello.
 *
 *  Inoltre, per facilitare l'operazione di modifica, EBookEditor dispone del helper privato 'setEBookToolTips' per mostrare mostrare informazioni utili per la modifica di un media EBook.
 */


namespace View {
namespace Editor {

class EBookEditor : public QWidget {

    Q_OBJECT

public:

    /**
     * @brief EBookEditor : costruttore, imposta il layout princiale, imposta il form con gli attributi del media EBook e collega i segnali/slot
     * @param ebook : riferimento costante al media EBook da modificare
     * @param ind : indice del media EBook
     * @param parent : parent widget
     */
    EBookEditor(
        const Model::Media::EBook& ebook,
        unsigned int ind,
        QWidget* parent = nullptr
    );

signals:

    /**
     * @brief mediaEditsConfirmed : segnala la richiesta di modifica del media
     * @param ind : indice del media da modificare
     * @param edits : attributi del media (con le modifiche)
     */
    void mediaEditsConfirmed(unsigned int ind, QMap<QString, QString> edits);

    /**
     * @brief closed : segnala chiusura del widget
     */
    void closed();

private slots:

    /**
     * @brief onConfirmButtonClicked : gestisce richiesta di conferma modifiche
     * @details raccoglie gli attributi del media EBook dal QFormLayout e le memorizza in un QMap<QString, QString>
     */
    void onConfirmButtonClicked();

    /**
     * @brief onCancelButtonClicked : gestisce richiesta di annullamento dell'operazione di modifica
     */
    void onCancelButtonClicked();

private:

    unsigned int ebookIndex;
    Model::Media::EBook ebookCopy;

    QVBoxLayout* ebookEditorMainLayout;
    QFormLayout* ebookEditorFormLayout;
    QDialogButtonBox* ebookEditorButtonBox;

    QLabel* editorTypeLabel;

    // attributi AbstractFile
    QLineEdit* idEdit;
    QLineEdit* pathEdit;
    QDoubleSpinBox* sizeSpinBox;

    // attributi AbstractMedia
    QLineEdit* nameEdit;
    QLineEdit* uploaderEdit;
    QComboBox* formatComboBox;
    QSpinBox* ratingSpinBox;

    // attributi EBook
    QLineEdit* authorEdit;
    QLineEdit* publisherEdit;
    QSpinBox* releaseYearSpinBox;
    QLineEdit* isbnEdit;
    QSpinBox* lengthSpinBox;
    QLineEdit* categoryEdit;
    QLineEdit* languageEdit;
    QLineEdit* coverPathEdit;
    QCheckBox* hasImagesCheckBox;

    /** @brief setAbstractFileAttributes : imposta attributi EBook ereditati da AbstractFile nel QFormLayout */
    void setAbstractFileAttributes();
    /** @brief setAbstractMediaAttributes : imposta attributi EBook ereditati da AbstractMedia nel QFormLayout */
    void setAbstractMediaAttributes();
    /** @brief setEBookAttributes : imposta attributi specifici al media EBook nel QFormLayout */
    void setEBookAttributes();
    /** @brief setEBookEditorToolTips : imposta tooltip per modifiche attributi media EBook */
    void setEBookEditorToolTips();


};

}
}

#endif // VIEW_EDITOR_EBOOK_EDITOR_H

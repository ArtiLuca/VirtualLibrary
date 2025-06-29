#ifndef VIEW_EDITOR_IMAGE_EDITOR_H
#define VIEW_EDITOR_IMAGE_EDITOR_H

#include "Model/Media/Image.h"

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

/** @brief ImageEditor
 *
 *  ImageEditor e' un custom widget utilizzato per la modifica dei media di tipo Image.
 *  ImageEditor mostra gli attributi del media Image in un QFormLayout, permettendo la loro modifica tramite QLineEdit, QSpinBox, QDoubleSpinBox e QCheckBox.
 *
 *  Dispone di due pulsanti: "Confirm" per confermare le modifiche, e "Cancel" per annullare l'operazione.
 *  Quando viene cliccato il pulsante "Confirm", gli attributi vengono raccolti in un oggetto del tipo QMap<QString, QString> e poi viene emesso al Controller il segnale 'mediaEditsConfirmed'.
 *  ImageEditor non gestisce direttamente la modifica/validazione degli attributi, ma si limita a rappresentare l'interfaccia per la modifica.
 *  Delega l'operazione di modifica e la conversione (QMap -> std::undordered_map) al Controller, e quindi al moodello.
 *
 *  Inoltre, per facilitare l'operazione di modifica, ImageEditor dispone del helper privato 'setImageToolTips' per mostrare mostrare informazioni utili per la modifica di un media Image.
 */


namespace View {
namespace Editor {

class ImageEditor : public QWidget {

    Q_OBJECT

public:

    /**
     * @brief ImageEditor : costruttore, imposta il layout princiale, imposta il form con gli attributi del media Image e collega i segnali/slot
     * @param image : riferimento costante al media Image da modificare
     * @param ind : indice del media Image
     * @param parent : parent widget
     */
    ImageEditor(
        const Model::Media::Image& image,
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
     * @details raccoglie gli attributi del media Audio dal QFormLayout e le memorizza in un QMap<QString, QString>
     */
    void onConfirmButtonClicked();

    /**
     * @brief onCancelButtonClicked : gestisce richiesta di annullamento dell'operazione di modifica
     */
    void onCancelButtonClicked();

private:

    unsigned int imageIndex;
    Model::Media::Image imageCopy;

    QVBoxLayout* imageEditorMainLayout;
    QFormLayout* imageEditorFormLayout;
    QDialogButtonBox* imageEditorButtonBox;

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

    // attributi Image
    QLineEdit* createdEdit;
    QLineEdit* creatorEdit;
    QLineEdit* categoryEdit;
    QSpinBox* bitdepthSpinBox;
    QCheckBox* compressedCheckBox;
    QLineEdit* locationEdit;

    // risoluzione Image
    QWidget* resolutionContainer;
    QHBoxLayout* resolutionLayout;
    QSpinBox* resolutionWidthSpinBox;
    QSpinBox* resolutionHeightSpinBox;

    // aspect ratio Image
    QWidget* aspectRatioContainer;
    QHBoxLayout* aspectRatioLayout;
    QSpinBox* aspectWidthSpinBox;
    QSpinBox* aspectHeightSpinBox;

    /** @brief setAbstractFileAttributes : imposta attributi Image ereditati da AbstractFile nel QFormLayout */
    void setAbstractFileAttributes();
    /** @brief setAbstractMediaAttributes : imposta attributi Image ereditati da AbstractMedia nel QFormLayout */
    void setAbstractMediaAttributes();
    /** @brief setImageAttributes : imposta attributi specifici al media Image nel QFormLayout */
    void setImageAttributes();
    /** @brief setImageEditorToolTips : imposta tooltip per modifiche attributi media Image */
    void setImageEditorToolTips();
};

}
}

#endif // VIEW_EDITOR_IMAGE_EDITOR_H

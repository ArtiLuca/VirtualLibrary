#ifndef VIEW_EDITOR_VIDEO_EDITOR_H
#define VIEW_EDITOR_VIDEO_EDITOR_H

#include "Model/Media/Video.h"

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
#include <QMap>

/** @brief VideoEditor
 *
 *  VideoEditor e' un custom widget utilizzato per la modifica dei media di tipo Video.
 *  VideoEditor mostra gli attributi del media Video in un QFormLayout, permettendo la loro modifica tramite QLineEdit, QSpinBox e QDoubleSpinBox.
 *
 *  Dispone di due pulsanti: "Confirm" per confermare le modifiche, e "Cancel" per annullare l'operazione.
 *  Quando viene cliccato il pulsante "Confirm", gli attributi vengono raccolti in un oggetto del tipo QMap<QString, QString> e poi viene emesso al Controller il segnale 'mediaEditsConfirmed'.
 *  VideoEditor non gestisce direttamente la modifica/validazione degli attributi, ma si limita a rappresentare l'interfaccia per la modifica.
 *  Delega l'operazione di modifica e la conversione (QMap -> std::undordered_map) al Controller, e quindi al moodello.
 *
 *  Inoltre, per facilitare l'operazione di modifica, VideoEditor dispone del helper privato 'setVideoToolTips' per mostrare mostrare informazioni utili per la modifica di un media Video.
 */


namespace View {
namespace Editor {

class VideoEditor : public QWidget {

    Q_OBJECT

public:

    /**
     * @brief VideoEditor : costruttore, imposta il layout princiale, imposta il form con gli attributi del media Video e collega i segnali/slot
     * @param video : riferimento costante al media Video da modificare
     * @param ind : indice del media Video
     * @param parent : parent widget
     */
    VideoEditor(
        const Model::Media::Video& video,
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
     * @details raccoglie gli attributi del media Video dal QFormLayout e le memorizza in un QMap<QString, QString>
     */
    void onConfirmButtonClicked();

    /**
     * @brief onCancelButtonClicked : gestisce richiesta di annullamento dell'operazione di modifica
     */
    void onCancelButtonClicked();

private:

    unsigned int videoIndex;
    Model::Media::Video videoCopy;

    QVBoxLayout* videoEditorMainLayout;
    QFormLayout* videoEditorFormLayout;
    QDialogButtonBox* videoEditorButtonBox;

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

    // attributi Video
    QLineEdit* directorEdit;
    QLineEdit* genreEdit;
    QSpinBox* releaseYearSpinBox;
    QSpinBox* lengthSpinBox;
    QSpinBox* framerateSpinBox;
    QSpinBox* colordepthSpinBox;
    QLineEdit* subtitlesEdit;
    QLineEdit* languageEdit;

    // risoluzione Video
    QWidget* resolutionContainer;
    QHBoxLayout* resolutionLayout;
    QSpinBox* resolutionWidthSpinBox;
    QSpinBox* resolutionHeightSpinBox;

    /** @brief setAbstractFileAttributes : imposta attributi Video ereditati da AbstractFile nel QFormLayout */
    void setAbstractFileAttributes();
    /** @brief setAbstractMediaAttributes : imposta attributi Video ereditati da AbstractMedia nel QFormLayout */
    void setAbstractMediaAttributes();
    /** @brief setVideoAttributes : imposta attributi specifici al media Video nel QFormLayout */
    void setVideoAttributes();
    /** @brief setVideoEditorToolTips : imposta tooltip per modifiche attributi media Video */
    void setVideoEditorToolTips();
};

}
}

#endif // VIEW_EDITOR_VIDEO_EDITOR_H

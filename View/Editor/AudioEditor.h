#ifndef VIEW_EDITOR_AUDIO_EDITOR_H
#define VIEW_EDITOR_AUDIO_EDITOR_H

#include "Model/Media/Audio.h"

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


/** @brief AudioEditor
 *
 *  AudioEditor e' un custom widget utilizzato per la modifica dei media di tipo Audio.
 *  AudioEditor mostra gli attributi del media Audio in un QFormLayout, permettendo la loro modifica tramite QLineEdit, QSpinBox e QDoubleSpinBox.
 *
 *  Dispone di due pulsanti: "Confirm" per confermare le modifiche, e "Cancel" per annullare l'operazione.
 *  Quando viene cliccato il pulsante "Confirm", gli attributi vengono raccolti in un oggetto del tipo QMap<QString, QString> e poi viene emesso al Controller il segnale 'mediaEditsConfirmed'.
 *  AudioEditor non gestisce direttamente la modifica/validazione degli attributi, ma si limita a rappresentare l'interfaccia per la modifica.
 *  Delega l'operazione di modifica e la conversione (QMap -> std::undordered_map) al Controller, e quindi al moodello.
 *
 *  Inoltre, per facilitare l'operazione di modifica, AudioEditor dispone del helper privato 'setAudioToolTips' per mostrare mostrare informazioni utili per la modifica di un media Audio.
 */

namespace View {
namespace Editor {

class AudioEditor : public QWidget {

    Q_OBJECT

public:

    /**
     * @brief AudioEditor : costruttore, imposta il layout princiale, imposta il form con gli attributi del media Audio e collega i segnali/slot
     * @param audio : riferimento costante al media Audio da modificare
     * @param ind : indice del media Audio
     * @param parent : parent widget
     */
    AudioEditor(
        const Model::Media::Audio& audio,
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

    unsigned int audioIndex;
    Model::Media::Audio audioCopy;

    QVBoxLayout* audioEditorMainLayout;
    QFormLayout* audioEditorFormLayout;
    QDialogButtonBox* audioEditorButtonBox;

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

    // attributi Audio
    QLineEdit* artistEdit;
    QLineEdit* genreEdit;
    QLineEdit* albumEdit;
    QSpinBox* releaseYearSpinBox;
    QSpinBox* lengthSpinBox;
    QSpinBox* bitrateSpinBox;
    QDoubleSpinBox* sampleRateSpinBox;
    QSpinBox* bitdepthSpinBox;
    QSpinBox* channelsSpinBox;
    QLineEdit* collaboratorsEdit;

    /** @brief setAbstractFileAttributes : imposta attributi Audio ereditati da AbstractFile nel QFormLayout */
    void setAbstractFileAttributes();
    /** @brief setAbstractMediaAttributes : imposta attributi Audio ereditati da AbstractMedia nel QFormLayout */
    void setAbstractMediaAttributes();
    /** @brief setAudioAttributes : imposta attributi specifici al media Audio nel QFormLayout */
    void setAudioAttributes();
    /** @brief setAudioEditorToolTips : imposta tooltip per modifiche attributi media Audio */
    void setAudioEditorToolTips();
};

}
}

#endif // VIEW_EDITOR_AUDIO_EDITOR_H

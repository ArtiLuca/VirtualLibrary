#ifndef VIEW_CREATOR_AUDIO_CREATOR_H
#define VIEW_CREATOR_AUDIO_CREATOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QMap>


/** @brief AudioCreator
 *
 *  AudioCreator e' un custom widget dedicato alla creazione dei media di tipo Audio.
 *
 *  AudioCreator imposta in un QFormLayout tutti gli attributi di un media Audio, resi modificabili tramite QLineEdit, QSpinBox e QDoubleSpinBox.
 *  L'unico campo "read-only" e' quello relativo all'identificatore univoco del nuovo media, che viene automaticamente incrementato e provveduto dal costruttore di AbstractFile.
 *
 *  AudioCreator dispone di metodi helper privati, per impostare nel QFormLayout gli attributi del media Audio e di un metodo 'setAudioToolTips' per aggiungere informazioni utili all'utente
 *  durante l'input degli attributi del media Audio.
 *
 *  Quando l'utente conferma gli attributi per il nuovo media Audio (pulsante "Create"), viene utilizzato il metodo 'onCreateButtonClicked' per raccogliere gli attributi in un oggetto del tipo QMap<QString, QString>.
 *  Poi viene emesso il segnale 'createRequested', che delega la conversione (QMap -> std::unordered_map) e creazione al Controller (e quindi al Manager).
 */

namespace View {
namespace Creator {

class AudioCreator : public QWidget {

    Q_OBJECT

public:

    // costanti statiche per differenziare campi obbligatori/opzionali
    static const QString REQUIRED_ATTRIBUTE_STYLE;
    static const QString OPTIONAL_ATTRIBUTE_STYLE;

    /**
     * @brief AudioCreator : costruttore, inizializza il layout principale e il form per gli attributi, inserendo valori di default per un media Audio
     * @param parent : parent widget (di default 'nullptr')
     */
    explicit AudioCreator(QWidget* parent = nullptr);

signals:

    /**
     * @brief createRequested : segnala la creazione di un nuovo media
     * @param attributes : mappa di attributi del nuovo media
     */
    void createRequested(QMap<QString, QString> attributes);

    /**
     * @brief createCancelled : segnala annullamente operazione creazione
     */
    void createCancelled();

private slots:

    /**
     * @brief onCreateButtonClicked : gestisce conferma degli attributi per il nuovo media Audio. Raccoglie gli attributi in una QMap<QString, QString> e notifica il Controller con il segnale 'createRequested'.
     */
    void onCreateButtonClicked();

    /**
     * @brief onCancelButtonClicked : gestisce richiesta di annullamento operazione creazione
     */
    void onCancelButtonClicked();

private:

    QVBoxLayout* audioCreatorMainLayout;
    QFormLayout* audioCreatorFormLayout;
    QDialogButtonBox* audioCreatorButtonBox;

    QLabel* creatorTypeLabel;

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

    /** @brief setAbstractFileAttributes : helper privato per impostare campi Audio ereditati da AbstractFile */
    void setAbstractFileAttributes();
    /** @brief setAbstractMediaAttributes : helper privato per impostare campi Audio ereditati da AbstractMedia */
    void setAbstractMediaAttributes();
    /** @brief setAudioAttributes : helper privato per impostare campi Audio */
    void setAudioAttributes();
    /** @brief setAudioToolTips : imposta tooltip con informazioni utili all'utente relativi agli attributi del media Audio */
    void setAudioToolTips();


};

}
}

#endif // VIEW_CREATOR_AUDIO_CREATOR_H

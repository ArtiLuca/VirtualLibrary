#ifndef VIEW_CREATOR_VIDEO_CREATOR_H
#define VIEW_CREATOR_VIDEO_CREATOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QMap>


/** @brief VideoCreator
 *
 *  VideoCreator e' un custom widget dedicato alla creazione dei media di tipo Video.
 *
 *  VideoCreator imposta in un QFormLayout tutti gli attributi di un media Video, resi modificabili tramite QLineEdit, QSpinBox e QDoubleSpinBox.
 *  L'unico campo "read-only" e' quello relativo all'identificatore univoco del nuovo media, che viene automaticamente incrementato e provveduto dal costruttore di AbstractFile.
 *
 *  VideoCreator dispone di metodi helper privati, per impostare nel QFormLayout gli attributi del media Video e di un metodo 'setVideoToolTips' per aggiungere informazioni utili all'utente
 *  durante l'input degli attributi del media Video.
 *
 *  Quando l'utente conferma gli attributi per il nuovo media Video (pulsante "Create"), viene utilizzato il metodo 'onCreateButtonClicked' per raccogliere gli attributi in un oggetto del tipo QMap<QString, QString>.
 *  Poi viene emesso il segnale 'createRequested', che delega la conversione (QMap -> std::unordered_map) e creazione al Controller (e quindi al Manager).
 */

namespace View {
namespace Creator {

class VideoCreator : public QWidget {

    Q_OBJECT

public:

    // costanti statiche per differenziare campi obbligatori/opzionali
    static const QString REQUIRED_ATTRIBUTE_STYLE;
    static const QString OPTIONAL_ATTRIBUTE_STYLE;

    /**
     * @brief VideoCreator : costruttore, inizializza il layout principale e il form per gli attributi, inserendo valori di default per un media Video
     * @param parent : parent widget (di default 'nullptr')
     */
    explicit VideoCreator(QWidget* parent = nullptr);

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
     * @brief onCreateButtonClicked : gestisce conferma degli attributi per il nuovo media Video. Raccoglie gli attributi in una QMap<QString, QString> e notifica il Controller con il segnale 'createRequested'.
     */
    void onCreateButtonClicked();

    /**
     * @brief onCancelButtonClicked : gestisce richiesta di annullamento operazione creazione
     */
    void onCancelButtonClicked();

private:

    QVBoxLayout* videoCreatorMainLayout;
    QFormLayout* videoCreatorFormLayout;
    QDialogButtonBox* videoCreatorButtonBox;

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

    /** @brief setAbstractFileAttributes : helper privato per impostare campi Video ereditati da AbstractFile */
    void setAbstractFileAttributes();
    /** @brief setAbstractMediaAttributes : helper privato per impostare campi Video ereditati da AbstractMedia */
    void setAbstractMediaAttributes();
    /** @brief setVideoAttributes : helper privato per impostare campi Video */
    void setVideoAttributes();

    /** @brief setVideoToolTips : imposta tooltip con informazioni utili all'utente relativi agli attributi del media Video */
    void setVideoToolTips();
};

}
}

#endif // VIEW_CREATOR_VIDEO_CREATOR_H

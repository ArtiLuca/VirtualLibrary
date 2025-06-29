#ifndef VIEW_CREATOR_IMAGE_CREATOR_H
#define VIEW_CREATOR_IMAGE_CREATOR_H

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
#include <QCheckBox>
#include <QMap>


/** @brief ImageCreator
 *
 *  ImageCreator e' un custom widget dedicato alla creazione dei media di tipo Image.
 *
 *  VideoCreator imposta in un QFormLayout tutti gli attributi di un media Image, resi modificabili tramite QLineEdit, QSpinBox, QDoubleSpinBox e QCheckBox.
 *  L'unico campo "read-only" e' quello relativo all'identificatore univoco del nuovo media, che viene automaticamente incrementato e provveduto dal costruttore di AbstractFile.
 *
 *  ImageCreator dispone di metodi helper privati, per impostare nel QFormLayout gli attributi del media Image e di un metodo 'setImageToolTips' per aggiungere informazioni utili all'utente
 *  durante l'input degli attributi del media Image.
 *
 *  Quando l'utente conferma gli attributi per il nuovo media Image (pulsante "Create"), viene utilizzato il metodo 'onCreateButtonClicked' per raccogliere gli attributi in un oggetto del tipo QMap<QString, QString>.
 *  Poi viene emesso il segnale 'createRequested', che delega la conversione (QMap -> std::unordered_map) e creazione al Controller (e quindi al Manager).
 */

namespace View {
namespace Creator {

class ImageCreator : public QWidget {

    Q_OBJECT

public:

    // costanti statiche per differenziare campi obbligatori/opzionali
    static const QString REQUIRED_ATTRIBUTE_STYLE;
    static const QString OPTIONAL_ATTRIBUTE_STYLE;

    /**
     * @brief ImageCreator : costruttore, inizializza il layout principale e il form per gli attributi, inserendo valori di default per un media Image
     * @param parent : parent widget (di default 'nullptr')
     */
    explicit ImageCreator(QWidget* parent = nullptr);

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
     * @brief onCreateButtonClicked : gestisce conferma degli attributi per il nuovo media Image. Raccoglie gli attributi in una QMap<QString, QString> e notifica il Controller con il segnale 'createRequested'.
     */
    void onCreateButtonClicked();

    /**
     * @brief onCancelButtonClicked : gestisce richiesta di annullamento operazione creazione
     */
    void onCancelButtonClicked();

private:

    QVBoxLayout* imageCreatorMainLayout;
    QFormLayout* imageCreatorFormLayout;
    QDialogButtonBox* imageCreatorButtonBox;

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

    /** @brief setAbstractFileAttributes : helper privato per impostare campi Image ereditati da AbstractFile */
    void setAbstractFileAttributes();
    /** @brief setAbstractMediaAttributes : helper privato per impostare campi Image ereditati da AbstractMedia */
    void setAbstractMediaAttributes();
    /** @brief setImageAttributes : helper privato per impostare campi Image */
    void setImageAttributes();
    /** @brief setImageToolTips : imposta tooltip con informazioni utili all'utente relativi agli attributi del media Image */
    void setImageToolTips();
};

}
}

#endif // VIEW_CREATOR_IMAGE_CREATOR_H

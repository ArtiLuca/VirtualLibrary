#ifndef VIEW_CREATOR_EBOOK_CREATOR_H
#define VIEW_CREATOR_EBOOK_CREATOR_H

#include <QWidget>
#include <QVBoxLayout>
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

/** @brief EBookCreator
 *
 *  EBookCreator e' un custom widget dedicato alla creazione dei media di tipo EBook.
 *
 *  EBookCreator imposta in un QFormLayout tutti gli attributi di un media EBook, resi modificabili tramite QLineEdit, QSpinBox, QDoubleSpinBox e QCheckBox.
 *  L'unico campo "read-only" e' quello relativo all'identificatore univoco del nuovo media, che viene automaticamente incrementato e provveduto dal costruttore di AbstractFile.
 *
 *  EBookCreator dispone di metodi helper privati, per impostare nel QFormLayout gli attributi del media EBook e di un metodo 'setEBookToolTips' per aggiungere informazioni utili all'utente
 *  durante l'input degli attributi del media EBook.
 *
 *  Quando l'utente conferma gli attributi per il nuovo media EBook (pulsante "Create"), viene utilizzato il metodo 'onCreateButtonClicked' per raccogliere gli attributi in un oggetto del tipo QMap<QString, QString>.
 *  Poi viene emesso il segnale 'createRequested', che delega la conversione (QMap -> std::unordered_map) e creazione al Controller (e quindi al Manager).
 */

namespace View {
namespace Creator {

class EBookCreator : public QWidget {

    Q_OBJECT

public:

    // costanti statiche per differenziare campi obbligatori/opzionali
    static const QString REQUIRED_ATTRIBUTE_STYLE;
    static const QString OPTIONAL_ATTRIBUTE_STYLE;

    /**
     * @brief EBookCreator : costruttore, inizializza il layout principale e il form per gli attributi, inserendo valori di default per un media EBook
     * @param parent : parent widget (di default 'nullptr')
     */
    explicit EBookCreator(QWidget* parent = nullptr);

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
     * @brief onCreateButtonClicked : gestisce conferma degli attributi per il nuovo media EBook. Raccoglie gli attributi in una QMap<QString, QString> e notifica il Controller con il segnale 'createRequested'.
     */
    void onCreateButtonClicked();

    /**
     * @brief onCancelButtonClicked : gestisce richiesta di annullamento operazione creazione
     */
    void onCancelButtonClicked();

private:

    QVBoxLayout* ebookCreatorMainLayout;
    QFormLayout* ebookCreatorFormLayout;
    QDialogButtonBox* ebookCreatorButtonBox;

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

    /** @brief setAbstractFileAttributes : helper privato per impostare campi EBook ereditati da AbstractFile */
    void setAbstractFileAttributes();
    /** @brief setAbstractMediaAttributes : helper privato per impostare campi EBook ereditati da AbstractMedia */
    void setAbstractMediaAttributes();
    /** @brief setEBookAttributes : helper privato per impostare campi EBook */
    void setEBookAttributes();
    /** @brief setEBookToolTips : imposta tooltip con informazioni utili all'utente relativi agli attributi del media EBook */
    void setEBookToolTips();

};

}
}

#endif // VIEW_CREATOR_EBOOK_CREATOR_H


#ifndef VIEW_CREATOR_TYPE_SELECTOR_WIDGET_H
#define VIEW_CREATOR_TYPE_SELECTOR_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QDialogButtonBox>

/** @brief TypeSelectorWidget
 *
 *  TypeSelectorWidget e' un custom widget "semplice" utilizzato nell'operazione di creazione dei media.
 *  Viene utilizzato assieme alla classe MediaCreatorFactory e i vari custom widget (Creator) per creare i vari tipi di media supportati dalla libreria multimediale.
 *
 *  Quando l'utente selezione l'azione "Create" viene inserito nel pannello destro TypeSelectorWidget. Dispone di un QComboBox per la scelta del tipo di media da creare
 *  e di un QDialogButtonBox con due pulsanti. Il pulsante "Confirm" emette il segnale 'mediaTypeSelected' per notificare la MainWindow del tipo selezionato, mentre il
 *  pulsante "Cancel" emette il segnale 'closed' per notificare l'annullamento dell'operazione.
 */

namespace View {
namespace Creator {

class TypeSelectorWidget : public QWidget {

    Q_OBJECT

public:

    /**
     * @brief TypeSelectorWidget : costruttore, imposta layout, combo box, bottoni e collega segnali/slot
     * @param parent : parent widget
     */
    explicit TypeSelectorWidget(QWidget* parent = nullptr);

signals:

    /**
     * @brief mediaTypeSelected : segnale emesso quando viene scelto un tipo dalla QComboBox
     * @param mediaType : stringa con tipo scelto
     */
    void mediaTypeSelected(const QString& mediaType);

    /**
     * @brief closed : segnale emesso quando viene annullato l'operazione
     */
    void closed();

private slots:

    /**
     * @brief onConfirmButtonClicked : gestisce richiesta conferma di selezione tipo dalla QComboBox
     * @details mostra un warning se il tipo selezionato della QComboBox e' il valore predefinito "Select Type" di indice 0
     */
    void onConfirmButtonClicked();

    /**
     * @brief onCancelButtonClicked : gestisce richiesta annullamento operazione
     */
    void onCancelButtonClicked();

private:

    QVBoxLayout* typeSelectorMainLayout;
    QLabel* typeSelectorLabel;
    QComboBox* typeSelector;
    QDialogButtonBox* typeSelectorButtonBox;
};

}
}



#endif // VIEW_CREATOR_TYPE_SELECTOR_WIDGET_H

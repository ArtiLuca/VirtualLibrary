#ifndef VIEW_VIEWER_CONCISE_VIEWER_H
#define VIEW_VIEWER_CONCISE_VIEWER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QString>
#include <QLabel>
#include <QRadioButton>
#include <QMouseEvent>

/** @brief ConciseViewer
 *
 *  ConciseViewer e' un custom widget utilizzato per la visualizzazione compatta ("concisa") dei media in libreria.
 *  Viene tipicamente utilizzata come item widget all'interno di una QListWidget, ad esempio per mostrare la lista dei media attualmente in libreria o per mostrare i media trovati in un'operazione di ricerca.
 *
 *  Ogni ConciseViewer mostra l'indice in libreria del media, il suo identificatore univoco, il tipo del media e il nome del media.
 *  Inoltre, ogni ConciseViewer include un QRadioButton per consentire la selezione del media, in modo da poter poi impostare il suo indice come indice corrente.
 *
 *  A tale scopo ho definito i segnali 'mediaWasClicked' e 'selectedMediaChanged' assieme allo slot 'onRadioButtonToggled' per notificare la selezione/click e/o cambio di stato del media.
 */

namespace View {
namespace Viewer {

class ConciseViewer : public QWidget {

    Q_OBJECT

public:

    /**
     * @brief ConciseViewer : costruttore, imposta campi privati
     * @param ind : indice del media
     * @param mediaID : identificatore univoco del media
     * @param mediaType : tipo del media
     * @param mediaName : nome del media
     * @param parent : parent widget (con valore di default 'nullptr')
     */
    ConciseViewer(
        int ind,
        int mediaID,
        QString mediaType,
        QString mediaName,
        QWidget* parent = nullptr
    );

    /**
     * @brief getMediaIndex : restituisce l'indice del media
     * @return int : indice del media
     */
    int getMediaIndex() const;

    /**
     * @brief mediaSelected : indica se il media e' attualmente selezionato tramite il suo QRadioButton
     * @return bool : true se il media e' selezionato, false altrimenti
     */
    bool mediaSelected() const;

    /**
     * @brief setMediaSelected : imposta stato di selezione del QRadioButton associato al media
     * @param select : stato di selezione (true=media selezionato, false=media deselezionato)
     */
    void setMediaSelected(bool select);

signals:

    /**
     * @brief mediaWasClicked : segnala il selezionamento/click del media
     * @param ind : indice del media selezionato/clicked
     */
    void mediaWasClicked(int ind);

    /**
     * @brief selectedMediaChanged : segnala cambio del stato di selezione del media
     * @param ind : indice del media
     * @param select : true se il media e' selezionato, false altrimenti
     */
    void selectedMediaChanged(int ind, bool select);

private slots:

    /**
     * @brief onRadioButtonToggled : gestisce la richiesta di cambio stato di selezione QRadioButton
     * @param checked : true se selezionato
     */
    void onRadioButtonToggled(bool checked);

private:

    int mediaIndex;
    QHBoxLayout* mediaLayout;
    QRadioButton* mediaRadioButton;
    QLabel* mediaIndexLabel;
    QLabel* mediaIDLabel;
    QLabel* mediaTypeLabel;
    QLabel* mediaNameLabel;
};

}
}

#endif // VIEW_VIEWER_CONCISE_VIEWER_H

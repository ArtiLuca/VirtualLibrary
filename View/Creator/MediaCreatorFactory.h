#ifndef VIEW_CREATOR_MEDIA_CREATOR_FACTORY_H
#define VIEW_CREATOR_MEDIA_CREATOR_FACTORY_H

#include "Controller/Controller.h"

#include <QString>
#include <QWidget>

/** @brief MediaCreatorFactory
 *
 *  MediaCreatorFactory e' una classe utilizzata per implementare l'operazione di creazione per i vari tipi di media supportati dalla libreria multimediale.
 *  Viene utilizzata assieme alla classe TypeSelectorWidget, usata per scegliere il tipo da creare, e i vari custom widget dedicati (Creator) per ciascun tipo di media.
 *
 *  Il costruttore di MediaCreatorFactory prende come parametri una stringa contenente il tipo di media da creare e un punatatore al Controller.
 *  La stringa con il nome del tipo da creare viene passata dalla stringa scelta nel QComboBox di TypeSelectorWidget.
 *
 *  Poi, in base alla stringa passata, il metodo 'fetchAndReset' restituisce il custom widget (Creator) dedicato per la creazione del tipo specifico del media, in modo
 *  analogo alle altre 'Factory' MediaViewerFactory e MediaEditorFactory.
 *
 *  NOTA1: Come nel caso degli Editor, ho dovuto usare una QMap<QString, QString> per gli attributi del media in modo da poter utilizzare il sistema di segnali/slot di Qt.
 */

namespace View {
namespace Creator {

class MediaCreatorFactory {

public:

    /**
     * @brief MediaCreatorFactory : costruttore, imposta campi privati
     * @param mediaType : string con nome del tipo di media da creare
     * @param c : puntatore al Controller
     * @param parent : parent widget
     */
    MediaCreatorFactory(const QString& mediaType, Controller::Controller* c, QWidget* parent = nullptr);

    /**
     * @brief fetchAndReset : resetta e restituisce il widget creato
     * @return QWidget* : puntatore al Creator widget creato (in base a 'mediaType')
     */
    QWidget* fetchAndReset();

private:

    Controller::Controller* controller; // puntatore al Controller
    QWidget* createdWidget;             // puntatore al Creator widget
    QWidget* parentWidget;              // puntatore al parent widget


};

}
}

#endif // VIEW_CREATOR_MEDIA_CREATOR_FACTORY_H


#ifndef VIEW_VIEWER_MEDIA_VIEWER_FACTORY_H
#define VIEW_VIEWER_MEDIA_VIEWER_FACTORY_H

#include "Controller/Controller.h"
#include "Model/Visitors/IConstVisitor.h"

#include <QWidget>

/** @brief MediaViewerFactory
 *
 *  MediaViewerFactory e' una sottoclasse concreta che deriva pubblicamente da Model::Visitors::IConstVisitor, in quanto non va a modificare i media.
 *  Implementa il design pattern "Factory" assieme al design pattern "Visitor" per la creazione dei custom widget (Viewer) per la visualizzazione dei media.
 *
 *  Il costruttore di MediaViewerFactory prende come parametri un punatore al Controller, l'indice del media da visualizzare, e il parent widget.
 *  Il metodo 'fetchAndReset' restituisce il widget creato (Viewer) che ho dovuto dicharare 'mutable' essendo che MediaViewerFactory deriva da IConstVisitor.
 *
 *  MediaViewerFactory e' concreta in quanto va a ridefinire i metodi virtuali puri ereditati da IConstVisitor in modo specifico per ciascun tipo di media.
 *
 */

namespace View {
namespace Viewer {

class MediaViewerFactory : public Model::Visitors::IConstVisitor {

public:

    /**
     * @brief MediaViewerFactory : costruttore
     * @param c : puntatore al controller
     * @param ind : indice del media
     * @param parent : parent widger
     */
    MediaViewerFactory(Controller::Controller* c, int ind, QWidget* parent);

    /**
     * @brief fetchAndReset : restituisce e resetta (imposta a 'nullptr') il widget creato (Viewer concreto)
     * @return QWidget : puntatore al Viewer widget creato
     */
    QWidget* fetchAndReset();

    /** @brief visit : riefinizione virtuale puro ereditato da IConstVisitor per il tipo Audio */
    void visit(const Model::Media::Audio& audio) const override;
    /** @brief visit : riefinizione virtuale puro ereditato da IConstVisitor per il tipo Video */
    void visit(const Model::Media::Video& video) const override;
    /** @brief visit : riefinizione virtuale puro ereditato da IConstVisitor per il tipo EBook */
    void visit(const Model::Media::EBook& ebook) const override;
    /** @brief visit : riefinizione virtuale puro ereditato da IConstVisitor per il tipo Image */
    void visit(const Model::Media::Image& image) const override;

private:

    Controller::Controller* controller; // puntatore al controller
    int mediaIndex;                     // indice del media
    QWidget* parentWidget;              // puntatore al parent widget
    mutable QWidget* createdWidget;     // puntatore al widget Viewer creato (dichiarato 'mutable' per permettere la modifica)
};

}
}



#endif // VIEW_VIEWER_MEDIA_VIEWER_FACTORY_H

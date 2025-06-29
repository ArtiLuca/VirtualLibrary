#ifndef VIEW_EDITOR_MEDIA_EDITOR_FACTORY_H
#define VIEW_EDITOR_MEDIA_EDITOR_FACTORY_H

#include "Controller/Controller.h"
#include "Model/Visitors/IVisitor.h"

#include <QWidget>

/** @brief MediaEditorFactory
 *
 *  MediaEditorFactory e' una sottoclasse concreta che deriva pubblicamente da Model::Visitors::IVisitor.
 *  Implementa il design pattern "Factory" assieme al design pattern "Visitor" per la creazione dei custom widget (Editor) per la modifica dei media.
 *
 *  Il suo funzionamento e' analogo a quello di MediaViewerFactory.
 *
 *  NOTA:
 *  I vari Editor raccolgono le modifiche date in input in un'oggetto del tipo QMap<QString, QString>. Questo era necessario per poter correttamente utilizzare il sistema di segnali/slot di Qt.
 *  Per questo, ho definito dei metodi helper di conversione nel Controller per convertire un oggetto QMap<QString, QString> in un corrispondente oggetto std::unordered_map<std::string, std::string> (e vicecersa).
 */

namespace View {
namespace Editor {

class MediaEditorFactory : public Model::Visitors::IVisitor {

public:

    /**
     * @brief MediaEditorFactory : costruttore, inizializza i campi privati
     * @param c : puntatore al Controller
     * @param ind : indice del media da modificare
     * @param parent : parent widget
     */
    MediaEditorFactory(Controller::Controller* c, int ind, QWidget* parent = nullptr);

    /**
     * @brief fetchAndReset : restituisce e resetta (imposta a 'nullptr') il widget creato (Editor concreto)
     * @return QWidget : puntatore al Editor widget creato
     */
    QWidget* fetchAndReset();

    /** @brief visit : ridefinizione metodo virtuale puro ereditato da IVisitor per il tipo Audio */
    void visit(Model::Media::Audio&) override;
    /** @brief visit : ridefinizione metodo virtuale puro ereditato da IVisitor per il tipo Video */
    void visit(Model::Media::Video&) override;
    /** @brief visit : ridefinizione metodo virtuale puro ereditato da IVisitor per il tipo EBook */
    void visit(Model::Media::EBook&) override;
    /** @brief visit : ridefinizione metodo virtuale puro ereditato da IVisitor per il tipo Image */
    void visit(Model::Media::Image&) override;

private:

    Controller::Controller* controller;  // puntatore al Controller
    int mediaIndex;                      // indice del media
    QWidget* parentWidget;               // puntatore a parent widget
    QWidget* createdWidget;              // puntatore al Editor widget creato

};

}
}

#endif // VIEW_EDITOR_MEDIA_EDITOR_FACTORY_H

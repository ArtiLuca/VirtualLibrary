#ifndef MODEL_VISITORS_I_VISITOR_H
#define MODEL_VISITORS_I_VISITOR_H

#include "Model/Media/Audio.h"
#include "Model/Media/EBook.h"
#include "Model/Media/Video.h"
#include "Model/Media/Image.h"

/** @brief IVisitor
 *
 *  IVisitor rappresenta l'interfaccia base astratta per l'implementazione del design pattern Visitor.
 *  In particolare, i visitor concreti che ereditanto da IVisitor possono andare a modificare i media su cui vanno ad agire (ad esempio, il visitor MediaEditor).
 *
 *  IVisitor e' astratta in quanto dispone dei metodi virtuali puri 'visit' per implementare la versione non-const del design pattern Visitor per ciascun tipo di media.
*/

namespace Model {
namespace Visitors {

class IVisitor {
public:

    /** @brief ~IVisitor : distruttore virtuale */
    virtual ~IVisitor() = default;

    /**
     * @brief visit : virtuale puro, implementa design pattern Visitor (versione non-const) per il media Audio
     * @param audio : riferimento a media Audio
     */
    virtual void visit(Media::Audio& audio) = 0;

    /**
     * @brief visit : virtuale puro, implementa design pattern Visitor (versione non-const) per il media Video
     * @param video : riferimento a media Video
     */
    virtual void visit(Media::Video& video) = 0;

    /**
     * @brief visit : virtuale puro, implementa design pattern Visitor (versione non-const) per il media EBook
     * @param ebook : riferimento a media EBook
     */
    virtual void visit(Media::EBook& ebook) = 0;

    /**
     * @brief visit : virtuale puro, implementa design pattern Visitor (versione non-const) per il media Image
     * @param image : riferimento a media Image
     */
    virtual void visit(Media::Image& image) = 0;
};

}
}

#endif // MODEL_VISITORS_I_VISITOR_H

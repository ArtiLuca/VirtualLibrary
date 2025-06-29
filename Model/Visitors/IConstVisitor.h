#ifndef MODEL_VISITORS_I_CONST_VISITOR_H
#define MODEL_VISITORS_I_CONST_VISITOR_H

#include "Model/Media/Audio.h"
#include "Model/Media/EBook.h"
#include "Model/Media/Video.h"
#include "Model/Media/Image.h"



/** @brief IConstVisitor
 *
 *  IConstVisitor rappresenta l'interfaccia base astratta per l'implementazione della versione const del design pattern Visitor.
 *  In particolare, i visitor concreti che ereditano da IConstVisitor non andranno a produrre "side effects".
 *  Cioe', non andranno a fare modifiche sul media su cui andranno ad agire.
 *
 *  IConstVisitor e' astratta in quanto dispone dei metodi virtuali puri 'visit' per implementare la versione const del design pattern Visitor per ciascun tipo di media.
*/


namespace Model {
namespace Visitors {

class IConstVisitor {
public:

    /** @brief ~IConstVisitor : distruttore virtuale */
    virtual ~IConstVisitor() = default;

    /**
     * @brief visit : virtuale puro, implementa design pattern Visitor (versione const) per il media Audio
     * @param audio : riferimento costante a media Audio
     */
    virtual void visit(const Media::Audio& audio) const = 0;

    /**
     * @brief visit : virtuale puro, implementa design pattern Visitor (versione const) per il media Video
     * @param video : riferimento costante a media Video
     */
    virtual void visit(const Media::Video& video) const = 0;

    /**
     * @brief visit : virtuale puro, implementa design pattern Visitor (versione const) per il media EBook
     * @param ebook : riferimento costante a media EBook
     */
    virtual void visit(const Media::EBook& ebook) const = 0;

    /**
     * @brief visit : virtuale puro, implementa design pattern Visitor (versione const) per il media Image
     * @param image : riferimento costante a media Image
     */
    virtual void visit(const Media::Image& image) const = 0;

};

}
}

#endif // MODEL_VISITORS_I_CONST_VISITOR_H


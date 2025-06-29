#ifndef MODEL_UTILITIES_I_MEDIA_RESOLUTION_H
#define MODEL_UTILITIES_I_MEDIA_RESOLUTION_H

#include <utility>

/** @brief IMediaResolution
 *
 *  IMediaResolution rappresenta l'interfaccia base astratta usata da tutti i media che dispongono di una risoluzione, e quindi anche di un aspect ratio.
 *  IMediaResolution viene ereditata da tutti i media che dispongono di una risoluzione e di un aspect ratio (ad esempio Video e Image).
 *  Invece, i media EBook e Audio non la ereditano in quanto non avrebbe logicamente avere un media audio o ebook con una risoluzione (o aspect ratio) impostato.
 *
 *  La risoluzione e l'aspect ratio di un media viene rappresentato tramite un'oggetto del tipo std::pair<int, int>.
 *
 *  IMediaResolution e' astratta in quanto dispone di tre metodi virtuali puri che vanno ridefiniti nei media concreti che la ereditano.
 *  I metodi 'getResolution' e 'setResolution' vengono ridefiniti in modo da agire da getter/setter della risoluzione del media, mentre il metodo 'matchesAspectRatio'
 *  viene ridefinito per restituire true solamente se la risoluzione impostata rispecchia l'aspect ratio impostato del media.
 */

namespace Model {
namespace Utilities {

class IMediaResolution {
public:

    /** @brief ~IMediaResolution : distruttore virtuale */
    virtual ~IMediaResolution() = default;


    /** @brief getResolution : virtuale puro, "getter" risoluzione del media
     * @return std::par<int, int> : risoluzione del media
     */
    virtual std::pair<int, int> getResolution() const = 0;

    /**
     * @brief setResolution : virtuale puro, "setter" della risoluzione del media
     * @param resolution : risoluzione del media
     */
    virtual void setResolution(std::pair<int, int> res) = 0;

    /**
     * @brief matchesAspectRatio : virtuale puro, controlla se l'aspect ratio rispecchia la risoluzione
     * @return bool : true se l'aspect ratio rispecchia la risoluzione impostata, false altrimenti
     */
    virtual bool matchesAspectRatio() const = 0;
};

}
}

#endif // MODEL_UTILITIES_I_MEDIA_RESOLUTION_H

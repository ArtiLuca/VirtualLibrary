#ifndef MODEL_UTILITIES_I_MEDIA_LENGTH_H
#define MODEL_UTILITIES_I_MEDIA_LENGTH_H

/** @brief IMediaLength
 *
 *  IMediaLength rappresenta l'interfaccia base astratta usata dai media che dispongono di una "durata".
 *  IMediaLength viene ereditata solamente dai media che dispongono di una durata (Audio, EBook, Video).
 *  Ad esempio, il media Image non la eredita in quanto non avrebbe logicamente senso applicare una durata ad una immagine.
 *
 *  La durata di un media viene espressa in termini di tempo (cioe come totale in minuti), oppure per il numero totale di pagine.
 *  Ho fatto questa scelta per aiutare a differenziare i media della libreria, e per formare le basi per poter poi implementare il polimorfismo in modo meno banale.
 *
 *  IMediaLength e' astratta in quanto dispone di tre metodi virtuali puri che vanno ridefiniti nei media concreti che la ereditano.
 *  Il metodo 'measuredInPages' viene ridefinito per restituire true solamente nei media che rappresentano la loro durata per numero di pagine (EBook).
 *  I due metodi 'getMediaLength' e 'setMediaLength' vengono invece ridefiniti per agire da getter/setter della durata di un media.
 *
 */

namespace Model {
namespace Utilities {

class IMediaLength {
public:

    /** @brief ~IMediaLength : distruttore virtuale */
    virtual ~IMediaLength() = default;

    /**
     * @brief measuredInPages : virtuale puro per determinare se la durata e' espressa in termini di pagine oppure in termini di minuti
     * @return bool : true se la durata e' espressa in pagine, false se e' espressa in minuti
     */
    virtual bool measuredInPages() const = 0;

    /**
     * @brief getMediaLength : virtuale puro, "getter" per la durata del media
     * @return unsigned int : durata del media espressa come numero di pagine o minuti totali
     */
    virtual unsigned int getMediaLength() const = 0;

    /**
     * @brief setMediaLength : virtuale puro, "setter" per la durata del media
     * @param length : la durata del media (in pagine o minuti)
     */
    virtual void setMediaLength(unsigned int length) = 0;
};

}
}

#endif // MODEL_UTILITIES_I_MEDIA_LENGTH_H

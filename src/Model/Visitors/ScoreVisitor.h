#ifndef MODEL_VISITORS_SCORE_VISITOR_H
#define MODEL_VISITORS_SCORE_VISITOR_H

#include "IConstVisitor.h"
#include "Model/Media/Audio.h"
#include "Model/Media/Video.h"
#include "Model/Media/EBook.h"
#include "Model/Media/Image.h"

#include <string>

/** @brief ScoreVisitor
 *
 *  ScoreVisitor e' una sottoclasse concreta che derivata pubblicamente da IConstVisitor.
 *  Implementa il design pattern "Visitor" per lo "scoring" della qualita' dei vari tipi di media della libreria supportati dalla liberia.
 *
 *  ScoreVisitor calcola uno score numerico 'scoreValue' nel range [0,100] e ci associa un label qualitativo corrispondente.
 *  Il calcolo avviene mediante una media ponderata degli attributi piu' rilvenati alla "qualita"  di ciascun media.
 *
 *  Ciascun attributo e' dato un suo peso e viene poi normalizzato nel range [0,1] utilizzando il metodo helper privato 'normalizeValue' e in alcuni casi altri helper privati,
 *  come ad esempio 'normalizeVideoResolution' nel caso dei media Video, oppure 'normalizeAudioQuality' nel caso dei media Audio.
 *
 *  In molti casi la normalizzazione degli attributi utilizza valori di soglia massimi/minimi, percepibili dall'utente, utilizzati per indicare i limiti per i valori, che
 *  tipicamente quando oltrepassati (in basso o in alto) non presentano differenze di qualita' percepibili.
 *
 *  Il calcolo per i vari tipi di media avviene secondo il seguente comportamento:
 *
 *   - Audio: rating(40%), qualita' audio (50%), format (10%)
 *   - Video: rating (35%), risoluzione video (45&), framerate (10%), supporto HDR (10%)
 *   - EBook: rating (100%)
 *   - Image: rating (30%), megapixel immagine (40%), compressione (20%), bitdepth (10%)
 *
 *  Le informazioni relative allo "scoring" di un media vengono salvate nella stringa 'scoreInfo'.
 *
 */

namespace Model {
namespace Visitors {

class ScoreVisitor : public IConstVisitor {

public:

    // === COSTANTI STATICHE ===

    static const std::string LABEL_UKNOWN;
    static const std::string LABEL_LOW;
    static const std::string LABEL_AVERAGE;
    static const std::string LABEL_HIGH;
    static const std::string LABEL_VERY_HIGH;

    static const float SCORE_UNKNOWN;
    static const float SCORE_LOW;
    static const float SCORE_AVERAGE;
    static const float SCORE_HIGH;
    static const float SCORE_VERY_HIGH;

    // === COSTRUTTORE ===

    /**
     * @brief ScoreVisitor : costruttore di default, inizializza i campi dati privati con valori iniziali
     */
    ScoreVisitor();


    // === GETTER CAMPI PRIVATI ===

    /**
     * @brief getScoreValue : restituisce lo score numerico del media
     * @return float : score numerico del media, normalizzato nel range [0-100]
     */
    float getScoreValue() const;

    /**
     * @brief getScoreLabel : restituisce un label qualitativo del media in base al suo score numerico
     * @return const std::string& : label qualitativo
     */
    const std::string& getScoreLabel() const;

    /**
     * @brief getScoreInfo : restituisce informazioni relative al "scoring" per il dato tipo di media
     * @return const std::string& : informazioni aggiuntive
     */
    const std::string& getScoreInfo() const;


    // === RESET ===

    /**
     * @brief resetScoreVisitor : reimposta il visitor (serve const_cast) impostanto i suoi campi dati privati ai valori iniziali
     */
    void resetScoreVisitor();


    // === RIDEFINIZIONE VIRTUALI PURI IConstVisitor ===

    /**
     * @brief visit : ridefinizione virtuale puro ereditato da IConstVisitor, effettua lo scoring di un media Audio
     * @param audio : riferimento costante a media Audio
     * @details score dato da rating (40%), qualita' audio (50%), format (10%)
     */
    void visit(const Media::Audio& audio) const override;

    /**
     * @brief visit : ridefinizione virtuale puro ereditato da IConstVisitor, effettua lo scoring di un media Video
     * @param video : riferimento costante a media Video
     * @details score dato da rating (35%), risoluzione video (45%), framerate (10%), HDR support (10%)
     */
    void visit(const Media::Video& video) const override;

    /**
     * @brief visit : ridefinizione virtuale puro ereditato da IConstVisitor, effettua lo scoring di un media EBook
     * @param ebook : riferimento costante a media EBook
     * @details score dato da rating (100%)
     */
    void visit(const Media::EBook& ebook) const override;

    /**
     * @brief visit : ridefinizione virtuale puro ereditato da IConstVisitor, effettua lo scoring di un media Image
     * @param image : riferimento costante a media Image
     * @details score dato da rating (30%), megapixel totali (40%), compressione (20%), bitdepth (10%)
     */
    void visit(const Media::Image& image) const override;


private:

    // === CAMPI DATI PRIVATI ===

    mutable float scoreValue;       // score numerico
    mutable std::string scoreLabel; // score come label
    mutable std::string scoreInfo;  // dettagli sul calcolo


    // === HELPER GENERALI ===

    /**
     * @brief normalizeValue : normalizza un valore nel range [0-100]
     * @param val : valore da normalizzare
     * @param min : valore minimo
     * @param max : valore massimo
     * @return float : valore normalizzato
     */
    float normalizeValue(float val, float min, float max) const;

    /**
     * @brief assignScoreLabel : restituisce il label qualitativo corrispondente in base allo score
     * @param score : score calcolato
     * @return std::string : label qualitativo corrispondente
     */
    std::string assignScoreLabel(float score) const;


    // === HELPER SPECIFICI AL TIPO ===

    /**
     * @brief calculateAudioScore : helper per calcolare score media Audio
     * @param audio : riferimento costante a Audio
     * @param info : info sul calcolo
     * @return float : valore normalizzato nel range [0-100] dello score
     */
    float calculateAudioScore(const Media::Audio& audio, std::string& info) const;

    /**
     * @brief calculateAudioQuality : helper per normalizzare qualita' audio
     * @param audio :  riferimento costante a Audio
     * @return float : valore normalizzato della qualita' audio nel range [0-1]
     * @details calcola media ponderate del suo bitrate (50%), samplerate (30%), bitdepth (10%), channels (10%)
     */
    float normalizeAudioQuality(const Media::Audio& audio) const;

    /**
     * @brief calculateVideoScore : helper per calcolare score media Video
     * @param video : riferimento costante a Video
     * @param info : info sul calcolo
     * @return float : valore normalizzato nel range [0-100] dello score
     */
    float calculateVideoScore(const Media::Video& video, std::string& info) const;

    /**
     * @brief normalizeVideoResolution : helper per normalizzare risoluzione video
     * @param videoRes : altezza della risoluzione video
     * @return float : valore normalizzato della risoluzione video nel range [0-1]
     */
    float normalizeVideoResolution(int videoRes) const;

    /**
     * @brief calculateImageScore : helper per calcolare score media Image
     * @param image : riferimento costante a Image
     * @param info : info sul calcolo
     * @return float : valore normalizzato nel range [0-100] dello score
     */
    float calculateImageScore(const Media::Image& image, std::string& info) const;

    /**
     * @brief normalizeImageQuality : helper per normalizzare qualita' immagine, in base ai suoi megapixel
     * @param imageMP : numero totale di megapixel del media Image
     * @return float : valore normalizzato dei megapixel totali nel range [0-1]
     */
    float normalizeImageQuality(float imageMP) const;

};

}
}

#endif // MODEL_VISITORS_SCORE_VISITOR_H

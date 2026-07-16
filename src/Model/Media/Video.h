#ifndef MODEL_MEDIA_VIDEO_H
#define MODEL_MEDIA_VIDEO_H

#include "AbstractMedia.h"
#include "Model/Utilities/IMediaLength.h"
#include "Model/Utilities/IMediaResolution.h"

#include <string>
#include <vector>
#include <utility>
#include <QJsonObject>

/** @brief Video
 *
 *  Video e' una sottoclasse concreta derivata pubblicamente da AbstractMedia, IMediaLength e IMediaResolution.
 *  Un oggetto della classe Video rappresenta un film, cioe' un media aventa una durata in minuti e una risoluzione (espressa come larghezza x altezza) che e' vincolata all'aspect ratio 16:9.
 *
 *  Un oggetto Video rappresenta un film tramite il suo regista, genre, anno d'uscita, durata totale in minuti, framerate (espresso in fps), colordepth (in bit),
 *  la risoluzione del film, i sottotitoli (se presenti), e la lingua parlata del film.
 *
 *  La classe Video dispone di un costruttore di default, un costruttore di copia, la ridefinizione dell'operatore di assegnazione e dei getter/setter dei campi dati privati.
 *  Il costruttore di default di Video inizializza i campi dati ai valori di default definiti dalle costanti statiche nella parte pubblica della classe.
 *
 *  Un media Video di Virtual Library e' considerato valido se:
 *
 *       - ha una durata espressa in minuti e una risoluzione vincolata all'aspect ratio "16:9"
 *       - contiene tutti i campi impostati (con l'eccezione dei campi 'language' e 'subtitles')
 *       - ha una durata in minuti definita nell'intervallo [45, 220]
 *       - ha un framerate (in fps) definito nell'intervallo [24,120]
 *       - ha un color depth del video definito nell'intervallo [8-16]
 *       - ha un formato ammesso al tipo Video.
 *
 *  La classe Video e' concreta in quanto va a ridefinire i metodi virtuali puri ereditati da IMediaResolution, IMediaLength, AbstractMedia (e quindi anche AbstractFile) in modo specifico per il tipo Video.
 */

namespace Model {
namespace Media {

class Video : public Media::AbstractMedia, public Utilities::IMediaLength, public Utilities::IMediaResolution {

public:

    // === COSTANTI STATICHE ===

    static const unsigned int MIN_VIDEO_LENGTH;
    static const unsigned int MAX_VIDEO_LENGTH;
    static const unsigned int MIN_VIDEO_FRAME_RATE;
    static const unsigned int MAX_VIDEO_FRAME_RATE;
    static const std::pair<int, int> VIDEO_ASPECT_RATIO;
    static const unsigned int MIN_VIDEO_COLOR_DEPTH;
    static const unsigned int MAX_VIDEO_COLOR_DEPTH;
    static const unsigned int MIN_COLOR_DEPTH_HDR;
    static const unsigned int MIN_VIDEO_RESOLUTION_WIDTH;
    static const unsigned int MAX_VIDEO_RESOLUTION_WIDTH;
    static const unsigned int MIN_VIDEO_RESOLUTION_HEIGHT;
    static const unsigned int MAX_VIDEO_RESOLUTION_HEIGHT;
    static const std::vector<std::string> VIDEO_FORMATS;

    static const std::string defaultVideoFormat;
    static const float defaultVideoSize;
    static const std::string defaultVideoDirector;
    static const std::string defaultVideoGenre;
    static const unsigned int defaultVideoReleaseYear;
    static const unsigned int defaultVideoLength;
    static const unsigned int defaultVideoFrameRate;
    static const std::pair<int, int> defaultVideoResolution;
    static const unsigned int defaultVideoColorDepth;
    static const std::string defaultSubtitles;
    static const std::string defaultVideoLanguage;


    // === COSTRUTTORI, ASSEGNAZIONE ===

    /** @brief Video : costruttore di default, inizializza i campi dati con valori di default */
    Video();

    /** @brief Video : costruttore di copia */
    Video(const Video& video);

    /** @brief operator= : operatore di assegnazione */
    Video& operator=(const Video& video);


    // === GETTER ===

    const std::string& getDirector() const;
    const std::string& getGenre() const;
    unsigned int getCreationYear() const;
    unsigned int getFrameRate() const;
    const std::string& getLanguage() const;
    unsigned int getVideoColorDepth() const;
    const std::string& getSubtitles() const;


    // == SETTER ===

    void setDirector(const std::string& dir);
    void setGenre(const std::string& gnr);
    void setCreationYear(unsigned int year);
    void setFrameRate(unsigned int fr);
    void setLanguage(const std::string& lang);
    void setVideoColorDepth(unsigned int depth);
    void setSubtitles(const std::string& subs);


    // === METODI SPECIFICI Video ===

    /**
     * @brief supportsHDR : verifica se il video ha il supporto HDR
     * @return bool : ritorna true se il color depth e' maggiore o uguale a '12-bit', false altrimenti
     */
    bool supportsHDR() const;

    /**
     * @brief getVideoDuration : restituisce durata espressa in ore, minuti
     * @return std::string : durata in ore, minuti
     */
    std::string getVideoDuration() const;


    // == RIDEFINIZIONE VIRTUALI PURI IMediaLength ===

    /** * @brief measuredInPages : ridefinizione virtuale puro ereditato da Utilities::IMediaLength, ritorna sempre false */
    bool measuredInPages() const override;

    /** @brief getMediaLength : ridefinizione virtuale puro ereditato da Utilities::IMediaLength, ritorna la durata totale (in minuti) */
    unsigned int getMediaLength() const override;

    /** @brief setMediaLength : ridefinizione virtuale puro ereditato da Utilities::IMediaLength, imposta la durata totale (in minuti) */
    void setMediaLength(unsigned int length) override;


    // == RIDEFINIZIONE VIRTUALI PURI IMediaResolution ===

    /**
     * @brief getResolution : ridefinizione virtuale puro ereditato da Utilities::IMediaResolution, ritorna la risoluzione
     * @return std::pair<int, int> : risoluzione del video, espressa come 'larghezza x altezza'
     */
    std::pair<int, int> getResolution() const override;

    /**
     * @brief setResolution : ridefinizione virtuale puro ereditato da Utilities::IMediaResolution, imposta la risoluzione
     * @param std::pair<int, int> : risoluzione del video da impostare (espressa come 'larghezza x altezza')
     */
    void setResolution(std::pair<int, int> res) override;

    /**
     * @brief matchesAspectRatio : ridefinizione virtuale puro ereditato da Utilities::IMediaResolution
     * @return bool : true se la risoluzione rispecchia l'aspect ratio, vincolata '16:9' per il tipo Video, false altrimenti
     */
    bool matchesAspectRatio() const override;


    // == RIDEFINIZIONE VIRTUALI PURI AbstractMedia ===

    /** @brief hasLength : ridefinizione virtuale puro ereditato da AbstractMedia, ritorna sempre true */
    bool hasLength() const override;

    /** @brief hasResolution : ridefinizione virtuale puro ereditato da AbstractMedia, ritorna sempre true */
    bool hasResolution() const override;


    // == RIDEFINIZIONE VIRTUALI PURI AbstractFile ===

    /**
     * @brief clone : ridefinizione del metodo di clonazione ereditato da AbstractFile
     * @return Video* : puntatore a Video, tipo di ritorno covariante
     */
    Video* clone() const override;

    /** @brief accept : ridefinizione virtuale puro ereditato da AbstractFile per l'implementazione non-const del design pattern Visitor per il tipo Video (commentato nella definizione) */
    void accept(Visitors::IVisitor& visitor) override;

    /** @brief accept : ridefinizione virtuale puro ereditato da AbstractFile per l'implementazione const del design pattern Visitor per il tipo Video (commentato nella definizione) */
    void accept(Visitors::IConstVisitor& visitor) const override;


    /**
     * @brief displayStringType : ridefinizione virtuale puro ereditato da AbstractFile
     * @return std::string : stringa usata solamente per stampare/mostrare il tipo del media (e non come sostituzione al polimorfismo)
     */
    std::string displayStringType() const override;


    // === PERSISTENZA DATI JSON ===


    /** @brief toJson : ridefinizione virtuale puro ereditato da AbstractMedia per la persistenza dei dati in formato JSON, in modo specifico al tipo Video */
    QJsonObject toJson() const override;

    /** @brief fromJson :  ridefinizione virtuale puro ereditato da AbstractMedia per la persistenza dei dati in formato JSON, in modo specifico al tipo Video */
    void fromJson(const QJsonObject& obj) override;


private:

    // === CAMPI DATI ===

    std::string director;                 // regista del media video
    std::string genre;                    // genre del media video
    unsigned int creationYear;            // anno d'uscita del media video
    unsigned int lengthInMinutes;         // durata totale del media videoin minuti
    unsigned int frameRate;               // frame rate del media video (in fps)
    std::pair<int, int> videoResolution;  // risoluzione del media video
    unsigned int videoColorDepth;         // color depth per channel (in bit)
    std::string subtitles;                // sottotitoli del media video
    std::string language;                 // lingua parlata del media video

};


}
}

#endif // MODEL_MEDIA_VIDEO_H

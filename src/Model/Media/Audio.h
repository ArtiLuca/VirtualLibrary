#ifndef MODEL_MEDIA_AUDIO_H
#define MODEL_MEDIA_AUDIO_H

#include "AbstractMedia.h"
#include "Model/Utilities/IMediaLength.h"

#include <string>
#include <vector>
#include <QJsonObject>

/** @brief Audio
 *
 *  Audio e' una sottoclasse concreta derivata pubblicamente da AbstractMedia e IMediaLength.
 *  Un oggetto della classe Audio rappresenta un media audio, cioe' un canzone con durata espressa in minuti e senza una risoluzione, in quanto non avrebbe logicamente senso.
 *
 *  Un oggetto Audio rappresenta una canzone tramite il suo artista, il genre, l'album (se presente), l'anno d'uscita, la durata (espressa in minuti), il bitrate (espresso in kbps),
 *  il samplerate (espresso in kHz), il bitdepth (espresso in bit), il numero di canali audio, e i collaboratori (se presenti).
 *
 *  La classe Audio dispone di un costruttore di default, un costruttore a parametri, un costruttore di copia, la ridefinizione dell'operatore di assegnazione e dei getter/setter dei campi dati privati.
 *  Il costruttore di default di Audio inizializza i campi dati ai valori di default definiti dalle costanti statiche nella parte pubblica della classe.
 *
 *  Un media Audio di Virtual Library e' considerato valido se:
 *
 *      - ha una durata espressa in minuti e non disopone di una risoluzione
 *      - contiene tutti i campi definiti (con l'eccezione del campo 'collaborators')
 *      - ha una durata in minuti definita nell'intervallo (0, 15]
 *      - ha un bitrate (in kbps) definito nell'intervallo [32,320]
 *      - ha un samplerate (in kHz) definito nell'intervallo [22, 192]
 *      - ha un bitdepth (in bit) definito nell'intervallo [8, 32]
 *      - ha un numero di canali audio definito nell'intervallo [1, 8]
 *      - ha un formato ammesso al tipo Audio.
 *
 *  La classe Audio e' concreta, in quanto va a ridefinire i metodi virtuali puri ereditati da IMediaLength, AbstractMedia (e quindi anche AbstractFile) in modo specifico al tipo Audio.
 *
 */


namespace Model {
namespace Media {

class Audio : public AbstractMedia, public Utilities::IMediaLength {

public:

    // === COSTANTI STATICHE ===

    static const unsigned int MIN_AUDIO_LENGTH;
    static const unsigned int MAX_AUDIO_LENGTH;
    static const unsigned int MIN_AUDIO_BIT_RATE;
    static const unsigned int MAX_AUDIO_BITRATE;
    static const float MIN_AUDIO_SAMPLE_RATE;
    static const float MAX_AUDIO_SAMPLE_RATE;
    static const unsigned int MIN_AUDIO_BIT_DEPTH;
    static const unsigned int MAX_AUDIO_BIT_DEPTH;
    static const unsigned int MIN_AUDIO_CHANNELS;
    static const unsigned int MAX_AUDIO_CHANNELS;
    static const std::vector<std::string> AUDIO_FORMATS;

    static const std::string defaultAudioFormat;
    static const float defaultAudioSize;
    static const std::string defaultAudioArtist;
    static const std::string defaultAudioGenre;
    static const std::string defaultAudioAlbum;
    static const unsigned int defaultAudioReleaseYear;
    static const unsigned int defaultAudioLength;
    static const unsigned int defaultAudioBitRate;
    static const float defaultAudioSampleRate;
    static const unsigned int defaultAudioBitDepth;
    static const unsigned int defaultAudioChannels;
    static const std::string defaultAudioCollaborators;


    // === COSTRUTTORI, ASSEGNAZIONE ===

    /** @brief Audio : costruttore di default, inizializza i campi dati con valori di default */
    Audio();

    /** @brief Audio : costruttore di copia */
    Audio(const Audio& audio);

    /** * @brief operator= : operatore di assegnazione */
    Audio& operator=(const Audio& audio);


    // === GETTER ===

    const std::string& getArtist() const;
    const std::string& getGenre() const;
    const std::string& getAlbum() const;
    unsigned int getReleaseYear() const;
    unsigned int getBitRate() const;
    float getSampleRate() const;
    unsigned int getBitDepth() const;
    unsigned int getAudioChannels() const;
    const std::string& getCollaborators() const;


    // === SETTER ===

    void setArtist(const std::string art);
    void setGenre(const std::string& gnr);
    void setAlbum(const std::string& alb);
    void setReleaseYear(unsigned int year);
    void setBitRate(unsigned int br);
    void setSampleRate(float sr);
    void setBitDepth(unsigned int bd);
    void setAudioChannels(unsigned int ch);
    void setCollaborators(const std::string& clb);


    // === RIDEFINIZIONE VIRTUALI PURI IMediaLength ===

    /** @brief measuredInPages : ridefinizione virtuale puro ereditato da Utilities::IMediaLength, ritorna sempre false */
    bool measuredInPages() const override;

    /** @brief getMediaLength : ridefinizione virtuale puro ereditato da Utilities::IMediaLength, ritorna la durata (in minuti) */
    unsigned int getMediaLength() const override;

    /** @brief setMediaLength : ridefinizione virtuale puro ereditato da Utilities::IMediaLength, imposta la durata (in minuti) */
    void setMediaLength(unsigned int length) override;


    // === RIDEFINIZIONE VIRTUALI PURI AbstractMedia ===

    /** @brief hasLength : ridefinizione virtuale puro ereditato da AbstractMedia, ritorna sempre true */
    bool hasLength() const override;

    /** @brief hasResolution : ridefinizione virtuale puro ereditato da AbstractMedia, ritorna sempre false */
    bool hasResolution() const override;


    // === RIDEFINIZIONE VIRTUALI PURI AbstractFile ===

    /**
     * @brief clone : ridefinizione del metodo di clonazione ereditato da AbstractFile
     * @return Audio* : puntatore a Audio, tipo di ritorno covariante
     */
    Audio* clone() const override;

    /** @brief accept : ridefinizione virtuale puro ereditato da AbstractFile per l'implementazione non-const del design pattern Visitor per il tipo Audio */
    void accept(Visitors::IVisitor& visitor) override;

    /** @brief accept : ridefinizione virtuale puro ereditato da AbstractFile per l'implementazione const del design pattern Visitor per il tipo Audio */
    void accept(Visitors::IConstVisitor& visitor) const override;


    /**
     * @brief displayStringType : ridefinizione virtuale puro ereditato da AbstractFile
     * @return std::string : stringa usata solamente per stampare/mostrare il tipo del media (e non come sostituzione al polimorfismo)
     */
    std::string displayStringType() const override;


    // === PERSISTENZA DATI JSON ===

    /** @brief toJson : ridefinizione virtuale puro ereditato da AbstractMedia per la persistenza dei dati in formato JSON, specifico al tipo Audio (commentato nella definizione) */
    QJsonObject toJson() const override;

    /** @brief :  ridefinizione virtuale puro ereditato da AbstractMedia per la persistenza dei dati in formato JSON, specifico al tipo Audio (commentato nella definizione) */
    void fromJson(const QJsonObject& obj) override;


private:

    // === CAMPI DATI ===

    std::string artist;            // artista del media audio
    std::string genre;             // genre del media audio
    std::string album;             // album del media audio (se presente)
    unsigned int releaseYear;      // anno di uscita
    unsigned int lengthInMinutes;  // durata (espressa in minuti)
    unsigned int bitRate;          // bitrate dell'audio (in kbps)
    float sampleRate;              // samplerate dell'audio (in kHz)
    unsigned int bitDepth;         // bitdepth dell'audio (in bit)
    unsigned int numberOfChannels; // numeri di canali audio
    std::string collaborators;     // collaboratori (se presenti)

};

}
}

#endif // MODEL_MEDIA_AUDIO_H




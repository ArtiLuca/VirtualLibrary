#ifndef MODEL_MEDIA_IMAGE_H
#define MODEL_MEDIA_IMAGE_H

#include "AbstractMedia.h"
#include "Model/Utilities/IMediaResolution.h"

#include <string>
#include <vector>
#include <utility>
#include <QJsonObject>

/** @brief Image
 *
 *  Image e' una sottoclasse concreta derivata pubblicamente da AbstractMedia e IMediaResolution.
 *  Un oggetto della classe Image rappresenta una immagine, cioe' un media avente una risoluzione ma non una durata, in quanto non avrebbe logicamente senso.
 *  A differenza del tipo Video, che ha un aspect ratio vincolato a '16:9', un media Image puo' avere un aspect ratio diverso ma che comunque rispecchia la risoluzione impostata.
 *
 *  Un oggetto Image rappresenta un'immagine tramite la data di creazione, il creatore/fotografo, la tipologia di immagine (foto, screenshot, ...), la risoluzione,
 *  l'aspect ratio, il bitdepth (espresso in bit), dall'essere compressa oppure no e un campo opzionale per indicare il luogo dove e' stata creata/scattata.
 *  La classe Image dispone di un costruttore di default, un costruttore di copia, la ridefinizione dell'operatore di assegnazione e dei getter/setter dei campi dati privati.
 *  Il costruttore di default di Image inizializza i campi dati ai valori di default definiti dalle costanti statiche nella parte pubblica della classe.
 *
 *  Un media Image di Virtual Library e' considerato valido se:
 *
 *      - dispone di una risoluzione ma non di una durata
 *      - contiene tutti i campi impostati (con l'eccezione del campo 'locationTaken')
 *      - ha un aspect ratio che rispecchia la risoluzione impostata
 *      - ha sia larghezza che altezza della risoluzione impostata nell'intervallo [200-8000]
 *      - ha un bit depth (in bit) impostato nell'intervallo [8, 32]
 *      - ha un formato ammesso al tipo Image
 *
 *  La classe Image e' concreta in quanto va a ridefinire i metodi virtuali puri ereditati da IMediaResolution e AbstractMedia (e quindi anche AbstractFile) in modo specifico per il tipo Image.
 *
 */

namespace Model {
namespace Media {

class Image : public AbstractMedia, public Utilities::IMediaResolution {

public:

    // === COSTANTI STATICHE ===

    static const unsigned int MIN_IMAGE_RESOLUTION_WIDTH;
    static const unsigned int MAX_IMAGE_RESOLUTION_WIDTH;
    static const unsigned int MIN_IMAGE_RESOLUTION_HEIGHT;
    static const unsigned int MAX_IMAGE_RESOLUTION_HEIGHT;
    static const unsigned int MIN_ASPECT_RATIO_VALUE;
    static const unsigned int MIN_IMAGE_BITDEPTH;
    static const unsigned int MAX_IMAGE_BITDEPTH;
    static const std::vector<std::string> IMAGE_FORMATS;

    static const std::string defaultImageFormat;
    static const float defaultImageSize;
    static const std::string defaultImageCreationDate;
    static const std::string defaultImageCreator;
    static const std::string defaultImageCategory;
    static const std::pair<int, int> defaultImageResolution;
    static const std::pair<int, int> defaultImageAspectRatio;
    static const unsigned int defaultImageBitDepth;
    static const bool defaultImageCompression;
    static const std::string defaultImageLocation;


    // === COSTRUTTORI, ASSEGNAZIONE ===

    /** @brief Image : costruttore di default, inizializza i campi dati con valori di default */
    Image();

    /** @brief Image : costruttore di copia */
    Image(const Image& image);

    /** @brief operator= : operatore di assegnazione */
    Image& operator=(const Image& image);


    // === GETTER ===

    const std::string& getDateCreated() const;
    const std::string& getImageCreator() const;
    const std::string& getImageCategory() const;
    std::pair<int, int> getImageAspectRatio() const;
    unsigned int getImageBitDepth() const;
    bool isCompressed() const;
    const std::string& getLocationTaken() const;


    // === SETTER ===

    void setDateCreated(const std::string& created);
    void setImageCreator(const std::string& creator);
    void setImageCategory(const std::string& ctg);
    void setImageAspectRatio(std::pair<int, int> ar);
    void setImageBitDepth(unsigned int bd);
    void setImageCompression(bool cmpr);
    void setImageLocationTaken(const std::string& loc);


    // === METODI SPECIFICI Image ===

    /** @brief getAspectRatioAsFloat : ritorna l'aspect ratio come float */
    float getAspectAsFloat() const;

    /**
     * @brief getTotalMegapixels : restituisce il numero totale di megapixels del media Image (in base alla risoluzione impostata)
     * @return float : numero di megapixels, espresso come: (resolutionWidth * resolutionHeight) / 1,000,000
     */
    float getMegaPixels() const;


    // == RIDEFINIZIONE VIRTUALI PURI IMediaResolution ===

    /**
     * @brief getResolution : ridefinizione virtuale puro ereditato da Utilities::IMediaResolution, ritorna la risoluzione
     * @return std::pair<int, int> : risoluzione dellimmagine, espressa come 'larghezza x altezza'
     */
    std::pair<int, int> getResolution() const override;

    /**
     * @brief setResolution : ridefinizione virtuale puro ereditato da Utilities::IMediaResolution, imposta la risoluzione
     * @param std::pair<int, int> : risoluzione dell'immagine da impostare (espressa come 'larghezza x altezza')
     */
    void setResolution(std::pair<int, int> resolution) override;

    /**
     * @brief matchesAspectRatio : ridefinizione virtuale puro ereditato da Utilities::IMediaResolution
     * @return bool : true se la risoluzione rispecchia l'aspect ratio, false altrimenti
     */
    bool matchesAspectRatio() const override;


    // == RIDEFINIZIONE VIRTUALI PURI AbstractMedia ===

    /** @brief hasLength : ridefinizione virtuale puro ereditato da AbstractMedia, ritorna sempre false */
    bool hasLength() const override;

    /** @brief hasResolution : ridefinizione virtuale puro ereditato da AbstractMedia, ritorna sempre true */
    bool hasResolution() const override;


    // == RIDEFINIZIONE VIRTUALI PURI AbstractFile ===

    /**
     * @brief clone : ridefinizione del metodo di clonazione ereditato da AbstractFile
     * @return Image* : puntatore a Image, tipo di ritorno covariante
     */
    Image* clone() const override;

    /** @brief accept : ridefinizione virtuale puro ereditato da AbstractFile per l'implementazione non-const del design pattern Visitor per il tipo Image */
    void accept(Visitors::IVisitor& visitor) override;

    /** @brief accept : ridefinizione virtuale puro ereditato da AbstractFile per l'implementazione const del design pattern Visitor per il tipo Image */
    void accept(Visitors::IConstVisitor& visitor) const override;

    /**
     * @brief displayStringType : ridefinizione virtuale puro ereditato da AbstractFile
     * @return std::string : stringa usata solamente per stampare/mostrare il tipo del media (e non come sostituzione al polimorfismo)
     */
    std::string displayStringType() const override;


    // === PERSISTENZA DATI JSON ===

    /** @brief toJson : ridefinizione virtuale puro ereditato da AbstractMedia per la persistenza dei dati in formato JSON, in modo specifico al tipo Image (commentato nella definizione) */
    QJsonObject toJson() const override;

    /** @brief fromJson :  ridefinizione virtuale puro ereditato da AbstractMedia per la persistenza dei dati in formato JSON, in modo specifico al tipo Image (commentato nella definizione) */
    void fromJson(const QJsonObject& obj) override;

private:

    // === CAMPI DATI ===

    std::string dateCreated;               // data creazione
    std::string imageCreator;              // creatore (fotografa/macchina fotografica)
    std::string imageCategory;             // categoria (foto, screenshot, etc...)
    std::pair<int, int> imageResolution;   // risoluzione
    std::pair<int, int> imageAspectRatio;  // aspect ratio
    unsigned int imageBitDepth;            // bitdepth (in bit)
    bool compression;                      // se use o non usa compressione
    std::string locationTaken;             // luogo creazione (se applicabile)
};

}
}


#endif // MODEL_MEDIA_IMAGE_H

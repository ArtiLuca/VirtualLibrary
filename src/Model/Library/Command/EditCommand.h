#ifndef MODEL_LIBRARY_EDIT_COMMAND_H
#define MODEL_LIBRARY_EDIT_COMMAND_H

#include "IAbstractCommand.h"
#include "Model/Library/Library.h"
#include "Model/Media/AbstractMedia.h"

#include <unordered_map>
#include <memory>

/** @brief EditCommand
 *
 *  EditCommand e' una sottoclasse concreta che deriva pubblicamente da IAbstractCommand.
 *  Implementa il design pattern "Command" per implementare l'operazione di modifica di un media della libreria.
 *
 *  EditCommand e' concreta in quanto va a ridefinire i due metodi virtuali puri 'execute' e 'undo' ereditati da IAbstractCommand.
 *  Il metodo 'execute' viene ridefinito per eseguire la modifica di un media, mantenendo una copia del media originale prima di applicare le modifiche.
 *  Il metodo 'undo' viene ridefinito per ripristinare il media appena modificato al suo stato originale, rimuovendo il media modificato e poi reinserendo la copia dell'originale.
 *  Il metodo 'getCommandInfo' viene ridefinito per mostrare dettagli sull'ultima operazione di modifica effettuata oppure l'ultimo annullamento di modifica effettuata.
 *
 */


namespace Model {
namespace Library {
namespace Command {

class EditCommand : public IAbstractCommand {

public:

    /**
     * @brief EditCommand : costruttore, inizializza i campi dati privati
     * @param lib : puntatore alla libreria
     * @param id : identificatore univoco del media
     * @param mediaEdits : mappa di modifiche
     */
    EditCommand(Library* lib, unsigned int id, const std::unordered_map<std::string, std::string>& mediaEdits);

    /**
     * @brief execute : ridefinizione metodo virtuale puro ereditato da IAbstractCommand, esegue la modifica del media
     * @throws MediaValidatorException se la modifica non ha avuto successo
     */
    void execute() override;

    /**
     * @brief undo : ridefinizione metodo virtuale puro ereditato da IAbstractCommand, esegue il "rollback" del media al suo stato originale
     */
    void undo() override;

    /**
     * @brief getCommandInfo : ridefinizione metodo virtuale puro ereditato da IAbstractCommand, restituisce dettagli ultima operazione di modifica
     * @return std::string : dettagli ultima operazione di modifica
     */
    std::string getCommandInfo() const override;

private:

    Library* libraryPtr;                                            // puntatore alla libreria multimediale
    unsigned int editedID;                                          // identificatore del media da modificare
    std::unordered_map<std::string, std::string> edits;             // mappa di coppie (nome/valore) delle modifiche
    std::shared_ptr<Media::AbstractMedia> originalMedia;            // smart pointer con copia del media originale
    bool edited;                                                    // indica se il media e' stato modificato oppure no
};

}
}
}

#endif // MODEL_LIBRARY_EDIT_COMMAND_H

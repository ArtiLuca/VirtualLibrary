#ifndef MODEL_LIBRARY_REMOVE_COMMAND_H
#define MODEL_LIBRARY_REMOVE_COMMAND_H

#include "IAbstractCommand.h"
#include "Model/Library/Library.h"
#include "Model/Media/AbstractMedia.h"

#include <memory>

/** @brief RemoveCommand
 *
 *  RemoveCommand e' una sottoclasse concreta che deriva pubblicamente da IAbstractCommand.
 *  Implementa il design pattern "Command" per implementate l'operazione di rimozione di un media della libreria.
 *
 *  RemoveCommand e' concreta in quanto va a ridefinire i due metodi virtuali puri 'execute' e 'undo' ereditati da IAbstractCommand,
 *  Il metodo 'execute' viene ridefinito per effettuare la rimozione di un media, salvandone una copia mediante il metodo polimorfo 'clone'.
 *  Il metodo 'undo' viene ridefinito per reinserire nuovamente in libreria il media appena rimosso utilizzando la copia salvata.
 *  Il metodo 'getCommandInfo' viene ridefinito per mostrare dettagli sull'ultimo media rimosso oppure reinserito.
 *
 */


namespace Model {
namespace Library {
namespace Command {

class RemoveCommand : public IAbstractCommand {

public:

    /**
     * @brief RemoveCommand : costruttore, inizializza i campi dati
     * @param lib : puntatore alla libreria
     * @param id : identificatore univoco del media da rimuovere
     */
    RemoveCommand(Library* lib, unsigned int id);

    /**
     * @brief execute : ridefinizione metodo virtuale puro ereditato da IAbstractCommand, esegue la rimozione del media
     */
    void execute() override;

    /**
     * @brief undo : ridefinizione metodo virtuale puro ereditato da IAbstractCommand, esegue il re-inserimento del media appena rimosso
     */
    void undo() override;

    /**
     * @brief getCommandInfo : ridefinizione metodo virtuale puro ereditato da IAbstractCommand, restituisce dettagli ultima operazione di rimozione
     * @return std::string : dettagli ultima operazione di rimozione
     */
    std::string getCommandInfo() const override;

private:

    Library* libraryPtr;                                         // puntatore alla libreria
    unsigned int removedID;                                      // identificatore del media
    std::shared_ptr<Media::AbstractMedia> backupMedia;           // copia del media rimosso
    bool removed;                                                // indica se il media e' stato rimosso oppure no
};

}
}
}

#endif // MODEL_LIBRARY_REMOVE_COMMAND_H

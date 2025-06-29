#ifndef MODEL_LIBRARY_INSERT_COMMAND_H
#define MODEL_LIBRARY_INSERT_COMMAND_H

#include "IAbstractCommand.h"
#include "Model/Library/Library.h"
#include "Model/Media/AbstractMedia.h"

#include <memory>

/** @brief InsertCommand
 *
 *  InsertCommand e' una sottoclasse concreta che deriva pubblicamente da IAbstractCommand.
 *  Implementa il design pattern "Command" per implementare l'operazione di inserimento di un nuovo media nella libreria.
 *
 *  InsertCommand e' concreta in quanto va a ridefinire i due metodi virtuali puri 'execute' e 'undo' ereditati da IAbstractCommand.
 *  Il metodo 'execute' viene ridefinito per eseguire l'inserimento di un media in libreria.
 *  Il metodo 'undo' viene ridefinito per rimuovere il media appena inserito.
 *  Il metodo 'getCommandInfo' viene ridefinito per mostrare dettagli sull'ultimo media inserito oppure rimosso.
 *
 */


namespace Model {
namespace Library {
namespace Command {

class InsertCommand : public IAbstractCommand {

public:

    /**
     * @brief InsertCommand : costruttore, inizializza campi dati privati
     * @param lib : puntatore alla libreria multimediale
     * @param media : smart pointer al media da inserire
     */
    InsertCommand(Library* lib, std::shared_ptr<Media::AbstractMedia> media);

    /**
     * @brief execute : ridefinizione metodo virtuale puro ereditato da IAbstractCommand, esegue l'inserimento del media nella libreria
     */
    void execute() override;

    /**
     * @brief undo : ridefinizione metodo virtuale puro ereditato da IAbstractCommand, rimuove il media appena aggiunto
     */
    void undo() override;

    /**
     * @brief getCommandInfo : ridefinizione metodo virtuale puro ereditato da IAbstractCommand, restituisce dettagli ultima operazione di inserimento
     * @return std::string : dettagli ultima operazione di inserimento
     */
    std::string getCommandInfo() const override;

private:

    Library* libraryPtr;                                      // puntatore alla libreria
    std::shared_ptr<Media::AbstractMedia> mediaPtr;           // smart pointer al media
    bool inserted;                                            // indica se inserito o meno
};

}
}
}

#endif // MODEL_LIBRARY_INSERT_COMMAND_H

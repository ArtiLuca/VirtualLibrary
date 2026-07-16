#ifndef MODEL_LIBRARY_I_ABSTRACT_COMMAND_H
#define MODEL_LIBRARY_I_ABSTRACT_COMMAND_H

#include <string>

/** @brief IAbstractCommand
 *
 *  IAbstractCommand rappresenta l'interfaccia base astratta per il design pattern Command.
 *  Ho deciso di utilizzare il design pattern Command per implementare le operazioni di Undo/Redo nella gestione della libreria multimediale.
 *  Ogni operazione eseguita (inserimento, rimozione, modifica) viene vista come un oggetto del tipo IAbstractCommand (o di una classe sua derivata).
 *
 *  IAbstractCommand e' astratta in quanto dispone dei due metodi virtuali puri 'execute' e 'undo' che vengono ridefiniti per implementare le operazioni Undo e Redo
 *  nel caso di inserimento, rimozione o modifica di un media in libreria.
 *  Inoltre, ho aggiunto il metodo virtuale puro 'getCommandInfo' che viene ridefinito per restituire una breve descrizione sull'ultima operazione Undo/Redo disponibile.
 *
 */


namespace Model {
namespace Library {
namespace Command {

class IAbstractCommand {

public:

    /** @brief ~IAbstractCommand : distruttore virtuale */
    virtual ~IAbstractCommand() = default;

    /** @brief execute : metodo virtuale puro, ridefinito per implementare l'operazione Redo */
    virtual void execute() = 0;

    /** @brief undo : metodo virtuale puro, ridefinito per implementare l'operazione Undo */
    virtual void undo() = 0;

    /** @brief getCommandInfo : metodo virtuale puro, ridefinito per ottenere una descrizione dell'ultima operazione Undo/Redo disponibile */
    virtual std::string getCommandInfo() const = 0;
};

}
}
}

#endif // MODEL_LIBRARY_I_ABSTRACT_COMMAND_H

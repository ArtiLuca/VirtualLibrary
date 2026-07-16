#ifndef MODEL_LOGGERS_I_MEDIA_LOGGER_H
#define MODEL_LOGGERS_I_MEDIA_LOGGER_H

#include <string>

/** @brief IMediaLogger
 *
 *  IMediaLogger rappresenta l'interfaccia base astratta per implementare il sistema di "logging" usato dalle classi Library e Manager.
 *  Viene ereditata dai vari Logger concreti per implementare un sistema di "logging" per mostrare/salvare le varie operazioni o aggiornamenti
 *  effettuati nella libreria.
 *
 *  IMediaLogger e' astratta in quanto dispone del metodo 'logMessage' che viene poi ridefinito nei vari Logger concreti.
 *
 */

namespace Model {
namespace Loggers {

class IMediaLogger {
public:

    /**
     * @brief ~IMediaLogger : distruttore virtuale di IMediaLogger
     */
    virtual ~IMediaLogger() = default;

    /**
     * @brief logMessage : virtuale puro, effettua il "logging" di un messaggio
     * @param msg : messagio di cui fare il "logging"
     */
    virtual void logMessage(const std::string& msg) = 0;
};

}
}

#endif // MODEL_LOGGERS_I_MEDIA_LOGGER_H

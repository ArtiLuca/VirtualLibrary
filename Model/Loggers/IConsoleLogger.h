#ifndef MODEL_LOGGERS_I_CONSOLER_LOGGER_H
#define MODEL_LOGGERS_I_CONSOLER_LOGGER_H

#include "IMediaLogger.h"

#include <iostream>
#include <string>

/** @brief IConsoleLogger
 *
 *  IConsoleLogger e' una sottoclasse concreta di IMediaLogger.
 *  Va a ridefinire il metodo virtuale puro 'logMessage' per effettuare il sistema di "logging" direttamente sul terminale.
 */

namespace Model {
namespace Loggers {

class IConsoleLogger : public IMediaLogger {
public:

    /**
     * @brief logMessage : virtuale puro ereditato da IMediaLogger, stampa su terminale la stringa con il messaggio
     * @param msg : messaggio da "loggare"
     */
    void logMessage(const std::string& msg) override {
        std::cout << "[ConsoleLogger]: " << msg << std::endl;
    }
};

}
}

#endif // MODEL_LOGGERS_I_CONSOLER_LOGGER_H

#ifndef LIBRARY_LOGGERS_LOG_LEVEL_H
#define LIBRARY_LOGGERS_LOG_LEVEL_H

/** @brief LogLevel
 *
 *  LogLevel e' una enum class utilizzata per gestire per gestire il grado di "severita" con cui effettuare il logging.
 *  I logger concreti associati alla libreria hanno di default il grado di severita' "Info".
 */

namespace Model {
namespace Loggers {

enum class LogLevel {

    None = 0,  // nessun logging
    Error = 1, // errori critici
    Info = 2,  // operazioni che hanno avuto successo, e altre generali meno frequenti
    Debug = 3  // operazioni frequenti, meno rilevanti
};

}
}

#endif // LIBRARY_LOGGERS_LOG_LEVEL_H

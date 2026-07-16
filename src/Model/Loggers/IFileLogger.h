#ifndef MODEL_LOGGERS_I_FILE_LOGGER_H
#define MODEL_LOGGERS_I_FILE_LOGGER_H

#include "IMediaLogger.h"

#include <fstream>
#include <string>

/** @brief IFileLogger
 *
 *  IFileLogger e' una sottoclasse concreta di IMediaLogger.
 *  Va a ridefinire il metodo virtuale puro 'logMessage' per effettuare il sistema di "logging" su file.
 *  Il suo costruttore apre un file in modalita' scrittura, effettuando le scritture a fine file.
 *
 */

namespace Model {
namespace Loggers {

class IFileLogger : public IMediaLogger {

private:

    std::ofstream outputPath;

public:

    /**
     * @brief IFileLogger : costruttore, apre il file in modalita' scrittura (append)
     * @param fileName : path del output file
     */
    explicit IFileLogger(const std::string& fileName) {
        outputPath.open(fileName, std::ios::out | std::ios::app);
        if (!outputPath.is_open()) {
            throw std::runtime_error("Coudl not open file: " + fileName);
        }
    }

    /** @brief distruttore */
    ~IFileLogger() override {
        if (outputPath.is_open()) {
            outputPath.close();
        }
    }

    /**
     * @brief logMessage : ridefinizione virtuale puro ereditato da IMediaLogger
     * @param msg : messaggio da "loggare"
     */
    void logMessage(const std::string& msg) override {
        if (outputPath.is_open()) {
            outputPath <<  "\n" << msg << std::endl;
        }
    }

    /**
     * @brief flush : svuota il buffer e chiude il file
     */
    void flush() {
        if (outputPath.is_open()) {
            outputPath.flush();
            outputPath.close();
        }
    }
};

}
}

#endif // MODEL_LOGGERS_I_FILE_LOGGER_H

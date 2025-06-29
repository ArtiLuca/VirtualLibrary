#include <QApplication>
#include "Model/Loggers/IFileLogger.h"
#include "Model/Library/Manager.h"
#include "Controller/Controller.h"
#include "View/Window.h"

using namespace View;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Model::Loggers::IFileLogger fileLogger("fileLog.log");
    Model::Library::Manager manager(&fileLogger);
    Controller::Controller c(&manager);

    Window window;
    window.setController(&c);

    window.resize(800, 600);
    window.show();

    return app.exec();
}


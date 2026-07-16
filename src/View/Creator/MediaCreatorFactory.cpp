#include "MediaCreatorFactory.h"
#include "AudioCreator.h"
#include "VideoCreator.h"
#include "EBookCreator.h"
#include "ImageCreator.h"

namespace View {
namespace Creator {

MediaCreatorFactory::MediaCreatorFactory(
    const QString& mediaType,
    Controller::Controller* c,
    QWidget* parent)
    : controller(c),
    createdWidget(nullptr),
    parentWidget(parent)
{
    if (mediaType == "AUDIO") {
        createdWidget = new AudioCreator(parent);
    }
    else if (mediaType == "VIDEO") {
        createdWidget = new VideoCreator(parent);
    }
    else if (mediaType == "EBOOK") {
        createdWidget = new EBookCreator(parent);
    }
    else if (mediaType == "IMAGE") {
        createdWidget = new ImageCreator(parent);
    }
    else {
        createdWidget = nullptr;
    }
}


QWidget* MediaCreatorFactory::fetchAndReset() {

    QWidget* tempWidet = createdWidget;
    createdWidget = nullptr;
    return tempWidet;
}

}
}


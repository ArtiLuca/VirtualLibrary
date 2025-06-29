#include "MediaViewerFactory.h"
#include "View/Viewer/AudioViewer.h"
#include "View/Viewer/VideoViewer.h"
#include "View/Viewer/EBookViewer.h"
#include "View/Viewer/ImageViewer.h"

namespace View {
namespace Viewer {

MediaViewerFactory::MediaViewerFactory(Controller::Controller* c, int ind, QWidget* parent)
    : controller(c),
    mediaIndex(ind),
    parentWidget(parent),
    createdWidget(nullptr)
{}

QWidget* MediaViewerFactory::fetchAndReset() {

    QWidget* tempWidget = createdWidget;
    createdWidget = nullptr;
    return tempWidget;
}

void MediaViewerFactory::visit(const Model::Media::Audio& audio) const {
    createdWidget = new AudioViewer(audio, mediaIndex, parentWidget);
}

void MediaViewerFactory::visit(const Model::Media::Video& video) const {
    createdWidget = new VideoViewer(video, mediaIndex, parentWidget);
}

void MediaViewerFactory::visit(const Model::Media::EBook& ebook) const {
    createdWidget = new EBookViewer(ebook, mediaIndex, parentWidget);
}

void MediaViewerFactory::visit(const Model::Media::Image& image) const {
    createdWidget = new ImageViewer(image, mediaIndex, parentWidget);
}

}
}

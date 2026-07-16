#include "MediaEditorFactory.h"
#include "Controller/Controller.h"

#include "View/Editor/AudioEditor.h"
#include "View/Editor/VideoEditor.h"
#include "View/Editor/EBookEditor.h"
#include "View/Editor/ImageEditor.h"

namespace View {
namespace Editor {

MediaEditorFactory::MediaEditorFactory(
    Controller::Controller* c,
    int ind,
    QWidget* parent)
    : controller(c),
    mediaIndex(ind),
    parentWidget(parent),
    createdWidget(nullptr)
{}

QWidget* MediaEditorFactory::fetchAndReset() {

    QWidget* tempWidget = createdWidget;
    createdWidget = nullptr;
    return tempWidget;
}


void MediaEditorFactory::visit(Model::Media::Audio& audio) {
    createdWidget = new AudioEditor(audio, mediaIndex, parentWidget);
}

void MediaEditorFactory::visit(Model::Media::Video& video) {
    createdWidget = new VideoEditor(video, mediaIndex, parentWidget);
}

void MediaEditorFactory::visit(Model::Media::EBook& ebook) {
    createdWidget = new EBookEditor(ebook, mediaIndex, parentWidget);
}

void MediaEditorFactory::visit(Model::Media::Image& image) {
    createdWidget = new ImageEditor(image, mediaIndex, parentWidget);
}

}
}

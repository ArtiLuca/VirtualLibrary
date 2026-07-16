#include "ConciseViewer.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QString>
#include <QLabel>
#include <QRadioButton>
#include <QMouseEvent>

namespace View {
namespace Viewer {

ConciseViewer::ConciseViewer(int ind, int mediaID, QString mediaType, QString mediaName, QWidget* parent)
    : QWidget(parent),
    mediaIndex(ind)
{
    setCursor(Qt::PointingHandCursor);

    mediaLayout = new QHBoxLayout(this);
    mediaLayout->setContentsMargins(4, 2, 4, 2);
    mediaLayout->setSpacing(8);

    mediaRadioButton = new QRadioButton(this);
    mediaIndexLabel = new QLabel(QString::number(mediaIndex), this);
    mediaIDLabel = new QLabel("[ID: " + QString::number(mediaID) + "]", this);
    mediaTypeLabel = new QLabel(mediaType, this);
    mediaNameLabel = new QLabel(mediaName, this);

    mediaLayout->addWidget(mediaRadioButton);
    mediaLayout->addWidget(mediaIndexLabel);
    mediaLayout->addWidget(mediaIDLabel);
    mediaLayout->addWidget(mediaTypeLabel);
    mediaLayout->addWidget(mediaNameLabel);
    mediaLayout->setAlignment(Qt::AlignLeft);

    // connect vecchio stile
    connect(mediaRadioButton, &QRadioButton::toggled,
            this, &ConciseViewer::onRadioButtonToggled);
}

int ConciseViewer::getMediaIndex() const { return mediaIndex; }

bool ConciseViewer::mediaSelected() const { return mediaRadioButton->isChecked(); }

void ConciseViewer::setMediaSelected(bool select) { mediaRadioButton->setChecked(select); }

void ConciseViewer::onRadioButtonToggled(bool checked) {
    emit selectedMediaChanged(mediaIndex, checked);
}

}
}

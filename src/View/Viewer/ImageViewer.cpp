#include "ImageViewer.h"
#include "Model/Media/Image.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFormLayout>
#include <QLineEdit>
#include <QString>

namespace View {
namespace Viewer {

ImageViewer::ImageViewer(const Model::Media::Image& image, unsigned int ind, QWidget* parent)
    : QWidget(parent),
    imageIndex(ind),
    imageCopy(image)
{

    // layout principale
    imageViewerLayout = new QVBoxLayout(this);
    imageViewerLayout->setSpacing(10);
    imageViewerLayout->setContentsMargins(8, 8, 8, 8);

    // icona
    QPixmap imageIcon(":/rsc/image.png");
    imageIconLabel = new QLabel;
    imageIconLabel->setPixmap(imageIcon.scaled(48, 48));
    imageIconLabel->setAlignment(Qt::AlignLeft);
    imageViewerLayout->addWidget(imageIconLabel);
    imageIconLabelText = new QLabel;
    imageIconLabelText->setText("Image Media");
    imageIconLabelText->setStyleSheet("font: 12pt;");
    imageIconLabelText->setAlignment(Qt::AlignLeft);
    imageViewerLayout->addWidget(imageIconLabelText);

    // form layout
    imageFormLayout = new QFormLayout;
    imageFormLayout->setLabelAlignment(Qt::AlignLeft);
    imageFormLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    imageFormLayout->setHorizontalSpacing(12);
    imageFormLayout->setVerticalSpacing(6);
    imageFormLayout->setContentsMargins(0, 0, 0, 0);

    // attributi comuni
    idLabel = new QLabel; imageFormLayout->addRow("ID: ", idLabel);
    nameLabel = new QLabel; imageFormLayout->addRow("Name: ", nameLabel);
    ratingLabel = new QLabel; imageFormLayout->addRow("Rating: ", ratingLabel);
    pathLabel = new QLabel; imageFormLayout->addRow("Path: ", pathLabel);
    sizeLabel = new QLabel; imageFormLayout->addRow("Size (MB): ", sizeLabel);
    uploaderLabel = new QLabel; imageFormLayout->addRow("Uploader: ", uploaderLabel);
    formatLabel = new QLabel; imageFormLayout->addRow("Format: ", formatLabel);

    // attributi Image
    dateCreatedLabel = new QLabel; imageFormLayout->addRow("Date Created: ", dateCreatedLabel);
    creatorLabel = new QLabel; imageFormLayout->addRow("Creator: ", creatorLabel);
    categoryLabel = new QLabel; imageFormLayout->addRow("Category: ", categoryLabel);

    // risoluzione Image
    resolutionWidthLabel = new QLabel; resolutionHeightLabel = new QLabel;
    resolutionContainer = new QWidget(this);
    resolutionContainer->setMaximumWidth(220);
    resolutionLayout = new QHBoxLayout(resolutionContainer);
    resolutionLayout->setContentsMargins(0, 0, 0, 0);
    resolutionLayout->addWidget(resolutionWidthLabel);
    resolutionLayout->addWidget(new QLabel("x"));
    resolutionLayout->addWidget(resolutionHeightLabel);
    resolutionLayout->setSpacing(5);
    imageFormLayout->addRow("Resolution: ", resolutionContainer);
    imageFormLayout->setAlignment(resolutionContainer, Qt::AlignLeft);

    // aspect ratio Image
    aspectWidthLabel = new QLabel; aspectHeightLabel = new QLabel;
    aspectRatioContainer = new QWidget(this);
    aspectRatioContainer->setMaximumWidth(220);
    aspectRatioLayout = new QHBoxLayout(aspectRatioContainer);
    aspectRatioLayout->setContentsMargins(0, 0, 0, 0);
    aspectRatioLayout->addWidget(aspectWidthLabel);
    aspectRatioLayout->addWidget(new QLabel(":"));
    aspectRatioLayout->addWidget(aspectHeightLabel);
    aspectRatioLayout->setSpacing(5);
    imageFormLayout->addRow("Aspect Ratio: ", aspectRatioContainer);
    imageFormLayout->setAlignment(aspectRatioContainer, Qt::AlignLeft);

    bitdepthLabel = new QLabel; imageFormLayout->addRow("Bitdepth (bits): ", bitdepthLabel);
    compressionLabel = new QLabel; imageFormLayout->addRow("Compressed? ", compressionLabel);
    locationTakenLabel = new QLabel; imageFormLayout->addRow("Location Taken: ", locationTakenLabel);

    imageFormLayout->setAlignment(Qt::AlignLeft);
    imageFormLayout->setFormAlignment(Qt::AlignHCenter);
    imageViewerLayout->addLayout(imageFormLayout);

    // label
    imageScoreValue = new QLabel("Score Value: ");
    imageViewerLayout->addWidget(imageScoreValue);
    imageScoreLabel = new QLabel("Score Label: ");
    imageViewerLayout->addWidget(imageScoreLabel);
    imageScoreInfo = new QLabel();

    // buttons
    scoreButton = new QPushButton("Score");
    scoreInfoButton = new QPushButton("Score Info");
    closeButton = new QPushButton("Close");

    scoreInfoButton->setEnabled(false);
    scoreInfoButton->setToolTip("Calculate Score to enable");

    // connect buttons
    connect(scoreButton, &QPushButton::clicked,
            this, &ImageViewer::onImageScoreButtonClicked);
    connect(scoreInfoButton, &QPushButton::clicked,
            this, &ImageViewer::onImageScoreInfoButtonClicked);
    connect(closeButton, &QPushButton::clicked,
            this, &ImageViewer::onCloseClicked);

    // button layout
    imageButtonLayout = new QHBoxLayout;
    imageButtonLayout->setAlignment(Qt::AlignLeft);
    imageButtonLayout->setSpacing(8);
    imageButtonLayout->setContentsMargins(0, 0, 0, 0);
    imageButtonLayout->addWidget(scoreButton);
    imageButtonLayout->addWidget(scoreInfoButton);
    imageButtonLayout->addWidget(closeButton);
    imageViewerLayout->addLayout(imageButtonLayout);

    setCommonAttributes();
    setImageAttributes();

}


void ImageViewer::setScore(float scoreValue, const QString& scoreLabel, const QString& scoreInfo) {

    int val = scoreValue;
    imageScoreValue->setText("Score Value: " + QString::number(val) + "/100");
    imageScoreLabel->setText("Score Label: " + scoreLabel);
    imageScoreInfo->setText(scoreInfo);
    scoreInfoButton->setEnabled(true);
}


void ImageViewer::onCloseClicked() {
    emit closed();
}

void ImageViewer::onImageScoreButtonClicked() {

    emit scoreRequested(imageIndex, this);
}

void ImageViewer::onImageScoreInfoButtonClicked() {

    QMessageBox::information(this, "Audio Scoring Info", imageScoreInfo->text());

}



void ImageViewer::setCommonAttributes() {

    idLabel->setText(QString::fromStdString(std::to_string(imageCopy.getUniqueID())));
    nameLabel->setText(QString::fromStdString(imageCopy.getMediaName()));
    ratingLabel->setText(QString::fromStdString(std::to_string(imageCopy.getMediaRating())) + "/100");
    pathLabel->setText(QString::fromStdString(imageCopy.getFilePath()));
    sizeLabel->setText(QString::fromStdString(std::to_string(imageCopy.getFileSize()).substr(0, 4)) + " MB");
    uploaderLabel->setText(QString::fromStdString(imageCopy.getMediaUploader()));
    formatLabel->setText(QString::fromStdString(imageCopy.getMediaFormat()));
}

void ImageViewer::setImageAttributes() {

    dateCreatedLabel->setText(QString::fromStdString(imageCopy.getDateCreated()));
    creatorLabel->setText(QString::fromStdString(imageCopy.getImageCreator()));
    categoryLabel->setText(QString::fromStdString(imageCopy.getImageCategory()));
    resolutionWidthLabel->setText(QString::fromStdString(std::to_string(imageCopy.getResolution().first)));
    resolutionHeightLabel->setText(QString::fromStdString(std::to_string(imageCopy.getResolution().second)));
    aspectWidthLabel->setText(QString::fromStdString(std::to_string(imageCopy.getImageAspectRatio().first)));
    aspectHeightLabel->setText(QString::fromStdString(std::to_string(imageCopy.getImageAspectRatio().second)));
    bitdepthLabel->setText(QString::fromStdString(std::to_string(imageCopy.getImageBitDepth())) + "-bit");
    if (imageCopy.isCompressed()) compressionLabel->setText("true");
    else compressionLabel->setText("false");
    if (!imageCopy.getLocationTaken().empty()) locationTakenLabel->setText(QString::fromStdString(imageCopy.getLocationTaken()));
    else locationTakenLabel->setText("Not Given");
}


}
}

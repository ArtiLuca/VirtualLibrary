#include "EBookViewer.h"
#include "Model/Media/EBook.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QDialogButtonBox>

namespace View {
namespace Viewer {

EBookViewer::EBookViewer(const Model::Media::EBook& ebook, unsigned int ind, QWidget* parent)
    : QWidget(parent),
    ebookIndex(ind),
    ebookCopy(ebook)
{
    // layout principale
    ebookViewerLayout = new QVBoxLayout(this);
    ebookViewerLayout->setSpacing(10);
    ebookViewerLayout->setContentsMargins(8, 8, 8, 8);

    // icona
    QPixmap ebookIcon(":/rsc/ebook.png");
    ebookIconLabel = new QLabel;
    ebookIconLabel->setPixmap(ebookIcon.scaled(48, 48));
    ebookIconLabel->setAlignment(Qt::AlignLeft);
    ebookViewerLayout->addWidget(ebookIconLabel);
    ebookIconTextLabel = new QLabel;
    ebookIconTextLabel->setText("EBook Media");
    ebookIconTextLabel->setStyleSheet("font: 12pt;");
    ebookIconTextLabel->setAlignment(Qt::AlignLeft);
    ebookViewerLayout->addWidget(ebookIconTextLabel);

    // form layout
    ebookFormLayout = new QFormLayout;
    ebookFormLayout->setLabelAlignment(Qt::AlignLeft);
    ebookFormLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    ebookFormLayout->setHorizontalSpacing(12);
    ebookFormLayout->setVerticalSpacing(6);
    ebookFormLayout->setContentsMargins(0, 0, 0, 0);

    // attributi comuni
    idLabel = new QLabel; ebookFormLayout->addRow("ID: ", idLabel);
    nameLabel = new QLabel; ebookFormLayout->addRow("Name: ", nameLabel);
    ratingLabel = new QLabel; ebookFormLayout->addRow("Rating: ", ratingLabel);
    pathLabel = new QLabel; ebookFormLayout->addRow("Path: ", pathLabel);
    sizeLabel = new QLabel; ebookFormLayout->addRow("Size (MB): ", sizeLabel);
    uploaderLabel = new QLabel; ebookFormLayout->addRow("Uploader: ", uploaderLabel);
    formatLabel = new QLabel; ebookFormLayout->addRow("Format: ", formatLabel);

    // attributi EBook
    authorLabel = new QLabel; ebookFormLayout->addRow("Author: ", authorLabel);
    publisherLabel = new QLabel; ebookFormLayout->addRow("Publisher: ", publisherLabel);
    releaseYearLabel = new QLabel; ebookFormLayout->addRow("Released: ", releaseYearLabel);
    categoryLabel = new QLabel; ebookFormLayout->addRow("Category: ", categoryLabel);
    lengthLabel = new QLabel; ebookFormLayout->addRow("Length (pages): ", lengthLabel);
    languageLabel = new QLabel; ebookFormLayout->addRow("Language ", languageLabel);
    isbnLabel = new QLabel; ebookFormLayout->addRow("ISBN: ", isbnLabel);
    hasImagesLabel = new QLabel; ebookFormLayout->addRow("Images? ", hasImagesLabel);
    coverPathLabel = new QLabel; ebookFormLayout->addRow("Cover Path: ", coverPathLabel);

    ebookFormLayout->setAlignment(Qt::AlignLeft);
    ebookFormLayout->setFormAlignment(Qt::AlignHCenter);
    ebookViewerLayout->addLayout(ebookFormLayout);

    // label
    ebookScoreValue = new QLabel("Score Value: ");
    ebookViewerLayout->addWidget(ebookScoreValue);
    ebookScoreLabel = new QLabel("Score Label: ");
    ebookViewerLayout->addWidget(ebookScoreLabel);
    ebookScoreInfo = new QLabel();
    //ebookViewerLayout->addWidget(ebookScoreInfo);
    ebookValidISBN = new QLabel("Valid ISBN: -");
    ebookViewerLayout->addWidget(ebookValidISBN);

    // buttons
    scoreButton = new QPushButton("Score");
    scoreInfoButton = new QPushButton("Score Info");
    isbnCheckButton = new QPushButton("Check ISBN");
    closeButton = new QPushButton("Close");

    scoreInfoButton->setEnabled(false);
    scoreInfoButton->setToolTip("Calculate Score to enable");

    // connect buttons
    connect(scoreButton, &QPushButton::clicked,
            this, &EBookViewer::onEBookScoreButtonClicked);
    connect(scoreInfoButton, &QPushButton::clicked,
            this, &EBookViewer::onEBookScoreInfoButtonClicked);
    connect(isbnCheckButton, &QPushButton::clicked,
            this, &EBookViewer::onCheckISBNButtonClicked);
    connect(closeButton, &QPushButton::clicked,
            this, &EBookViewer::oncloseButtonClicked);

    // buttons layout
    ebookButtonLayout = new QHBoxLayout;
    ebookButtonLayout->setAlignment(Qt::AlignLeft);
    ebookButtonLayout->setSpacing(8);
    ebookButtonLayout->setContentsMargins(0, 0, 0, 0);
    ebookButtonLayout->addWidget(isbnCheckButton);
    ebookButtonLayout->addWidget(scoreButton);
    ebookButtonLayout->addWidget(scoreInfoButton);
    ebookButtonLayout->addWidget(closeButton);
    ebookViewerLayout->addLayout(ebookButtonLayout);

    setCommonAttributes();
    setEBookAttributes();
}


void EBookViewer::setScore(float scoreValue, const QString& scoreLabel, const QString& scoreInfo) {

    int val = scoreValue;
    ebookScoreValue->setText("Score Value: " + QString::number(val) + "/100");
    ebookScoreLabel->setText("Score Label: " + scoreLabel);
    ebookScoreInfo->setText(scoreInfo);
    scoreInfoButton->setEnabled(true);
}

void EBookViewer::setEBookISBNValidation(const QString& checkISBN) {
    ebookValidISBN->setText("ISBN: " + checkISBN);
}


void EBookViewer::onEBookScoreButtonClicked() {

    emit scoreRequested(ebookIndex, this);
}

void EBookViewer::onEBookScoreInfoButtonClicked() {

    QMessageBox::information(this, "Audio Scoring Info", ebookScoreInfo->text());

}

void EBookViewer::onCheckISBNButtonClicked() {

    emit isbnValidateRequest(ebookIndex, this);
}

void EBookViewer::oncloseButtonClicked() {
    emit closed();
}


void EBookViewer::setCommonAttributes() {

    idLabel->setText(QString::fromStdString(std::to_string(ebookCopy.getUniqueID())));
    nameLabel->setText(QString::fromStdString(ebookCopy.getMediaName()));
    ratingLabel->setText(QString::fromStdString(std::to_string(ebookCopy.getMediaRating())) + "/100");
    pathLabel->setText(QString::fromStdString(ebookCopy.getFilePath()));
    sizeLabel->setText(QString::fromStdString(std::to_string(ebookCopy.getFileSize()).substr(0, 4)) + " MB");
    uploaderLabel->setText(QString::fromStdString(ebookCopy.getMediaUploader()));
    formatLabel->setText(QString::fromStdString(ebookCopy.getMediaFormat()));
}

void EBookViewer::setEBookAttributes() {

    authorLabel->setText(QString::fromStdString(ebookCopy.getAuthor()));
    publisherLabel->setText(QString::fromStdString(ebookCopy.getPublisher()));
    releaseYearLabel->setText(QString::fromStdString(std::to_string(ebookCopy.getReleaseYear())));
    categoryLabel->setText(QString::fromStdString(ebookCopy.getCategory()));
    lengthLabel->setText(QString::fromStdString(std::to_string(ebookCopy.getMediaLength())) + " pages");
    languageLabel->setText(QString::fromStdString(ebookCopy.getLanguage()));
    isbnLabel->setText(QString::fromStdString(ebookCopy.getISBN()));

    if (ebookCopy.hasImages()) hasImagesLabel->setText("true");
    else hasImagesLabel->setText("false");

    if (ebookCopy.hasCoverPath()) coverPathLabel->setText(QString::fromStdString(ebookCopy.getCoverImagePath()));
    else coverPathLabel->setText("...");
}

}
}

#include "AudioViewer.h"
#include "Model/Media/Audio.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFormLayout>
#include <QLineEdit>
#include <QString>
#include <QMessageBox>

namespace View {
namespace Viewer {

AudioViewer::AudioViewer(const Model::Media::Audio& audio, unsigned int ind, QWidget* parent)
    : QWidget(parent),
    audioIndex(ind),
    audioCopy(audio)
{
    // layout principale
    audioViewerLayout = new QVBoxLayout(this);
    audioViewerLayout->setSpacing(10);
    audioViewerLayout->setContentsMargins(8, 8, 8, 8);

    // icona
    QPixmap audioIcon(":/rsc/audio.png");
    audioIconLabel = new QLabel;
    audioIconLabel->setPixmap(audioIcon.scaled(48, 48));
    audioIconLabel->setAlignment(Qt::AlignLeft);
    audioViewerLayout->addWidget(audioIconLabel);
    audioIconLabelText = new QLabel;
    audioIconLabelText->setText("Audio Media");
    audioIconLabelText->setStyleSheet("font: 12pt;");
    audioIconLabelText->setAlignment(Qt::AlignLeft);
    audioViewerLayout->addWidget(audioIconLabelText);

    // form layout
    audioFormLayout = new QFormLayout;
    audioFormLayout->setLabelAlignment(Qt::AlignLeft);
    audioFormLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    audioFormLayout->setHorizontalSpacing(12);
    audioFormLayout->setVerticalSpacing(6);
    audioFormLayout->setContentsMargins(0, 0, 0, 0);

    // attributi comuni
    idLabel = new QLabel; audioFormLayout->addRow("ID: ", idLabel);
    nameLabel = new QLabel; audioFormLayout->addRow("Name: ", nameLabel);
    ratingLabel = new QLabel; audioFormLayout->addRow("Rating: ", ratingLabel);
    pathLabel = new QLabel; audioFormLayout->addRow("Path: ", pathLabel);
    sizeLabel = new QLabel; audioFormLayout->addRow("Size (MB): ", sizeLabel);
    uploaderLabel = new QLabel; audioFormLayout->addRow("Uploader: ", uploaderLabel);
    formatLabel = new QLabel; audioFormLayout->addRow("Format: ", formatLabel);

    // attributi Audio
    artistLabel = new QLabel; audioFormLayout->addRow("Artist:", artistLabel);
    releaseYearLabel = new QLabel; audioFormLayout->addRow("Released: ", releaseYearLabel);
    genreLabel = new QLabel; audioFormLayout->addRow("Genre: ", genreLabel);
    albumLabel = new QLabel; audioFormLayout->addRow("Album:", albumLabel);
    lengthLabel = new QLabel; audioFormLayout->addRow("Length (minutes): ", lengthLabel);
    bitRateLabel = new QLabel; audioFormLayout->addRow("Bitrate (kbps): ", bitRateLabel);
    sampleRateLabel = new QLabel; audioFormLayout->addRow("Samplerate (kHz): ", sampleRateLabel);
    bitDepthLabel = new QLabel; audioFormLayout->addRow("Bitdepth (bits): ", bitDepthLabel);
    channelsLabel = new QLabel; audioFormLayout->addRow("Audio Channels: ", channelsLabel);
    collaboratorsLabel = new QLabel; audioFormLayout->addRow("Collaborators: ", collaboratorsLabel);

    audioFormLayout->setAlignment(Qt::AlignLeft);
    audioFormLayout->setFormAlignment(Qt::AlignHCenter);
    audioViewerLayout->addLayout(audioFormLayout);

    // label
    audioScoreValue = new QLabel("Score Value: ");
    audioViewerLayout->addWidget(audioScoreValue);
    audioScoreLabel = new QLabel("Score Label: ");
    audioViewerLayout->addWidget(audioScoreLabel);
    audioScoreInfo = new QLabel();

    // buttons
    scoreButton = new QPushButton("Score");
    scoreInfoButton = new QPushButton("Score Info");
    closeButton = new QPushButton("Close");

    scoreInfoButton->setEnabled(false);
    scoreInfoButton->setToolTip("Calculate Score to enable");

    // connect buttons
    connect(scoreButton, &QPushButton::clicked,
            this, &AudioViewer::onAudioScoreButtonClicked);
    connect(scoreInfoButton, &QPushButton::clicked,
            this, &AudioViewer::onAudioScoreInfoButtonClicked);
    connect(closeButton, &QPushButton::clicked,
            this, &AudioViewer::onCloseClicked);

    // layout buttons
    audioButtonLayout = new QHBoxLayout;
    audioButtonLayout->setAlignment(Qt::AlignLeft);
    audioButtonLayout->setSpacing(8);
    audioButtonLayout->setContentsMargins(0, 0, 0, 0);
    audioButtonLayout->addWidget(scoreButton);
    audioButtonLayout->addWidget(scoreInfoButton);
    audioButtonLayout->addWidget(closeButton);
    audioViewerLayout->addLayout(audioButtonLayout);

    setCommonAttributes();
    setAudioAttributes();
}


void AudioViewer::setScore(float scoreValue, const QString& scoreLabel, const QString& scoreInfo) {

    int val = scoreValue;
    audioScoreValue->setText("Score Value: " + QString::number(val) + "/100");
    audioScoreLabel->setText("Score Label: " + scoreLabel);
    audioScoreInfo->setText(scoreInfo);
    scoreInfoButton->setEnabled(true);
}



void AudioViewer::onCloseClicked() {
    emit closed();
}

void AudioViewer::onAudioScoreButtonClicked() {
    emit scoreRequested(audioIndex, this);
}

void AudioViewer::onAudioScoreInfoButtonClicked() {

    QMessageBox::information(this, "Audio Scoring Info", audioScoreInfo->text());

}


void AudioViewer::setCommonAttributes() {

    idLabel->setText(QString::fromStdString(std::to_string(audioCopy.getUniqueID())));
    nameLabel->setText(QString::fromStdString(audioCopy.getMediaName()));
    ratingLabel->setText(QString::fromStdString(std::to_string(audioCopy.getMediaRating())) + "/100");
    pathLabel->setText(QString::fromStdString(audioCopy.getFilePath()));
    sizeLabel->setText(QString::fromStdString(std::to_string(audioCopy.getFileSize()).substr(0, 5)) + " MB");
    uploaderLabel->setText(QString::fromStdString(audioCopy.getMediaUploader()));
    formatLabel->setText(QString::fromStdString(audioCopy.getMediaFormat()));
}

void AudioViewer::setAudioAttributes() {

    artistLabel->setText(QString::fromStdString(audioCopy.getArtist()));
    releaseYearLabel->setText(QString::fromStdString(std::to_string(audioCopy.getReleaseYear())));
    genreLabel->setText(QString::fromStdString(audioCopy.getGenre()));
    albumLabel->setText(QString::fromStdString(audioCopy.getAlbum()));
    lengthLabel->setText(QString::fromStdString(std::to_string(audioCopy.getMediaLength())) + " minutes");
    bitRateLabel->setText(QString::fromStdString(std::to_string(audioCopy.getBitRate())) + " kbps");
    sampleRateLabel->setText(QString::fromStdString(std::to_string(audioCopy.getSampleRate()).substr(0, 5)) + " kHz");
    bitDepthLabel->setText(QString::fromStdString(std::to_string(audioCopy.getBitDepth())) + "-bit");
    channelsLabel->setText(QString::fromStdString(std::to_string(audioCopy.getAudioChannels())) + " channels");
    collaboratorsLabel->setText(QString::fromStdString(audioCopy.getCollaborators()));

}

}
}

#include "VideoViewer.h"
#include "Model/Media/Video.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFormLayout>
#include <QLineEdit>
#include <QString>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QDialog>

namespace View {
namespace Viewer {

VideoViewer::VideoViewer(const Model::Media::Video& video, unsigned int ind, QWidget* parent)
    : QWidget(parent),
    videoIndex(ind),
    videoCopy(video)
{
    // layout principale
    videoViewerLayout = new QVBoxLayout(this);
    videoViewerLayout->setSpacing(10);
    videoViewerLayout->setContentsMargins(8, 8, 8, 8);

    // icona
    QPixmap videoIcon(":/rsc/video.png");
    videoIconLabel = new QLabel;
    videoIconLabel->setPixmap(videoIcon.scaled(48, 48));
    videoIconLabel->setAlignment(Qt::AlignLeft);
    videoViewerLayout->addWidget(videoIconLabel);
    videoIconTextLabel = new QLabel("Video Media");
    videoIconTextLabel->setStyleSheet("font: 12pt;");
    videoIconTextLabel->setAlignment(Qt::AlignLeft);
    videoViewerLayout->addWidget(videoIconTextLabel);

    // form layout
    videoFormLayout = new QFormLayout;
    videoFormLayout = new QFormLayout();
    videoFormLayout->setLabelAlignment(Qt::AlignLeft);
    videoFormLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    videoFormLayout->setHorizontalSpacing(12);
    videoFormLayout->setVerticalSpacing(6);
    videoFormLayout->setContentsMargins(0, 0, 0, 0);

    // attributi comuni
    idLabel = new QLabel; videoFormLayout->addRow("ID:  ", idLabel);
    nameLabel  = new QLabel; videoFormLayout->addRow("Name:  ", nameLabel);
    ratingLabel  = new QLabel; videoFormLayout->addRow("Rating:  ", ratingLabel);
    pathLabel  = new QLabel; videoFormLayout->addRow("Path:  ", pathLabel);
    sizeLabel  = new QLabel; videoFormLayout->addRow("Size (MB):  ", sizeLabel);
    uploaderLabel  = new QLabel; videoFormLayout->addRow("Uploader:  ", uploaderLabel);
    formatLabel  = new QLabel; videoFormLayout->addRow("Format:  ", formatLabel);
    videoFormLayout->setAlignment(Qt::AlignLeft);

    // attributi Video
    directorLabel = new QLabel; videoFormLayout->addRow("Director:  ", directorLabel);
    genreLabel = new QLabel; videoFormLayout->addRow("Genre:  ", genreLabel);
    releaseYearLabel = new QLabel; videoFormLayout->addRow("Release Year:  ", releaseYearLabel);
    languagesLabel = new QLabel; videoFormLayout->addRow("Audio Language(s):  ", languagesLabel);
    subtitlesLabel = new QLabel; videoFormLayout->addRow("Subtitle List:  ", subtitlesLabel);
    lengthLabel = new QLabel; videoFormLayout->addRow("Length (min):  ", lengthLabel);

    resolutionWidthLabel = new QLabel; resolutionHeightLabel = new QLabel;
    resolutionContainer = new QWidget(this);
    resolutionContainer->setMaximumWidth(220);
    resolutionLayout = new QHBoxLayout(resolutionContainer);
    resolutionLayout->setContentsMargins(0, 0, 0, 0);
    resolutionLayout->addWidget(resolutionWidthLabel);
    resolutionLayout->addWidget(new QLabel("x"));
    resolutionLayout->addWidget(resolutionHeightLabel);
    videoFormLayout->addRow("Resolution", resolutionContainer);
    videoFormLayout->setAlignment(resolutionContainer, Qt::AlignLeft);

    framerateLabel = new QLabel; videoFormLayout->addRow("Framerate (fps):", framerateLabel);
    colordepthLabel = new QLabel; videoFormLayout->addRow("Colordepth (bits):", colordepthLabel);

    videoFormLayout->setAlignment(Qt::AlignLeft);
    videoFormLayout->setFormAlignment(Qt::AlignHCenter);
    videoViewerLayout->addLayout(videoFormLayout);

    // label
    videoScoreValue = new QLabel("Score Value: ");
    videoViewerLayout->addWidget(videoScoreValue);
    videoScoreLabel = new QLabel("Score Label: ");
    videoViewerLayout->addWidget(videoScoreLabel);
    videoScoreInfo = new QLabel();

    videoDurationLabel = new QLabel("Video Duration: ");
    videoViewerLayout->addWidget(videoDurationLabel);

    // buttons
    scoreButton = new QPushButton("Score");
    scoreInfoButton = new QPushButton("Score Info");
    videoDurationButton = new QPushButton("Duration");
    closeButton = new QPushButton("Close");

    scoreInfoButton->setEnabled(false);
    scoreInfoButton->setToolTip("Calculate Score to enable");

    // connect buttons
    connect(scoreButton, &QPushButton::clicked,
            this, &VideoViewer::onVideoScoreButtonClicked);
    connect(scoreInfoButton, &QPushButton::clicked,
            this, &VideoViewer::onVideoScoreInfoButtonClicked);
    connect(videoDurationButton, &QPushButton::clicked,
            this, &VideoViewer::onVideoDurationButtonClicked);
    connect(closeButton, &QPushButton::clicked,
            this, &VideoViewer::onCloseClicked);

    // layout buttons
    videoButtonLayout = new QHBoxLayout;
    videoButtonLayout->setAlignment(Qt::AlignLeft);
    videoButtonLayout->setSpacing(8);
    videoButtonLayout->setContentsMargins(0, 0, 0, 0);
    videoButtonLayout->addWidget(scoreButton);
    videoButtonLayout->addWidget(scoreInfoButton);
    videoButtonLayout->addWidget(videoDurationButton);
    videoButtonLayout->addWidget(closeButton);
    videoViewerLayout->addLayout(videoButtonLayout);

    setCommonAttributes();
    setVideoAttributes();

}


void VideoViewer::setScore(float scoreValue, const QString& scoreLabel, const QString& scoreInfo) {

    int val = scoreValue;
    videoScoreValue->setText("Score Value: " + QString::number(val) + "/100");
    videoScoreLabel->setText("Score Label: " + scoreLabel);
    videoScoreInfo->setText(scoreInfo);
    scoreInfoButton->setEnabled(true);
}

void VideoViewer::setVideoDuration(const QString& duration) {

    videoDurationLabel->setText(duration);
}


void VideoViewer::onCloseClicked() {

    emit closed();
}

void VideoViewer::onVideoScoreButtonClicked() {

    emit scoreRequested(videoIndex, this);
}

void VideoViewer::onVideoDurationButtonClicked() {

    emit videoDurationRequested(videoIndex, this);
}

void VideoViewer::onVideoScoreInfoButtonClicked() {

    QMessageBox::information(this, "Audio Scoring Info", videoScoreInfo->text());

}


void VideoViewer::setCommonAttributes() {

    idLabel->setText(QString::fromStdString(std::to_string(videoCopy.getUniqueID())));
    nameLabel->setText(QString::fromStdString(videoCopy.getMediaName()));
    ratingLabel->setText(QString::fromStdString(std::to_string(videoCopy.getMediaRating())) + "/100");
    pathLabel->setText(QString::fromStdString(videoCopy.getFilePath()));
    sizeLabel->setText(QString::fromStdString(std::to_string(videoCopy.getFileSize()).substr(0, 6)) + " MB");
    uploaderLabel->setText(QString::fromStdString(videoCopy.getMediaUploader()));
    formatLabel->setText(QString::fromStdString(videoCopy.getMediaFormat()));
}

void VideoViewer::setVideoAttributes() {

    directorLabel->setText(QString::fromStdString(videoCopy.getDirector()));
    genreLabel->setText(QString::fromStdString(videoCopy.getGenre()));
    releaseYearLabel->setText(QString::fromStdString(std::to_string(videoCopy.getCreationYear())));
    languagesLabel->setText(QString::fromStdString(videoCopy.getLanguage()));
    subtitlesLabel->setText(QString::fromStdString(videoCopy.getSubtitles()));
    lengthLabel->setText(QString::fromStdString(std::to_string(videoCopy.getMediaLength())) + " minutes");
    framerateLabel->setText(QString::fromStdString(std::to_string(videoCopy.getFrameRate())) + " fps");
    resolutionWidthLabel->setText(QString::fromStdString(std::to_string(videoCopy.getResolution().first)));
    resolutionHeightLabel->setText(QString::fromStdString(std::to_string(videoCopy.getResolution().second)));
    colordepthLabel->setText(QString::fromStdString(std::to_string(videoCopy.getVideoColorDepth())) + "-bit");
}

}
}

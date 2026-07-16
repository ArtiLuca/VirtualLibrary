#include "VideoCreator.h"
#include "Model/Media/Video.h"
#include "Model/Builders/VideoBuilder.h"

namespace View {
namespace Creator {

const QString VideoCreator::REQUIRED_ATTRIBUTE_STYLE = "color: #000000; font-weight: bold;";
const QString VideoCreator::OPTIONAL_ATTRIBUTE_STYLE = "color: #000000; font-style: italic;";

VideoCreator::VideoCreator(QWidget* parent)
    : QWidget(parent)
{
    // layout principale
    videoCreatorMainLayout = new QVBoxLayout(this);
    videoCreatorMainLayout->setSpacing(10);
    videoCreatorMainLayout->setContentsMargins(8, 8, 8, 8);

    // form layout
    videoCreatorFormLayout = new QFormLayout();
    videoCreatorFormLayout->setLabelAlignment(Qt::AlignLeft);
    videoCreatorFormLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    videoCreatorFormLayout->setHorizontalSpacing(12);
    videoCreatorFormLayout->setVerticalSpacing(6);
    videoCreatorFormLayout->setContentsMargins(0, 0, 0, 0);

    creatorTypeLabel = new QLabel("Video Creator");
    creatorTypeLabel->setStyleSheet("font-weight: bold;");
    videoCreatorFormLayout->addRow("", creatorTypeLabel);

    // setup form
    setAbstractFileAttributes();
    setAbstractMediaAttributes();
    setVideoAttributes();
    setVideoToolTips();

    videoCreatorMainLayout->addLayout(videoCreatorFormLayout);

    // aggiunta pulsanti
    videoCreatorButtonBox = new QDialogButtonBox(Qt::Horizontal, this);
    videoCreatorButtonBox->addButton("Create", QDialogButtonBox::AcceptRole);
    videoCreatorButtonBox->addButton("Cancel", QDialogButtonBox::RejectRole);
    videoCreatorMainLayout->addWidget(videoCreatorButtonBox);

    // connect pulsanti
    connect(videoCreatorButtonBox, &QDialogButtonBox::accepted,
            this, &VideoCreator::onCreateButtonClicked);
    connect(videoCreatorButtonBox, &QDialogButtonBox::rejected,
            this, &VideoCreator::onCancelButtonClicked);


}


void VideoCreator::onCreateButtonClicked() {

    QMap<QString, QString> videoAttributes;

    const auto videoAttributeNames = Model::Builders::VideoBuilder::VIDEO_ATTRIBUTES;

    for (const auto& attr : videoAttributeNames) {

        QString attrName = QString::fromStdString(attr);
        QString attrValue;

        if (attrName == "path") attrValue = pathEdit->text();
        else if (attrName == "size") attrValue = QString::number(sizeSpinBox->value());
        else if (attrName == "name") attrValue = nameEdit->text();
        else if (attrName == "uploader") attrValue = uploaderEdit->text();
        else if (attrName == "format") attrValue = formatComboBox->currentText();
        else if (attrName == "rating") attrValue = QString::number(ratingSpinBox->value());
        else if (attrName == "director") attrValue = directorEdit->text();
        else if (attrName == "genre") attrValue = genreEdit->text();
        else if (attrName == "releaseYear") attrValue = QString::number(releaseYearSpinBox->value());
        else if (attrName == "length") attrValue = QString::number(lengthSpinBox->value());
        else if (attrName == "framerate") attrValue = QString::number(framerateSpinBox->value());
        else if (attrName == "width") attrValue = QString::number(resolutionWidthSpinBox->value());
        else if (attrName == "height") attrValue = QString::number(resolutionHeightSpinBox->value());
        else if (attrName == "colordepth") attrValue = QString::number(colordepthSpinBox->value());
        else if (attrName == "subtitles") attrValue = subtitlesEdit->text();
        else if (attrName == "language") attrValue = languageEdit->text();

        videoAttributes.insert(attrName, attrValue);
    }

    emit createRequested(videoAttributes);
}

void VideoCreator::onCancelButtonClicked() {

    emit createCancelled();
}


void VideoCreator::setAbstractFileAttributes() {

    idEdit = new QLineEdit(this);
    idEdit->setText(QString::number(Model::Media::AbstractMedia::uniqueIDCounter));
    idEdit->setReadOnly(true);
    videoCreatorFormLayout->addRow("ID:", idEdit);

    pathEdit = new QLineEdit(this);
    pathEdit->setPlaceholderText(QString::fromStdString(Model::Media::AbstractFile::defaultPath));
    QLabel* pathLabel = new QLabel("Path:"); pathLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(pathLabel, pathEdit);

    sizeSpinBox = new QDoubleSpinBox(this);
    sizeSpinBox->setSuffix(" MB");
    sizeSpinBox->setMinimum(Model::Media::AbstractFile::MIN_FILE_SIZE);
    sizeSpinBox->setMaximum(Model::Media::AbstractFile::MAX_FILE_SIZE);
    sizeSpinBox->setValue(Model::Media::Video::defaultVideoSize);
    QLabel* sizeLabel = new QLabel("Size:"); sizeLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(sizeLabel, sizeSpinBox);
}

void VideoCreator::setAbstractMediaAttributes() {

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText(QString::fromStdString(Model::Media::AbstractMedia::defaultName));
    QLabel* nameLabel = new QLabel("Name:"); nameLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(nameLabel, nameEdit);

    uploaderEdit = new QLineEdit(this);
    uploaderEdit->setPlaceholderText(QString::fromStdString(Model::Media::AbstractMedia::defaultUploader));
    QLabel* uploaderLabel = new QLabel("Uploader:"); uploaderLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(uploaderLabel, uploaderEdit);

    formatComboBox = new QComboBox(this);
    for (const auto& fmt : Model::Media::Video::VIDEO_FORMATS) {
        formatComboBox->addItem(QString::fromStdString(fmt));
    }
    QLabel* formatLabel = new QLabel("Format:"); formatLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(formatLabel, formatComboBox);

    ratingSpinBox = new QSpinBox(this);
    ratingSpinBox->setMinimum(Model::Media::AbstractMedia::MIN_MEDIA_RATING);
    ratingSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_MEDIA_RATING);
    ratingSpinBox->setValue(Model::Media::AbstractMedia::defaultRating);
    QLabel* ratingLabel = new QLabel("Rating:"); ratingLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(ratingLabel, ratingSpinBox);
}

void VideoCreator::setVideoAttributes() {

    directorEdit = new QLineEdit(this);
    directorEdit->setPlaceholderText(QString::fromStdString(Model::Media::Video::defaultVideoDirector));
    QLabel* directorLabel = new QLabel("Director:"); directorLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(directorLabel, directorEdit);

    genreEdit = new QLineEdit(this);
    genreEdit->setPlaceholderText(QString::fromStdString(Model::Media::Video::defaultVideoGenre));
    QLabel* genreLabel = new QLabel("Genre:"); genreLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(genreLabel, genreEdit);

    releaseYearSpinBox = new QSpinBox(this);
    releaseYearSpinBox->setMinimum(Model::Media::AbstractMedia::MIN_RELEASE_YEAR);
    releaseYearSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_RELEASE_YEAR);
    releaseYearSpinBox->setValue(Model::Media::Video::defaultVideoReleaseYear);
    QLabel* releaseYearLabel = new QLabel("Release Year:"); releaseYearLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(releaseYearLabel, releaseYearSpinBox);

    lengthSpinBox = new QSpinBox(this);
    lengthSpinBox->setSuffix(" min");
    lengthSpinBox->setMinimum(Model::Media::Video::MIN_VIDEO_LENGTH);
    lengthSpinBox->setMaximum(Model::Media::Video::MAX_VIDEO_LENGTH);
    lengthSpinBox->setValue(Model::Media::Video::defaultVideoLength);
    QLabel* lengthLabel = new QLabel("Length:"); lengthLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(lengthLabel, lengthSpinBox);

    framerateSpinBox = new QSpinBox(this);
    framerateSpinBox->setSuffix(" fps");
    framerateSpinBox->setMinimum(Model::Media::Video::MIN_VIDEO_FRAME_RATE);
    framerateSpinBox->setMaximum(Model::Media::Video::MAX_VIDEO_FRAME_RATE);
    framerateSpinBox->setValue(Model::Media::Video::defaultVideoFrameRate);
    QLabel* framerateLabel = new QLabel("Framerate:"); framerateLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(framerateLabel, framerateSpinBox);

    resolutionWidthSpinBox = new QSpinBox(this);
    resolutionWidthSpinBox->setMinimumWidth(100);
    resolutionHeightSpinBox = new QSpinBox(this);
    resolutionHeightSpinBox->setMinimumWidth(100);

    resolutionWidthSpinBox->setMinimum(Model::Media::Video::MIN_VIDEO_RESOLUTION_WIDTH);
    resolutionWidthSpinBox->setMaximum(Model::Media::Video::MAX_VIDEO_RESOLUTION_WIDTH);
    resolutionWidthSpinBox->setValue(Model::Media::Video::defaultVideoResolution.first);
    resolutionHeightSpinBox->setMinimum(Model::Media::Video::MIN_VIDEO_RESOLUTION_HEIGHT);
    resolutionHeightSpinBox->setMaximum(Model::Media::Video::MAX_VIDEO_RESOLUTION_HEIGHT);
    resolutionHeightSpinBox->setValue(Model::Media::Video::defaultVideoResolution.second);

    resolutionContainer = new QWidget(this);
    resolutionContainer->setMaximumWidth(220);
    resolutionLayout = new QHBoxLayout(resolutionContainer);
    resolutionLayout->setContentsMargins(0, 0, 0, 0);
    resolutionLayout->addWidget(resolutionWidthSpinBox);
    resolutionLayout->addWidget(new QLabel("x"));
    resolutionLayout->addWidget(resolutionHeightSpinBox);
    resolutionLayout->setSpacing(5);
    QLabel* resolutionLabel = new QLabel("Resolution:"); resolutionLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(resolutionLabel, resolutionContainer);
    videoCreatorFormLayout->setAlignment(resolutionContainer, Qt::AlignLeft);

    colordepthSpinBox = new QSpinBox(this);
    colordepthSpinBox->setSuffix("-bit");
    colordepthSpinBox->setMinimum(Model::Media::Video::MIN_VIDEO_COLOR_DEPTH);
    colordepthSpinBox->setMaximum(Model::Media::Video::MAX_VIDEO_COLOR_DEPTH);
    colordepthSpinBox->setValue(Model::Media::Video::defaultVideoColorDepth);
    QLabel* colordepthLabel = new QLabel("Colordepth:"); colordepthLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(colordepthLabel, colordepthSpinBox);

    subtitlesEdit = new QLineEdit(this);
    subtitlesEdit->setPlaceholderText(QString::fromStdString(Model::Media::Video::defaultSubtitles));
    QLabel* subtitlesLabel = new QLabel("Subtitles:"); subtitlesLabel->setStyleSheet(OPTIONAL_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(subtitlesLabel, subtitlesEdit);

    languageEdit = new QLineEdit(this);
    languageEdit->setPlaceholderText(QString::fromStdString(Model::Media::Video::defaultVideoLanguage));
    QLabel* languageLabel = new QLabel("Language:"); languageLabel->setStyleSheet(OPTIONAL_ATTRIBUTE_STYLE);
    videoCreatorFormLayout->addRow(languageLabel, languageEdit);
}

void VideoCreator::setVideoToolTips() {

    ratingSpinBox->setToolTip("Rating must be defined in range (0-100)");
    lengthSpinBox->setToolTip("Video length must be defined in range [45-220] minutes");
    resolutionWidthSpinBox->setToolTip("Video resolution must match 16:9 aspect ratio");
    resolutionHeightSpinBox->setToolTip("Video resolution must match 16:9 aspect ratio");
    framerateSpinBox->setToolTip("Video framerate must be defined in range [24-120] fps");
    colordepthSpinBox->setToolTip("Video colordepth must be defined in range [8-16] bits");
}



}
}








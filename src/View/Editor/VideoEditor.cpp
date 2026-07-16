#include "VideoEditor.h"
#include "Model/Media/Video.h"
#include "Model/Builders/VideoBuilder.h"

namespace View {
namespace Editor {

VideoEditor::VideoEditor(
    const Model::Media::Video& video,
    unsigned int ind,
    QWidget* parent)
    : QWidget(parent),
    videoIndex(ind),
    videoCopy(video)
{
    // layout principale
    videoEditorMainLayout = new QVBoxLayout(this);
    videoEditorMainLayout->setSpacing(8);
    videoEditorMainLayout->setContentsMargins(8, 8, 8, 8);

    // form layout
    videoEditorFormLayout = new QFormLayout();
    videoEditorFormLayout->setLabelAlignment(Qt::AlignLeft);
    videoEditorFormLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    videoEditorFormLayout->setHorizontalSpacing(12);
    videoEditorFormLayout->setVerticalSpacing(6);
    videoEditorFormLayout->setContentsMargins(0, 0, 0, 0);

    editorTypeLabel = new QLabel("Video Editor");
    editorTypeLabel->setStyleSheet("font-weight: bold;");
    videoEditorFormLayout->addRow("", editorTypeLabel);

    setAbstractFileAttributes();
    setAbstractMediaAttributes();
    setVideoAttributes();
    setVideoEditorToolTips();

    videoEditorMainLayout->addLayout(videoEditorFormLayout);

    // aggiunta pulasanti
    videoEditorButtonBox = new QDialogButtonBox(Qt::Horizontal, this);
    videoEditorButtonBox->addButton("Confirm", QDialogButtonBox::AcceptRole);
    videoEditorButtonBox->addButton("Cancel", QDialogButtonBox::RejectRole);
    videoEditorMainLayout->addWidget(videoEditorButtonBox);

    // connect pulsanti
    connect(videoEditorButtonBox, &QDialogButtonBox::accepted,
            this, &VideoEditor::onConfirmButtonClicked);
    connect(videoEditorButtonBox, &QDialogButtonBox::rejected,
            this, &VideoEditor::onCancelButtonClicked);
}


void VideoEditor::onConfirmButtonClicked() {

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

    emit mediaEditsConfirmed(videoIndex, videoAttributes);
}

void VideoEditor::onCancelButtonClicked() {

    emit closed();
}


void VideoEditor::setAbstractFileAttributes() {

    idEdit = new QLineEdit(this);
    idEdit->setText(QString::number(videoCopy.getUniqueID()));
    idEdit->setReadOnly(true);
    videoEditorFormLayout->addRow("ID:", idEdit);

    pathEdit = new QLineEdit(this);
    pathEdit->setText(QString::fromStdString(videoCopy.getFilePath()));
    videoEditorFormLayout->addRow("Path:", pathEdit);

    sizeSpinBox = new QDoubleSpinBox(this);
    sizeSpinBox->setSuffix(" MB");
    sizeSpinBox->setMinimum(Model::Media::AbstractFile::MIN_FILE_SIZE);
    sizeSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_FILE_SIZE);
    sizeSpinBox->setValue(videoCopy.getFileSize());
    videoEditorFormLayout->addRow("Size:", sizeSpinBox);
}

void VideoEditor::setAbstractMediaAttributes() {

    nameEdit = new QLineEdit(this);
    nameEdit->setText(QString::fromStdString(videoCopy.getMediaName()));
    videoEditorFormLayout->addRow("Name:", nameEdit);

    uploaderEdit = new QLineEdit(this);
    uploaderEdit->setText(QString::fromStdString(videoCopy.getMediaUploader()));
    videoEditorFormLayout->addRow("Uploader:", uploaderEdit);

    QString videoFormat = QString::fromStdString(videoCopy.getMediaFormat());
    int formatIndex = -1;
    formatComboBox = new QComboBox(this);
    for (unsigned int i = 0; i < Model::Media::Video::VIDEO_FORMATS.size(); ++i) {
        QString fmt = QString::fromStdString(Model::Media::Video::VIDEO_FORMATS[i]);
        formatComboBox->addItem(fmt);
        if (fmt == videoFormat) {
            formatIndex = i;
        }
        if (formatIndex >= 0) formatComboBox->setCurrentIndex(formatIndex);
    }
    videoEditorFormLayout->addRow("Format:", formatComboBox);

    ratingSpinBox = new QSpinBox(this);
    ratingSpinBox->setMinimum(Model::Media::AbstractMedia::MIN_MEDIA_RATING);
    ratingSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_MEDIA_RATING);
    ratingSpinBox->setValue(videoCopy.getMediaRating());
    videoEditorFormLayout->addRow("Rating:", ratingSpinBox);

}

void VideoEditor::setVideoAttributes() {

    directorEdit = new QLineEdit(this);
    directorEdit->setText(QString::fromStdString(videoCopy.getDirector()));
    videoEditorFormLayout->addRow("Director:", directorEdit);

    genreEdit = new QLineEdit(this);
    genreEdit->setText(QString::fromStdString(videoCopy.getGenre()));
    videoEditorFormLayout->addRow("Genre:", genreEdit);


    releaseYearSpinBox = new QSpinBox(this);
    releaseYearSpinBox->setMinimum(Model::Media::AbstractMedia::MIN_RELEASE_YEAR);
    releaseYearSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_RELEASE_YEAR);
    releaseYearSpinBox->setValue(videoCopy.getCreationYear());
    videoEditorFormLayout->addRow("Release Year:", releaseYearSpinBox);

    lengthSpinBox = new QSpinBox(this);
    lengthSpinBox->setSuffix(" min");
    lengthSpinBox->setMinimum(Model::Media::Video::MIN_VIDEO_LENGTH);
    lengthSpinBox->setMaximum(Model::Media::Video::MAX_VIDEO_LENGTH);
    lengthSpinBox->setValue(videoCopy.getMediaLength());
    videoEditorFormLayout->addRow("Length:", lengthSpinBox);


    framerateSpinBox = new QSpinBox(this);
    framerateSpinBox->setSuffix(" fps");
    framerateSpinBox->setMinimum(Model::Media::Video::MIN_VIDEO_FRAME_RATE);
    framerateSpinBox->setMaximum(Model::Media::Video::MAX_VIDEO_FRAME_RATE);
    framerateSpinBox->setValue(videoCopy.getFrameRate());
    videoEditorFormLayout->addRow("Framerate:", framerateSpinBox);


    resolutionWidthSpinBox = new QSpinBox(this);
    resolutionWidthSpinBox->setMinimumWidth(100);
    resolutionHeightSpinBox = new QSpinBox(this);
    resolutionHeightSpinBox->setMinimumWidth(100);

    resolutionWidthSpinBox->setMinimum(Model::Media::Video::MIN_VIDEO_RESOLUTION_WIDTH);
    resolutionWidthSpinBox->setMaximum(Model::Media::Video::MAX_VIDEO_RESOLUTION_WIDTH);
    resolutionWidthSpinBox->setValue(videoCopy.getResolution().first);
    resolutionHeightSpinBox->setMinimum(Model::Media::Video::MIN_VIDEO_RESOLUTION_HEIGHT);
    resolutionHeightSpinBox->setMaximum(Model::Media::Video::MAX_VIDEO_RESOLUTION_HEIGHT);
    resolutionHeightSpinBox->setValue(videoCopy.getResolution().second);

    resolutionContainer = new QWidget(this);
    resolutionContainer->setMaximumWidth(220);
    resolutionLayout = new QHBoxLayout(resolutionContainer);
    resolutionLayout->setContentsMargins(0, 0, 0, 0);
    resolutionLayout->addWidget(resolutionWidthSpinBox);
    resolutionLayout->addWidget(new QLabel("x"));
    resolutionLayout->addWidget(resolutionHeightSpinBox);
    resolutionLayout->setSpacing(5);
    videoEditorFormLayout->addRow("Resolution:", resolutionContainer);
    videoEditorFormLayout->setAlignment(resolutionContainer, Qt::AlignLeft);

    colordepthSpinBox = new QSpinBox(this);
    colordepthSpinBox->setSuffix("-bit");
    colordepthSpinBox->setMinimum(Model::Media::Video::MIN_VIDEO_COLOR_DEPTH);
    colordepthSpinBox->setMaximum(Model::Media::Video::MAX_VIDEO_COLOR_DEPTH);
    colordepthSpinBox->setValue(videoCopy.getVideoColorDepth());
    videoEditorFormLayout->addRow("Colordepth:", colordepthSpinBox);

    subtitlesEdit = new QLineEdit(this);
    if (videoCopy.getSubtitles().empty()) subtitlesEdit->setText("Not given");
    else subtitlesEdit->setText(QString::fromStdString(videoCopy.getSubtitles()));
    videoEditorFormLayout->addRow("Subtitles:", subtitlesEdit);

    languageEdit = new QLineEdit(this);
    if (videoCopy.getLanguage().empty()) languageEdit->setText("Not given");
    else languageEdit->setText(QString::fromStdString(videoCopy.getLanguage()));
    videoEditorFormLayout->addRow("Language:", languageEdit);

}

void VideoEditor::setVideoEditorToolTips() {

    ratingSpinBox->setToolTip("Rating must be defined in range (0-100)");
    lengthSpinBox->setToolTip("Video length must be defined in range [45-220] minutes");
    resolutionWidthSpinBox->setToolTip("Video resolution must match 16:9 aspect ratio");
    resolutionHeightSpinBox->setToolTip("Video resolution must match 16:9 aspect ratio");
    framerateSpinBox->setToolTip("Video framerate must be defined in range [24-120] fps");
    colordepthSpinBox->setToolTip("Video colordepth must be defined in range [8-16] bits");
}

}
}

#include "AudioEditor.h"
#include "Model/Media/Audio.h"
#include "Model/Builders/AudioBuilder.h"

namespace View {
namespace Editor {

AudioEditor::AudioEditor(
    const Model::Media::Audio& audio,
    unsigned int ind,
    QWidget* parent)
    : QWidget(parent),
    audioIndex(ind),
    audioCopy(audio)
{
    // layout principale
    audioEditorMainLayout = new QVBoxLayout(this);
    audioEditorMainLayout->setSpacing(8);
    audioEditorMainLayout->setContentsMargins(8, 8, 8, 8);

    // form layout
    audioEditorFormLayout = new QFormLayout();
    audioEditorFormLayout->setLabelAlignment(Qt::AlignLeft);
    audioEditorFormLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    audioEditorFormLayout->setHorizontalSpacing(12);
    audioEditorFormLayout->setVerticalSpacing(6);
    audioEditorFormLayout->setContentsMargins(0, 0, 0, 0);

    editorTypeLabel = new QLabel("Audio Editor");
    editorTypeLabel->setStyleSheet("font-weight: bold;");
    audioEditorFormLayout->addRow("", editorTypeLabel);

    setAbstractFileAttributes();
    setAbstractMediaAttributes();
    setAudioAttributes();
    setAudioEditorToolTips();

    audioEditorMainLayout->addLayout(audioEditorFormLayout);


    // aggiunta pulasanti
    audioEditorButtonBox = new QDialogButtonBox(Qt::Horizontal, this);
    audioEditorButtonBox->addButton("Confirm", QDialogButtonBox::AcceptRole);
    audioEditorButtonBox->addButton("Cancel", QDialogButtonBox::RejectRole);
    audioEditorMainLayout->addWidget(audioEditorButtonBox);

    // connect pulsanti
    connect(audioEditorButtonBox, &QDialogButtonBox::accepted,
            this, &AudioEditor::onConfirmButtonClicked);
    connect(audioEditorButtonBox, &QDialogButtonBox::rejected,
            this, &AudioEditor::onCancelButtonClicked);
}


void AudioEditor::onConfirmButtonClicked() {

    QMap<QString, QString> audioAttributes;

    const auto audioAttributeNames = Model::Builders::AudioBuilder::AUDIO_ATTRIBUTES;

    for (const auto& attr : audioAttributeNames) {

        QString attrName = QString::fromStdString(attr);
        QString attrValue;

        if (attrName == "path") attrValue = pathEdit->text();
        else if (attrName == "size") attrValue = QString::number(sizeSpinBox->value());
        else if (attrName == "name") attrValue = nameEdit->text();
        else if (attrName == "uploader") attrValue = uploaderEdit->text();
        else if (attrName == "format") attrValue = formatComboBox->currentText();   //formatEdit->text();
        else if (attrName == "rating") attrValue = QString::number(ratingSpinBox->value());
        else if (attrName == "artist") attrValue = artistEdit->text();
        else if (attrName == "genre") attrValue = genreEdit->text();
        else if (attrName == "album") attrValue = albumEdit->text();
        else if (attrName == "releaseYear") attrValue = QString::number(releaseYearSpinBox->value());
        else if (attrName == "length") attrValue = QString::number(lengthSpinBox->value());
        else if (attrName == "bitrate") attrValue = QString::number(bitrateSpinBox->value());
        else if (attrName == "samplerate") attrValue = QString::number(sampleRateSpinBox->value());
        else if (attrName == "bitdepth") attrValue = QString::number(bitdepthSpinBox->value());
        else if (attrName == "channels") attrValue = QString::number(channelsSpinBox->value());
        else if (attrName == "collaborators") attrValue = collaboratorsEdit->text();

        audioAttributes.insert(attrName, attrValue);
    }

    emit mediaEditsConfirmed(audioIndex, audioAttributes);
}

void AudioEditor::onCancelButtonClicked() {

    emit closed();
}


void AudioEditor::setAbstractFileAttributes() {

    idEdit = new QLineEdit(this);
    idEdit->setText(QString::number(audioCopy.getUniqueID()));
    idEdit->setReadOnly(true);
    audioEditorFormLayout->addRow("ID:", idEdit);

    pathEdit = new QLineEdit(this);
    pathEdit->setText(QString::fromStdString(audioCopy.getFilePath()));
    audioEditorFormLayout->addRow("Path:", pathEdit);

    sizeSpinBox = new QDoubleSpinBox(this);
    sizeSpinBox->setSuffix(" MB");
    sizeSpinBox->setMinimum(Model::Media::AbstractFile::MIN_FILE_SIZE);
    sizeSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_FILE_SIZE);
    sizeSpinBox->setValue(audioCopy.getFileSize());
    audioEditorFormLayout->addRow("Size:", sizeSpinBox);
}

void AudioEditor::setAbstractMediaAttributes() {

    nameEdit = new QLineEdit(this);
    nameEdit->setText(QString::fromStdString(audioCopy.getMediaName()));
    audioEditorFormLayout->addRow("Name:", nameEdit);

    uploaderEdit = new QLineEdit(this);
    uploaderEdit->setText(QString::fromStdString(audioCopy.getMediaUploader()));
    audioEditorFormLayout->addRow("Uploader:", uploaderEdit);

    QString audioFormat = QString::fromStdString(audioCopy.getMediaFormat());
    int formatIndex = -1;
    formatComboBox = new QComboBox(this);
    for (unsigned int i = 0; i < Model::Media::Audio::AUDIO_FORMATS.size(); ++i) {
        QString fmt = QString::fromStdString(Model::Media::Audio::AUDIO_FORMATS[i]);
        formatComboBox->addItem(fmt);
        if (fmt == audioFormat) {
            formatIndex = i;
        }
        if (formatIndex >= 0) formatComboBox->setCurrentIndex(formatIndex);
    }
    audioEditorFormLayout->addRow("Format:", formatComboBox);

    ratingSpinBox = new QSpinBox(this);
    ratingSpinBox->setMinimum(Model::Media::AbstractMedia::MIN_MEDIA_RATING);
    ratingSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_MEDIA_RATING);
    ratingSpinBox->setValue(audioCopy.getMediaRating());
    audioEditorFormLayout->addRow("Rating:", ratingSpinBox);
}

void AudioEditor::setAudioAttributes() {

    artistEdit = new QLineEdit(this);
    artistEdit->setText(QString::fromStdString(audioCopy.getArtist()));
    audioEditorFormLayout->addRow("Artist:", artistEdit);

    genreEdit = new QLineEdit(this);
    genreEdit->setText(QString::fromStdString(audioCopy.getGenre()));
    audioEditorFormLayout->addRow("Genre:", genreEdit);

    albumEdit = new QLineEdit(this);
    albumEdit->setText(QString::fromStdString(audioCopy.getAlbum()));
    audioEditorFormLayout->addRow("Album:", albumEdit);

    releaseYearSpinBox = new QSpinBox(this);
    releaseYearSpinBox->setMinimum(Model::Media::AbstractMedia::MIN_RELEASE_YEAR);
    releaseYearSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_RELEASE_YEAR);
    releaseYearSpinBox->setValue(audioCopy.getReleaseYear());
    audioEditorFormLayout->addRow("Release Year:", releaseYearSpinBox);

    lengthSpinBox = new QSpinBox(this);
    lengthSpinBox->setSuffix(" min");
    lengthSpinBox->setMinimum(Model::Media::Audio::MIN_AUDIO_LENGTH);
    lengthSpinBox->setMaximum(Model::Media::Audio::MAX_AUDIO_LENGTH);
    lengthSpinBox->setValue(audioCopy.getMediaLength());
    audioEditorFormLayout->addRow("Length:", lengthSpinBox);

    bitrateSpinBox = new QSpinBox(this);
    bitrateSpinBox->setSuffix(" kbps");
    bitrateSpinBox->setMinimum(Model::Media::Audio::MIN_AUDIO_BIT_RATE);
    bitrateSpinBox->setMaximum(Model::Media::Audio::MAX_AUDIO_BITRATE);
    bitrateSpinBox->setValue(audioCopy.getBitRate());
    audioEditorFormLayout->addRow("Bitrate:", bitrateSpinBox);

    sampleRateSpinBox = new QDoubleSpinBox(this);
    sampleRateSpinBox->setSuffix(" kHz");
    sampleRateSpinBox->setMinimum(Model::Media::Audio::MIN_AUDIO_SAMPLE_RATE);
    sampleRateSpinBox->setMaximum(Model::Media::Audio::MAX_AUDIO_SAMPLE_RATE);
    sampleRateSpinBox->setValue(audioCopy.getSampleRate());
    audioEditorFormLayout->addRow("Samplerate:", sampleRateSpinBox);

    bitdepthSpinBox = new QSpinBox(this);
    bitdepthSpinBox->setSuffix("-bit");
    bitdepthSpinBox->setMinimum(Model::Media::Audio::MIN_AUDIO_BIT_DEPTH);
    bitdepthSpinBox->setMaximum(Model::Media::Audio::MAX_AUDIO_BIT_DEPTH);
    bitdepthSpinBox->setValue(audioCopy.getBitDepth());
    audioEditorFormLayout->addRow("Bitdepth:", bitdepthSpinBox);

    channelsSpinBox = new QSpinBox(this);
    channelsSpinBox->setMinimum(Model::Media::Audio::MIN_AUDIO_CHANNELS);
    channelsSpinBox->setMaximum(Model::Media::Audio::MAX_AUDIO_CHANNELS);
    channelsSpinBox->setValue(audioCopy.getAudioChannels());
    audioEditorFormLayout->addRow("Audio Channels:", channelsSpinBox);

    collaboratorsEdit = new QLineEdit(this);
    if (audioCopy.getCollaborators().empty()) collaboratorsEdit->setText("Not given");
    else collaboratorsEdit->setText(QString::fromStdString(audioCopy.getCollaborators()));
    audioEditorFormLayout->addRow("Collaborators:", collaboratorsEdit);
}

void AudioEditor::setAudioEditorToolTips() {

    ratingSpinBox->setToolTip("Rating must be defined in range (0-100)");
    lengthSpinBox->setToolTip("Audio must have length defined in range [1-15] minutes");
    bitrateSpinBox->setToolTip("Audio must have bitrate defined in range [32-320] kbps");
    sampleRateSpinBox->setToolTip("Audio must have samplerate defined in range [8-384] kHz");
    bitdepthSpinBox->setToolTip("Audio must have bidepth set in range [1-32] bits");
    channelsSpinBox->setToolTip("Audio must have channels defined in range [1-8]");
}


}
}

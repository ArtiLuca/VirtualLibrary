#include "AudioCreator.h"
#include "Model/Media/Audio.h"
#include "Model/Builders/AudioBuilder.h"

namespace View {
namespace Creator {

const QString AudioCreator::REQUIRED_ATTRIBUTE_STYLE = "color: #000000; font-weight: bold;";
const QString AudioCreator::OPTIONAL_ATTRIBUTE_STYLE = "color: #000000; font-style: italic;";

AudioCreator::AudioCreator(QWidget* parent)
    : QWidget(parent)
{
    // layout principale
    audioCreatorMainLayout = new QVBoxLayout(this);
    audioCreatorMainLayout->setSpacing(10);
    audioCreatorMainLayout->setContentsMargins(8, 8, 8, 8);

    // form layout
    audioCreatorFormLayout = new QFormLayout();
    audioCreatorFormLayout->setLabelAlignment(Qt::AlignRight);
    audioCreatorFormLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    audioCreatorFormLayout->setHorizontalSpacing(12);
    audioCreatorFormLayout->setVerticalSpacing(6);
    audioCreatorFormLayout->setContentsMargins(0, 0, 0, 0);

    creatorTypeLabel = new QLabel("Audio Creator");
    creatorTypeLabel->setStyleSheet("font-weight: bold;");
    audioCreatorFormLayout->addRow("", creatorTypeLabel);

    // setup form
    setAbstractFileAttributes();
    setAbstractMediaAttributes();
    setAudioAttributes();
    setAudioToolTips();

    audioCreatorMainLayout->addLayout(audioCreatorFormLayout);

    // aggiunta pulsanti
    audioCreatorButtonBox = new QDialogButtonBox(Qt::Horizontal, this);
    audioCreatorButtonBox->addButton("Create", QDialogButtonBox::AcceptRole);
    audioCreatorButtonBox->addButton("Cancel", QDialogButtonBox::RejectRole);
    audioCreatorMainLayout->addWidget(audioCreatorButtonBox);

    // connect pulsanti
    connect(audioCreatorButtonBox, &QDialogButtonBox::accepted,
            this, &AudioCreator::onCreateButtonClicked);
    connect(audioCreatorButtonBox, &QDialogButtonBox::rejected,
            this, &AudioCreator::onCancelButtonClicked);


}


void AudioCreator::onCreateButtonClicked() {

    QMap<QString, QString> audioAttributes;

    const auto audioAttributeNames = Model::Builders::AudioBuilder::AUDIO_ATTRIBUTES;

    for (const auto& attr : audioAttributeNames) {

        QString attrName = QString::fromStdString(attr);
        QString attrValue;

        if (attrName == "path") attrValue = pathEdit->text();
        else if (attrName == "size") attrValue = QString::number(sizeSpinBox->value());
        else if (attrName == "name") attrValue = nameEdit->text();
        else if (attrName == "uploader") attrValue = uploaderEdit->text();
        else if (attrName == "format") attrValue = formatComboBox->currentText();
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

    emit createRequested(audioAttributes);
}

void AudioCreator::onCancelButtonClicked() {

    emit createCancelled();
}


void AudioCreator::setAbstractFileAttributes() {

    idEdit = new QLineEdit(this);
    idEdit->setText(QString::number(Model::Media::AbstractMedia::uniqueIDCounter));
    audioCreatorFormLayout->addRow("ID:", idEdit);

    pathEdit = new QLineEdit(this);
    pathEdit->setPlaceholderText(QString::fromStdString(Model::Media::AbstractFile::defaultPath));
    QLabel* pathLabel = new QLabel("Path:"); pathLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(pathLabel, pathEdit);

    sizeSpinBox = new QDoubleSpinBox(this);
    sizeSpinBox->setSuffix(" MB");
    sizeSpinBox->setMinimum(Model::Media::AbstractFile::MIN_FILE_SIZE);
    sizeSpinBox->setMaximum(Model::Media::AbstractFile::MAX_FILE_SIZE);
    sizeSpinBox->setValue(Model::Media::Audio::defaultAudioSize);
    QLabel* sizeLabel = new QLabel("Size:"); sizeLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(sizeLabel, sizeSpinBox);
}

void AudioCreator::setAbstractMediaAttributes() {

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText(QString::fromStdString(Model::Media::AbstractMedia::defaultName));
    QLabel* nameLabel = new QLabel("Name:"); nameLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(nameLabel, nameEdit);

    uploaderEdit = new QLineEdit(this);
    uploaderEdit->setPlaceholderText(QString::fromStdString(Model::Media::AbstractMedia::defaultUploader));
    QLabel* uploaderLabel = new QLabel("Uploader:"); uploaderLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(uploaderLabel, uploaderEdit);

    formatComboBox = new QComboBox(this);
    for (const auto& fmt : Model::Media::Audio::AUDIO_FORMATS) {
        formatComboBox->addItem(QString::fromStdString(fmt));
    }
    QLabel* formatLabel = new QLabel("Format:"); formatLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(formatLabel, formatComboBox);

    ratingSpinBox = new QSpinBox(this);
    ratingSpinBox->setMinimum(Model::Media::AbstractMedia::MIN_MEDIA_RATING);
    ratingSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_MEDIA_RATING);
    ratingSpinBox->setValue(Model::Media::AbstractMedia::defaultRating);
    QLabel* ratingLabel = new QLabel("Rating:"); ratingLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(ratingLabel, ratingSpinBox);
}

void AudioCreator::setAudioAttributes() {

    artistEdit = new QLineEdit(this);
    artistEdit->setPlaceholderText(QString::fromStdString(Model::Media::Audio::defaultAudioArtist));
    QLabel* artistLabel = new QLabel("Artist:"); artistLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(artistLabel, artistEdit);

    genreEdit = new QLineEdit(this);
    genreEdit->setPlaceholderText(QString::fromStdString(Model::Media::Audio::defaultAudioGenre));
    QLabel* genreLabel = new QLabel("Genre:"); genreLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(genreLabel, genreEdit);

    albumEdit = new QLineEdit(this);
    albumEdit->setPlaceholderText(QString::fromStdString(Model::Media::Audio::defaultAudioAlbum));
    QLabel* albumLabel = new QLabel("Album:"); albumLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(albumLabel, albumEdit);

    releaseYearSpinBox = new QSpinBox(this);
    releaseYearSpinBox->setMaximum(Model::Media::AbstractMedia::MIN_RELEASE_YEAR);
    releaseYearSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_RELEASE_YEAR);
    releaseYearSpinBox->setValue(Model::Media::Audio::defaultAudioReleaseYear);
    QLabel* releaseYearLabel = new QLabel("Release Year:"); releaseYearLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(releaseYearLabel, releaseYearSpinBox);

    lengthSpinBox = new QSpinBox(this);
    lengthSpinBox->setSuffix(" min");
    lengthSpinBox->setMaximum(Model::Media::Audio::MIN_AUDIO_LENGTH);
    lengthSpinBox->setMaximum(Model::Media::Audio::MAX_AUDIO_LENGTH);
    lengthSpinBox->setValue(Model::Media::Audio::defaultAudioLength);
    QLabel* lengthLabel = new QLabel("Length:"); lengthLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(lengthLabel, lengthSpinBox);

    bitrateSpinBox = new QSpinBox(this);
    bitrateSpinBox->setSuffix(" kbps");
    bitrateSpinBox->setMinimum(Model::Media::Audio::MIN_AUDIO_BIT_RATE);
    bitrateSpinBox->setMaximum(Model::Media::Audio::MAX_AUDIO_BITRATE);
    bitrateSpinBox->setValue(Model::Media::Audio::defaultAudioBitRate);
    QLabel* bitrateLabel = new QLabel("Bitrate:"); bitrateLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(bitrateLabel, bitrateSpinBox);

    sampleRateSpinBox = new QDoubleSpinBox(this);
    sampleRateSpinBox->setSuffix(" kHz");
    sampleRateSpinBox->setMinimum(Model::Media::Audio::MIN_AUDIO_SAMPLE_RATE);
    sampleRateSpinBox->setMaximum(Model::Media::Audio::MAX_AUDIO_SAMPLE_RATE);
    sampleRateSpinBox->setValue(Model::Media::Audio::defaultAudioSampleRate);
    QLabel* samplerateLabel = new QLabel("Samplerate:"); samplerateLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(samplerateLabel, sampleRateSpinBox);

    bitdepthSpinBox = new QSpinBox(this);
    bitdepthSpinBox->setSuffix("-bit");
    bitdepthSpinBox->setMinimum(Model::Media::Audio::MIN_AUDIO_BIT_DEPTH);
    bitdepthSpinBox->setMaximum(Model::Media::Audio::MAX_AUDIO_BIT_DEPTH);
    bitdepthSpinBox->setValue(Model::Media::Audio::defaultAudioBitDepth);
    QLabel* bitdepthLabel = new QLabel("Bitdepth:"); bitdepthLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(bitdepthLabel, bitdepthSpinBox);

    channelsSpinBox = new QSpinBox(this);
    channelsSpinBox->setMinimum(Model::Media::Audio::MIN_AUDIO_CHANNELS);
    channelsSpinBox->setMaximum(Model::Media::Audio::MAX_AUDIO_CHANNELS);
    channelsSpinBox->setValue(Model::Media::Audio::defaultAudioChannels);
    QLabel* channelsLabel = new QLabel("Audio Channels::"); channelsLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(channelsLabel, channelsSpinBox);

    collaboratorsEdit = new QLineEdit(this);
    collaboratorsEdit->setPlaceholderText(QString::fromStdString(Model::Media::Audio::defaultAudioCollaborators));
    QLabel* collaboratorsLabel = new QLabel("Collaborators:"); collaboratorsLabel->setStyleSheet(OPTIONAL_ATTRIBUTE_STYLE);
    audioCreatorFormLayout->addRow(collaboratorsLabel, collaboratorsEdit);
}

void AudioCreator::setAudioToolTips() {

    ratingSpinBox->setToolTip("Rating must be defined in range (0-100)");
    lengthSpinBox->setToolTip("Audio must have length defined in range [1-15] minutes");
    bitrateSpinBox->setToolTip("Audio must have bitrate defined in range [32-320] kbps");
    sampleRateSpinBox->setToolTip("Audio must have samplerate defined in range [8-384] kHz");
    bitdepthSpinBox->setToolTip("Audio must have bidepth set in range [1-32] bits");
    channelsSpinBox->setToolTip("Audio must have channels defined in range [1-8]");
}

}
}

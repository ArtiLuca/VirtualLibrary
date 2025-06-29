#include "ImageCreator.h"
#include "Model/Media/Image.h"
#include "Model/Builders/ImageBuilder.h"

namespace View {
namespace Creator {

const QString ImageCreator::REQUIRED_ATTRIBUTE_STYLE = "color: #000000; font-weight: bold;";
const QString ImageCreator::OPTIONAL_ATTRIBUTE_STYLE = "color: #000000; font-style: italic;";

ImageCreator::ImageCreator(QWidget* parent)
    : QWidget(parent)
{
    // layout principale
    imageCreatorMainLayout = new QVBoxLayout(this);
    imageCreatorMainLayout->setSpacing(10);
    imageCreatorMainLayout->setContentsMargins(8, 8, 8, 8);

    // form layout
    imageCreatorFormLayout = new QFormLayout();
    imageCreatorFormLayout->setLabelAlignment(Qt::AlignLeft);
    imageCreatorFormLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    imageCreatorFormLayout->setHorizontalSpacing(12);
    imageCreatorFormLayout->setVerticalSpacing(6);
    imageCreatorFormLayout->setContentsMargins(0, 0, 0, 0);

    creatorTypeLabel = new QLabel("Image Creator");
    creatorTypeLabel->setStyleSheet("font-weight: bold;");
    imageCreatorFormLayout->addRow("", creatorTypeLabel);

    // setup form
    setAbstractFileAttributes();
    setAbstractMediaAttributes();
    setImageAttributes();
    setImageToolTips();

    imageCreatorMainLayout->addLayout(imageCreatorFormLayout);

    // aggiunta pulsanti
    imageCreatorButtonBox = new QDialogButtonBox(Qt::Horizontal, this);
    imageCreatorButtonBox->addButton("Create", QDialogButtonBox::AcceptRole);
    imageCreatorButtonBox->addButton("Cancel", QDialogButtonBox::RejectRole);
    imageCreatorMainLayout->addWidget(imageCreatorButtonBox);

    // connect pulsanti
    connect(imageCreatorButtonBox, &QDialogButtonBox::accepted,
            this, &ImageCreator::onCreateButtonClicked);
    connect(imageCreatorButtonBox, &QDialogButtonBox::rejected,
            this, &ImageCreator::onCancelButtonClicked);
}


void ImageCreator::onCreateButtonClicked() {

    QMap<QString, QString> imageAttributes;

    const auto imageAttributeNames = Model::Builders::ImageBuilder::IMAGE_ATTRIBUTES;

    for (const auto& attr : imageAttributeNames) {

        QString attrName = QString::fromStdString(attr);
        QString attrValue;

        if (attrName == "path") attrValue = pathEdit->text();
        else if (attrName == "size") attrValue = QString::number(sizeSpinBox->value());
        else if (attrName == "name") attrValue = nameEdit->text();
        else if (attrName == "uploader") attrValue = uploaderEdit->text();
        else if (attrName == "format") attrValue = formatComboBox->currentText();
        else if (attrName == "rating") attrValue = QString::number(ratingSpinBox->value());
        else if (attrName == "dateCreated") attrValue = createdEdit->text();
        else if (attrName == "imageCreator") attrValue = creatorEdit->text();
        else if (attrName == "imageCategory") attrValue = categoryEdit->text();
        else if (attrName == "resolutionWidth") attrValue = QString::number(resolutionWidthSpinBox->value());
        else if (attrName == "resolutionHeight") attrValue = QString::number(resolutionHeightSpinBox->value());
        else if (attrName == "aspectWidth") attrValue = QString::number(aspectWidthSpinBox->value());
        else if (attrName == "aspectHeight") attrValue = QString::number(aspectHeightSpinBox->value());
        else if (attrName == "bitdepth") attrValue = QString::number(bitdepthSpinBox->value());
        else if (attrName == "compressed") attrValue = compressedCheckBox->isChecked() ? "true" : "false";
        else if (attrName == "location") attrValue = locationEdit->text();

        imageAttributes.insert(attrName, attrValue);
    }

    emit createRequested(imageAttributes);
}

void ImageCreator::onCancelButtonClicked() {

    emit createCancelled();
}


void ImageCreator::setAbstractFileAttributes() {

    idEdit = new QLineEdit(this);
    idEdit->setText(QString::number(Model::Media::AbstractMedia::uniqueIDCounter));
    idEdit->setReadOnly(true);
    imageCreatorFormLayout->addRow("ID:", idEdit);

    pathEdit = new QLineEdit(this);
    pathEdit->setPlaceholderText(QString::fromStdString(Model::Media::AbstractFile::defaultPath));
    QLabel* pathLabel = new QLabel("Path:"); pathLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    imageCreatorFormLayout->addRow(pathLabel, pathEdit);

    sizeSpinBox = new QDoubleSpinBox(this);
    sizeSpinBox->setSuffix(" MB");
    sizeSpinBox->setMinimum(Model::Media::AbstractFile::MIN_FILE_SIZE);
    sizeSpinBox->setMaximum(Model::Media::AbstractFile::MAX_FILE_SIZE);
    sizeSpinBox->setValue(Model::Media::Image::defaultImageSize);
    QLabel* sizeLabel = new QLabel("Size:"); sizeLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    imageCreatorFormLayout->addRow(sizeLabel, sizeSpinBox);
}

void ImageCreator::setAbstractMediaAttributes() {

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText(QString::fromStdString(Model::Media::AbstractMedia::defaultName));
    QLabel* nameLabel = new QLabel("Name:"); nameLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    imageCreatorFormLayout->addRow(nameLabel, nameEdit);

    uploaderEdit = new QLineEdit(this);
    uploaderEdit->setPlaceholderText(QString::fromStdString(Model::Media::AbstractMedia::defaultUploader));
    QLabel* uploaderLabel = new QLabel("Uploader:"); uploaderLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    imageCreatorFormLayout->addRow(uploaderLabel, uploaderEdit);

    formatComboBox = new QComboBox(this);
    for (const auto& fmt : Model::Media::Image::IMAGE_FORMATS) {
        formatComboBox->addItem(QString::fromStdString(fmt));
    }
    QLabel* formatLabel = new QLabel("Format:"); formatLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    imageCreatorFormLayout->addRow(formatLabel, formatComboBox);

    ratingSpinBox = new QSpinBox(this);
    ratingSpinBox->setMinimum(Model::Media::AbstractMedia::MIN_MEDIA_RATING);
    ratingSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_MEDIA_RATING);
    ratingSpinBox->setValue(Model::Media::AbstractMedia::defaultRating);
    QLabel* ratingLabel = new QLabel("Rating:"); ratingLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    imageCreatorFormLayout->addRow(ratingLabel, ratingSpinBox);
}

void ImageCreator::setImageAttributes() {

    createdEdit = new QLineEdit(this);
    createdEdit->setPlaceholderText(QString::fromStdString(Model::Media::Image::defaultImageCreationDate));
    QLabel* createdLabel = new QLabel("Date Created:"); createdLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    imageCreatorFormLayout->addRow(createdLabel, createdEdit);

    creatorEdit = new QLineEdit(this);
    creatorEdit->setPlaceholderText(QString::fromStdString(Model::Media::Image::defaultImageCreator));
    QLabel* creatorLabel = new QLabel("Creator:"); creatorLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    imageCreatorFormLayout->addRow(creatorLabel, creatorEdit);

    categoryEdit = new QLineEdit(this);
    categoryEdit->setPlaceholderText(QString::fromStdString(Model::Media::Image::defaultImageCategory));
    QLabel* categoryLabel = new QLabel("Category:"); categoryLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    imageCreatorFormLayout->addRow(categoryLabel, categoryEdit);

    // risoluzione
    resolutionWidthSpinBox = new QSpinBox(this);
    resolutionWidthSpinBox->setMinimumWidth(100);
    resolutionHeightSpinBox = new QSpinBox(this);
    resolutionHeightSpinBox->setMinimumWidth(100);

    resolutionWidthSpinBox->setMinimum(Model::Media::Image::MIN_IMAGE_RESOLUTION_WIDTH);
    resolutionWidthSpinBox->setMaximum(Model::Media::Image::MAX_IMAGE_RESOLUTION_WIDTH);
    resolutionWidthSpinBox->setValue(Model::Media::Image::defaultImageResolution.first);
    resolutionHeightSpinBox->setMinimum(Model::Media::Image::MIN_IMAGE_RESOLUTION_HEIGHT);
    resolutionHeightSpinBox->setMaximum(Model::Media::Image::MAX_IMAGE_RESOLUTION_HEIGHT);
    resolutionHeightSpinBox->setValue(Model::Media::Image::defaultImageResolution.second);

    resolutionContainer = new QWidget(this);
    resolutionContainer->setMaximumWidth(220);
    resolutionLayout = new QHBoxLayout(resolutionContainer);
    resolutionLayout->setContentsMargins(0, 0, 0, 0);
    resolutionLayout->addWidget(resolutionWidthSpinBox);
    resolutionLayout->addWidget(new QLabel("x"));
    resolutionLayout->addWidget(resolutionHeightSpinBox);
    resolutionLayout->setSpacing(5);
    QLabel* resolutionLabel = new QLabel("Resolution:"); resolutionLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    imageCreatorFormLayout->addRow(resolutionLabel, resolutionContainer);
    imageCreatorFormLayout->setAlignment(resolutionContainer, Qt::AlignLeft);

    // aspect ratio
    aspectWidthSpinBox = new QSpinBox(this);
    aspectWidthSpinBox->setMinimumWidth(100);
    aspectHeightSpinBox = new QSpinBox(this);
    aspectHeightSpinBox->setMinimumWidth(100);

    aspectWidthSpinBox->setMinimum(Model::Media::Image::MIN_ASPECT_RATIO_VALUE);
    aspectWidthSpinBox->setValue(Model::Media::Image::defaultImageAspectRatio.first);
    aspectHeightSpinBox->setMinimum(Model::Media::Image::MIN_ASPECT_RATIO_VALUE);
    aspectHeightSpinBox->setValue(Model::Media::Image::defaultImageAspectRatio.second);

    aspectRatioContainer = new QWidget(this);
    aspectRatioContainer->setMaximumWidth(220);
    aspectRatioLayout = new QHBoxLayout(aspectRatioContainer);
    aspectRatioLayout->setContentsMargins(0, 0, 0, 0);
    aspectRatioLayout->addWidget(aspectWidthSpinBox);
    aspectRatioLayout->addWidget(new QLabel("x"));
    aspectRatioLayout->addWidget(aspectHeightSpinBox);
    aspectRatioLayout->setSpacing(5);
    QLabel* aspectRatioLabel = new QLabel("Aspect Ratio:"); aspectRatioLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    imageCreatorFormLayout->addRow(aspectRatioLabel, aspectRatioContainer);
    imageCreatorFormLayout->setAlignment(aspectRatioContainer, Qt::AlignLeft);

    bitdepthSpinBox = new QSpinBox(this);
    bitdepthSpinBox->setSuffix("-bit");
    bitdepthSpinBox->setMinimum(Model::Media::Image::MIN_IMAGE_BITDEPTH);
    bitdepthSpinBox->setMaximum(Model::Media::Image::MAX_IMAGE_BITDEPTH);
    bitdepthSpinBox->setValue(Model::Media::Image::defaultImageBitDepth);
    QLabel* bitdepthLabel = new QLabel("Bitdepth:"); bitdepthLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    imageCreatorFormLayout->addRow(bitdepthLabel, bitdepthSpinBox);

    compressedCheckBox = new QCheckBox("Compressed?", this);
    QLabel* compressedLabel = new QLabel("Compression:"); compressedLabel->setStyleSheet(OPTIONAL_ATTRIBUTE_STYLE);
    imageCreatorFormLayout->addRow(compressedLabel, compressedCheckBox);

    locationEdit = new QLineEdit(this);
    locationEdit->setPlaceholderText(QString::fromStdString(Model::Media::Image::defaultImageLocation));
    QLabel* locationLabel = new QLabel("Location:"); locationLabel->setStyleSheet(OPTIONAL_ATTRIBUTE_STYLE);
    imageCreatorFormLayout->addRow(locationLabel, locationEdit);
}

void ImageCreator::setImageToolTips() {

    ratingSpinBox->setToolTip("Rating must be defined in range (0-100)");
    resolutionWidthSpinBox->setToolTip("Resolution width must be defined in range [200-8000] and must match aspect ratio");
    resolutionHeightSpinBox->setToolTip("Resolution height must be defined in range [200-8000] and must match aspect ratio");
    aspectWidthSpinBox->setToolTip("Image aspect ratio must match resolution");
    aspectHeightSpinBox->setToolTip("Image aspect ratio must match resolution");
    bitdepthSpinBox->setToolTip("Image bitdepth must be defined in range [8-32] bits");
}

}
}

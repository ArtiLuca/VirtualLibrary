#include "ImageEditor.h"
#include "Model/Media/Image.h"
#include "Model/Builders/ImageBuilder.h"

namespace View {
namespace Editor {

ImageEditor::ImageEditor(
    const Model::Media::Image& image,
    unsigned int ind,
    QWidget* parent)
    : QWidget(parent),
    imageIndex(ind),
    imageCopy(image)
{
    // layout principale
    imageEditorMainLayout = new QVBoxLayout(this);
    imageEditorMainLayout->setSpacing(8);
    imageEditorMainLayout->setContentsMargins(8, 8, 8, 8);

    // form layout
    imageEditorFormLayout = new QFormLayout();
    imageEditorFormLayout->setLabelAlignment(Qt::AlignLeft);
    imageEditorFormLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    imageEditorFormLayout->setHorizontalSpacing(12);
    imageEditorFormLayout->setVerticalSpacing(6);
    imageEditorFormLayout->setContentsMargins(0, 0, 0, 0);

    editorTypeLabel = new QLabel("Image Editor");
    editorTypeLabel->setStyleSheet("font-weight: bold;");
    imageEditorFormLayout->addRow("", editorTypeLabel);

    setAbstractFileAttributes();
    setAbstractMediaAttributes();
    setImageAttributes();
    setImageEditorToolTips();

    imageEditorMainLayout->addLayout(imageEditorFormLayout);


    // aggiunta pulasanti
    imageEditorButtonBox = new QDialogButtonBox(Qt::Horizontal, this);
    imageEditorButtonBox->addButton("Confirm", QDialogButtonBox::AcceptRole);
    imageEditorButtonBox->addButton("Cancel", QDialogButtonBox::RejectRole);
    imageEditorMainLayout->addWidget(imageEditorButtonBox);

    // connect pulsanti
    connect(imageEditorButtonBox, &QDialogButtonBox::accepted,
            this, &ImageEditor::onConfirmButtonClicked);
    connect(imageEditorButtonBox, &QDialogButtonBox::rejected,
            this, &ImageEditor::onCancelButtonClicked);
}


void ImageEditor::onConfirmButtonClicked() {

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

    emit mediaEditsConfirmed(imageIndex, imageAttributes);
}

void ImageEditor::onCancelButtonClicked() {

    emit closed();
}


void ImageEditor::setAbstractFileAttributes() {

    idEdit = new QLineEdit(this);
    idEdit->setText(QString::number(imageCopy.getUniqueID()));
    idEdit->setReadOnly(true);
    imageEditorFormLayout->addRow("ID:", idEdit);

    pathEdit = new QLineEdit(this);
    pathEdit->setText(QString::fromStdString(imageCopy.getFilePath()));
    imageEditorFormLayout->addRow("Path:", pathEdit);

    sizeSpinBox = new QDoubleSpinBox(this);
    sizeSpinBox->setSuffix(" MB");
    sizeSpinBox->setMinimum(Model::Media::AbstractFile::MIN_FILE_SIZE);
    sizeSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_FILE_SIZE);
    sizeSpinBox->setValue(imageCopy.getFileSize());
    imageEditorFormLayout->addRow("Size:", sizeSpinBox);
}

void ImageEditor::setAbstractMediaAttributes() {

    nameEdit = new QLineEdit(this);
    nameEdit->setText(QString::fromStdString(imageCopy.getMediaName()));
    imageEditorFormLayout->addRow("Name:", nameEdit);

    uploaderEdit = new QLineEdit(this);
    uploaderEdit->setText(QString::fromStdString(imageCopy.getMediaUploader()));
    imageEditorFormLayout->addRow("Uploader:", uploaderEdit);

    QString imageFormat = QString::fromStdString(imageCopy.getMediaFormat());
    int formatIndex = -1;
    formatComboBox = new QComboBox(this);
    for (unsigned int i = 0; i < Model::Media::Image::IMAGE_FORMATS.size(); ++i) {
        QString fmt = QString::fromStdString(Model::Media::Image::IMAGE_FORMATS[i]);
        formatComboBox->addItem(fmt);
        if (fmt == imageFormat) {
            formatIndex = i;
        }
        if (formatIndex >= 0) formatComboBox->setCurrentIndex(formatIndex);
    }
    imageEditorFormLayout->addRow("Format:", formatComboBox);

    ratingSpinBox = new QSpinBox(this);
    ratingSpinBox->setMinimum(Model::Media::AbstractMedia::MIN_MEDIA_RATING);
    ratingSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_MEDIA_RATING);
    ratingSpinBox->setValue(imageCopy.getMediaRating());
    imageEditorFormLayout->addRow("Rating:", ratingSpinBox);
}

void ImageEditor::setImageAttributes() {

    createdEdit = new QLineEdit(this);
    createdEdit->setText(QString::fromStdString(imageCopy.getDateCreated()));
    imageEditorFormLayout->addRow("Date Created:", createdEdit);

    creatorEdit = new QLineEdit(this);
    creatorEdit->setText(QString::fromStdString(imageCopy.getImageCreator()));
    imageEditorFormLayout->addRow("Creator:", creatorEdit);

    categoryEdit = new QLineEdit(this);
    categoryEdit->setText(QString::fromStdString(imageCopy.getImageCategory()));
    imageEditorFormLayout->addRow("Category:", categoryEdit);

    // risoluzione
    resolutionWidthSpinBox = new QSpinBox(this);
    resolutionWidthSpinBox->setMinimumWidth(100);
    resolutionHeightSpinBox = new QSpinBox(this);
    resolutionHeightSpinBox->setMinimumWidth(100);

    resolutionWidthSpinBox->setMinimum(Model::Media::Image::MIN_IMAGE_RESOLUTION_WIDTH);
    resolutionWidthSpinBox->setMaximum(Model::Media::Image::MAX_IMAGE_RESOLUTION_WIDTH);
    resolutionWidthSpinBox->setValue(imageCopy.getResolution().first);
    resolutionHeightSpinBox->setMinimum(Model::Media::Image::MIN_IMAGE_RESOLUTION_HEIGHT);
    resolutionHeightSpinBox->setMaximum(Model::Media::Image::MAX_IMAGE_RESOLUTION_HEIGHT);
    resolutionHeightSpinBox->setValue(imageCopy.getResolution().second);

    resolutionContainer = new QWidget(this);
    resolutionContainer->setMaximumWidth(220);
    resolutionLayout = new QHBoxLayout(resolutionContainer);
    resolutionLayout->setContentsMargins(0, 0, 0, 0);
    resolutionLayout->addWidget(resolutionWidthSpinBox);
    resolutionLayout->addWidget(new QLabel("x"));
    resolutionLayout->addWidget(resolutionHeightSpinBox);
    resolutionLayout->setSpacing(5);
    imageEditorFormLayout->addRow("Resolution:", resolutionContainer);
    imageEditorFormLayout->setAlignment(resolutionContainer, Qt::AlignLeft);

    // aspect ratio
    aspectWidthSpinBox = new QSpinBox(this);
    aspectWidthSpinBox->setMinimumWidth(100);
    aspectHeightSpinBox = new QSpinBox(this);
    aspectHeightSpinBox->setMinimumWidth(100);

    aspectWidthSpinBox->setMinimum(Model::Media::Image::MIN_ASPECT_RATIO_VALUE);
    aspectWidthSpinBox->setValue(imageCopy.getImageAspectRatio().first);
    aspectHeightSpinBox->setMinimum(Model::Media::Image::MIN_ASPECT_RATIO_VALUE);
    aspectHeightSpinBox->setValue(imageCopy.getImageAspectRatio().second);

    aspectRatioContainer = new QWidget(this);
    aspectRatioContainer->setMaximumWidth(220);
    aspectRatioLayout = new QHBoxLayout(aspectRatioContainer);
    aspectRatioLayout->setContentsMargins(0, 0, 0, 0);
    aspectRatioLayout->addWidget(aspectWidthSpinBox);
    aspectRatioLayout->addWidget(new QLabel("x"));
    aspectRatioLayout->addWidget(aspectHeightSpinBox);
    aspectRatioLayout->setSpacing(5);
    imageEditorFormLayout->addRow("Aspect Ratio:", aspectRatioContainer);
    imageEditorFormLayout->setAlignment(aspectRatioContainer, Qt::AlignLeft);

    bitdepthSpinBox = new QSpinBox(this);
    bitdepthSpinBox->setSuffix("-bit");
    bitdepthSpinBox->setMinimum(Model::Media::Image::MIN_IMAGE_BITDEPTH);
    bitdepthSpinBox->setMaximum(Model::Media::Image::MAX_IMAGE_BITDEPTH);
    bitdepthSpinBox->setValue(imageCopy.getImageBitDepth());
    imageEditorFormLayout->addRow("Bitdepth:", bitdepthSpinBox);

    compressedCheckBox = new QCheckBox("Compressed?", this);
    if (imageCopy.isCompressed()) compressedCheckBox->setChecked(true);
    else compressedCheckBox->setChecked(false);
    imageEditorFormLayout->addRow("Compressed?", compressedCheckBox);

    locationEdit = new QLineEdit(this);
    if (imageCopy.getLocationTaken().empty()) locationEdit->setText("Not given");
    else locationEdit->setText(QString::fromStdString(imageCopy.getLocationTaken()));
    imageEditorFormLayout->addRow("Location Taken:", locationEdit);

}

void ImageEditor::setImageEditorToolTips() {

    ratingSpinBox->setToolTip("Rating must be defined in range (0-100)");
    resolutionWidthSpinBox->setToolTip("Resolution width must be defined in range [200-8000] and must match aspect ratio");
    resolutionHeightSpinBox->setToolTip("Resolution height must be defined in range [200-8000] and must match aspect ratio");
    aspectWidthSpinBox->setToolTip("Image aspect ratio must match resolution");
    aspectHeightSpinBox->setToolTip("Image aspect ratio must match resolution");
    bitdepthSpinBox->setToolTip("Image bitdepth must be defined in range [8-32] bits");
}

}
}

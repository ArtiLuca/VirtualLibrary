#include "EBookEditor.h"
#include "Model/Media/EBook.h"
#include "Model/Builders/EBookBuilder.h"

namespace View {
namespace Editor {

EBookEditor::EBookEditor(
    const Model::Media::EBook& ebook,
    unsigned int ind,
    QWidget* parent)
    : QWidget(parent),
    ebookIndex(ind),
    ebookCopy(ebook)
{
    // layout principale
    ebookEditorMainLayout = new QVBoxLayout(this);
    ebookEditorMainLayout->setSpacing(8);
    ebookEditorMainLayout->setContentsMargins(8, 8, 8, 8);

    // form layout
    ebookEditorFormLayout = new QFormLayout();
    ebookEditorFormLayout->setLabelAlignment(Qt::AlignLeft);
    ebookEditorFormLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    ebookEditorFormLayout->setHorizontalSpacing(12);
    ebookEditorFormLayout->setVerticalSpacing(6);
    ebookEditorFormLayout->setContentsMargins(0, 0, 0, 0);

    editorTypeLabel = new QLabel("EBook Editor");
    editorTypeLabel->setStyleSheet("font-weight: bold;");
    ebookEditorFormLayout->addRow("", editorTypeLabel);

    setAbstractFileAttributes();
    setAbstractMediaAttributes();
    setEBookAttributes();
    setEBookEditorToolTips();

    ebookEditorMainLayout->addLayout(ebookEditorFormLayout);

    // aggiunta pulasanti
    ebookEditorButtonBox = new QDialogButtonBox(Qt::Horizontal, this);
    ebookEditorButtonBox->addButton("Confirm", QDialogButtonBox::AcceptRole);
    ebookEditorButtonBox->addButton("Cancel", QDialogButtonBox::RejectRole);
    ebookEditorMainLayout->addWidget(ebookEditorButtonBox);

    // connect pulsanti
    connect(ebookEditorButtonBox, &QDialogButtonBox::accepted,
            this, &EBookEditor::onConfirmButtonClicked);
    connect(ebookEditorButtonBox, &QDialogButtonBox::rejected,
            this, &EBookEditor::onCancelButtonClicked);
}


void EBookEditor::onConfirmButtonClicked() {

    QMap<QString, QString> ebookAttributes;

    const auto ebookAttributeNames = Model::Builders::EBookBuilder::EBOOK_ATTRIBUTES;

    for (const auto& attr : ebookAttributeNames) {

        QString attrName = QString::fromStdString(attr);
        QString attrValue;

        if (attrName == "path") attrValue = pathEdit->text();
        else if (attrName == "size") attrValue = QString::number(sizeSpinBox->value());
        else if (attrName == "name") attrValue = nameEdit->text();
        else if (attrName == "uploader") attrValue = uploaderEdit->text();
        else if (attrName == "format") attrValue = formatComboBox->currentText();
        else if (attrName == "rating") attrValue = QString::number(ratingSpinBox->value());
        else if (attrName == "author") attrValue = authorEdit->text();
        else if (attrName == "publisher") attrValue = publisherEdit->text();
        else if (attrName == "releaseYear") attrValue = QString::number(releaseYearSpinBox->value());
        else if (attrName == "isbn") attrValue = isbnEdit->text();
        else if (attrName == "length") attrValue = QString::number(lengthSpinBox->value());
        else if (attrName == "category") attrValue = categoryEdit->text();
        else if (attrName == "language") attrValue = languageEdit->text();
        else if (attrName == "coverPath") attrValue = coverPathEdit->text();
        else if (attrName == "hasImages") attrValue = hasImagesCheckBox->isChecked() ? "true" : "false";

        ebookAttributes.insert(attrName, attrValue);
    }

    emit mediaEditsConfirmed(ebookIndex, ebookAttributes);
}

void EBookEditor::onCancelButtonClicked() {

    emit closed();
}


void EBookEditor::setAbstractFileAttributes() {

    idEdit = new QLineEdit(this);
    idEdit->setText(QString::number(ebookCopy.getUniqueID()));
    idEdit->setReadOnly(true);
    ebookEditorFormLayout->addRow("ID:", idEdit);

    pathEdit = new QLineEdit(this);
    pathEdit->setText(QString::fromStdString(ebookCopy.getFilePath()));
    ebookEditorFormLayout->addRow("Path:", pathEdit);

    sizeSpinBox = new QDoubleSpinBox(this);
    sizeSpinBox->setSuffix(" MB");
    sizeSpinBox->setMinimum(Model::Media::AbstractFile::MIN_FILE_SIZE);
    sizeSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_FILE_SIZE);
    sizeSpinBox->setValue(ebookCopy.getFileSize());
    ebookEditorFormLayout->addRow("Size:", sizeSpinBox);
}

void EBookEditor::setAbstractMediaAttributes() {

    nameEdit = new QLineEdit(this);
    nameEdit->setText(QString::fromStdString(ebookCopy.getMediaName()));
    ebookEditorFormLayout->addRow("Name:", nameEdit);

    uploaderEdit = new QLineEdit(this);
    uploaderEdit->setText(QString::fromStdString(ebookCopy.getMediaUploader()));
    ebookEditorFormLayout->addRow("Uploader:", uploaderEdit);

    QString ebookFormat = QString::fromStdString(ebookCopy.getMediaFormat());
    int formatIndex = -1;
    formatComboBox = new QComboBox(this);
    for (unsigned int i = 0; i < Model::Media::EBook::EBOOK_FORMATS.size(); ++i) {
        QString fmt = QString::fromStdString(Model::Media::EBook::EBOOK_FORMATS[i]);
        formatComboBox->addItem(fmt);
        if (fmt == ebookFormat) {
            formatIndex = i;
        }
        if (formatIndex >= 0) formatComboBox->setCurrentIndex(formatIndex);
    }
    ebookEditorFormLayout->addRow("Format:", formatComboBox);

    ratingSpinBox = new QSpinBox(this);
    ratingSpinBox->setMinimum(Model::Media::AbstractMedia::MIN_MEDIA_RATING);
    ratingSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_MEDIA_RATING);
    ratingSpinBox->setValue(ebookCopy.getMediaRating());
    ebookEditorFormLayout->addRow("Rating:", ratingSpinBox);

}

void EBookEditor::setEBookAttributes() {

    authorEdit = new QLineEdit(this);
    authorEdit->setText(QString::fromStdString(ebookCopy.getAuthor()));
    ebookEditorFormLayout->addRow("Author:", authorEdit);

    publisherEdit = new QLineEdit(this);
    publisherEdit->setText(QString::fromStdString(ebookCopy.getPublisher()));
    ebookEditorFormLayout->addRow("Publisher:", publisherEdit);


    releaseYearSpinBox = new QSpinBox(this);
    releaseYearSpinBox->setMinimum(Model::Media::AbstractMedia::MIN_RELEASE_YEAR);
    releaseYearSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_RELEASE_YEAR);
    releaseYearSpinBox->setValue(ebookCopy.getReleaseYear());
    ebookEditorFormLayout->addRow("Release Year:", releaseYearSpinBox);

    isbnEdit = new QLineEdit(this);
    isbnEdit->setText(QString::fromStdString(ebookCopy.getISBN()));
    ebookEditorFormLayout->addRow("ISBN:", isbnEdit);

    lengthSpinBox = new QSpinBox(this);
    lengthSpinBox->setSuffix(" pages");
    lengthSpinBox->setMinimum(Model::Media::EBook::MIN_EBOOK_LENGTH);
    lengthSpinBox->setMaximum(Model::Media::EBook::MAX_EBOOK_LENGTH);
    lengthSpinBox->setValue(ebookCopy.getMediaLength());
    ebookEditorFormLayout->addRow("Length:", lengthSpinBox);

    categoryEdit = new QLineEdit(this);
    if (ebookCopy.getCategory().empty()) categoryEdit->setText("Not given");
    else categoryEdit->setText(QString::fromStdString(ebookCopy.getCategory()));
    ebookEditorFormLayout->addRow("Category:", categoryEdit);

    languageEdit = new QLineEdit(this);
    languageEdit->setText(QString::fromStdString(ebookCopy.getLanguage()));
    ebookEditorFormLayout->addRow("Language:", languageEdit);

    coverPathEdit = new QLineEdit(this);
    if (ebookCopy.hasCoverPath()) coverPathEdit->setText(QString::fromStdString(ebookCopy.getCoverImagePath()));
    else coverPathEdit->setText("None");
    ebookEditorFormLayout->addRow("Cover Path:", coverPathEdit);

    hasImagesCheckBox = new QCheckBox("Has Images?", this);
    if (ebookCopy.hasImages()) hasImagesCheckBox->setChecked(true);
    else hasImagesCheckBox->setChecked(false);
    ebookEditorFormLayout->addRow("Images?", hasImagesCheckBox);
}

void EBookEditor::setEBookEditorToolTips() {

    ratingSpinBox->setToolTip("Rating must be defined in range (0-100)");
    lengthSpinBox->setToolTip("EBook must have length defined in range [1-10,000] pages");
    isbnEdit->setToolTip("EBook must have an ISBN made up of exactly 13 characters");
}


}
}

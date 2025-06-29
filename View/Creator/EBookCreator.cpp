#include "EBookCreator.h"
#include "Model/Media/EBook.h"
#include "Model/Builders/EBookBuilder.h"

namespace View {
namespace Creator {

const QString EBookCreator::REQUIRED_ATTRIBUTE_STYLE = "color: #000000; font-weight: bold;";
const QString EBookCreator::OPTIONAL_ATTRIBUTE_STYLE = "color: #000000; font-style: italic;";

EBookCreator::EBookCreator(QWidget* parent)
    : QWidget(parent)
{
    // layout principale
    ebookCreatorMainLayout = new QVBoxLayout(this);
    ebookCreatorMainLayout->setSpacing(10);
    ebookCreatorMainLayout->setContentsMargins(8, 8, 8, 8);

    // form layout
    ebookCreatorFormLayout = new QFormLayout();
    ebookCreatorFormLayout->setLabelAlignment(Qt::AlignRight);
    ebookCreatorFormLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    ebookCreatorFormLayout->setHorizontalSpacing(12);
    ebookCreatorFormLayout->setVerticalSpacing(6);
    ebookCreatorFormLayout->setContentsMargins(0, 0, 0, 0);

    creatorTypeLabel = new QLabel("EBook Creator");
    creatorTypeLabel->setStyleSheet("font-weight: bold;");
    ebookCreatorFormLayout->addRow("", creatorTypeLabel);

    // setup form
    setAbstractFileAttributes();
    setAbstractMediaAttributes();
    setEBookAttributes();
    setEBookToolTips();

    ebookCreatorMainLayout->addLayout(ebookCreatorFormLayout);

    // aggiunta pulsanti
    ebookCreatorButtonBox = new QDialogButtonBox(Qt::Horizontal, this);
    ebookCreatorButtonBox->addButton("Confirm", QDialogButtonBox::AcceptRole);
    ebookCreatorButtonBox->addButton("Cancel", QDialogButtonBox::RejectRole);
    ebookCreatorMainLayout->addWidget(ebookCreatorButtonBox);

    // connect pulsanti
    connect(ebookCreatorButtonBox, &QDialogButtonBox::accepted,
            this, &EBookCreator::onCreateButtonClicked);
    connect(ebookCreatorButtonBox, &QDialogButtonBox::rejected,
            this, &EBookCreator::onCancelButtonClicked);
}


void EBookCreator::onCreateButtonClicked() {

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

    emit createRequested(ebookAttributes);
}

void EBookCreator::onCancelButtonClicked() {

    emit createCancelled();
}


void EBookCreator::setAbstractFileAttributes() {

    idEdit = new QLineEdit(this);
    idEdit->setText(QString::number(Model::Media::AbstractMedia::uniqueIDCounter));
    idEdit->setReadOnly(true);
    ebookCreatorFormLayout->addRow("ID:", idEdit);

    pathEdit = new QLineEdit(this);
    pathEdit->setPlaceholderText(QString::fromStdString(Model::Media::AbstractFile::defaultPath));
    QLabel* pathLabel = new QLabel("Path:"); pathLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(pathLabel, pathEdit);

    sizeSpinBox = new QDoubleSpinBox(this);
    sizeSpinBox->setSuffix(" MB");
    sizeSpinBox->setMinimum(Model::Media::EBook::defaultEBookSize);
    sizeSpinBox->setMaximum(Model::Media::AbstractFile::MAX_FILE_SIZE);
    sizeSpinBox->setValue(Model::Media::AbstractFile::defaultSize);
    QLabel* sizeLabel = new QLabel("Size:"); sizeLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(sizeLabel, sizeSpinBox);
}

void EBookCreator::setAbstractMediaAttributes() {

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText(QString::fromStdString(Model::Media::AbstractMedia::defaultName));
    QLabel* nameLabel = new QLabel("Name:"); nameLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(nameLabel, nameEdit);

    uploaderEdit = new QLineEdit(this);
    uploaderEdit->setPlaceholderText(QString::fromStdString(Model::Media::AbstractMedia::defaultUploader));
    QLabel* uploaderLabel = new QLabel("Uploader:"); uploaderLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(uploaderLabel, uploaderEdit);

    formatComboBox = new QComboBox(this);
    for (const auto& fmt : Model::Media::EBook::EBOOK_FORMATS) {
        formatComboBox->addItem(QString::fromStdString(fmt));
    }
    QLabel* formatLabel = new QLabel("Format:"); formatLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(formatLabel, formatComboBox);


    ratingSpinBox = new QSpinBox(this);
    ratingSpinBox->setMinimum(Model::Media::AbstractMedia::MIN_MEDIA_RATING);
    ratingSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_MEDIA_RATING);
    ratingSpinBox->setValue(Model::Media::AbstractMedia::defaultRating);
    QLabel* ratingLabel = new QLabel("Rating:"); ratingLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(ratingLabel, ratingSpinBox);
}

void EBookCreator::setEBookAttributes() {

    authorEdit = new QLineEdit(this);
    authorEdit->setPlaceholderText(QString::fromStdString(Model::Media::EBook::defaultEBookAuthor));
    QLabel* authorLabel = new QLabel("Author:"); authorLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(authorLabel, authorEdit);

    publisherEdit = new QLineEdit(this);
    publisherEdit->setPlaceholderText(QString::fromStdString(Model::Media::EBook::defaultEBookPublisher));
    QLabel* publisherLabel = new QLabel("Publisher:"); publisherLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(publisherLabel, publisherEdit);

    releaseYearSpinBox = new QSpinBox(this);
    releaseYearSpinBox->setMinimum(Model::Media::AbstractMedia::MIN_RELEASE_YEAR);
    releaseYearSpinBox->setMaximum(Model::Media::AbstractMedia::MAX_RELEASE_YEAR);
    releaseYearSpinBox->setValue(Model::Media::EBook::defaultEBookReleaseYear);
    QLabel* releaseYearLabel = new QLabel("Release Year:"); releaseYearLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(releaseYearLabel, releaseYearSpinBox);

    isbnEdit = new QLineEdit(this);
    isbnEdit->setPlaceholderText(QString::fromStdString(Model::Media::EBook::defaultEBookISBN));
    QLabel* isbnLabel = new QLabel("ISBN:"); isbnLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(isbnLabel, isbnEdit);

    lengthSpinBox = new QSpinBox(this);
    lengthSpinBox->setSuffix(" pages");
    lengthSpinBox->setMinimum(Model::Media::EBook::MIN_EBOOK_LENGTH);
    lengthSpinBox->setMaximum(Model::Media::EBook::MAX_EBOOK_LENGTH);
    lengthSpinBox->setValue(Model::Media::EBook::defaultEBookLength);
    QLabel* lengthLabel = new QLabel("Length:"); lengthLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(lengthLabel, lengthSpinBox);

    categoryEdit = new QLineEdit(this);
    categoryEdit->setPlaceholderText(QString::fromStdString(Model::Media::EBook::defaultEBookCategory));
    QLabel* categoryLabel = new QLabel("Category:"); categoryLabel->setStyleSheet(OPTIONAL_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(categoryLabel, categoryEdit);

    languageEdit = new QLineEdit(this);
    languageEdit->setPlaceholderText(QString::fromStdString(Model::Media::EBook::defaultEBookLanguage));
    QLabel* languageLabel = new QLabel("Language:"); languageLabel->setStyleSheet(REQUIRED_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(languageLabel, languageEdit);

    coverPathEdit = new QLineEdit(this);
    coverPathEdit->setPlaceholderText(QString::fromStdString(Model::Media::AbstractFile::defaultPath));
    QLabel* coverPathLabel = new QLabel("Cover Path:"); coverPathLabel->setStyleSheet(OPTIONAL_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(coverPathLabel, coverPathEdit);

    hasImagesCheckBox = new QCheckBox("Has Images?", this);
    QLabel* hasImagesLabel = new QLabel("Images?"); hasImagesLabel->setStyleSheet(OPTIONAL_ATTRIBUTE_STYLE);
    ebookCreatorFormLayout->addRow(hasImagesLabel, hasImagesCheckBox);
}

void EBookCreator::setEBookToolTips() {

    ratingSpinBox->setToolTip("Rating must be defined in range (0-100)");
    lengthSpinBox->setToolTip("EBook must have length defined in range [1-10,000] pages");
    isbnEdit->setToolTip("EBook must have an ISBN made up of exactly 13 characters");
}

}
}

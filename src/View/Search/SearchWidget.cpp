#include "SearchWidget.h"

namespace View {
namespace Search {

SearchWidget::SearchWidget(
    Controller::Controller*c,
    bool filters,
    QString name,
    QWidget* parent)
    : QWidget(parent),
    controller(c),
    allFiltersEnabled(filters),
    mediaName(name)
{
    // layout principale
    searchWidgetMainLayout = new QVBoxLayout(this);
    searchWidgetMainLayout->setSpacing(10);
    searchWidgetMainLayout->setContentsMargins(8, 8, 8, 8);

    // form layout
    searchWidgetFormLayout = new QFormLayout();
    searchWidgetFormLayout->setLabelAlignment(Qt::AlignLeft);
    searchWidgetFormLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    searchWidgetFormLayout->setHorizontalSpacing(12);
    searchWidgetFormLayout->setVerticalSpacing(6);
    searchWidgetFormLayout->setContentsMargins(0, 0, 0, 0);

    // ricerca per nome
    nameFilter = new QLineEdit(this);
    nameFilter->setPlaceholderText("Search media name...");
    searchWidgetFormLayout->addRow("Name:", nameFilter);

    // se fitlri abilitati
    if (allFiltersEnabled) {

        setupCommonFilters();
        setupAudioFilters();
        setupVideoFilters();
        setupEBookFilters();
        setupImageFilters();
    }

    searchWidgetMainLayout->addLayout(searchWidgetFormLayout);

    // aggiunta pulsanti
    searchWidgetButtonBox = new QDialogButtonBox(Qt::Horizontal, this);
    searchWidgetButtonBox->addButton("Search", QDialogButtonBox::AcceptRole);
    searchWidgetButtonBox->addButton("Cancel", QDialogButtonBox::RejectRole);
    searchWidgetMainLayout->addWidget(searchWidgetButtonBox);

    // connect pulsanti
    connect(searchWidgetButtonBox, &QDialogButtonBox::accepted,
            this, &SearchWidget::onConfirmButtonClicked);
    connect(searchWidgetButtonBox, &QDialogButtonBox::rejected,
            this, &SearchWidget::onCancelButtonClicked);
}

void SearchWidget::onConfirmButtonClicked() {

    buildSearchQuery();
}

void SearchWidget::onCancelButtonClicked() {

    emit closed();
}

void SearchWidget::onTypeButtonSelected() {

    if (getSelectedRadioText() == audioTypeButton->text()) onAudioTypeSelected();
    else if (getSelectedRadioText() == videoTypeButton->text()) onVideoTypeSelected();
    else if (getSelectedRadioText() == ebookTypeButton->text()) onEBookTypeSelected();
    else if (getSelectedRadioText() == imageTypeButton->text()) onImageTypeSelected();
    else return;
}


void SearchWidget::disableSearchFilters() {

    audioArtistFilter->setEnabled(false); audioArtistFilter->setPlaceholderText("");
    audioGenreFilter->setEnabled(false); audioGenreFilter->setPlaceholderText("");
    videoDirectorFilter->setEnabled(false); videoDirectorFilter->setPlaceholderText("");
    videoGenreFilter->setEnabled(false); videoGenreFilter->setPlaceholderText("");
    ebookAuthorFilter->setEnabled(false); ebookAuthorFilter->setPlaceholderText("");
    ebookPublisherFilter->setEnabled(false); ebookPublisherFilter->setPlaceholderText("");
    imageCreatorFilter->setEnabled(false); imageCreatorFilter->setPlaceholderText("");
    imageLocationFilter->setEnabled(false); imageLocationFilter->setPlaceholderText("");
}

void SearchWidget::buildSearchQuery() {

    Model::Library::SearchQuery query;

    if (!nameFilter->text().isEmpty()) query.setMediaName(nameFilter->text().toStdString());
    if (idFilter->value() != 0) query.setMediaID(idFilter->value());
    if (!formatFilter->text().isEmpty()) query.setMediaFormat(formatFilter->text().toStdString());
    if (!uploaderFilter->text().isEmpty()) query.setMediaUploader(uploaderFilter->text().toStdString());

    if (minRatingFilter->value() != 0) query.setMinimumMediaRating(minRatingFilter->value());
    if (maxRatingFilter->value() != 0) query.setMaximumMediaRating(maxRatingFilter->value());

    if (getSelectedRadioText() == audioTypeButton->text()) {
        query.setMediaType(audioTypeButton->text().toUpper().toStdString());
        if (!audioArtistFilter->text().isEmpty()) query.setAudioArtist(audioArtistFilter->text().toStdString());
        if (!audioGenreFilter->text().isEmpty()) query.setMediaGenre(audioGenreFilter->text().toStdString());
    }
    if (getSelectedRadioText() == videoTypeButton->text()) {
        query.setMediaType(videoTypeButton->text().toUpper().toStdString());
        if (!videoDirectorFilter->text().isEmpty()) query.setVideoDirector(videoDirectorFilter->text().toStdString());
        if (!videoGenreFilter->text().isEmpty()) query.setMediaGenre(videoGenreFilter->text().toStdString());
    }
    if (getSelectedRadioText() == ebookTypeButton->text()) {
        query.setMediaType(ebookTypeButton->text().toUpper().toStdString());
        if (!ebookAuthorFilter->text().isEmpty()) query.setEBookAuthor(ebookAuthorFilter->text().toStdString());
        if (!ebookPublisherFilter->text().isEmpty()) query.setEBookPublisher(ebookPublisherFilter->text().toStdString());

    }
    if (getSelectedRadioText() == imageTypeButton->text()) {
        query.setMediaType(imageTypeButton->text().toUpper().toStdString());
        if (!imageCreatorFilter->text().isEmpty()) query.setImageCreator(imageCreatorFilter->text().toStdString());
        if (!imageLocationFilter->text().isEmpty()) query.setImageLocation(imageLocationFilter->text().toStdString());

    }

    emit confirmSearchFilters(query);
    emit closed();
}

QString SearchWidget::getSelectedRadioText() const {

    QAbstractButton* checked = typeRadioButtonGroup->checkedButton();
    if (checked) return checked->text();
    else return "";
}


void SearchWidget::onAudioTypeSelected() {

    disableSearchFilters();
    audioArtistFilter->setEnabled(true);
    audioGenreFilter->setEnabled(true);
    audioArtistFilter->setPlaceholderText("Audio media's artist");
    audioGenreFilter->setPlaceholderText("Audio media's genre");
}

void SearchWidget::onVideoTypeSelected() {

    disableSearchFilters();
    videoDirectorFilter->setEnabled(true);
    videoGenreFilter->setEnabled(true);
    videoDirectorFilter->setPlaceholderText("Video media's director");
    videoGenreFilter->setPlaceholderText("Video media's genre");
}

void SearchWidget::onEBookTypeSelected() {

    disableSearchFilters();
    ebookAuthorFilter->setEnabled(true);
    ebookPublisherFilter->setEnabled(true);
    ebookAuthorFilter->setPlaceholderText("EBook media's author");
    ebookPublisherFilter->setPlaceholderText("EBook media's publisher");
}

void SearchWidget::onImageTypeSelected() {

    disableSearchFilters();
    imageCreatorFilter->setEnabled(true);
    imageLocationFilter->setEnabled(true);
    imageCreatorFilter->setPlaceholderText("Image media's creator");
    imageLocationFilter->setPlaceholderText("Image media's location");
}

void SearchWidget::setupCommonFilters() {

    typeRadioButtonContainer = new QWidget(this);
    typeRadioButtonLayout = new QHBoxLayout(typeRadioButtonContainer);
    typeRadioButtonLayout->setContentsMargins(0, 0, 0, 0);

    audioTypeButton = new QRadioButton("Audio", typeRadioButtonContainer);
    videoTypeButton = new QRadioButton("Video", typeRadioButtonContainer);
    ebookTypeButton = new QRadioButton("EBook", typeRadioButtonContainer);
    imageTypeButton = new QRadioButton("Image", typeRadioButtonContainer);

    typeRadioButtonLayout->addWidget(audioTypeButton);
    typeRadioButtonLayout->addWidget(videoTypeButton);
    typeRadioButtonLayout->addWidget(ebookTypeButton);
    typeRadioButtonLayout->addWidget(imageTypeButton);

    typeRadioButtonGroup = new QButtonGroup(this);
    typeRadioButtonGroup->addButton(audioTypeButton);
    typeRadioButtonGroup->addButton(videoTypeButton);
    typeRadioButtonGroup->addButton(ebookTypeButton);
    typeRadioButtonGroup->addButton(imageTypeButton);

    searchWidgetFormLayout->addRow("Media Type:", typeRadioButtonContainer);

    connect(typeRadioButtonGroup, &QButtonGroup::buttonClicked,
            this, &SearchWidget::onTypeButtonSelected);

    idFilter = new QSpinBox(this);
    idFilter->setMinimum(0);
    idFilter->setMaximum(9999);
    idFilter->setValue(0);
    searchWidgetFormLayout->addRow("ID:", idFilter);

    formatFilter = new QLineEdit(this);
    formatFilter->setPlaceholderText("Media's format");
    searchWidgetFormLayout->addRow("Format:", formatFilter);

    uploaderFilter = new QLineEdit(this);
    uploaderFilter->setPlaceholderText("Media's uploader");
    searchWidgetFormLayout->addRow("Uploader:", uploaderFilter);

    minRatingFilter = new QSpinBox(this);
    minRatingFilter->setMinimum(0);
    minRatingFilter->setMaximum(100);
    minRatingFilter->setValue(0);
    searchWidgetFormLayout->addRow("Min Rating:", minRatingFilter);

    maxRatingFilter = new QSpinBox(this);
    maxRatingFilter->setMinimum(0);
    maxRatingFilter->setMaximum(100);
    maxRatingFilter->setValue(0);
    searchWidgetFormLayout->addRow("Max Rating:", maxRatingFilter);
}

void SearchWidget::setupAudioFilters() {

    audioArtistFilter = new QLineEdit(this);
    audioArtistFilter->setEnabled(false);
    searchWidgetFormLayout->addRow("Audio Artist:", audioArtistFilter);
    audioGenreFilter = new QLineEdit(this);
    audioGenreFilter->setEnabled(false);
    searchWidgetFormLayout->addRow("Audio Genre:", audioGenreFilter);
}

void SearchWidget::setupVideoFilters() {

    videoDirectorFilter = new QLineEdit(this);
    videoDirectorFilter->setEnabled(false);
    searchWidgetFormLayout->addRow("Video Director:", videoDirectorFilter);
    videoGenreFilter = new QLineEdit(this);
    videoGenreFilter->setEnabled(false);
    searchWidgetFormLayout->addRow("Video Genre", videoGenreFilter);
}

void SearchWidget::setupEBookFilters() {

    ebookAuthorFilter = new QLineEdit(this);
    ebookAuthorFilter->setEnabled(false);
    searchWidgetFormLayout->addRow("EBook Author:", ebookAuthorFilter);
    ebookPublisherFilter = new QLineEdit(this);
    ebookPublisherFilter->setEnabled(false);
    searchWidgetFormLayout->addRow("EBook Publisher", ebookPublisherFilter);
}

void SearchWidget::setupImageFilters() {

    imageCreatorFilter = new QLineEdit(this);
    imageCreatorFilter->setEnabled(false);
    searchWidgetFormLayout->addRow("Image Creator:", imageCreatorFilter);
    imageLocationFilter = new QLineEdit(this);
    imageLocationFilter->setEnabled(false);
    searchWidgetFormLayout->addRow("Location Taken", imageLocationFilter);
}

}
}

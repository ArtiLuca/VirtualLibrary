#include "TypeSelectorWidget.h"

#include <QMessageBox>

namespace View {
namespace Creator {

TypeSelectorWidget::TypeSelectorWidget(QWidget* parent)
    : QWidget(parent)
{
    // layout principale
    typeSelectorMainLayout = new QVBoxLayout(this);
    typeSelectorMainLayout->setSpacing(2);
    typeSelectorMainLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    typeSelectorMainLayout->setContentsMargins(8, 8, 8, 8);

    // combo box per selezione tipo
    typeSelector = new QComboBox(this);
    typeSelector->setToolTip("Select media type to create");
    typeSelector->addItem("Select Type");
    typeSelector->addItem("AUDIO");
    typeSelector->addItem("VIDEO");
    typeSelector->addItem("EBOOK");
    typeSelector->addItem("IMAGE");
    typeSelectorMainLayout->addWidget(typeSelector);

    // aggiuta buttons
    typeSelectorButtonBox = new QDialogButtonBox(Qt::Horizontal, this);
    typeSelectorButtonBox->addButton("Confirm", QDialogButtonBox::AcceptRole);
    typeSelectorButtonBox->addButton("Cancel", QDialogButtonBox::RejectRole);
    typeSelectorMainLayout->addWidget(typeSelectorButtonBox);

    // connect buttons
    connect(typeSelectorButtonBox, &QDialogButtonBox::accepted,
            this, &TypeSelectorWidget::onConfirmButtonClicked);
    connect(typeSelectorButtonBox, &QDialogButtonBox::rejected,
            this, &TypeSelectorWidget::onCancelButtonClicked);
}

void TypeSelectorWidget::onConfirmButtonClicked() {

    int selectIndex = typeSelector->currentIndex();
    if (selectIndex <= 0) {
        QMessageBox::warning(this, "Error", "Please select a type");
        return;
    }

    emit mediaTypeSelected(typeSelector->currentText());
}

void TypeSelectorWidget::onCancelButtonClicked() {

    emit closed();
}

}
}

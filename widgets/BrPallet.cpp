#include "BrPallet.h"

br_widgets::BrPallet::BrPallet(QWidget *parent) {
    gridLayout = new QGridLayout(this);

    cboPalletType = new QComboBox(this);
    cboPalletType->addItem("Find and Replace");

    gridLayout->addWidget(cboPalletType, 0, 0, 1, 2);

    setLayout(gridLayout);

    connect(cboPalletType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BrPallet::updatePalletType);
}

void br_widgets::BrPallet::updatePalletType(int index) {
    palletType = static_cast<br_enums::PalletType>(index);
}

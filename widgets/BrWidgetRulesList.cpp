#include "BrWidgetRulesList.h"

#include <QListWidgetItem>

#include "BrPalletFindAndRepl.h"

br_widgets::BrWidgetRulesList::BrWidgetRulesList(QWidget *parent) : QListWidget(parent) {

}

br_widgets::BrWidgetRulesList::~BrWidgetRulesList() {

}

void br_widgets::BrWidgetRulesList::addWidget() {
    auto *pallet = new BrPalletFindAndRepl(this);
    auto *item = new QListWidgetItem(this);

    item->setSizeHint(pallet->sizeHint());

    this->addItem(item);
    setItemWidget(item, pallet);

    connect(pallet, &BrPalletFindAndRepl::ruleChanged, this, &BrWidgetRulesList::ruleChanged);

    emit ruleChanged();
}

void br_widgets::BrWidgetRulesList::removeSelectedRows() {
    auto items = this->selectedItems();

    for (auto item: items) {
        this->removeItemWidget(item);
        delete takeItem(row(item));
    }
}

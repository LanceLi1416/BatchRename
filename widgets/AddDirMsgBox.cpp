#include "AddDirMsgBox.h"

#include <QPushButton>
#include <QVBoxLayout>

br_widgets::AddDirMsgBox::AddDirMsgBox(QWidget *parent) : QMessageBox(parent) {
    setIcon(QMessageBox::Information);
    setText(tr("You have dropped a folder."));
    setInformativeText(tr("How would you like to handle its contents?"));

    QAbstractButton *recursiveButton = addButton(tr("Add All Files Recursively"), QMessageBox::AcceptRole);
    QAbstractButton *contentsButton = addButton(tr("Add Folder Contents"), QMessageBox::AcceptRole);
    QAbstractButton *folderOnlyButton = addButton(tr("Add Folder Only"), QMessageBox::AcceptRole);

    QPushButton::connect(recursiveButton, &QPushButton::clicked, [this] { emit done(0); });
    QPushButton::connect(contentsButton, &QPushButton::clicked, [this] { emit done(1); });
    QPushButton::connect(folderOnlyButton, &QPushButton::clicked, [this] { emit done(2); });
}

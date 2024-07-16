#include "BrWidgetTable.h"

#include <QDir>
#include <QDragEnterEvent>
#include <QFileInfo>
#include <QMessageBox>
#include <QMimeData>
#include <QString>
#include <QToolTip>

#include "AddDirMsgBox.h"
#include "BrPallet.h"
#include "BrPalletFindAndRepl.h"
#include "../utils/utils.h"

br_widgets::BrWidgetTable::BrWidgetTable(QWidget *parent) : QTableWidget(parent) {
    setAcceptDrops(true);
    setRowCount(0);
    setColumnCount(2);
    setHorizontalHeaderLabels(QStringList() << tr("Current Name") << tr("New Name"));

    setColumnWidth(0, width() / 2);
    setColumnWidth(1, width() / 2);

    setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(this, &BrWidgetTable::onFileAdded, this, &BrWidgetTable::updateTable);
}

void br_widgets::BrWidgetTable::resizeEvent(QResizeEvent *event) {
    setColumnWidth(0, width() / 2);
    setColumnWidth(1, width() / 2);
}

void br_widgets::BrWidgetTable::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void br_widgets::BrWidgetTable::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void br_widgets::BrWidgetTable::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();

        for (const QUrl &url: urls) {
            QString file = url.toLocalFile();
            QFileInfo info(file);

            if (info.isDir()) {
                handleDirectory(file);
            } else {
                addFile(file);
            }
        }
    }
}

void br_widgets::BrWidgetTable::handleDirectory(const QString &dir) {
    AddDirMsgBox msgBox;

    int ret = msgBox.exec();

    switch (ret) {
        case 0:
            // Add all files recursively
            addDirectory(dir, true);
            break;
        case 1:
            // Add folder contents
            addDirectory(dir, false);
            break;
        case 2:
            // Add folder only
            addFile(dir);
            break;
        default:
            break;
    }
}

void br_widgets::BrWidgetTable::addFile(const QString &file) {
    QFileInfo info(file);

    if (info.exists()) {
        // File exists
        if (files.contains(file)) {
            // File already added
            QMessageBox::warning(
                    this,
                    tr("File already added"),
                    tr("The file %1 has already been added").arg(file)
            );
        } else {
            // Add new file
            files.insert(file, info);

            // Add to table
            int row = rowCount();
            insertRow(row);

            auto *item = new QTableWidgetItem(info.fileName());
            item->setToolTip(file);
            setItem(row, 0, item);

            auto *newName = new QTableWidgetItem();
            newName->setToolTip(file);
            newName->setFlags(newName->flags() & ~Qt::ItemIsEditable);
            setItem(row, 1, newName);

            emit onFileAdded(file);
        }
    } else {
        // File DNE -- Should never happen
        QMessageBox::warning(
                this,
                tr("File does not exist"),
                tr("The file %1 does not exist").arg(file)
        );
    }
}

void br_widgets::BrWidgetTable::addDirectory(const QString &dir, const bool recursive) {
    QDir directory(dir);
    QStringList fileList = directory.entryList(
            QDir::AllEntries | QDir::NoDotAndDotDot,
            QDir::Name | QDir::DirsFirst
    );

    for (const QString &file: fileList) {
        QString path = directory.filePath(file);
        QFileInfo info(path);

        if (info.isDir()) {
            if (recursive) {
                addDirectory(path, true);
            } else {
                addFile(path);
            }
        } else {
            addFile(path);
        }
    }
}

void br_widgets::BrWidgetTable::removeSelectedRows() {
    QList<QTableWidgetItem *> items = selectedItems();

    QMap<int, QString> rows;
    for (QTableWidgetItem *item: items) {
        if (!rows.contains(item->row()))
            rows.insert(item->row(), item->toolTip());
    }

    // for (QTableWidgetItem *item: items) {
    //     files.remove(item->toolTip());
    //     removeRow(item->row());
    // }

    for (auto i = rows.size() - 1; i >= 0; --i) {
        files.remove(rows[i]);
        removeRow(i);
    }
}

void br_widgets::BrWidgetTable::setRulesList(const br_widgets::BrWidgetRulesList *rulesList) {
    this->rulesList = rulesList;
}

void br_widgets::BrWidgetTable::updateTable() {
    // Re-compute the file names
    for (int i = 0; i < rowCount(); ++i) {
        QTableWidgetItem *item = this->item(i, 0);
        QString file = item->toolTip();
        QFileInfo info(file);

        // iterate through all the pallets in the rules list
        for (int j = 0; j < rulesList->count(); ++j) {
            auto *pallet = dynamic_cast<BrPalletFindAndRepl *>(rulesList->itemWidget(rulesList->item(j)));

            if (pallet) file = pallet->process(file);
        }

        // Change the text of the second column
        this->item(i, 1)->setText(file);
    }
}

void br_widgets::BrWidgetTable::run() {
    // Apply the changes
    for (int i = 0; i < rowCount(); ++i) {
        QString path = item(i, 0)->toolTip();
        QString newName = item(i, 1)->text();

        QFileInfo info = files[path];

        br_utils::os::rename(info, newName);
        files.remove(path);
        files.insert(newName, QFileInfo(newName));

        // Update the table
        item(i, 0)->setText(newName);
        item(i, 0)->setToolTip(newName);
        item(i, 1)->setText("");
    }
}


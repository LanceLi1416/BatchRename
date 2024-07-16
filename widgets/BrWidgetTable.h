#ifndef BR_TABLE_WIDGET_H
#define BR_TABLE_WIDGET_H

#include <QTableWidget>

#include <QFileInfo>
#include <QMap>

#include "BrWidgetRulesList.h"

namespace br_widgets {

    class BrWidgetTable : public QTableWidget {
    Q_OBJECT

    public:
        explicit BrWidgetTable(QWidget *parent = nullptr);

        ~BrWidgetTable() override = default;

        void setRulesList(const br_widgets::BrWidgetRulesList *rulesList);

    public slots:

        void removeSelectedRows();

        void updateTable();

        void run();

    signals:

        void onFileAdded(const QString &file);

    protected:
        void dragEnterEvent(QDragEnterEvent *event) override;

        void dragMoveEvent(QDragMoveEvent *event) override;

        void dropEvent(QDropEvent *event) override;

        void resizeEvent(QResizeEvent *event) override;

    private:

        void handleDirectory(const QString &dir);

        void addFile(const QString &file);

        void addDirectory(const QString &dir, bool recursive = false);

    private:
        QMap<QString, QFileInfo> files;

        const br_widgets::BrWidgetRulesList *rulesList;
    };

}


#endif //BR_TABLE_WIDGET_H

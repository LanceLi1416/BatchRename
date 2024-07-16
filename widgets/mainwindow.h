#ifndef BATCHRENAME_MAINWINDOW_H
#define BATCHRENAME_MAINWINDOW_H

#include <QMainWindow>

#include <QListWidget>
#include <QPushButton>

#include "BrWidgetTable.h"
#include "BrWidgetRulesList.h"

namespace br_widgets {
    QT_BEGIN_NAMESPACE
    namespace Ui { class mainwindow; }
    QT_END_NAMESPACE

    class mainwindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit mainwindow(QWidget *parent = nullptr);

        ~mainwindow() override;

    private:
        void init();

    private:
        Ui::mainwindow *ui;

        QListWidget *lstPresets;

        br_widgets::BrWidgetRulesList *lstRules;
        QPushButton *btnAddRule;
        QPushButton *btnRemoveRule;

        br_widgets::BrWidgetTable *tblMain;
    };
}

#endif //BATCHRENAME_MAINWINDOW_H

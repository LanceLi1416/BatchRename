#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSplitter>
#include <QTableWidget>

namespace br_widgets {
    mainwindow::mainwindow(QWidget *parent) :
            QMainWindow(parent), ui(new Ui::mainwindow) {
        ui->setupUi(this);

        init();

        // Connect the signal to the slot
        connect(ui->btnRun, &QPushButton::clicked, tblMain, &BrWidgetTable::run);

        connect(ui->btnRemoveFile, &QPushButton::clicked, tblMain, &BrWidgetTable::removeSelectedRows);

        connect(this->btnAddRule, &QPushButton::clicked, lstRules, &BrWidgetRulesList::addWidget);
        connect(this->btnRemoveRule, &QPushButton::clicked, lstRules, &BrWidgetRulesList::removeSelectedRows);

        connect(lstRules, &BrWidgetRulesList::ruleChanged, tblMain, &BrWidgetTable::updateTable);
    }

    void mainwindow::init() {
        // Presets
        lstPresets = new QListWidget(this);

        // Rules
        QWidget *rulesRegion = new QWidget(this);
        QVBoxLayout *rulesLayout = new QVBoxLayout(rulesRegion);
        QHBoxLayout *rulesButtonsLayout = new QHBoxLayout(rulesRegion);

        btnAddRule = new QPushButton("+", rulesRegion);
        btnRemoveRule = new QPushButton("-", rulesRegion);
        lstRules = new BrWidgetRulesList(rulesRegion);

        rulesButtonsLayout->addWidget(btnAddRule);
        rulesButtonsLayout->addWidget(btnRemoveRule);

        rulesLayout->addWidget(lstRules);
        rulesLayout->addLayout(rulesButtonsLayout);

        rulesRegion->setLayout(rulesLayout);

        // Table
        tblMain = new BrWidgetTable(this);

        // Add the widgets to the splitter
        QSplitter *splitter = new QSplitter(this);
        splitter->addWidget(lstPresets);
        splitter->addWidget(rulesRegion);
        splitter->addWidget(tblMain);
        QList<int> sizes;
        sizes << 100 << 100 << 400;
        splitter->setSizes(sizes);

        // Add splitter to the main layout
        ui->centralwidget->layout()->addWidget(splitter);

        tblMain->setRulesList(lstRules);
    }

    mainwindow::~mainwindow() {
        delete tblMain;

        delete ui;
    }
} // br_utils

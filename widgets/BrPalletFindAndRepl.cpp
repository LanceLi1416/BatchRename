#include "BrPalletFindAndRepl.h"

#include <QDir>
#include <QFileInfo>

#include "../utils/utils.h"

br_widgets::BrPalletFindAndRepl::BrPalletFindAndRepl(QWidget *parent) : BrPallet(parent) {
    lblApplyTo = new QLabel(this);
    cboApplyTo = new QComboBox(this);
    cboApplyTo->addItem("Name Only");
    cboApplyTo->addItem("Name and Extension");
    cboApplyTo->addItem("Extension Only");

    lblFind = new QLabel(this);
    lneFind = new QLineEdit(this);

    lblReplace = new QLabel(this);
    lneReplace = new QLineEdit(this);

    chkRegex = new QCheckBox(this);
    chkCase = new QCheckBox(this);
    chkFirstMatch = new QCheckBox(this);

    gridLayout->addWidget(lblApplyTo, 1, 0, 1, 1);
    gridLayout->addWidget(cboApplyTo, 1, 1, 1, 1);
    gridLayout->addWidget(lblFind, 2, 0, 1, 1);
    gridLayout->addWidget(lneFind, 2, 1, 1, 1);
    gridLayout->addWidget(lblReplace, 3, 0, 1, 1);
    gridLayout->addWidget(lneReplace, 3, 1, 1, 1);
    gridLayout->addWidget(chkRegex, 4, 1, 1, 1);
    gridLayout->addWidget(chkCase, 5, 1, 1, 1);
    gridLayout->addWidget(chkFirstMatch, 6, 1, 1, 1);

    translateUi(this);

    connect(cboApplyTo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BrPalletFindAndRepl::updateApplyTo);
    connect(lneFind, &QLineEdit::textChanged, this, &BrPalletFindAndRepl::updateFind);
    connect(lneReplace, &QLineEdit::textChanged, this, &BrPalletFindAndRepl::updateReplace);
    connect(chkRegex, &QCheckBox::stateChanged, this, &BrPalletFindAndRepl::updateRegex);
    connect(chkCase, &QCheckBox::stateChanged, this, &BrPalletFindAndRepl::updateCase);
    connect(chkFirstMatch, &QCheckBox::stateChanged, this, &BrPalletFindAndRepl::updateFirstMatch);
}

br_widgets::BrPalletFindAndRepl::~BrPalletFindAndRepl() {

}

QString br_widgets::BrPalletFindAndRepl::process(const QString &filePath) {
    QFileInfo info(filePath);

    QDir dir = info.dir();
    QString fileName = info.fileName();

    return br_utils::findAndReplace(fileName, applyTo, find, replace, regex, caseSensitive, firstMatch);
}

void br_widgets::BrPalletFindAndRepl::translateUi(QWidget *FindAndReplacePallet) {
    lblApplyTo->setText(QCoreApplication::translate(
            "FindAndReplacePallet",
            "Apply to:",
            nullptr)
    );

    lblFind->setText(QCoreApplication::translate(
            "FindAndReplacePallet",
            "Find:",
            nullptr)
    );

    lblReplace->setText(QCoreApplication::translate(
            "FindAndReplacePallet",
            "Replace:",
            nullptr)
    );

    chkRegex->setText(QCoreApplication::translate(
            "FindAndReplacePallet",
            "Use Regular Expression",
            nullptr)
    );

    chkCase->setText(QCoreApplication::translate(
            "FindAndReplacePallet",
            "Case Sensitive",
            nullptr)
    );

    chkFirstMatch->setText(QCoreApplication::translate(
            "FindAndReplacePallet",
            "First Match Only",
            nullptr)
    );
}

void br_widgets::BrPalletFindAndRepl::updateApplyTo(int index) {
    applyTo = static_cast<br_enums::ApplyTo>(index);
    emit ruleChanged();
}

void br_widgets::BrPalletFindAndRepl::updateFind(const QString &text) {
    find = text;
    emit ruleChanged();
}

void br_widgets::BrPalletFindAndRepl::updateReplace(const QString &text) {
    replace = text;
    emit ruleChanged();
}

void br_widgets::BrPalletFindAndRepl::updateRegex(int state) {
    regex = state == Qt::Checked;
    if (regex) {
        chkCase->setEnabled(false);
        chkFirstMatch->setEnabled(false);
    } else {
        chkCase->setEnabled(true);
        chkFirstMatch->setEnabled(true);
    }
    emit ruleChanged();
}

void br_widgets::BrPalletFindAndRepl::updateCase(int state) {
    caseSensitive = state == Qt::Checked;
    emit ruleChanged();
}

void br_widgets::BrPalletFindAndRepl::updateFirstMatch(int state) {
    firstMatch = state == Qt::Checked;
    emit ruleChanged();
}

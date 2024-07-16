#ifndef BATCHRENAME_BRPALLETFINDANDREPL_H
#define BATCHRENAME_BRPALLETFINDANDREPL_H

#include "BrPallet.h"

#include <QCheckBox>
#include <QComboBox>
#include <QCoreApplication>
#include <QLabel>
#include <QLineEdit>


namespace br_widgets {

    class BrPalletFindAndRepl : public BrPallet {
    Q_OBJECT

    public:
        explicit BrPalletFindAndRepl(QWidget *parent = nullptr);

        ~BrPalletFindAndRepl() override;

        QString process(const QString &filePath) override;

    private:
        void translateUi(QWidget *FindAndReplacePallet);

    private slots:

        void updateApplyTo(int index);

        void updateFind(const QString &text);

        void updateReplace(const QString &text);

        void updateRegex(int state);

        void updateCase(int state);

        void updateFirstMatch(int state);

    private:
        QLabel *lblApplyTo;
        QComboBox *cboApplyTo;

        QLabel *lblFind;
        QLineEdit *lneFind;

        QLabel *lblReplace;
        QLineEdit *lneReplace;

        QCheckBox *chkRegex;
        QCheckBox *chkCase;
        QCheckBox *chkFirstMatch;

        br_enums::ApplyTo applyTo;
        QString find;
        QString replace;
        bool regex;
        bool caseSensitive;
        bool firstMatch;
    };

}

#endif //BATCHRENAME_BRPALLETFINDANDREPL_H

#ifndef BATCHRENAME_BRWIDGETRULESLIST_H
#define BATCHRENAME_BRWIDGETRULESLIST_H

#include <QListWidget>

namespace br_widgets {

    class BrWidgetRulesList : public QListWidget {
    Q_OBJECT

    public:
        explicit BrWidgetRulesList(QWidget *parent = nullptr);

        ~BrWidgetRulesList() override;

    signals:

        void ruleChanged();

    public slots:

        void addWidget();

        void removeSelectedRows();
    };

}

#endif //BATCHRENAME_BRWIDGETRULESLIST_H

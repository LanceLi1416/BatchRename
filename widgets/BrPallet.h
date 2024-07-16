#ifndef BATCHRENAME_BRPALLET_H
#define BATCHRENAME_BRPALLET_H

#include <QWidget>

#include <QComboBox>
#include <QGridLayout>

#include "../utils/enums.h"

namespace br_widgets {

    class BrPallet : public QWidget {
    Q_OBJECT

    public:
        explicit BrPallet(QWidget *parent = nullptr);

        ~BrPallet() override = default;

        virtual QString process(const QString &filePath) = 0;

    signals:

        void ruleChanged();

    private slots:

        void updatePalletType(int index);

    public:
        br_enums::PalletType palletType;

    protected:
        QGridLayout *gridLayout;
        QComboBox *cboPalletType;
    };

}

#endif //BATCHRENAME_BRPALLET_H
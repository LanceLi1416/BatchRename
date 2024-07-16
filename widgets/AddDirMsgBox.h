#include <QMessageBox>

namespace br_widgets {

    class AddDirMsgBox : public QMessageBox {
    Q_OBJECT

    public:
        explicit AddDirMsgBox(QWidget *parent = nullptr);
    };

}
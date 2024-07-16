#include "widgets/mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    br_widgets::mainwindow w;
    w.show();

    return QApplication::exec();
}

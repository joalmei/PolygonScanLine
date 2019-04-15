#include "mainwindow.h"
#include <QApplication>
#include "appcontroller.h"

// ==================================================================================================
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    AppController app(&w);
    return a.exec();
}

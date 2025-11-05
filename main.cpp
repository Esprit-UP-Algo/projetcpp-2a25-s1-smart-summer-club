#include "mainwindow.h"
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Connection* c = Connection::createInstance();
    bool test = c->createConnection();

    if (test) {
        MainWindow w;
        w.show();
        return a.exec();
    } else {
        return -1;
    }
}


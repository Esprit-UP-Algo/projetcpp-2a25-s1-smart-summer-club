#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("Smart Summer Club");
    QApplication::setOrganizationName("SmartSummerClub");

    MainWindow w;
    w.show();

    return a.exec();
}

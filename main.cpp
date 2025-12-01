#include "connection.h"
#include "login.h"
#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(nullptr, "Erreur",
                              "Impossible de se connecter à la base !");
        return 0;
    }

    Login log;
    if (log.exec() == QDialog::Accepted)
    {
        MainWindow *w = new MainWindow(nullptr,
                                       log.getPosteBD(),
                                       log.getIdEmploye());
        w->show();
        return a.exec();
    }

    return 0;
}

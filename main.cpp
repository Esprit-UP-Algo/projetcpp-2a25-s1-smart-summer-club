#include "mainwindow.h"
#include "connection.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection connection;
    if (!connection.open()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle(QObject::tr("Erreur base de données"));
        msgBox.setText(QObject::tr("Impossible d'ouvrir la base. Vérifiez dbconfig.ini."));
        QString detail = connection.lastError();
        if (!detail.isEmpty()) {
            detail.prepend(QObject::tr("Erreur SQL : "));
        } else {
            detail = QObject::tr("Aucun message d'erreur SQL n'a été fourni.");
        }
        detail += QObject::tr("\nFichier utilisé : %1").arg(connection.configPath());
        msgBox.setInformativeText(detail);
        msgBox.exec();
        return EXIT_FAILURE;
    }

    MainWindow w;
    w.show();
    return a.exec();
}

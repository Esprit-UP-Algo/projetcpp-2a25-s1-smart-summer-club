#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test = c.createconnect();

    if (test) {
        QMessageBox::information(nullptr,
                                 QObject::tr("Connexion réussie"),
                                 QObject::tr("✅ Connexion à la base de données réussie.\n"
                                             "Cliquez sur OK pour continuer."));
    } else {
        QMessageBox::critical(nullptr,
                              QObject::tr("Erreur de connexion"),
                              QObject::tr("❌ La connexion à la base de données a échoué.\n"
                                          "Vérifiez le DSN, l'utilisateur ou le mot de passe."));
        return -1; // stoppe le programme si échec
    }

    MainWindow w;
    w.show();

    return a.exec();
}

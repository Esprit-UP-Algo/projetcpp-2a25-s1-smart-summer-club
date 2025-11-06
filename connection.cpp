#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

Connection::Connection()
{
    // Constructeur vide
}

bool Connection::createconnect()
{
    bool test = false;

    // Créer la connexion avec le driver ODBC
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet25");  // Nom de la source de données (DSN)
    db.setUserName("summer");        // Nom utilisateur
    db.setPassword("smart");         // Mot de passe

    if (db.open()) {
        test = true;
        qDebug() << "✅ Connexion à la base réussie.";
    } else {
        test = false;
        qDebug() << "❌ Erreur connexion :" << db.lastError().text();
        QMessageBox::critical(nullptr, "Erreur Base de Données", db.lastError().text());
    }

    return test;
}

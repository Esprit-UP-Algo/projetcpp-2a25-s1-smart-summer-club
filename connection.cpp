#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

Connection::Connection()
{
}

bool Connection::createconnect()
{
    bool test = false;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet25");
    db.setUserName("summer");
    db.setPassword("smart");

    if (db.open()) {
        test = true;
        qDebug() << "Connexion réussie";
    } else {
        test = false;
        qDebug() << "Erreur connexion :" << db.lastError().text();
        QMessageBox::critical(nullptr, "Erreur Base", db.lastError().text());
    }

    return test;
}

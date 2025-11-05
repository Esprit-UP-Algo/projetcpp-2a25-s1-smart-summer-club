#include "connection.h"
#include <QDebug>
#include <QSqlError>
#include <QString>

Connection* Connection::instance = nullptr;

Connection* Connection::createInstance() {
    if (!instance)
        instance = new Connection();
    return instance;
}

bool Connection::createConnection() {
    db = QSqlDatabase::addDatabase("QODBC");

    // ⚠️ Modify the line below with your actual Oracle DSN and credentials
    QString dsn = "DRIVER={Oracle in XE};DBQ=XE;Uid=system;Pwd=smartsparks;";
    db.setDatabaseName(dsn);

    if (!db.open()) {
        qDebug() << "Erreur de connexion à Oracle:" << db.lastError().text();
        return false;
    }

    qDebug() << "Connexion Oracle via ODBC réussie !";
    return true;
}

void Connection::closeConnection() {
    if (db.isOpen())
        db.close();
}

#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::initializeDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir;
    if (!dir.exists(dbPath)) {
        dir.mkpath(dbPath);
    }
    
    db.setDatabaseName(dbPath + "/smart_summer_club.db");
    
    if (!db.open()) {
        qWarning() << "Erreur d'ouverture de la base de données:" << db.lastError().text();
        return false;
    }
    
    return createTables();
}

bool DatabaseManager::createTables()
{
    QSqlQuery query(db);
    
    // Table abonnes
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS abonnes ("
        "id_abonne INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nom TEXT NOT NULL,"
        "prenom TEXT NOT NULL"
        ")")) {
        qWarning() << "Erreur création table abonnes:" << query.lastError().text();
        return false;
    }
    
    // Table activites
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS activites ("
        "id_activite INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nom TEXT NOT NULL,"
        "prix REAL NOT NULL,"
        "capacite_max INTEGER DEFAULT 50"
        ")")) {
        qWarning() << "Erreur création table activites:" << query.lastError().text();
        return false;
    }
    
    // Table inscriptions
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS inscriptions ("
        "id_inscription INTEGER PRIMARY KEY AUTOINCREMENT,"
        "id_abonne INTEGER NOT NULL,"
        "id_activite INTEGER NOT NULL,"
        "date_inscription TEXT NOT NULL,"
        "statut TEXT NOT NULL CHECK(statut IN ('confirmé', 'en attente', 'annulée')),"
        "paiement_effectue INTEGER NOT NULL DEFAULT 0,"
        "prix REAL NOT NULL,"
        "FOREIGN KEY(id_abonne) REFERENCES abonnes(id_abonne),"
        "FOREIGN KEY(id_activite) REFERENCES activites(id_activite)"
        ")")) {
        qWarning() << "Erreur création table inscriptions:" << query.lastError().text();
        return false;
    }
    
    // Insérer quelques données de test si les tables sont vides
    query.exec("SELECT COUNT(*) FROM abonnes");
    if (query.next() && query.value(0).toInt() == 0) {
        query.exec("INSERT INTO abonnes (nom, prenom) VALUES ('Dupont', 'Jean'), ('Martin', 'Marie'), ('Bernard', 'Pierre')");
    }
    
    query.exec("SELECT COUNT(*) FROM activites");
    if (query.next() && query.value(0).toInt() == 0) {
        query.exec("INSERT INTO activites (nom, prix, capacite_max) VALUES "
                   "('Natation', 50.0, 30), "
                   "('Tennis', 40.0, 20), "
                   "('Football', 35.0, 25)");
    }
    
    return true;
}

QSqlDatabase DatabaseManager::getDatabase() const
{
    return db;
}



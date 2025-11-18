#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QMessageBox>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::initializeDatabase()
{
    // Par défaut, utiliser SQLite
    dbType = SQLite;
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

bool DatabaseManager::initializeOracleDatabase(const QString& host, int port, 
                                                const QString& databaseName,
                                                const QString& user, const QString& password)
{
    // Vérifier si le driver Oracle est disponible
    if (!QSqlDatabase::isDriverAvailable("QOCI")) {
        qWarning() << "Driver Oracle (QOCI) non disponible. Veuillez installer Oracle Client.";
        return false;
    }

    dbType = Oracle;
    
    // Supprimer la connexion existante si elle existe
    if (db.isOpen()) {
        db.close();
    }
    QSqlDatabase::removeDatabase("oracle_connection");
    
    db = QSqlDatabase::addDatabase("QOCI", "oracle_connection");
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(databaseName); // Pour Oracle, c'est le SID ou Service Name
    db.setUserName(user);
    db.setPassword(password);
    
    if (!db.open()) {
        QString errorMsg = "Erreur de connexion à Oracle: " + db.lastError().text();
        qWarning() << errorMsg;
        return false;
    }
    
    qDebug() << "Connexion Oracle réussie!";
    return createTables();
}

bool DatabaseManager::createTables()
{
    if (dbType == SQLite) {
        return createTablesSQLite();
    } else if (dbType == Oracle) {
        return createTablesOracle();
    }
    return false;
}

bool DatabaseManager::createTablesSQLite()
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

bool DatabaseManager::createTablesOracle()
{
    QSqlQuery query(db);
    
    // Créer les séquences pour Oracle (ignorer si elles existent déjà)
    query.exec("CREATE SEQUENCE seq_abonnes START WITH 1 INCREMENT BY 1");
    if (query.lastError().isValid() && !query.lastError().text().contains("ORA-00955")) {
        qWarning() << "Erreur création séquence abonnes:" << query.lastError().text();
    }
    
    query.exec("CREATE SEQUENCE seq_activites START WITH 1 INCREMENT BY 1");
    if (query.lastError().isValid() && !query.lastError().text().contains("ORA-00955")) {
        qWarning() << "Erreur création séquence activites:" << query.lastError().text();
    }
    
    query.exec("CREATE SEQUENCE seq_inscriptions START WITH 1 INCREMENT BY 1");
    if (query.lastError().isValid() && !query.lastError().text().contains("ORA-00955")) {
        qWarning() << "Erreur création séquence inscriptions:" << query.lastError().text();
    }
    
    // Table abonnes (Oracle)
    if (!query.exec(
        "CREATE TABLE abonnes ("
        "id_abonne NUMBER PRIMARY KEY,"
        "nom VARCHAR2(100) NOT NULL,"
        "prenom VARCHAR2(100) NOT NULL"
        ")")) {
        // Ignorer l'erreur si la table existe déjà
        if (!query.lastError().text().contains("ORA-00955")) {
            qWarning() << "Erreur création table abonnes:" << query.lastError().text();
        }
    }
    
    // Trigger pour auto-incrémenter id_abonne
    query.exec(
        "CREATE OR REPLACE TRIGGER trg_abonnes_id "
        "BEFORE INSERT ON abonnes "
        "FOR EACH ROW "
        "BEGIN "
        "  IF :NEW.id_abonne IS NULL THEN "
        "    SELECT seq_abonnes.NEXTVAL INTO :NEW.id_abonne FROM DUAL; "
        "  END IF; "
        "END;"
    );
    
    // Table activites (Oracle)
    if (!query.exec(
        "CREATE TABLE activites ("
        "id_activite NUMBER PRIMARY KEY,"
        "nom VARCHAR2(100) NOT NULL,"
        "prix NUMBER(10,2) NOT NULL,"
        "capacite_max NUMBER DEFAULT 50"
        ")")) {
        if (!query.lastError().text().contains("ORA-00955")) {
            qWarning() << "Erreur création table activites:" << query.lastError().text();
        }
    }
    
    // Trigger pour auto-incrémenter id_activite
    query.exec(
        "CREATE OR REPLACE TRIGGER trg_activites_id "
        "BEFORE INSERT ON activites "
        "FOR EACH ROW "
        "BEGIN "
        "  IF :NEW.id_activite IS NULL THEN "
        "    SELECT seq_activites.NEXTVAL INTO :NEW.id_activite FROM DUAL; "
        "  END IF; "
        "END;"
    );
    
    // Table inscriptions (Oracle)
    if (!query.exec(
        "CREATE TABLE inscriptions ("
        "id_inscription NUMBER PRIMARY KEY,"
        "id_abonne NUMBER NOT NULL,"
        "id_activite NUMBER NOT NULL,"
        "date_inscription DATE NOT NULL,"
        "statut VARCHAR2(20) NOT NULL CHECK(statut IN ('confirmé', 'en attente', 'annulée')),"
        "paiement_effectue NUMBER(1) NOT NULL DEFAULT 0,"
        "prix NUMBER(10,2) NOT NULL,"
        "CONSTRAINT fk_abonne FOREIGN KEY(id_abonne) REFERENCES abonnes(id_abonne),"
        "CONSTRAINT fk_activite FOREIGN KEY(id_activite) REFERENCES activites(id_activite)"
        ")")) {
        if (!query.lastError().text().contains("ORA-00955")) {
            qWarning() << "Erreur création table inscriptions:" << query.lastError().text();
        }
    }
    
    // Trigger pour auto-incrémenter id_inscription
    query.exec(
        "CREATE OR REPLACE TRIGGER trg_inscriptions_id "
        "BEFORE INSERT ON inscriptions "
        "FOR EACH ROW "
        "BEGIN "
        "  IF :NEW.id_inscription IS NULL THEN "
        "    SELECT seq_inscriptions.NEXTVAL INTO :NEW.id_inscription FROM DUAL; "
        "  END IF; "
        "END;"
    );
    
    // Insérer quelques données de test si les tables sont vides
    query.exec("SELECT COUNT(*) FROM abonnes");
    if (query.next() && query.value(0).toInt() == 0) {
        query.exec("INSERT INTO abonnes (nom, prenom) VALUES ('Dupont', 'Jean')");
        query.exec("INSERT INTO abonnes (nom, prenom) VALUES ('Martin', 'Marie')");
        query.exec("INSERT INTO abonnes (nom, prenom) VALUES ('Bernard', 'Pierre')");
    }
    
    query.exec("SELECT COUNT(*) FROM activites");
    if (query.next() && query.value(0).toInt() == 0) {
        query.exec("INSERT INTO activites (nom, prix, capacite_max) VALUES ('Natation', 50.0, 30)");
        query.exec("INSERT INTO activites (nom, prix, capacite_max) VALUES ('Tennis', 40.0, 20)");
        query.exec("INSERT INTO activites (nom, prix, capacite_max) VALUES ('Football', 35.0, 25)");
    }
    
    return true;
}

QSqlDatabase DatabaseManager::getDatabase() const
{
    return db;
}

#include "databasemanager.h"
#include <QDebug>
#include <QApplication>
#include <QSqlQuery>
#include <QMessageBox>

DatabaseManager* DatabaseManager::m_instance = nullptr;

DatabaseManager::DatabaseManager(QObject* parent) : QObject(parent)
{
}

DatabaseManager::~DatabaseManager()
{
    disconnect();
}

DatabaseManager& DatabaseManager::getInstance()
{
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    if (!m_instance) {
        m_instance = new DatabaseManager(qApp);
    }
    return *m_instance;
}

bool DatabaseManager::connect()
{
    QMutexLocker locker(&m_mutex);

    if (m_database.isOpen()) {
        qDebug() << "La connexion est déjà établie.";
        return true;
    }

    // Configuration Oracle XE 11g
    m_database = QSqlDatabase::addDatabase("QODBC", "SmartSummerApp_Connection");

    // Set up the connection using a DSN
    m_database.setDatabaseName("SmartSummerAppDB");
    m_database.setUserName("SYSTEM");
    m_database.setPassword("smartsparks");
    m_database.setConnectOptions("SQL_ATTR_CONNECTION_TIMEOUT=5;SQL_ATTR_LOGIN_TIMEOUT=5");

    if (!m_database.open()) {
        QString error = m_database.lastError().text();
        qCritical() << "Échec de la connexion à la base de données:" << error;
        QMessageBox::critical(nullptr, "Erreur de connexion", 
                            "Impossible de se connecter à la base de données.\n"
                            "Veuillez vérifier que le service Oracle est démarré.\n"
                            "Détails: " + error);
        return false;
    }
    
    // Configuration de la session
    QSqlQuery sessionQuery(m_database);
    if (!sessionQuery.exec("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY'")) {
        qWarning() << "Impossible de définir le format de date:" << sessionQuery.lastError().text();
    }

    // Vérification de la connexion
    QSqlQuery testQuery(m_database);
    if (!testQuery.exec("SELECT 1 FROM DUAL")) {
        QString error = testQuery.lastError().text();
        qCritical() << "Test de connexion échoué:" << error;
        m_database.close();
        return false;
    }

    qDebug() << "Connexion à la base de données établie avec succès.";
    
    // Création des tables si nécessaire
    if (!createTables()) {
        qCritical() << "Échec lors de la création des tables.";
        return false;
    }

    return true;
}

void DatabaseManager::disconnect()
{
    QMutexLocker locker(&m_mutex);
    if (m_database.isOpen()) {
        m_database.close();
    }
}

bool DatabaseManager::isConnected() const
{
    QMutexLocker locker(&m_mutex);
    return m_database.isOpen();
}

QSqlDatabase DatabaseManager::getDatabase() const
{
    return m_database;
}

QSqlQuery DatabaseManager::executeQuery(const QString& queryStr)
{
    QMutexLocker locker(&m_mutex);
    QSqlQuery query(m_database);
    if (!query.exec(queryStr)) {
        qDebug() << "Erreur query:" << query.lastError().text();
    }
    return query;
}

bool DatabaseManager::executeTransaction(const QStringList& queries)
{
    QMutexLocker locker(&m_mutex);
    if (!m_database.transaction()) {
        qDebug() << "Transaction échouée";
        return false;
    }

    foreach (const QString& queryStr, queries) {
        QSqlQuery query(m_database);
        if (!query.exec(queryStr)) {
            qDebug() << "Query échouée:" << query.lastError().text();
            m_database.rollback();
            return false;
        }
    }

    return m_database.commit();
}

bool DatabaseManager::testConnection()
{
    return isConnected();
}

bool DatabaseManager::createTables()
{
    QMutexLocker locker(&m_mutex);
    QSqlQuery query(m_database);
    bool success = true;

    // Désactiver temporairement les contraintes de clé étrangère
    if (!query.exec("ALTER SESSION SET CONSTRAINTS = DEFERRED")) {
        qWarning() << "Impossible de désactiver les contraintes:" << query.lastError().text();
    }

    // Fonction utilitaire pour exécuter les requêtes avec gestion d'erreur
    auto executeQuery = [&](const QString& sql) -> bool {
        if (!query.exec(sql)) {
            qWarning() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
            qDebug() << "Requête en échec:" << sql;
            return false;
        }
        return true;
    };

    // Table ABONNE
    const QString createAbonneTable = 
    "BEGIN "
    "   BEGIN "
    "       EXECUTE IMMEDIATE 'CREATE TABLE ABONNE ("
    "           ID_ABONNE NUMBER PRIMARY KEY, "
    "           NOM VARCHAR2(100) NOT NULL, "
    "           PRENOM VARCHAR2(100) NOT NULL, "
    "           DATE_NAISSANCE DATE, "
    "           ADRESSE VARCHAR2(200), "
    "           TELEPHONE VARCHAR2(20), "
    "           EMAIL VARCHAR2(100), "
    "           DATE_INSCRIPTION DATE DEFAULT SYSDATE, "
    "           CONSTRAINT CHK_EMAIL CHECK (EMAIL LIKE ''%@%.%''), "
    "           CONSTRAINT CHK_TELEPHONE CHECK (REGEXP_LIKE(TELEPHONE, ''^[0-9+() -]+$''))"
    "       )';"
    "   EXCEPTION "
    "       WHEN OTHERS THEN "
    "           IF SQLCODE = -955 THEN NULL; "
    "           ELSE RAISE; "
    "           END IF; "
    "   END; "
    "END;";

    // Séquence pour ABONNE
    const QString createAbonneSeq = 
    "DECLARE "
    "   v_count NUMBER; "
    "BEGIN "
    "   SELECT COUNT(*) INTO v_count FROM user_sequences WHERE sequence_name = 'SEQ_ABONNE'; "
    "   IF v_count = 0 THEN "
    "       EXECUTE IMMEDIATE 'CREATE SEQUENCE SEQ_ABONNE "
    "           START WITH 1 INCREMENT BY 1 NOCACHE NOCYCLE';"
    "   END IF; "
    "END;";

    // Table ACTIVITE
    const QString createActiviteTable = 
    "BEGIN "
    "   BEGIN "
    "       EXECUTE IMMEDIATE 'CREATE TABLE ACTIVITE ("
    "           ID_ACTIVITE NUMBER PRIMARY KEY, "
    "           NOM VARCHAR2(100) NOT NULL, "
    "           DESCRIPTION VARCHAR2(500), "
    "           DUREE_SEANCE NUMBER, "
    "           LIEU VARCHAR2(100), "
    "           NB_PARTICIPANTS_MAX NUMBER, "
    "           DATE_CREATION DATE DEFAULT SYSDATE, "
    "           CONSTRAINT CHK_DUREE CHECK (DUREE_SEANCE > 0), "
    "           CONSTRAINT CHK_PARTICIPANTS CHECK (NB_PARTICIPANTS_MAX > 0)"
    "       )';"
    "   EXCEPTION "
    "       WHEN OTHERS THEN "
    "           IF SQLCODE = -955 THEN NULL; "
    "           ELSE RAISE; "
    "           END IF; "
    "   END; "
    "END;";

    // Table INSCRIPTION avec contraintes améliorées
    const QString createInscriptionTable = 
    "BEGIN "
    "   BEGIN "
    "       EXECUTE IMMEDIATE 'CREATE TABLE INSCRIPTION ("
    "           ID_INSCRIPTION NUMBER PRIMARY KEY, "
    "           ID_ABONNE NUMBER NOT NULL, "
    "           ID_ACTIVITE NUMBER NOT NULL, "
    "           DATE_INSCRIPTION DATE DEFAULT SYSDATE, "
    "           STATUT VARCHAR2(20) DEFAULT ''EN ATTENTE'' "
    "               CHECK (STATUT IN (''EN ATTENTE'', ''CONFIRMEE'', ''ANNULEE'')), "
    "           PAIEMENT_EFFECTUE VARCHAR2(1) DEFAULT ''N'' "
    "               CHECK (PAIEMENT_EFFECTUE IN (''O'', ''N'')), "
    "           PRIX NUMBER(10,2), "
    "           DATE_MODIFICATION TIMESTAMP DEFAULT SYSTIMESTAMP, "
    "           CONSTRAINT FK_INSCRIPTION_ABONNE FOREIGN KEY (ID_ABONNE) "
    "               REFERENCES ABONNE(ID_ABONNE) ON DELETE CASCADE, "
    "           CONSTRAINT FK_INSCRIPTION_ACTIVITE FOREIGN KEY (ID_ACTIVITE) "
    "               REFERENCES ACTIVITE(ID_ACTIVITE) ON DELETE CASCADE, "
    "           CONSTRAINT UQ_INSCRIPTION UNIQUE (ID_ABONNE, ID_ACTIVITE), "
    "           CONSTRAINT CHK_PRIX CHECK (PRIX >= 0)"
    "       )';"
    "   EXCEPTION "
    "       WHEN OTHERS THEN "
    "           IF SQLCODE = -955 THEN NULL; "
    "           ELSE RAISE; "
    "           END IF; "
    "   END; "
    "END;";

    // Exécution des requêtes
    success &= executeQuery(createAbonneTable);
    success &= executeQuery(createAbonneSeq);
    success &= executeQuery(createActiviteTable);
    success &= executeQuery(createInscriptionTable);

    // Création des index pour améliorer les performances
    const QString createIndexes = 
    "BEGIN "
    "   -- Index sur les champs de recherche fréquents "
    "   BEGIN "
    "       EXECUTE IMMEDIATE 'CREATE INDEX IDX_ABONNE_NOM ON ABONNE(NOM)';"
    "   EXCEPTION WHEN OTHERS THEN NULL; END; "
    "   BEGIN "
    "       EXECUTE IMMEDIATE 'CREATE INDEX IDX_ABONNE_PRENOM ON ABONNE(PRENOM)';"
    "   EXCEPTION WHEN OTHERS THEN NULL; END; "
    "   BEGIN "
    "       EXECUTE IMMEDIATE 'CREATE INDEX IDX_ABONNE_EMAIL ON ABONNE(EMAIL)';"
    "   EXCEPTION WHEN OTHERS THEN NULL; END; "
    "   BEGIN "
    "       EXECUTE IMMEDIATE 'CREATE INDEX IDX_INSCRIPTION_DATES ON INSCRIPTION(DATE_INSCRIPTION, ID_ACTIVITE)';"
    "   EXCEPTION WHEN OTHERS THEN NULL; END; "
    "END;";
    
    success &= executeQuery(createIndexes);

    // Réactiver les contraintes
    if (!query.exec("ALTER SESSION SET CONSTRAINTS = IMMEDIATE")) {
        qWarning() << "Impossible de réactiver les contraintes:" << query.lastError().text();
        success = false;
    }

    // Vérification de l'intégrité des tables
    if (success) {
        qDebug() << "Structure de la base de données vérifiée avec succès.";
        // Insérer des données de test uniquement si les tables viennent d'être créées
        QSqlQuery checkQuery("SELECT COUNT(*) FROM ABONNE", m_database);
        if (checkQuery.next() && checkQuery.value(0).toInt() == 0) {
            qDebug() << "Insertion des données de test...";
            insertSampleData();
        }
    } else {
        qCritical() << "Des erreurs sont survenues lors de la création des tables.";
    }

    return success;
}

bool DatabaseManager::insertSampleData()
{
    QMutexLocker locker(&m_mutex);
    QSqlQuery query(m_database);
    
    // Désactiver temporairement les contraintes
    query.exec("SET CONSTRAINTS ALL DEFERRED");
    
    // Vérifier si des données existent déjà
    query.exec("SELECT COUNT(*) FROM ABONNE");
    if (query.next() && query.value(0).toInt() > 0) {
        qDebug() << "Des données existent déjà, insertion des données de test ignorée.";
        return true;
    }
    
    // Démarrer une transaction
    if (!m_database.transaction()) {
        qWarning() << "Impossible de démarrer la transaction:" << m_database.lastError().text();
        return false;
    }
    
    try {
        // Insérer des abonnés de test
        QStringList abonnes = {
            "1, 'Dupont', 'Jean', TO_DATE('15/05/1990', 'DD/MM/YYYY'), '123 Rue de Paris', '0123456789', 'jean.dupont@example.com', SYSDATE",
            "2, 'Martin', 'Sophie', TO_DATE('22/11/1985', 'DD/MM/YYYY'), '456 Avenue des Fleurs', '0612345678', 'sophie.martin@example.com', SYSDATE",
            "3, 'Dubois', 'Pierre', TO_DATE('03/07/1995', 'DD/MM/YYYY'), '789 Boulevard Voltaire', '0789456123', 'pierre.dubois@example.com', SYSDATE"
        };
        
        foreach (const QString& abonne, abonnes) {
            if (!query.exec("INSERT INTO ABONNE (ID_ABONNE, NOM, PRENOM, DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL, DATE_INSCRIPTION) VALUES (" + abonne + ")")) {
                throw query.lastError();
            }
        }
        
        // Insérer des activités de test
        QStringList activites = {
            "1, 'Yoga', 'Séance de yoga relaxante', 60, 'Salle 1', 15, SYSDATE",
            "2, 'Natation', 'Cours de natation pour tous niveaux', 45, 'Piscine', 10, SYSDATE",
            "3, 'Musculation', 'Renforcement musculaire', 60, 'Salle de musculation', 8, SYSDATE"
        };
        
        foreach (const QString& activite, activites) {
            if (!query.exec("INSERT INTO ACTIVITE (ID_ACTIVITE, NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX, DATE_CREATION) VALUES (" + activite + ")")) {
                throw query.lastError();
            }
        }
        
        // Insérer des inscriptions de test
        QStringList inscriptions = {
            "1, 1, 1, SYSDATE, 'CONFIRMEE', 'O', 25.00, SYSTIMESTAMP",
            "2, 1, 2, SYSDATE, 'EN ATTENTE', 'N', 20.00, SYSTIMESTAMP",
            "3, 2, 1, SYSDATE, 'CONFIRMEE', 'O', 25.00, SYSTIMESTAMP",
            "4, 3, 3, SYSDATE, 'CONFIRMEE', 'O', 30.00, SYSTIMESTAMP"
        };
        
        foreach (const QString& inscription, inscriptions) {
            if (!query.exec("INSERT INTO INSCRIPTION (ID_INSCRIPTION, ID_ABONNE, ID_ACTIVITE, DATE_INSCRIPTION, STATUT, PAIEMENT_EFFECTUE, PRIX, DATE_MODIFICATION) VALUES (" + inscription + ")")) {
                throw query.lastError();
            }
        }
        
        // Valider la transaction
        if (!m_database.commit()) {
            throw m_database.lastError();
        }
        
        qDebug() << "Données de test insérées avec succès.";
        return true;
        
    } catch (const QSqlError& e) {
        m_database.rollback();
        qCritical() << "Erreur lors de l'insertion des données de test:" << e.text();
        return false;
    }
}

#include "connection.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QtGlobal>
#include <QStringList>
#include <QTextStream>
#include <QObject>
#include <vector>

Connection::Connection()
{
    loadConfiguration();
    if (m_driver.isEmpty()) {
        m_driver = QStringLiteral("QSQLITE");
    }
}

Connection::~Connection()
{
    close();
}

bool Connection::open()
{
    if (m_driver.isEmpty()) {
        m_driver = QStringLiteral("QSQLITE");
    }

    if (QSqlDatabase::contains(m_connectionName)) {
        m_db = QSqlDatabase::database(m_connectionName);
    } else {
        m_db = QSqlDatabase::addDatabase(m_driver, m_connectionName);
    }

    if (m_driver.compare(QStringLiteral("QSQLITE"), Qt::CaseInsensitive) == 0) {
        const QString sqlitePath = resolveSqlitePath();
        QFileInfo info(sqlitePath);
        if (!info.absolutePath().isEmpty()) {
            QDir().mkpath(info.absolutePath());
        }
        m_db.setDatabaseName(sqlitePath);

    } else if (m_driver.compare(QStringLiteral("QODBC"), Qt::CaseInsensitive) == 0) {
        const QString dsn = !m_dsn.isEmpty() ? m_dsn : buildOracleConnectionString();
        m_db.setDatabaseName(dsn);
    } else {
        if (!m_host.isEmpty()) {
            m_db.setHostName(m_host);
        }
        if (m_port > 0) {
            m_db.setPort(m_port);
        }
        if (!m_serviceName.isEmpty()) {
            m_db.setDatabaseName(m_serviceName);
        }
    }

    if (!m_user.isEmpty()) {
        m_db.setUserName(m_user);
    }
    if (!m_password.isEmpty()) {
        m_db.setPassword(m_password);
    }

    if (!m_db.open()) {
        m_lastError = m_db.lastError().text();
        qCritical() << QObject::tr("Échec de la connexion à la base :")
                    << m_db.lastError().text();
        return false;
    }

    if (!ensureSchema()) {
        qCritical() << QObject::tr("Impossible de préparer le schéma :") << m_lastError;
        return false;
    }

    m_lastError.clear();
    qInfo() << "Connexion à la base établie via" << m_driver
            << "connection name:" << m_db.connectionName();
    return true;
}

void Connection::close()
{
    if (m_db.isValid() && m_db.isOpen()) {
        m_db.close();
    }
}

bool Connection::isOpen() const
{
    return m_db.isValid() && m_db.isOpen();
}

QSqlDatabase Connection::database() const
{
    return m_db;
}

QString Connection::ensureConfigFile() const
{
    const QString envPath = qEnvironmentVariable("SMART_SUMMER_DBCONFIG");
    if (!envPath.isEmpty() && QFile::exists(envPath)) {
        qInfo() << QObject::tr("Fichier de configuration (env) :") << envPath;
        return envPath;
    }

    const QString fileName = QStringLiteral("dbconfig.ini");
    const QString appDir = QCoreApplication::applicationDirPath();
    QStringList searchPaths;
    auto collectPaths = [&](const QString& base) {
        QDir dir(base);
        for (int level = 0; level < 5 && dir.exists(); ++level) {
            searchPaths << dir.filePath(fileName);
            if (!dir.cdUp()) {
                break;
            }
        }
    };
    collectPaths(appDir);
    collectPaths(QDir::currentPath());
    searchPaths.removeDuplicates();

    for (const QString &path : searchPaths) {
        if (QFile::exists(path)) {
            return path;
        }
    }

    const QString targetPath = searchPaths.first();
    const QString examplePath = QDir(appDir).filePath(QStringLiteral("dbconfig.example.ini"));
    if (QFile::exists(examplePath)) {
        if (QFile::copy(examplePath, targetPath)) {
            qInfo() << QObject::tr("Fichier de configuration copié depuis le modèle.");
            return targetPath;
        }
    }

    QFile file(targetPath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "[database]\n";
        out << "driver=QSQLITE\n";
        out << "path=" << defaultSqlitePath() << "\n";
        out << "dsn=\n";
        out << "host=\n";
        out << "port=\n";
        out << "service=\n";
        out << "user=\n";
        out << "password=\n";
        file.close();
        qWarning() << QObject::tr("Fichier de configuration créé à :") << targetPath;
    }
    return targetPath;
}

void Connection::loadConfiguration()
{
    m_configPath = ensureConfigFile();
    QSettings settings(m_configPath, QSettings::IniFormat);
    const QStringList groups = settings.childGroups();
    const bool hasDatabaseGroup = groups.contains(QStringLiteral("database"));
    const QString group = hasDatabaseGroup ? QStringLiteral("database")
                                           : QStringLiteral("oracle");
    settings.beginGroup(group);
    const QString defaultDriver = hasDatabaseGroup ? QStringLiteral("QSQLITE")
                                                   : QStringLiteral("QODBC");
    m_driver = settings.value(QStringLiteral("driver"), defaultDriver).toString();
    m_dsn = settings.value(QStringLiteral("dsn")).toString();
    m_host = settings.value(QStringLiteral("host")).toString();
    m_port = settings.value(QStringLiteral("port"), hasDatabaseGroup ? 0 : 1521).toInt();
    m_serviceName = settings.value(QStringLiteral("service")).toString();
    m_user = settings.value(QStringLiteral("user")).toString();
    m_password = settings.value(QStringLiteral("password")).toString();
    m_databasePath = settings.value(QStringLiteral("path"),
                                    settings.value(QStringLiteral("database"))).toString();
    settings.endGroup();
}

QString Connection::buildOracleConnectionString() const
{
    // For Oracle ODBC we normally just use the DSN.
    if (!m_dsn.isEmpty()) {
        return m_dsn;   // "Source_Projet2A"
    }

    // Fallback: build a full connection string if someone sets host/port/service instead.
    QString descriptor = QStringLiteral("%1:%2/%3")
                             .arg(m_host.isEmpty() ? QStringLiteral("localhost") : m_host)
                             .arg(m_port > 0 ? m_port : 1521)
                             .arg(m_serviceName.isEmpty() ? QStringLiteral("xe") : m_serviceName);

    QStringList parts;
    parts << QStringLiteral("Driver={Oracle in XE}")
          << QStringLiteral("Dbq=%1").arg(descriptor);
    if (!m_user.isEmpty()) {
        parts << QStringLiteral("Uid=%1").arg(m_user);
    }
    if (!m_password.isEmpty()) {
        parts << QStringLiteral("Pwd=%1").arg(m_password);
    }
    return parts.join(QStringLiteral(";"));
}

QString Connection::lastError() const
{
    return m_lastError;
}

QString Connection::configPath() const
{
    return m_configPath;
}

bool Connection::ensureSchema()
{
    // Only create the SQLite table when using SQLite.
    if (m_driver.compare(QStringLiteral("QSQLITE"), Qt::CaseInsensitive) != 0) {
        return true;
    }

    QSqlQuery query(m_db);
    const QString sql = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS ACTIVITE ("
        "ID INTEGER PRIMARY KEY,"
        "NOM TEXT NOT NULL,"
        "DESCRIPTION TEXT NOT NULL,"
        "DUREE_SEANCE INTEGER,"
        "LIEU TEXT,"
        "NB_PARTICIPANTS_MAX INTEGER,"
        "RESPONSABLE_CLUB TEXT"
        ")"
        );

    if (!query.exec(sql)) {
        m_lastError = query.lastError().text();
        return false;
    }

    if (!seedSampleActivities()) {
        return false;
    }
    return true;
}

QString Connection::resolveSqlitePath() const
{
    if (!m_databasePath.isEmpty()) {
        return m_databasePath;
    }
    return defaultSqlitePath();
}

QString Connection::defaultSqlitePath() const
{
    QString base = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (base.isEmpty()) {
        base = QDir::currentPath();
    }
    QDir dir(base);
    dir.mkpath(QStringLiteral("."));
    return dir.filePath(QStringLiteral("smart_summer.db"));
}

bool Connection::seedSampleActivities()
{
    QSqlQuery countQuery(m_db);
    if (!countQuery.exec(QStringLiteral("SELECT COUNT(*) FROM ACTIVITE"))) {
        m_lastError = countQuery.lastError().text();
        return false;
    }
    if (countQuery.next() && countQuery.value(0).toInt() > 0) {
        return true;
    }

    struct Sample {
        int id;
        QString nom;
        QString description;
        int duree;
        QString lieu;
        int participantsMax;
        QString responsable;
    };

    const std::vector<Sample> samples = {
        {1, QObject::tr("Atelier robotique"), QObject::tr("Assemblage et programmation d'un mini-rover."), 120, QObject::tr("Lab Tech"), 12, QObject::tr("Club InnovBot")},
        {2, QObject::tr("Yoga matinal"), QObject::tr("Séance bien-être pour lancer la journée."), 60, QObject::tr("Terrasse"), 25, QObject::tr("Club Santé")},
        {3, QObject::tr("Hackathon vert"), QObject::tr("Prototypage d'idées éco-responsables."), 180, QObject::tr("Open Space"), 30, QObject::tr("Club GreenTech")},
        {4, QObject::tr("Tournoi e-sport"), QObject::tr("Compétition amicale sur jeux coopératifs."), 150, QObject::tr("Arena"), 40, QObject::tr("Club Gaming")},
        {5, QObject::tr("Atelier cuisine zéro déchet"), QObject::tr("Recettes créatives avec restes alimentaires."), 90, QObject::tr("FabLab"), 15, QObject::tr("Club Culinaire")}
    };

    QSqlQuery insert(m_db);
    insert.prepare(QStringLiteral(
        "INSERT INTO ACTIVITE (ID, NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX, RESPONSABLE_CLUB) "
        "VALUES (:id, :nom, :description, :duree, :lieu, :participants, :responsable)"));

    for (const auto &sample : samples) {
        insert.bindValue(QStringLiteral(":id"), sample.id);
        insert.bindValue(QStringLiteral(":nom"), sample.nom);
        insert.bindValue(QStringLiteral(":description"), sample.description);
        insert.bindValue(QStringLiteral(":duree"), sample.duree);
        insert.bindValue(QStringLiteral(":lieu"), sample.lieu);
        insert.bindValue(QStringLiteral(":participants"), sample.participantsMax);
        insert.bindValue(QStringLiteral(":responsable"), sample.responsable);
        if (!insert.exec()) {
            m_lastError = insert.lastError().text();
            return false;
        }
    }

    qInfo() << QObject::tr("Base peuplée avec %1 activités de démonstration.").arg(samples.size());
    return true;
}

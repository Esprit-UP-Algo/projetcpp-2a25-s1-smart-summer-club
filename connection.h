#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QString>

class Connection
{
public:
    Connection();
    ~Connection();

    bool open();
    void close();
    bool isOpen() const;
    QSqlDatabase database() const;
    QString lastError() const;
    QString configPath() const;

private:
    QString ensureConfigFile() const;
    void loadConfiguration();
    QString buildOracleConnectionString() const;
    bool ensureSchema();
    bool seedSampleActivities();
    QString resolveSqlitePath() const;
    QString defaultSqlitePath() const;

    QString m_driver;
    QString m_dsn;
    QString m_host;
    int m_port = 1521;
    QString m_serviceName;
    QString m_user;
    QString m_password;
    QString m_databasePath;
    QString m_configPath;
    QString m_connectionName = QStringLiteral("SMART_SUMMER_DB");

    QSqlDatabase m_db;
    QString m_lastError;
};

#endif // CONNECTION_H

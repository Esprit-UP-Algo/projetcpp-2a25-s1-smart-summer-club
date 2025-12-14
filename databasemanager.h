#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMutex>
#include <QMessageBox>

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    static DatabaseManager& getInstance();
    bool connect();
    void disconnect();
    bool isConnected() const;
    QSqlDatabase getDatabase() const;
    QSqlQuery executeQuery(const QString& query);
    bool executeTransaction(const QStringList& queries);

    // Test connection
    bool testConnection();

private:
    DatabaseManager(QObject* parent = nullptr);
    ~DatabaseManager();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    QSqlDatabase m_database;
    mutable QMutex m_mutex;
    static DatabaseManager* m_instance;

    // Helper methods
    bool createTables();
    bool insertSampleData();
};

#endif // DATABASEMANAGER_H

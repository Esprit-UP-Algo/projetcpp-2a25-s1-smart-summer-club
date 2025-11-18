#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>

class DatabaseManager
{
public:
    enum DatabaseType {
        SQLite,
        Oracle
    };

    static DatabaseManager& instance();
    bool initializeDatabase();
    bool initializeOracleDatabase(const QString& host, int port, const QString& databaseName, 
                                  const QString& user, const QString& password);
    QSqlDatabase getDatabase() const;
    DatabaseType getDatabaseType() const { return dbType; }

private:
    DatabaseManager() = default;
    ~DatabaseManager() = default;
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    QSqlDatabase db;
    DatabaseType dbType = SQLite;
    bool createTables();
    bool createTablesSQLite();
    bool createTablesOracle();
};

#endif // DATABASEMANAGER_H

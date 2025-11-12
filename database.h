#ifndef DATABASE_H
#define DATABASE_H

#include <QString>

namespace Database {
// Initialise la connexion DB par défaut (SQLite ou autre selon vos besoins)
bool init(const QString& driverName,
          const QString& connectionName = "default",
          const QString& databaseName = QString(),
          const QString& host = QString(),
          int port = -1,
          const QString& user = QString(),
          const QString& password = QString());
}

#endif // DATABASE_H

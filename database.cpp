#include "database.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

namespace Database {

bool init(const QString& driverName,
          const QString& connectionName,
          const QString& databaseName,
          const QString& host,
          int port,
          const QString& user,
          const QString& password)
{
    if (!QSqlDatabase::isDriverAvailable(driverName)) {
        qWarning() << "Driver non disponible:" << driverName;
        return false;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(driverName, connectionName);

    if (!host.isEmpty()) db.setHostName(host);
    if (!databaseName.isEmpty()) db.setDatabaseName(databaseName);
    if (port > 0) db.setPort(port);
    if (!user.isEmpty()) db.setUserName(user);
    if (!password.isEmpty()) db.setPassword(password);

    if (!db.open()) {
        qWarning() << "Echec ouverture DB:" << db.lastError().text();
        return false;
    }
    return true;
}

} // namespace Database

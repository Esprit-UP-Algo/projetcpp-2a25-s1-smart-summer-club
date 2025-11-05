#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>

class Connection {
public:
    static Connection* createInstance();
    bool createConnection();
    void closeConnection();

private:
    Connection() = default;
    static Connection* instance;
    QSqlDatabase db;
};

#endif // CONNECTION_H

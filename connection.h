#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QObject>

class Connection
{
public:
    Connection();          // Constructeur
    bool createconnect();  // Fonction pour établir la connexion
};

#endif // CONNECTION_H

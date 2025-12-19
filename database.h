#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QList>
#include <QDebug>

class Database
{
public:
    Database();

    // Connexion & création table
    bool connect();
    bool createTable();

    // ===== CRUD MATERIEL =====
    bool addItem(const QString &nom,
                 const QString &categorie,
                 int quantite,
                 const QString &etat);

    QList<QList<QVariant>> getAllItems();

    bool updateItem(int id,
                    const QString &nom,
                    const QString &categorie,
                    int quantite,
                    const QString &etat);

    bool deleteItem(int id);

    void close();

private:
    QSqlDatabase db;
};

#endif // DATABASE_H

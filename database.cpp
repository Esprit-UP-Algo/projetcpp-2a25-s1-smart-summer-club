#include "database.h"

Database::Database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("materiel.db");
}

bool Database::connect()
{
    if (!db.open()) {
        qDebug() << "Erreur DB :" << db.lastError().text();
        return false;
    }
    return true;
}

bool Database::createTable()
{
    QSqlQuery query;
    QString sql =
        "CREATE TABLE IF NOT EXISTS materiel ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "nom TEXT NOT NULL, "
        "categorie TEXT, "
        "quantite INTEGER, "
        "etat TEXT)";

    if (!query.exec(sql)) {
        qDebug() << "Erreur création table :" << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::addItem(const QString &nom,
                       const QString &categorie,
                       int quantite,
                       const QString &etat)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO materiel (nom, categorie, quantite, etat) "
        "VALUES (?, ?, ?, ?)");
    query.addBindValue(nom);
    query.addBindValue(categorie);
    query.addBindValue(quantite);
    query.addBindValue(etat);

    return query.exec();
}

QList<QList<QVariant>> Database::getAllItems()
{
    QList<QList<QVariant>> items;
    QSqlQuery query("SELECT * FROM materiel ORDER BY id");

    while (query.next()) {
        QList<QVariant> row;
        row << query.value("id")
            << query.value("nom")
            << query.value("categorie")
            << query.value("quantite")
            << query.value("etat");
        items.append(row);
    }
    return items;
}

bool Database::updateItem(int id,
                          const QString &nom,
                          const QString &categorie,
                          int quantite,
                          const QString &etat)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE materiel SET nom=?, categorie=?, quantite=?, etat=? "
        "WHERE id=?");

    query.addBindValue(nom);
    query.addBindValue(categorie);
    query.addBindValue(quantite);
    query.addBindValue(etat);
    query.addBindValue(id);

    return query.exec() && query.numRowsAffected() > 0;
}

bool Database::deleteItem(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM materiel WHERE id=?");
    query.addBindValue(id);

    return query.exec() && query.numRowsAffected() > 0;
}

void Database::close()
{
    db.close();
}

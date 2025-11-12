qDebug() << QSqlDatabase::drivers();
#include <QApplication>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlDatabase>

#include "database.h"
#include "gestion-inscription.h

static bool createSchemaIfNeeded()
{
    // Minimal schema to support the Inscription CRUD and business rules
    QSqlQuery q;

    // activites
    if (!q.exec(
            "CREATE TABLE IF NOT EXISTS activites ("
            "  id_activite   INTEGER PRIMARY KEY AUTOINCREMENT,"
            "  nom           TEXT NOT NULL,"
            "  capacite_max  INTEGER NOT NULL CHECK (capacite_max >= 0)"
            ")"))
    {
        qWarning() << "Create activites failed:" << q.lastError().text();
        return false;
    }

    // abonnes
    if (!q.exec(
            "CREATE TABLE IF NOT EXISTS abonnes ("
            "  id_abonne INTEGER PRIMARY KEY AUTOINCREMENT,"
            "  nom       TEXT NOT NULL"
            ")"))
    {
        qWarning() << "Create abonnes failed:" << q.lastError().text();
        return false;
    }

    // inscriptions
    if (!q.exec(
            "CREATE TABLE IF NOT EXISTS inscriptions ("
            "  id_inscription  INTEGER PRIMARY KEY AUTOINCREMENT,"
            "  id_abonne       INTEGER NOT NULL,"
            "  id_activite     INTEGER NOT NULL,"
            "  date_inscription TEXT NOT NULL,"
            "  statut          TEXT NOT NULL CHECK (statut IN ('En attente','Confirmée','Annulée')),"
            "  paiement        INTEGER NOT NULL CHECK (paiement IN (0,1)),"
            "  prix            REAL NOT NULL CHECK (prix >= 0),"
            "  FOREIGN KEY (id_abonne)  REFERENCES abonnes(id_abonne)   ON UPDATE CASCADE ON DELETE RESTRICT,"
            "  FOREIGN KEY (id_activite) REFERENCES activites(id_activite) ON UPDATE CASCADE ON DELETE RESTRICT,"
            "  UNIQUE (id_abonne, id_activite)"
            ")"))
    {
        qWarning() << "Create inscriptions failed:" << q.lastError().text();
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("Gestion des inscriptions");
    QApplication::setOrganizationName("YourOrg");

    // Init DB (SQLite file app.db in working directory)
    if (!Database::init("QSQLITE", "default", "app.db")) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur DB"),
                              QObject::tr("Impossible d'initialiser la base de données."));
        return 1;
    }

    if (!createSchemaIfNeeded()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur DB"),
                              QObject::tr("Création du schéma impossible. Voir la sortie console."));
        return 1;
    }

    GestionInscriptions w;
    w.setWindowTitle(QObject::tr("Gestion des inscriptions"));
    w.resize(900, 600);
    w.show();

    return a.exec();
}

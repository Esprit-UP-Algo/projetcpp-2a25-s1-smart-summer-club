#include "abonnedao.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

AbonneDAO::AbonneDAO(QObject* parent) : QObject(parent)
{
}

bool AbonneDAO::create(Abonne* abonne)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());

    // Si l'ID est 0, utiliser la séquence Oracle
    if (abonne->id() == 0) {
        query.prepare("INSERT INTO ABONNE (NOM, PRENOM, DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL, DATE_INSCRIPTION) "
                      "VALUES (:nom, :prenom, :date_naissance, :adresse, :telephone, :email, SYSDATE) "
                      "RETURNING ID_ABONNE INTO :id");
    } else {
        query.prepare("INSERT INTO ABONNE (ID_ABONNE, NOM, PRENOM, DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL, DATE_INSCRIPTION) "
                      "VALUES (:id, :nom, :prenom, :date_naissance, :adresse, :telephone, :email, SYSDATE)");
        query.bindValue(":id", abonne->id());
    }

    query.bindValue(":nom", abonne->nom());
    query.bindValue(":prenom", abonne->prenom());
    query.bindValue(":date_naissance", abonne->dateNaissance());
    query.bindValue(":adresse", abonne->adresse());
    query.bindValue(":telephone", abonne->telephone());
    query.bindValue(":email", abonne->email());

    if (abonne->id() == 0) {
        query.bindValue(":id", 0, QSql::Out);
    }

    bool success = query.exec();
    if (success && abonne->id() == 0) {
        // Récupérer l'ID généré
        query.next();
        abonne->setId(query.boundValue(":id").toInt());
    }

    if (!success) {
        qDebug() << "Erreur création abonné:" << query.lastError().text();
    }
    return success;
}

Abonne* AbonneDAO::read(int id)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT ID_ABONNE, NOM, PRENOM, DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL, DATE_INSCRIPTION "
                  "FROM ABONNE WHERE ID_ABONNE = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return abonneFromQuery(query);
    }
    return nullptr;
}

QList<Abonne*> AbonneDAO::readAll()
{
    QList<Abonne*> abonnes;
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT ID_ABONNE, NOM, PRENOM, DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL, DATE_INSCRIPTION "
                  "FROM ABONNE ORDER BY NOM, PRENOM");

    if (query.exec()) {
        while (query.next()) {
            abonnes.append(abonneFromQuery(query));
        }
    }
    return abonnes;
}

bool AbonneDAO::update(Abonne* abonne)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("UPDATE ABONNE SET "
                  "NOM = :nom, "
                  "PRENOM = :prenom, "
                  "DATE_NAISSANCE = :date_naissance, "
                  "ADRESSE = :adresse, "
                  "TELEPHONE = :telephone, "
                  "EMAIL = :email "
                  "WHERE ID_ABONNE = :id");

    query.bindValue(":id", abonne->id());
    query.bindValue(":nom", abonne->nom());
    query.bindValue(":prenom", abonne->prenom());
    query.bindValue(":date_naissance", abonne->dateNaissance());
    query.bindValue(":adresse", abonne->adresse());
    query.bindValue(":telephone", abonne->telephone());
    query.bindValue(":email", abonne->email());

    bool success = query.exec();
    if (!success) {
        qDebug() << "Erreur mise à jour abonné:" << query.lastError().text();
    }
    return success;
}

bool AbonneDAO::remove(int id)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("DELETE FROM ABONNE WHERE ID_ABONNE = :id");
    query.bindValue(":id", id);

    bool success = query.exec();
    if (!success) {
        qDebug() << "Erreur suppression abonné:" << query.lastError().text();
    }
    return success;
}

QList<Abonne*> AbonneDAO::searchByNom(const QString& nom)
{
    QList<Abonne*> abonnes;
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT ID_ABONNE, NOM, PRENOM, DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL, DATE_INSCRIPTION "
                  "FROM ABONNE WHERE UPPER(NOM) LIKE UPPER(:nom) ORDER BY NOM, PRENOM");
    query.bindValue(":nom", "%" + nom + "%");

    if (query.exec()) {
        while (query.next()) {
            abonnes.append(abonneFromQuery(query));
        }
    }
    return abonnes;
}

QList<Abonne*> AbonneDAO::searchByPrenom(const QString& prenom)
{
    QList<Abonne*> abonnes;
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT ID_ABONNE, NOM, PRENOM, DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL, DATE_INSCRIPTION "
                  "FROM ABONNE WHERE UPPER(PRENOM) LIKE UPPER(:prenom) ORDER BY NOM, PRENOM");
    query.bindValue(":prenom", "%" + prenom + "%");

    if (query.exec()) {
        while (query.next()) {
            abonnes.append(abonneFromQuery(query));
        }
    }
    return abonnes;
}

QList<Abonne*> AbonneDAO::searchByNomComplet(const QString& nomComplet)
{
    QList<Abonne*> abonnes;
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT ID_ABONNE, NOM, PRENOM, DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL, DATE_INSCRIPTION "
                  "FROM ABONNE "
                  "WHERE UPPER(NOM || ' ' || PRENOM) LIKE UPPER(:nomComplet) "
                  "OR UPPER(PRENOM || ' ' || NOM) LIKE UPPER(:nomComplet) "
                  "ORDER BY NOM, PRENOM");
    query.bindValue(":nomComplet", "%" + nomComplet + "%");

    if (query.exec()) {
        while (query.next()) {
            abonnes.append(abonneFromQuery(query));
        }
    }
    return abonnes;
}

QList<Abonne*> AbonneDAO::searchByTelephone(const QString& telephone)
{
    QList<Abonne*> abonnes;
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT ID_ABONNE, NOM, PRENOM, DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL, DATE_INSCRIPTION "
                  "FROM ABONNE WHERE TELEPHONE LIKE :telephone ORDER BY NOM, PRENOM");
    query.bindValue(":telephone", "%" + telephone + "%");

    if (query.exec()) {
        while (query.next()) {
            abonnes.append(abonneFromQuery(query));
        }
    }
    return abonnes;
}

int AbonneDAO::count()
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT COUNT(*) FROM ABONNE");

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

QMap<QString, int> AbonneDAO::countByTrancheAge()
{
    QMap<QString, int> tranches;

    QSqlQuery query(DatabaseManager::getInstance().getDatabase());

    // Requête pour Oracle pour calculer les tranches d'âge
    query.prepare(
        "SELECT "
        "'< 10 ans' as tranche, "
        "COUNT(CASE WHEN TRUNC(MONTHS_BETWEEN(SYSDATE, DATE_NAISSANCE)/12) < 10 THEN 1 END) as count "
        "FROM ABONNE "
        "UNION ALL "
        "SELECT "
        "'10-19 ans', "
        "COUNT(CASE WHEN TRUNC(MONTHS_BETWEEN(SYSDATE, DATE_NAISSANCE)/12) BETWEEN 10 AND 19 THEN 1 END) "
        "FROM ABONNE "
        "UNION ALL "
        "SELECT "
        "'20-29 ans', "
        "COUNT(CASE WHEN TRUNC(MONTHS_BETWEEN(SYSDATE, DATE_NAISSANCE)/12) BETWEEN 20 AND 29 THEN 1 END) "
        "FROM ABONNE "
        "UNION ALL "
        "SELECT "
        "'30-39 ans', "
        "COUNT(CASE WHEN TRUNC(MONTHS_BETWEEN(SYSDATE, DATE_NAISSANCE)/12) BETWEEN 30 AND 39 THEN 1 END) "
        "FROM ABONNE "
        "UNION ALL "
        "SELECT "
        "'40+ ans', "
        "COUNT(CASE WHEN TRUNC(MONTHS_BETWEEN(SYSDATE, DATE_NAISSANCE)/12) >= 40 THEN 1 END) "
        "FROM ABONNE"
        );

    if (query.exec()) {
        while (query.next()) {
            tranches[query.value(0).toString()] = query.value(1).toInt();
        }
    } else {
        qDebug() << "Erreur statistiques tranches d'âge:" << query.lastError().text();
    }

    return tranches;
}

Abonne* AbonneDAO::abonneFromQuery(const QSqlQuery& query)
{
    Abonne* abonne = new Abonne(
        query.value("ID_ABONNE").toInt(),
        query.value("NOM").toString(),
        query.value("PRENOM").toString(),
        query.value("DATE_NAISSANCE").toDate(),
        query.value("ADRESSE").toString(),
        query.value("TELEPHONE").toString(),
        query.value("EMAIL").toString(),
        query.value("DATE_INSCRIPTION").toDate()
        );

    return abonne;
}

#include "activitedao.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

ActiviteDAO::ActiviteDAO(QObject* parent) : QObject(parent)
{
}

bool ActiviteDAO::create(Activite* activite)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());

    if (activite->id() == 0) {
        query.prepare("INSERT INTO ACTIVITE (NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX) "
                      "VALUES (:nom, :description, :duree, :lieu, :max) "
                      "RETURNING ID_ACTIVITE INTO :id");
    } else {
        query.prepare("INSERT INTO ACTIVITE (ID_ACTIVITE, NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX) "
                      "VALUES (:id, :nom, :description, :duree, :lieu, :max)");
        query.bindValue(":id", activite->id());
    }

    query.bindValue(":nom", activite->nom());
    query.bindValue(":description", activite->description());
    query.bindValue(":duree", activite->dureeSeance());
    query.bindValue(":lieu", activite->lieu());
    query.bindValue(":max", activite->nbParticipantsMax());

    if (activite->id() == 0) {
        query.bindValue(":id", 0, QSql::Out);
    }

    bool success = query.exec();
    if (success && activite->id() == 0) {
        query.next();
        activite->setId(query.boundValue(":id").toInt());
    }

    if (!success) {
        qDebug() << "Erreur création activité:" << query.lastError().text();
    }
    return success;
}

Activite* ActiviteDAO::read(int id)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT ID_ACTIVITE, NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX "
                  "FROM ACTIVITE WHERE ID_ACTIVITE = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return activiteFromQuery(query);
    }
    return nullptr;
}

QList<Activite*> ActiviteDAO::readAll()
{
    QList<Activite*> activites;
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT ID_ACTIVITE, NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX "
                  "FROM ACTIVITE ORDER BY NOM");

    if (query.exec()) {
        while (query.next()) {
            activites.append(activiteFromQuery(query));
        }
    }
    return activites;
}

bool ActiviteDAO::update(Activite* activite)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("UPDATE ACTIVITE SET "
                  "NOM = :nom, "
                  "DESCRIPTION = :description, "
                  "DUREE_SEANCE = :duree, "
                  "LIEU = :lieu, "
                  "NB_PARTICIPANTS_MAX = :max "
                  "WHERE ID_ACTIVITE = :id");

    query.bindValue(":id", activite->id());
    query.bindValue(":nom", activite->nom());
    query.bindValue(":description", activite->description());
    query.bindValue(":duree", activite->dureeSeance());
    query.bindValue(":lieu", activite->lieu());
    query.bindValue(":max", activite->nbParticipantsMax());

    bool success = query.exec();
    if (!success) {
        qDebug() << "Erreur mise à jour activité:" << query.lastError().text();
    }
    return success;
}

bool ActiviteDAO::remove(int id)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("DELETE FROM ACTIVITE WHERE ID_ACTIVITE = :id");
    query.bindValue(":id", id);

    bool success = query.exec();
    if (!success) {
        qDebug() << "Erreur suppression activité:" << query.lastError().text();
    }
    return success;
}

QList<Activite*> ActiviteDAO::searchByNom(const QString& nom)
{
    QList<Activite*> activites;
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT ID_ACTIVITE, NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX "
                  "FROM ACTIVITE WHERE UPPER(NOM) LIKE UPPER(:nom) ORDER BY NOM");
    query.bindValue(":nom", "%" + nom + "%");

    if (query.exec()) {
        while (query.next()) {
            activites.append(activiteFromQuery(query));
        }
    }
    return activites;
}

QList<Activite*> ActiviteDAO::searchByLieu(const QString& lieu)
{
    QList<Activite*> activites;
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT ID_ACTIVITE, NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX "
                  "FROM ACTIVITE WHERE UPPER(LIEU) LIKE UPPER(:lieu) ORDER BY NOM");
    query.bindValue(":lieu", "%" + lieu + "%");

    if (query.exec()) {
        while (query.next()) {
            activites.append(activiteFromQuery(query));
        }
    }
    return activites;
}

int ActiviteDAO::count()
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT COUNT(*) FROM ACTIVITE");

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int ActiviteDAO::countParticipants(int idActivite)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT COUNT(*) FROM INSCRIPTION WHERE ID_ACTIVITE = :id AND STATUT = 'Confirmé'");
    query.bindValue(":id", idActivite);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

bool ActiviteDAO::isFull(int idActivite)
{
    Activite* activite = read(idActivite);
    if (!activite) return false;

    int participants = countParticipants(idActivite);
    bool isFull = participants >= activite->nbParticipantsMax();

    delete activite;
    return isFull;
}

Activite* ActiviteDAO::activiteFromQuery(const QSqlQuery& query)
{
    Activite* activite = new Activite(
        query.value("ID_ACTIVITE").toInt(),
        query.value("NOM").toString(),
        query.value("DESCRIPTION").toString(),
        query.value("DUREE_SEANCE").toInt(),
        query.value("LIEU").toString(),
        query.value("NB_PARTICIPANTS_MAX").toInt()
        );

    return activite;
}

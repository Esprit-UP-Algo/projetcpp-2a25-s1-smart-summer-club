#include "inscriptiondao.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

InscriptionDAO::InscriptionDAO(QObject* parent) : QObject(parent)
{
}

bool InscriptionDAO::create(Inscription* inscription)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("INSERT INTO INSCRIPTION (ID_ABONNE, ID_ACTIVITE, "
                  "DATE_INSCRIPTION, STATUT, PAIEMENT_EFFECTUE, PRIX) "
                  "VALUES (:id_abonne, :id_activite, :date_inscription, "
                  ":statut, :paiement, :prix)");

    query.bindValue(":id_abonne", inscription->idAbonne());
    query.bindValue(":id_activite", inscription->idActivite());
    query.bindValue(":date_inscription", inscription->dateInscription());
    query.bindValue(":statut", inscription->statut());
    query.bindValue(":paiement", inscription->paiementEffectue() ? 1 : 0);
    query.bindValue(":prix", inscription->prix());

    bool success = query.exec();
    if (!success) {
        qDebug() << "Error creating inscription:" << query.lastError().text();
    }
    return success;
}

Inscription* InscriptionDAO::read(int id)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT * FROM INSCRIPTION WHERE ID_INSCRIPTION = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return inscriptionFromQuery(query);
    }
    return nullptr;
}

QList<Inscription*> InscriptionDAO::readAll()
{
    QList<Inscription*> inscriptions;
    QSqlQuery query("SELECT * FROM INSCRIPTION ORDER BY DATE_INSCRIPTION DESC",
                    DatabaseManager::getInstance().getDatabase());

    while (query.next()) {
        inscriptions.append(inscriptionFromQuery(query));
    }
    return inscriptions;
}

bool InscriptionDAO::update(Inscription* inscription)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("UPDATE INSCRIPTION SET ID_ABONNE = :id_abonne, "
                  "ID_ACTIVITE = :id_activite, DATE_INSCRIPTION = :date_inscription, "
                  "STATUT = :statut, PAIEMENT_EFFECTUE = :paiement, PRIX = :prix "
                  "WHERE ID_INSCRIPTION = :id");

    query.bindValue(":id", inscription->id());
    query.bindValue(":id_abonne", inscription->idAbonne());
    query.bindValue(":id_activite", inscription->idActivite());
    query.bindValue(":date_inscription", inscription->dateInscription());
    query.bindValue(":statut", inscription->statut());
    query.bindValue(":paiement", inscription->paiementEffectue() ? "Y" : "N");
    query.bindValue(":prix", inscription->prix());

    return query.exec();
}

bool InscriptionDAO::remove(int id)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("DELETE FROM INSCRIPTION WHERE ID_INSCRIPTION = :id");
    query.bindValue(":id", id);

    return query.exec();
}

QList<Inscription*> InscriptionDAO::searchByAbonne(int idAbonne)
{
    QList<Inscription*> inscriptions;
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT i.* FROM INSCRIPTION i "
                  "JOIN ABONNE a ON i.ID_ABONNE = a.ID_ABONNE "
                  "WHERE i.ID_ABONNE = :id_abonne "
                  "ORDER BY i.DATE_INSCRIPTION DESC");
    query.bindValue(":id_abonne", idAbonne);

    if (query.exec()) {
        while (query.next()) {
            inscriptions.append(inscriptionFromQuery(query));
        }
    }
    return inscriptions;
}

QList<Inscription*> InscriptionDAO::searchByActivite(int idActivite)
{
    QList<Inscription*> inscriptions;
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT i.* FROM INSCRIPTION i "
                  "JOIN ACTIVITE act ON i.ID_ACTIVITE = act.ID_ACTIVITE "
                  "WHERE i.ID_ACTIVITE = :id_activite "
                  "ORDER BY i.DATE_INSCRIPTION DESC");
    query.bindValue(":id_activite", idActivite);

    if (query.exec()) {
        while (query.next()) {
            inscriptions.append(inscriptionFromQuery(query));
        }
    }
    return inscriptions;
}

QList<Inscription*> InscriptionDAO::searchByDate(const QDate& date)
{
    QList<Inscription*> inscriptions;
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT * FROM INSCRIPTION WHERE TRUNC(DATE_INSCRIPTION) = :date "
                  "ORDER BY DATE_INSCRIPTION DESC");
    query.bindValue(":date", date);

    if (query.exec()) {
        while (query.next()) {
            inscriptions.append(inscriptionFromQuery(query));
        }
    }
    return inscriptions;
}

QList<Inscription*> InscriptionDAO::searchByStatut(const QString& statut)
{
    QList<Inscription*> inscriptions;
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT * FROM INSCRIPTION WHERE STATUT = :statut "
                  "ORDER BY DATE_INSCRIPTION DESC");
    query.bindValue(":statut", statut);

    if (query.exec()) {
        while (query.next()) {
            inscriptions.append(inscriptionFromQuery(query));
        }
    }
    return inscriptions;
}

QList<Inscription*> InscriptionDAO::searchByNomAbonne(const QString& nom)
{
    QList<Inscription*> inscriptions;
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT i.* FROM INSCRIPTION i "
                  "JOIN ABONNE a ON i.ID_ABONNE = a.ID_ABONNE "
                  "WHERE UPPER(a.NOM || ' ' || a.PRENOM) LIKE UPPER(:nom) "
                  "OR UPPER(a.PRENOM || ' ' || a.NOM) LIKE UPPER(:nom) "
                  "ORDER BY i.DATE_INSCRIPTION DESC");
    query.bindValue(":nom", "%" + nom + "%");

    if (query.exec()) {
        while (query.next()) {
            inscriptions.append(inscriptionFromQuery(query));
        }
    }
    return inscriptions;
}

bool InscriptionDAO::validateInscription(int idInscription)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("UPDATE INSCRIPTION SET STATUT = 'Confirmé' WHERE ID_INSCRIPTION = :id");
    query.bindValue(":id", idInscription);

    return query.exec();
}

bool InscriptionDAO::cancelInscription(int idInscription)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("UPDATE INSCRIPTION SET STATUT = 'Annulé' WHERE ID_INSCRIPTION = :id");
    query.bindValue(":id", idInscription);

    return query.exec();
}

bool InscriptionDAO::markAsPaid(int idInscription)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("UPDATE INSCRIPTION SET PAIEMENT_EFFECTUE = 'Y' WHERE ID_INSCRIPTION = :id");
    query.bindValue(":id", idInscription);

    return query.exec();
}

int InscriptionDAO::count()
{
    QSqlQuery query("SELECT COUNT(*) FROM INSCRIPTION", DatabaseManager::getInstance().getDatabase());
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int InscriptionDAO::countByStatut(const QString& statut)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT COUNT(*) FROM INSCRIPTION WHERE STATUT = :statut");
    query.bindValue(":statut", statut);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

double InscriptionDAO::totalRevenue()
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT SUM(PRIX) FROM INSCRIPTION WHERE PAIEMENT_EFFECTUE = 'Y'");

    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}

double InscriptionDAO::revenueByDateRange(const QDate& start, const QDate& end)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT SUM(PRIX) FROM INSCRIPTION "
                  "WHERE PAIEMENT_EFFECTUE = 'Y' "
                  "AND TRUNC(DATE_INSCRIPTION) BETWEEN :start AND :end");

    query.bindValue(":start", start);
    query.bindValue(":end", end);

    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}

QMap<QString, int> InscriptionDAO::countByActivite()
{
    QMap<QString, int> counts;
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());
    query.prepare("SELECT a.NOM, COUNT(i.ID_INSCRIPTION) as count "
                  "FROM ACTIVITE a "
                  "LEFT JOIN INSCRIPTION i ON a.ID_ACTIVITE = i.ID_ACTIVITE "
                  "GROUP BY a.NOM "
                  "ORDER BY count DESC");

    if (query.exec()) {
        while (query.next()) {
            counts[query.value("NOM").toString()] = query.value("count").toInt();
        }
    }
    return counts;
}

QMap<QString, int> InscriptionDAO::countByStatutDistribution()
{
    QMap<QString, int> distribution;

    distribution["En attente"] = countByStatut("En attente");
    distribution["Confirmé"] = countByStatut("Confirmé");
    distribution["Annulé"] = countByStatut("Annulé");

    return distribution;
}

int InscriptionDAO::getTotalInscriptions()
{
    return count();
}

double InscriptionDAO::getGrowthRate(const QDate& start, const QDate& end)
{
    QSqlQuery query(DatabaseManager::getInstance().getDatabase());

    // Count previous period
    QDate prevStart = start.addDays(-(end.daysTo(start) + 1));
    QDate prevEnd = start.addDays(-1);

    query.prepare("SELECT COUNT(*) FROM INSCRIPTION "
                  "WHERE TRUNC(DATE_INSCRIPTION) BETWEEN :start AND :end");
    query.bindValue(":start", prevStart);
    query.bindValue(":end", prevEnd);

    int previousCount = 0;
    if (query.exec() && query.next()) {
        previousCount = query.value(0).toInt();
    }

    // Count current period
    query.prepare("SELECT COUNT(*) FROM INSCRIPTION "
                  "WHERE TRUNC(DATE_INSCRIPTION) BETWEEN :start AND :end");
    query.bindValue(":start", start);
    query.bindValue(":end", end);

    int currentCount = 0;
    if (query.exec() && query.next()) {
        currentCount = query.value(0).toInt();
    }

    if (previousCount == 0) return 0.0;
    return ((currentCount - previousCount) / (double)previousCount) * 100.0;
}

double InscriptionDAO::getConversionRate()
{
    int total = count();
    int confirmed = countByStatut("Confirmé");

    if (total == 0) return 0.0;
    return (confirmed / (double)total) * 100.0;
}

Inscription* InscriptionDAO::inscriptionFromQuery(const QSqlQuery& query)
{
    return new Inscription(
        query.value("ID_INSCRIPTION").toInt(),
        query.value("ID_ABONNE").toInt(),
        query.value("ID_ACTIVITE").toInt(),
        query.value("DATE_INSCRIPTION").toDate(),
        query.value("STATUT").toString(),
        query.value("PAIEMENT_EFFECTUE").toString() == "Y",
        query.value("PRIX").toDouble()
        );
}

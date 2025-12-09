#include "activite.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>

static QSqlDatabase db()
{
    return QSqlDatabase::database(); // ✅ DEFAULT CONNECTION ONLY
}

Activite::Activite()
{
    id = 0;
    duree_seance = 0;
    nb_participants_max = 0;
}

/* ================= GETTERS ================= */

int Activite::getId() const { return id; }
QString Activite::getNom() const { return nom; }
QString Activite::getDescription() const { return description; }
int Activite::getDureeSeance() const { return duree_seance; }
QString Activite::getLieu() const { return lieu; }
int Activite::getNbParticipantsMax() const { return nb_participants_max; }
QString Activite::getResponsableClub() const { return responsable_club; }

/* ================= SETTERS ================= */

void Activite::setId(int v) { id = v; }
void Activite::setNom(const QString &v) { nom = v; }
void Activite::setDescription(const QString &v) { description = v; }
void Activite::setDureeSeance(int v) { duree_seance = v; }
void Activite::setLieu(const QString &v) { lieu = v; }
void Activite::setNbParticipantsMax(int v) { nb_participants_max = v; }
void Activite::setResponsableClub(const QString &v) { responsable_club = v; }

/* ================= ADD ================= */

bool Activite::ajouter()
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.isOpen()) return false;

    database.transaction();   // ✅ START TRANSACTION

    QSqlQuery query(database);
    query.prepare(
        "INSERT INTO ACTIVITE (ID, NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX, RESPONSABLE_CLUB) "
        "VALUES (?, ?, ?, ?, ?, ?, ?)");

    query.addBindValue(id);
    query.addBindValue(nom);
    query.addBindValue(description);
    query.addBindValue(duree_seance);
    query.addBindValue(lieu);
    query.addBindValue(nb_participants_max);
    query.addBindValue(responsable_club);

    if (!query.exec()) {
        qCritical() << "ADD ERROR:" << query.lastError().text();
        database.rollback();
        return false;
    }

    database.commit();
    return true;
}


/* ================= UPDATE ================= */

bool Activite::mettreAJour(int id)
{
    if (!db().isOpen()) return false;

    QSqlQuery query;
    query.prepare(
        "UPDATE ACTIVITE SET "
        "NOM=:nom, DESCRIPTION=:desc, DUREE_SEANCE=:duree, "
        "LIEU=:lieu, NB_PARTICIPANTS_MAX=:nb, RESPONSABLE_CLUB=:resp "
        "WHERE ID=:id");

    query.bindValue(":nom", nom);
    query.bindValue(":desc", description);
    query.bindValue(":duree", duree_seance);
    query.bindValue(":lieu", lieu);
    query.bindValue(":nb", nb_participants_max);
    query.bindValue(":resp", responsable_club);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qCritical() << "UPDATE ERROR:" << query.lastError().text();
        return false;
    }

    return true;
}

/* ================= DELETE ================= */

bool Activite::supprimer(int id)
{
    if (!db().isOpen()) return false;

    QSqlQuery query;
    query.prepare("DELETE FROM ACTIVITE WHERE ID=:id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qCritical() << "DELETE ERROR:" << query.lastError().text();
        return false;
    }

    return true;
}

/* ================= EXISTS ================= */

bool Activite::exists(int id) const
{
    if (!db().isOpen()) return false;

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM ACTIVITE WHERE ID=:id");
    query.bindValue(":id", id);
    query.exec();

    if (query.next())
        return query.value(0).toInt() > 0;

    return false;
}

/* ================= DISPLAY ================= */

QSqlQueryModel* Activite::afficher() const
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ACTIVITE ORDER BY ID ASC", db());
    return model;
}

/* ================= SEARCH ================= */

QSqlQueryModel* Activite::rechercher(const QString &terme) const
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare(
        "SELECT * FROM ACTIVITE WHERE "
        "NOM LIKE :t OR LIEU LIKE :t OR RESPONSABLE_CLUB LIKE :t");

    query.bindValue(":t", "%" + terme + "%");
    query.exec();
    model->setQuery(query);

    return model;
}

/* ================= SORT ================= */

QSqlQueryModel* Activite::trier(const QString &champ, Qt::SortOrder ordre) const
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QString order = ordre == Qt::AscendingOrder ? "ASC" : "DESC";
    QString sql = "SELECT * FROM ACTIVITE ORDER BY " + champ + " " + order;

    model->setQuery(sql, db());
    return model;
}

/* ================= STATS ================= */

QSqlQueryModel* Activite::statistiquesParLieu() const
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(
        "SELECT LIEU, COUNT(*) FROM ACTIVITE GROUP BY LIEU", db());
    return model;
}

QSqlQueryModel* Activite::statistiquesParResponsable() const
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(
        "SELECT RESPONSABLE_CLUB, COUNT(*) FROM ACTIVITE GROUP BY RESPONSABLE_CLUB",
        db());
    return model;
}

int Activite::statistiques() const
{
    if (!db().isOpen()) return 0;

    QSqlQuery query("SELECT COUNT(*) FROM ACTIVITE", db());
    if (query.next())
        return query.value(0).toInt();

    return 0;
}

#include "inscription.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlQueryModel>
#include <QDate>
#include <QDebug>

Inscription::Inscription()
    : id_inscription(0),
    id_abonne(0),
    id_activite(0),
    date_inscription(QDate::currentDate().toString("yyyy-MM-dd")),
    statut("En attente"),
    paiement(false),
    prix(0.0)
{
}

Inscription::Inscription(int id_inscription,
                         int id_abonne,
                         int id_activite,
                         const QString& date_inscription,
                         const QString& statut,
                         bool paiement,
                         double prix)
    : id_inscription(id_inscription),
    id_abonne(id_abonne),
    id_activite(id_activite),
    date_inscription(date_inscription),
    statut(statut),
    paiement(paiement),
    prix(prix)
{
}

// Getters
int Inscription::getIdInscription() const { return id_inscription; }
int Inscription::getIdAbonne() const { return id_abonne; }
int Inscription::getIdActivite() const { return id_activite; }
QString Inscription::getDateInscription() const { return date_inscription; }
QString Inscription::getStatut() const { return statut; }
bool Inscription::getPaiement() const { return paiement; }
double Inscription::getPrix() const { return prix; }

// Setters
void Inscription::setIdInscription(int v) { id_inscription = v; }
void Inscription::setIdAbonne(int v) { id_abonne = v; }
void Inscription::setIdActivite(int v) { id_activite = v; }
void Inscription::setDateInscription(const QString& v) { date_inscription = v; }
void Inscription::setStatut(const QString& v) { statut = v; }
void Inscription::setPaiement(bool v) { paiement = v; }
void Inscription::setPrix(double v) { prix = v; }

// Validation
bool Inscription::validerChamps() const
{
    if (id_abonne <= 0 || id_activite <= 0) return false;

    // Date format yyyy-MM-dd
    const QDate d = QDate::fromString(date_inscription, "yyyy-MM-dd");
    if (!d.isValid()) return false;

    const QString s = statut.trimmed();
    if (!(s == "En attente" || s == "Confirmée" || s == "Annulée")) return false;

    if (prix < 0.0) return false;

    // Règle simple: si statut = Annulée alors paiement doit être false
    if (s == "Annulée" && paiement) return false;

    return true;
}

// Métiers/utilitaires
bool Inscription::existeDoublon(int idAbonne, int idActivite, int saufId) const
{
    QSqlQuery q;
    if (saufId > 0) {
        q.prepare("SELECT COUNT(*) FROM inscriptions "
                  "WHERE id_abonne = :a AND id_activite = :c AND id_inscription <> :id");
        q.bindValue(":id", saufId);
    } else {
        q.prepare("SELECT COUNT(*) FROM inscriptions "
                  "WHERE id_abonne = :a AND id_activite = :c");
    }
    q.bindValue(":a", idAbonne);
    q.bindValue(":c", idActivite);

    if (!q.exec()) {
        qWarning() << "existeDoublon failed:" << q.lastError().text();
        return false; // fail-safe: treat as no-duplicate to not block unexpectedly
    }
    if (q.next()) {
        return q.value(0).toInt() > 0;
    }
    return false;
}

int Inscription::placesRestantesPourActivite(int idActivite) const
{
    // Nécessite activites(id_activite, capacite_max)
    QSqlQuery q;
    q.prepare(
        "SELECT a.capacite_max - COUNT(i.id_inscription) AS places_restantes "
        "FROM activites a "
        "LEFT JOIN inscriptions i ON i.id_activite = a.id_activite AND i.statut <> 'Annulée' "
        "WHERE a.id_activite = :c "
        "GROUP BY a.id_activite");
    q.bindValue(":c", idActivite);

    if (!q.exec()) {
        qWarning() << "placesRestantesPourActivite failed:" << q.lastError().text();
        return 0;
    }
    if (q.next()) {
        return q.value(0).toInt();
    }
    // Si l'activité n'existe pas, 0 pour bloquer
    return 0;
}

double Inscription::calculerPrixFinal(int /*idAbonne*/, int /*idActivite*/, double prixBase) const
{
    // Exemple simple: pas de remises. Branchez vos règles ici (étudiant, promo, etc.)
    return prixBase;
}

// CRUD
bool Inscription::ajouter() const
{
    if (!validerChamps()) return false;

    // Règles métiers
    if (existeDoublon(id_abonne, id_activite)) {
        qWarning() << "ajouter refusé: doublon abonne/activite";
        return false;
    }
    if (statut != "Annulée" && placesRestantesPourActivite(id_activite) <= 0) {
        qWarning() << "ajouter refusé: activité pleine";
        return false;
    }

    const double prixFinal = calculerPrixFinal(id_abonne, id_activite, prix);

    QSqlQuery query;
    // Si id_inscription est AUTO_INCREMENT/AUTOINCREMENT, omettre la colonne
    query.prepare(
        "INSERT INTO inscriptions "
        "(id_abonne, id_activite, date_inscription, statut, paiement, prix) "
        "VALUES (:id_abonne, :id_activite, :date_inscription, :statut, :paiement, :prix)");

    query.bindValue(":id_abonne", id_abonne);
    query.bindValue(":id_activite", id_activite);
    query.bindValue(":date_inscription", date_inscription);
    query.bindValue(":statut", statut);
    query.bindValue(":paiement", paiement);
    query.bindValue(":prix", prixFinal);

    const bool ok = query.exec();
    if (!ok) {
        qWarning() << "Inscription::ajouter() failed:" << query.lastError().text();
    }
    return ok;
}

bool Inscription::modifier() const
{
    if (id_inscription <= 0) return false;
    if (!validerChamps()) return false;

    // Règles métiers
    if (existeDoublon(id_abonne, id_activite, id_inscription)) {
        qWarning() << "modifier refusé: doublon abonne/activite";
        return false;
    }
    if (statut != "Annulée" && placesRestantesPourActivite(id_activite) <= 0) {
        // Autoriser si on reste sur la même activité et que l'inscription existe
        // Ici on applique une règle stricte: bloquer si aucune place
        qWarning() << "modifier refusé: activité pleine";
        return false;
    }

    const double prixFinal = calculerPrixFinal(id_abonne, id_activite, prix);

    QSqlQuery query;
    query.prepare(
        "UPDATE inscriptions SET "
        "id_abonne = :id_abonne, "
        "id_activite = :id_activite, "
        "date_inscription = :date_inscription, "
        "statut = :statut, "
        "paiement = :paiement, "
        "prix = :prix "
        "WHERE id_inscription = :id_inscription");

    query.bindValue(":id_abonne", id_abonne);
    query.bindValue(":id_activite", id_activite);
    query.bindValue(":date_inscription", date_inscription);
    query.bindValue(":statut", statut);
    query.bindValue(":paiement", paiement);
    query.bindValue(":prix", prixFinal);
    query.bindValue(":id_inscription", id_inscription);

    const bool ok = query.exec();
    if (!ok) {
        qWarning() << "Inscription::modifier() failed:" << query.lastError().text();
        return false;
    }
    return query.numRowsAffected() > 0;
}

bool Inscription::supprimer(int id) const
{
    if (id <= 0) return false;

    QSqlQuery query;
    query.prepare("DELETE FROM inscriptions WHERE id_inscription = :id");
    query.bindValue(":id", id);

    const bool ok = query.exec();
    if (!ok) {
        qWarning() << "Inscription::supprimer() failed:" << query.lastError().text();
        return false;
    }
    return query.numRowsAffected() > 0;
}

QSqlQueryModel* Inscription::afficher() const
{
    auto* model = new QSqlQueryModel();
    model->setQuery(
        "SELECT id_inscription, id_abonne, id_activite, date_inscription, statut, paiement, prix "
        "FROM inscriptions "
        "ORDER BY id_inscription DESC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Abonné"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Activité"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Payé"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Prix"));

    return model; // ownership transferé à l'appelant
}

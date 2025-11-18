#include "inscription.h"
#include "databasemanager.h"

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
    statut("en attente"),
    paiement_effectue(false),
    prix(0.0)
{
}

Inscription::Inscription(int id_inscription,
                         int id_abonne,
                         int id_activite,
                         const QString& date_inscription,
                         const QString& statut,
                         bool paiement_effectue,
                         double prix)
    : id_inscription(id_inscription),
    id_abonne(id_abonne),
    id_activite(id_activite),
    date_inscription(date_inscription),
    statut(statut),
    paiement_effectue(paiement_effectue),
    prix(prix)
{
}

// Getters
int Inscription::getIdInscription() const { return id_inscription; }
int Inscription::getIdAbonne() const { return id_abonne; }
int Inscription::getIdActivite() const { return id_activite; }
QString Inscription::getDateInscription() const { return date_inscription; }
QString Inscription::getStatut() const { return statut; }
bool Inscription::getPaiementEffectue() const { return paiement_effectue; }
double Inscription::getPrix() const { return prix; }

// Setters
void Inscription::setIdInscription(int v) { id_inscription = v; }
void Inscription::setIdAbonne(int v) { id_abonne = v; }
void Inscription::setIdActivite(int v) { id_activite = v; }
void Inscription::setDateInscription(const QString& v) { date_inscription = v; }
void Inscription::setStatut(const QString& v) { statut = v; }
void Inscription::setPaiementEffectue(bool v) { paiement_effectue = v; }
void Inscription::setPrix(double v) { prix = v; }

// Validation
bool Inscription::validerChamps() const
{
    if (id_abonne <= 0 || id_activite <= 0) return false;

    // Date format yyyy-MM-dd
    const QDate d = QDate::fromString(date_inscription, "yyyy-MM-dd");
    if (!d.isValid()) return false;

    const QString s = statut.trimmed().toLower();
    if (!(s == "en attente" || s == "confirmé" || s == "annulée")) return false;

    if (prix < 0.0) return false;

    // Règle simple: si statut = annulée alors paiement doit être false
    if (s == "annulée" && paiement_effectue) return false;

    return true;
}

// Métiers/utilitaires
bool Inscription::existeDoublon(int idAbonne, int idActivite, int saufId) const
{
    QSqlQuery q(DatabaseManager::instance().getDatabase());
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
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare(
        "SELECT a.capacite_max - COUNT(i.id_inscription) AS places_restantes "
        "FROM activites a "
        "LEFT JOIN inscriptions i ON i.id_activite = a.id_activite AND i.statut <> 'annulée' "
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
    if (statut != "annulée" && placesRestantesPourActivite(id_activite) <= 0) {
        qWarning() << "ajouter refusé: activité pleine";
        return false;
    }

    const double prixFinal = calculerPrixFinal(id_abonne, id_activite, prix);

    QSqlQuery query(DatabaseManager::instance().getDatabase());
    
    // Adapter selon le type de base de données
    if (DatabaseManager::instance().getDatabaseType() == DatabaseManager::Oracle) {
        // Pour Oracle, utiliser TO_DATE pour la conversion de date
        query.prepare(
            "INSERT INTO inscriptions "
            "(id_abonne, id_activite, date_inscription, statut, paiement_effectue, prix) "
            "VALUES (:id_abonne, :id_activite, TO_DATE(:date_inscription, 'YYYY-MM-DD'), :statut, :paiement_effectue, :prix)");
    } else {
        // SQLite
        query.prepare(
            "INSERT INTO inscriptions "
            "(id_abonne, id_activite, date_inscription, statut, paiement_effectue, prix) "
            "VALUES (:id_abonne, :id_activite, :date_inscription, :statut, :paiement_effectue, :prix)");
    }

    query.bindValue(":id_abonne", id_abonne);
    query.bindValue(":id_activite", id_activite);
    query.bindValue(":date_inscription", date_inscription);
    query.bindValue(":statut", statut);
    query.bindValue(":paiement_effectue", paiement_effectue ? 1 : 0);
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
    if (statut != "annulée" && placesRestantesPourActivite(id_activite) <= 0) {
        qWarning() << "modifier refusé: activité pleine";
        return false;
    }

    const double prixFinal = calculerPrixFinal(id_abonne, id_activite, prix);

    QSqlQuery query(DatabaseManager::instance().getDatabase());
    
    // Adapter selon le type de base de données
    if (DatabaseManager::instance().getDatabaseType() == DatabaseManager::Oracle) {
        query.prepare(
            "UPDATE inscriptions SET "
            "id_abonne = :id_abonne, "
            "id_activite = :id_activite, "
            "date_inscription = TO_DATE(:date_inscription, 'YYYY-MM-DD'), "
            "statut = :statut, "
            "paiement_effectue = :paiement_effectue, "
            "prix = :prix "
            "WHERE id_inscription = :id_inscription");
    } else {
        query.prepare(
            "UPDATE inscriptions SET "
            "id_abonne = :id_abonne, "
            "id_activite = :id_activite, "
            "date_inscription = :date_inscription, "
            "statut = :statut, "
            "paiement_effectue = :paiement_effectue, "
            "prix = :prix "
            "WHERE id_inscription = :id_inscription");
    }

    query.bindValue(":id_abonne", id_abonne);
    query.bindValue(":id_activite", id_activite);
    query.bindValue(":date_inscription", date_inscription);
    query.bindValue(":statut", statut);
    query.bindValue(":paiement_effectue", paiement_effectue ? 1 : 0);
    query.bindValue(":prix", prixFinal);
    query.bindValue(":id_inscription", id_inscription);

    const bool ok = query.exec();
    if (!ok) {
        qWarning() << "Inscription::modifier() failed:" << query.lastError().text();
        return false;
    }
    return query.numRowsAffected() > 0;
}

bool Inscription::supprimer() const
{
    if (id_inscription <= 0) return false;

    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("DELETE FROM inscriptions WHERE id_inscription = :id");
    query.bindValue(":id", id_inscription);

    const bool ok = query.exec();
    if (!ok) {
        qWarning() << "Inscription::supprimer() failed:" << query.lastError().text();
        return false;
    }
    return query.numRowsAffected() > 0;
}

bool Inscription::sauvegarder() const
{
    if (id_inscription > 0) {
        return modifier();
    } else {
        return ajouter();
    }
}

Inscription* Inscription::charger(int id)
{
    if (id <= 0) return nullptr;

    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("SELECT * FROM inscriptions WHERE id_inscription = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        qWarning() << "Inscription::charger() failed:" << query.lastError().text();
        return nullptr;
    }

    Inscription* inscription = new Inscription();
    inscription->id_inscription = query.value("id_inscription").toInt();
    inscription->id_abonne = query.value("id_abonne").toInt();
    inscription->id_activite = query.value("id_activite").toInt();
    inscription->date_inscription = query.value("date_inscription").toString();
    inscription->statut = query.value("statut").toString();
    inscription->paiement_effectue = query.value("paiement_effectue").toBool();
    inscription->prix = query.value("prix").toDouble();

    return inscription;
}

QSqlQueryModel* Inscription::afficher() const
{
    auto* model = new QSqlQueryModel();
    QSqlDatabase db = DatabaseManager::instance().getDatabase();
    model->setQuery(
        "SELECT id_inscription, id_abonne, id_activite, date_inscription, statut, paiement_effectue, prix "
        "FROM inscriptions "
        "ORDER BY id_inscription DESC", db);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Abonné"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Activité"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Payé"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Prix"));

    return model;
}

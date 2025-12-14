#include "inscription.h"
#include "Activite.h"

Inscription::Inscription(QObject* parent) : QObject(parent), m_id(0),
    m_idAbonne(0), m_idActivite(0), m_paiementEffectue(false), m_prix(0.0)
{
    m_statut = statutToString(EN_ATTENTE);
}

Inscription::Inscription(int id, int idAbonne, int idActivite,
                         const QDate& dateInscription, const QString& statut,
                         bool paiementEffectue, double prix, QObject* parent)
    : QObject(parent), m_id(id), m_idAbonne(idAbonne), m_idActivite(idActivite),
    m_dateInscription(dateInscription), m_statut(statut),
    m_paiementEffectue(paiementEffectue), m_prix(prix)
{
}

int Inscription::id() const { return m_id; }
int Inscription::idAbonne() const { return m_idAbonne; }
int Inscription::idActivite() const { return m_idActivite; }
QDate Inscription::dateInscription() const { return m_dateInscription; }
QString Inscription::statut() const { return m_statut; }
bool Inscription::paiementEffectue() const { return m_paiementEffectue; }
double Inscription::prix() const { return m_prix; }

QString Inscription::statutToString() const
{
    return m_statut;
}

QString Inscription::statutToString(Statut statut)
{
    switch (statut) {
    case EN_ATTENTE: return "En attente";
    case CONFIRME: return "Confirmé";
    case ANNULE: return "Annulé";
    default: return "En attente";
    }
}

Inscription::Statut Inscription::stringToStatut(const QString& statut)
{
    if (statut == "Confirmé") return CONFIRME;
    if (statut == "Annulé") return ANNULE;
    return EN_ATTENTE;
}

void Inscription::setId(int id) { m_id = id; }
void Inscription::setIdAbonne(int id) { m_idAbonne = id; }
void Inscription::setIdActivite(int id) { m_idActivite = id; }
void Inscription::setDateInscription(const QDate& date) { m_dateInscription = date; }
void Inscription::setStatut(const QString& statut) { m_statut = statut; }
void Inscription::setStatut(Statut statut) { m_statut = statutToString(statut); }
void Inscription::setPaiementEffectue(bool effectue) { m_paiementEffectue = effectue; }
void Inscription::setPrix(double prix) { m_prix = prix; }

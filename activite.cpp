#include "Activite.h"

Activite::Activite(QObject* parent) : QObject(parent), m_id(0),
    m_dureeSeance(0), m_nbParticipantsMax(0)
{
}

Activite::Activite(int id, const QString& nom, const QString& description,
                   int dureeSeance, const QString& lieu, int nbParticipantsMax,
                   QObject* parent)
    : QObject(parent), m_id(id), m_nom(nom), m_description(description),
    m_dureeSeance(dureeSeance), m_lieu(lieu), m_nbParticipantsMax(nbParticipantsMax)
{
}

int Activite::id() const { return m_id; }
QString Activite::nom() const { return m_nom; }
QString Activite::description() const { return m_description; }
int Activite::dureeSeance() const { return m_dureeSeance; }
QString Activite::lieu() const { return m_lieu; }
int Activite::nbParticipantsMax() const { return m_nbParticipantsMax; }

void Activite::setId(int id) { m_id = id; }
void Activite::setNom(const QString& nom) { m_nom = nom; }
void Activite::setDescription(const QString& description) { m_description = description; }
void Activite::setDureeSeance(int duree) { m_dureeSeance = duree; }
void Activite::setLieu(const QString& lieu) { m_lieu = lieu; }
void Activite::setNbParticipantsMax(int nb) { m_nbParticipantsMax = nb; }

#include "abonne.h"
#include <QDate>

Abonne::Abonne(QObject* parent) : QObject(parent), m_id(0)
{
}

Abonne::Abonne(int id, const QString& nom, const QString& prenom,
               const QDate& dateNaissance, const QString& adresse,
               const QString& telephone, const QString& email,
               const QDate& dateInscription, QObject* parent)
    : QObject(parent), m_id(id), m_nom(nom), m_prenom(prenom),
    m_dateNaissance(dateNaissance), m_adresse(adresse),
    m_telephone(telephone), m_email(email), m_dateInscription(dateInscription)
{
}

int Abonne::id() const { return m_id; }
QString Abonne::nom() const { return m_nom; }
QString Abonne::prenom() const { return m_prenom; }
QDate Abonne::dateNaissance() const { return m_dateNaissance; }
QString Abonne::adresse() const { return m_adresse; }
QString Abonne::telephone() const { return m_telephone; }
QString Abonne::email() const { return m_email; }
QDate Abonne::dateInscription() const { return m_dateInscription; }

QString Abonne::nomComplet() const
{
    return m_prenom + " " + m_nom;
}

int Abonne::age() const
{
    QDate currentDate = QDate::currentDate();
    int age = currentDate.year() - m_dateNaissance.year();

    if (currentDate.month() < m_dateNaissance.month() ||
        (currentDate.month() == m_dateNaissance.month() &&
         currentDate.day() < m_dateNaissance.day())) {
        age--;
    }

    return age;
}

QString Abonne::toString() const
{
    return QString("%1 %2 (ID: %3, Tél: %4)").arg(prenom(), nom(), QString::number(id()), telephone());
}

void Abonne::setId(int id) { m_id = id; }
void Abonne::setNom(const QString& nom) { m_nom = nom; }
void Abonne::setPrenom(const QString& prenom) { m_prenom = prenom; }
void Abonne::setDateNaissance(const QDate& date) { m_dateNaissance = date; }
void Abonne::setAdresse(const QString& adresse) { m_adresse = adresse; }
void Abonne::setTelephone(const QString& telephone) { m_telephone = telephone; }
void Abonne::setEmail(const QString& email) { m_email = email; }
void Abonne::setDateInscription(const QDate& date) { m_dateInscription = date; }

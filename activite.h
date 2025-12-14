#ifndef ACTIVITE_H
#define ACTIVITE_H

#include <QObject>
#include <QString>

class Activite : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(QString nom READ nom WRITE setNom)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(int dureeSeance READ dureeSeance WRITE setDureeSeance)
    Q_PROPERTY(QString lieu READ lieu WRITE setLieu)
    Q_PROPERTY(int nbParticipantsMax READ nbParticipantsMax WRITE setNbParticipantsMax)

public:
    explicit Activite(QObject* parent = nullptr);
    Activite(int id, const QString& nom, const QString& description,
             int dureeSeance, const QString& lieu, int nbParticipantsMax,
             QObject* parent = nullptr);

    // Getters
    int id() const;
    QString nom() const;
    QString description() const;
    int dureeSeance() const;
    QString lieu() const;
    int nbParticipantsMax() const;

    // Setters
    void setId(int id);
    void setNom(const QString& nom);
    void setDescription(const QString& description);
    void setDureeSeance(int duree);
    void setLieu(const QString& lieu);
    void setNbParticipantsMax(int nb);

private:
    int m_id;
    QString m_nom;
    QString m_description;
    int m_dureeSeance;
    QString m_lieu;
    int m_nbParticipantsMax;
};

#endif // ACTIVITE_H

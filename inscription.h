#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QObject>
#include <QDate>
#include <QString>
#include "abonne.h"
#include "Activite.h"

class Inscription : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(int idAbonne READ idAbonne WRITE setIdAbonne)
    Q_PROPERTY(int idActivite READ idActivite WRITE setIdActivite)
    Q_PROPERTY(QDate dateInscription READ dateInscription WRITE setDateInscription)
    Q_PROPERTY(QString statut READ statut WRITE setStatut)
    Q_PROPERTY(bool paiementEffectue READ paiementEffectue WRITE setPaiementEffectue)
    Q_PROPERTY(double prix READ prix WRITE setPrix)

public:
    enum Statut { EN_ATTENTE, CONFIRME, ANNULE };
    Q_ENUM(Statut)

    explicit Inscription(QObject* parent = nullptr);
    Inscription(int id, int idAbonne, int idActivite, const QDate& dateInscription,
                const QString& statut, bool paiementEffectue, double prix,
                QObject* parent = nullptr);

    // Getters
    int id() const;
    int idAbonne() const;
    int idActivite() const;
    QDate dateInscription() const;
    QString statut() const;
    bool paiementEffectue() const;
    double prix() const;

    QString statutToString() const;
    static QString statutToString(Statut statut);
    static Statut stringToStatut(const QString& statut);

    // Setters
    void setId(int id);
    void setIdAbonne(int id);
    void setIdActivite(int id);
    void setDateInscription(const QDate& date);
    void setStatut(const QString& statut);
    void setStatut(Statut statut);
    void setPaiementEffectue(bool effectue);
    void setPrix(double prix);

private:
    int m_id;
    int m_idAbonne;
    int m_idActivite;
    QDate m_dateInscription;
    QString m_statut;
    bool m_paiementEffectue;
    double m_prix;
};

#endif // INSCRIPTION_H

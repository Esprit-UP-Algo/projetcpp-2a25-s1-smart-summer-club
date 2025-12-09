#ifndef ACTIVITE_H
#define ACTIVITE_H

#include <QString>
#include <QSqlQueryModel>

class Activite
{
public:
    Activite();

    // Getters
    int getId() const;
    QString getNom() const;
    QString getDescription() const;
    int getDureeSeance() const;
    QString getLieu() const;
    int getNbParticipantsMax() const;
    QString getResponsableClub() const;

    // Setters
    void setId(int id);
    void setNom(const QString &nom);
    void setDescription(const QString &description);
    void setDureeSeance(int duree);
    void setLieu(const QString &lieu);
    void setNbParticipantsMax(int nb);
    void setResponsableClub(const QString &resp);

    // CRUD
    bool ajouter();
    bool mettreAJour(int id);
    bool supprimer(int id);
    bool exists(int id) const;

    // Display & Search
    QSqlQueryModel* afficher() const;
    QSqlQueryModel* rechercher(const QString &terme) const;
    QSqlQueryModel* trier(const QString &champ, Qt::SortOrder ordre) const;

    // Stats
    QSqlQueryModel* statistiquesParLieu() const;
    QSqlQueryModel* statistiquesParResponsable() const;
    int statistiques() const;

private:
    int id;
    QString nom;
    QString description;
    int duree_seance;
    QString lieu;
    int nb_participants_max;
    QString responsable_club;
};

#endif

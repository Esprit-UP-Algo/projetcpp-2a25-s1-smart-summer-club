#ifndef ACTIVITE_H
#define ACTIVITE_H

#include <Qt>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

class Activite
{
private:
    int id;
    QString nom;
    QString description;
    int dureeSeance;  // En minutes
    QString lieu;
    int nbParticipantsMax;
    QString responsableClub;

public:
    // Constructeurs
    Activite();
    Activite(int id, QString nom, QString description, int dureeSeance, QString lieu, int nbParticipantsMax, QString responsableClub);

    // Getters
    int getId() const { return id; }
    QString getNom() const { return nom; }
    QString getDescription() const { return description; }
    int getDureeSeance() const { return dureeSeance; }
    QString getLieu() const { return lieu; }
    int getNbParticipantsMax() const { return nbParticipantsMax; }
    QString getResponsableClub() const { return responsableClub; }

    // Setters
    void setId(int id) { this->id = id; }
    void setNom(QString nom) { this->nom = nom; }
    void setDescription(QString description) { this->description = description; }
    void setDureeSeance(int dureeSeance) { this->dureeSeance = dureeSeance; }
    void setLieu(QString lieu) { this->lieu = lieu; }
    void setNbParticipantsMax(int nbParticipantsMax) { this->nbParticipantsMax = nbParticipantsMax; }
    void setResponsableClub(QString responsableClub) { this->responsableClub = responsableClub; }

    // Méthodes CRUD
    bool ajouter();
    bool supprimer(int id);
    bool mettreAJour(int id);
    QSqlQueryModel* afficher() const;
    bool exists(int id) const;

    // Méthodes supplémentaires
    QSqlQueryModel* rechercher(const QString& terme) const;  // Recherche avancée
    QSqlQueryModel* trier(const QString& critere, Qt::SortOrder ordre = Qt::AscendingOrder) const;  // Tri
    QSqlQueryModel* statistiquesParLieu() const;
    QSqlQueryModel* statistiquesParResponsable() const;
    void exporterPDF() const;  // Exportation en PDF
    bool genererQRCode(int activiteId, const QString& fichierSortie) const;
    int statistiques() const;  // Retourne le nombre total d'activités
};

#endif // ACTIVITE_H

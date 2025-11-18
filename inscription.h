#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QString>

class QSqlQueryModel;
class QSqlDatabase;

class Inscription
{
private:
    int id_inscription;
    int id_abonne;
    int id_activite;
    QString date_inscription;   // format: "yyyy-MM-dd"
    QString statut;             // confirmé | en attente | annulée
    bool paiement_effectue;
    double prix;

public:
    // Constructeurs
    Inscription();
    Inscription(int id_inscription, int id_abonne, int id_activite,
                const QString& date_inscription, const QString& statut,
                bool paiement_effectue, double prix);

    // Getters
    int getIdInscription() const;
    int getIdAbonne() const;
    int getIdActivite() const;
    QString getDateInscription() const;
    QString getStatut() const;
    bool getPaiementEffectue() const;
    double getPrix() const;

    // Setters
    void setIdInscription(int);
    void setIdAbonne(int);
    void setIdActivite(int);
    void setDateInscription(const QString&);
    void setStatut(const QString&);
    void setPaiementEffectue(bool);
    void setPrix(double);

    // Méthodes CRUD
    bool ajouter() const;
    bool modifier() const;
    bool supprimer() const;  // Supprime l'inscription courante
    bool sauvegarder() const; // Sauvegarde (ajoute ou modifie selon l'ID)
    static Inscription* charger(int id); // Charge une inscription par ID
    QSqlQueryModel* afficher() const;

    // Validation
    bool validerChamps() const;

    // Métiers/utilitaires
    bool existeDoublon(int idAbonne, int idActivite, int saufId = 0) const;
    int placesRestantesPourActivite(int idActivite) const;
    double calculerPrixFinal(int idAbonne, int idActivite, double prixBase) const;
};

#endif // INSCRIPTION_H

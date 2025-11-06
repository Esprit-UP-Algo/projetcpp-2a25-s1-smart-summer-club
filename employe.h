#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Employe
{
private:
    int id_employe;
    QString nom;
    QString prenom;
    QString poste;
    QString fonction;
    QString genre;
    QString email;
    QString telephone;
    QString date_de_naissance;
    QString adresse;
    float salaire;

public:
    // Constructeurs
    Employe();
    Employe(int, QString, QString, QString, QString, QString, QString,
            QString, QString, QString, float);

    // Getters
    int getIdEmploye() { return id_employe; }
    QString getNom() { return nom; }
    QString getPrenom() { return prenom; }
    QString getPoste() { return poste; }
    QString getFonction() { return fonction; }
    QString getGenre() { return genre; }
    QString getEmail() { return email; }
    QString getTelephone() { return telephone; }
    QString getDateNaissance() { return date_de_naissance; }
    QString getAdresse() { return adresse; }
    float getSalaire() { return salaire; }

    // Setters
    void setIdEmploye(int id) { id_employe = id; }
    void setNom(QString n) { nom = n; }
    void setPrenom(QString p) { prenom = p; }
    void setPoste(QString p) { poste = p; }
    void setFonction(QString f) { fonction = f; }
    void setGenre(QString g) { genre = g; }
    void setEmail(QString e) { email = e; }
    void setTelephone(QString t) { telephone = t; }
    void setDateNaissance(QString d) { date_de_naissance = d; }
    void setAdresse(QString a) { adresse = a; }
    void setSalaire(float s) { salaire = s; }

    // Méthodes CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
};

#endif // EMPLOYE_H

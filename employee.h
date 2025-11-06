#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Employe
{
private:
    int id_employe;
    QString nom;
    QString prenom;
    QString genre;
    QString poste;
    QString email;
    QString telephone;
    QDate date_naissance;
    QString statut;
    double salaire;
    QString adresse;

public:
    // Constructeurs
    Employe();
    Employe(int, QString, QString, QString, QString, QString, QString, QDate, QString, double, QString);

    // Getters
    int getId() const { return id_employe; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getGenre() const { return genre; }
    QString getPoste() const { return poste; }
    QString getEmail() const { return email; }
    QString getTelephone() const { return telephone; }
    QDate getDateNaissance() const { return date_naissance; }
    QString getStatut() const { return statut; }
    double getSalaire() const { return salaire; }
    QString getAdresse() const { return adresse; }

    // Setters
    void setId(int id) { id_employe = id; }
    void setNom(const QString &n) { nom = n; }
    void setPrenom(const QString &p) { prenom = p; }
    void setGenre(const QString &g) { genre = g; }
    void setPoste(const QString &p) { poste = p; }
    void setEmail(const QString &e) { email = e; }
    void setTelephone(const QString &t) { telephone = t; }
    void setDateNaissance(const QDate &d) { date_naissance = d; }
    void setStatut(const QString &s) { statut = s; }
    void setSalaire(double s) { salaire = s; }
    void setAdresse(const QString &a) { adresse = a; }

    // Fonctions CRUD
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int id);
    bool modifier();

    // Recherche / Tri
    QSqlQueryModel *rechercher(const QString &critere);
    QSqlQueryModel *trierParSalaire(bool ascendant);
};

#endif // EMPLOYE_H

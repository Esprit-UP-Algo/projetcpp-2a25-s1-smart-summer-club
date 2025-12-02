#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QPair>

class Employee
{
private:
    int id_employee;
    QString nom;
    QString prenom;
    QString poste;
    QString fonction;
    QString genre;
    QString email;
    QString telephone;
    QDate date_naissance;
    QString adresse;
    double salaire;

public:
    // Constructeurs
    Employee();
    Employee(QString n, QString p, QString pos, QString fonc, QString g,
             QString e, QString tel, QDate dn, QString adr, double sal);
    Employee(int id, QString n, QString p, QString pos, QString fonc, QString g,
             QString e, QString tel, QDate dn, QString adr, double sal);

    // Constructeur avec seulement l'ID
    Employee(int id);

    // Getters
    int getId() const { return id_employee; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getPoste() const { return poste; }
    QString getFonction() const { return fonction; }
    QString getGenre() const { return genre; }
    QString getEmail() const { return email; }
    QString getTelephone() const { return telephone; }
    QString getAdresse() const { return adresse; }
    QDate getDateNaissance() const { return date_naissance; }
    double getSalaire() const { return salaire; }

    // Méthodes CRUD
    bool ajouter();
    bool supprimer(int id);
    bool modifier();

    // Rechercher et trier
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercherParId(int id);
    QSqlQueryModel* trierParId();
    QSqlQueryModel* trierParNom();
    QSqlQueryModel* trierParPrenom();

    // Statistiques
    QPair<double,double> calculerPourcentageGenre();
};

#endif // EMPLOYEE_H

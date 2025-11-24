#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>

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
    Employee();
    // Constructor for adding (without ID)
    Employee(QString n, QString p, QString pos, QString fonc, QString g,
             QString e, QString tel, QDate dn, QString adr, double sal);
    // Constructor with ID (for modify)
    Employee(int id, QString n, QString p, QString pos, QString fonc, QString g,
             QString e, QString tel, QDate dn, QString adr, double sal);

    // Getters
    int getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getPoste() const;
    QString getFonction() const;
    QString getGenre() const;
    QString getEmail() const;
    QString getTelephone() const;
    QDate getDateNaissance() const;
    QString getAdresse() const;
    double getSalaire() const;

    // CRUD operations
    bool ajouter();
    bool supprimer(int id);
    bool modifier();
    QSqlQueryModel* afficher();
};

#endif // EMPLOYEE_H

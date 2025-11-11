#ifndef ABONNE_H
#define ABONNE_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>

class Abonne
{
private:
    int id_abonne;
    QString nom, prenom, adresse, telephone, email;
    QDate date_naissance;

public:
    Abonne();
    Abonne(int, QString, QString, QDate, QString, QString, QString);

    int getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QDate getDateNaissance() const;
    QString getAdresse() const;
    QString getTelephone() const;
    QString getEmail() const;

    bool ajouter();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel *afficher();
};

#endif // ABONNE_H

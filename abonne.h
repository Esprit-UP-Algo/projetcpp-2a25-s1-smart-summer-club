#ifndef ABONNE_H
#define ABONNE_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Abonne
{
private:
    int id_abonne;
    QString nom;
    QString prenom;
    QDate date_naissance;
    QString adresse;
    QString telephone;
    QString email;

public:
    Abonne();
    Abonne(int id, QString n, QString p, QDate dn, QString a, QString t, QString e);

    // Getters
    int getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QDate getDateNaissance() const;
    QString getAdresse() const;
    QString getTelephone() const;
    QString getEmail() const;

    // Setters
    void setId(int id);
    void setNom(const QString &n);
    void setPrenom(const QString &p);
    void setDateNaissance(const QDate &dn);
    void setAdresse(const QString &a);
    void setTelephone(const QString &t);
    void setEmail(const QString &e);

    // Fonctions CRUD
    bool ajouter();
    bool supprimer(int id);
    bool modifier();
    QSqlQueryModel* afficher();

    // Rechercher
    QSqlQueryModel* rechercher(const QString &critere);
    QSqlQueryModel* rechercherParId(int id);

    // Trier par critère : "nom", "prenom", "adresse"
    QSqlQueryModel* trier(const QString &critere);
};

#endif // ABONNE_H

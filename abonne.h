#ifndef ABONNE_H
#define ABONNE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Abonne {
private:
    int id_abonne;
    QString nom, prenom, adresse, telephone, email, date_naissance;

public:
    Abonne() {}
    Abonne(QString nom, QString prenom, QString adresse, QString telephone, QString email, QString date_naissance);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier(int id);
    bool supprimer(int id);
};

#endif // ABONNE_H

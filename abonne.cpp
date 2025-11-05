#include "abonne.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <QDebug>
#include <QSqlError>


Abonne::Abonne(QString nom, QString prenom, QString adresse, QString telephone, QString email, QString date_naissance) {
    this->nom = nom;
    this->prenom = prenom;
    this->adresse = adresse;
    this->telephone = telephone;
    this->email = email;
    this->date_naissance = date_naissance;
}

bool Abonne::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO ABONNE (NOM, PRENOM, ADRESSE, TELEPHONE, EMAIL, DATE_NAISSANCE) "
                  "VALUES (:nom, :prenom, :adresse, :telephone, :email, TO_DATE(:date_naissance, 'YYYY-MM-DD'))");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);
    query.bindValue(":date_naissance", date_naissance);
    return query.exec();
}


QSqlQueryModel* Abonne::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_ABONNE, NOM, PRENOM, ADRESSE, TELEPHONE, EMAIL, DATE_NAISSANCE FROM ABONNE");
    return model;
}

bool Abonne::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE ABONNE SET "
                  "NOM=:nom, PRENOM=:prenom, ADRESSE=:adresse, TELEPHONE=:telephone, EMAIL=:email, "
                  "DATE_NAISSANCE=TO_DATE(:date_naissance, 'YYYY-MM-DD') "
                  "WHERE ID_ABONNE=:id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);
    query.bindValue(":date_naissance", date_naissance); // must be "yyyy-MM-dd"

    if (!query.exec()) {
        qDebug() << "Erreur modifier:" << query.lastError().text();
        return false;
    }
    return true;
}


bool Abonne::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM ABONNE WHERE ID_ABONNE = :id");
    query.bindValue(":id", id);
    return query.exec();
}

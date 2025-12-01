#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>

Employe::Employe(){}

Employe::Employe(int id, QString nom, QString prenom, QString poste,
                 QString fonction, QString genre, QString email,
                 QString telephone, QString date_naissance,
                 QString adresse, float salaire)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->poste=poste;
    this->fonction=fonction;
    this->genre=genre;
    this->email=email;
    this->telephone=telephone;
    this->date_naissance=date_naissance;
    this->adresse=adresse;
    this->salaire=salaire;
}

bool Employe::ajouter()
{
    QSqlQuery q;
    q.prepare("INSERT INTO EMPLOYE VALUES "
              "(:id,:nom,:prenom,:poste,:fonction,:genre,:email,"
              ":tel,:date_n,:adr,:sal)");

    q.bindValue(":id", id);
    q.bindValue(":nom", nom);
    q.bindValue(":prenom", prenom);
    q.bindValue(":poste", poste);
    q.bindValue(":fonction", fonction);
    q.bindValue(":genre", genre);
    q.bindValue(":email", email);
    q.bindValue(":tel", telephone);
    q.bindValue(":date_n", date_naissance);
    q.bindValue(":adr", adresse);
    q.bindValue(":sal", salaire);

    if(!q.exec()){ m_lastError=q.lastError().text(); return false; }
    return true;
}

bool Employe::modifier()
{
    QSqlQuery q;
    q.prepare("UPDATE EMPLOYE SET NOM=:nom WHERE ID_EMPLOYE=:id");
    q.bindValue(":id",id);
    if(!q.exec()){ m_lastError=q.lastError().text(); return false; }
    return true;
}

bool Employe::supprimer(int id)
{
    QSqlQuery q;
    q.prepare("DELETE FROM EMPLOYE WHERE ID_EMPLOYE=:id");
    q.bindValue(":id",id);
    return q.exec();
}

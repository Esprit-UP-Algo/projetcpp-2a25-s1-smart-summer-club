#include "employe.h"

Employe::Employe() {}

Employe::Employe(int id, QString nom, QString prenom, QString poste, QString fonction,
                 QString genre, QString email, QString telephone,
                 QString date_naissance, QString adresse, float salaire)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->poste = poste;
    this->fonction = fonction;
    this->genre = genre;
    this->email = email;
    this->telephone = telephone;
    this->date_naissance = date_naissance;
    this->adresse = adresse;
    this->salaire = salaire;
}

bool Employe::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO EMPLOYE "
                  "(ID_EMPLOYE, NOM, PRENOM, POSTE, FONCTION, GENRE, EMAIL, TELEPHONE, "
                  "DATE_DE_NAISSANCE, ADRESSE, SALAIRE) "
                  "VALUES (:id, :nom, :prenom, :poste, :fonction, :genre, :email, "
                  ":telephone, :date_naissance, :adresse, :salaire)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":fonction", fonction);
    query.bindValue(":genre", genre);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":adresse", adresse);
    query.bindValue(":salaire", salaire);

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool Employe::modifier()
{
    QSqlQuery query;

    query.prepare("UPDATE EMPLOYE SET "
                  "NOM = :nom, PRENOM = :prenom, POSTE = :poste, FONCTION = :fonction, "
                  "GENRE = :genre, EMAIL = :email, TELEPHONE = :telephone, "
                  "DATE_DE_NAISSANCE = :date_naissance, ADRESSE = :adresse, SALAIRE = :salaire "
                  "WHERE ID_EMPLOYE = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":fonction", fonction);
    query.bindValue(":genre", genre);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":adresse", adresse);
    query.bindValue(":salaire", salaire);
    query.bindValue(":id", id);

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }

    return true;
}

bool Employe::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

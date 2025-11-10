#include "employee.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>

Employe::Employe()
{
    id_employe = 0;
    salaire = 0;
}

Employe::Employe(int id_employe, QString nom, QString prenom, QString genre,
                 QString poste, QString email, QString telephone,
                 QDate date_naissance, QString statut, double salaire, QString adresse)
{
    this->id_employe = id_employe;
    this->nom = nom;
    this->prenom = prenom;
    this->genre = genre;
    this->poste = poste;
    this->email = email;
    this->telephone = telephone;
    this->date_naissance = date_naissance;
    this->statut = statut;
    this->salaire = salaire;
    this->adresse = adresse;
}

// Ajouter un employé
bool Employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO employe (id_employe, nom, prenom, genre, poste, email, telephone, date_naissance, statut, salaire, adresse) "
                  "VALUES (:id, :nom, :prenom, :genre, :poste, :email, :telephone, :date_naissance, :statut, :salaire, :adresse)");

    query.bindValue(":id", id_employe);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":genre", genre);
    query.bindValue(":poste", poste);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":statut", statut);
    query.bindValue(":salaire", salaire);
    query.bindValue(":adresse", adresse);

    return query.exec();
}

// Afficher tous les employés
QSqlQueryModel *Employe::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Adresse"));
    return model;
}

// Supprimer un employé
bool Employe::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM employe WHERE id_employe = :id");
    query.bindValue(":id", id);
    return query.exec();
}

// Modifier un employé
bool Employe::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE employe SET nom=:nom, prenom=:prenom, genre=:genre, poste=:poste, email=:email, "
                  "telephone=:telephone, date_naissance=:date_naissance, statut=:statut, salaire=:salaire, adresse=:adresse "
                  "WHERE id_employe=:id");

    query.bindValue(":id", id_employe);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":genre", genre);
    query.bindValue(":poste", poste);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":statut", statut);
    query.bindValue(":salaire", salaire);
    query.bindValue(":adresse", adresse);

    return query.exec();
}

// Rechercher un employé
QSqlQueryModel *Employe::rechercher(const QString &critere)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe WHERE nom LIKE '%" + critere + "%' OR prenom LIKE '%" + critere + "%'");
    return model;
}

// Trier par salaire
QSqlQueryModel *Employe::trierParSalaire(bool ascendant)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString ordre = ascendant ? "ASC" : "DESC";
    model->setQuery("SELECT * FROM employe ORDER BY salaire " + ordre);
    return model;
}

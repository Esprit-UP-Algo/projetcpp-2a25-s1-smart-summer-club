#include "employee.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>

// ---------------- CONSTRUCTEURS -----------------
Employee::Employee()
{
    id_employee = 0;
    nom = prenom = poste = fonction = genre = email = telephone = adresse = "";
    date_naissance = QDate();
    salaire = 0.0;
}

Employee::Employee(QString n, QString p, QString pos, QString fonc, QString g,
                   QString e, QString tel, QDate dn, QString adr, double sal)
{
    id_employee = 0;
    nom = n; prenom = p; poste = pos; fonction = fonc; genre = g;
    email = e; telephone = tel; date_naissance = dn; adresse = adr;
    salaire = sal;
}

Employee::Employee(int id, QString n, QString p, QString pos, QString fonc, QString g,
                   QString e, QString tel, QDate dn, QString adr, double sal)
{
    id_employee = id;
    nom = n; prenom = p; poste = pos; fonction = fonc; genre = g;
    email = e; telephone = tel; date_naissance = dn; adresse = adr;
    salaire = sal;
}

// Constructeur avec seulement l'ID
Employee::Employee(int id)
{
    id_employee = id;
    nom = prenom = poste = fonction = genre = email = telephone = adresse = "";
    date_naissance = QDate();
    salaire = 0.0;
}

// ---------------- AJOUTER -----------------
bool Employee::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYEE "
                  "(NOM, PRENOM, POSTE, FONCTION, GENRE, EMAIL, TELEPHONE, DATE_NAISSANCE, ADRESSE, SALAIRE) "
                  "VALUES (:nom, :prenom, :poste, :fonction, :genre, :email, :tel, :dn, :adr, :sal)");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":fonction", fonction);
    query.bindValue(":genre", genre);
    query.bindValue(":email", email);
    query.bindValue(":tel", telephone);
    query.bindValue(":dn", date_naissance);
    query.bindValue(":adr", adresse);
    query.bindValue(":sal", salaire);

    return query.exec();
}

// ---------------- AFFICHER -----------------
QSqlQueryModel* Employee::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT ID_EMPLOYEE, NOM, PRENOM, POSTE, FONCTION, GENRE, EMAIL, TELEPHONE, "
                  "TO_CHAR(DATE_NAISSANCE,'YYYY-MM-DD') AS DATE_NAISSANCE, ADRESSE, SALAIRE "
                  "FROM EMPLOYEE");
    query.exec();
    model->setQuery(std::move(query));
    return model;
}

// ---------------- SUPPRIMER -----------------
bool Employee::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYEE WHERE ID_EMPLOYEE=:id");
    query.bindValue(":id", id);
    return query.exec();
}

// ---------------- MODIFIER -----------------
bool Employee::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYEE SET NOM=:nom, PRENOM=:prenom, POSTE=:poste, "
                  "FONCTION=:fonction, GENRE=:genre, EMAIL=:email, TELEPHONE=:tel, "
                  "DATE_NAISSANCE=:dn, ADRESSE=:adr, SALAIRE=:sal "
                  "WHERE ID_EMPLOYEE=:id");

    query.bindValue(":id", id_employee);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":fonction", fonction);
    query.bindValue(":genre", genre);
    query.bindValue(":email", email);
    query.bindValue(":tel", telephone);
    query.bindValue(":dn", date_naissance);
    query.bindValue(":adr", adresse);
    query.bindValue(":sal", salaire);

    return query.exec();
}

// ---------------- RECHERCHER PAR ID -----------------
QSqlQueryModel* Employee::rechercherParId(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT ID_EMPLOYEE, NOM, PRENOM, POSTE, FONCTION, GENRE, EMAIL, TELEPHONE, "
                  "TO_CHAR(DATE_NAISSANCE,'YYYY-MM-DD') AS DATE_NAISSANCE, ADRESSE, SALAIRE "
                  "FROM EMPLOYEE WHERE ID_EMPLOYEE=:id");
    query.bindValue(":id", id);
    query.exec();
    model->setQuery(std::move(query));
    return model;
}

// ---------------- TRIER -----------------
QSqlQueryModel* Employee::trierParId()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.exec("SELECT * FROM EMPLOYEE ORDER BY ID_EMPLOYEE ASC");
    model->setQuery(std::move(query));
    return model;
}

QSqlQueryModel* Employee::trierParNom()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.exec("SELECT * FROM EMPLOYEE ORDER BY NOM ASC");
    model->setQuery(std::move(query));
    return model;
}

QSqlQueryModel* Employee::trierParPrenom()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.exec("SELECT * FROM EMPLOYEE ORDER BY PRENOM ASC");
    model->setQuery(std::move(query));
    return model;
}

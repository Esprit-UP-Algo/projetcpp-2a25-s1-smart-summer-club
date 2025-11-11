#include "employee.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QObject>
#include <QDate>

Employee::Employee()
{
    id_employee = 0;
    nom = prenom = poste = fonction = genre = email = telephone = adresse = "";
    date_naissance = QDate();
    salaire = 0.0;
}


// Without ID (for adding)
Employee::Employee(QString n, QString p, QString pos, QString fonc, QString g,
                   QString e, QString tel, QDate dn, QString adr, double sal)
    : id_employee(0), nom(n), prenom(p), poste(pos), fonction(fonc),
    genre(g), email(e), telephone(tel), date_naissance(dn), adresse(adr), salaire(sal)
{}

// With ID (for modify)
Employee::Employee(int id, QString n, QString p, QString pos, QString fonc, QString g,
                   QString e, QString tel, QDate dn, QString adr, double sal)
    : id_employee(id), nom(n), prenom(p), poste(pos), fonction(fonc),
    genre(g), email(e), telephone(tel), date_naissance(dn), adresse(adr), salaire(sal)
{}


int Employee::getId() const { return id_employee; }
QString Employee::getNom() const { return nom; }
QString Employee::getPrenom() const { return prenom; }
QString Employee::getPoste() const { return poste; }
QString Employee::getFonction() const { return fonction; }
QString Employee::getGenre() const { return genre; }
QString Employee::getEmail() const { return email; }
QString Employee::getTelephone() const { return telephone; }
QString Employee::getAdresse() const { return adresse; }
QDate Employee::getDateNaissance() const { return date_naissance; }
double Employee::getSalaire() const { return salaire; }

bool Employee::ajouter()
{
    QSqlQuery query;

    // Get next ID from sequence
    if(!query.exec("SELECT EMPLOYEE_SEQ.NEXTVAL FROM dual")) {
        qDebug() << "Erreur génération ID Employee:" << query.lastError().text();
        return false;
    }

    if(query.next()) {
        id_employee = query.value(0).toInt();
    } else {
        qDebug() << "Erreur génération ID Employee: Aucun résultat";
        return false;
    }

    query.prepare("INSERT INTO EMPLOYEE (ID_EMPLOYEE, NOM, PRENOM, POSTE, FONCTION, GENRE, EMAIL, TELEPHONE, DATE_NAISSANCE, ADRESSE, SALAIRE) "
                  "VALUES (:id, :nom, :prenom, :poste, :fonction, :genre, :email, :telephone, TO_DATE(:date_naissance,'YYYY-MM-DD'), :adresse, :salaire)");

    query.bindValue(":id", id_employee);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":fonction", fonction);
    query.bindValue(":genre", genre);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":date_naissance", date_naissance.toString("yyyy-MM-dd"));
    query.bindValue(":adresse", adresse);
    query.bindValue(":salaire", salaire);

    if(!query.exec()) {
        qDebug() << "Erreur ajout Employee:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Employee::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYEE WHERE ID_EMPLOYEE = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool Employee::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYEE SET "
                  "NOM=:nom, PRENOM=:prenom, POSTE=:poste, FONCTION=:fonction, GENRE=:genre, EMAIL=:email, TELEPHONE=:telephone, "
                  "DATE_NAISSANCE=TO_DATE(:date_naissance,'YYYY-MM-DD'), ADRESSE=:adresse, SALAIRE=:salaire "
                  "WHERE ID_EMPLOYEE=:id");

    query.bindValue(":id", id_employee);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":fonction", fonction);
    query.bindValue(":genre", genre);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":date_naissance", date_naissance.toString("yyyy-MM-dd"));
    query.bindValue(":adresse", adresse);
    query.bindValue(":salaire", salaire);

    if(!query.exec()) {
        qDebug() << "Erreur modification Employee:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Employee::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EMPLOYEE, NOM, PRENOM, POSTE, FONCTION, GENRE, EMAIL, TELEPHONE, "
                    "TO_CHAR(DATE_NAISSANCE,'YYYY-MM-DD') AS DATE_NAISSANCE, ADRESSE, SALAIRE FROM EMPLOYEE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Fonction"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Salaire"));
    return model;
}

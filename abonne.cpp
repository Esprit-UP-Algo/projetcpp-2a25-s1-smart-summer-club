#include "abonne.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QObject>
#include <QDate>

Abonne::Abonne()
{
    id_abonne = 0;
    nom = prenom = adresse = telephone = email = "";
    date_naissance = QDate();
}

Abonne::Abonne(int id, QString n, QString p, QDate dn, QString a, QString t, QString e)
    : id_abonne(id), nom(n), prenom(p), date_naissance(dn), adresse(a), telephone(t), email(e)
{}


int Abonne::getId() const { return id_abonne; }
QString Abonne::getNom() const { return nom; }
QString Abonne::getPrenom() const { return prenom; }
QDate Abonne::getDateNaissance() const { return date_naissance; }
QString Abonne::getAdresse() const { return adresse; }
QString Abonne::getTelephone() const { return telephone; }
QString Abonne::getEmail() const { return email; }

bool Abonne::ajouter()
{
    QSqlQuery query;

    // Get next ID from sequence
    query.exec("SELECT abonne_seq.NEXTVAL FROM dual");
    if(query.next()) {
        id_abonne = query.value(0).toInt();
    } else {
        qDebug() << "Erreur génération ID Abonne:" << query.lastError().text();
        return false;
    }

    query.prepare("INSERT INTO abonne (ID_ABONNE, NOM, PRENOM, DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL) "
                  "VALUES (:id, :nom, :prenom, TO_DATE(:date_naissance,'YYYY-MM-DD'), :adresse, :telephone, :email)");

    query.bindValue(":id", id_abonne);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_naissance", date_naissance.toString("yyyy-MM-dd")); // correct format for TO_DATE
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);

    if(!query.exec()) {
        qDebug() << "Erreur ajout Abonne:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Abonne::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM abonne WHERE ID_ABONNE = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool Abonne::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE abonne SET "
                  "NOM = :nom, PRENOM = :prenom, DATE_NAISSANCE = TO_DATE(:date_naissance,'YYYY-MM-DD'), "
                  "ADRESSE = :adresse, TELEPHONE = :telephone, EMAIL = :email "
                  "WHERE ID_ABONNE = :id");

    query.bindValue(":id", id_abonne);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_naissance", date_naissance.toString("yyyy-MM-dd"));
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);

    if(!query.exec()) {
        qDebug() << "Erreur modification Abonne:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Abonne::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_ABONNE, NOM, PRENOM, TO_CHAR(DATE_NAISSANCE,'YYYY-MM-DD') AS DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL FROM abonne");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID abonné"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));

    return model;
}

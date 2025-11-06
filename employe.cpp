#include "employe.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QVariant> // Nécessaire pour lier correctement les floats

// Constructeur par défaut
Employe::Employe()
{
    id_employe = 0;
    nom = "";
    prenom = "";
    poste = "";
    fonction = "";
    genre = "";
    email = "";
    telephone = "";
    date_de_naissance = "";
    adresse = "";
    salaire = 0.0;
}

// Constructeur avec paramètres
Employe::Employe(int id, QString n, QString p, QString post, QString f,
                 QString g, QString em, QString tel, QString date,
                 QString adr, float sal)
{
    id_employe = id;
    nom = n;
    prenom = p;
    poste = post;
    fonction = f;
    genre = g;
    email = em;
    telephone = tel;
    date_de_naissance = date;
    adresse = adr;
    salaire = sal;
}

// Méthode ajouter avec requête préparée (sécurisée)
bool Employe::ajouter()
{
    QSqlQuery query;

    // Préparation de la requête avec des bind values
    query.prepare("INSERT INTO SUMMER.EMPLOYE "
                  "(ID_EMPLOYE, NOM, PRENOM, POSTE, FONCTION, GENRE, "
                  "EMAIL, TELEPHONE, DATE_DE_NAISSANCE, ADRESSE, SALAIRE) "
                  "VALUES (:id, :nom, :prenom, :poste, :fonction, :genre, "
                  ":email, :telephone, :date_naissance, :adresse, :salaire)");

    // Liaison des valeurs (protection contre injection SQL)
    query.bindValue(":id", id_employe);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":fonction", fonction);
    query.bindValue(":genre", genre);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":date_naissance", date_de_naissance);
    query.bindValue(":adresse", adresse);
    // Utiliser QVariant pour lier les valeurs numériques float (salaire)
    query.bindValue(":salaire", QVariant(salaire));

    // Exécution de la requête
    if (query.exec()) {
        qDebug() << "✅ Employé ajouté avec succès";
        return true;
    } else {
        qDebug() << "❌ Erreur lors de l'ajout:" << query.lastError().text();
        return false;
    }
}

// Méthode afficher (avec QSqlQueryModel)
QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM SUMMER.EMPLOYE");

    // Personnalisation des en-têtes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Fonction"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Salaire"));

    return model;
}

// Méthode supprimer
bool Employe::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM SUMMER.EMPLOYE WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "✅ Employé supprimé avec succès";
        return true;
    } else {
        qDebug() << "❌ Erreur lors de la suppression:" << query.lastError().text();
        return false;
    }
}

// ✅ Nouvelle méthode MODIFIER
bool Employe::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE SUMMER.EMPLOYE SET "
                  "NOM = :nom, PRENOM = :prenom, POSTE = :poste, "
                  "FONCTION = :fonction, GENRE = :genre, EMAIL = :email, "
                  "TELEPHONE = :telephone, DATE_DE_NAISSANCE = :date_naissance, "
                  "ADRESSE = :adresse, SALAIRE = :salaire "
                  "WHERE ID_EMPLOYE = :id");

    // Liaison des nouvelles valeurs
    query.bindValue(":id", id_employe); // L'ID sert à identifier la ligne à modifier
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":fonction", fonction);
    query.bindValue(":genre", genre);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":date_naissance", date_de_naissance);
    query.bindValue(":adresse", adresse);
    query.bindValue(":salaire", QVariant(salaire)); // Liaison du float

    if (query.exec()) {
        qDebug() << "✅ Employé modifié avec succès (ID:" << id_employe << ")";
        return true;
    } else {
        qDebug() << "❌ Erreur lors de la modification:" << query.lastError().text();
        return false;
    }
}

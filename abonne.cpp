#include "abonne.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QDate>
#include <QSqlError>
#include "smtp.h"


// -------------------------
// Constructeurs
Abonne::Abonne()
{
    id_abonne = 0;
    nom = prenom = adresse = telephone = email = "";
    date_naissance = QDate();
}

Abonne::Abonne(int id, QString n, QString p, QDate dn, QString a, QString t, QString e)
    : id_abonne(id), nom(n), prenom(p), date_naissance(dn), adresse(a), telephone(t), email(e)
{}

// -------------------------
// Getters
int Abonne::getId() const { return id_abonne; }
QString Abonne::getNom() const { return nom; }
QString Abonne::getPrenom() const { return prenom; }
QDate Abonne::getDateNaissance() const { return date_naissance; }
QString Abonne::getAdresse() const { return adresse; }
QString Abonne::getTelephone() const { return telephone; }
QString Abonne::getEmail() const { return email; }

// -------------------------
// Setters
void Abonne::setId(int id) { id_abonne = id; }
void Abonne::setNom(const QString &n) { nom = n; }
void Abonne::setPrenom(const QString &p) { prenom = p; }
void Abonne::setDateNaissance(const QDate &dn) { date_naissance = dn; }
void Abonne::setAdresse(const QString &a) { adresse = a; }
void Abonne::setTelephone(const QString &t) { telephone = t; }
void Abonne::setEmail(const QString &e) { email = e; }

// -------------------------
// Ajouter
bool Abonne::ajouter()
{
    QSqlQuery query;
    query.exec("SELECT abonne_seq.NEXTVAL FROM dual");
    if(query.next()) id_abonne = query.value(0).toInt();
    else { qDebug() << "Erreur génération ID Abonne:" << query.lastError().text(); return false; }

    query.prepare("INSERT INTO abonne (ID_ABONNE, NOM, PRENOM, DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL) "
                  "VALUES (:id, :nom, :prenom, TO_DATE(:date_naissance,'YYYY-MM-DD'), :adresse, :telephone, :email)");
    query.bindValue(":id", id_abonne);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_naissance", date_naissance.toString("yyyy-MM-dd"));
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);

    return query.exec();
}

// -------------------------
// Supprimer
bool Abonne::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM abonne WHERE ID_ABONNE = :id");
    query.bindValue(":id", id);
    return query.exec();
}

// -------------------------
// Modifier
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

    bool ok = query.exec();

    if (ok) {
        // ✅ Si la modification a réussi, on envoie un email

        // 1. Config SMTP (mets TES infos ici)
        QString smtpUser = "salsabilkhoualdi@gmail.com";      // ton email
        QString smtpPass = "abwp yynx mnzl tala";        // mot de passe d'application Gmail
        QString smtpHost = "smtp.gmail.com";
        int smtpPort = 465;                           // SSL

        Smtp *smtp = new Smtp(smtpUser, smtpPass, smtpHost, smtpPort, true);

        // 2. Construire le message
        QString from = smtpUser;
        QString to = email;  // on envoie a l’abonné
        QString subject = "Modification de vos informations";
        QString body = QString(
                           "Bonjour %1 %2,\n\n"
                           "Vos informations ont été modifiées dans notre système.\n\n"
                           "Nouvelles informations :\n"
                           "Nom: %1\n"
                           "Prénom: %2\n"
                           "Date de naissance: %3\n"
                           "Adresse: %4\n"
                           "Téléphone: %5\n"
                           "Email: %6\n\n"
                           "Cordialement,\n"
                           "L'équipe de gestion."
                           ).arg(nom)
                           .arg(prenom)
                           .arg(date_naissance.toString("yyyy-MM-dd"))
                           .arg(adresse)
                           .arg(telephone)
                           .arg(email);

        // 3. Envoyer
        smtp->sendMail(from, to, subject, body);

        // Optionnel : connecter le signal si tu veux afficher un message
        QObject::connect(smtp, &Smtp::mailSent, [=](bool success, const QString &err){
            if (!success) {
                qDebug() << "Erreur envoi mail:" << err;
            } else {
                qDebug() << "Email envoyé avec succès à" << to;
            }
            smtp->deleteLater();
        });
    }

    return ok;
}


// -------------------------
// Afficher
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

// -------------------------
// Rechercher par texte
QSqlQueryModel* Abonne::rechercher(const QString &critere)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT ID_ABONNE, NOM, PRENOM, TO_CHAR(DATE_NAISSANCE,'YYYY-MM-DD') AS DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL "
                  "FROM abonne "
                  "WHERE ID_ABONNE LIKE :critere OR NOM LIKE :critere OR PRENOM LIKE :critere OR ADRESSE LIKE :critere");
    query.bindValue(":critere", "%" + critere + "%");
    query.exec();
    model->setQuery(query);
    return model;
}

// -------------------------
// Rechercher par ID
QSqlQueryModel* Abonne::rechercherParId(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT ID_ABONNE, NOM, PRENOM, TO_CHAR(DATE_NAISSANCE,'YYYY-MM-DD') AS DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL "
                  "FROM abonne WHERE ID_ABONNE = :id");
    query.bindValue(":id", id);
    query.exec();
    model->setQuery(query);
    return model;
}

// -------------------------
// Trier
QSqlQueryModel* Abonne::trier(const QString &critere)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryStr = "SELECT ID_ABONNE, NOM, PRENOM, TO_CHAR(DATE_NAISSANCE,'YYYY-MM-DD') AS DATE_NAISSANCE, ADRESSE, TELEPHONE, EMAIL "
                       "FROM abonne "
                       "WHERE UPPER(NOM) LIKE UPPER('%" + critere + "%') "
                       "OR UPPER(PRENOM) LIKE UPPER('%" + critere + "%') "
                       "OR UPPER(ADRESSE) LIKE UPPER('%" + critere + "%') "
                       "ORDER BY NOM, PRENOM, ADRESSE";
    model->setQuery(queryStr);
    return model;
}

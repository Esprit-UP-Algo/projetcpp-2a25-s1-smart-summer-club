#include "activite.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QImage>
#include <QPainter>
#include <QPrinter>
#include <QObject>
#include <memory>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QStandardPaths>
#include <QTextDocument>
#include <QDate>
#include <QPageSize>
#include <QPageLayout>
#include <utility>
#include <QVariant>

#include "qrcodehelper.h"

namespace {
QSqlDatabase getDatabase()
{
    return QSqlDatabase::database(QStringLiteral("SMART_SUMMER_DB"));
}
}

Activite::Activite()
{
    this->id = 0;
    this->nom = "";
    this->description = "";
    this->dureeSeance = 0;
    this->lieu = "";
    this->nbParticipantsMax = 0;
    this->responsableClub = "";
}

Activite::Activite(int id, QString nom, QString description, int dureeSeance, QString lieu, int nbParticipantsMax, QString responsableClub)
{
    this->id = id;
    this->nom = nom;
    this->description = description;
    this->dureeSeance = dureeSeance;
    this->lieu = lieu;
    this->nbParticipantsMax = nbParticipantsMax;
    this->responsableClub = responsableClub;
}

bool Activite::ajouter()
{
    QSqlDatabase db = getDatabase();
    if (!db.isOpen()) {
        qCritical() << "Base de données non ouverte";
        return false;
    }
    QSqlQuery query(db);
    const bool hasId = id > 0;
    QString sql;
    if (hasId) {
        sql = QStringLiteral("INSERT INTO ACTIVITE (ID, NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX, RESPONSABLE_CLUB) "
                             "VALUES (:id, :nom, :description, :dureeSeance, :lieu, :nbParticipantsMax, :responsableClub)");
    } else {
        sql = QStringLiteral("INSERT INTO ACTIVITE (NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX, RESPONSABLE_CLUB) "
                             "VALUES (:nom, :description, :dureeSeance, :lieu, :nbParticipantsMax, :responsableClub)");
    }
    query.prepare(sql);
    if (hasId) {
        query.bindValue(":id", id);
    }
    query.bindValue(":nom", nom);
    query.bindValue(":description", description);
    query.bindValue(":dureeSeance", dureeSeance);
    query.bindValue(":lieu", lieu);
    query.bindValue(":nbParticipantsMax", nbParticipantsMax);
    query.bindValue(":responsableClub", responsableClub);

    if (query.exec()) {
        if (!hasId) {
            id = query.lastInsertId().toInt();
        }
        qDebug() << "Activité ajoutée avec succès. ID:" << id;
        return true;
    } else {
        qDebug() << "Erreur lors de l'ajout de l'activité :" << query.lastError().text();
        return false;
    }
}

bool Activite::supprimer(int id)
{
    QSqlDatabase db = getDatabase();
    if (!db.isOpen()) {
        qCritical() << "Base de données non ouverte";
        return false;
    }
    QSqlQuery query(db);
    query.prepare("DELETE FROM ACTIVITE WHERE ID = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "Activité supprimée avec succès.";
        return true;
    } else {
        qDebug() << "Erreur lors de la suppression de l'activité :" << query.lastError().text();
        return false;
    }
}

bool Activite::mettreAJour(int id)
{
    QSqlDatabase db = getDatabase();
    if (!db.isOpen()) {
        qCritical() << "Base de données non ouverte";
        return false;
    }
    QSqlQuery query(db);
    query.prepare("UPDATE ACTIVITE SET NOM = :nom, DESCRIPTION = :description, DUREE_SEANCE = :dureeSeance, "
                  "LIEU = :lieu, NB_PARTICIPANTS_MAX = :nbParticipantsMax, RESPONSABLE_CLUB = :responsableClub "
                  "WHERE ID = :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":description", description);
    query.bindValue(":dureeSeance", dureeSeance);
    query.bindValue(":lieu", lieu);
    query.bindValue(":nbParticipantsMax", nbParticipantsMax);
    query.bindValue(":responsableClub", responsableClub);

    if (query.exec()) {
        qDebug() << "Activité mise à jour avec succès.";
        return true;
    } else {
        qDebug() << "Erreur lors de la mise à jour de l'activité :" << query.lastError().text();
        return false;
    }
}

QSqlQueryModel* Activite::afficher() const
{
    QSqlDatabase db = getDatabase();
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM ACTIVITE ORDER BY ID ASC");
    query.exec();
    model->setQuery(std::move(query));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Durée Séance (min)"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Lieu"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Participants Max"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Responsable Club"));
    return model;
}

bool Activite::exists(int id) const
{
    QSqlDatabase db = getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM ACTIVITE WHERE ID = :id");
    query.bindValue(":id", id);
    query.exec();
    query.next();
    return query.value(0).toInt() > 0;
}

QSqlQueryModel* Activite::rechercher(const QString& terme) const
{
    QSqlDatabase db = getDatabase();
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query(db);
    QString sql = QStringLiteral(
        "SELECT * FROM ACTIVITE "
        "WHERE LOWER(NOM) LIKE :term "
        "   OR LOWER(DESCRIPTION) LIKE :term "
        "   OR LOWER(LIEU) LIKE :term "
        "   OR LOWER(RESPONSABLE_CLUB) LIKE :term");

    bool ok = false;
    const int idRecherche = terme.toInt(&ok);
    if (ok) {
        sql.append(" OR ID = :id");
    }

    query.prepare(sql);
    const QString termLower = terme.trimmed().toLower();
    const QString pattern = QStringLiteral("%%1%").arg(termLower);
    query.bindValue(":term", pattern);
    if (ok) {
        query.bindValue(":id", idRecherche);
    }
    query.exec();
    model->setQuery(std::move(query));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Durée Séance (min)"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Lieu"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Participants Max"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Responsable Club"));
    return model;
}

QSqlQueryModel* Activite::trier(const QString& critere, Qt::SortOrder ordre) const
{
    QSqlDatabase db = getDatabase();
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr;
    const QString orderStr = (ordre == Qt::DescendingOrder) ? QStringLiteral("DESC") : QStringLiteral("ASC");
    if (critere == "nom") {
        queryStr = QStringLiteral("SELECT * FROM ACTIVITE ORDER BY NOM %1").arg(orderStr);
    } else if (critere == "duree") {
        queryStr = QStringLiteral("SELECT * FROM ACTIVITE ORDER BY DUREE_SEANCE %1").arg(orderStr);
    } else {
        queryStr = QStringLiteral("SELECT * FROM ACTIVITE ORDER BY ID %1").arg(orderStr);
    }
    QSqlQuery query(db);
    query.prepare(queryStr);
    query.exec();
    model->setQuery(std::move(query));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Durée Séance (min)"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Lieu"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Participants Max"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Responsable Club"));
    return model;
}

QSqlQueryModel* Activite::statistiquesParLieu() const
{
    QSqlDatabase db = getDatabase();
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT LIEU, COUNT(*) AS TOTAL FROM ACTIVITE GROUP BY LIEU ORDER BY TOTAL DESC");
    query.exec();
    model->setQuery(std::move(query));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Lieu"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Total"));
    return model;
}

void Activite::exporterPDF() const
{
    QSqlDatabase db = getDatabase();
    if (!db.isOpen()) {
        qCritical() << "Base de données non ouverte pour l'export PDF";
        return;
    }

    QString fileName = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/activites_rapport.pdf";
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMarginsF(20, 20, 20, 20), QPageLayout::Millimeter);

    QPainter painter;
    if (!painter.begin(&printer)) {
        qCritical() << "Erreur lors de l'ouverture du PDF.";
        return;
    }

    QSqlQuery queryActivites(db);
    queryActivites.prepare("SELECT ID, NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX, RESPONSABLE_CLUB FROM ACTIVITE ORDER BY ID ASC");
    if (!queryActivites.exec()) {
        qCritical() << "Erreur lors de la récupération des activités:" << queryActivites.lastError().text();
        painter.end();
        return;
    }

    QSqlQuery queryStats(db);
    queryStats.prepare("SELECT LIEU, COUNT(*) AS TOTAL FROM ACTIVITE GROUP BY LIEU ORDER BY TOTAL DESC");
    if (!queryStats.exec()) {
        qCritical() << "Erreur lors de la récupération des statistiques:" << queryStats.lastError().text();
    }

    int totalActivites = statistiques();

    QString html = QStringLiteral(
        "<html><head><meta charset='UTF-8'></head><body>"
        "<h1 style='text-align:center; color:#2c3e50;'>Rapport des Activités</h1>"
        "<p style='text-align:center; font-size:12pt;'><strong>Total des activités : %1</strong></p>"
        "<hr>"
        "<h2 style='color:#34495e;'>Liste des Activités</h2>"
        "<table border='1' cellpadding='5' cellspacing='0' style='border-collapse:collapse; width:100%; font-size:9pt;'>"
        "<tr style='background-color:#3498db; color:white;'>"
        "<th>ID</th><th>Nom</th><th>Description</th><th>Durée (min)</th><th>Lieu</th><th>Participants Max</th><th>Responsable</th>"
        "</tr>"
    ).arg(totalActivites);

    int rowNum = 0;
    while (queryActivites.next()) {
        QString rowColor = (rowNum % 2 == 0) ? "#ecf0f1" : "#ffffff";
        html += QStringLiteral("<tr style='background-color:%1;'>").arg(rowColor);
        html += QStringLiteral("<td>%1</td>").arg(queryActivites.value(0).toString());
        html += QStringLiteral("<td>%1</td>").arg(queryActivites.value(1).toString().toHtmlEscaped());
        html += QStringLiteral("<td>%1</td>").arg(queryActivites.value(2).toString().toHtmlEscaped());
        html += QStringLiteral("<td style='text-align:center;'>%1</td>").arg(queryActivites.value(3).toString());
        html += QStringLiteral("<td>%1</td>").arg(queryActivites.value(4).toString().toHtmlEscaped());
        html += QStringLiteral("<td style='text-align:center;'>%1</td>").arg(queryActivites.value(5).toString());
        html += QStringLiteral("<td>%1</td>").arg(queryActivites.value(6).toString().toHtmlEscaped());
        html += "</tr>";
        rowNum++;
    }
    html += "</table>";

    if (queryStats.size() > 0) {
        html += QStringLiteral(
            "<hr>"
            "<h2 style='color:#34495e; margin-top:30px;'>Statistiques par Lieu</h2>"
            "<table border='1' cellpadding='5' cellspacing='0' style='border-collapse:collapse; width:100%; font-size:9pt;'>"
            "<tr style='background-color:#27ae60; color:white;'>"
            "<th>Lieu</th><th>Nombre d'activités</th>"
            "</tr>"
        );

        int statRowNum = 0;
        while (queryStats.next()) {
            QString rowColor = (statRowNum % 2 == 0) ? "#d5f4e6" : "#ffffff";
            html += QStringLiteral("<tr style='background-color:%1;'>").arg(rowColor);
            html += QStringLiteral("<td>%1</td>").arg(queryStats.value(0).toString().toHtmlEscaped());
            html += QStringLiteral("<td style='text-align:center; font-weight:bold;'>%1</td>").arg(queryStats.value(1).toString());
            html += "</tr>";
            statRowNum++;
        }
        html += "</table>";
    }

    html += QStringLiteral(
        "<hr>"
        "<p style='text-align:center; font-size:8pt; color:#7f8c8d; margin-top:30px;'>"
        "Généré le %1 par Smart Summer Application"
        "</p>"
        "</body></html>"
    ).arg(QDate::currentDate().toString("dd/MM/yyyy"));

    QTextDocument doc;
    doc.setHtml(html);
    doc.setPageSize(printer.pageRect(QPrinter::Point).size());
    doc.drawContents(&painter);
    painter.end();

    qInfo() << "PDF exporté avec succès vers :" << fileName;
}

bool Activite::genererQRCode(int activiteId, const QString& fichierSortie) const
{
    QSqlDatabase db = getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT ID, NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX, RESPONSABLE_CLUB "
                  "FROM ACTIVITE WHERE ID = :id");
    query.bindValue(":id", activiteId);
    if (!query.exec() || !query.next()) {
        qWarning() << "Impossible de générer le QR code, activité introuvable:" << query.lastError();
        return false;
    }

    const QString payload = QObject::tr("Activité #%1\nNom: %2\nLieu: %3\nDurée: %4 min\nParticipants: %5\nResponsable: %6")
                                .arg(query.value("ID").toString(),
                                     query.value("NOM").toString(),
                                     query.value("LIEU").toString(),
                                     query.value("DUREE_SEANCE").toString(),
                                     query.value("NB_PARTICIPANTS_MAX").toString(),
                                     query.value("RESPONSABLE_CLUB").toString());

    const QImage image = QrCodeHelper::generate(payload, 512, 12);
    if (image.isNull()) {
        return false;
    }

    QFileInfo info(fichierSortie);
    if (!info.absolutePath().isEmpty()) {
        QDir().mkpath(info.absolutePath());
    }
    return image.save(fichierSortie);
}

int Activite::statistiques() const
{
    QSqlDatabase db = getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM ACTIVITE");
    query.exec();
    query.next();
    return query.value(0).toInt();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "smtp.h"
#include "QrCode.hpp"
#include <QAbstractItemView>
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QStringList>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QDate>
#include <QPageSize>
#include <QPageLayout>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <algorithm>
#include "QDebug"
using namespace qrcodegen;

namespace {
bool hasMandatoryFields(const Activite& activite)
{
    return !activite.getNom().isEmpty()
        && !activite.getDescription().isEmpty()
        && !activite.getLieu().isEmpty()
        && !activite.getResponsableClub().isEmpty();
}
} // namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
    m_proxy = new QSortFilterProxyModel(this);
    m_proxy->setFilterKeyColumn(-1);
    m_proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->tableView_activites->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_activites->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_activites->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_activites->verticalHeader()->setVisible(false);

    ui->comboBox_tri->clear();
    ui->comboBox_tri->addItem(tr("ID croissant"), QStringLiteral("id|asc"));
    ui->comboBox_tri->addItem(tr("ID décroissant"), QStringLiteral("id|desc"));
    ui->comboBox_tri->addItem(tr("Nom (A-Z)"), QStringLiteral("nom|asc"));
    ui->comboBox_tri->addItem(tr("Nom (Z-A)"), QStringLiteral("nom|desc"));
    ui->comboBox_tri->addItem(tr("Durée croissante"), QStringLiteral("duree|asc"));
    ui->comboBox_tri->addItem(tr("Durée décroissante"), QStringLiteral("duree|desc"));

    initializeCharts();

    refreshTable();
    refreshStats();
    updateStatsLabel();
}

MainWindow::~MainWindow()
{
    delete m_model;
    delete m_statsModel;
    delete m_statsSecondaryModel;
    delete ui;
}

void MainWindow::setModel(QSqlQueryModel *model)
{
    if (!model) {
        return;
    }
    if (m_model) {
        delete m_model;
    }
    m_model = model;
    m_proxy->setSourceModel(m_model);
    ui->tableView_activites->setModel(m_proxy);
    ui->tableView_activites->resizeColumnsToContents();
}

void MainWindow::setStatsModel(QSqlQueryModel *model)
{
    if (!model) {
        return;
    }
    if (m_statsModel) {
        delete m_statsModel;
    }
    m_statsModel = model;
}

void MainWindow::setStatsSecondaryModel(QSqlQueryModel *model)
{
    if (!model) {
        return;
    }
    if (m_statsSecondaryModel) {
        delete m_statsSecondaryModel;
    }
    m_statsSecondaryModel = model;
}

void MainWindow::initializeCharts()
{
    if (!m_chartLieuView) {
        m_chartLieuView = new QChartView(ui->tab_statistique);
        m_chartLieuView->setRenderHint(QPainter::Antialiasing);
        m_chartLieuView->setFrameShape(QFrame::NoFrame);
    }

    if (!m_chartResponsableView) {
        m_chartResponsableView = new QChartView(ui->tab_statistique);
        m_chartResponsableView->setRenderHint(QPainter::Antialiasing);
        m_chartResponsableView->setFrameShape(QFrame::NoFrame);
    }

    updateChartGeometry();
}

void MainWindow::updateCharts()
{
    if (!m_chartLieuView || !m_chartResponsableView) {
        return;
    }

    updateBarChart(modelToVector(m_statsModel));
    updatePieChart(modelToVector(m_statsSecondaryModel));
}

QVector<QPair<QString, int>> MainWindow::modelToVector(const QSqlQueryModel *model) const
{
    QVector<QPair<QString, int>> data;
    if (!model) {
        return data;
    }
    for (int row = 0; row < model->rowCount(); ++row) {
        const QString label = model->data(model->index(row, 0)).toString();
        const int value = model->data(model->index(row, 1)).toInt();
        data.append(qMakePair(label, value));
    }
    return data;
}

void MainWindow::updateBarChart(const QVector<QPair<QString, int>> &data)
{
    if (!m_chartLieuView) {
        return;
    }

    QChart *chart = m_chartLieuView->chart();
    if (!chart) {
        chart = new QChart();
        m_chartLieuView->setChart(chart);
    }

    chart->removeAllSeries();
    const auto axes = chart->axes();
    for (QAbstractAxis *axis : axes) {
        chart->removeAxis(axis);
        delete axis;
    }

    chart->setTheme(QChart::ChartThemeLight);
    chart->setBackgroundBrush(QColor("#FFFFFF"));
    chart->setDropShadowEnabled(false);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle(tr("Répartition des activités par lieu"));

    if (data.isEmpty()) {
        chart->setTitle(tr("Répartition des activités par lieu (aucune donnée)"));
        return;
    }

    auto *series = new QBarSeries(chart);
    auto *barSet = new QBarSet(tr("Activités"));
    QStringList categories;
    int maxValue = 0;

    for (const auto &entry : data) {
        const QString label = entry.first.isEmpty() ? tr("Non défini") : entry.first;
        *barSet << entry.second;
        categories << label;
        maxValue = std::max(maxValue, entry.second);
    }

    barSet->setColor(QColor("#1DA1F2"));
    series->append(barSet);
    chart->addSeries(series);

    auto *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText(tr("Lieux"));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QValueAxis();
    axisY->setRange(0, std::max(1, maxValue + 1));
    axisY->setLabelFormat("%d");
    axisY->setTitleText(tr("Nombre d'activités"));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(false);
}

void MainWindow::updatePieChart(const QVector<QPair<QString, int>> &data)
{
    if (!m_chartResponsableView) {
        return;
    }

    QChart *chart = m_chartResponsableView->chart();
    if (!chart) {
        chart = new QChart();
        m_chartResponsableView->setChart(chart);
    }

    chart->removeAllSeries();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setBackgroundBrush(QColor("#FFFFFF"));
    chart->setDropShadowEnabled(false);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle(tr("Répartition des activités par responsable"));

    if (data.isEmpty()) {
        chart->setTitle(tr("Répartition des activités par responsable (aucune donnée)"));
        chart->legend()->setVisible(false);
        return;
    }

    auto *series = new QPieSeries(chart);
    series->setHoleSize(0.0);

    const QVector<QColor> palette = {
        QColor("#1DA1F2"),
        QColor("#0A5E9A"),
        QColor("#17BEBB"),
        QColor("#F5A623"),
        QColor("#F45B69"),
        QColor("#9B59B6")
    };

    for (int i = 0; i < data.size(); ++i) {
        const auto &entry = data.at(i);
        const QString label = entry.first.isEmpty() ? tr("Non défini") : entry.first;
        QPieSlice *slice = series->append(label, entry.second);
        slice->setLabel(QStringLiteral("%1 (%2)").arg(label, QString::number(entry.second)));
        slice->setLabelVisible(true);
        slice->setColor(palette.at(i % palette.size()));
    }

    chart->addSeries(series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
}

void MainWindow::updateChartGeometry()
{
    if (!m_chartLieuView || !m_chartResponsableView) {
        return;
    }

    const int sideMargin = 20;
    const int chartHeight = 230;
    const int spacing = 60;
    const int topOffset = 110;
    const int width = std::max(400, ui->tab_statistique->width() - 2 * sideMargin);

    m_chartLieuView->setGeometry(sideMargin, topOffset, width, chartHeight);
    m_chartResponsableView->setGeometry(sideMargin, topOffset + chartHeight + spacing, width, chartHeight);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    updateChartGeometry();
}

void MainWindow::refreshTable(const QString &orderBy, Qt::SortOrder order)
{
    m_currentOrderField = orderBy;
    m_currentOrder = order;
    if (orderBy.isEmpty()) {
        setModel(activite.afficher());
    } else {
        setModel(activite.trier(orderBy, order));
    }
    on_lineEdit_search_textChanged(ui->lineEdit_search->text());
}

void MainWindow::refreshStats()
{
    setStatsModel(activite.statistiquesParLieu());
    setStatsSecondaryModel(activite.statistiquesParResponsable());
    updateCharts();
}

void MainWindow::updateStatsLabel()
{
    const int total = activite.statistiques();
    ui->label_statsValue->setText(QString::number(total));
    if (ui->label_totalActivites) {
        ui->label_totalActivites->setText(tr("Total des activités : %1").arg(total));
    }
}

Activite MainWindow::activiteFromForm() const
{
    Activite a;
    bool ok = false;
    const int id = ui->lineEdit_idActivite->text().toInt(&ok);
    a.setId(ok ? id : 0);
    a.setNom(ui->lineEdit_nom->text().trimmed());
    a.setDescription(ui->textEdit_description->toPlainText().trimmed());
    const int duree = ui->lineEdit_duree->text().toInt(&ok);
    a.setDureeSeance(ok && duree > 0 ? duree : 0);
    a.setLieu(ui->lineEdit_lieu->text().trimmed());
    const int nbMax = ui->lineEdit_nbmax->text().toInt(&ok);
    a.setNbParticipantsMax(ok && nbMax > 0 ? nbMax : 0);
    a.setResponsableClub(ui->lineEdit_responsable->text().trimmed());
    return a;
}

int MainWindow::currentActiviteIdFromForm() const
{
    bool ok = false;
    const int id = ui->lineEdit_idActivite->text().toInt(&ok);
    return ok ? id : -1;
}

void MainWindow::clearForm()
{
    ui->lineEdit_idActivite->clear();
    ui->lineEdit_nom->clear();
    ui->textEdit_description->clear();
    ui->lineEdit_duree->clear();
    ui->lineEdit_lieu->clear();
    ui->lineEdit_nbmax->clear();
    ui->lineEdit_responsable->clear();
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    Activite a = activiteFromForm();
    if (!hasMandatoryFields(a)) {
        QMessageBox::warning(this, tr("Champs manquants"), 
                            tr("Veuillez remplir tous les champs obligatoires :\n"
                               "- Nom\n"
                               "- Description\n"
                               "- Lieu\n"
                               "- Responsable Club\n"
                               "- Durée (en minutes, > 0)\n"
                               "- Nombre de participants max (> 0)"));
        return;
    }

    if (a.getDureeSeance() <= 0) {
        QMessageBox::warning(this, tr("Durée invalide"), tr("La durée de la séance doit être supérieure à 0 minutes."));
        return;
    }

    if (a.getNbParticipantsMax() <= 0) {
        QMessageBox::warning(this, tr("Participants invalides"), tr("Le nombre maximum de participants doit être supérieur à 0."));
        return;
    }

    if (a.ajouter()) {
        refreshTable(m_currentOrderField, m_currentOrder);
        refreshStats();
        updateStatsLabel();
        QMessageBox::information(this, tr("Succès"), tr("Activité ajoutée avec succès."));
        clearForm();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ajouter l'activité.\nVérifiez la connexion à la base de données."));
    }
}

void MainWindow::on_pushButton_modifier_clicked()
{
    Activite a = activiteFromForm();
    if (a.getId() <= 0) {
        QMessageBox::warning(this, tr("ID manquant"), tr("Veuillez sélectionner une activité à modifier en cliquant sur une ligne du tableau."));
        return;
    }

    if (!activite.exists(a.getId())) {
        QMessageBox::critical(this, tr("Inconnu"), tr("L'activité avec l'ID %1 n'existe pas.").arg(a.getId()));
        return;
    }

    if (!hasMandatoryFields(a)) {
        QMessageBox::warning(this, tr("Champs manquants"), 
                            tr("Veuillez remplir tous les champs obligatoires :\n"
                               "- Nom\n"
                               "- Description\n"
                               "- Lieu\n"
                               "- Responsable Club\n"
                               "- Durée (en minutes, > 0)\n"
                               "- Nombre de participants max (> 0)"));
        return;
    }

    if (a.getDureeSeance() <= 0) {
        QMessageBox::warning(this, tr("Durée invalide"), tr("La durée de la séance doit être supérieure à 0 minutes."));
        return;
    }

    if (a.getNbParticipantsMax() <= 0) {
        QMessageBox::warning(this, tr("Participants invalides"), tr("Le nombre maximum de participants doit être supérieur à 0."));
        return;
    }

    if (a.mettreAJour(a.getId())) {
        refreshTable(m_currentOrderField, m_currentOrder);
        refreshStats();
        updateStatsLabel();
        QMessageBox::information(this, tr("Succès"), tr("Activité mise à jour avec succès."));
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("La mise à jour a échoué.\nVérifiez la connexion à la base de données."));
    }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    const int id = currentActiviteIdFromForm();
    if (id <= 0) {
        QMessageBox::warning(this, tr("ID manquant"), tr("Sélectionnez l'activité à supprimer."));
        return;
    }

    if (!activite.exists(id)) {
        QMessageBox::critical(this, tr("Inconnu"), tr("L'activité %1 n'existe pas.").arg(id));
        return;
    }

    const auto confirmation = QMessageBox::question(this, tr("Confirmation"),
                                                    tr("Supprimer définitivement l'activité %1 ?").arg(id));
    if (confirmation != QMessageBox::Yes) {
        return;
    }

    if (activite.supprimer(id)) {
        refreshTable(m_currentOrderField, m_currentOrder);
        refreshStats();
        updateStatsLabel();
        QMessageBox::information(this, tr("Succès"), tr("Activité supprimée."));
        clearForm();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("La suppression a échoué."));
    }
}

void MainWindow::on_pushButton_actualiser_clicked()
{
    clearForm();
}

void MainWindow::on_pushButton_search_clicked()
{
    const QString terme = ui->lineEdit_search->text().trimmed();
    if (terme.isEmpty()) {
        refreshTable(m_currentOrderField, m_currentOrder);
    } else {
        setModel(activite.rechercher(terme));
    }
}

void MainWindow::on_lineEdit_search_textChanged(const QString &text)
{
    if (!m_proxy) {
        return;
    }

    if (text.trimmed().isEmpty()) {
        m_proxy->setFilterRegularExpression(QRegularExpression());
    } else {
        const QRegularExpression regex(QRegularExpression::escape(text.trimmed()),
                                       QRegularExpression::CaseInsensitiveOption);
        m_proxy->setFilterRegularExpression(regex);
    }
}

void MainWindow::on_pushButton_trier_clicked()
{
    const QString value = ui->comboBox_tri->currentData().toString();
    const QStringList parts = value.split('|');
    if (parts.size() != 2) {
        refreshTable();
        return;
    }

    const QString critere = parts.at(0);
    const Qt::SortOrder ordre = (parts.at(1) == QLatin1String("desc")) ? Qt::DescendingOrder : Qt::AscendingOrder;
    refreshTable(critere, ordre);
}

void MainWindow::on_pushButton_export_clicked()
{
    const QString defaultFileName = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)
    + QStringLiteral("/activites_rapport.pdf");
    const QString fileName = QFileDialog::getSaveFileName(this,
                                                          tr("Exporter le rapport PDF"),
                                                          defaultFileName,
                                                          tr("Fichiers PDF (*.pdf)"));
    if (fileName.isEmpty()) {
        return;
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMarginsF(20, 20, 20, 20), QPageLayout::Millimeter);

    QPainter painter;
    if (!painter.begin(&printer)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de créer le fichier PDF."));
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Base de données non ouverte."));
        painter.end();
        return;
    }

    QSqlQuery queryActivites(db);
    queryActivites.prepare("SELECT ID, NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX, RESPONSABLE_CLUB FROM ACTIVITE ORDER BY ID ASC");
    if (!queryActivites.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de la récupération des activités."));
        painter.end();
        return;
    }

    QSqlQuery queryStats(db);
    queryStats.prepare("SELECT LIEU, COUNT(*) AS TOTAL FROM ACTIVITE GROUP BY LIEU ORDER BY TOTAL DESC");
    if (!queryStats.exec()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de la récupération des statistiques."));
    }

    const int totalActivites = activite.statistiques();

    QString html = QStringLiteral(
                       "<html><head><meta charset='UTF-8'></head>"
                       "<body style='color:black;'>"
                       "<h1 style='text-align:center; color:black;'>Rapport des Activités</h1>"
                       "<p style='text-align:center; font-size:12pt; color:black;'><strong>Total des activités : %1</strong></p>"
                       "<hr>"
                       "<h2 style='color:black;'>Liste des Activités</h2>"
                       "<table border='1' cellpadding='5' cellspacing='0' style='border-collapse:collapse; width:100%; font-size:9pt; color:black;'>"
                       "<tr style='background-color:#3498db; color:black;'>"
                       "<th>ID</th><th>Nom</th><th>Description</th><th>Durée (min)</th><th>Lieu</th><th>Participants Max</th><th>Responsable</th>"
                       "</tr>"
                       ).arg(totalActivites);

    int rowNum = 0;
    while (queryActivites.next()) {
        const QString rowColor = (rowNum % 2 == 0) ? "#ecf0f1" : "#ffffff";
        html += QStringLiteral("<tr style='background-color:%1; color:black;'>").arg(rowColor);
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
            "<h2 style='color:black; margin-top:30px;'>Statistiques par Lieu</h2>"
            "<table border='1' cellpadding='5' cellspacing='0' style='border-collapse:collapse; width:100%; font-size:9pt; color:black;'>"
            "<tr style='background-color:#27ae60; color:black;'>"
            "<th>Lieu</th><th>Nombre d'activités</th>"
            "</tr>"
            );

        int statRowNum = 0;
        while (queryStats.next()) {
            const QString rowColor = (statRowNum % 2 == 0) ? "#d5f4e6" : "#ffffff";
            html += QStringLiteral("<tr style='background-color:%1; color:black;'>").arg(rowColor);
            html += QStringLiteral("<td>%1</td>").arg(queryStats.value(0).toString().toHtmlEscaped());
            html += QStringLiteral("<td style='text-align:center; font-weight:bold;'>%1</td>").arg(queryStats.value(1).toString());
            html += "</tr>";
            statRowNum++;
        }
        html += "</table>";
    }

    html += QStringLiteral(
                "<hr>"
                "<p style='text-align:center; font-size:8pt; color:black; margin-top:30px;'>"
                "Généré le %1 par Smart Summer Application"
                "</p>"
                "</body></html>"
                ).arg(QDate::currentDate().toString("dd/MM/yyyy"));

    QTextDocument doc;
    doc.setHtml(html);
    doc.setPageSize(printer.pageRect(QPrinter::Point).size());
    doc.drawContents(&painter);
    painter.end();

    QMessageBox::information(this, tr("Succès"), tr("Le rapport PDF a été exporté avec succès.\n\nFichier : %1").arg(fileName));
}


void MainWindow::on_pushButton_refresh_table_clicked()
{
    refreshTable(m_currentOrderField, m_currentOrder);
    ui->lineEdit_search->clear();
}
void MainWindow::on_pushButton_generateQR_clicked()
{
    int row = ui->tableView_activites->currentIndex().row();
    if (row < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une activité.");
        return;
    }

    int id = ui->tableView_activites->model()
                 ->data(ui->tableView_activites->model()->index(row, 0))
                 .toInt();

    QSqlQuery qry(QSqlDatabase::database());
    qry.prepare("SELECT ID, NOM, DESCRIPTION, DUREE_SEANCE, LIEU, NB_PARTICIPANTS_MAX, RESPONSABLE_CLUB FROM ACTIVITE WHERE ID = :id");
    qry.bindValue(":id", id);

    if (!qry.exec()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'exécuter la requête : " );
        return;
    }

    if (!qry.next()) {
        QMessageBox::warning(this, "Erreur", "Aucune activité trouvée avec l'ID spécifié.");
        return;
    }

    // Read values from the query
    int idActivite        = qry.value("ID").toInt();
    QString nom           = qry.value("NOM").toString();
    QString description   = qry.value("DESCRIPTION").toString();
    int duree             = qry.value("DUREE_SEANCE").toInt();
    QString lieu          = qry.value("LIEU").toString();
    int participantsMax   = qry.value("NB_PARTICIPANTS_MAX").toInt();
    QString responsable   = qry.value("RESPONSABLE_CLUB").toString();

    // Construct QR code text
    QString info = QString(
                       "ID: %1\n"
                       "Nom: %2\n"
                       "Description: %3\n"
                       "Durée séance: %4 min\n"
                       "Lieu: %5\n"
                       "Participants max: %6\n"
                       "Responsable: %7")
                       .arg(idActivite)
                       .arg(nom)
                       .arg(description)
                       .arg(duree)
                       .arg(lieu)
                       .arg(participantsMax)
                       .arg(responsable);

    // Generate QR code
    QrCode qr = QrCode::encodeText(info.toUtf8().constData(), QrCode::Ecc::HIGH);

    QImage qrImg(qr.getSize(), qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            qrImg.setPixel(x, y, qr.getModule(x, y) ? qRgb(0, 0, 0) : qRgb(255, 255, 255));
        }
    }

    qrImg = qrImg.scaled(200, 200, Qt::KeepAspectRatio, Qt::FastTransformation);

    ui->qrcodecommande->setPixmap(QPixmap::fromImage(qrImg));
    ui->qrcodecommande->setAlignment(Qt::AlignCenter);
    ui->qrcodecommande->setStyleSheet("background:white; border:2px solid #3498db; border-radius:5px;");

    QString fileName = QString("activite_%1_qrcode.png").arg(idActivite);
    if (!qrImg.save(fileName)) {
        QMessageBox::warning(this, "Erreur", "Impossible de sauvegarder le QR code dans le fichier : " + fileName);
    }
}

void MainWindow::on_pushButton_stats_clicked()
{
    refreshStats();
    updateStatsLabel();
}

void MainWindow::on_pushButton_refresh_stats_clicked()
{
    refreshStats();
    updateStatsLabel();
}

void MainWindow::on_tableView_activites_clicked(const QModelIndex &index)
{
    if (!m_model || !m_proxy) {
        return;
    }
    const QModelIndex sourceIndex = m_proxy->mapToSource(index);
    if (!sourceIndex.isValid()) {
        return;
    }

    ui->lineEdit_idActivite->setText(m_model->data(m_model->index(sourceIndex.row(), 0)).toString());
    ui->lineEdit_nom->setText(m_model->data(m_model->index(sourceIndex.row(), 1)).toString());
    ui->textEdit_description->setPlainText(m_model->data(m_model->index(sourceIndex.row(), 2)).toString());
    ui->lineEdit_duree->setText(m_model->data(m_model->index(sourceIndex.row(), 3)).toString());
    ui->lineEdit_lieu->setText(m_model->data(m_model->index(sourceIndex.row(), 4)).toString());
    ui->lineEdit_nbmax->setText(m_model->data(m_model->index(sourceIndex.row(), 5)).toString());
    ui->lineEdit_responsable->setText(m_model->data(m_model->index(sourceIndex.row(), 6)).toString());
}

void MainWindow::on_browseBtn_clicked()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}

void MainWindow::on_sendBtn_clicked()
{

    Smtp* smtp = new Smtp("gafsibacem99@gmail.com",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
   // zzko qdvr yvxz pjja

    if( !files.isEmpty() )
        smtp->sendMail("gafsibacem99@gmail.com", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("gafsibacem99@gmail.com", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "databasemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouterInscription_clicked();
    void on_modifierInscription_clicked();
    void on_supprimerInscription_clicked();
    void on_validerInscription_clicked();
    void on_marquerPaiement_clicked();
    void on_actualiserStatistiques_clicked();
    void on_tableInscriptions_clicked(const QModelIndex &index);
    void on_pushButton_search_clicked();
    void on_pushButton_trier_clicked();
    void on_pushButton_export_clicked();
    void on_pushButton_refresh_table_clicked();
    void on_lineEdit_search_textChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *modelInscriptions;
    QStandardItemModel *modelAbonnes;
    QStandardItemModel *modelActivites;
    int currentInscriptionId;
    QString currentSortColumn;
    Qt::SortOrder currentSortOrder;

    void initialiserUI();
    void chargerDonnees();
    void chargerInscriptions(const QString &filter = QString(), const QString &sortColumn = QString(), Qt::SortOrder sortOrder = Qt::DescendingOrder);
    void chargerAbonnes();
    void chargerActivites();
    void mettreAJourStatistiques();
    void exporterPDF();
    void genererQRCode(int idInscription);
    void initialiserStatistiques();
};

#endif // MAINWINDOW_H

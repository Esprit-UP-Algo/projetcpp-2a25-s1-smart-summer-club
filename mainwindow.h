#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "database.h"

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

private:
    Ui::MainWindow *ui;
    QStandardItemModel *modelInscriptions;
    QStandardItemModel *modelAbonnes;
    QStandardItemModel *modelActivites;
    int currentInscriptionId;

    void initialiserUI();
    void chargerDonnees();
    void chargerInscriptions();
    void chargerAbonnes();
    void chargerActivites();
    void mettreAJourStatistiques();
};

#endif // MAINWINDOW_H

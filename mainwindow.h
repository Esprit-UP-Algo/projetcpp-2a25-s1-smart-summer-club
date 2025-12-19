#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAjouter_clicked();      // Si votre bouton s'appelle "btnAjouter"
    void on_btnModifier_clicked();     // "btnModifier"
    void on_btnSupprimer_clicked();    // "btnSupprimer"
    void ouvrirGestionMaterielle();

    // Si vous avez une liste ou autre
    void on_liste_itemClicked();       // Pour QListWidget

private slots:
    void ajouterMateriel();
    void modifierMateriel();
    void supprimerMateriel();
    void actualiserMateriel();
    void remplirChamps(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;


#endif // MAINWINDOW_H

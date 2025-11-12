#ifndef GESTIONINSCRIPTIONS_H
#define GESTIONINSCRIPTIONS_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQueryModel>
#include "inscription.h"

namespace Ui {
class GestionInscriptions;
}

class GestionInscriptions : public QDialog
{
    Q_OBJECT

public:
    explicit GestionInscriptions(QWidget *parent = nullptr);
    ~GestionInscriptions();

private slots:
    void on_btnAjouter_clicked();
    void on_btnModifier_clicked();
    void on_btnSupprimer_clicked();
    void on_btnRafraichir_clicked();
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::GestionInscriptions *ui;
    Inscription inscription;

    void chargerTable();
    void viderChamps();
};

#endif // GESTIONINSCRIPTIONS_H

#ifndef EMPLOYEEWINDOW_H
#define EMPLOYEEWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QPrinter>
#include <QTextDocument>
#include "employee.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EmployeeWindow; }
QT_END_NAMESPACE

class EmployeeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeWindow(QWidget *parent = nullptr);
    ~EmployeeWindow();

private slots:
    // CRUD
    void on_pushButton_ajouter_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_supprimer_clicked();

    // Recherche
    void on_pushButton_recherche_clicked();

    // Tri
    void trierEmployees(int index);

    // Statistique
    void afficherStatistique();

    // Sélection d’une ligne
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    // Attestation PDF
    void on_pushButton_attestation_clicked();

private:
    Ui::EmployeeWindow *ui;

    // ID de l'employé sélectionné
    int selectedId;

    // Afficher tous les employés
    void afficherEmployees();
};

#endif // EMPLOYEEWINDOW_H

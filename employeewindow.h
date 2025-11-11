#ifndef EMPLOYEEWINDOW_H
#define EMPLOYEEWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include "employee.h"

namespace Ui {
class EmployeeWindow;
}

class EmployeeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeWindow(QWidget *parent = nullptr);
    ~EmployeeWindow();

private slots:
    void afficherEmployees();
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void on_pushButton_ajouter_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_supprimer_clicked();

private:
    Ui::EmployeeWindow *ui;
    int selectedId;
};

#endif // EMPLOYEEWINDOW_H

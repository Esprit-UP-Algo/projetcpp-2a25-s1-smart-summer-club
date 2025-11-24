#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "abonnewindow.h"
#include "employeewindow.h"

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
    void openAbonneWindow();
    void openEmployeeWindow();

private:
    Ui::MainWindow *ui;
    AbonneWindow *abonneWindow;
    EmployeeWindow *employeeWindow;
};

#endif // MAINWINDOW_H

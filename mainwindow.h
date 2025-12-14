// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QPushButton>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT  // Add this line

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAbonneClicked();
    void onEmployeClicked();
    void onInscriptionClicked();
    void onActiviteClicked();
    void onMateriauxClicked();
    void refreshInscriptions();

private:
    Ui::MainWindow *ui;
    
    void setupConnections();
    void loadInscriptions();
    void clearForm();
    bool validateForm();
    void updateButtonsState(bool isEditing);
    void updateLcdDisplay();
};

#endif // MAINWINDOW_H
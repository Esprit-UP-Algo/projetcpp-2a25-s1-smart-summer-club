#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();
    void on_tableWidget_cellClicked(int row, int column);   // ✅ Sélection
    void on_pushButton_6_clicked();                         // ✅ Modifier
    void on_pushButton_7_clicked();                         // ✅ Supprimer

private:
    Ui::MainWindow *ui;
    Employe Etmp;

    // Méthodes de validation
    bool validerGenre(const QString &genre);
    bool validerEmail(const QString &email);
    bool validerTelephone(const QString &telephone);
    bool validerDate(const QString &date);

    // Méthode pour afficher les données
    void afficherEmployes();
};

#endif // MAINWINDOW_H

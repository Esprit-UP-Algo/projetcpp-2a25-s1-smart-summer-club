#ifndef ABONNEWINDOW_H
#define ABONNEWINDOW_H

#include <QMainWindow>
#include "abonne.h"
#include <QItemSelection>
#include <QItemSelectionModel>

QT_BEGIN_NAMESPACE
namespace Ui { class AbonneWindow; }
QT_END_NAMESPACE

class AbonneWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AbonneWindow(QWidget *parent = nullptr);
    ~AbonneWindow();

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_supprimer_clicked();

    // Slot for table row selection
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    Ui::AbonneWindow *ui;
    int selectedId = 0;  // store the ID of the selected row

    void afficherAbonnes();
};

#endif // ABONNEWINDOW_H

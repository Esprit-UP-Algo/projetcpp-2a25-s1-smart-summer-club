#ifndef ABONNEWINDOW_H
#define ABONNEWINDOW_H

#include <QMainWindow>

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
    void rechercherAbonne();   // Bouton Rechercher
    void ajouterAbonne();      // Bouton Ajouter
    void modifierAbonne();     // Bouton Modifier
    void supprimerAbonne();    // Bouton Supprimer
    void exporterPDF();        // Bouton Exportation PDF
    void trierAbonne();        // Bouton Trier
    void historiqueAbonne();   // Bouton Historique
    void remplirChampsDepuisTable(const QModelIndex &index); // 🔹 NEW

private:
    Ui::AbonneWindow *ui;
};

#endif // ABONNEWINDOW_H

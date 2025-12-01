#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr,
                        const QString &posteUser = QString(),
                        int idUser = -1);
    ~MainWindow();

private slots:
    // menu
    void onMenuButtonClicked();

    // CRUD / actions
    void on_pushButton_ajouter_clicked();
    void on_pushButton_6_clicked();   // modifier
    void on_pushButton_7_clicked();   // supprimer
    void on_pushButton_12_clicked();  // tri
    void on_pushButton_10_clicked();  // export PDF
    void on_pushButton_imprimer_clicked();
    void on_pushButton_11_clicked();  // recherche
    void on_pushButton_8_clicked();   // stats
    void on_pushButton_9_clicked();   // déconnexion
    void on_tableWidget_cellClicked(int row, int column);

    // validations (moc les voit comme slots dans certains projets)
    bool validerGenre(const QString &genre);
    bool validerEmail(const QString &email);
    bool validerTelephone(const QString &telephone);
    bool validerDate(const QString &date);

private:
    Ui::MainWindow *ui;

    QString m_posteUser;  // poste connecté (colonne POSTE)
    int m_idUser;         // ID employé connecté

    void afficherEmployes();
    QString construireAttestationHtml(const QString &mode,
                                      const QString &id,
                                      const QString &nom,
                                      const QString &prenom,
                                      const QString &poste,
                                      const QString &fonction,
                                      const QString &naissance,
                                      const QString &adresse,
                                      const QString &salaire);
    bool aLeDroit(const QString &action); // même si on renvoie toujours true

};

#endif // MAINWINDOW_H

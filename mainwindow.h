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

    // MENU (protection accès)
    void onMenuButtonClicked();

    // ===== GESTION EMPLOYÉS =====
    void afficherEmployes();

    // ===== VALIDATIONS =====
    bool validerGenre(const QString &genre);
    bool validerEmail(const QString &email);
    bool validerTelephone(const QString &telephone);
    bool validerDate(const QString &date);

    // ===== CRUD =====
    void on_pushButton_ajouter_clicked();
    void on_pushButton_6_clicked();   // modifier
    void on_pushButton_7_clicked();   // supprimer

    // ===== TABLE =====
    void on_tableWidget_cellClicked(int row, int column);

    // ===== TRI =====
    void on_pushButton_12_clicked();

    // ===== EXPORT PDF =====
    void on_pushButton_10_clicked();

    // ===== IMPRESSION DIRECTE =====
    void on_pushButton_imprimer_clicked();

    // ===== STATISTIQUES =====
    void on_pushButton_8_clicked();

    // ===== RECHERCHE =====
    void on_pushButton_11_clicked();

    // ===== DECONNEXION =====
    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;

    // Informations sur l'utilisateur connecté
    QString m_posteUser;   // poste de l'employé connecté
    int m_idUser;          // ID employé connecté

    // Gestion permissions
    bool aLeDroit(const QString &action);

    // Génération HTML pour les attestations
    QString construireAttestationHtml(const QString &mode,
                                      const QString &id,
                                      const QString &nom,
                                      const QString &prenom,
                                      const QString &poste,
                                      const QString &fonction,
                                      const QString &naissance,
                                      const QString &adresse,
                                      const QString &salaire);
};

#endif // MAINWINDOW_H

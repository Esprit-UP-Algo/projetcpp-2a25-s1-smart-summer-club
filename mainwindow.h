#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>

#include "activite.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_actualiser_clicked();
    void on_pushButton_search_clicked();
    void on_pushButton_trier_clicked();
    void on_pushButton_export_clicked();
    void on_pushButton_refresh_table_clicked();
    void on_pushButton_generateQR_clicked();
    void on_pushButton_stats_clicked();
    void on_pushButton_refresh_stats_clicked();
    void on_lineEdit_search_textChanged(const QString &text);
    void on_tableView_activites_clicked(const QModelIndex &index);

private:
    void refreshTable(const QString &orderBy = QStringLiteral("id"), Qt::SortOrder order = Qt::AscendingOrder);
    void refreshStats();
    void setModel(QSqlQueryModel *model);
    void setStatsModel(QSqlQueryModel *model);
    Activite activiteFromForm() const;
    void clearForm();
    void updateStatsLabel();
    int currentActiviteIdFromForm() const;

    Ui::MainWindow *ui;
    Activite activite;
    QSqlQueryModel *m_model = nullptr;
    QSqlQueryModel *m_statsModel = nullptr;
    QSortFilterProxyModel *m_proxy = nullptr;
    QString m_currentOrderField = QStringLiteral("id");
    Qt::SortOrder m_currentOrder = Qt::AscendingOrder;
};
#endif // MAINWINDOW_H

#ifndef GESTION_MATERIELLE_H
#define GESTION_MATERIELLE_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class gestion_materielle;
}

class gestion_materielle : public QWidget
{
    Q_OBJECT

public:
    explicit gestion_materielle(QWidget *parent = nullptr);
    ~gestion_materielle();

private slots:
    void ajouter();
    void modifier();
    void supprimer();

private:
    Ui::gestion_materielle *ui;
    QSqlTableModel *model;
};

#endif // GESTION_MATERIELLE_H



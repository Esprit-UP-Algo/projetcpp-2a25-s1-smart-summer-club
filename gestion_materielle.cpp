#include "gestion_materielle.h"
#include "ui_gestion_materielle.h"
#include <QSqlQuery>

gestion_materielle::gestion_materielle(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::gestion_materielle)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("materiel");
    model->select();

    ui->tableView->setModel(model);

    connect(ui->pushButton_ajouter, &QPushButton::clicked,
            this, &gestion_materielle::ajouter);
    connect(ui->pushButton_modifier, &QPushButton::clicked,
            this, &gestion_materielle::modifier);
    connect(ui->pushButton_supprimer, &QPushButton::clicked,
            this, &gestion_materielle::supprimer);
}

gestion_materielle::~gestion_materielle()
{
    delete ui;
}

void gestion_materielle::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO materiel (nom, type, quantite, etat) VALUES (?, ?, ?, ?)");
    query.addBindValue(ui->lineEdit_nom->text());
    query.addBindValue(ui->lineEdit_type->text());
    query.addBindValue(ui->lineEdit_quantite->text().toInt());
    query.addBindValue(ui->lineEdit_etat->text());
    query.exec();

    model->select();
}

void gestion_materielle::modifier()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) return;

    int id = model->data(model->index(index.row(), 0)).toInt();

    QSqlQuery query;
    query.prepare("UPDATE materiel SET nom=?, type=?, quantite=?, etat=? WHERE id=?");
    query.addBindValue(ui->lineEdit_nom->text());
    query.addBindValue(ui->lineEdit_type->text());
    query.addBindValue(ui->lineEdit_quantite->text().toInt());
    query.addBindValue(ui->lineEdit_etat->text());
    query.addBindValue(id);
    query.exec();

    model->select();
}

void gestion_materielle::supprimer()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) return;

    model->removeRow(index.row());
    model->submitAll();
}

#include "gestioninscriptionswidget.h"
#include "ui_gestioninscriptionswidget.h"

GestionInscriptionsWidget::GestionInscriptionsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GestionInscriptionsWidget)
{
    ui->setupUi(this);
}

GestionInscriptionsWidget::~GestionInscriptionsWidget()
{
    delete ui;
}

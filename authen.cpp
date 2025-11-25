#include "authen.h"
#include "ui_authen.h"

authen::authen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::authen)
{
    ui->setupUi(this);
}

authen::~authen()
{
    delete ui;
}

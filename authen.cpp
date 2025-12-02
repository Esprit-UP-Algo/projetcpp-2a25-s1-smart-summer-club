#include "authen.h"

authen::authen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::authen)   // match generated class
{
    ui->setupUi(this);
}

authen::~authen()
{
    delete ui;
}

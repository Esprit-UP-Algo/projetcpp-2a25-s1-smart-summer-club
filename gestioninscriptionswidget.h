#ifndef GESTIONINSCRIPTIONSWIDGET_H
#define GESTIONINSCRIPTIONSWIDGET_H

#include <QWidget>

namespace Ui {
class GestionInscriptionsWidget;
}

class GestionInscriptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GestionInscriptionsWidget(QWidget *parent = nullptr);
    ~GestionInscriptionsWidget();

private:
    Ui::GestionInscriptionsWidget *ui;
};

#endif // GESTIONINSCRIPTIONSWIDGET_H

#include "dashboardwidget.h"
#include "ui_dashboardwidget.h"
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>

DashboardWidget::DashboardWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DashboardWidget)
{
    ui->setupUi(this);
}

DashboardWidget::~DashboardWidget()
{
    delete ui;
}

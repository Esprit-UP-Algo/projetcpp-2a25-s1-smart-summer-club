#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QMainWindow>

// Forward declarations
class QChartView;
class QBarSeries;

QT_BEGIN_NAMESPACE
namespace Ui { class DashboardWidget; }
QT_END_NAMESPACE

class DashboardWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit DashboardWidget(QWidget *parent = nullptr);
    ~DashboardWidget();

private:
    Ui::DashboardWidget *ui;
};

#endif // DASHBOARDWIDGET_H

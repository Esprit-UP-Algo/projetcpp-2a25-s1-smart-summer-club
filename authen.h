#ifndef AUTHEN_H
#define AUTHEN_H

#include <QDialog>

namespace Ui {
class authen;
}

class authen : public QDialog
{
    Q_OBJECT

public:
    explicit authen(QWidget *parent = nullptr);
    ~authen();

private:
    Ui::authen *ui;
};

#endif // AUTHEN_H

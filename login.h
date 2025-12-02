#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    int     getIdEmploye() const;
    QString getPosteBD()   const;

private slots:
    void onConnectClicked();
    void onForgotPasswordClicked();

private:
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    QLineEdit *posteEdit;

    QPushButton *btnConnect;
    QPushButton *btnForgot;

    int m_idEmploye;
    QString m_posteBD;

    void setupUI();
};

#endif // LOGIN_H

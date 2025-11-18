#ifndef DATABASECONFIGDIALOG_H
#define DATABASECONFIGDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>

class DatabaseConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseConfigDialog(QWidget *parent = nullptr);
    
    QString getHost() const;
    int getPort() const;
    QString getDatabaseName() const;
    QString getUser() const;
    QString getPassword() const;
    QString getDatabaseType() const;

private slots:
    void onDatabaseTypeChanged(int index);
    void onTestConnection();

private:
    QComboBox *dbTypeCombo;
    QLineEdit *hostEdit;
    QSpinBox *portSpin;
    QLineEdit *databaseEdit;
    QLineEdit *userEdit;
    QLineEdit *passwordEdit;
    QPushButton *testButton;
    QPushButton *okButton;
    QPushButton *cancelButton;
    
    void setupUI();
};

#endif // DATABASECONFIGDIALOG_H


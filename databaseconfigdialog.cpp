#include "databaseconfigdialog.h"
#include "databasemanager.h"
#include <QMessageBox>
#include <QFormLayout>
#include <QSqlDatabase>
#include <QSqlError>

DatabaseConfigDialog::DatabaseConfigDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    
    // Valeurs par défaut pour Oracle
    hostEdit->setText("localhost");
    portSpin->setValue(1521);
    databaseEdit->setText("XE"); // SID par défaut pour Oracle XE
    userEdit->setText("system");
    
    // Connecter le signal de changement de type
    connect(dbTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DatabaseConfigDialog::onDatabaseTypeChanged);
    connect(testButton, &QPushButton::clicked, this, &DatabaseConfigDialog::onTestConnection);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void DatabaseConfigDialog::setupUI()
{
    setWindowTitle("Configuration de la Base de Données");
    setMinimumWidth(400);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Type de base de données
    QGroupBox *typeGroup = new QGroupBox("Type de Base de Données");
    QVBoxLayout *typeLayout = new QVBoxLayout;
    dbTypeCombo = new QComboBox;
    dbTypeCombo->addItem("SQLite (Local)");
    dbTypeCombo->addItem("Oracle");
    typeLayout->addWidget(dbTypeCombo);
    typeGroup->setLayout(typeLayout);
    mainLayout->addWidget(typeGroup);
    
    // Paramètres Oracle
    QGroupBox *oracleGroup = new QGroupBox("Paramètres Oracle");
    QFormLayout *formLayout = new QFormLayout;
    
    hostEdit = new QLineEdit;
    hostEdit->setPlaceholderText("localhost ou adresse IP");
    formLayout->addRow("Hôte:", hostEdit);
    
    portSpin = new QSpinBox;
    portSpin->setRange(1, 65535);
    portSpin->setValue(1521);
    formLayout->addRow("Port:", portSpin);
    
    databaseEdit = new QLineEdit;
    databaseEdit->setPlaceholderText("SID ou Service Name (ex: XE, ORCL)");
    formLayout->addRow("Base de données (SID):", databaseEdit);
    
    userEdit = new QLineEdit;
    userEdit->setPlaceholderText("Nom d'utilisateur");
    formLayout->addRow("Utilisateur:", userEdit);
    
    passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("Mot de passe");
    formLayout->addRow("Mot de passe:", passwordEdit);
    
    oracleGroup->setLayout(formLayout);
    mainLayout->addWidget(oracleGroup);
    
    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    testButton = new QPushButton("Tester la Connexion");
    testButton->setStyleSheet("background-color: orange; color: white; font-weight: bold;");
    okButton = new QPushButton("OK");
    okButton->setStyleSheet("background-color: green; color: white; font-weight: bold;");
    cancelButton = new QPushButton("Annuler");
    cancelButton->setStyleSheet("background-color: red; color: white; font-weight: bold;");
    
    buttonLayout->addWidget(testButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // Initialiser l'état
    onDatabaseTypeChanged(0);
}

void DatabaseConfigDialog::onDatabaseTypeChanged(int index)
{
    bool oracleSelected = (index == 1);
    hostEdit->setEnabled(oracleSelected);
    portSpin->setEnabled(oracleSelected);
    databaseEdit->setEnabled(oracleSelected);
    userEdit->setEnabled(oracleSelected);
    passwordEdit->setEnabled(oracleSelected);
    testButton->setEnabled(oracleSelected);
}

void DatabaseConfigDialog::onTestConnection()
{
    if (dbTypeCombo->currentIndex() == 0) {
        // SQLite - toujours disponible
        QMessageBox::information(this, "Test", "SQLite est toujours disponible (base locale)");
        return;
    }
    
    // Tester la connexion Oracle
    QString host = hostEdit->text();
    int port = portSpin->value();
    QString dbName = databaseEdit->text();
    QString user = userEdit->text();
    QString password = passwordEdit->text();
    
    if (host.isEmpty() || dbName.isEmpty() || user.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires");
        return;
    }
    
    // Vérifier si le driver est disponible
    if (!QSqlDatabase::isDriverAvailable("QOCI")) {
        QMessageBox::critical(this, "Erreur", 
            "Le driver Oracle (QOCI) n'est pas disponible.\n\n"
            "Pour utiliser Oracle, vous devez:\n"
            "1. Installer Oracle Instant Client\n"
            "2. Configurer les variables d'environnement (ORACLE_HOME, PATH)\n"
            "3. Redémarrer Qt Creator");
        return;
    }
    
    // Tester la connexion
    QSqlDatabase testDb = QSqlDatabase::addDatabase("QOCI", "test_connection");
    testDb.setHostName(host);
    testDb.setPort(port);
    testDb.setDatabaseName(dbName);
    testDb.setUserName(user);
    testDb.setPassword(password);
    
    if (testDb.open()) {
        QMessageBox::information(this, "Succès", "Connexion à Oracle réussie!");
        testDb.close();
    } else {
        QMessageBox::critical(this, "Erreur", 
            "Échec de la connexion:\n" + testDb.lastError().text() + 
            "\n\nVérifiez:\n"
            "- Que Oracle est démarré\n"
            "- Les paramètres de connexion\n"
            "- Le listener Oracle");
    }
    
    QSqlDatabase::removeDatabase("test_connection");
}

QString DatabaseConfigDialog::getHost() const
{
    return hostEdit->text();
}

int DatabaseConfigDialog::getPort() const
{
    return portSpin->value();
}

QString DatabaseConfigDialog::getDatabaseName() const
{
    return databaseEdit->text();
}

QString DatabaseConfigDialog::getUser() const
{
    return userEdit->text();
}

QString DatabaseConfigDialog::getPassword() const
{
    return passwordEdit->text();
}

QString DatabaseConfigDialog::getDatabaseType() const
{
    return dbTypeCombo->currentText();
}


#include "login.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QInputDialog>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , m_idEmploye(-1)
{
    setupUI();
}

Login::~Login() {}

void Login::setupUI()
{
    setWindowTitle("Authentification");
    setFixedSize(350, 200);

    emailEdit    = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);

    emailEdit->setPlaceholderText("Email");
    passwordEdit->setPlaceholderText("Mot de passe");
    passwordEdit->setEchoMode(QLineEdit::Password);

    btnConnect = new QPushButton("Connexion", this);
    btnForgot  = new QPushButton("Mot de passe oublié ?", this);
    btnForgot->setStyleSheet("color: blue; background:none; border:none; text-decoration:underline;");

    QVBoxLayout *v = new QVBoxLayout(this);
    v->addWidget(new QLabel("Email :"));
    v->addWidget(emailEdit);
    v->addWidget(new QLabel("Mot de passe :"));
    v->addWidget(passwordEdit);
    v->addWidget(btnConnect);
    v->addWidget(btnForgot);

    connect(btnConnect, &QPushButton::clicked, this, &Login::onConnectClicked);
    connect(btnForgot,  &QPushButton::clicked, this, &Login::onForgotPasswordClicked);
}

int Login::getIdEmploye() const
{
    return m_idEmploye;
}

QString Login::getPosteBD() const
{
    return m_posteBD;
}

void Login::onConnectClicked()
{
    QString email = emailEdit->text().trimmed();
    QString pass  = passwordEdit->text().trimmed();

    if (email.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs sont obligatoires !");
        return;
    }

    QSqlQuery q;
    q.prepare("SELECT ID_EMPLOYE, POSTE "
              "FROM EMPLOYE "
              "WHERE EMAIL = :email AND MOT_DE_PASSE = :pass");
    q.bindValue(":email", email);
    q.bindValue(":pass",  pass);

    if (!q.exec()) {
        QMessageBox::critical(this, "Erreur SQL", q.lastError().text());
        return;
    }

    if (!q.next()) {
        QMessageBox::warning(this, "Erreur",
                             "Email ou mot de passe incorrect !");
        return;
    }

    m_idEmploye = q.value("ID_EMPLOYE").toInt();
    m_posteBD   = q.value("POSTE").toString();

    accept();
}

void Login::onForgotPasswordClicked()
{
    QString email = QInputDialog::getText(this,
                                          "Mot de passe oublié",
                                          "Entrez votre email :").trimmed();

    if (email.isEmpty())
        return;

    QSqlQuery q;
    q.prepare("SELECT ID_EMPLOYE FROM SUMMER.EMPLOYE WHERE EMAIL = :email");
    q.bindValue(":email", email);

    if (!q.exec()) {
        QMessageBox::critical(this, "Erreur SQL", q.lastError().text());
        return;
    }

    if (!q.next()) {
        QMessageBox::warning(this, "Erreur",
                             "Cet email n'existe pas !");
        return;
    }

    QString newPwd = QInputDialog::getText(this,
                                           "Nouveau mot de passe",
                                           "Entrez le nouveau mot de passe :").trimmed();

    if (newPwd.isEmpty()) {
        QMessageBox::warning(this, "Erreur",
                             "Mot de passe vide !");
        return;
    }

    QSqlQuery update;
    update.prepare("UPDATE SUMMER.EMPLOYE SET MOT_DE_PASSE = :pwd WHERE EMAIL = :email");
    update.bindValue(":pwd",   newPwd);
    update.bindValue(":email", email);

    if (!update.exec()) {
        QMessageBox::critical(this, "Erreur SQL",
                              update.lastError().text());
        return;
    }

    QMessageBox::information(this,
                             "Succès",
                             "Le mot de passe a été modifié !");
}

#include "login.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QInputDialog>

Login::Login(QWidget *parent)
    : QDialog(parent), m_idEmploye(-1)
{
    setupUI();
}

Login::~Login() {}

void Login::setupUI()
{
    setWindowTitle("Authentification");
    setFixedSize(350, 270);

    emailEdit    = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    posteEdit    = new QLineEdit(this);

    emailEdit->setPlaceholderText("Email");
    passwordEdit->setPlaceholderText("Mot de passe");
    posteEdit->setPlaceholderText("Poste");

    passwordEdit->setEchoMode(QLineEdit::Password);

    btnConnect = new QPushButton("Connexion");
    btnForgot  = new QPushButton("Mot de passe oublié ?");
    btnForgot->setStyleSheet("color: blue; background:none; border:none; text-decoration:underline;");

    QVBoxLayout *v = new QVBoxLayout(this);
    v->addWidget(new QLabel("Email :"));
    v->addWidget(emailEdit);
    v->addWidget(new QLabel("Mot de passe :"));
    v->addWidget(passwordEdit);
    v->addWidget(new QLabel("Poste :"));
    v->addWidget(posteEdit);
    v->addWidget(btnConnect);
    v->addWidget(btnForgot);

    connect(btnConnect, &QPushButton::clicked, this, &Login::onConnectClicked);
    connect(btnForgot,  &QPushButton::clicked, this, &Login::onForgotPasswordClicked);
}

int Login::getIdEmploye() const { return m_idEmploye; }
QString Login::getPosteBD() const { return m_posteBD; }

void Login::onConnectClicked()
{
    QString email = emailEdit->text().trimmed();
    QString pass  = passwordEdit->text().trimmed();
    QString poste = posteEdit->text().trimmed().toLower();

    if (email.isEmpty() || pass.isEmpty() || poste.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Champs manquants !");
        return;
    }

    QSqlQuery q;
    q.prepare("SELECT ID_EMPLOYE, POSTE "
              "FROM EMPLOYE "
              "WHERE EMAIL=:email AND MOT_DE_PASSE=:pass");

    q.bindValue(":email", email);
    q.bindValue(":pass", pass);

    if (!q.exec()) {
        QMessageBox::critical(this, "Erreur SQL", q.lastError().text());
        return;
    }

    // ❌ mot de passe incorrect → essayer récupération
    if (!q.next()) {
        onForgotPasswordClicked();
        return;
    }

    // Vérifier le poste
    QString posteBD = q.value("POSTE").toString().trimmed().toLower();
    if (!posteBD.contains(poste)) {
        QMessageBox::warning(this, "Erreur",
                             "Poste incorrect ! Poste enregistré : " + posteBD);
        return;
    }

    // Succès
    m_idEmploye = q.value("ID_EMPLOYE").toInt();
    m_posteBD   = q.value("POSTE").toString();
    accept();
}

void Login::onForgotPasswordClicked()
{
    QString email = emailEdit->text().trimmed();

    if (email.isEmpty()) {
        email = QInputDialog::getText(this, "Mot de passe oublié",
                                      "Entrez votre email :").trimmed();
    }

    if (email.isEmpty()) return;

    // 1) Vérifier email
    QSqlQuery q;
    q.prepare("SELECT ID_EMPLOYE, POSTE, DATE_DE_NAISSANCE "
              "FROM EMPLOYE WHERE EMAIL=:email");
    q.bindValue(":email", email);

    if (!q.exec() || !q.next()) {
        QMessageBox::warning(this, "Erreur", "Email introuvable !");
        return;
    }

    QString naissanceBD = q.value("DATE_DE_NAISSANCE").toString().trimmed();
    int id = q.value("ID_EMPLOYE").toInt();
    QString poste = q.value("POSTE").toString();

    // 2) Poser la question
    QString rep = QInputDialog::getText(this,
                                        "Question secrète",
                                        "Votre date de naissance (JJ/MM/AAAA) :")
                      .trimmed();

    if (rep != naissanceBD) {
        QMessageBox::critical(this, "Erreur", "Réponse incorrecte !");
        return;
    }

    // 3) Succès → ouvrir interface
    m_idEmploye = id;
    m_posteBD   = poste;
    accept();
}

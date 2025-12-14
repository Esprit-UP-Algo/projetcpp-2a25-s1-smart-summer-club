#ifndef ABONNE_H
#define ABONNE_H

#include <QObject>
#include <QDate>
#include <QString>

class Abonne : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(QString nom READ nom WRITE setNom)
    Q_PROPERTY(QString prenom READ prenom WRITE setPrenom)
    Q_PROPERTY(QDate dateNaissance READ dateNaissance WRITE setDateNaissance)
    Q_PROPERTY(QString adresse READ adresse WRITE setAdresse)
    Q_PROPERTY(QString telephone READ telephone WRITE setTelephone)
    Q_PROPERTY(QString email READ email WRITE setEmail)
    Q_PROPERTY(QDate dateInscription READ dateInscription WRITE setDateInscription)

public:
    explicit Abonne(QObject* parent = nullptr);
    Abonne(int id, const QString& nom, const QString& prenom,
           const QDate& dateNaissance, const QString& adresse,
           const QString& telephone, const QString& email,
           const QDate& dateInscription = QDate::currentDate(),
           QObject* parent = nullptr);

    // Getters
    int id() const;
    QString nom() const;
    QString prenom() const;
    QDate dateNaissance() const;
    QString adresse() const;
    QString telephone() const;
    QString email() const;
    QDate dateInscription() const;
    QString nomComplet() const;
    int age() const;
    QString toString() const;

    // Setters
    void setId(int id);
    void setNom(const QString& nom);
    void setPrenom(const QString& prenom);
    void setDateNaissance(const QDate& date);
    void setAdresse(const QString& adresse);
    void setTelephone(const QString& telephone);
    void setEmail(const QString& email);
    void setDateInscription(const QDate& date);

private:
    int m_id;
    QString m_nom;
    QString m_prenom;
    QDate m_dateNaissance;
    QString m_adresse;
    QString m_telephone;
    QString m_email;
    QDate m_dateInscription;
};

#endif // ABONNE_H

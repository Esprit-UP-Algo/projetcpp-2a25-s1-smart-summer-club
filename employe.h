#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>

class Employe
{
public:
    Employe();
    Employe(int id, QString nom, QString prenom, QString poste,
            QString fonction, QString genre, QString email,
            QString telephone, QString date_naissance,
            QString adresse, float salaire);

    bool ajouter();
    bool modifier();
    bool supprimer(int id);

    QString lastError() const { return m_lastError; }

private:
    int id;
    QString nom, prenom, poste, fonction, genre;
    QString email, telephone, date_naissance, adresse;
    float salaire;
    QString m_lastError;
};

#endif

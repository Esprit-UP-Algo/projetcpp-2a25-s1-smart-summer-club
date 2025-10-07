#ifndef ABONNE_H
#define ABONNE_H
#include<QString>

class abonne
{
public:
    void setID(QString n);
    void setNom(QString n);
    void setPrenom(QString n);
    void setdatedenaissance(QString n);
    void setAdresse(QString n);
    void setNumerodetelephone(QString n);
    void setEmail(QString n);
    QString get_ID();
    QString get_Nom();
    QString get_Prenom();
    QString get_datedenaissance();
    QString get_Adresse();
    QString get_Numerodetelephone();
    QString get_Email();
    abonne();
private:
    QString ID,Nom,Prenom,datedenaissance,Adresse,Numerodetelephone,Email;
};

#endif // ABONNE_H

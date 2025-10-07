#include "abonne.h"

abonne::abonne() {
    ID="";
    Nom="";
    Prenom="";
    datedenaissance="";
    Adresse="";
    Numerodetelephone="";
    Email="";
}
void abonne::setID(QString n){ID=n;}
void abonne::setNom(QString n){Nom=n;}
void abonne::setPrenom(QString n){Prenom=n;}
void abonne::setdatedenaissance(QString n){datedenaissance=n;}
void abonne::setAdresse(QString n){Adresse=n;}
void abonne::setNumerodetelephone(QString n){Numerodetelephone=n;}
void abonne::setEmail(QString n){Email=n;}

QString abonne::get_ID(){return ID;}
QString abonne::get_Nom(){return Nom;}
QString abonne::get_Prenom(){return Prenom;}
QString abonne::get_datedenaissance(){return datedenaissance;}
QString abonne::get_Adresse(){return Adresse; }
QString abonne::get_Numerodetelephone(){return Numerodetelephone;}
QString abonne::get_Email(){return Email;}


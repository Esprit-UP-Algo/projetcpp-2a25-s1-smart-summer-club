#ifndef ABONNEDAO_H
#define ABONNEDAO_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QSqlQuery>
#include "abonne.h"

class AbonneDAO : public QObject
{
    Q_OBJECT

public:
    explicit AbonneDAO(QObject* parent = nullptr);  // Constructeur avec paramètre

    // CRUD operations
    bool create(Abonne* abonne);
    Abonne* read(int id);
    QList<Abonne*> readAll();
    bool update(Abonne* abonne);
    bool remove(int id);

    // Search operations
    QList<Abonne*> searchByNom(const QString& nom);
    QList<Abonne*> searchByPrenom(const QString& prenom);
    QList<Abonne*> searchByNomComplet(const QString& nomComplet);
    QList<Abonne*> searchByTelephone(const QString& telephone);

    // Statistics
    int count();
    QMap<QString, int> countByTrancheAge();

private:
    Abonne* abonneFromQuery(const QSqlQuery& query);
};

#endif // ABONNEDAO_H

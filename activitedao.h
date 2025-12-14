#ifndef ACTIVITEDAO_H
#define ACTIVITEDAO_H
#include "Activite.h"

#include <QObject>
#include <QList>
#include <QSqlQuery>

class ActiviteDAO : public QObject
{
    Q_OBJECT

public:
    explicit ActiviteDAO(QObject* parent = nullptr);

    // CRUD operations
    bool create(Activite* activite);
    Activite* read(int id);
    QList<Activite*> readAll();
    bool update(Activite* activite);
    bool remove(int id);

    // Search operations
    QList<Activite*> searchByNom(const QString& nom);
    QList<Activite*> searchByLieu(const QString& lieu);

    // Statistics
    int count();
    int countParticipants(int idActivite);
    bool isFull(int idActivite);

private:
    Activite* activiteFromQuery(const QSqlQuery& query);
};

#endif // ACTIVITEDAO_H

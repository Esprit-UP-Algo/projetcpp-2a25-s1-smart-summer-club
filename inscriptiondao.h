#ifndef INSCRIPTIONDAO_H
#define INSCRIPTIONDAO_H

#include <QObject>
#include <QList>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include "inscription.h"

class InscriptionDAO : public QObject
{
    Q_OBJECT

public:
    explicit InscriptionDAO(QObject* parent = nullptr);

    // CRUD operations
    bool create(Inscription* inscription);
    Inscription* read(int id);
    QList<Inscription*> readAll();
    bool update(Inscription* inscription);
    bool remove(int id);

    // Search operations
    QList<Inscription*> searchByAbonne(int idAbonne);
    QList<Inscription*> searchByActivite(int idActivite);
    QList<Inscription*> searchByDate(const QDate& date);
    QList<Inscription*> searchByStatut(const QString& statut);
    QList<Inscription*> searchByNomAbonne(const QString& nom);

    // Validation operations
    bool validateInscription(int idInscription);
    bool cancelInscription(int idInscription);
    bool markAsPaid(int idInscription);

    // Statistics
    int count();
    int countByStatut(const QString& statut);
    double totalRevenue();
    double revenueByDateRange(const QDate& start, const QDate& end);
    QMap<QString, int> countByActivite();
    QMap<QString, int> countByStatutDistribution();

    // Dashboard statistics
    int getTotalInscriptions();
    double getGrowthRate(const QDate& start, const QDate& end);
    double getConversionRate();

private:
    Inscription* inscriptionFromQuery(const QSqlQuery& query);
};

#endif // INSCRIPTIONDAO_H

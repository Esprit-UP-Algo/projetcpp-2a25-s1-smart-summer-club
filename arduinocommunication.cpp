#include "arduinocommunication.h"

ArduinoCommunication::ArduinoCommunication(QObject *parent) : QObject(parent)
{
    qDebug() << "ArduinoCommunication initialisé (mode simulation)";
    logToFile("=== Communication Arduino démarrée ===");
}

ArduinoCommunication::~ArduinoCommunication()
{
    logToFile("=== Communication Arduino arrêtée ===");
}

void ArduinoCommunication::sendMessage(const QString &message, int line)
{
    QString log = QString("[LCD] Ligne %1: %2").arg(line).arg(message);
    qDebug() << log;
    logToFile(log);
}

void ArduinoCommunication::clearDisplay()
{
    qDebug() << "[LCD] Effacement de l'écran";
    logToFile("[LCD] Écran effacé");
}

void ArduinoCommunication::logToFile(const QString &message)
{
    QFile file("lcd_simulation.log");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") 
               << " - " << message << "\n";
        file.close();
    }
}
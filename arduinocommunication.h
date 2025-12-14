#ifndef ARDUINOCOMMUNICATION_H
#define ARDUINOCOMMUNICATION_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

class ArduinoCommunication : public QObject
{
    Q_OBJECT

public:
    explicit ArduinoCommunication(QObject *parent = nullptr);
    ~ArduinoCommunication();

    void sendMessage(const QString &message, int line = 0);
    void clearDisplay();

private:
    void logToFile(const QString &message);
};

#endif // ARDUINOCOMMUNICATION_H
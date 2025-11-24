#ifndef SMTP_H
#define SMTP_H

#include <QObject>
#include <QSslSocket>
#include <QAbstractSocket>

class Smtp : public QObject
{
    Q_OBJECT
public:
    Smtp(const QString &user,
         const QString &password,
         const QString &host,
         int port = 465,
         bool useSsl = true);

    void sendMail(const QString &from,
                  const QString &to,
                  const QString &subject,
                  const QString &body);

signals:
    void mailSent(bool success, const QString &errorString = QString());

private slots:
    void readyRead();
    void connected();
    void errorOccurred(QAbstractSocket::SocketError socketError);

private:
    QString user;
    QString password;
    QString host;
    int port;
    bool useSsl;

    QString from;
    QString to;
    QString subject;
    QString body;

    QSslSocket *socket;
    int state;
};

#endif // SMTP_H

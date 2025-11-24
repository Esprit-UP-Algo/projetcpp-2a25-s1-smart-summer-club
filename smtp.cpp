#include "smtp.h"
#include <QDebug>
#include <QTextStream>
#include <QByteArray>
#include <QCoreApplication>

Smtp::Smtp(const QString &user,
           const QString &password,
           const QString &host,
           int port,
           bool useSsl)
    : user(user),
    password(password),
    host(host),
    port(port),
    useSsl(useSsl),
    socket(new QSslSocket(this)),
    state(0)
{
    connect(socket, &QSslSocket::readyRead, this, &Smtp::readyRead);
    connect(socket, &QSslSocket::connected, this, &Smtp::connected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QSslSocket::errorOccurred),
            this, &Smtp::errorOccurred);
}

void Smtp::sendMail(const QString &from,
                    const QString &to,
                    const QString &subject,
                    const QString &body)
{
    this->from = from;
    this->to = to;
    this->subject = subject;
    this->body = body;
    state = 0;

    if (useSsl) {
        socket->connectToHostEncrypted(host, port);
    } else {
        socket->connectToHost(host, port);
    }
}

void Smtp::connected()
{
    // Quand connecté, on attend le message du serveur dans readyRead()
}

void Smtp::readyRead()
{
    QByteArray response = socket->readAll();
    qDebug() << "SMTP Response:" << response;

    // Très simple machine à états
    if (response.startsWith("220") && state == 0) {
        // 220 = Service ready
        socket->write("EHLO localhost\r\n");
        state = 1;
    } else if (response.startsWith("250") && state == 1) {
        // 250 = OK
        socket->write("AUTH LOGIN\r\n");
        state = 2;
    } else if (response.startsWith("334") && state == 2) {
        // 334 demande username (base64)
        socket->write(user.toUtf8().toBase64() + "\r\n");
        state = 3;
    } else if (response.startsWith("334") && state == 3) {
        // 334 demande password
        socket->write(password.toUtf8().toBase64() + "\r\n");
        state = 4;
    } else if (response.startsWith("235") && state == 4) {
        // 235 = Auth successful
        socket->write("MAIL FROM:<" + from.toUtf8() + ">\r\n");
        state = 5;
    } else if (response.startsWith("250") && state == 5) {
        socket->write("RCPT TO:<" + to.toUtf8() + ">\r\n");
        state = 6;
    } else if (response.startsWith("250") && state == 6) {
        socket->write("DATA\r\n");
        state = 7;
    } else if (response.startsWith("354") && state == 7) {
        QByteArray data;
        data.append("From: <" + from.toUtf8() + ">\r\n");
        data.append("To: <" + to.toUtf8() + ">\r\n");
        data.append("Subject: " + subject.toUtf8() + "\r\n");
        data.append("Content-Type: text/plain; charset=\"utf-8\"\r\n");
        data.append("\r\n");
        data.append(body.toUtf8());
        data.append("\r\n.\r\n");

        socket->write(data);
        state = 8;
    } else if (response.startsWith("250") && state == 8) {
        socket->write("QUIT\r\n");
        emit mailSent(true);
        state = 9;
    } else if (state == 9) {
        socket->disconnectFromHost();
    }
}

void Smtp::errorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    emit mailSent(false, socket->errorString());
}

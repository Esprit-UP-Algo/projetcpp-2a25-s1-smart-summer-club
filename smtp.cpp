#include "smtp.h"

Smtp::Smtp(const QString &user, const QString &pass, const QString &host, qint16 port, int timeout)
{
    socket = new QSslSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorReceived(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    this->user = user;
    this->pass = pass;
    this->host = host;
    this->port = port;
    this->timeout = timeout;
}

void Smtp::sendMail(const QString &from, const QString &to, const QString &subject, const QString &body, QStringList files)
{
    message = "To: " + to + "\n";
    message.append("From: " + from + "\n");
    message.append("Subject: " + subject + "\n");

    message.append("MIME-Version: 1.0\n");
    message.append("Content-Type: multipart/mixed; boundary=frontier\n\n");

    message.append("--frontier\n");
    message.append("Content-Type: text/plain\n\n");
    message.append(body + "\n\n");

    if (!files.isEmpty())
    {
        foreach (QString filePath, files)
        {
            QFile file(filePath);
            if (!file.open(QIODevice::ReadOnly))
            {
                qDebug("Couldn't open the file");
                return;
            }

            QByteArray bytes = file.readAll();

            message.append("--frontier\n");
            message.append("Content-Type: application/octet-stream\nContent-Disposition: attachment; filename=" + QFileInfo(file.fileName()).fileName() + ";\nContent-Transfer-Encoding: base64\n\n");
            message.append(bytes.toBase64());
            message.append("\n");
        }
    }

    message.append("--frontier--\n");

    message.replace("\n", "\r\n");
    message.replace("\r\n.\r\n", "\r\n..\r\n");

    this->from = from;
    rcpt = to;

    state = Init;

    // SSL direct → NO STARTTLS
    socket->connectToHostEncrypted("smtp.gmail.com", 465);

    if (!socket->waitForConnected(timeout))
        qDebug() << "send_mail " << socket->errorString();

    t = new QTextStream(socket);
}

Smtp::~Smtp()
{
    delete t;
    delete socket;
}

void Smtp::stateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "stateChanged " << socketState;
}

void Smtp::errorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug() << "error " << socketError;
}

void Smtp::disconnected()
{
    qDebug() << "disconnected";
    qDebug() << "error " << socket->errorString();
}

void Smtp::connected()
{
    qDebug() << "Connected ";
}

void Smtp::readyRead()
{
    qDebug() << "readyRead";

    QString responseLine;
    do
    {
        responseLine = socket->readLine();
        response += responseLine;
    } while (socket->canReadLine() && responseLine[3] != ' ');

    responseLine.truncate(3);

    qDebug() << "Server response code:" << responseLine;
    qDebug() << "Server response:" << response;

    if (state == Init && responseLine == "220")
    {
        *t << "EHLO localhost\r\n";
        t->flush();
        state = HandShake;
    }
    else if (state == HandShake && responseLine == "250")
    {
        // Already encrypted → skip STARTTLS
        *t << "EHLO localhost\r\n";
        t->flush();
        state = Auth;
    }
    else if (state == Auth && responseLine == "250")
    {
        *t << "AUTH LOGIN\r\n";
        t->flush();
        state = User;
    }
    else if (state == User && responseLine == "334")
    {
        *t << user.toUtf8().toBase64() << "\r\n";
        t->flush();
        state = Pass;
    }
    else if (state == Pass && responseLine == "334")
    {
        // FIX: send PASS instead of USER !
        *t << pass.toUtf8().toBase64() << "\r\n";
        t->flush();
        state = Mail;
    }
    else if (state == Mail && responseLine == "235")
    {
        *t << "MAIL FROM:<" << from << ">\r\n";
        t->flush();
        state = Rcpt;
    }
    else if (state == Rcpt && responseLine == "250")
    {
        *t << "RCPT TO:<" << rcpt << ">\r\n";
        t->flush();
        state = Data;
    }
    else if (state == Data && responseLine == "250")
    {
        *t << "DATA\r\n";
        t->flush();
        state = Body;
    }
    else if (state == Body && responseLine == "354")
    {
        *t << message << "\r\n.\r\n";
        t->flush();
        state = Quit;
    }
    else if (state == Quit && responseLine == "250")
    {
        *t << "QUIT\r\n";
        t->flush();
        emit status(tr("Message sent"));
    }
    else
    {
        state = Close;
        emit status(tr("Failed to send message"));
    }
}

#ifndef QRCODEHELPER_H
#define QRCODEHELPER_H

#include <QImage>
#include <QString>

class QrCodeHelper
{
public:
    static QImage generate(const QString& payload, int size = 256, int margin = 4);
};

#endif // QRCODEHELPER_H


#include "qrcodehelper.h"

#include <QPainter>
#include <QRectF>

#include "thirdparty/qrcodegen.hpp"

QImage QrCodeHelper::generate(const QString& payload, int size, int margin)
{
    using qrcodegen::QrCode;

    if (payload.trimmed().isEmpty()) {
        return QImage();
    }

    const QByteArray data = payload.toUtf8();
    const QrCode qr = QrCode::encodeText(data.constData(), QrCode::Ecc::QUARTILE);

    const int qrSize = qr.getSize();
    const int imageSize = size > 0 ? size : (qrSize + 2 * margin);
    QImage image(imageSize, imageSize, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setBrush(Qt::black);
    painter.setPen(Qt::NoPen);

    const double scale = static_cast<double>(imageSize - 2 * margin) / qrSize;
    for (int y = 0; y < qrSize; ++y) {
        for (int x = 0; x < qrSize; ++x) {
            if (qr.getModule(x, y)) {
                const QRectF rect(margin + x * scale, margin + y * scale, scale, scale);
                painter.drawRect(rect);
            }
        }
    }
    painter.end();

    return image;
}


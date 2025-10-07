#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Application du style fusion pour un look moderne
    a.setStyle(QStyleFactory::create("Fusion"));

    // Définition de la palette de couleurs
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(248, 249, 250));
    palette.setColor(QPalette::WindowText, Qt::black);
    palette.setColor(QPalette::Base, Qt::white);
    palette.setColor(QPalette::AlternateBase, QColor(233, 235, 239));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::black);
    palette.setColor(QPalette::Text, Qt::black);
    palette.setColor(QPalette::Button, QColor(52, 152, 219));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Highlight, QColor(52, 152, 219));
    palette.setColor(QPalette::HighlightedText, Qt::white);
    a.setPalette(palette);

    MainWindow w;
    w.show();
    return a.exec();
}

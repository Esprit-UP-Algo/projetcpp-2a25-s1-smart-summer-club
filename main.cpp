#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"
#include "databasemanager.h"
#include <QFile>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Set application metadata
    app.setApplicationName("Smart Summer Club");
    app.setOrganizationName("Smart Sparks");
    app.setOrganizationDomain("smartsummer.com");
    app.setApplicationVersion("1.0.0");

    // Set application style (optional)
    app.setStyle(QStyleFactory::create("Fusion"));

    // Set application palette with summer colors
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    palette.setColor(QPalette::WindowText, QColor(0, 0, 0));
    palette.setColor(QPalette::Base, QColor(240, 248, 255));
    palette.setColor(QPalette::AlternateBase, QColor(233, 245, 255));
    palette.setColor(QPalette::ToolTipBase, QColor(255, 255, 220));
    palette.setColor(QPalette::ToolTipText, QColor(0, 0, 0));
    palette.setColor(QPalette::Text, QColor(0, 0, 0));
    palette.setColor(QPalette::Button, QColor(240, 240, 240));
    palette.setColor(QPalette::ButtonText, QColor(0, 0, 0));
    palette.setColor(QPalette::BrightText, QColor(255, 0, 0));
    palette.setColor(QPalette::Link, QColor(0, 102, 204));
    palette.setColor(QPalette::Highlight, QColor(255, 102, 0)); // Orange from charter
    palette.setColor(QPalette::HighlightedText, QColor(255, 255, 255));
    app.setPalette(palette);

    // Initialize database connection
    DatabaseManager& dbManager = DatabaseManager::getInstance();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Connexion Base de Données");
    msgBox.setText("Connexion à la base de données Oracle...");
    msgBox.setStandardButtons(QMessageBox::NoButton);
    msgBox.show();
    QApplication::processEvents();

    if (!dbManager.connect()) {
        msgBox.hide();
        QMessageBox::critical(nullptr, "Erreur de connexion",
                              "Impossible de se connecter à la base de données Oracle.\n\n"
                              "Détails :\n"
                              "- Vérifiez que Oracle XE 11g est installé et démarré\n"
                              "- Vérifiez les identifiants de connexion\n"
                              "- Vérifiez que le service Oracle est en cours d'exécution\n\n"
                              "L'application va maintenant se fermer.");
        return 1;
    }

    msgBox.hide();
    QMessageBox::information(nullptr, "Connexion réussie",
                             "Connexion à la base de données établie avec succès!");

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}

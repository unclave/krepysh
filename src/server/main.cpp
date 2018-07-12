#include "server.h"
#include <QApplication>
#include <QTextCodec>
#include <QSystemTrayIcon>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(
                    0,
                    QApplication::applicationName(),
                    "Couldn't detect any system tray on this platform.");
    }

    Server server;
    server.show();

    return a.exec();
}

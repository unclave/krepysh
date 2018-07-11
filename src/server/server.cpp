#include "server.h"
#include "ui_server.h"

#include <QApplication>
#include <QSettings>
#include <QPainter>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDesktopWidget>
#include <qmath.h>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QDebug>
//#include <QCoreApplication>


Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon("://images/tray.png"));
    trayIcon->setToolTip("Tray program");

    QMenu *menu = new QMenu(this);
    QAction *oneAction = new QAction(trUtf8("1"), this);
    QAction *twoAction = new QAction(trUtf8("2"), this);
    QAction *threeAction = new QAction(trUtf8("3"), this);
    QAction *quitAction = new QAction(trUtf8("Выход"), this);

    connect(oneAction, SIGNAL(triggered()), this, SLOT (onOneAction()));
    connect(twoAction, SIGNAL(triggered()), this, SLOT (onTwoAction()));
    connect(threeAction, SIGNAL(triggered()), this, SLOT(onThreeAction()));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    menu->addAction(oneAction);
    menu->addAction(twoAction);
    menu->addAction(threeAction);
    menu->addAction(quitAction);

    trayIcon->setContextMenu(menu);
    trayIcon->show();
}

Server::~Server()
{
    delete ui;
}

void Server::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPosition_ = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void Server::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPoint pos = event->globalPos() - dragPosition_;
        move(pos);
        static QPoint oldPos = pos;
        if (pos.x() > oldPos.x()) {
            direction_ = toRight;
            oldPos = pos;

        } else if (pos.x() < oldPos.x()) {
            direction_ = toLeft;
            oldPos = pos;
        }

        event->accept();
    }
}

void Server::onOneAction()
{
    qDebug() << Q_FUNC_INFO;
}

void Server::onTwoAction()
{
    qDebug() << Q_FUNC_INFO;
}

void Server::onThreeAction()
{
    qDebug() << Q_FUNC_INFO;
}

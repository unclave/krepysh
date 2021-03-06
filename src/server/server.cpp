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
#include <QVariant>
#include <stdlib.h>
#include <QCoreApplication>
#include <QSharedMemory>


Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    QSettings settings("./../server.conf", QSettings::IniFormat);
    x_ = settings.value("Window/x_", 150).toInt();
    y_ = settings.value("Window/y_", 150).toInt();

    //fileMenu
    fileMenuItems_["Open"] = 0;
    fileMenuItems_["Save"] = 1;
    fileMenuItems_["Close"] = 2;

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon("://images/tray.png"));
    trayIcon->setToolTip("Tray program");

    QList<QAction *> fileMenuActions;
    QMap <QString, int>::const_iterator i = fileMenuItems_.constBegin();
    while(i != fileMenuItems_.constEnd()) {
        QAction *act = new QAction(i.key(), this);
        act->setData(QVariant(i.value()));
        fileMenuActions << act;
        ++i;
    }

    QMenu *fileMenu = new QMenu ("File", this);
    fileMenu->addActions(fileMenuActions);

    signalMapper_ = new QSignalMapper(this);

    Q_FOREACH(QAction *action, fileMenuActions) {
        connect (action, SIGNAL(triggered()), signalMapper_, SLOT(map()));
        signalMapper_->setMapping(action, action);
    }

    connect(signalMapper_,
            SIGNAL(mapped(QObject *)), this,
            SLOT(onMappedReceived(QObject*)));

    move(x_,y_);
    trayIcon->setContextMenu(fileMenu);
    trayIcon->show();
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

void Server::onMappedReceived(QObject *object)
{
    int value;
    value = static_cast<QAction *>(object)->data().toInt();
    if (value == fileMenuItems_.value("Save"))
    {
        qDebug() << "Save";
    }
    if (value == fileMenuItems_.value("Open"))
    {
        qDebug() << "Open";
    }
    if (value == fileMenuItems_.value("Close"))
    {
        qApp->exit();
    }
}

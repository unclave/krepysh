#define SERVER_H

#include <QWidget>
#include <QTimer>
#include <QList>
#include <QPoint>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QPair>
#include <QPixmap>
#include <QBitmap>
#include <QSystemTrayIcon>

namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::Server *ui;
    QSystemTrayIcon *trayIcon;
    enum MovementDirection { toLeft, toRight };
    QPoint dragPosition_;
    MovementDirection direction_;

private slots:
   void onOneAction();
   void onTwoAction();
   void onThreeAction();
};



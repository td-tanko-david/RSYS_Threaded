#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QTimer>
#include "socketlistener.h"

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);
private:
    void update();

    QTimer *m_updateTimer;
    SocketListener *m_socketListener;
signals:
    void add_message(QString msg);
public slots:
};

#endif // RECEIVER_H

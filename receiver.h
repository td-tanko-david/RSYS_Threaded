#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QTimer>
#include "socketlistener.h"
#include <thread>

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);
private:
    // Called every second by a QTimer timeout.
    // Calls Receiver::update.
    void update_helper();
    // Calls SocketListener::get_messages to provide
    // the messages to be displayed.
    void update();
    QTimer *m_updateTimer;

    // SocketListener instance for accepting UDP datagrams.
    SocketListener *m_socketListener;
signals:
    // Emitted when Receiver::update finds a message to be shown.
    void add_message(QString msg);
public slots:
};

#endif // RECEIVER_H

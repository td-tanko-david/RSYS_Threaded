#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include "socketlistener.h"

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);
private:
    // Called every second by a QTimer timeout.
    void update();
    QTimer *m_updateTimer;

    // SocketListener instance for accepting UDP datagrams.
    SocketListener *m_socketListener;
    // The thread for the SocketListener to live in.
    QThread *m_socketListenerThread;
signals:
    // Emitted when Receiver::update finds a message to be shown.
    void add_message(QString msg);
public slots:
};

#endif // RECEIVER_H

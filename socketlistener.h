#ifndef SOCKETLISTENER_H
#define SOCKETLISTENER_H

#include <QObject>
#include <QUdpSocket>
//#include "mainwindow.h"
#include <QMutex>

class SocketListener : public QObject
{
    Q_OBJECT
public:
    SocketListener(QObject *parent = nullptr);
    QString get_messages();
private:
    QUdpSocket *m_socket;
    std::vector<QString> m_receivedMessages;

    QMutex mutex;

    void process();
};

#endif // SOCKETLISTENER_H

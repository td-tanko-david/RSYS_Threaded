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
<<<<<<< HEAD
    QUdpSocket *m_sock;
    void process();
    void update();

    std::vector<QString> m_receivedMessages;

    QThread *m_updateThread;
    QThread *m_processThread;
    QTimer *m_updateTimer;
=======
    void update();

    QTimer *m_updateTimer;
    SocketListener *m_socketListener;
    QThread *m_socketListenerThread;
>>>>>>> dev2
signals:
    void add_message(QString msg);
public slots:
};

#endif // RECEIVER_H

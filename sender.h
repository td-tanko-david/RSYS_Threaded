#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QUdpSocket>
#include <iostream>

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = nullptr);
private:
    // QUdpSocket used for sending datagrams.
    QUdpSocket *m_sock;
signals:
public slots:
    // Connected to
    // - a QPushButton widget,
    // - a MyTextEdit widget.
    // Sends the message msg through the socket.
    void send_message(QString msg);
};

#endif // SENDER_H

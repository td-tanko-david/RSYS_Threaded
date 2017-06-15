#include "sender.h"

Sender::Sender(QObject *parent) : QObject(parent)
{
    // Creates a socket through which datagrams will be sent.
    this->m_sock = new QUdpSocket(this);
}

// Slot function which sends the message msg through the socket.
void Sender::send_message(QString msg){
    QByteArray data = msg.toUtf8();
    this->m_sock->writeDatagram(data,QHostAddress::LocalHost,64321);
}

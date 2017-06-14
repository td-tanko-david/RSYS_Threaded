#include "sender.h"

Sender::Sender(QObject *parent) : QObject(parent)
{
    this->m_sock = new QUdpSocket(this);
}

void Sender::send_message(QString msg){
    QByteArray data = msg.toUtf8();
    this->m_sock->writeDatagram(data,QHostAddress::LocalHost,64321);
}

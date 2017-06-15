#include "socketlistener.h"

SocketListener::SocketListener(QObject *parent) : QObject(parent)
{
    // Create the socket, bind it to an address and port
    // to enable receiving and connect the signal that is
    // emitted when a packet is received to a processing
    // function.
    this->m_socket = new QUdpSocket(this);
    this->m_socket->bind(QHostAddress::LocalHost,64321);
    connect(this->m_socket,
            &QUdpSocket::readyRead,
            this,
            &SocketListener::process
            );
}

// Gets every received datagram from the socket
// and stores the data in a vector.
void SocketListener::process(){
    if (this->mutex.tryLock()){
       while (this->m_socket->hasPendingDatagrams()){
            QByteArray datagram;
            datagram.resize(this->m_socket->pendingDatagramSize());
            this->m_socket->readDatagram(datagram.data(), datagram.size());
            this->m_receivedMessages.push_back(QString(datagram.data()));
        }
        this->mutex.unlock();
    }
}

// Gets every message from the vector of messages
// and sends them through an emitted signal.
// Every message sent is removed from the vector.
// This function is called by the Receiver::update method.
QString SocketListener::get_messages(){
    QString messages;
    if (this->mutex.tryLock()){
        while (!this->m_receivedMessages.empty()){
            messages += this->m_receivedMessages.back();
            if (this->m_receivedMessages.size()>1)
                 messages += "\n";
            this->m_receivedMessages.pop_back();
        }
        this->mutex.unlock();
    }
    return messages;
}

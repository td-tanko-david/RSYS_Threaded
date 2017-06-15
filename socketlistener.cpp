#include "socketlistener.h"
#include <QThread>
#include <iostream>

SocketListener::SocketListener(QObject *parent) : QThread(parent)
{
    // Create the socket and bind it to an address and port
    // to enable receiving packets.
    this->m_socket = new QUdpSocket(this);
    this->m_socket->bind(QHostAddress::LocalHost,64321);
}

void SocketListener::run(){
    // Connect the signal that is emitted when
    // a packet is received to a processing function.
    connect(this->m_socket,
            &QUdpSocket::readyRead,
            this,
            &SocketListener::process
            );
}

// Gets every received datagram from the socket
// and stores the data in a vector.
void SocketListener::process(){
    std::cout << "PROCESS " << this->thread()->currentThreadId() << std::endl;
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
    std::cout << "GET " << this->thread()->currentThreadId() << std::endl;
    QString messages;
    if (this->mutex.tryLock()){
        while (!this->m_receivedMessages.empty()){
            messages += this->m_receivedMessages.front();
            if (this->m_receivedMessages.size()>1)
                 messages += "\n";
            this->m_receivedMessages.erase(this->m_receivedMessages.begin());
        }
        this->mutex.unlock();
    }
    return messages;
}

#include "receiver.h"
#include <iostream>
#include <mainwindow.h>

Receiver::Receiver(QObject *parent) : QObject(parent)
{
    // Create the socket, bind it to an address and port
    // to enable receiving and connect the signal that is
    // emitted when a packet is received to a processing
    // function
    this->m_sock = new QUdpSocket(this);
    this->m_sock->bind(QHostAddress::LocalHost,64321);
    connect(this->m_sock,
            &QUdpSocket::readyRead,
            this,
            &Receiver::process
            );

    // Create a timer that calls a function every second
    // The function displays the received messages
    this->m_updateTimer = new QTimer(this);
    connect(this->m_updateTimer,
            &QTimer::timeout,
            this,
            &Receiver::update
            );
    this->m_updateTimer->start(1000);
}

// Gets every received datagram from the socket
// and stores the data in a vector
void Receiver::process(){
    MainWindow::mutex.tryLock();

    while (this->m_sock->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(this->m_sock->pendingDatagramSize());
        this->m_sock->readDatagram(datagram.data(), datagram.size());
        this->m_receivedMessages.push_back(QString(datagram.data()));
    }

    MainWindow::mutex.unlock();
}

// This function is called every second
// Gets every message from the vector of messages
// and sends them through an emitted signal.
// Every message sent is removed from the vector
void Receiver::update(){
    MainWindow::mutex.tryLock();

    while (!this->m_receivedMessages.empty()){
        emit add_message(this->m_receivedMessages.back());
        this->m_receivedMessages.pop_back();
    }

    MainWindow::mutex.unlock();
}

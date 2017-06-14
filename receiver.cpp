#include "receiver.h"
#include <iostream>
#include <mainwindow.h>

Receiver::Receiver(QObject *parent) : QObject(parent)
{
    this->m_sock = new QUdpSocket(this);
    this->m_sock->bind(QHostAddress::LocalHost,64321);

    connect(this->m_sock,
            &QUdpSocket::readyRead,
            this,
            &Receiver::process
            );

    this->m_updateTimer = new QTimer(this);

    connect(this->m_updateTimer,
            &QTimer::timeout,
            this,
            &Receiver::update
            );

    this->m_updateTimer->start(1000);
}

void Receiver::process(){
    MainWindow::mutex.lock();

    while (this->m_sock->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(this->m_sock->pendingDatagramSize());
        this->m_sock->readDatagram(datagram.data(), datagram.size());
        this->m_receivedMessages.push_back(QString(datagram.data()));
    }

    MainWindow::mutex.unlock();
}

void Receiver::update(){
    MainWindow::mutex.lock();

    while (!this->m_receivedMessages.empty()){
        emit add_message(this->m_receivedMessages.back());
        this->m_receivedMessages.pop_back();
    }

    MainWindow::mutex.unlock();
}

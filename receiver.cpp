#include "receiver.h"
#include <iostream>
#include <mainwindow.h>

Receiver::Receiver(QObject *parent) : QObject(parent)
{
    // Create the socket, bind it to an address and port
    // to enable receiving and connect the signal that is
    // emitted when a packet is received to a processing
    // function
    this->m_sock = new QUdpSocket();
    this->m_sock->bind(QHostAddress::LocalHost,64321);
    connect(this->m_sock,
            &QUdpSocket::readyRead,
            this,
            &Receiver::process,
            Qt::QueuedConnection
            );



    /*this->m_processThread = new QThread();
    this->m_processThread->start();*/
    //this->m_updateThread = new QThread();
    //this->m_updateThread->start();
    this->m_updater = new Updater();

    //connect(thread, &Updater::update_now, this, &Receiver::update_str);

    //this->m_updater->moveToThread(this->m_updateThread);
    connect(this->m_updater,
            &Updater::update_now,
            this,
            &Receiver::update_str
            );
    connect(this,
            &Receiver::msg_received,
            this->m_updater,
            &Updater::add_message
            );
    // Create a timer that calls a function every second
    // The function displays the received messages
    /*this->m_updateTimer = new QTimer(this);
    connect(this->m_updateTimer,
            &QTimer::timeout,
            this,
            &Receiver::update
            );
    this->m_updateTimer->start(1000);*/
}

// Gets every received datagram from the socket
// and stores the data in a vector
void Receiver::process(){
    // Access the vector only if the lock is acquired
    //if( MainWindow::mutex.tryLock() ){
        while (this->m_sock->hasPendingDatagrams()){
            this->m_updater->start();
            QByteArray datagram;
            datagram.resize(this->m_sock->pendingDatagramSize());
            this->m_sock->readDatagram(datagram.data(), datagram.size());
            //this->m_receivedMessages.push_back(QString(datagram.data()));
            emit msg_received(QString(datagram.data()));
        }
       // MainWindow::mutex.unlock();
    /*} else {
        std::cout << "Process cant acquire lock!" << std::endl;
    }*/
}

// This function is called every second
// Gets every message from the vector of messages
// and sends them through an emitted signal.
// Every message sent is removed from the vector
void Receiver::update(){
    this->moveToThread(this->m_updateThread);
    // Access the vector only if the lock is acquired
    if( MainWindow::mutex.tryLock() ){
        std::cout << "Update 1" << this->thread()->currentThreadId() << std::endl;
        while (!this->m_receivedMessages.empty()){
            emit add_message(this->m_receivedMessages.back());
            this->m_receivedMessages.pop_back();
        }
        MainWindow::mutex.unlock();
    } else {
        std::cout << "Update cant acquire lock!" << std::endl;
    }
}

void Receiver::update_str(QString msg){
    emit add_message(msg);
}

#include "receiver.h"
#include <iostream>

Receiver::Receiver(QObject *parent) : QObject(parent)
{
    // Create a socket listener and a thread for it to work in
    this->m_socketListener = new SocketListener();
    this->m_socketListenerThread = new QThread();
    this->m_socketListenerThread->start();
    this->m_socketListener->moveToThread(this->m_socketListenerThread);


    this->m_processThread = new QThread();
    this->m_processThread->start();
    this->m_updateThread = new QThread();
    this->m_updateThread->start();
    /*this->m_updater = new Updater();
    this->m_updater->moveToThread(this->m_updateThread);
    connect(this->m_updater,
            &Updater::update_now,
            this,
            &Receiver::update
            );*/
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

<<<<<<< HEAD
// Gets every received datagram from the socket
// and stores the data in a vector
void Receiver::process(){
    std::cout << "Process 1" << this->thread()->currentThreadId() << std::endl;
    this->moveToThread(this->m_processThread);
    std::cout << "Process 2" << this->thread()->currentThreadId() << std::endl;
    // Access the vector only if the lock is acquired
    if( MainWindow::mutex.tryLock() ){
        while (this->m_sock->hasPendingDatagrams()){
            QByteArray datagram;
            datagram.resize(this->m_sock->pendingDatagramSize());
            this->m_sock->readDatagram(datagram.data(), datagram.size());
            this->m_receivedMessages.push_back(QString(datagram.data()));
        }
        MainWindow::mutex.unlock();
    }
}

// This function is called every second
// Gets every message from the vector of messages
// and sends them through an emitted signal.
// Every message sent is removed from the vector
void Receiver::update(){
    std::cout << "Update 1" << this->thread()->currentThreadId() << std::endl;
    this->moveToThread(this->m_updateThread);
    std::cout << "Update 2" << this->thread()->currentThreadId() << std::endl;
    // Access the vector only if the lock is acquired
    if( MainWindow::mutex.tryLock() ){
        while (!this->m_receivedMessages.empty()){
            emit add_message(this->m_receivedMessages.back());
            this->m_receivedMessages.pop_back();
        }
        MainWindow::mutex.unlock();
    }
=======
// This function is called every second.
// Calls SocketListener::get_messages to get all the
// received messages. Those messages, if they are not
// an empty string, are sent forward through Receiver::add_message
void Receiver::update(){
    QString msg = this->m_socketListener->get_messages();
    if (msg!="")
        emit add_message(msg);
>>>>>>> dev2
}

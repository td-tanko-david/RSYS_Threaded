#include "receiver.h"

Receiver::Receiver(QObject *parent) : QObject(parent)
{
    // Create a socket listener and a thread for it to work in
    this->m_socketListener = new SocketListener();
    this->m_socketListenerThread = new QThread();
    this->m_socketListenerThread->start();
    this->m_socketListener->moveToThread(this->m_socketListenerThread);

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

// This function is called every second.
// Calls SocketListener::get_messages to get all the
// received messages. Those messages, if they are not
// an empty string, are sent forward through Receiver::add_message
void Receiver::update(){
    QString msg = this->m_socketListener->get_messages();
    if (msg!="")
        emit add_message(msg);
}

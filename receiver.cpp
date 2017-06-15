#include "receiver.h"
#include <iostream>

Receiver::Receiver(QObject *parent) : QObject(parent)
{

    this->m_socketListener = new SocketListener(this);

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

// This function is called every second
// Gets every message from the vector of messages
// and sends them through an emitted signal.
// Every message sent is removed from the vector
void Receiver::update(){
    QString msg = this->m_socketListener->get_messages();
    if (msg!="")
        emit add_message(msg);
}

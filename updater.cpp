#include "updater.h"
#include <iostream>
#include <mainwindow.h>

Updater::Updater(QObject *parent) : QObject(parent)
{
    // Create a timer that calls a function every second
    // The function displays the received messages
    this->m_updateTimer = new QTimer(this);
    connect(this->m_updateTimer,
            &QTimer::timeout,
            this,
            &Updater::update
            );
    this->m_updateTimer->start(1000);
}

// This function is called every second
// Gets every message from the vector of messages
// and sends them through an emitted signal.
// Every message sent is removed from the vector
void Updater::update(){
    emit update_now();
    std::cout << "Update now" << std::endl;
}

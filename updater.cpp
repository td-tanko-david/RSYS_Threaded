#include "updater.h"
#include <iostream>

Updater::Updater(QObject *parent) : QThread(parent)
{
    this->m_abort = false;
}

Updater::~Updater()
{
    this->mutex.lock();
    std::cout << "Upd destroyed" << std::endl;
    this->m_abort = true;
    this->mutex.unlock();

    wait();
}

void Updater::run()
{
    this->mutex.lock();
    std::cout << "Updater running" << std::endl;
    while (!this->m_receivedMessages.empty()){
        emit update_now(this->m_receivedMessages.back());
        this->m_receivedMessages.pop_back();
    }
    if (this->m_abort)
        return;
    this->mutex.unlock();
    //msleep(1);
}

void Updater::add_message(QString msg){
    this->mutex.lock();
    std::cout << "Message in updater is " << msg.toStdString() << std::endl;
    this->m_receivedMessages.push_back(msg);
    std::cout << "Message in updater is " << msg.toStdString() << std::endl;
    this->mutex.unlock();
}

void Updater::stopProcess()
{
    this->mutex.lock();
    m_abort = true;
    this->mutex.unlock();
}

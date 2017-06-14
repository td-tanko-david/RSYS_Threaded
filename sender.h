#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QUdpSocket>
#include <iostream>

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = nullptr);
    void send_message(QString msg);
private:
    QUdpSocket *m_sock;
signals:

public slots:
};

#endif // SENDER_H

#ifndef SOCKETLISTENER_H
#define SOCKETLISTENER_H

#include <QObject>
#include <QUdpSocket>
#include <QMutex>

class SocketListener : public QObject
{
    Q_OBJECT
public:
    SocketListener(QObject *parent = nullptr);
    // This function can be called to get all the messages
    // from the m_receivedMessages vector.
    // The vector will be emptied.
    QString get_messages();
private:
    // QUdpSocket used to receive datagrams.
    QUdpSocket *m_socket;

    // Stores the received datagrams
    std::vector<QString> m_receivedMessages;
    QMutex mutex;
private slots:
    // Connected to QUdpSocket::readyRead signal.
    // Reads all the messages from the socket.
    void process();
};

#endif // SOCKETLISTENER_H

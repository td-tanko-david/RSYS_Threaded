#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QMutex>

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);
private:
    QUdpSocket *m_sock;
    void update();
    void process();

    QMutex m_mutex;
    QTimer *m_updateTimer;
    std::vector<QString> m_receivedMessages;
signals:
    void add_message(QString msg);
public slots:
};

#endif // RECEIVER_H

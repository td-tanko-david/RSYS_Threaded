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
    void process();
    void update();

    std::vector<QString> m_receivedMessages;

    QThread *m_updateThread;
    QThread *m_processThread;
    QTimer *m_updateTimer;
signals:
    void add_message(QString msg);
public slots:
};

#endif // RECEIVER_H

#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QMutex>
#include <QThread>

class Updater : public QThread
{
    Q_OBJECT
public:
    Updater(QObject *parent = 0);
    ~Updater();

    void processImage(const QImage &image);

signals:
    void update_now(const QString &data);

public slots:
    void stopProcess();
    void add_message(QString msg);

protected:
    void run();

private:
    bool m_abort;
    QMutex mutex;
    std::vector<QString> m_receivedMessages;
};

#endif // UPDATER_H

#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QTimer>
#include <QMutex>

class Updater : public QObject
{
    Q_OBJECT
public:
    explicit Updater(QObject *parent = nullptr);
private:
    void update();
    QTimer *m_updateTimer;
signals:
    void update_now();
public slots:
};

#endif // UPDATER_H

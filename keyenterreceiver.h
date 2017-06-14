#ifndef KEYENTERRECEIVER_H
#define KEYENTERRECEIVER_H

#include <QObject>

class keyEnterReceiver : public QObject
{
    Q_OBJECT
public:
    explicit keyEnterReceiver(QObject *parent = nullptr);

signals:
    void enter_pressed();
public slots:
protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // KEYENTERRECEIVER_H

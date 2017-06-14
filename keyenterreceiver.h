#ifndef KEYENTERRECEIVER_H
#define KEYENTERRECEIVER_H

#include <QObject>

class keyEnterReceiver : public QObject
{
    Q_OBJECT
public:
    explicit keyEnterReceiver(QObject *parent = nullptr);

signals:
    // Signal emitted when the Enter key is pressed
    void enter_pressed();
public slots:
protected:
    // A filter which handles the Enter key being pressed
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // KEYENTERRECEIVER_H

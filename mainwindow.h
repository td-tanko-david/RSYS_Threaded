#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>
#include "receiver.h"
#include "sender.h"
#include <QThread>
#include "mytextedit.h"
#include "keyenterreceiver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString mode="c", QWidget *parent = 0);
    ~MainWindow();
    void update_messages();
    static QMutex mutex;
private:
    Ui::MainWindow *ui;

    QThread *m_senderThread;
    QThread *m_receiverThread;

    Receiver *m_receiver;
    Sender *m_sender;

    keyEnterReceiver *m_key;
};

#endif // MAINWINDOW_H

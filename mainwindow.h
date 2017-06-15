#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "sender.h"
#include "mytextedit.h"
#include "keyenterreceiver.h"
#include "receiver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString mode="c", QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

    // The thread the server runs in
    QThread *m_senderThread;
    // The thred the client runs in
    QThread *m_receiverThread;

    // Server object
    Receiver *m_receiver;
    // Client object
    Sender *m_sender;

    // Allows sending messages from QTextEdit implementation
    // by pressing the enter key using an eventFiler.
    keyEnterReceiver *m_key;
};

#endif // MAINWINDOW_H

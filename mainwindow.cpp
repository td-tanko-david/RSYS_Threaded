#include "mainwindow.h"
#include "ui_mainwindow.h"

QMutex MainWindow::mutex;

MainWindow::MainWindow(QString mode,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    if(mode=="s"){
        ui->label_modeLabel->setText("Server mode");
        ui->textEdit_messageInput->setReadOnly(true);
        ui->button_sendMessage->setEnabled(false);

        QThread *thread_rcv = new QThread();
        thread_rcv->start();
        this->m_receiver = new Receiver();
        this->m_receiver->moveToThread(thread_rcv);

        connect(this->m_receiver,
                &Receiver::add_message,
                ui->window_displayWindow,
                &QTextBrowser::append,
                Qt::QueuedConnection
                );

    } else {
        ui->label_modeLabel->setText("Client mode");
        ui->textEdit_messageInput->setReadOnly(false);
        ui->button_sendMessage->setEnabled(true);
        this->m_key = new keyEnterReceiver();
        ui->textEdit_messageInput->installEventFilter(this->m_key);

        connect(this->m_key,
                &keyEnterReceiver::enter_pressed,
                ui->textEdit_messageInput,
                &MyTextEdit::init_send
                    );

        QThread *thread_snd = new QThread();
        thread_snd->start();

        this->m_sender = new Sender();
        this->m_sender->moveToThread(thread_snd);

        connect(ui->button_sendMessage,
                &QPushButton::clicked,
                ui->textEdit_messageInput,
                &MyTextEdit::init_send,
                Qt::QueuedConnection
                );
        connect(ui->textEdit_messageInput,
                &MyTextEdit::send_msg,
                this->m_sender,
                &Sender::send_message,
                Qt::QueuedConnection
                );
        connect(ui->textEdit_messageInput,
                &MyTextEdit::send_msg,
                ui->window_displayWindow,
                &QTextBrowser::append,
                Qt::QueuedConnection
                );
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

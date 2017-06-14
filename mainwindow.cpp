#include "mainwindow.h"
#include "ui_mainwindow.h"

QMutex MainWindow::mutex;

MainWindow::MainWindow(QString mode,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(mode=="s"){
        // Set up server mode
        ui->label_modeLabel->setText("Server mode");
        ui->textEdit_messageInput->setReadOnly(true);
        ui->button_sendMessage->setEnabled(false);

        // Start the server thread
        QThread *thread_rcv = new QThread();
        thread_rcv->start();
        this->m_receiver = new Receiver();
        this->m_receiver->moveToThread(thread_rcv);

        // Appends a message from the server to the displaying element
        // The server checks for new messages every second
        connect(this->m_receiver,
                &Receiver::add_message,
                ui->window_displayWindow,
                &QTextBrowser::append,
                Qt::QueuedConnection
                );

    } else {
        // Set up client mode
        ui->label_modeLabel->setText("Client mode");
        ui->textEdit_messageInput->setReadOnly(false);
        ui->button_sendMessage->setEnabled(true);
        // Set up a filter which handles the enter key being pressed
        // Emits the enter_pressed signal
        this->m_key = new keyEnterReceiver();
        ui->textEdit_messageInput->installEventFilter(this->m_key);
        connect(this->m_key,
                &keyEnterReceiver::enter_pressed,
                ui->textEdit_messageInput,
                &MyTextEdit::init_send
                );

        // Start the client thread
        QThread *thread_snd = new QThread();
        thread_snd->start();
        this->m_sender = new Sender();
        this->m_sender->moveToThread(thread_snd);

        // Send a message when the Send button is pressed
        connect(ui->button_sendMessage,
                &QPushButton::clicked,
                ui->textEdit_messageInput,
                &MyTextEdit::init_send,
                Qt::QueuedConnection
                );
        // Send a message when the enter key is pressed
        connect(ui->textEdit_messageInput,
                &MyTextEdit::send_msg,
                this->m_sender,
                &Sender::send_message,
                Qt::QueuedConnection
                );
        // Append the sent message to the display window
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

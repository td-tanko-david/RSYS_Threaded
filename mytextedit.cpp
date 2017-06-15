#include "mytextedit.h"
#include <QEvent>
#include <QKeyEvent>

MyTextEdit::MyTextEdit(QWidget *parent): QTextEdit(parent)
{
    this->m_date = new QDateTime();
}

// Sets up the message to be sent and emits a signal containing the message.
void MyTextEdit::init_send(){
    QString msgToSend = "";
    //msgToSend += this->m_date->currentDateTime().toString(Qt::SystemLocaleShortDate);
    msgToSend += this->m_date->currentDateTimeUtc().toString();
    msgToSend += ": " + this->toPlainText();
    this->setText("");
    emit send_msg(msgToSend);
}

// Solves the issue of a newline character being left in the editor
// after confirming a message send using the Enter key by ignoring it.
void MyTextEdit::keyPressEvent(QKeyEvent *e){
    if((e->key()==Qt::Key_Enter) || (e->key()==Qt::Key_Return) ){
        return;
    }
    return QTextEdit::keyPressEvent(e);
}

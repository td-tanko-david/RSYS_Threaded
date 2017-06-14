#include "mytextedit.h"
#include <QEvent>
#include <QKeyEvent>

MyTextEdit::MyTextEdit(QWidget *parent): QTextEdit(parent)
{
    this->m_date = new QDateTime();
}

void MyTextEdit::init_send(){
    QString msgToSend = "";
    msgToSend += this->m_date->currentDateTime().toString(Qt::SystemLocaleShortDate);
    msgToSend += ": " + this->toPlainText();
    this->setText("");
    emit send_msg(msgToSend);
}

void MyTextEdit::keyPressEvent(QKeyEvent *e){
    if((e->key()==Qt::Key_Enter) || (e->key()==Qt::Key_Return) ){

        //enter clicked
        return;
    }

    return QTextEdit::keyPressEvent(e);
}

#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QObject>
#include <QTextEdit>
#include <QDateTime>

class MyTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    MyTextEdit(QWidget *parent = 0);
private:
    QDateTime *m_date;
public slots:
    // Constructs a message from the contents of the superclass TextEdit
    // and emits it through the MyTextEdit::send_msg signal.
    void init_send();
signals:
    // Emitted by the MyTextEdit::init_send method.
    void send_msg(QString msg);
protected:
    // Ignores the enter key inside a MyTextEdit widget.
    virtual void keyPressEvent(QKeyEvent *e);
};

#endif // MYTEXTEDIT_H

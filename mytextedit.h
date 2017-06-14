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
    void init_send();
signals:
    void send_msg(QString msg);
protected:
    virtual void keyPressEvent(QKeyEvent *e);
};

#endif // MYTEXTEDIT_H

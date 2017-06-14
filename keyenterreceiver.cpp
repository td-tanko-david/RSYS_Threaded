#include "keyenterreceiver.h"
#include <QEvent>
#include <QKeyEvent>

keyEnterReceiver::keyEnterReceiver(QObject *parent) : QObject(parent)
{

}

bool keyEnterReceiver::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
            emit enter_pressed();
        } else {
            return QObject::eventFilter(obj, event);
        }
        return false;
    } else {
        return QObject::eventFilter(obj, event);
    }
    return false;
}

#include "lineeditshortcutkey.h"
#include<QMessageBox>
#include<QDebug>
LineEditShortcutKey::LineEditShortcutKey(QWidget *parent)
    : QLineEdit(parent)
{

}

void LineEditShortcutKey::setKey(int key)
{
    Qt::Key qkey = static_cast<Qt::Key>(key);
    if (qkey != Qt::Key_unknown)
    {
        m_key = qkey;
        setText(QKeySequence(qkey).toString());
    }
    else
    {
        m_key = Qt::Key_unknown;
        setText("无");
    }
}

int LineEditShortcutKey::getKey()
{
    return m_key;
}

void LineEditShortcutKey::setText(QString qsText)
{
    QLineEdit::setText(qsText);
}

void LineEditShortcutKey::keyPressEvent(QKeyEvent *e)
{
    int uKey = e->key();
    Qt::Key key = static_cast<Qt::Key>(uKey);
    if (key == Qt::Key_unknown)
    {
        return;
    }

    bool bModifiers = false;
    Qt::KeyboardModifiers modifiers = e->modifiers();
    if (modifiers & Qt::ShiftModifier)
    {
        uKey += Qt::SHIFT;
        bModifiers = true;
    }
    if (modifiers & Qt::ControlModifier)
    {
        uKey += Qt::CTRL;
        bModifiers = true;
    }
    if (modifiers & Qt::AltModifier)
    {
        uKey += Qt::ALT;
        bModifiers = true;
    }
    QString qsKey = QKeySequence(uKey).toString();
    bool bNum = (e->key() >= Qt::Key_0 && e->key() <= Qt::Key_9);
    bool bChar = (e->key() >= Qt::Key_A && e->key() <= Qt::Key_Z);
    if ((bNum || bChar) && bModifiers)
    {
       //除去Windows常用快捷键
       QStringList blackList;
       blackList << "CTRL+S" << "CTRL+C" << "CTRL+V" << "CTRL+A" << "CTRL+D" << "CTRL+Z" << "CTRL+X";
       if (blackList.contains(qsKey, Qt::CaseInsensitive))
       {
           return;
       }
       setText(QKeySequence(uKey).toString());
       this->setStyleSheet("color:black;");
    }else
    {
    }
}



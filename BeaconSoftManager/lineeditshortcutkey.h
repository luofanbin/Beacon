#ifndef LINEEDITSHORTCUTKEY_H
#define LINEEDITSHORTCUTKEY_H

#include <QLineEdit>
#include <QKeyEvent>
#include <QFocusEvent>
#include <QMessageBox>
class LineEditShortcutKey : public QLineEdit
{
    Q_OBJECT
public:
    LineEditShortcutKey(QWidget *parent = 0);

public:
    void setKey(int key);
    int getKey();
    void setText(QString qsText);

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    int	m_key = Qt::Key_unknown;


};

#endif // LINEEDITSHORTCUTKEY_H

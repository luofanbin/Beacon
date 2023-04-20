#include "mybutton.h"
#include <QPainter>
#include <QStyleOption>

MyButton::MyButton(QWidget *parent)
{
    this->setParent(parent);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void MyButton::paintEvent(QPaintEvent * e)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(e);
}

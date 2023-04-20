#ifndef SELECTIONBAR_H
#define SELECTIONBAR_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include "mybutton.h"

class SelectionBar : public QWidget
{
    Q_OBJECT
public:
    explicit SelectionBar(QWidget *parent = nullptr);
    void init();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPixmap backgroundPic;
    QLabel * separator;//分隔线

public:
    MyButton * smallDot;//细线
    MyButton * mediumDot;//中线
    MyButton * bigDot;//粗线
    QLabel * fontLabel;
    QComboBox * fontSize;//字体大小

    MyButton * color;//显示当前选中颜色
    MyButton * black;//黑色
    MyButton * white;//白色
    MyButton * dimgrey;//暗灰色
    MyButton * grey;//灰色
    MyButton * maroon;//褐红色
    MyButton * red;//红色
    MyButton * orange;//橙色
    MyButton * yellow;//黄色
    MyButton * green;//绿色
    MyButton * yellowgreen;//黄绿色
    MyButton * mediumblue;//中蓝色
    MyButton * dodgerblue;//闪蓝色
    MyButton * purple;//紫色
    MyButton * magenta;//品红
    MyButton * teal;//青色
    MyButton * turquoise;//宝石绿
};

#endif // SELECTIONBAR_H

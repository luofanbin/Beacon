#ifndef FUNCTIONKEY_H
#define FUNCTIONKEY_H

#include <QWidget>
#include <QLabel>
#include "mybutton.h"

class FunctionKey : public QWidget
{
    Q_OBJECT
public:
    explicit FunctionKey(QWidget *parent = nullptr);
    void initWindow();

private:
    QPixmap background;//背景图片
    QLabel * separator;//分割线

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    MyButton * submit;//确定按钮
    MyButton * cancel; //取消按钮
    MyButton * save; //另存为按钮
    MyButton * arrows; //箭头按钮
    MyButton * ellipse; //椭圆按钮
    MyButton * brush; //画笔按钮
    MyButton * rectangle; //矩形按钮
    MyButton * text; //文字按钮
    MyButton * revocation;//撤销按钮
};

#endif // FUNCTIONKEY_H

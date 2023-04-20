#include "functionkey.h"

FunctionKey::FunctionKey(QWidget *parent)
    : QWidget(parent)
    ,background(":/pic/icon/background.png")
{
    initWindow();
    setCursor(Qt::ArrowCursor);
}

void FunctionKey::initWindow()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setFixedSize(315,background.height());
    this->setAutoFillBackground(true);
    QPalette pal = this->palette();
    pal.setBrush(backgroundRole(), background);
    setPalette(pal); //设置背景图片

    submit = new MyButton(this);
    submit->resize(65,26);
    submit->setStyleSheet("QPushButton{border-image:url(:/pic/icon/submit.png);}"
                          "QPushButton:hover{border-image:url(:/pic/icon/submit_selected.png);}");
    submit->setToolTip("完成截图");
    submit->move(width()-67,2);

    cancel = new MyButton(this);
    cancel->resize(24,24);
    cancel->setStyleSheet("QPushButton{border-image:url(:/pic/icon/cancel.png);}"
                          "QPushButton:hover{border-image:url(:/pic/icon/cancel_selected.png);}");
    cancel->setToolTip("取消截图");
    cancel->move(width()-67-28,3);

    save = new MyButton(this);
    save->resize(24,24);
    save->setStyleSheet("QPushButton{border-image:url(:/pic/icon/save.png);}"
                        "QPushButton:hover{border-image:url(:/pic/icon/save_selected.png);}");
    save->setToolTip("保存到本地");
    save->move(width()-67-29*2,3);

    separator = new QLabel(this);
    QPixmap separator_pix(":/pic/icon/separator.png");
    separator->setPixmap(separator_pix);
    separator->resize(24,24);
    separator->move(width()-67-20-29*2,3);

    revocation = new MyButton(this);
    revocation->resize(24,24);
    revocation->setStyleSheet("QPushButton{border-image:url(:/pic/icon/revocation.png);}"
                        "QPushButton:hover{border-image:url(:/pic/icon/revocation_selected.png);}");
    revocation->setToolTip("撤回");
    revocation->move(width()-67-20*2-29*2,3);

    text = new MyButton(this);
    text->resize(24,24);
    text->setStyleSheet("QPushButton{border-image:url(:/pic/icon/type.png);}"
                        "QPushButton:hover{border-image:url(:/pic/icon/type_selected.png);}");
    text->setToolTip("文字工具");
    text->move(width()-67-20*2-29*3,3);

    brush = new MyButton(this);
    brush->resize(24,24);
    brush->setStyleSheet("QPushButton{border-image:url(:/pic/icon/brush.png);}"
                        "QPushButton:hover{border-image:url(:/pic/icon/brush_selected.png);}");
    brush->setToolTip("画笔工具");
    brush->move(width()-67-20*2-29*4,3);

    arrows = new MyButton(this);
    arrows->resize(24,24);
    arrows->setStyleSheet("QPushButton{border-image:url(:/pic/icon/arrows.png);}"
                        "QPushButton:hover{border-image:url(:/pic/icon/arrows_selected.png);}");
    arrows->setToolTip("箭头工具");
    arrows->move(width()-67-20*2-29*5,3);

    ellipse = new MyButton(this);
    ellipse->resize(24,24);
    ellipse->setStyleSheet("QPushButton{border-image:url(:/pic/icon/ellipse.png);}"
                        "QPushButton:hover{border-image:url(:/pic/icon/ellipse_selected.png);}");
    ellipse->setToolTip("椭圆工具");
    ellipse->move(width()-67-20*2-29*6,3);

    rectangle = new MyButton(this);
    rectangle->resize(24,24);
    rectangle->setStyleSheet("QPushButton{border-image:url(:/pic/icon/rectangle.png);}"
                        "QPushButton:hover{border-image:url(:/pic/icon/rectangle_selected.png);}");
    rectangle->setToolTip("矩形工具");
    rectangle->move(width()-67-20*2-29*7,3);
}

void FunctionKey::mousePressEvent(QMouseEvent *event)
{
    return QWidget::mousePressEvent(event);
}

void FunctionKey::mouseMoveEvent(QMouseEvent *event)
{
    return QWidget::mouseMoveEvent(event);
}

void FunctionKey::mouseReleaseEvent(QMouseEvent *event)
{
    return QWidget::mouseReleaseEvent(event);
}

#include "selectionbar.h"
#include <QListView>

SelectionBar::SelectionBar(QWidget *parent)
    : QWidget(parent)
    ,backgroundPic(":/pic/icon/background.png")
{
    init();
}

void SelectionBar::init()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setFixedSize(322,50);
    this->setAutoFillBackground(true);
    QPalette pal = this->palette();
    pal.setBrush(backgroundRole(), backgroundPic);
    setPalette(pal); //设置背景图片

    separator = new QLabel(this);//注册分隔符
    QPixmap separator_pix(":/pic/barIcon/separator35.png");
    separator->setPixmap(separator_pix);
    separator->resize(35,46);
    separator->move(5+34*2+15,2);


    smallDot = new MyButton(this);
    smallDot->resize(30,30);
    smallDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/smalldot.png);}"
                            "QPushButton:hover{border-image:url(:/pic/barIcon/smalldot_selected.png);}");
    smallDot->move(3,10);
    //smallDot->hide();

    mediumDot = new MyButton(this);
    mediumDot->resize(30,30);
    mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot.png);}"
                            "QPushButton:hover{border-image:url(:/pic/barIcon/middledot_selected.png);}");
    mediumDot->move(5+33,10);
    //mediumDot->hide();

    bigDot = new MyButton(this);
    bigDot->resize(30,30);
    bigDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/bigdot.png);}"
                            "QPushButton:hover{border-image:url(:/pic/barIcon/bigdot_selected.png);}");
    bigDot->move(5+33*2,10);
    //bigDot->hide();

    fontLabel = new QLabel(this);
    fontLabel->hide();
    QPixmap font_pix(":/pic/icon/type.png");
    fontLabel->setPixmap(font_pix);
    fontLabel->resize(60,60);
    fontLabel->move(5,-5);


    fontSize = new QComboBox(this);
    fontSize->hide();
    fontSize->addItems({"8","9","10","11","12","14","16","18","20","22"});
    fontSize->resize(60,30);
    fontSize->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 3px; padding: 1px 2px 1px 2px; min-width: 2em;}"
                            "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 20px;border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;border-top-right-radius: 3px;border-bottom-right-radius: 3px;}"
                            "QComboBox::down-arrow {image: url(:/pic/barIcon/pullDown.png);}");
    fontSize->setMaxVisibleItems(6);
    fontSize->setView(new QListView());
    fontSize->move(40,10);
    //connect(fontSize,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(onIndexChanged(const QString &)));

    color = new MyButton(this);
    color->resize(35,35);
    color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/black_selected.png);}");
    color->move(113,7);

    black = new MyButton(this);
    black->resize(16,16);
    black->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/black.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/black_selected.png);}");
    black->move(155,7);

    white = new MyButton(this);
    white->resize(16,16);
    white->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/white.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/white_selected.png);}");
    white->move(155,26);

    dimgrey = new MyButton(this);
    dimgrey->resize(16,16);
    dimgrey->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/dimgrey.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/dimgrey_selected.png);}");
    dimgrey->move(155+20,7);

    grey = new MyButton(this);
    grey->resize(16,16);
    grey->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/grey.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/grey_selected.png);}");
    grey->move(155+20,26);

    maroon = new MyButton(this);
    maroon->resize(16,16);
    maroon->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/maroon.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/maroon_selected.png);}");
    maroon->move(155+20*2,7);

    red = new MyButton(this);
    red->resize(16,16);
    red->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/red.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/red_selected.png);}");
    red->move(155+20*2,26);

    orange = new MyButton(this);
    orange->resize(16,16);
    orange->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/orange.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/orange_selected.png);}");
    orange->move(155+20*3,7);

    yellow = new MyButton(this);
    yellow->resize(16,16);
    yellow->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/yellow.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/yellow_selected.png);}");
    yellow->move(155+20*3,26);

    green = new MyButton(this);
    green->resize(16,16);
    green->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/green.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/green_selected.png);}");
    green->move(155+20*4,7);

    yellowgreen = new MyButton(this);
    yellowgreen->resize(16,16);
    yellowgreen->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/yellowgreen.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/yellowgreen_selected.png);}");
    yellowgreen->move(155+20*4,26);

    mediumblue = new MyButton(this);
    mediumblue->resize(16,16);
    mediumblue->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/mediumblue.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/mediumblue_selected.png);}");
    mediumblue->move(155+20*5,7);

    dodgerblue = new MyButton(this);
    dodgerblue->resize(16,16);
    dodgerblue->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/dodgerblue.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/dodgerblue_selected.png);}");
    dodgerblue->move(155+20*5,26);

    purple = new MyButton(this);
    purple->resize(16,16);
    purple->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/purple.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/purple_selected.png);}");
    purple->move(155+20*6,7);

    magenta = new MyButton(this);
    magenta->resize(16,16);
    magenta->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/magenta.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/magenta_selected.png);}");
    magenta->move(155+20*6,26);

    teal = new MyButton(this);
    teal->resize(16,16);
    teal->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/teal.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/teal_selected.png);}");
    teal->move(155+20*7,7);

    turquoise = new MyButton(this);
    turquoise->resize(16,16);
    turquoise->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/turquoise.png);}"
                         "QPushButton:hover{border-image:url(:/pic/barIcon/turquoise_selected.png);}");
    turquoise->move(155+20*7,26);
}

void SelectionBar::mousePressEvent(QMouseEvent *event)
{
    return QWidget::mousePressEvent(event);
}

void SelectionBar::mouseMoveEvent(QMouseEvent *event)
{
    return QWidget::mouseMoveEvent(event);
}

void SelectionBar::mouseReleaseEvent(QMouseEvent *event)
{
    return QWidget::mouseReleaseEvent(event);
}

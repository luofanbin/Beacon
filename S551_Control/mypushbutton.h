#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QPoint>

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;

typedef struct
{
    BYTE WinID;		// max WinID is 6.
    BYTE SignalID;		// ID: 0,1,2 is on the main board,   //      3,4,5 is on the first slave board,
    WORD WinPosX;
    WORD WinPosY;
    WORD WinSizeX;
    WORD WinSizeY;
    BYTE Contrast;
    BYTE Brightness;
    BYTE ColorTmp;
    BYTE Gamma;
    BYTE ShowFlg;//0 on 1 off   del
    BYTE ShowMode;//0 full screen 1 native 2 as
    WORD WinGetPosX;
    WORD WinGetPosY;
}Win_Attri_t_1;
typedef struct
{
    BYTE ValidData;
    BYTE LayoutID;
    BYTE LayoutName[9];
    BYTE BacklightValue;
    BYTE WinNum;
    Win_Attri_t_1 Windows[8];
}Layout_Attri_t_1;
class mypushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit mypushButton(QWidget *parent = 0);
    //void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);
    int n=100,rectnum,lay_id;
    bool ok=0;
    int x,y,w,h;
//    struct{
//        Win_Attri_t_1 Windows[8];
//        }get_data;
    Layout_Attri_t_1 get_data;
 signals:
    int emit_btn_id(int);
protected slots:
    // 点击子窗口中按钮的slot
    void ClickedBtn();
    void pressed_dl();
};

#endif // MYPUSHBUTTON_H

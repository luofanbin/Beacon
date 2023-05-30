#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include<QTimer>
#include<QTime>
#include"mypushbutton.h"
#include"dialog.h"


#define MCU_CMD_SWITCH_LAYOUT			0x65
#define Para 3

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
}Win_Attri_t;

typedef struct
{
    BYTE ValidData;
    BYTE LayoutID;
    BYTE LayoutName[9];
    BYTE BacklightValue;
    BYTE WinNum;
    Win_Attri_t Windows[8];
}Layout_Attri_t;
typedef struct{
        BYTE RetLen;
        BYTE Btaddress0;
        BYTE Btaddress1;
        BYTE CmdId;
        BYTE CmdSerial;
        BYTE RetState;
        Layout_Attri_t LayoutData;
        BYTE Checksum;
    }RetLayDetailbuffer;

struct{
    RetLayDetailbuffer All_Data[20];
}Read_All_Data={0};

namespace Ui {
class MainWindow;
}
class mypushButton;
class Dialog;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);
    void initPort();
    void sleep(int n);
    void data_handle_new(char *data);
    void data_handle(char * data);
private slots:
    void push1_function(int n);
    void Read_Data();
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_pressed();

    void on_pushButton_3_released();

    void on_pushButton_2_pressed();

    void on_pushButton_2_released();

private:
    Ui::MainWindow *ui;
    QPainter *paint;
    mypushButton *push1;
    mypushButton *push2;
    mypushButton *push3;
    mypushButton *push4;
    mypushButton *push5;
    mypushButton *push6;
    mypushButton *push7;
    mypushButton *push8;

    mypushButton *push9;
    mypushButton *push10;
    mypushButton *push11;
    mypushButton *push12;
    mypushButton *push13;
    mypushButton *push14;
    mypushButton *push15;
    mypushButton *push16;

    mypushButton *push17;
    mypushButton *push18;
    mypushButton *push19;
    mypushButton *push20;
    mypushButton *push21;
    mypushButton *push22;
    mypushButton *push23;
    mypushButton *push24;

    mypushButton *push25;
    mypushButton *push26;
    mypushButton *push27;
    mypushButton *push28;
    mypushButton *push29;
    mypushButton *push30;
    mypushButton *push31;
    mypushButton *push32;

    mypushButton *push33;
    mypushButton *push34;

    QTimer *timer;
    QTime prv_time,tem_time,cur_time;
    QSerialPort *serial;
    QByteArray buf,tem_buf;
    Dialog *dialog;
    int g_nActScreenX,g_nActScreenY,x_width,y_height,flag=0,flag_1=0,flag_2=0,flag_3=0;
    int cur_id=0,prv_id=0;
    int laynum=0,cur_lay,tem_id=0,tem_id_1=0;
    int displayNumchanged=0;
    int conunt=0,pagnum=0,pagnumsum;
    QList<mypushButton *> mypushButton_list;
    int ok_1=1,ok_2=0,ok_3=0,ok_4=0,ok_5=0;
signals:
   int isok(bool);
protected slots:
    void SendCmd(bool ok);
    void SendConnectCmd();
};

#endif // MAINWINDOW_H

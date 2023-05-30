#ifndef DIALOG
#define DIALOG
#include<QDialog>
#include<QDebug>
#include<QTranslator>
//#include <QtSerialPort/QSerialPort>
//#include <QtSerialPort/QSerialPortInfo>
#include"ui_dialog.h"
class Dialog:public QDialog,Ui::Dialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent=0);
    //QSerialPort *serial;
    QByteArray buf;
    int flag=0;

private slots:
    void on_OK_2_clicked();

    void on_OK_clicked();
    void Read_Data();

private:

};

#endif // DIALOG

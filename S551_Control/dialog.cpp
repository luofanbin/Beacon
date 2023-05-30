#include"dialog.h"

Dialog::Dialog(QWidget *parent):QDialog(parent)
{
    setupUi(this);
    setAttribute(Qt::WA_QuitOnClose,false);
    this->show();
    //查找可用的串口
    /*
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            //ui->comboBox->addItem(serial.portName());
            serial.close();
        }
    }
    */
}

void Dialog::Read_Data()
{
    //buf = serial->readAll();
}
void Dialog::on_OK_2_clicked()
{
    exit(0);
}

void Dialog::on_OK_clicked()
{
   /*
    serial = new QSerialPort;
    //设置串口名
    serial->setPortName(comboBox->currentText());
    //打开串口
    serial->open(QIODevice::ReadWrite);
    //设置波特率
    serial->setBaudRate(comboBox_2->currentText().toInt());
    //设置数据位数
    serial->setDataBits(QSerialPort::Data8);

    //设置奇偶校验
    serial->setParity(QSerialPort::NoParity);
    //设置停止位
    serial->setStopBits(QSerialPort::OneStop);
    //设置流控制
    serial->setFlowControl(QSerialPort::NoFlowControl);
    //关闭设置菜单使能
    comboBox->setEnabled(false);
    comboBox_2->setEnabled(false);
    //连接信号槽
    QObject::connect(serial, SIGNAL(QSerialPort::readyRead), this, SLOT(Read_Data()));
*/
}

#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <QtConcurrent>
#include <QTextStream>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_socket=new QTcpSocket(this);
    //connect(m_socket,SIGNAL(readyRead()),this,SLOT(Readyread()));  //连接接收消息槽
    connect(this,SIGNAL(emitSendData(int)),this,SLOT(slotDealSendDataSignal(int)));
    connect(this,SIGNAL(emmitSendStr(QString)),this,SLOT(displayStr(QString)));
    connect(ui->CAT_6_LivecheckBox,SIGNAL(stateChanged(int)),this,SLOT(chockBoxStatus(int)));
    connect(ui->CAT_6_RefcheckBox,SIGNAL(stateChanged(int)),this,SLOT(chockBoxStatus(int)));
    connect(ui->DVI_LivecheckBox,SIGNAL(stateChanged(int)),this,SLOT(chockBoxStatus(int)));
    connect(ui->DVI_RefcheckBox,SIGNAL(stateChanged(int)),this,SLOT(chockBoxStatus(int)));
    connect(ui->DP_LivecheckBox,SIGNAL(stateChanged(int)),this,SLOT(chockBoxStatus(int)));
    connect(ui->DP_RefcheckBox,SIGNAL(stateChanged(int)),this,SLOT(chockBoxStatus(int)));
    connect(ui->SDI_LivecheckBox,SIGNAL(stateChanged(int)),this,SLOT(chockBoxStatus(int)));
    connect(ui->SDI_RefcheckBox,SIGNAL(stateChanged(int)),this,SLOT(chockBoxStatus(int)));
    connect(ui->GrabActivecheckBox,SIGNAL(stateChanged(int)),this,SLOT(chockBoxStatus(int)));
    ui->IPlineEdit->setText("10.1.1.111");
    ui->PortlineEdit->setText("33800");
    nCmdId=0;
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    nDownCount=0;
    //on_ConnectTcpServiceButton_clicked();

    connect(this,SIGNAL(emitSendConnect()),this,SLOT(ConnectTest()));
    //ConnectTest();
    ui->frame->setHidden(true);
    ui->frame_2->setHidden(true);
    ui->lineEditIntervalTime->setText("100");
}

Widget::~Widget()
{
    delete ui;
}

QByteArray Widget::ReadDataFromFile(QString strFilePath)
{
    qDebug()<<strFilePath;
    QFile file(strFilePath);
    bool isOk=file.open(QIODevice::ReadOnly);
    if(isOk==true)
    {
        qDebug()<<"111111111";
        QByteArray pFileData = file.readAll();
        qDebug()<<pFileData.size();
        file.close();
        return pFileData;
    }
}

bool Widget::WriteDataToFile(QString strFilePath, char *pFileData)
{
    QString str=QDir::currentPath()+"/"+strFilePath;
    qDebug()<<str;
    QFile file(strFilePath);
    bool isOk=file.open(QIODevice::Append);
    if(isOk==true)
    {
        //QDataStream stream(&file);
        int num=strlen(pFileData);
//        for(int i=0;i<num;i++)
//        {
//            stream<<pFileData[i];
//        }
        file.write(pFileData);
//        stream<<pFileData[0];
//        stream<<&pFileData[1];
        //qDebug()<<"pFileData"<<pFileData[0];
        file.close();
        return true;
    }
    return false;
}

void Widget::CirculateSendTest()
{
    int Count=ui->SendCountlineEdit->text().toInt();
    nSendCount=0;
    int n_cmd_id;
    while(Count)
    {
        if(blCloseThread)
            break;
        int n_delay_num=ui->DelaylineEdit->text().toInt();
        int msec=qrand()%n_delay_num;
        QThread::msleep(msec);
        if(isMultiple)
          n_cmd_id=qrand()%16;
        else
          n_cmd_id=ui->CmdIDcomboBox->currentIndex();
                //qrand()%16;
                //ui->CmdIDcomboBox->currentIndex();
       // qDebug()<<"sleep:"<<msec<<"cmd id:"<<n_cmd_id;
        qDebug()<<"cmdId:"<<n_cmd_id;
        switch (n_cmd_id) {
        case ASK_WORKLIST:
            emit emitSendData(ASK_WORKLIST);
            break;
        case SINGLE_GRAB_START:
            emit emitSendData(SINGLE_GRAB_START);
            break;
        case CLEAR_MEMORY:
            emit emitSendData(CLEAR_MEMORY);
            break;
        case SWITCH_INPUT:
            emit emitSendData(SWITCH_INPUT);
            break;
        case SCAN_INPUTS:
            emit emitSendData(SCAN_INPUTS);
            break;
        case SCAN_INPUTS_ABORT:
            emit emitSendData(SCAN_INPUTS_ABORT);
            break;
        case SWITCH_NEXT_INPUT:
            emit emitSendData(SWITCH_NEXT_INPUT);
            break;
        case SEND_VALID_INPUTS:
            emit emitSendData(SEND_VALID_INPUTS);
            break;
        case OUTPUT_ACTIVE:
            emit emitSendData(OUTPUT_ACTIVE);
            break;
        case GRABBING_ACTIVE:
            emit emitSendData(GRABBING_ACTIVE);
            break;
        case SEND_STATUS:
            emit emitSendData(SEND_STATUS);
            break;
        case SET_DATE_TIME:
            emit emitSendData(SET_DATE_TIME);
            break;
        case SWITCH_OUTPUTS:
            emit emitSendData(SWITCH_OUTPUTS);
            break;
        case SEND_STATUS_2:
            emit emitSendData(SEND_STATUS_2);
            break;
        case PIP_ON:
            emit emitSendData(PIP_ON);
            break;
        case PIP_OFF:
            emit emitSendData(PIP_OFF);
            break;
        case SEND_VERSION:
            emit emitSendData(SEND_VERSION);
            break;
        default:
            break;
        }
        Count--;
    }
    ui->CirculateSendButton->setText("CirculateSend");
}

void Widget::ConnectTimeTest(QTcpSocket *socket)
{
//    on_RebootButton_clicked();
    emit emitSendConnect();
    int n=ui->lineEdit_2->text().toInt();
    int nRebootCount=n;
    int nNum=0;
    while (n--) {

       if(!bltuatus)
           return;
       QThread::msleep(35000);
       emit emitSendConnect();
       int m=50;
       int i=0;

       while (m--) {

          if(!bltuatus)
            return;
          QThread::msleep(2000);
          if(!blConnectStutes)
          {
//            if((35+i*2>60))
//            {

//                    QString strFileName=ui->lineEdit->text()+".csv";
//                    QStringList CSVList;
//                    CSVList<<QString("%1").arg(nRebootCount-n)<<","<<QString("%1").arg(35+i*2)<<"\n";
//                //QString strFileData=QString("%1").arg(nRebootCount-n)+","+QString("%1").arg(35+i*2)+"\n";
//                    setCSVData(strFileName,CSVList);
//                    return;
//            }
//            else
              emit emitSendConnect();
          }
          else
          {
              //qDebug()<<35+i*2;
              QString strFileName=ui->lineEdit->text()+".csv";
              QStringList CSVList;
              CSVList<<QString("%1").arg(nRebootCount-n)<<","<<QString("%1").arg(35+i*2)<<"\n";
              //QString strFileData=QString("%1").arg(nRebootCount-n)+","+QString("%1").arg(35+i*2)+"\n";
              setCSVData(strFileName,CSVList);
//              if((35+i*2)>60)
//                  nNum++;

              break;
          }
          i++;
       }
    }
}

bool Widget::setCSVData(QString strFileName, const QStringList &CSVList)
{
    if (CSVList.isEmpty())
        return false;
    QString strFilePath = QDir::currentPath()+"/"+strFileName;
    //qDebug()<<strFilePath;
    QFile csvFile(strFilePath);
    if (!csvFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return false;

//    if (!csvFile.resize(0))
//        return false;

    //csvFile.seek(0,2);
    //QTextStream txtOutput(&csvFile);
    Q_FOREACH(QString str, CSVList)
    {
        csvFile.write(str.toLatin1());
    //QTextStream out(&csvFile);
    //out <<CSVList;
        //txtOutput << str<< endl;
    }
    csvFile.flush();
    csvFile.close();
    return true;
}

void Widget::AskWorkListTest()
{

    int n=0;
    bool bl_result;
    char data[256];
    QString str;
    while(1)
    {
        if(n!=0)
            QThread::msleep(50000);

        bl_result=ConnectTest();
        if(!bl_result)
            continue;
        on_GrabActiveButton_clicked();
        memset(data,0,256);
        if (m_socket->waitForReadyRead(10000))
            m_socket->read(data,256);

        str=QString(&data[8]);
        emit emmitSendStr(str);

        QThread::msleep(10000);
        bl_result=false;
        for(int m=0;m<3;m++)
        {
            memset(data,0,256);
//            if(m>0)
//                QThread::msleep(20000);
            on_AskWorklistButton_clicked();
            if (m_socket->waitForReadyRead(60000))
                m_socket->read(data,256);

            str=QString(&data[8]);
            emit emmitSendStr(str);

            if(memcmp(&data[8],"ASK_WORKLIST OK",15)==0)
            {
                n++;
                bl_result=true;
                break;
            }
        }

        if(!bl_result)
            break;

        //ui->lineEditIntervalTime->setText(QString("%1").arg(n));
        emitSendData(n);
        on_RebootButton_clicked();
        on_CloseButton_clicked();
    }


}

void Widget::GrabImageTest()
{
    char data[256];
    QString str;
    m_socket->disconnectFromHost();
    if(m_socket->state()==QAbstractSocket::UnconnectedState
           || m_socket->waitForDisconnected(1000))
    {
        //ui->textBrowser->setText("已断开");
    }

    bool bl_result=ConnectTest();
    if(!bl_result)
        return;

    on_GrabActiveButton_clicked();
    memset(data,0,256);
    if (m_socket->waitForReadyRead(60000))
        m_socket->read(data,256);
    //qDebug()<<&data[8];

    on_AskWorklistButton_clicked();
    memset(data,0,256);
    if (m_socket->waitForReadyRead(60000))
        m_socket->read(data,256);

    str=QString(&data[8]);
    emit emmitSendStr(str);
    //qDebug()<<&data[8];

    if(memcmp(&data[8],"ASK_WORKLIST OK",15)!=0)
        return;

    int n=0;
    while(1)
    {
        on_GrabImageButton_clicked();
        memset(data,0,256);

        if (m_socket->waitForReadyRead(60000))
            m_socket->read(data,256);

        //qDebug()<<&data[8];

        str=QString(&data[8]);
        emit emmitSendStr(str);

        memset(data,0,256);
        if (m_socket->waitForReadyRead(60000))
            m_socket->read(data,256);

      //  qDebug()<<&data[8];

        str=QString(&data[8]);
        emit emmitSendStr(str);

        n++;
        if(n>ui->lineEditIntervalTime->text().toInt()-1)
        {
            on_ClearMeMoryButton_clicked();
            memset(data,0,256);
            if (m_socket->waitForReadyRead(60000))
                m_socket->read(data,256);

            str=QString(&data[8]);
            emit emmitSendStr(str);
            n=0;
            //if(memcmp(&data[8],"CLEAR_MEMORY OK",15)!=0)
            //    return;
            QThread::msleep(10000);
        }
    }
}

void Widget::displayStr(QString str)
{
    ui->textBrowser->setText(str);
}

bool Widget::ConnectTest()
{
    //QTcpSocket *socket=new QTcpSocket(this);
    QString strIP=ui->IPlineEdit->text();
    int n_port=ui->PortlineEdit->text().toInt();
    m_socket->connectToHost(strIP,n_port,QTcpSocket::ReadWrite);
    QString strError=tr("Error:");
    if(!m_socket->waitForConnected(1000))

    {
        strError+=QString("%1").arg(m_socket->error());
        //ui->textBrowser->append(strError);
        //ui->textBrowser->append("连接失败");
        emit emmitSendStr(strError);
        blConnectStutes=false;
        return false;
    }
    else{
        //ui->textBrowser->append("已连接");
        emit emmitSendStr("已连接");
        blConnectStutes=true;
//        char send_data[1024];
//        memset(send_data, 0, 1024);
//        memcpy(send_data, "SMS:", 4);
//        char *data = "REBOOT";
//        int len = strlen(data);
//        //send_data[0]=nCmdId;
//        send_data[4] = (len >> 24) & 0xff;
//        send_data[5] = (len >> 16) & 0xff;
//        send_data[6] = (len >> 8) & 0xff;
//        send_data[7] = (len) & 0xff;

//        memcpy(&send_data[8], data, len);
//        int n=m_socket->write(send_data,len+8);
    }
//   m_socket->close();
    //delete socket;
    return true;
}

void Widget::on_ConnectTcpServiceButton_clicked()
{
    m_socket->disconnectFromHost();
    if(m_socket->state()==QAbstractSocket::UnconnectedState
           || m_socket->waitForDisconnected(1000))
    {
        //ui->textBrowser->setText("已断开");
    }

    QString strIP=ui->IPlineEdit->text();
    int n_port=ui->PortlineEdit->text().toInt();
    m_socket->connectToHost(strIP,n_port,QTcpSocket::ReadWrite);
    if(!m_socket->waitForConnected(1000))

    {
        ui->textBrowser->setText("连接失败");
    }
    else{
        ui->textBrowser->setText("已连接");
    }
}

void Widget::on_CloseButton_clicked()
{
    m_socket->disconnectFromHost();
    if(m_socket->state()==QAbstractSocket::UnconnectedState
           || m_socket->waitForDisconnected(1000))
    {
        //ui->textBrowser->setText("已断开");
    }
}

void Widget::Readyread()
{
    char recvData[1024];
    memset(recvData,0,1024);
    //int recvLen=
    QByteArray QB_Data=m_socket->readAll();
    char *ch=QB_Data.data();
    int len=QB_Data.size();
//    qDebug()<<"recv len:"<<len;
    QString str;
    int Len=0;
    int n_cmd_id;
    int recvLen;
    while(len)
    {
        memset(recvData,0,1024);
        int data_len=(ch[Len+4]<<24)+(ch[Len+5]<<16)+(ch[Len+6]<<8)+ch[Len+7];
//        qDebug()<<data_len;
//        if(ch[Len]<0)
//            n_cmd_id=ch[Len]+128+128;
//        else
//            n_cmd_id=ch[Len];

        if(data_len<1024)
        {
            memcpy(recvData,&ch[Len+8],data_len);
        //qDebug()<<"cmdid:"<<n_cmd_id<<"data:"<<recvData;
            str=QString("%1:%2").arg(nSendCount+1).arg(recvData);
            if(str.contains("SINGLE_GRAB_START",Qt::CaseSensitive))
            {
                QTime stopTime = QTime::currentTime();
                QString date_time = stopTime.toString("hh:mm:ss.zzz");
                ui->lineEditStop->setText(date_time);
                QTime intervalTime=QTime::fromString(ui->lineEditStart->text(),"hh:mm:ss.zzz");
                int elapsed = intervalTime.msecsTo(stopTime);
                ui->lineEditIntervalTime->setText(QString("%1").arg(elapsed));
            }
//            if(str.contains("SINGLE_GRAB_STORED",Qt::CaseSensitive))
//            {
//                QTime saveTime = QTime::currentTime();
//                QString date_time = saveTime.toString("hh:mm:ss.zzz");
//                ui->lineEditSave->setText(date_time);
//                QTime intervalTime=QTime::fromString(ui->lineEditStop->text(),"hh:mm:ss.zzz");
//                int elapsed = intervalTime.msecsTo(saveTime);
//                ui->lineEditIntervalTime_2->setText(QString("%1").arg(elapsed));
//            }
            len-=(data_len+8);
            Len+=(data_len+8);
            ui->textBrowser->append(str);
            nSendCount++;
//            qDebug()<<nSendCount;
        }

        if(data_len>1024)
        {
            if(nDownCount==0)
            {
                WriteDataToFile("SystemConfig.json",&ch[36]);
//                qDebug()<<"ch[36]"<<ch[36];
                nDownCount++;
                len=0;
                continue;
            }

            if(nDownCount==1)
            {
                WriteDataToFile("SystemConfig.json",ch);
                nDownCount=0;
                len=0;
                continue;
            } 
        }
    }
//    if(recvLen<1024)
//    {
//        QDateTime current_date_time = QDateTime::currentDateTime();
//        QString date_time = current_date_time.toString("yyyy-MM-dd hh:mm:ss.zzz");
//        QString strText=QString(QLatin1String(recvData));
//        ui->textBrowser->append(strText);
//    }else
//    {
//        int data_len=(recvData[4]<<24)+(recvData[5]<<16)+(recvData[6]<<8)+recvData[7];
//        char file_data[data_len];
//        memset(file_data,0,data_len);
//        memcpy(file_data,&recvData[36],recvLen-36);
//        int curr_len=recvLen-36;
//        while(1)
//        {
//            recvLen=m_socket->read(&file_data[curr_len],data_len);
//            curr_len+=recvLen;
//            if(curr_len==data_len)
//                break;
//        }
//        WriteDataToFile("SystemConfig.json",file_data);
//    }
}

void Widget::on_GrabImageButton_clicked()
{
    char send_data[1024] = {0};
    memcpy(send_data, "SMS:", 4);
    char *data = "SINGLE_GRAB_START";
    int len = strlen(data);
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len)& 0xff;

    memcpy(&send_data[8], data, len);
    int send_len;


//    TestGrab->GrabIamgeStartLable->setText(date_time);
//    TestGrab->repaint();
//    QThread::msleep(5);
    QTime startTime = QTime::currentTime();
    QString date_time = startTime.toString("hh:mm:ss.zzz");
    ui->lineEditStart->setText(date_time);
    m_socket->write(send_data,len+8);


//    qDebug()<<"send Time:"<<date_time;
    return;
}

void Widget::on_GrabActiveButton_clicked()
{
    char send_data[1024];
    //CString str;
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    int len;
    char data[1024];
    memset(data, 0, 1024);
    if(ui->GrabActivecheckBox->isChecked())
        memcpy(data, "GRABBING_ACTIVE 1156775298144085", 32);
    else
        memcpy(data, "GRABBING_ACTIVE 1156775298144101", 32);
    len= strlen(data);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len)& 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);
}

void Widget::on_AskWorklistButton_clicked()
{
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    char *data = "ASK_WORKLIST";
    int len = strlen(data);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_ClearMeMoryButton_clicked()
{
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    char *data = "CLEAR_MEMORY";
    int len = strlen(data);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_SwitchInputButton_clicked()
{
    int nSigId =ui->InputcomboBox->currentIndex();//取得目前已经有的行数

    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    //memcpy(&send_data[8], "SWITCH_INPUT", 12);
    //QString str=QString("SWITCH_INPUT #%1").arg(nSigId);
    sprintf(&send_data[8],"SWITCH_INPUT #%d", nSigId);
    int len = strlen(&send_data[8]);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    m_socket->write(send_data,len+8);

    return;
}

void Widget::on_ScanInputButton_clicked()
{
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    char *data = "SCAN_INPUTS";
    int len = strlen(data);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);

    return;
}

void Widget::on_StopScanInputButton_clicked()
{
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    char *data = "SCAN_INPUTS_ABORT";
    int len = strlen(data);
   // send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_SwitchNextInputButton_clicked()
{
    char send_data[1024];
    //CString str;
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    char *data = "SWITCH_NEXT_INPUT";
    int len = strlen(data);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_SendValidInputButton_clicked()
{
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    char *data = "SEND_VALID_INPUTS";
    int len = strlen(data);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_OutputActiveButton_clicked()
{
    int output1 = 0, output2 = 0;
    int key_value= 25776511,Prefix_value=374956;
    if (ui->CAT_6_LivecheckBox->isChecked())
        output1 += 4;
    if(ui->DVI_LivecheckBox->isChecked())
        output1 += 8;
    if (ui->DP_LivecheckBox->isChecked())
        output1 += 64;
    if (ui->SDI_LivecheckBox->isChecked())
        output1 += 256;

    if (ui->CAT_6_RefcheckBox->isChecked())
        output2 += 16;
    if (ui->DVI_RefcheckBox->isChecked())
        output2 += 32;
    if (ui->DP_RefcheckBox->isChecked())
        output2 += 128;
    if (ui->SDI_RefcheckBox->isChecked())
        output2 += 512;

    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    if (output1 + output2 == 0)
    {
        sprintf(&send_data[8], "OUTPUT_ACTIVE %d%u", 11567752, ((Prefix_value * 100 + (output1 + output2)) + 2) ^ key_value);
    }
    else
    {
        if ((output1 + output2) / 1000 > 0)
        {
            sprintf(&send_data[8], "OUTPUT_ACTIVE %d%u", 11567752, ((Prefix_value * 10000 + (output1 + output2)) + 2) ^ key_value);
        }
        else if ((output1 + output2) / 100 > 0 && (output1 + output2) / 100 < 10)
        {
            sprintf(&send_data[8], "OUTPUT_ACTIVE %d%u", 11567752, ((Prefix_value * 1000 + (output1 + output2)) + 2) ^ key_value);
        }
        else
        {
            sprintf(&send_data[8], "OUTPUT_ACTIVE %d%u", 11567752, ((Prefix_value * 100 + (output1 + output2)) + 2) ^ key_value);
        }

    }
    int len = strlen(&send_data[8]);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;
    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_DownCfgFileButton_clicked()
{
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    char *data = "DOWNLOAD_CONFIGURATION_FILE";
    int len = strlen(data);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_UploadCfgFileButton_clicked()
{
    QString strFilePath = QFileDialog::getOpenFileName(NULL, "Select File", "", "json(*.json)");
    if (strFilePath.isEmpty())
    {
         QMessageBox::warning(NULL, "提示", "未选择数据文件", "确定");
         return;
    }
    QByteArray Data=ReadDataFromFile(strFilePath);

    int file_len=Data.size();
    qDebug()<<Data.size();
    char send_data[file_len+34];
    memset(send_data, 0, file_len+34);
    memcpy(send_data, "SMS:", 4);
    char *data = "UPLOAD_CONFIGURATION_FILE ";
    int len = file_len+26;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len)& 0xff;

    memcpy(&send_data[8], data, 26);

    char* ch=Data.data();
    memcpy(&send_data[34],ch,file_len);
    int n=m_socket->write(send_data,len+8);
}

void Widget::on_SendStatusButton_clicked()
{
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    char *data = "SEND_STATUS";
    int len = strlen(data);
   // send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_SetDateTimeButton_clicked()
{
    QDateTime m_DateTime_Start=ui->dateTimeEdit->dateTime();
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);

    sprintf(&send_data[8], "SET_DATE_TIME %d%d.%d%d.%d %d%d:%d%d:%d%d", m_DateTime_Start.date().day()/10, m_DateTime_Start.date().day()%10,
                                                                        m_DateTime_Start.date().month()/10, m_DateTime_Start.date().month()%10,
                                                                        m_DateTime_Start.date().year(),
                                                                        m_DateTime_Start.time().hour()/10, m_DateTime_Start.time().hour()%10,
                                                                        m_DateTime_Start.time().minute()/10,m_DateTime_Start.time().minute()%10,
                                                                        m_DateTime_Start.time().second()/10,m_DateTime_Start.time().second()%10);
    int len = strlen(&send_data[8]);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_RebootButton_clicked()
{
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    char *data = "REBOOT";
    int len = strlen(data);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_SwitchOutputsButton_clicked()
{
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    char *data = "SWITCH_OUTPUTS";
    int len = strlen(data);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_SendStatus2Button_clicked()
{
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    char *data = "SEND_STATUS_2";
    int len = strlen(data);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_SendVersionButton_clicked()
{
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    char *data = "SEND_VERSION";
    int len = strlen(data);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_PipOnButton_clicked()
{
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    char *data = "PIP_ON #4";
    int len = strlen(data);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_PipOffButton_clicked()
{
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    char *data = "PIP_OFF";
    int len = strlen(data);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;

    memcpy(&send_data[8], data, len);
    m_socket->write(send_data,len+8);
    return;
}

void Widget::on_CirculateSendButton_clicked()
{
    if(ui->CirculateSendButton->text()=="CirculateSend")
    {
        blCloseThread=false;
        nCmdId=0;
        isMultiple=false;
        QtConcurrent::run(this,&Widget::CirculateSendTest);
        ui->CirculateSendButton->setText("StopCirculateSend");
    }else
    {
        blCloseThread=true;
        ui->CirculateSendButton->setText("CirculateSend");
    }
}

void Widget::slotDealSendDataSignal(int nType)
{
    ui->lineEditIntervalTime->setText(QString("%1").arg(nType));
    /*
    mutex.lock();
    nCmdId++;
    switch (nType) {
    case ASK_WORKLIST:
        on_AskWorklistButton_clicked();
        break;
    case SINGLE_GRAB_START:
        on_GrabImageButton_clicked();
        break;
    case CLEAR_MEMORY:
        on_ClearMeMoryButton_clicked();
        break;
    case SWITCH_INPUT:
        on_SwitchInputButton_clicked();
        break;
    case SCAN_INPUTS:
        on_ScanInputButton_clicked();
        break;
    case SCAN_INPUTS_ABORT:
        on_StopScanInputButton_clicked();
        break;
    case SWITCH_NEXT_INPUT:
        on_SwitchNextInputButton_clicked();
        break;
    case SEND_VALID_INPUTS:
        on_SendValidInputButton_clicked();
        break;
    case OUTPUT_ACTIVE:
        on_OutputActiveButton_clicked();
        break;
    case GRABBING_ACTIVE:
        on_GrabActiveButton_clicked();
        break;
    case DOWNLOAD_CONFIGURATION_FILE:
        on_DownCfgFileButton_clicked();
        break;
    case UPLOAD_CONFIGURATION_FILE:
        on_UploadCfgFileButton_clicked();
        break;
    case SEND_STATUS:
        on_SendStatusButton_clicked();
        break;
    case SET_DATE_TIME:
        on_SetDateTimeButton_clicked();
        break;
    case REBOOT:
        on_RebootButton_clicked();
        break;
    case SWITCH_OUTPUTS:
        on_SwitchOutputsButton_clicked();
        break;
    case SEND_STATUS_2:
        on_SendStatus2Button_clicked();
        break;
    case SEND_VERSION:
        on_SendVersionButton_clicked();
        break;
    case PIP_ON:
        on_PipOnButton_clicked();
        break;
    case PIP_OFF:
        on_PipOffButton_clicked();
        break;

    default:
        break;
    }
    mutex.unlock();
    */

}

void Widget::on_pushButtonHigh_clicked()
{
    //nCmdId=0;
    blCloseThread=false;
    isMultiple=true;
    QtConcurrent::run(this,&Widget::CirculateSendTest);
}

void Widget::on_pushButtonLow_clicked()
{

}

void Widget::on_pushButton_clicked()
{
    blConnectStutes=false;
    bltuatus=true;
    QtConcurrent::run(this,&Widget::ConnectTimeTest,m_socket);
}

void Widget::on_pushButton_2_clicked()
{
    bltuatus=false;
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    int nAppendix=0;
    if(index==0)
    {
        ui->lineEditPrefix->setText("374956");

        if (ui->CAT_6_LivecheckBox->isChecked())
            nAppendix += 4;
        if(ui->DVI_LivecheckBox->isChecked())
            nAppendix += 8;
        if (ui->DP_LivecheckBox->isChecked())
            nAppendix += 64;
        if (ui->SDI_LivecheckBox->isChecked())
            nAppendix += 256;

        if (ui->CAT_6_RefcheckBox->isChecked())
            nAppendix += 16;
        if (ui->DVI_RefcheckBox->isChecked())
            nAppendix += 32;
        if (ui->DP_RefcheckBox->isChecked())
            nAppendix += 128;
        if (ui->SDI_RefcheckBox->isChecked())
            nAppendix += 512;
    }

    if(index==1)
    {
        ui->lineEditPrefix->setText("724086");
        if(ui->GrabActiveButton->isChecked())
            nAppendix += 16;
    }

    if(nAppendix<10)
     ui->lineEditAppendix->setText(QString("0%1").arg(nAppendix));
    else
    ui->lineEditAppendix->setText(QString("%1").arg(nAppendix));
}

void Widget::chockBoxStatus(int nStatus)
{
    QCheckBox *chockBox = qobject_cast<QCheckBox *>(sender());
    QString name = sender()->objectName();

    int nAppendix=ui->lineEditAppendix->text().toInt();
    if(ui->comboBox->currentIndex()==0)
    {
        if(name=="CAT_6_LivecheckBox")
        {
            if(nStatus==0)
               nAppendix-=4;
            else
               nAppendix+=4;
        }

        if(name=="DVI_LivecheckBox")
        {
            if(nStatus==0)
               nAppendix-=8;
            else
               nAppendix+=8;
        }

        if(name=="DP_LivecheckBox")
        {
            if(nStatus==0)
               nAppendix-=64;
            else
               nAppendix+=64;
        }

        if(name=="SDI_LivecheckBox")
        {
            if(nStatus==0)
               nAppendix-=256;
            else
               nAppendix+=256;
        }

        if(name=="CAT_6_RefcheckBox")
        {
            if(nStatus==0)
               nAppendix-=16;
            else
               nAppendix+=16;
        }

        if(name=="DVI_RefcheckBox")
        {
            if(nStatus==0)
               nAppendix-=32;
            else
               nAppendix+=32;
        }

        if(name=="DP_RefcheckBox")
        {
            if(nStatus==0)
               nAppendix-=128;
            else
               nAppendix+=128;
        }

        if(name=="SDI_RefcheckBox")
        {
            if(nStatus==0)
               nAppendix-=512;
            else
               nAppendix+=512;
        }
    }

    if(ui->comboBox->currentIndex()==1)
    {
        if(name=="GrabActivecheckBox")
        {
            if(nStatus==0)
               nAppendix-=16;
            else
               nAppendix+=16;
        }
    }

    if(nAppendix<10)
     ui->lineEditAppendix->setText(QString("0%1").arg(nAppendix));
    else
     ui->lineEditAppendix->setText(QString("%1").arg(nAppendix));
}

void Widget::on_pushButtonSend_clicked()
{
    char send_data[1024];
    memset(send_data, 0, 1024);
    memcpy(send_data, "SMS:", 4);
    int nAppendix=ui->lineEditAppendix->text().toInt();
    int Prefix_value=ui->lineEditPrefix->text().toInt();
    int key_value=ui->lineEditKey->text().toInt();
    int nAddNum=key_value/qPow(10,ui->lineEditKey->text().count()-1);

    int key_value_reversal=0;
    int nCount=ui->lineEditKey->text().count();
    int nCount1=ui->lineEditAppendix->text().count();
    int temp_value=key_value;
    int n_value;

    for(int i=0;i<nCount;i++)
    {
        n_value=temp_value/qPow(10,nCount-1-i);
        temp_value=temp_value%(int)(qPow(10,nCount-1-i));

        key_value_reversal+=(n_value*qPow(10,i));
    }

    if(ui->comboBox->currentIndex()==0)
    {
//        if (nAppendix == 0)
//        {
//            sprintf(&send_data[8], "OUTPUT_ACTIVE %d%u", key_value_reversal, ((Prefix_value * 100 + nAppendix) + nAddNum) ^ key_value);
//        }
//        else
//        {
//            if (nAppendix / 1000 > 0)
//            {
//                sprintf(&send_data[8], "OUTPUT_ACTIVE %d%u", key_value_reversal, ((Prefix_value * 10000 + nAppendix) + nAddNum) ^ key_value);
//            }
//            else if (nAppendix / 100 > 0 && nAppendix / 100 < 10)
//            {
//                sprintf(&send_data[8], "OUTPUT_ACTIVE %d%u", key_value_reversal, ((Prefix_value * 1000 + nAppendix) + nAddNum) ^ key_value);
//            }
//            else
//            {
//                sprintf(&send_data[8], "OUTPUT_ACTIVE %d%u", key_value_reversal, ((Prefix_value * 100 + nAppendix) + nAddNum) ^ key_value);
//            }
//        }
//        if(nCount1<2)
//         sprintf(&send_data[8], "OUTPUT_ACTIVE %d%u", key_value_reversal, ((Prefix_value * (int)qPow(10,2) + nAppendix) + nAddNum) ^ key_value);
//        else
         sprintf(&send_data[8], "OUTPUT_ACTIVE %d%u", key_value_reversal, ((Prefix_value * (int)qPow(10,nCount1) + nAppendix) + nAddNum) ^ key_value);
    }

    if(ui->comboBox->currentIndex()==1)
    {
//        if(nCount1<2)
//         sprintf(&send_data[8], "GRABBING_ACTIVE %d%u", key_value_reversal, ((Prefix_value * (int)qPow(10,2) + nAppendix) + nAddNum) ^ key_value);
//        else
         sprintf(&send_data[8], "GRABBING_ACTIVE %d%u", key_value_reversal, ((Prefix_value * (int)qPow(10,nCount1) + nAppendix) + nAddNum) ^ key_value);
    }
    qDebug()<<&send_data[8];
    int len = strlen(&send_data[8]);
    //send_data[0]=nCmdId;
    send_data[4] = (len >> 24) & 0xff;
    send_data[5] = (len >> 16) & 0xff;
    send_data[6] = (len >> 8) & 0xff;
    send_data[7] = (len) & 0xff;
    m_socket->write(send_data,len+8);
}

void Widget::on_pushButton_3_clicked()
{
    QtConcurrent::run(this,&Widget::GrabImageTest);
}

#include "mvmethodosd.h"
#include<QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QFile>
#include <QDateTime>
#include <QDir>
mvMethodOsd::mvMethodOsd()
{
    qRegisterMetaType<stDispOsd_INFO>("stDispOsd_INFO");
    qDBusRegisterMetaType<stDispOsd_INFO>();

    qRegisterMetaType<stOsdMsg_INFO>("stOsdMsg_INFO");
    qDBusRegisterMetaType<stOsdMsg_INFO>();
}

void mvMethodOsd::run()
{
        //建立到session bus的连接
        QDBusConnection connection = QDBusConnection::sessionBus();
        //在session bus上注册名为com.scorpio.test的服务
        if(!connection.registerService("mv.osd.server"))
        {
            qDebug() << "error:" << connection.lastError().message();
            exit(-1);
        }
        //mvMethodOsd ct;
        //注册名为/test/objects的对象，把类Object所有槽函数导出为object的method
        connection.registerObject("/mv/mvosd/osd", this,QDBusConnection::ExportAllSlots);
        exec();
}

stDispOsd_INFO mvMethodOsd::GetSingleSel(int osddisp_type)
{
    stDispOsd_INFO stDispOsd;
    QFile file("/opt/cfg/timming_cfg.json");
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
    }

    QByteArray allData = file.readAll();
    file.close();

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!";
    }
    QJsonObject rootObj = jsonDoc.object();

    switch (osddisp_type) {
    case OSDDISP_TYPE_SmallOsd:
        if(rootObj.contains("SmallOsd"))
        {
            stDispOsd.id=OSDDISP_TYPE_SmallOsd;
            QJsonObject subObj = rootObj.value("SmallOsd").toObject();
            stDispOsd.value=subObj["enable"].toInt();
        }
        if(json_error.error != QJsonParseError::NoError)
        {
            stDispOsd.id=OSDDISP_TYPE_SmallOsd;
            stDispOsd.value=stSettingData.nRefLive;
        }
        break;
    case OSDDISP_TYPE_SCREENMSG:
        if(rootObj.contains("On_Screen"))
        {
            stDispOsd.id=OSDDISP_TYPE_SCREENMSG;
            QJsonObject subObj = rootObj.value("On_Screen").toObject();
            if(subObj["enable"].toInt()==1)
               stDispOsd.value=1;
            else if(subObj["enable"].toInt()==0)
               stDispOsd.value=0;           
        }
        if(json_error.error != QJsonParseError::NoError)
        {
            stDispOsd.id=OSDDISP_TYPE_SCREENMSG;
            stDispOsd.value=stSettingData.nOnScreenEnable;
        }
        break;
    case OSDDISP_TYPE_GRABINDICT:
        if(rootObj.contains("Frame_Grab_Indicator"))
        {
            stDispOsd.id=OSDDISP_TYPE_GRABINDICT;
            QJsonObject subObj = rootObj.value("Frame_Grab_Indicator").toObject();
            if(subObj["type"].toInt()==1)
            {
                stDispOsd.value=1;
            }else{
                stDispOsd.value=0;
            }
        }
        break;
    case OSDDISP_TYPE_SCANMSG:
        if(rootObj.contains("Scan_Input_Configuration"))
        {
            stDispOsd.id=OSDDISP_TYPE_SCANMSG;
            QJsonObject subObj = rootObj.value("Scan_Input_Configuration").toObject();
            if(subObj["disp_message"].toInt()==1)
            {
               stDispOsd.value=1;
            }else if(subObj["disp_message"].toInt()==0) {
               stDispOsd.value=0;
            }
        }
        if(json_error.error != QJsonParseError::NoError)
        {
            stDispOsd.id=OSDDISP_TYPE_SCANMSG;
            stDispOsd.value=stSettingData.nScanInputEnable;
        }
        break;
    case OSDDISP_TYPE_PIPMSG:
        if(rootObj.contains("PIP_Message_Configuretion"))
        {
            stDispOsd.id=OSDDISP_TYPE_PIPMSG;
            QJsonObject subObj = rootObj.value("PIP_Message_Configuretion").toObject();
            if(subObj["variable_time"].toInt())
            {
                stDispOsd.value=1;
            }else {
                stDispOsd.value=0;
            }
        }
        break;
    default:
        break;
    }

    qDebug()<<"stDispOsd:"<<stDispOsd.id<<stDispOsd.value;
    return stDispOsd;
}

void mvMethodOsd::SetSingleSel(stDispOsd_INFO setValue)
{
    emit Send_DispOnOff(setValue);
}

stDispOsd_INFO mvMethodOsd::GetItemSpan(int osddisp_type)
{
    stDispOsd_INFO stDispOsd;
    QFile file("/opt/cfg/timming_cfg.json");
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
    }

    QByteArray allData = file.readAll();
    file.close();

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!";
    }
    QJsonObject rootObj = jsonDoc.object();

    switch (osddisp_type) {
    case OSDDISP_TYPE_GRABINDICT:
        if(rootObj.contains("Frame_Grab_Indicator"))
        {
            stDispOsd.id=OSDDISP_TYPE_GRABINDICT;
            QJsonObject subObj = rootObj.value("Frame_Grab_Indicator").toObject();
            stDispOsd.value=subObj["time"].toInt();
        }
        break;
    case OSDDISP_TYPE_SCANMSG:
        if(rootObj.contains("Scan_Input_Configuration"))
        {
            stDispOsd.id=OSDDISP_TYPE_SCANMSG;
            QJsonObject subObj = rootObj.value("Scan_Input_Configuration").toObject();
            stDispOsd.value=subObj["time"].toInt();
        }
        if(json_error.error != QJsonParseError::NoError)
        {
            stDispOsd.id=OSDDISP_TYPE_SCANMSG;
            stDispOsd.value=stSettingData.nScanInputTime;
        }
        break;
    case OSDDISP_TYPE_PIPMSG:
        if(rootObj.contains("PIP_Message_Configuretion"))
        {
            stDispOsd.id=OSDDISP_TYPE_PIPMSG;
            QJsonObject subObj = rootObj.value("PIP_Message_Configuretion").toObject();
            stDispOsd.value=subObj["time"].toInt();
        }
        break;
    case OSDDISP_TYPE_MVIDMSG:
        if(rootObj.contains("Mian_Video"))
        {
            stDispOsd.id=OSDDISP_TYPE_MVIDMSG;
            QJsonObject subObj = rootObj.value("Mian_Video").toObject();
            stDispOsd.value=subObj["time"].toInt();
        }
        if(json_error.error != QJsonParseError::NoError)
        {
            stDispOsd.id=OSDDISP_TYPE_MVIDMSG;
            stDispOsd.value=stSettingData.nMainVideoTime;
        }
        break;
    case OSDDISP_TYPE_SWTMSG:
        if(rootObj.contains("Switch_Input"))
        {
            stDispOsd.id=OSDDISP_TYPE_SWTMSG;
            QJsonObject subObj = rootObj.value("Switch_Input").toObject();
            stDispOsd.value=subObj["time"].toInt();
        }
        if(json_error.error != QJsonParseError::NoError)
        {
            stDispOsd.id=OSDDISP_TYPE_SWTMSG;
            stDispOsd.value=stSettingData.nSwitchInputTime;
        }
        break;
    default:
        break;
    }
    return stDispOsd;
}

void mvMethodOsd::SetItemSpan(stDispOsd_INFO setValue)
{
    emit Send_DispSpan(setValue);
}

void mvMethodOsd::SetOsdMsg(stOsdMsg_INFO stOsdMsg)
{
    emit Send_Msg(stOsdMsg);
}


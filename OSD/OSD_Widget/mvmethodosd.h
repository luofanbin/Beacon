#ifndef MVMETHODOSD_H
#define MVMETHODOSD_H

#include <QObject>
#include <QThread>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusInterface>
#include<QtDBus>
#include <QDebug>
#include <QtDBus/QDBusError>

typedef enum eOSDDISP_TYPE_tag{
    OSDDISP_TYPE_SmallOsd =0,
    OSDDISP_TYPE_SCREENMSG,
    OSDDISP_TYPE_GRABINDICT,
    OSDDISP_TYPE_SCANMSG,
    OSDDISP_TYPE_PIPMSG,
    OSDDISP_TYPE_MVIDMSG,
    OSDDISP_TYPE_SWTMSG,
    OSDDISP_TYPE_Cnt
}OSDDISP_TYPE;

typedef struct StSettingData_Info_tag
{
    int nOnScreenEnable;
    int nRefLive;
    int nScanInputEnable;
    int nScanInputTime;
    int nMainVideoTime;
    int nSwitchInputTime;
}StSettingData;

typedef struct stDispOsd_INFO_tag{
    int id;
    int value;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stDispOsd_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.id;
        argument << arg.value;
        argument.endStructure();
        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stDispOsd_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.id;
        argument >> arg.value;
        argument.endStructure();
        return argument;
    }
}stDispOsd_INFO;
Q_DECLARE_METATYPE(stDispOsd_INFO)

typedef struct stOsdMsg_INFO_tag{
    int id;
    QString value;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stOsdMsg_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.id;
        argument << arg.value;
        argument.endStructure();
        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stOsdMsg_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.id;
        argument >> arg.value;
        argument.endStructure();
        return argument;
    }
}stOsdMsg_INFO;
Q_DECLARE_METATYPE(stOsdMsg_INFO)

class mvMethodOsd : public QThread
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "mv.mvosd.osd.disposd")
public:
    explicit mvMethodOsd();
    void run();
signals:
    void Send_DispOnOff(stDispOsd_INFO);
    void Send_DispSpan(stDispOsd_INFO);
    void Send_Msg(stOsdMsg_INFO);
    void SigSetSingleSel(stDispOsd_INFO);
    void SigSetItemSpan(stDispOsd_INFO);
    void SigSetOsdMsg(stOsdMsg_INFO);
public slots:
    stDispOsd_INFO GetSingleSel(int osddisp_type);
    void SetSingleSel(stDispOsd_INFO setValue);
    stDispOsd_INFO GetItemSpan(int osddisp_type);
    void SetItemSpan(stDispOsd_INFO setValue);
    void SetOsdMsg(stOsdMsg_INFO stOsdMsg);

public:
    StSettingData stSettingData;
};


#endif // MVMETHODOSD_H

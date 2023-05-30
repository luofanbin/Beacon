#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QMutex>
#include "testgrabiamgetime.h"
namespace Ui {
class Widget;
}

typedef enum
{
    ASK_WORKLIST,
    SINGLE_GRAB_START,
    CLEAR_MEMORY,
    SWITCH_INPUT,
    SCAN_INPUTS_ABORT,
    SWITCH_NEXT_INPUT,
    SEND_VALID_INPUTS,
    OUTPUT_ACTIVE,
    GRABBING_ACTIVE,
    SEND_STATUS,
    SET_DATE_TIME,
    SWITCH_OUTPUTS,
    SEND_STATUS_2,
    SEND_VERSION,
    PIP_ON,
    PIP_OFF,

    REBOOT,
    SCAN_INPUTS,
    DOWNLOAD_CONFIGURATION_FILE,
    UPLOAD_CONFIGURATION_FILE,
}enCmdId;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QByteArray ReadDataFromFile(QString strFilePath);
    bool WriteDataToFile(QString strFilePath,char *pFileData);
    void CirculateSendTest();
    void ConnectTimeTest(QTcpSocket *socket);
    bool setCSVData(QString strFilePath,const QStringList& CSVList);
    void AskWorkListTest();
    void GrabImageTest();


private slots:
    void displayStr(QString str);
    bool ConnectTest();
    void on_ConnectTcpServiceButton_clicked();
    void Readyread();
    void on_GrabImageButton_clicked();

    void on_CloseButton_clicked();

    void on_GrabActiveButton_clicked();

    void on_AskWorklistButton_clicked();

    void on_ClearMeMoryButton_clicked();

    void on_SwitchInputButton_clicked();

    void on_ScanInputButton_clicked();

    void on_StopScanInputButton_clicked();

    void on_SwitchNextInputButton_clicked();

    void on_SendValidInputButton_clicked();

    void on_OutputActiveButton_clicked();

    void on_DownCfgFileButton_clicked();

    void on_UploadCfgFileButton_clicked();

    void on_SendStatusButton_clicked();

    void on_SetDateTimeButton_clicked();

    void on_RebootButton_clicked();

    void on_SwitchOutputsButton_clicked();

    void on_SendStatus2Button_clicked();

    void on_SendVersionButton_clicked();

    void on_PipOnButton_clicked();

    void on_PipOffButton_clicked();

    void on_CirculateSendButton_clicked();

    void slotDealSendDataSignal(int nType);
    void on_pushButtonHigh_clicked();

    void on_pushButtonLow_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);
    void chockBoxStatus(int nStatus);

    void on_pushButtonSend_clicked();

    void on_pushButton_3_clicked();

signals:
    void emitSendData(int);
    void emitSendConnect();
    void emmitSendStr(QString);

private:
    Ui::Widget *ui;
    QTcpSocket *m_socket;
    bool blCloseThread;
    int nCmdId;
    QMutex mutex;
    int nDownCount;
    int nSendCount;
    bool isMultiple;
    bool blConnectStutes;
    bool bltuatus;
};

#endif // WIDGET_H

#include "widget.h"
#include "ui_widget.h"
#include "ui_sigvinscaninfo.h"
#include<QDebug>
#include<QFileDialog>
#include<QPixmap>
#include <QMetaType>
#include<QString>
#include<QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QFileInfo>
#include <QTimer>
#include <QFrame>
#include <QDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QStandardItemModel>
#include <QtConcurrent/QtConcurrent>
#include <QtConcurrentRun>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QIcon close_button_ico(":/image/close.png");
    ui->OSD_Hide_pushButton->setIcon(close_button_ico);
    ui->groupBox_8->hide();

    //fist_osd_on_off=0;
    this->setGeometry(151,0,1024,768);
    //this->setFixedSize(1024,768);
    sigvinscan=new ScanningDialog(this);
    sigvinscan->setMouseHide();
    sigvinscan->setGeometry(0,0,150,500);
    sigvinscan->show();
    //Test();

    display_message=new DisplayMessages();
    display_message->setGeometry(0,769,300,80);
    init_set();
    Read_Timming_Cfg_File();
    ui_init();
    slider_instaneventfiliter();//slider控件安装一个事件过滤器
    nTabIndex=2;

}

Widget::~Widget()
{
    dbus_server->terminate();
    dbus_server->wait();
    delete ui;
}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    int dur,pos;
    if(obj==ui->Mouse_Slider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =ui->Mouse_Slider->maximum() - ui->Mouse_Slider->minimum();
                pos = ui->Mouse_Slider->minimum() + dur * ((double)mouseEvent->x() / ui->Mouse_Slider->width()+0.05);
                if(pos != ui->Mouse_Slider->sliderPosition())
                {
                    ui->Mouse_Slider->setValue(pos);
                }
            }
        }
    }else if(obj==ui->Frame_Grab_Slider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =ui->Frame_Grab_Slider->maximum() - ui->Frame_Grab_Slider->minimum();
                pos = ui->Frame_Grab_Slider->minimum() + dur * ((double)mouseEvent->x() / ui->Frame_Grab_Slider->width()+0.05);
                if(pos != ui->Frame_Grab_Slider->sliderPosition())
                {
                      ui->Frame_Grab_Slider->setValue(pos);
                }
            }
        }
    }else if(obj==ui->Scan_Input_Slider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =ui->Scan_Input_Slider->maximum() - ui->Scan_Input_Slider->minimum();
                pos = ui->Scan_Input_Slider->minimum() + dur * ((double)mouseEvent->x() / ui->Scan_Input_Slider->width()+0.05);
                if(pos != ui->Scan_Input_Slider->sliderPosition())
                {
                    ui->Scan_Input_Slider->setValue(pos);
                }
            }
        }
    }else if(obj==ui->PHP_Slider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =ui->PHP_Slider->maximum() - ui->PHP_Slider->minimum();
                pos = ui->PHP_Slider->minimum() + dur * ((double)mouseEvent->x() / ui->PHP_Slider->width()+0.05);
                if(pos != ui->PHP_Slider->sliderPosition())
                {
                    ui->PHP_Slider->setValue(pos);
                }
            }
        }
    }else if(obj==ui->Main_Vedio_Slider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =ui->Main_Vedio_Slider->maximum() - ui->Main_Vedio_Slider->minimum();
                pos = ui->Main_Vedio_Slider->minimum() + dur * ((double)mouseEvent->x() / ui->Main_Vedio_Slider->width()+0.05);
                if(pos != ui->Main_Vedio_Slider->sliderPosition())
                {
                    ui->Main_Vedio_Slider->setValue(pos);
                }
            }
        }
    }else if(obj==ui->Switch_Input_Slider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =ui->Switch_Input_Slider->maximum() - ui->Switch_Input_Slider->minimum();
                pos = ui->Switch_Input_Slider->minimum() + dur * ((double)mouseEvent->x() / ui->Switch_Input_Slider->width()+0.05);
                if(pos != ui->Switch_Input_Slider->sliderPosition())
                {
                    ui->Switch_Input_Slider->setValue(pos);
                }
            }
        }
    }else if(obj==ui->HActiveSlider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =ui->HActiveSlider->maximum() - ui->HActiveSlider->minimum();
                pos = ui->HActiveSlider->minimum() + dur * ((double)mouseEvent->x() / ui->HActiveSlider->width());
                if(pos != ui->HActiveSlider->sliderPosition())
                {
                    ui->HActiveSlider->setValue(pos);
                }
            }
        }
    }else if(obj==ui->VActiveSlider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =ui->VActiveSlider->maximum() - ui->VActiveSlider->minimum();
                pos = ui->VActiveSlider->minimum() + dur * ((double)mouseEvent->x() / ui->VActiveSlider->width());
                if(pos != ui->VActiveSlider->sliderPosition())
                {
                    ui->VActiveSlider->setValue(pos);
                }
            }
        }
    }else if(obj==ui->HTotalSlider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =ui->HTotalSlider->maximum() - ui->HTotalSlider->minimum();
                pos = ui->HTotalSlider->minimum() + dur * ((double)mouseEvent->x() / ui->HTotalSlider->width());
                if(pos != ui->HTotalSlider->sliderPosition())
                {
                    ui->HTotalSlider->setValue(pos);
                }
            }
        }
    }else if(obj==ui->HStartSlider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =ui->HStartSlider->maximum() - ui->HStartSlider->minimum();
                pos = ui->HStartSlider->minimum() + dur * ((double)mouseEvent->x() / ui->HStartSlider->width());
                if(pos != ui->HStartSlider->sliderPosition())
                {
                    ui->HStartSlider->setValue(pos);
                }
            }
        }
    }else if(obj==ui->VStartSlider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =ui->VStartSlider->maximum() - ui->VStartSlider->minimum();
                pos = ui->VStartSlider->minimum() + dur * ((double)mouseEvent->x() / ui->VStartSlider->width());
                if(pos != ui->VStartSlider->sliderPosition())
                {
                    ui->VStartSlider->setValue(pos);
                }
            }
        }
    }

    Video_Adjust->mouse_no_work_time=QTime::currentTime();
    return QObject::eventFilter(obj,event);
}

void Widget::slider_instaneventfiliter()//slider控件安装一个事件过滤器
{
    ui->Mouse_Slider->installEventFilter(this);
    ui->Frame_Grab_Slider->installEventFilter(this);
    ui->Scan_Input_Slider->installEventFilter(this);
    ui->PHP_Slider->installEventFilter(this);
    ui->Main_Vedio_Slider->installEventFilter(this);
    ui->Switch_Input_Slider->installEventFilter(this);

    ui->HActiveSlider->installEventFilter(this);
    ui->VActiveSlider->installEventFilter(this);
    ui->HTotalSlider->installEventFilter(this);
    ui->HStartSlider->installEventFilter(this);
    ui->VStartSlider->installEventFilter(this);
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{    
//    stOsdOnOff_Info osdonoff;
//    osdonoff.id=eDEVFPGA_B;
//    osdonoff.value=1;
//    ubus_interface->osd->SetOnOff(osdonoff);
//    osdonoff.id=eDEVFPGA_C;
//    osdonoff.value=1;
    //    ubus_interface->osd->SetOnOff(osdonoff);
}

void Widget::init_set()
{
    connect(this,SIGNAL(emitDispalyTipsInfo(QString)),this,SLOT(displayTipsInfo(QString)));
    connect(ui->Mouse_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(ui->Frame_Grab_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(ui->Scan_Input_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(ui->PHP_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(ui->Main_Vedio_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(ui->Switch_Input_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));

    connect(ui->HActiveSlider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(ui->VActiveSlider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(ui->HTotalSlider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(ui->HStartSlider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(ui->VStartSlider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));

    connect(ui->Mouse_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed()));
    connect(ui->Frame_Grab_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed()));
    connect(ui->Scan_Input_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed()));
    connect(ui->PHP_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed()));
    connect(ui->Main_Vedio_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed()));
    connect(ui->Switch_Input_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed()));

    connect(ui->HActivespinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed()));
    connect(ui->VActivespinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed()));
    connect(ui->HTotalspinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed()));
    connect(ui->HStartspinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed()));
    connect(ui->VStartspinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed()));

    connect(ui->Net1_IP_Edit,SIGNAL(textEdited(QString)),this,SLOT(LineEditTextChanged(QString)));
    connect(ui->Net1_Mask_Edit,SIGNAL(textEdited(QString)),this,SLOT(LineEditTextChanged(QString)));
    connect(ui->Net2_IP_Edit,SIGNAL(textEdited(QString)),this,SLOT(LineEditTextChanged(QString)));
    connect(ui->Net2_Mask_Edit,SIGNAL(textEdited(QString)),this,SLOT(LineEditTextChanged(QString)));
    connect(ui->Port_Number_2,SIGNAL(textEdited(QString)),this,SLOT(LineEditTextChanged(QString)));
    connect(ui->Storage_IP_Edit,SIGNAL(textEdited(QString)),this,SLOT(LineEditTextChanged(QString)));
    connect(ui->Storage_Port_Edit,SIGNAL(textEdited(QString)),this,SLOT(LineEditTextChanged(QString)));
    connect(ui->Storage_Remote_AE_Edit,SIGNAL(textEdited(QString)),this,SLOT(LineEditTextChanged(QString)));
    connect(ui->Storage_Local_AE_Edit,SIGNAL(textEdited(QString)),this,SLOT(LineEditTextChanged(QString)));
    connect(ui->RIS_IP_Edit,SIGNAL(textEdited(QString)),this,SLOT(LineEditTextChanged(QString)));
    connect(ui->RIS_Port_Edit,SIGNAL(textEdited(QString)),this,SLOT(LineEditTextChanged(QString)));
    connect(ui->RIS_Remote_AE_Edit,SIGNAL(textEdited(QString)),this,SLOT(LineEditTextChanged(QString)));
    connect(ui->RIS_Local_AE_Edit,SIGNAL(textEdited(QString)),this,SLOT(LineEditTextChanged(QString)));

    connect(ui->RefSmallMsg_radioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->LiveSmallMsg_radioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->On_Screen_Set_RadioButton_1,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->On_Screen_Set_RadioButton_2,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->Frame_Grab_RadioButton_1,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->Frame_Grab_RadioButton_2,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->Input_Config_RadioButton_1,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->Input_Config_RadioButton_2,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->PHP_radioButton_1,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->PHP_radioButton_2,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->One_Net_Interface,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->Two_Net_Interface,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->SXGA_Ref_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->WUXGA_Ref_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->SXGA_live_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->WUXGA_live_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->Ref_SDI_1080i_radioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->Ref_SDI_1080p_radioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->Live_SDI_1080i_radioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->Live_SDI_1080p_radioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->BestImage_radioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(ui->Smallest_radioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));

    connect(ui->SetButton,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));
    connect(ui->SaveButton,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));
    connect(ui->CleanButton,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));
    connect(ui->AutoAdjustButton,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));

    connect(ui->Cancel_Changes,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));
    connect(ui->Submit_New_Set,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));

    connect(ui->Switch_Output_Button,SIGNAL(clicked()),this,SLOT(pushButton_Clicked()));
    connect(ui->Switch_Output_Button_2,SIGNAL(clicked()),this,SLOT(pushButton_Clicked()));

    connect(ui->Scan_Ref_pushButton,SIGNAL(clicked()),this,SLOT(pushButton_Clicked()));
    connect(ui->Scan_live_pushButton,SIGNAL(clicked()),this,SLOT(pushButton_Clicked()));
    connect(ui->SwtNextInput_Ref_Button,SIGNAL(clicked()),this,SLOT(pushButton_Clicked()));
    connect(ui->SwtNextInput_live_Button,SIGNAL(clicked()),this,SLOT(pushButton_Clicked()));
    connect(ui->Grab_Image_pushButton,SIGNAL(clicked()),this,SLOT(pushButton_Clicked()));
    connect(ui->Grab_Image_pushButton_2,SIGNAL(clicked()),this,SLOT(pushButton_Clicked()));

    connect(ui->Reboot_Button,SIGNAL(clicked()),this,SLOT(pushButton_Clicked()));
    connect(ui->Video_Adjust_Ref_Button,SIGNAL(clicked()),this,SLOT(pushButton_Clicked()));
    connect(ui->Video_Adjust_live_Button,SIGNAL(clicked()),this,SLOT(pushButton_Clicked()));
    connect(ui->Calibration_Time_Button,SIGNAL(clicked()),this,SLOT(pushButton_Clicked()));
    connect(ui->Reset_Button,SIGNAL(clicked()),this,SLOT(pushButton_Clicked()));

    connect(ui->SmartLock_Ref_CheckBox,SIGNAL(clicked()),this,SLOT(CheckBox_Clicked()));
    connect(ui->SmartLock_live_CheckBox,SIGNAL(clicked()),this,SLOT(CheckBox_Clicked()));

    connect(ui->Output_Ref_checkBox,SIGNAL(clicked()),this,SLOT(CheckBox_Clicked()));
    connect(ui->Output_Ref_checkBox_2,SIGNAL(clicked()),this,SLOT(CheckBox_Clicked()));
    connect(ui->Output_Ref_checkBox_3,SIGNAL(clicked()),this,SLOT(CheckBox_Clicked()));
    connect(ui->Output_Ref_checkBox_4,SIGNAL(clicked()),this,SLOT(CheckBox_Clicked()));

    connect(ui->Output_live_checkBox,SIGNAL(clicked()),this,SLOT(CheckBox_Clicked()));
    connect(ui->Output_live_checkBox_2,SIGNAL(clicked()),this,SLOT(CheckBox_Clicked()));
    connect(ui->Output_live_checkBox_3,SIGNAL(clicked()),this,SLOT(CheckBox_Clicked()));
    connect(ui->Output_live_checkBox_4,SIGNAL(clicked()),this,SLOT(CheckBox_Clicked()));

    connect(ui->Input_Ref_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(ComboBox_currentIndexChanged(int)));
    connect(ui->Input_live_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(ComboBox_currentIndexChanged(int)));

    Video_Adjust=new VideoAdjustment();
    Video_Adjust->setGeometry(151,0,1024,768);
    //Video_Adjust->dlgNewOverlay->setGeometry(200,200,727,300);
    Video_Adjust->dlgOverlayModes->setGeometry(200,200,866,300);
    Video_Adjust->hide();
    ubus_interface=new DbusInterface;

//    connect(Video_Adjust->dlgNewOverlay,&NewOverlayMode::sendOverlayModeData,[&](int nIndex,stSCAL_ANALOG_MODE_PARAMS stValue){
//        if(nIndex==SaveOverlayData)
//            ubus_interface->VinDispSetAnalogParams(stValue);

//        if(nIndex==DebugOverlayData)
//            ubus_interface->VinDispDebugAnalogParams(stValue);
//    });

    connect(Video_Adjust->dlgOverlayModes,&OverlayModes::emitOverlayModesIndex,[&](int nIndex){
            ubus_interface->VinDispSetAnalogOverlay(nIndex);
    });

    connect(Video_Adjust,&VideoAdjustment::emitSetOverlayCtrlMethod,[&](int val){
            ubus_interface->VinDispSetOverlayCtrlMethod(val);
    });

    connect(Video_Adjust,&VideoAdjustment::Set_AutoSetup,[&](stAuto_INFO stValue_Info){
        QtConcurrent::run(this,&Widget::SetAutoSetup,stValue_Info);
    });
   // connect(ubus_interface,SIGNAL(emitSaveOverlayModeOk()),Video_Adjust->dlgNewOverlay,SLOT(slotSaveOverlayModeOk()));
    connect(this,SIGNAL(emitSetOverlayModesData(int,int,stSCAL_ANALOG_MODE_PARAMS_Index_Array)),Video_Adjust->dlgOverlayModes,SLOT(displayTableData(int,int,stSCAL_ANALOG_MODE_PARAMS_Index_Array)));

    connect(Video_Adjust,SIGNAL(Set_Value(int,stVALUE_INFO)),this,SLOT(SetValue(int,stVALUE_INFO)));
    connect(Video_Adjust,SIGNAL(Set_ColorTemp(stDISP_COLORTEMP)),ubus_interface,SLOT(VidSigIn_SetCTemp(stDISP_COLORTEMP )));
    connect(Video_Adjust,SIGNAL(Set_SCaling(stVIDGOUT_SCAL)),ubus_interface,SLOT(VidSigIn_SetScaling(stVIDGOUT_SCAL)));
    //connect(Video_Adjust,SIGNAL(Set_AutoSetup(stAuto_INFO)),this,SLOT(SetAutoSetup(stAuto_INFO)));
    connect(Video_Adjust,SIGNAL(Set_PresetCfg(int)),this,SLOT(SetPresetCfg(int)));
    connect(Video_Adjust,SIGNAL(Get_DP_Info(int)),this,SLOT(gt_DP_INFO(int)));
    connect(Video_Adjust,SIGNAL(Set_DP_Info(stSCAL_INPUT_DP_INFO)),this,SLOT(st_DP_INFO(stSCAL_INPUT_DP_INFO)));
    connect(Video_Adjust,SIGNAL(Read_CTmep_Scaing(int)),this,SLOT(slot_Read_CTmep_Scaing(int)));
    connect(Video_Adjust,SIGNAL(emitOverlayModes(int)),this,SLOT(slotGetAnalogOverlay(int)));

    connect(ubus_interface,SIGNAL(Sig_GetValue(int,stVALUE_INFO)),this,SLOT(GetValue(int,stVALUE_INFO)));
    connect(ubus_interface,SIGNAL(Sig_GetCalibTime(bool,stTIME_INFO)),this,SLOT(GetCalibTime(bool,stTIME_INFO)));
    connect(ubus_interface,SIGNAL(Sig_GetColorTemp(stDISP_COLORTEMP)),Video_Adjust,SLOT(SetColorTempControlValue(stDISP_COLORTEMP)));
    connect(ubus_interface,SIGNAL(Sig_GetScaling(stVIDGOUT_SCAL)),Video_Adjust,SLOT(SetScalingControlValue(stVIDGOUT_SCAL)));
    connect(ubus_interface,SIGNAL(Sig_GetDevcomm_Srv(int,stDEVCOMM_SVR)),this,SLOT(GetDevcomm_Srv(int,stDEVCOMM_SVR)));
    connect(ubus_interface,SIGNAL(Sig_GetDevcomm_Net_IP(stDEVCOMM_NET)),this,SLOT(GetDevcomm_Net_IP(stDEVCOMM_NET)));
    connect(ubus_interface,SIGNAL(Sig_GetDevcomm_Net_Mac(stDEVCOMM_MAC)),this,SLOT(GetDevcomm_Net_Mac(stDEVCOMM_MAC)));
    connect(ubus_interface,SIGNAL(Sig_GetDevVer(stCfg_Ver_INFO)),this,SLOT(GetDevVer(stCfg_Ver_INFO)));
    connect(ubus_interface,SIGNAL(Sig_GetDevcomm_Net_Select_Port(int,int)),this,SLOT(GetDevcomm_Net_Select_Port(int,int)));
    connect(ubus_interface,SIGNAL(Sig_GetRouter(stRouter_Out)),this,SLOT(GetRouter(stRouter_Out)));
    connect(ubus_interface,SIGNAL(Sig_VidSigIn_GetStatus(int,stVIDSIGIN_STATUS_ARRAY)),this,SLOT(VidSigIn_GetStatus(int,stVIDSIGIN_STATUS_ARRAY)));
    connect(ubus_interface,SIGNAL(Sig_VinScan(int,stScan)),this,SLOT(VidSigIn_Scan(int,stScan)));
    connect(ubus_interface,SIGNAL(Sig_VinScanAbort(uchar)),this,SLOT(StopScan(uchar)));
    connect(ubus_interface,SIGNAL(Sig_OutPortGetOnOff(PortStatus)),this,SLOT(VidSigOutPort_GetOnOff(PortStatus)));
    connect(ubus_interface,SIGNAL(Sig_GtFrequency_INFO(gtFrequency_INFO)),Video_Adjust,SLOT(SetFrequencySliderValue(gtFrequency_INFO)));
    connect(ubus_interface,SIGNAL(Sig_SwtNextInput(SwitchNextSigOut)),this,SLOT(SigSwtNextInput(SwitchNextSigOut)));
    connect(ubus_interface,SIGNAL(Sig_SigSetGrabIndcatorSel(uchar)),this,SLOT(Slot_SigSetGrabIndcatorSel(uchar)));
    connect(ubus_interface,SIGNAL(Sig_SigSetFrozSpan(stFans_INFO)),this,SLOT(Slot_SigSetFrozSpan(stFans_INFO)));
    connect(ubus_interface,SIGNAL(Sig_SetMsg(QString)),this,SLOT(Slot_SetOsdMsg(QString)));
    connect(ubus_interface,SIGNAL(Sig_OsdOnOff(stOsdOnOff_Info)),this,SLOT(Slot_OsdOnOff(stOsdOnOff_Info)));
    connect(ubus_interface,SIGNAL(Sig_OutPortGetSdiType(stOutSig_INFO)),this,SLOT(slot_VidSigOutPortSdiType(stOutSig_INFO)));
    connect(ubus_interface,SIGNAL(emitSingleGrabStart(stGrabImageStaus_INFO)),this,SLOT(slotSingleGrabStart(stGrabImageStaus_INFO)));
    connect(ubus_interface,SIGNAL(SigSetRouteNotice(uchar)),this,SLOT(slotSetRouteNotice(uchar)));
    connect(ubus_interface,SIGNAL(SigSetSwtOutput(uchar)),this,SLOT(slotSetSwtOutput(uchar)));

    dbus_server=new mvMethodOsd();
    dbus_server->start();
    connect(dbus_server,SIGNAL(Send_DispOnOff(stDispOsd_INFO)),this,SLOT(Slot_SetSingleSel(stDispOsd_INFO)));
    connect(dbus_server,SIGNAL(Send_DispSpan(stDispOsd_INFO)),this,SLOT(Slot_SetItemSpan(stDispOsd_INFO)));

    QIcon reboot_button_ico(":/image/reboot.png");
    ui->Reboot_Button->setIcon(reboot_button_ico);
    ui->Reboot_Button->setStyleSheet("border:2px groove gray;border-radius:20px;padding:2px 4px;");

}

void Widget::ui_init()
{
    ui->groupBox_9->hide();
    nDisplaySmallOsdCount=0;
  /*
    stOsdOnOff_Info osdonoff;
    osdonoff.id=eDEVFPGA_B;
    osdonoff.value=0;
    ubus_interface->osd->SetScanListOnOff(osdonoff);
    ubus_interface->osd->SetSmallOsdOnOff(osdonoff);
    ubus_interface->osd->SetOnOff(osdonoff);
    osdonoff.id=eDEVFPGA_C;
    osdonoff.value=0;
    ubus_interface->osd->SetScanListOnOff(osdonoff);
    ubus_interface->osd->SetSmallOsdOnOff(osdonoff);
    ubus_interface->osd->SetOnOff(osdonoff);
*/


    ui->Mouse_checkBox->setHidden(true);
    ui->Mouse_checkBox->setChecked(true);
    //ui->OSD_Hide_pushButton->setHidden(true);
    ui->groupBox_7->setEnabled(false);
    ui->groupBox->setEnabled(false);
    ui->Firmware_Upgrade_Group->setEnabled(false);
    ui->Reset_Button->setEnabled(false);
    ui->Reset_comboBox->setEnabled(false);
    ui->Cancel_Changes->setEnabled(false);
    ui->Submit_New_Set->setEnabled(false);


    uchar grab;
    ubus_interface->getGrabIndcatorSel(&grab);
    if(grab==0)
        ui->Frame_Grab_RadioButton_1->setChecked(true);
    else
        ui->Frame_Grab_RadioButton_2->setChecked(true);

    uchar grab_time;
    ubus_interface->getFrozSpan(&grab_time);
    ui->Frame_Grab_Slider->setValue(grab_time);
    ui->Input_RGB_Ref_radioButton->setEnabled(false);
    ui->Input_YPrPb_Ref_radioButton->setEnabled(false);
    ui->Input_Y_Ref_radioButton->setEnabled(false);
    ui->Input_RGB_live_radioButton->setEnabled(false);
    ui->Input_YPrPb_live_radioButton->setEnabled(false);
    ui->Input_Y_live_radioButton->setEnabled(false);

//    stOutSig_INFO stRoutSigID;
//    stRoutSigID.gid=eVIDSIGOUT_G1;
//    stRoutSigID.sigid=eDEVPORTOUT_DVI_A;
//    gtOutSig_INFO gtRoutSigStatus;
//    ubus_interface->VidSigOutPort_GetOnOff(stRoutSigID,&gtRoutSigStatus);
//    if(gtRoutSigStatus.value==1)
    ui->Output_Ref_checkBox->setChecked(true);
    ui->Output_live_checkBox->setChecked(true);

    stOutSig_INFO SDIType;
    ubus_interface->VidOutPort_GetSDIType(1,&SDIType);
    if(SDIType.sigid==0)
        ui->Ref_SDI_1080p_radioButton->setChecked(true);
    else if(SDIType.sigid==1)
        ui->Ref_SDI_1080i_radioButton->setChecked(true);

    stOutSig_INFO SDIType_2;
    ubus_interface->VidOutPort_GetSDIType(1,&SDIType_2);
    if(SDIType_2.sigid==0)
        ui->Live_SDI_1080p_radioButton->setChecked(true);
    else if(SDIType.sigid==1)
        ui->Live_SDI_1080i_radioButton->setChecked(true);

    ubus_interface->VidSigOut_GetFormat(eVIDSIGOUT_G1);
    ubus_interface->VidSigOut_GetFormat(eVIDSIGOUT_G2);
    ubus_interface->VidSigOut_GetSmartlock(eVIDSIGOUT_G1);
    ubus_interface->VidSigOut_GetSmartlock(eVIDSIGOUT_G2);

    stRouter GetRouterId;
    ubus_interface->VidRout_GetRouter(eVIDSIGOUT_G1,&GetRouterId);
    if((GetRouterId.uiVidIn<eVIDSIGIN_DVI_D3) || (GetRouterId.uiVidIn==eVIDSIGIN_HDMI3) || (GetRouterId.uiVidIn>eVIDSIGIN_DVI_D4))
        return;
    if(GetRouterId.uiVidIn!=ui->Input_Ref_ComboBox->currentIndex()+1)
        read_InputSig_ref=true;
    ui->Input_Ref_ComboBox->setCurrentIndex(GetRouterId.uiVidIn-1);
    Video_Adjust->SigInId=GetRouterId.uiVidIn;
    nRefCurrSigId=GetRouterId.uiVidIn;

    uchar uOnOff;
    ubus_interface->VidRout_GetSwtOutput(&uOnOff);
    if(uOnOff==0)
    {
        ui->Switch_Output_Button->setStyleSheet("background-color:rgb(0,117,255)");
        ui->Switch_Output_Button_2->setStyleSheet("background-color:rgb(0,117,255)");
    }else {
        ui->Switch_Output_Button->setStyleSheet("background-color:rgb(240,240,240)");
        ui->Switch_Output_Button_2->setStyleSheet("background-color:rgb(240,240,240)");
    }


//    QDBusPendingReply<int> n_interlace_video_value =  ubus_interface->Router->GetInterlaceVideo();
//    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
//    //所以需要调用waitARForFinished来等到Message执行完成
//    n_interlace_video_value.waitForFinished();
//    if (n_interlace_video_value.isValid())
//    {
//        if(n_interlace_video_value.value()==1)
           ui->BestImage_radioButton->setChecked(true);
//        else
//           ui->Smallest_radioButton->setChecked(true);
//    }
//    else
//    {
//        qDebug() << "value method called failed!";
//    }

    stOsdOnOff_Info refOsdOnOff;
    QDBusPendingReply<stOsdOnOff_Info> reply = ubus_interface->osd->GetOnOff(eDEVFPGA_B);
    reply.waitForFinished();
    if (reply.isValid())
        refOsdOnOff=reply.value();

    stOsdOnOff_Info liveOsdOnOff;
    QDBusPendingReply<stOsdOnOff_Info> reply1 = ubus_interface->osd->GetOnOff(eDEVFPGA_C);
    reply.waitForFinished();
    if (reply.isValid())
        liveOsdOnOff=reply1.value();




    if((refOsdOnOff.value==1) || (liveOsdOnOff.value==1))
        EnableControlCursor();
    else
        DisableControlCursor();
}

int Widget::Read_Timming_Cfg_File()
{
    QFileInfo IsFile("/opt/cfg/timming_cfg.json");
    if(!IsFile.isFile())
    {
        Init_Timming_Cfg_File();
    }
    else
    {
        QFile file("/opt/cfg/timming_cfg.json");
        if(!file.open(QIODevice::ReadOnly)) {
            qDebug() << "File open error";
        }

        QByteArray allData = file.readAll();
        file.close();

        QJsonParseError json_error;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
        if(json_error.error != QJsonParseError::NoError)
        {
            qDebug()<<json_error.error;
            Init_Timming_Cfg_File();
            qDebug() << "json error!";
            return -1;
        }
        QJsonObject rootObj = jsonDoc.object();

        //因为是预先定义好的JSON数据格式，所以这里可以这样读取
        if(rootObj.contains("SmallOsd"))
        {
            QJsonObject subObj = rootObj.value("SmallOsd").toObject();
            if(subObj["enable"].toInt()==eDEVFPGA_B)
            {
                ui->RefSmallMsg_radioButton->setChecked(true);
            }
            if(subObj["enable"].toInt()==eDEVFPGA_C)
            {
                ui->LiveSmallMsg_radioButton->setChecked(true);
            }
            dbus_server->stSettingData.nRefLive=subObj["enable"].toInt();
            //ui->Mouse_Slider->setValue(subObj["time"].toInt());
        }
        if(rootObj.contains("On_Screen"))
        {
            QJsonObject subObj = rootObj.value("On_Screen").toObject();
            if(subObj["enable"].toInt()==1)
            {
                ui->On_Screen_Set_RadioButton_2->setChecked(true);
                ui->RefSmallMsg_radioButton->setEnabled(true);
                ui->LiveSmallMsg_radioButton->setEnabled(true);
            }else {
                ui->On_Screen_Set_RadioButton_1->setChecked(true);
                ui->RefSmallMsg_radioButton->setDisabled(true);
                ui->LiveSmallMsg_radioButton->setDisabled(true);
            }
            dbus_server->stSettingData.nOnScreenEnable=subObj["enable"].toInt();
        }
        if(rootObj.contains("Scan_Input_Configuration"))
        {
            QJsonObject subObj = rootObj.value("Scan_Input_Configuration").toObject();
            if(subObj["disp_message"].toInt()==1)
            {
                ui->Input_Config_RadioButton_2->setChecked(true);
            }else{
                ui->Input_Config_RadioButton_1->setChecked(true);
            }
            ui->Scan_Input_Slider->setValue(subObj["time"].toInt());
            dbus_server->stSettingData.nScanInputEnable=subObj["disp_message"].toInt();
            dbus_server->stSettingData.nScanInputTime=subObj["time"].toInt();
        }
        if(rootObj.contains("PIP_Message_Configuretion"))
        {
            QJsonObject subObj = rootObj.value("PIP_Message_Configuretion").toObject();
            ui->PHP_Slider->setValue(subObj["time"].toInt());
            if(subObj["variable_time"].toInt()==1)
            {
                ui->PHP_radioButton_2->setChecked(true);
                ui->PHP_Slider->setEnabled(true);
                ui->PHP_spinBox->setEnabled(true);
            }else {
                ui->PHP_radioButton_1->setChecked(true);
                ui->PHP_Slider->setEnabled(false);
                ui->PHP_spinBox->setEnabled(false);
            }
        }
        if(rootObj.contains("Mian_Video"))
        {
            QJsonObject subObj = rootObj.value("Mian_Video").toObject();
            ui->Main_Vedio_Slider->setValue(subObj["time"].toInt());
            dbus_server->stSettingData.nMainVideoTime=subObj["time"].toInt();
        }
        if(rootObj.contains("Switch_Input"))
        {
            QJsonObject subObj = rootObj.value("Switch_Input").toObject();
            ui->Switch_Input_Slider->setValue(subObj["time"].toInt());
            dbus_server->stSettingData.nSwitchInputTime=subObj["time"].toInt();
        }
    }
    return 0;
}

int Widget::Write_Timming_Cfg_File()
{
    int isOkFile=0;
    QFile file("/opt/cfg/timming_cfg.json");
    for(int i=0;i<10;i++)
    {
        if(!file.open(QIODevice::WriteOnly)) {
            qDebug() << "Write File open error";
        }
        QJsonObject OSD_CFG;
        QJsonObject SmallOsd;
        if(ui->RefSmallMsg_radioButton->isChecked())
        {
            SmallOsd.insert("enable",eDEVFPGA_B);
            dbus_server->stSettingData.nRefLive=eDEVFPGA_B;
        }
        else if(ui->LiveSmallMsg_radioButton->isChecked())
        {
           SmallOsd.insert("enable",eDEVFPGA_C);
           dbus_server->stSettingData.nRefLive=eDEVFPGA_C;
        }
        else
        {
           SmallOsd.insert("enable",0);
           dbus_server->stSettingData.nRefLive=0;
        }
        //SmallOsd.insert("time",ui->Mouse_spinBox->value());

        QJsonObject On_Screen;
        if(ui->On_Screen_Set_RadioButton_2->isChecked())
        {
            On_Screen.insert("enable",1);
            dbus_server->stSettingData.nOnScreenEnable=1;
        }
        else
        {
            On_Screen.insert("enable",0);
            dbus_server->stSettingData.nOnScreenEnable=0;
        }

        QJsonObject Scan_Input_Configuration;
        if(ui->Input_Config_RadioButton_2->isChecked())
        {
            Scan_Input_Configuration.insert("disp_message",1);
            dbus_server->stSettingData.nScanInputEnable=1;
        }
        else
        {
            Scan_Input_Configuration.insert("disp_message",0);
            dbus_server->stSettingData.nScanInputEnable=0;
        }
        Scan_Input_Configuration.insert("time",ui->Scan_Input_spinBox->value());
        dbus_server->stSettingData.nScanInputTime=ui->Scan_Input_spinBox->value();

        QJsonObject PIP_Message_Configuretion;
        if(ui->PHP_radioButton_1->isChecked())
        {
            PIP_Message_Configuretion.insert("variable_time",0);
        }
        else
        {
            PIP_Message_Configuretion.insert("variable_time",1);
        }
        PIP_Message_Configuretion.insert("time",ui->PHP_spinBox->value());

        QJsonObject Mian_Video;
        Mian_Video.insert("time",ui->Main_Vedio_spinBox->value());
        dbus_server->stSettingData.nMainVideoTime=ui->Main_Vedio_spinBox->value();

        QJsonObject Switch_Input;
        Switch_Input.insert("time",ui->Switch_Input_spinBox->value());
        dbus_server->stSettingData.nSwitchInputTime=ui->Switch_Input_spinBox->value();

        OSD_CFG.insert("SmallOsd",SmallOsd);
        OSD_CFG.insert("On_Screen",On_Screen);
        OSD_CFG.insert("Scan_Input_Configuration",Scan_Input_Configuration);
        OSD_CFG.insert("PIP_Message_Configuretion",PIP_Message_Configuretion);
        OSD_CFG.insert("Mian_Video",Mian_Video);
        OSD_CFG.insert("Switch_Input",Switch_Input);

        QJsonDocument document;

        document.setObject(OSD_CFG);

        QByteArray byteArray = document.toJson(QJsonDocument::Compact);

        QString str(byteArray);

        QTextStream in(&file);

        in<<str;
        file.close();

        if(!file.open(QIODevice::ReadOnly)) {
            qDebug() << " Read File open error";
        }

        QByteArray allData = file.readAll();
        file.close();

        QJsonParseError json_error;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
        if(json_error.error == QJsonParseError::NoError)
        {
            isOkFile=1;
            break;
        }
    }

    if(isOkFile==0)
        Init_Timming_Cfg_File();

    return 0;
}

int Widget::Init_Timming_Cfg_File()
{
    ui->RefSmallMsg_radioButton->setChecked(true);
    dbus_server->stSettingData.nRefLive=2;
    //ui->Mouse_Slider->setValue(30);

    ui->On_Screen_Set_RadioButton_2->setChecked(true);
    dbus_server->stSettingData.nOnScreenEnable=1;

    ui->Input_Config_RadioButton_2->setChecked(true);
    dbus_server->stSettingData.nScanInputEnable=1;
    ui->Scan_Input_Slider->setValue(2);
    dbus_server->stSettingData.nScanInputTime=2;

    ui->PHP_radioButton_2->setChecked(true);
    ui->PHP_spinBox->setValue(10);

    ui->Main_Vedio_Slider->setValue(3);
    dbus_server->stSettingData.nMainVideoTime=3;

    ui->Switch_Input_Slider->setValue(3);
    dbus_server->stSettingData.nSwitchInputTime=3;
}

void Widget::GetPresetParams(bool blIsValid)
{
    stSCAL_PRESET_PARAMS_INFO psPresetParams;
    ubus_interface->VidSigIn_GetPresetParams(Video_Adjust->SigInId, &psPresetParams);

    Video_Adjust->SetControlIsEnable(Video_Adjust->SigInId,blIsValid);

    if(psPresetParams.bDither==0)
        Video_Adjust->Dither_CheckBox->setChecked(false);
    else
        Video_Adjust->Dither_CheckBox->setChecked(true);

    stVALUE_INFO stValue;
    stHVStart stHVStart;
    stHVStart.sigid=Video_Adjust->SigInId;
    stValue.type=Video_Adjust->SigInId;
    stValue.value=psPresetParams.uiBrightness;
    Video_Adjust->SetBrightnessSliderValue(stValue);

    stValue.value=psPresetParams.uiContrast;
    Video_Adjust->SetContrastSliderValue(stValue);


     stValue.value=psPresetParams.uiColor;
     Video_Adjust->SetColorSliderValue(stValue);

     stValue.value=psPresetParams.uiHue;
     Video_Adjust->SetHueSliderValue(stValue);

     stValue.value=psPresetParams.uiSharpness;
     Video_Adjust->SetSharpnessSliderValue(stValue);

     stDISP_COLORTEMP stColorTemp;
     stColorTemp.uiDispSigId=Video_Adjust->SigInId;
     stColorTemp.uiCTempVal=psPresetParams.uiCTempVal;
     stColorTemp.uiCTR=psPresetParams.uiCTR;
     stColorTemp.uiCTG=psPresetParams.uiCTG;
     stColorTemp.uiCTB=psPresetParams.uiCTB;
     Video_Adjust->SetColorTempControlValue(stColorTemp);

     stValue.value=psPresetParams.uiGamma;
     Video_Adjust->SetGammaControlValue(stValue);

     stVIDGOUT_SCAL stScaling;
     stScaling.uiSigId=Video_Adjust->SigInId;
     stScaling.uiScalVal=psPresetParams.uiScalVal;
     stScaling.uiAdjVal=psPresetParams.uiScalAdjVal;
     stScaling.uiFramHth=psPresetParams.HScaling;
     Video_Adjust->SetScalingControlValue(stScaling);

     stValue.value=psPresetParams.uiNR;
     Video_Adjust->SetNoiseSliderValue(stValue);

     stValue.value=psPresetParams.uiClampwidth;
     Video_Adjust->SetClampwidthSliderValue(stValue);

     if(Video_Adjust->SigInId==eVIDSIGIN_CVBS || Video_Adjust->SigInId==eVIDSIGIN_S_VIDEO1 || Video_Adjust->SigInId==eVIDSIGIN_S_VIDEO2
       || Video_Adjust->SigInId==eVIDSIGIN_DVI_A1 || Video_Adjust->SigInId==eVIDSIGIN_DVI_A2)
     {
         stValue.value=psPresetParams.BandwidthValue;
         Video_Adjust->SetBandwidthControlValue(stValue);
     }

     stValue.value=psPresetParams.uiVGAPhase;
     Video_Adjust->SetPhaseSliderValue(stValue);

     stHVStart.HVStartValue=psPresetParams.uiHStart;
     //Video_Adjust->SetHStartSliderValue(stHVStart,psPresetParams.uiHStartMin,psPresetParams.uiHStartMax);

     stHVStart.HVStartValue=psPresetParams.uiVStart;
     //Video_Adjust->SetVStartSliderValue(stHVStart,psPresetParams.uiVStartMin,psPresetParams.uiVStartMax);

     if(Video_Adjust->SigInId==eVIDSIGIN_DVI_A1 || Video_Adjust->SigInId==eVIDSIGIN_DVI_A2)
     {
         gtFrequency_INFO gtFrequency;
         gtFrequency.currtvalue=psPresetParams.uiVGAHtotal;
         gtFrequency.minvlaue=psPresetParams.uiVGAHtotal_Min;
         gtFrequency.maxvlaue=psPresetParams.uiVGAHtotal_Max;
         Video_Adjust->SetFrequencySliderValue(gtFrequency);
     }else
     {
         Video_Adjust->label_33->setEnabled(false);
         Video_Adjust->Frequency_Slider->setEnabled(false);
         Video_Adjust->Frequency_spinBox->setEnabled(false);
     }

     int val;
     ubus_interface->VinDispGetOverlayCtrlMethod(&val);
     Video_Adjust->SetAutomaticValue(val);
}

void Widget::EnableControlCursor()
{
    ui->Mouse_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->On_Screen_Set_RadioButton_1->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->On_Screen_Set_RadioButton_2->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Frame_Grab_RadioButton_1->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Frame_Grab_RadioButton_2->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Frame_Grab_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Input_Config_RadioButton_1->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Input_Config_RadioButton_2->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Scan_Input_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->PHP_radioButton_1->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->PHP_radioButton_2->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->PHP_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Main_Vedio_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Switch_Input_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->One_Net_Interface->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Two_Net_Interface->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Input_Ref_ComboBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->SwtNextInput_Ref_Button->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Video_Adjust_Ref_Button->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Output_Ref_checkBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Output_Ref_checkBox_2->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Output_Ref_checkBox_3->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Output_Ref_checkBox_4->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->SXGA_Ref_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->WUXGA_Ref_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->SmartLock_Ref_CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Input_live_ComboBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->SwtNextInput_live_Button->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Video_Adjust_live_Button->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Output_live_checkBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Output_live_checkBox_2->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Output_live_checkBox_3->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Output_live_checkBox_4->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->SXGA_live_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->WUXGA_live_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->SmartLock_live_CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Scan_Ref_pushButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Switch_Output_Button->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Grab_Image_pushButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Scan_live_pushButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Switch_Output_Button_2->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Grab_Image_pushButton_2->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Reboot_Button->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->dateTimeEdit->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Calibration_Time_Button->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->tabWidget->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->OSD_Hide_pushButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    ui->HActiveSlider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->HActivespinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->VActiveSlider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->VActivespinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->HTotalSlider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->HTotalspinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->HStartSlider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->HStartspinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->VStartSlider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->VStartspinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->SetButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->AutoAdjustButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->SaveButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->CleanButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    ui->BestImage_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Smallest_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    Video_Adjust->EnableControlCursor();
}

void Widget::DisableControlCursor()
{
    ui->Mouse_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->On_Screen_Set_RadioButton_1->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->On_Screen_Set_RadioButton_2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Frame_Grab_RadioButton_1->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Frame_Grab_RadioButton_2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Frame_Grab_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Input_Config_RadioButton_1->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Input_Config_RadioButton_2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Scan_Input_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->PHP_radioButton_1->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->PHP_radioButton_2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->PHP_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Main_Vedio_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Switch_Input_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->One_Net_Interface->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Two_Net_Interface->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Input_Ref_ComboBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->SwtNextInput_Ref_Button->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Video_Adjust_Ref_Button->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Output_Ref_checkBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Output_Ref_checkBox_2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Output_Ref_checkBox_3->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Output_Ref_checkBox_4->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->SXGA_Ref_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->WUXGA_Ref_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->SmartLock_Ref_CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Input_live_ComboBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->SwtNextInput_live_Button->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Video_Adjust_live_Button->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Output_live_checkBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Output_live_checkBox_2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Output_live_checkBox_3->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Output_live_checkBox_4->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->SXGA_live_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->WUXGA_live_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->SmartLock_live_CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Scan_Ref_pushButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Switch_Output_Button->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Grab_Image_pushButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Scan_live_pushButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Switch_Output_Button_2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Grab_Image_pushButton_2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Reboot_Button->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->dateTimeEdit->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Calibration_Time_Button->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->tabWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->OSD_Hide_pushButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    ui->HActiveSlider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->HActivespinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->VActiveSlider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->VActivespinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->HTotalSlider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->HTotalspinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->HStartSlider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->HStartspinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->VStartSlider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->VStartspinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->SetButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->AutoAdjustButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->SaveButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->CleanButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    ui->BestImage_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->Smallest_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    Video_Adjust->DisableControlCursor();
}

void Widget::Slot_SetSingleSel(stDispOsd_INFO setValue)
{
    switch (setValue.id) {
    case OSDDISP_TYPE_SmallOsd:
        if(setValue.value==eDEVFPGA_B)
            ui->RefSmallMsg_radioButton->setChecked(true);
        if(setValue.value==eDEVFPGA_C)
            ui->LiveSmallMsg_radioButton->setChecked(true);

        Write_Timming_Cfg_File();
        break;
    case OSDDISP_TYPE_SCREENMSG:
        if(setValue.value==0)
        {
            ui->On_Screen_Set_RadioButton_1->setChecked(true);
            ui->RefSmallMsg_radioButton->setDisabled(true);
            ui->LiveSmallMsg_radioButton->setDisabled(true);
        }
        else
        {
            ui->On_Screen_Set_RadioButton_2->setChecked(true);
            ui->RefSmallMsg_radioButton->setEnabled(true);
            ui->LiveSmallMsg_radioButton->setEnabled(true);
        }

        Write_Timming_Cfg_File();
        break;
     case OSDDISP_TYPE_GRABINDICT:
        if(setValue.value==0)
            ui->Frame_Grab_RadioButton_1->setChecked(true);
        else
            ui->Frame_Grab_RadioButton_2->setChecked(true);

        Write_Timming_Cfg_File();
        break;
     case OSDDISP_TYPE_SCANMSG:
        if(setValue.value==0)
            ui->Input_Config_RadioButton_1->setChecked(true);
        else
            ui->Input_Config_RadioButton_2->setChecked(true);
        Write_Timming_Cfg_File();
        break;
     case OSDDISP_TYPE_PIPMSG:
        if(setValue.value==0)
            ui->PHP_radioButton_1->setChecked(true);
        else
            ui->PHP_radioButton_2->setChecked(true);
        Write_Timming_Cfg_File();
        break;
    default:
        break;
    }
}

void Widget::Slot_SetItemSpan(stDispOsd_INFO setValue)
{
    if(setValue.id==OSDDISP_TYPE_GRABINDICT)
    {
        ui->Frame_Grab_Slider->setValue(setValue.value);
    }else if(setValue.id==OSDDISP_TYPE_SCANMSG)
    {
        ui->Scan_Input_Slider->setValue(setValue.value);
    }else if(setValue.id==OSDDISP_TYPE_PIPMSG)
    {
        ui->PHP_Slider->setValue(setValue.value);
    }else if(setValue.id==OSDDISP_TYPE_MVIDMSG)
    {
        ui->Main_Vedio_Slider->setValue(setValue.value);
    }else if(setValue.id==OSDDISP_TYPE_SWTMSG)
    {
        ui->Switch_Input_Slider->setValue(setValue.value);
    }
}

void Widget::Slot_SigSetGrabIndcatorSel(uchar span_val)
{
    if(span_val==0)
        ui->Frame_Grab_RadioButton_1->setChecked(true);
    else if(span_val==1)
        ui->Frame_Grab_RadioButton_2->setChecked(true);
}

void Widget::Slot_SigSetFrozSpan(stFans_INFO stFrozSpan)
{
    if(stFrozSpan.id==1)
        ui->Frame_Grab_Slider->setValue(stFrozSpan.value);
}

void Widget::Slot_SetOsdMsg(QString setMsg)
{
    if(ui->On_Screen_Set_RadioButton_1->isChecked())
        return;

    QMessageBox::warning(this, tr("Warning"), setMsg, QMessageBox::Ok);
}

void Widget::Slot_OsdOnOff(stOsdOnOff_Info OnOff)
{
    qDebug()<<"OSD OnOff:"<<OnOff.id<<OnOff.value;
    if(OnOff.value==1)
        EnableControlCursor();
    else
        DisableControlCursor();
}

void Widget::slotSingleGrabStart(stGrabImageStaus_INFO stGrabImageStaus)
{
    if(stGrabImageStaus.id==GRABIMG_SRCID_OSD)
    {
        ui->Grab_Image_pushButton->setEnabled(true);
        ui->Grab_Image_pushButton_2->setEnabled(true);
    }
}

void Widget::Slider_Value_Changed(int value1)
{
    QSlider* Slider = qobject_cast<QSlider*>(sender());
    int value=0;
    if(Slider->objectName()=="Frame_Grab_Slider")
    {
        value=ui->Frame_Grab_Slider->value();
        ui->Frame_Grab_spinBox->setValue(value);
    }else if(Slider->objectName()=="Scan_Input_Slider")
    {
        value=ui->Scan_Input_Slider->value();
        ui->Scan_Input_spinBox->setValue(value);
    }else if(Slider->objectName()=="Mouse_Slider")
    {
        value=ui->Mouse_Slider->value();
        ui->Mouse_spinBox->setValue(value);
    }else if(Slider->objectName()=="PHP_Slider")
    {
        value=ui->PHP_Slider->value();
        ui->PHP_spinBox->setValue(value);
    }else if(Slider->objectName()=="Main_Vedio_Slider")
    {
        value=ui->Main_Vedio_Slider->value();
        ui->Main_Vedio_spinBox->setValue(value);
    }else if(Slider->objectName()=="Switch_Input_Slider")
    {
        value=ui->Switch_Input_Slider->value();
        ui->Switch_Input_spinBox->setValue(value);
    }else if(Slider->objectName()=="HActiveSlider")
        ui->HActivespinBox->setValue(value1);
    else if(Slider->objectName()=="VActiveSlider")
            ui->VActivespinBox->setValue(value1);
    else if(Slider->objectName()=="HTotalSlider")
            ui->HTotalspinBox->setValue(value1);
    else if(Slider->objectName()=="HStartSlider")
            ui->HStartspinBox->setValue(value1);
    else if(Slider->objectName()=="VStartSlider")
            ui->VStartspinBox->setValue(value1);
}

void Widget::spinBox_Valie_changed()
{
    QSpinBox* SpinBox = qobject_cast<QSpinBox*>(sender());
    int value=0;
    double value_2=0;
    stVALUE_INFO stValue_Info;
    stFans_INFO stFrozSpan;
    if(SpinBox->objectName()=="Frame_Grab_spinBox")
    {
        value=ui->Frame_Grab_spinBox->value();
        ui->Frame_Grab_Slider->setValue(value);
        stFrozSpan.id=2;
        stFrozSpan.value=value;
        ubus_interface->Grbi->SetFrozSpan(stFrozSpan);
    }else if(SpinBox->objectName()=="Scan_Input_spinBox")
    {
        value=ui->Scan_Input_spinBox->value();
        ui->Scan_Input_Slider->setValue(value);
        Write_Timming_Cfg_File();
    }else if(SpinBox->objectName()=="Mouse_spinBox")
    {
        value=ui->Mouse_spinBox->value();
        ui->Mouse_Slider->setValue(value);
        Write_Timming_Cfg_File();
    }else if(SpinBox->objectName()=="PHP_spinBox")
    {
        value=ui->PHP_spinBox->value();
        ui->PHP_Slider->setValue(value);
        Write_Timming_Cfg_File();
    }else if(SpinBox->objectName()=="Main_Vedio_spinBox")
    {
        value=ui->Main_Vedio_spinBox->value();
        ui->Main_Vedio_Slider->setValue(value);
        Write_Timming_Cfg_File();
    }else if(SpinBox->objectName()=="Switch_Input_spinBox")
    {
        value=ui->Switch_Input_spinBox->value();
        ui->Switch_Input_Slider->setValue(value);
        Write_Timming_Cfg_File();
    }
    else if(SpinBox->objectName()=="HActivespinBox")
    {
        value=ui->HActivespinBox->value();
        ui->HActiveSlider->setValue(value);
    }
    else if(SpinBox->objectName()=="VActivespinBox")
    {
        value=ui->VActivespinBox->value();
        ui->VActiveSlider->setValue(value);
    }
    else if(SpinBox->objectName()=="HTotalspinBox")
    {
        value=ui->HTotalspinBox->value();
        ui->HTotalSlider->setValue(value);
        if(!read_HTotal)
        {
            stVALUE_INFO stHTotal;
            stHTotal.type=Video_Adjust->SigInId;
            stHTotal.value=value;
            ubus_interface->VidSigIn_SetFrequency(stHTotal);
        }
        read_HTotal=false;
    }
    else if(SpinBox->objectName()=="HStartspinBox")
    {
        value=ui->HStartspinBox->value();
        ui->HStartSlider->setValue(value);
        if(!read_HStart)
        {
            stHVStart stHVStartValue;
            stHVStartValue.sigid=Video_Adjust->SigInId;
            stHVStartValue.HVStartValue=value;
            ubus_interface->VinSigIn_SetHStart(stHVStartValue);
        }
        read_HStart=false;
    }
    else if(SpinBox->objectName()=="VStartspinBox")
    {
        value=ui->VStartspinBox->value();
        ui->VStartSlider->setValue(value);
        if(!read_VStart)
        {
            stHVStart stHVStartValue;
            stHVStartValue.sigid=Video_Adjust->SigInId;
            stHVStartValue.HVStartValue=value;
            ubus_interface->VinSigIn_SetVStart(stHVStartValue);
        }
        read_VStart=false;
    }
}

void Widget::RadioButton_Clicked()
{
    stVALUE_INFO stValue;
    QRadioButton* radiobutton = qobject_cast<QRadioButton*>(sender());
    if(radiobutton->objectName()=="On_Screen_Set_RadioButton_1")
    {
        ui->RefSmallMsg_radioButton->setDisabled(true);
        ui->LiveSmallMsg_radioButton->setDisabled(true);
        Write_Timming_Cfg_File();
    }else if(radiobutton->objectName()=="On_Screen_Set_RadioButton_2")
    {
        ui->RefSmallMsg_radioButton->setEnabled(true);
        ui->LiveSmallMsg_radioButton->setEnabled(true);
        Write_Timming_Cfg_File();
    }else if(radiobutton->objectName()=="RefSmallMsg_radioButton")
    {
        Write_Timming_Cfg_File();
    }else if(radiobutton->objectName()=="LiveSmallMsg_radioButton")
    {
        Write_Timming_Cfg_File();
    }else if(radiobutton->objectName()=="Frame_Grab_RadioButton_1")
    {
        ubus_interface->Grbi->SetGrabIndcatorSel(0);
    }else if(radiobutton->objectName()=="Frame_Grab_RadioButton_2")
    {
        ubus_interface->Grbi->SetGrabIndcatorSel(1);
    }else if(radiobutton->objectName()=="Input_Config_RadioButton_1")
    {
        Write_Timming_Cfg_File();
    }else if(radiobutton->objectName()=="Input_Config_RadioButton_2")
    {
        Write_Timming_Cfg_File();
    }else if(radiobutton->objectName()=="PHP_radioButton_1")
    {
        Write_Timming_Cfg_File();
        ui->PHP_Slider->setEnabled(false);
        ui->PHP_spinBox->setEnabled(false);
    }else if(radiobutton->objectName()=="PHP_radioButton_2")
    {
        Write_Timming_Cfg_File();
        ui->PHP_Slider->setEnabled(true);
        ui->PHP_spinBox->setEnabled(true);
    }else if(radiobutton->objectName()=="One_Net_Interface")
    {
        ubus_interface->client_SetCmdNetSelect(1);
    }else if(radiobutton->objectName()=="Two_Net_Interface")
    {
        ubus_interface->client_SetCmdNetSelect(2);
    }else if(radiobutton->objectName()=="Ref_SDI_1080p_radioButton")
    {
        stOutSig_INFO SDIType;
        SDIType.gid=eVIDSIGOUT_G1;
        SDIType.sigid=0;
        ubus_interface->VidOutPort_SetSDIType(SDIType);
    }else if(radiobutton->objectName()=="Ref_SDI_1080i_radioButton")
    {
        stOutSig_INFO SDIType;
        SDIType.gid=eVIDSIGOUT_G1;
        SDIType.sigid=1;
        ubus_interface->VidOutPort_SetSDIType(SDIType);
    }else if(radiobutton->objectName()=="Live_SDI_1080p_radioButton")
    {
        stOutSig_INFO SDIType;
        SDIType.gid=eVIDSIGOUT_G2;
        SDIType.sigid=0;
        ubus_interface->VidOutPort_SetSDIType(SDIType);
    }else if(radiobutton->objectName()=="Live_SDI_1080i_radioButton")
    {
        stOutSig_INFO SDIType;
        SDIType.gid=eVIDSIGOUT_G2;
        SDIType.sigid=1;
        ubus_interface->VidOutPort_SetSDIType(SDIType);
    }else if(radiobutton->objectName()=="SXGA_Ref_RadioButton")
    {
        stValue.type=eVIDSIGOUT_G1;
        stValue.value=eVIDSIGOUT_SIGFMT_SXGA;
        ubus_interface->VidSigOut_SetFormat(stValue);
    }else if(radiobutton->objectName()=="WUXGA_Ref_RadioButton")
    {
        stValue.type=eVIDSIGOUT_G1;
        stValue.value=eVIDSIGOUT_SIGFMT_WUXGA;
        ubus_interface->VidSigOut_SetFormat(stValue);
    }else if(radiobutton->objectName()=="Input_RGB_live_radioButton")
    {
//        stValue.type=ui->Input_live_ComboBox->currentIndex()+16;
//        stValue.value=0;
//        ubus_interface->VidSigIn_SetAnalogType(stValue);
    }else if(radiobutton->objectName()=="Input_YPrPb_live_radioButton")
    {
//        stValue.type=ui->Input_live_ComboBox->currentIndex()+16;
//        stValue.value=1;
//        ubus_interface->VidSigIn_SetAnalogType(stValue);
    }else if(radiobutton->objectName()=="Input_Y_live_radioButton")
    {
//        stValue.type=ui->Input_live_ComboBox->currentIndex()+16;
//        stValue.value=2;
//        ubus_interface->VidSigIn_SetAnalogType(stValue);
    }else if(radiobutton->objectName()=="SXGA_live_RadioButton")
    {
        stValue.type=eVIDSIGOUT_G2;
        stValue.value=eVIDSIGOUT_SIGFMT_SXGA;
        ubus_interface->VidSigOut_SetFormat(stValue);
    }else if(radiobutton->objectName()=="WUXGA_live_RadioButton")
    {
        stValue.type=eVIDSIGOUT_G2;
        stValue.value=eVIDSIGOUT_SIGFMT_WUXGA;
        ubus_interface->VidSigOut_SetFormat(stValue);
    }else if(radiobutton->objectName()=="BestImage_radioButton")
    {
        ubus_interface->Router->SetInterlaceVideo(1);
    }
    else if(radiobutton->objectName()=="Smallest_radioButton")
    {
        ubus_interface->Router->SetInterlaceVideo(0);
     }
}

void Widget::pushButton_Clicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
     if(button->objectName()=="Cancel_Changes")
     {
        ui->Net1_IP_Edit->setText(Network_Data.strIpAddr[0]);
        ui->Net1_Mask_Edit->setText(Network_Data.strMask[0]);
        ui->Net2_IP_Edit->setText(Network_Data.strIpAddr[1]);
        ui->Net2_Mask_Edit->setText(Network_Data.strMask[1]);
        QString str=QString("%1").arg(Network_Data.server_port);
        ui->Port_Number_2->setText(str);

        ui->Storage_IP_Edit->setText(Network_Data.ip[0]);
        ui->Storage_Port_Edit->setText(QString::number(Network_Data.port[0]));
        ui->Storage_Remote_AE_Edit->setText(Network_Data.RAETitle[0]);
        ui->Storage_Local_AE_Edit->setText(Network_Data.LAETitle[0]);
        ui->RIS_IP_Edit->setText(Network_Data.ip[1]);
        ui->RIS_Port_Edit->setText(QString::number(Network_Data.port[1]));
        ui->RIS_Remote_AE_Edit->setText(Network_Data.RAETitle[1]);
        ui->RIS_Local_AE_Edit->setText(Network_Data.LAETitle[1]);

        ui->Cancel_Changes->setEnabled(false);
        ui->Submit_New_Set->setEnabled(false);
     }else if(button->objectName()=="Submit_New_Set")
     {
        bool ret=false,ret2=false,ret3=false;
        QString str;
        //QRegExp rx("((2{2}[0-3]|2[01][0-9]|1[0-9]{2}|0?[1-9][0-9]|0{0,2}[1-9])\\.)((25[0-5]|2[0-4][0-9]|[01]?[0-9]{0,2})\\.){2}(25[0-5]|2[0-4][0-9]|[0-1]?[0-9]?[0-9])");
        QRegExp rx("^((25[0-5]|2[0-4]\\d|[1]{1}\\d{1}\\d{1}|[1-9]{1}\\d{1}|\\d{1})($|(?!\\.$)\\.)){4}$");
        QRegExpValidator v(rx,0);
        QRegExp rx1("^((128|192)|2(24|4[08]|5[245]))(\.(0|(128|192)|2((24)|(4[08])|(5[245])))){3}$");
        //QRegExp rx1("((128\\.|192\\.|224\\.|240\\.|248\\.|252\\.|254\\.)(0\\.){2}(0)) | ((255\\.)(((128\\.|192\\.|224\\.|240\\.|248\\.|252\\.|254\\.)(0\\.0)) | ( (255\\.)((128\\.|192\\.|224\\.|240\\.|248\\.|252\\.|254\\.)(0)) | ((255\\.)((128|192|224|240|248|252|254|255|0))) ) ))");
        QRegExpValidator v1(rx1,0);
        QRegExp rx2("^([0-9]|[1-9]\\d|[1-9]\\d{2}|[1-9]\\d{3}|[1-5]\\d{4}|6[0-4]\\d{3}|65[0-4]\\d{2}|655[0-2]\\d|6553[0-5])$");
        QRegExpValidator v2(rx2,0);
        int pos=0;
        QValidator::State res;

        stDEVCOMM_NET setNet,setNet_2;
        stDEVCOMM_SVR DicomSvrInfo,DicomSvrInfo_2;
         if((QString::compare(ui->Net1_IP_Edit->text(),Network_Data.strIpAddr[0])!=0) ||
             (QString::compare(ui->Net1_Mask_Edit->text(),Network_Data.strMask[0])!=0) ||
              (QString::compare(ui->Net2_IP_Edit->text(),Network_Data.strIpAddr[1])!=0) ||
              (QString::compare(ui->Net2_Mask_Edit->text(),Network_Data.strMask[1])!=0) ||
               (ui->Port_Number_2->text().toInt() != Network_Data.server_port))
        {

            ret=true;
            str=ui->Net1_IP_Edit->text();
            qDebug()<<str;
            res=v.validate(str,pos);
            if(QValidator::Acceptable != res)
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("IP Address(1Gb Link) no valid")), QMessageBox::Ok);
                return;
            }

            res=QValidator::Invalid;
            str=ui->Net1_Mask_Edit->text();
            res=v1.validate(str,pos);
            if(QValidator::Acceptable != res)
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("Netmask(1Gb Link) no valid")), QMessageBox::Ok);
                return;
            }

            res=QValidator::Invalid;
            str=ui->Net2_IP_Edit->text();
            res=v.validate(str,pos);
            if(QValidator::Acceptable != res)
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("IP Address(1Mb Link) no valid")), QMessageBox::Ok);
                return;
            }

            res=QValidator::Invalid;
            str=ui->Net2_Mask_Edit->text();
            res=v1.validate(str,pos);
            if(QValidator::Acceptable != res)
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("Netmask(1Mb Link) no valid")), QMessageBox::Ok);
                return;
            }

            res=QValidator::Invalid;
            str=ui->Port_Number_2->text();
            res=v2.validate(str,pos);
            if(QValidator::Acceptable != res)
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("Enternet interfaces prot number no valid")), QMessageBox::Ok);
                return;
            }
        }

        if((QString::compare(ui->Storage_IP_Edit->text(),Network_Data.ip[0])!=0) || (ui->Storage_Port_Edit->text().toInt()!=Network_Data.port[0])
                || (QString::compare(ui->Storage_Remote_AE_Edit->text(),Network_Data.RAETitle[0])!=0) ||
                (QString::compare(ui->Storage_Local_AE_Edit->text(),Network_Data.LAETitle[0])!=0))
        {
            ret2=true;
            str=ui->Storage_IP_Edit->text();
            res=QValidator::Invalid;
            res=v.validate(str,pos);
            if(QValidator::Acceptable != res)
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("DICOM storage server ip address no valid")), QMessageBox::Ok);
                return;
            }

            res=QValidator::Invalid;
            str=ui->Storage_Port_Edit->text();
            res=v2.validate(str,pos);
            if(QValidator::Acceptable != res)
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("DICOM storage server prot number no valid")), QMessageBox::Ok);
                return;
            }

            if(ui->Storage_Remote_AE_Edit->text().isEmpty())
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("DICOM storage server remote ae title cannot be empty")), QMessageBox::Ok);
                return;
            }

            if(ui->Storage_Local_AE_Edit->text().isEmpty())
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("DICOM storage server local ae title cannot be empty")), QMessageBox::Ok);
                return;
            }
        }

        if((QString::compare(ui->RIS_IP_Edit->text(),Network_Data.ip[1])!=0) || (ui->RIS_Port_Edit->text().toInt()!=Network_Data.port[1])
                || (QString::compare(ui->RIS_Remote_AE_Edit->text(),Network_Data.RAETitle[1])!=0) ||
                (QString::compare(ui->RIS_Local_AE_Edit->text(),Network_Data.LAETitle[1])!=0))
        {
            ret3=true;
            str=ui->RIS_IP_Edit->text();
            res=QValidator::Invalid;
            res=v.validate(str,pos);
            if(QValidator::Acceptable != res)
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("DICOM RIS server ip address no valid")), QMessageBox::Ok);
                return;
            }

            res=QValidator::Invalid;
            str=ui->RIS_Port_Edit->text();
            res=v2.validate(str,pos);
            if(QValidator::Acceptable != res)
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("DICOM RIS server DICOM storage server prot number no valid")), QMessageBox::Ok);
                return;
            }

            if(ui->RIS_Remote_AE_Edit->text().isEmpty())
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("DICOM RIS server remote ae title cannot be empty")), QMessageBox::Ok);
                return;
            }

            if(ui->RIS_Local_AE_Edit->text().isEmpty())
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("DICOM RIS server local ae title cannot be empty")), QMessageBox::Ok);
                return;
            }
        }

        if(ret)
        {
            setNet.uiNetIndex=1;
            setNet.bIsDHCP=Network_Data.bIsDHCP[0];
            setNet.strIpAddr=ui->Net1_IP_Edit->text();
            setNet.strMask=ui->Net1_Mask_Edit->text();
            setNet.strGate=Network_Data.strGate[0];
            setNet.strNDS1=Network_Data.strNDS1[0];
            setNet.strNDS2=Network_Data.strNDS2[0];


            setNet_2.uiNetIndex=2;
            setNet_2.bIsDHCP=Network_Data.bIsDHCP[1];
            setNet_2.strIpAddr=ui->Net2_IP_Edit->text();
            setNet_2.strMask=ui->Net2_Mask_Edit->text();
            setNet_2.strGate=Network_Data.strGate[1];
            setNet_2.strNDS1=Network_Data.strNDS1[1];
            setNet_2.strNDS2=Network_Data.strNDS2[1];
            ubus_interface->client_setNetIp(setNet);
            ubus_interface->client_setNetIp(setNet_2);

            ubus_interface->client_SetCmdNetPort(ui->Port_Number_2->text().toInt());
        }

        if(ret2)
        {
            DicomSvrInfo.ip=ui->Storage_IP_Edit->text();
            DicomSvrInfo.port=ui->Storage_Port_Edit->text().toInt();
            DicomSvrInfo.RAETitle=ui->Storage_Remote_AE_Edit->text();
            DicomSvrInfo.LAETitle=ui->Storage_Local_AE_Edit->text();
            ubus_interface->client_setDicommSvrInfo(1,DicomSvrInfo);
        }

        if(ret3)
        {
            DicomSvrInfo_2.ip=ui->RIS_IP_Edit->text();
            DicomSvrInfo_2.port=ui->RIS_Port_Edit->text().toInt();
            DicomSvrInfo_2.RAETitle=ui->RIS_Remote_AE_Edit->text();
            DicomSvrInfo_2.LAETitle=ui->RIS_Local_AE_Edit->text();
            ubus_interface->client_setDicommSvrInfo(2,DicomSvrInfo_2);
        }

            ui->Cancel_Changes->setEnabled(false);
            ui->Submit_New_Set->setEnabled(false);

     }else if(button->objectName()=="Switch_Output_Button")
     {
         ubus_interface->Router->SetSwtOutput();
     }else if(button->objectName()=="Switch_Output_Button_2")
     {
         ubus_interface->Router->SetSwtOutput();
     }else if(button->objectName()=="Grab_Image_pushButton")
     {
         ui->Grab_Image_pushButton->setEnabled(false);
         ui->Grab_Image_pushButton_2->setEnabled(false);
         stSingleGrabStart_In stSingleGrabStart;
         stSingleGrabStart.id=GRABIMG_SRCID_OSD;
         stSingleGrabStart.socket=0;
         stSingleGrabStart.cmdid=0;
         ubus_interface->Grbi->SingleGrabStart(stSingleGrabStart);
     }else if(button->objectName()=="Grab_Image_pushButton_2")
     {
         ui->Grab_Image_pushButton->setEnabled(false);
         ui->Grab_Image_pushButton_2->setEnabled(false);
         stSingleGrabStart_In stSingleGrabStart;
         stSingleGrabStart.id=GRABIMG_SRCID_OSD;
         stSingleGrabStart.socket=0;
         stSingleGrabStart.cmdid=0;
         ubus_interface->Grbi->SingleGrabStart(stSingleGrabStart);
     }else if(button->objectName()=="Reboot_Button")
     {
         int choose;
         choose= QMessageBox::question(this, tr("Reboot"), QString(tr("Confirm Reboot?")), QMessageBox::Yes | QMessageBox::No);
         if (choose== QMessageBox::No)
         {
             return;
         } else if (choose== QMessageBox::Yes)
         {
             ubus_interface->Reset(eMVDEV_SYSTEM_REBOOT);
         }

     }else if(button->objectName()=="Reset_Button")
     {
         uchar submod_id=(uchar)ui->Reset_comboBox->currentIndex();
         ubus_interface->Reset(submod_id);
     }else if(button->objectName()=="Scan_Ref_pushButton")
     {
        stScan_INFO Sigid_time;
        Sigid_time.sigid=0;
        Sigid_time.time=ui->Scan_Input_Slider->value();
        ubus_interface->VidSigIn_Scan(Sigid_time);
        QFont ft;
        ft.setPointSize(11);
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::black);
        sigvinscan->label_list[0]->setFont(ft);
        sigvinscan->label_list[0]->setPalette(pa);
        sigvinscan->label_list[0]->setText("DVI-D 1");
     }else if(button->objectName()=="Scan_live_pushButton")
     {
         stScan_INFO Sigid_time;
         Sigid_time.sigid=0;
         Sigid_time.time=ui->Scan_Input_Slider->value();
         ubus_interface->VidSigIn_Scan(Sigid_time);
         QFont ft;
         ft.setPointSize(11);
         QPalette pa;
         pa.setColor(QPalette::WindowText,Qt::black);
         sigvinscan->label_list[0]->setFont(ft);
         sigvinscan->label_list[0]->setPalette(pa);
         sigvinscan->label_list[0]->setText("DVI-D 1");
     }else if(button->objectName()=="SwtNextInput_Ref_Button")
     {
        stSwtNextInput_INFO pstSwtNextInput;
        SwitchNextSigIn RoutSocket;
        RoutSocket.id=eVIDSIGOUT_G1;
        RoutSocket.socket=0;
        RoutSocket.cmdid=0;
        ubus_interface->VidRout_SwtNextInput(RoutSocket,&pstSwtNextInput);
     }else if(button->objectName()=="SwtNextInput_live_Button")
     {
         stSwtNextInput_INFO pstSwtNextInput;
         SwitchNextSigIn RoutSocket;
         RoutSocket.id=eVIDSIGOUT_G2;
         RoutSocket.socket=0;
         RoutSocket.cmdid=0;
         ubus_interface->VidRout_SwtNextInput(RoutSocket,&pstSwtNextInput);
     }else if(button->objectName()=="Calibration_Time_Button")
     {
         stTIME_INFO pstTime;
         QDate date=ui->dateTimeEdit->date();
         QTime time=ui->dateTimeEdit->time();
         pstTime.uiYear=date.year();
         pstTime.uiMon=date.month();
         pstTime.uiMday=date.day();
         pstTime.uiHour=time.hour();
         pstTime.uiMin=time.minute();
         pstTime.uiSec=time.second();
         ubus_interface->client_setCalibTime(pstTime);
     }else if(button->objectName()=="Video_Adjust_Ref_Button")
     {
         Video_Adjust->SigInId=ui->Input_Ref_ComboBox->currentIndex()+1;
         ubus_interface->VidSigIn_GetStatus(Video_Adjust->SigInId,0);
         switch (Video_Adjust->SigInId) {
         case eVIDSIGIN_S_VIDEO1:
         case eVIDSIGIN_S_VIDEO2:
         case eVIDSIGIN_SDI1:
         case eVIDSIGIN_SDI2:
         case eVIDSIGIN_CVBS:
         case eVIDSIGIN_DVI_A1:
         case eVIDSIGIN_DVI_A2:
             Video_Adjust->Scaling_FourToThree_RadioButton->setEnabled(true);
             break;
         default:
             Video_Adjust->Scaling_FourToThree_RadioButton->setEnabled(false);
             break;
         }

         Video_Adjust->setHidden(false);
     }
     else if(button->objectName()=="Video_Adjust_live_Button")
     {
         Video_Adjust->SigInId=ui->Input_live_ComboBox->currentIndex()+16;
         ubus_interface->VidSigIn_GetStatus(Video_Adjust->SigInId,0);
         Video_Adjust->Scaling_FourToThree_RadioButton->setEnabled(false);
         Video_Adjust->setHidden(false);
     }else if(button->objectName()=="AskWorkList_pushButton")
     {
         ubus_interface->Grbi->AskWorkList(GRABIMG_SRCID_OSD);
     }
     else if(button->objectName()=="SetButton")
     {
         ui->NameEdit->setText(QString("%1_%2").arg(ui->HActivespinBox->value()).arg(ui->VActivespinBox->value()));
         setVideoSetting(DebugOverlayData);
     }
     else if(button->objectName()=="SaveButton")
     {   
         if(ui->NameEdit->text().isEmpty())
            QMessageBox::question(this, tr("Warning"), QString(tr("Name cannot be blank, please fill in completely!")));
         else
            setVideoSetting(SaveOverlayData);
     }
     else if(button->objectName()=="CleanButton")
     {
         int choose;
         choose= QMessageBox::question(this, tr("Clean Model"), QString(tr("Please confirm whether to empty!")), QMessageBox::Yes | QMessageBox::No);
         if (choose== QMessageBox::No)
         {
             return;
         } else if (choose== QMessageBox::Yes)
         {
             ubus_interface->VinDispClearAnalogModeIndexTable();
         }
         QThread::msleep(1000);
         QMessageBox::question(this, tr("Information"), tr("Clean Success!"), QMessageBox::Ok);
     }else if(button->objectName()=="AutoAdjustButton")
     {
         stAuto_INFO stValue_Info;
         stValue_Info.uiSigInId=Video_Adjust->SigInId;
         stValue_Info.DISP_PARAM_INDEX=DISP_AUTO_ADJUSTMENT;
         stValue_Info.uiValue=1;
         QPalette pa1;
         pa1.setColor(QPalette::WindowText,Qt::red);
         ui->label_29->setPalette(pa1);
         ui->label_29->setText("Auto Setup is active.Please wait");
         ui->AutoAdjustButton->setEnabled(false);
         ui->SaveButton->setEnabled(false);
         ui->CleanButton->setEnabled(false);
         ui->SetButton->setEnabled(false);
         ui->HTotalSlider->setEnabled(false);
         ui->HTotalspinBox->setEnabled(false);
         ui->HStartSlider->setEnabled(false);
         ui->HStartspinBox->setEnabled(false);
         ui->VStartSlider->setEnabled(false);
         ui->VStartspinBox->setEnabled(false);
         ubus_interface->VinDispSetAnalogModeDebug(1);
         QtConcurrent::run(this,&Widget::SetAutoSetup,stValue_Info);
     }

}

void Widget::CheckBox_Clicked()
{
    QCheckBox* checkBox = qobject_cast<QCheckBox*>(sender());
    qDebug()<<checkBox->objectName();
    if(checkBox->objectName()=="Output_Ref_checkBox")
    {
       if(ui->Output_Ref_checkBox->isChecked())
          ui->Output_Ref_checkBox->setChecked(false);
       else
          ui->Output_Ref_checkBox->setChecked(true);
    }else if (checkBox->objectName()=="Output_Ref_checkBox_2")
    {
       if(ui->Output_Ref_checkBox_2->isChecked())
           ui->Output_Ref_checkBox_2->setChecked(false);
       else
           ui->Output_Ref_checkBox_2->setChecked(true);
    }else if (checkBox->objectName()=="Output_Ref_checkBox_3")
    {
        if(ui->Output_Ref_checkBox_3->isChecked())
            ui->Output_Ref_checkBox_3->setChecked(false);
        else
            ui->Output_Ref_checkBox_3->setChecked(true);
    }else if (checkBox->objectName()=="Output_Ref_checkBox_4")
    {
        if(ui->Output_Ref_checkBox_4->isChecked())
            ui->Output_Ref_checkBox_4->setChecked(false);
        else
            ui->Output_Ref_checkBox_4->setChecked(true);
    }else if (checkBox->objectName()=="Output_live_checkBox")
    {
        if(ui->Output_live_checkBox->isChecked())
            ui->Output_live_checkBox->setChecked(false);
        else
            ui->Output_live_checkBox->setChecked(true);
    }else if (checkBox->objectName()=="Output_live_checkBox_2")
    {
        if(ui->Output_live_checkBox_2->isChecked())
            ui->Output_live_checkBox_2->setChecked(false);
        else
            ui->Output_live_checkBox_2->setChecked(true);
    }else if (checkBox->objectName()=="Output_live_checkBox_3")
    {
        if(ui->Output_live_checkBox_3->isChecked())
            ui->Output_live_checkBox_3->setChecked(false);
        else
            ui->Output_live_checkBox_3->setChecked(true);
    }else if (checkBox->objectName()=="Output_live_checkBox_4")
    {
        if(ui->Output_live_checkBox_4->isChecked())
            ui->Output_live_checkBox_4->setChecked(false);
        else
            ui->Output_live_checkBox_4->setChecked(true);
    }else if (checkBox->objectName()=="SmartLock_Ref_CheckBox")
    {
            stVALUE_INFO stValue_Info;
            stValue_Info.type=eVIDSIGOUT_G1;
            if(ui->SmartLock_Ref_CheckBox->isChecked())
                stValue_Info.value=1;
            else
                stValue_Info.value=0;
            ubus_interface->VidSigOut_SetSmartlock(stValue_Info);
    }else if (checkBox->objectName()=="SmartLock_live_CheckBox")
    {
            stVALUE_INFO stValue_Info;
            stValue_Info.type=eVIDSIGOUT_G2;
            if(ui->SmartLock_live_CheckBox->isChecked())
                stValue_Info.value=1;
            else
                stValue_Info.value=0;
            ubus_interface->VidSigOut_SetSmartlock(stValue_Info);
    }

}

void Widget::LineEditTextChanged(QString text)
{
    QLineEdit* LineEdit = qobject_cast<QLineEdit*>(sender());

    if((QString::compare(ui->Net1_IP_Edit->text(),Network_Data.strIpAddr[0])==0) &
       (QString::compare(ui->Net1_Mask_Edit->text(),Network_Data.strMask[0])==0) &
       (QString::compare(ui->Net2_IP_Edit->text(),Network_Data.strIpAddr[1])==0) &
       (QString::compare(ui->Net2_Mask_Edit->text(),Network_Data.strMask[1])==0) &
       (ui->Port_Number_2->text().toInt() == Network_Data.server_port) &
       (QString::compare(ui->Storage_IP_Edit->text(),Network_Data.ip[0])==0) &
       (ui->Storage_Port_Edit->text().toInt()==Network_Data.port[0]) &
       (QString::compare(ui->Storage_Remote_AE_Edit->text(),Network_Data.RAETitle[0])==0) &
       (QString::compare(ui->Storage_Local_AE_Edit->text(),Network_Data.LAETitle[0])==0) &
       (QString::compare(ui->RIS_IP_Edit->text(),Network_Data.ip[1])==0) &
       (ui->RIS_Port_Edit->text().toInt()==Network_Data.port[1]) &
       (QString::compare(ui->RIS_Remote_AE_Edit->text(),Network_Data.RAETitle[1])==0) &
       (QString::compare(ui->RIS_Local_AE_Edit->text(),Network_Data.LAETitle[1])==0))
    {
        ui->Cancel_Changes->setEnabled(false);
        ui->Submit_New_Set->setEnabled(false);
        return;
    }

    ui->Cancel_Changes->setEnabled(true);
    ui->Submit_New_Set->setEnabled(true);
}

void Widget::GetValue(int type,stVALUE_INFO stValue)
{
    QString str;
    switch (type)
    {
        case WORK_TIME:
            ui->Work_Time_label->setText(QString("Work Time: %1h").arg(stValue.value));
            break;
        case LIGHTNESS:
            Video_Adjust->SetBrightnessSliderValue(stValue);
            break;
        case CONTRAST:
            Video_Adjust->SetContrastSliderValue(stValue);
            break;
        case COLOR:
            Video_Adjust->SetColorSliderValue(stValue);
            break;
        case HUE:
            Video_Adjust->SetHueSliderValue(stValue);
            break;
        case SHARPNESS:
            Video_Adjust->SetSharpnessSliderValue(stValue);
            break;
        case NOISEREDUCTION:
            Video_Adjust->SetNoiseSliderValue(stValue);
            break;
        case PHASE:
            Video_Adjust->SetPhaseSliderValue(stValue);
            break;
        case CLAMPWIDTH:
            Video_Adjust->SetClampwidthSliderValue(stValue);
            break;
        case INPUT_CONFIGURATION:
            break;
        case SIGVIN_FVFREQ:
            Video_Adjust->SetVFrequencyLabelValue(stValue);
            break;
        case SIGVIN_FHFREQ:
            Video_Adjust->SetHFrequencyLabelValue(stValue);
            break;
        case DITHER:
                if(stValue.value==0)
                    Video_Adjust->Dither_CheckBox->setChecked(false);
                else
                    Video_Adjust->Dither_CheckBox->setChecked(true);
            break;
        case SMARTLOCK:
               if(stValue.type==eVIDSIGOUT_G1)
               {                 
                   if(stValue.value==0)
                       ui->SmartLock_Ref_CheckBox->setChecked(false);
                   else
                       ui->SmartLock_Ref_CheckBox->setChecked(true);
               }else {
                   if(stValue.value==0)
                       ui->SmartLock_live_CheckBox->setChecked(false);
                   else
                       ui->SmartLock_live_CheckBox->setChecked(true);
               }
            break;
    case SIGFORMAT:
        if(stValue.type==eVIDSIGOUT_G1)
        {
            if(stValue.value==0)
                ui->SXGA_Ref_RadioButton->setChecked(true);
            else
                ui->WUXGA_Ref_RadioButton->setChecked(true);
        }else {
            if(stValue.value==0)
                ui->SXGA_live_RadioButton->setChecked(true);
            else
                ui->WUXGA_live_RadioButton->setChecked(true);
        }
        break;
        case GAMMA:
            Video_Adjust->SetGammaControlValue(stValue);
            break;
         case BANDWIDTH:
            Video_Adjust->SetBandwidthControlValue(stValue);
            break;
         case VidFmtPN:
            Video_Adjust->SetFmtPNControlValue(stValue);
            break;
    }
}

void Widget::SetValue(int type, stVALUE_INFO stValue)
{
    stHVStart stHVStartValue;
    stHVStartValue.sigid=stValue.type;
    stHVStartValue.HVStartValue=stValue.value;
    switch (type)
    {
        case LIGHTNESS:
            ubus_interface->VidSigIn_SetLightness(stValue);
            break;
        case CONTRAST:
            ubus_interface->VidSigIn_SetContrast(stValue);
            break;
        case COLOR:
            ubus_interface->VidSigIn_SetColor(stValue);
            break;
        case HUE:
            ubus_interface->VidSigIn_SetHue(stValue);
            break;
        case SHARPNESS:
            ubus_interface->VidSigIn_SetSharpness(stValue);
            break;
        case NOISEREDUCTION:
            ubus_interface->VidSigIn_SetNoiseReduction(stValue);
            break;
        case PHASE:
            ubus_interface->VidSigIn_SetPhase(stValue);
            break;
        case FREQUENCY:
            ubus_interface->VidSigIn_SetFrequency(stValue);
            break;
        case CLAMPWIDTH:
            ubus_interface->VidSigIn_SetClampwidth(stValue);
            break;
        case DITHER:
                ubus_interface->VidSigIn_SetDither(stValue);
            break;
        case GAMMA:
                ubus_interface->VidSigIn_SetGamma(stValue);
            break;
         case BANDWIDTH:
              ubus_interface->VidSigIn_SetBandWidth(stValue);
              break;
         case H_START:
            ubus_interface->VinSigIn_SetHStart(stHVStartValue);
             break;
        case V_START:
            ubus_interface->VinSigIn_SetVStart(stHVStartValue);
        break;
    }
}

void Widget::GetCalibTime(bool ok,stTIME_INFO stTime)
{
    QDate date;
    date.setDate(stTime.uiYear,stTime.uiMon,stTime.uiMday);
    QTime time;
    time.setHMS(stTime.uiHour,stTime.uiMin,stTime.uiSec);
    datetime.setDate(date);
    datetime.setTime(time);

    ui->dateTimeEdit->setDateTime(datetime);
//    if(ok)
//       connect(timer, SIGNAL(timeout()), this, SLOT(DateTime_Display()));

//    if(timer->isActive())
//        timer->stop();

//    timer->start(1000);
}

void Widget::SetAutoSetup(stAuto_INFO stValue_Info)
{
    if(stValue_Info.DISP_PARAM_INDEX==DISP_AUTO_ADJUSTMENT)
    {
        stAuto_INFO stAutoAdjustment;
        stAutoAdjustment=stValue_Info;
        stAutoAdjustment.DISP_PARAM_INDEX-=1;
        ubus_interface->VidSigIn_SetAutoSteup(stAutoAdjustment);
    }
    else
        ubus_interface->VidSigIn_SetAutoSteup(stValue_Info);
    stHVStart stHVStartValue;
    stVStart stVStartValue;
    gtFrequency_INFO stFrequency;
    if(stValue_Info.DISP_PARAM_INDEX==DISP_PARAM_RESOLUT)
    {
        QThread::msleep( 20000 );
        ubus_interface->VidSigIn_GetPhase(Video_Adjust->SigInId);

        ubus_interface->VidSigIn_GetFrequency(Video_Adjust->SigInId,&stFrequency);

//        ubus_interface->VinSigIn_GetHStart(Video_Adjust->SigInId,&stVStartValue);
//        stHVStartValue.sigid=stVStartValue.sigid;
//        stHVStartValue.HVStartValue=stVStartValue.nVStartValue;
//        Video_Adjust->SetHStartSliderValue(stHVStartValue,stVStartValue.nMinValue,stVStartValue.nMaxValue);


//        ubus_interface->VinSigIn_GetVStart(Video_Adjust->SigInId,&stVStartValue);
//        stHVStartValue.sigid=stVStartValue.sigid;
//        stHVStartValue.HVStartValue=stVStartValue.nVStartValue;
//        Video_Adjust->SetVStartSliderValue(stHVStartValue,stVStartValue.nMinValue,stVStartValue.nMaxValue)
    }

    if(stValue_Info.DISP_PARAM_INDEX==DISP_PARAM_PHASE)
    {
        QThread::msleep( 20000 );
        ubus_interface->VidSigIn_GetPhase(Video_Adjust->SigInId);
    }

    if(stValue_Info.DISP_PARAM_INDEX==DISP_PARAM_GEOMETY)
    {
        QThread::msleep( 20000 );
        ubus_interface->VidSigIn_GetPhase(Video_Adjust->SigInId);
        ubus_interface->VidSigIn_GetFrequency(Video_Adjust->SigInId,&stFrequency);
//        ui->HTotalSlider->setMinimum(stFrequency.minvlaue);
//        ui->HTotalSlider->setMaximum(stFrequency.maxvlaue);
//        ui->HTotalspinBox->setMinimum(stFrequency.minvlaue);
//        ui->HTotalspinBox->setMaximum(stFrequency.maxvlaue);
//        ui->HTotalSlider->setValue(stFrequency.currtvalue);

//        ubus_interface->VinSigIn_GetHStart(Video_Adjust->SigInId,&stVStartValue);
//        ui->HStartSlider->setMinimum(stVStartValue.nMinValue);
//        ui->HStartSlider->setMaximum(stVStartValue.nMaxValue);
//        ui->HStartspinBox->setMinimum(stVStartValue.nMinValue);
//        ui->HStartspinBox->setMaximum(stVStartValue.nMaxValue);
//        ui->HStartSlider->setValue(stVStartValue.nVStartValue);
//        stHVStartValue.sigid=stVStartValue.sigid;
//        stHVStartValue.HVStartValue=stVStartValue.nVStartValue;
//        Video_Adjust->SetHStartSliderValue(stHVStartValue,stVStartValue.nMinValue,stVStartValue.nMaxValue);
//        ubus_interface->VinSigIn_GetVStart(Video_Adjust->SigInId,&stVStartValue);
//        ui->VStartSlider->setMinimum(stVStartValue.nMinValue);
//        ui->VStartSlider->setMaximum(stVStartValue.nMaxValue);
//        ui->VStartspinBox->setMinimum(stVStartValue.nMinValue);
//        ui->VStartspinBox->setMaximum(stVStartValue.nMaxValue);
//        ui->VStartSlider->setValue(stVStartValue.nVStartValue);
//        stHVStartValue.sigid=stVStartValue.sigid;
//        stHVStartValue.HVStartValue=stVStartValue.nVStartValue;
//        Video_Adjust->SetVStartSliderValue(stHVStartValue,stVStartValue.nMinValue,stVStartValue.nMaxValue);


    }

    if(stValue_Info.DISP_PARAM_INDEX==DISP_AUTO_ADJUSTMENT)
    {
        QThread::msleep( 5000 );
        int n=60;
        int nRet=0,nStatus;

        while(n)
        {
            nStatus=0;
            ubus_interface->VidSigIn_VinDispGetAutoSet(&nStatus);

            if(nStatus==0)
            {
               QThread::msleep( 1000 );
               n--;
               continue;
            }else if(nStatus==1)
            {
               nRet=1;
               break;
            }else {
                nRet=2;
                break;
            }
        }

        getVideoSettingParameters();

        if(nRet==1)
            emit emitDispalyTipsInfo("Auto Success!");

        if(nRet==2)
            emit emitDispalyTipsInfo("Auto Failed!");
        ui->label_29->setText(" ");

        ui->AutoAdjustButton->setEnabled(true);
        ui->SaveButton->setEnabled(true);
        ui->CleanButton->setEnabled(true);
        ui->SetButton->setEnabled(true);
        ui->HTotalSlider->setEnabled(true);
        ui->HTotalspinBox->setEnabled(true);
        ui->HStartSlider->setEnabled(true);
        ui->HStartspinBox->setEnabled(true);
        ui->VStartSlider->setEnabled(true);
        ui->VStartspinBox->setEnabled(true);
    }

    Video_Adjust->labelSetAuto->setText(" ");
    Video_Adjust->EnableControlCursor();
}

void Widget::SetPresetCfg(int type)
{
    switch (type) {
    case 0:
        ubus_interface->disp->VinDispRestoreCurrentPreset((uchar)Video_Adjust->SigInId);
        break;
    case 1:
        ubus_interface->disp->VinDispSelectNextPreset((uchar)Video_Adjust->SigInId);
        break;
    case 2:
        ubus_interface->disp->VinDispSaveCurrentPreset((uchar)Video_Adjust->SigInId);
        break;
    case 3:
        ubus_interface->disp->VinDispClearAllPreset((uchar)Video_Adjust->SigInId);
        break;
    }
    QThread::msleep( 2000 );
    GetPresetParams(true);
}

void Widget::GetDevcomm_Srv(int Svr_id,stDEVCOMM_SVR stDevcomm_srv)
{
    if(Svr_id==1)
    {
        Network_Data.ip[0]=stDevcomm_srv.ip;
        Network_Data.port[0]=stDevcomm_srv.port;
        Network_Data.RAETitle[0]=stDevcomm_srv.RAETitle;
        Network_Data.LAETitle[0]=stDevcomm_srv.LAETitle;
        ui->Storage_IP_Edit->setText(stDevcomm_srv.ip);
        ui->Storage_Port_Edit->setText(QString("%1").arg(stDevcomm_srv.port));
        ui->Storage_Remote_AE_Edit->setText(stDevcomm_srv.RAETitle);
        ui->Storage_Local_AE_Edit->setText(stDevcomm_srv.LAETitle);
    }else
    {
        Network_Data.ip[1]=stDevcomm_srv.ip;
        Network_Data.port[1]=stDevcomm_srv.port;
        Network_Data.RAETitle[1]=stDevcomm_srv.RAETitle;
        Network_Data.LAETitle[1]=stDevcomm_srv.LAETitle;
        ui->RIS_IP_Edit->setText(stDevcomm_srv.ip);
        ui->RIS_Port_Edit->setText(QString("%1").arg(stDevcomm_srv.port));
        ui->RIS_Remote_AE_Edit->setText(stDevcomm_srv.RAETitle);
        ui->RIS_Local_AE_Edit->setText(stDevcomm_srv.LAETitle);
    }
}

void Widget::GetDevcomm_Net_Mac(stDEVCOMM_MAC stDevcomm_Net_Mac)
{
    QString str;
    if(stDevcomm_Net_Mac.uiNetIndex==1)
    {
        str=QString("MAC 100Mb:");
        str.append(stDevcomm_Net_Mac.strMac);
        ui->label_2->setText(str);
    }
    else
    {
        str=QString("MAC 1Gb:");
        str.append(stDevcomm_Net_Mac.strMac);
        ui->label_3->setText(str);
    }
}

void Widget::GetDevcomm_Net_Select_Port(int type, int value)
{
    if(type==1)
    {
        QString str=QString("%1").arg(value);
        ui->Port_Number_2->setText(str);
        Network_Data.server_port=value;
    }else {
        if(value==1)
        {
            ui->One_Net_Interface->setChecked(true);
        }else {
            ui->Two_Net_Interface->setChecked(true);
        }
        Network_Data.net_select=value;
    }
}

void Widget::GetRouter(stRouter_Out route_id_val)
{
    QString str;
    if((route_id_val.uiVidIn<eVIDSIGIN_DVI_D3) || (route_id_val.uiVidIn==eVIDSIGIN_HDMI3) || (route_id_val.uiVidIn>eVIDSIGIN_DVI_D4))
        return;
    if(route_id_val.uiVidOut==eVIDSIGOUT_G1)
    {
        if(route_id_val.uiVidIn!=ui->Input_Ref_ComboBox->currentIndex()+1)
            read_InputSig_ref=true;
        ui->Input_Ref_ComboBox->setCurrentIndex(route_id_val.uiVidIn-1);
        Video_Adjust->SigInId=route_id_val.uiVidIn;
        nRefCurrSigId=route_id_val.uiVidIn;
        stVIDSIGIN_STATUS stStatus;
        stStatus.uiSigInId=route_id_val.uiVidIn;
        stStatus.bIsValid=route_id_val.status;
        stVIDSIGIN_STATUS_ARRAY stStatusList;
        //ubus_interface->VinSigGetStatus(Video_Adjust->SigInId,&stStatusList);
        stStatusList.append(stStatus);
        VidSigIn_GetStatus(true,stStatusList);
        //if(fist_osd_on_off!=0)
        //    ubus_interface->VidSigIn_GetStatus(route_id_val.uiVidIn,1);

        //fist_osd_on_off=1;
    }
    else
    {
        if(route_id_val.uiVidIn!=ui->Input_live_ComboBox->currentIndex()+16)
            read_InputSig_live=true;
        ui->Input_live_ComboBox->setCurrentIndex(route_id_val.uiVidIn-16);
        Video_Adjust->SigInId=route_id_val.uiVidIn;
        //ubus_interface->VidSigIn_GetStatus(route_id_val.uiVidIn,1);

        stVIDSIGIN_STATUS stStatus;
        stStatus.uiSigInId=route_id_val.uiVidIn;
        stStatus.bIsValid=route_id_val.status;
        stVIDSIGIN_STATUS_ARRAY stStatusList;
        //ubus_interface->VinSigGetStatus(Video_Adjust->SigInId,&stStatusList);
        stStatusList.append(stStatus);
        VidSigIn_GetStatus(true,stStatusList);
    }
}

void Widget::SigSwtNextInput(SwitchNextSigOut SwitchStatus)
{
    if(SwitchStatus.RoutId==eVIDSIGOUT_G1)
    {
        if(SwitchStatus.SigId!=ui->Input_Ref_ComboBox->currentIndex()+1)
            read_InputSig_ref=true;
        ui->Input_Ref_ComboBox->setCurrentIndex(SwitchStatus.SigId-1);
        Video_Adjust->SigInId=SwitchStatus.SigId;
        nRefCurrSigId=SwitchStatus.SigId;
        stVIDSIGIN_STATUS stStatus;
        stStatus.uiSigInId=SwitchStatus.SigId;
        stStatus.bIsValid=SwitchStatus.Status;
        stVIDSIGIN_STATUS_ARRAY stStatusList;
        //ubus_interface->VinSigGetStatus(Video_Adjust->SigInId,&stStatusList);
        stStatusList.append(stStatus);
        VidSigIn_GetStatus(true,stStatusList);
        //ubus_interface->VidSigIn_GetStatus(route_id_val.siginid,1);
    }
    else
    {
        if(SwitchStatus.SigId!=ui->Input_live_ComboBox->currentIndex()+16)
            read_InputSig_live=true;
        ui->Input_live_ComboBox->setCurrentIndex(SwitchStatus.SigId-16);
        Video_Adjust->SigInId=SwitchStatus.SigId;
        stVIDSIGIN_STATUS stStatus;
        stStatus.uiSigInId=SwitchStatus.SigId;
        stStatus.bIsValid=SwitchStatus.Status;
        stVIDSIGIN_STATUS_ARRAY stStatusList;
        //ubus_interface->VinSigGetStatus(Video_Adjust->SigInId,&stStatusList);
        stStatusList.append(stStatus);
        VidSigIn_GetStatus(true,stStatusList);
        //ubus_interface->VidSigIn_GetStatus(route_id_val.siginid,1);
    }
}

void Widget::GetDevVer(stCfg_Ver_INFO Ver_Info)
{
   QString str;
   switch (Ver_Info.id) {
     case eDEVSN_DEV+15:
       str=QString("Serial Number: %1").arg(Ver_Info.value);
       ui->label->setText(str);
       break;
     case eDEVVER_LINUX_APP:
       str=QString("Firmware Version: %1").arg(Ver_Info.value);
       ui->label_4->setText(str);
       break;
   case eDEVVER_SCAL_A2796:
     str=QString("2797 Ref Version: %1").arg(Ver_Info.value);
     ui->label_9->setText(str);
     break;
   case eDEVVER_SCAL_C32626:
     str=QString("32626 Version: %1").arg(Ver_Info.value);
     ui->label_10->setText(str);
     break;
   case eDEVVER_MCU_SW:
     str=QString("MCU Version: %1").arg(Ver_Info.value);
     ui->label_11->setText(str);
     break;
   case eDEVVER_FPGA1_FW:
     str=QString("FPGA Ref Version: %1").arg(Ver_Info.value);
     ui->label_12->setText(str);
     break;
   case eDEVVER_SCAL_B2796:
     str=QString("2796 Live Version: %1").arg(Ver_Info.value);
     ui->label_14->setText(str);
     break;
   case eDEVVER_HARDWARE:
     str=QString("hardware Version: %1").arg(Ver_Info.value);
     ui->label_8->setText(str);
     break;
   case eDEVVER_FPGA2_FW:
     str=QString("FPGA Live Version: %1").arg(Ver_Info.value);
     ui->label_17->setText(str);
     break;
   case eDEVVER_FPGA5_FW:
     str=QString("FPGA Switch Version: %1").arg(Ver_Info.value);
     ui->label_18->setText(str);
     break;
   case eDEVVER_MCU_SUB_SW:
     str=QString("MCU SubVersion: %1").arg(Ver_Info.value);
     ui->label_20->setText(str);
     break;
   }

}

void Widget::VidSigIn_GetStatus(int flag,stVIDSIGIN_STATUS_ARRAY stStatus)
{
    QStandardItemModel *pItemModel_ref = qobject_cast<QStandardItemModel*>(ui->Input_Ref_ComboBox->model());
    QStandardItemModel *pItemModel_live = qobject_cast<QStandardItemModel*>(ui->Input_live_ComboBox->model());
    if(flag)
    {
        if(ui->On_Screen_Set_RadioButton_1->isChecked())
            return;

        if(stStatus[0].bIsValid==1)
        {
            if(stStatus[0].uiSigInId<16)
            {
                pItemModel_ref->item(stStatus[0].uiSigInId-1)->setForeground(QColor(Qt::darkGreen));
                display_message->Message_label->setText(QString("%1").arg(ui->Input_Ref_ComboBox->currentText()));
            }
            else
            {
                pItemModel_live->item(stStatus[0].uiSigInId-16)->setForeground(QColor(Qt::darkGreen));
                display_message->Message_label->setText(QString("%1").arg(ui->Input_live_ComboBox->currentText()));
            }

            qDebug()<<display_message->Message_label->text();
            //QThread::msleep(100);
            if(ui->Switch_Input_Slider->value()>0)
            {
                stOsdOnOff_Info smallosdonoff;
                if(ui->RefSmallMsg_radioButton->isChecked())
                {
                    smallosdonoff.id=eDEVFPGA_B;
                    smallosdonoff.value=1;
                    ubus_interface->osd->SetSmallOsdOnOff(smallosdonoff);
                }
                if(ui->LiveSmallMsg_radioButton->isChecked())
                {
                    smallosdonoff.id=eDEVFPGA_C;
                    smallosdonoff.value=1;
                    ubus_interface->osd->SetSmallOsdOnOff(smallosdonoff);
                }
                mutex.lock();
                nDisplaySmallOsdCount++;
                mutex.unlock();
                QTimer::singleShot(ui->Switch_Input_Slider->value()*1000, this, SLOT(Hide_Message()));
            }

        }else
        {

            if(stStatus[0].uiSigInId<16)
            {
                pItemModel_ref->item(stStatus[0].uiSigInId-1)->setForeground(QColor(200, 200, 200));
                display_message->Message_label->setText(QString("No valid signal at %1").arg(ui->Input_Ref_ComboBox->currentText()));
            }
            else
            {
                pItemModel_live->item(stStatus[0].uiSigInId-16)->setForeground(QColor(200, 200, 200));
                display_message->Message_label->setText(QString("No valid signal at %1").arg(ui->Input_live_ComboBox->currentText()));
            }

            qDebug()<<display_message->Message_label->text();
            //QThread::msleep(100);
            if(ui->Main_Vedio_Slider->value()>0)
            {
                stOsdOnOff_Info smallosdonoff;
                if(ui->RefSmallMsg_radioButton->isChecked())
                {
                    smallosdonoff.id=eDEVFPGA_B;
                    smallosdonoff.value=1;
                    ubus_interface->osd->SetSmallOsdOnOff(smallosdonoff);
                }
                if(ui->LiveSmallMsg_radioButton->isChecked())
                {
                    smallosdonoff.id=eDEVFPGA_C;
                    smallosdonoff.value=1;
                    ubus_interface->osd->SetSmallOsdOnOff(smallosdonoff);
                }
                mutex.lock();
                nDisplaySmallOsdCount++;
                mutex.unlock();
                QTimer::singleShot(ui->Main_Vedio_Slider->value()*1000, this, SLOT(Hide_Message()));
            }
        }
        return;
    }

    stVIDSIGIN_STATUS VidSigInStatus=stStatus[0];
    //qDebug()<<"OSD:"<<VidSigInStatus.uiSigInId<<VidSigInStatus.bIsValid<<VidSigInStatus.uiFrameHActive<<VidSigInStatus.uiFrameVActive<<VidSigInStatus.uiFrameVFreqP10<<VidSigInStatus.uiFrameHFreqP10K<<VidSigInStatus.uiPixelClkP10M;
    QString SigInName;
    if(VidSigInStatus.uiSigInId<16)
    {
        SigInName=QString("Input: %1").arg(ui->Input_Ref_ComboBox->currentText());
        Video_Adjust->SetInformationControlInfo(VidSigInStatus,SigInName);
        GetPresetParams(VidSigInStatus.bIsValid);
    }
    else
    {
        SigInName=QString("Input: %1").arg(ui->Input_live_ComboBox->currentText());
        Video_Adjust->SetInformationControlInfo(VidSigInStatus,SigInName);
        GetPresetParams(VidSigInStatus.bIsValid);
    }
}

void Widget::VidSigIn_Scan(int ok, stScan VinSigStatus)
{
    QStandardItemModel *pItemModel_ref = qobject_cast<QStandardItemModel*>(ui->Input_Ref_ComboBox->model());
    if(ok)
    {
        int curr_sig_id=0,next_sig_id=0;
        switch (VinSigStatus.uiSigInId) {
        case 1:
           curr_sig_id=eVIDSIGIN_DVI_D1;
           next_sig_id=eVIDSIGIN_DVI_D2;
            break;
        case 2:
           curr_sig_id=eVIDSIGIN_DVI_D2;
           next_sig_id=eVIDSIGIN_DVI_D3;
            break;
        case 3:
           curr_sig_id=eVIDSIGIN_DVI_D3;
           next_sig_id=eVIDSIGIN_HDMI1;
            break;
        case 4:
           curr_sig_id=eVIDSIGIN_HDMI1;
           next_sig_id=eVIDSIGIN_HDMI2;
            break;
        case 5:
           curr_sig_id=eVIDSIGIN_HDMI2;
           next_sig_id=eVIDSIGIN_DP1;
            break;
        case 6:
           curr_sig_id=eVIDSIGIN_DP1;
           next_sig_id=eVIDSIGIN_DP2;
            break;
        case 7:
           curr_sig_id=eVIDSIGIN_DP2;
           next_sig_id=eVIDSIGIN_CVBS;
            break;
        case 8:
           curr_sig_id=eVIDSIGIN_CVBS;
           next_sig_id=eVIDSIGIN_S_VIDEO1;
            break;
        case 9:
           curr_sig_id=eVIDSIGIN_S_VIDEO1;
           next_sig_id=eVIDSIGIN_S_VIDEO2;
            break;
        case 10:
           curr_sig_id=eVIDSIGIN_S_VIDEO2;
           next_sig_id=eVIDSIGIN_DVI_A1;
            break;
        case 11:
           curr_sig_id=eVIDSIGIN_DVI_A1;
           next_sig_id=eVIDSIGIN_DVI_A2;
            break;
        case 12:
           curr_sig_id=eVIDSIGIN_DVI_A2;
           next_sig_id=eVIDSIGIN_SDI1;
            break;
        case 13:
           curr_sig_id=eVIDSIGIN_SDI1;
           next_sig_id=eVIDSIGIN_SDI2;
            break;
        case 14:
           curr_sig_id=eVIDSIGIN_SDI2;
            break;
        default:
            break;
        }

        if(VinSigStatus.uiSigInId<eVIDSIGIN_DVI_D3-1 || VinSigStatus.uiSigInId>eVIDSIGIN_SDI2)
            return;

        if(VinSigStatus.uiSigInId==eVIDSIGIN_DVI_D3-1)
        {
            for(int i=0;i<eVIDSIGIN_SDI2;i++)
            {
                sigvinscan->label_list[i]->setText("");
            }
        }
        QFont ft;
        ft.setPointSize(11);
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::black);

        QPalette pa1;
        pa1.setColor(QPalette::WindowText,Qt::darkGreen);

        QPalette pa2;
        pa2.setColor(QPalette::WindowText,Qt::gray);


        QString str;
        if(VinSigStatus.uiSigInId>eVIDSIGIN_DVI_D3-1)
        {
            if(VinSigStatus.bIsValid==1)
            {
               pItemModel_ref->item(curr_sig_id-1)->setForeground(QColor(Qt::darkGreen));
               if(VinSigStatus.bIsInterLace==1)
                   str=QString("%1").arg(ui->Input_Ref_ComboBox->itemText(curr_sig_id-1));
                else
                   str=QString("%1").arg(ui->Input_Ref_ComboBox->itemText(curr_sig_id-1));
               sigvinscan->label_list[VinSigStatus.uiSigInId-1]->setFont(ft);
               sigvinscan->label_list[VinSigStatus.uiSigInId-1]->setPalette(pa1);
               sigvinscan->label_list[VinSigStatus.uiSigInId-1]->setText(str);
            }
            else
            {
               pItemModel_ref->item(curr_sig_id-1)->setForeground(QColor(200, 200, 200));
               str=QString("%1").arg(ui->Input_Ref_ComboBox->itemText(curr_sig_id-1));
               sigvinscan->label_list[VinSigStatus.uiSigInId-1]->setFont(ft);
               sigvinscan->label_list[VinSigStatus.uiSigInId-1]->setPalette(pa2);
               sigvinscan->label_list[VinSigStatus.uiSigInId-1]->setText(str);
            }


            if(VinSigStatus.uiSigInId<eVIDSIGIN_SDI2)
            {
                sigvinscan->label_list[VinSigStatus.uiSigInId]->setFont(ft);
                sigvinscan->label_list[VinSigStatus.uiSigInId]->setPalette(pa);
                str=QString("%1").arg(ui->Input_Ref_ComboBox->itemText(next_sig_id-1));
                sigvinscan->label_list[VinSigStatus.uiSigInId]->setText(str);
            }
        }


        uchar OnOff;
        if(ui->Input_Config_RadioButton_2->isChecked() && (VinSigStatus.uiSigInId==eVIDSIGIN_DVI_D3-1) && ui->On_Screen_Set_RadioButton_2->isChecked())
        {
            //ubus_interface->GetOsdOnOff(&OnOff);
            //OsdOnOff_Scan=OnOff;
            //QApplication::setOverrideCursor(Qt::BlankCursor);
            //sigvinscan->show();
            sigvinscan->label_list[0]->setFont(ft);
            sigvinscan->label_list[0]->setPalette(pa);
            str=QString("%1").arg(ui->Input_Ref_ComboBox->itemText(2));
            sigvinscan->label_list[0]->setText(str);

            this->setCursor(Qt::BlankCursor);
            sigvinscan->setMouseHide();
            stOsdOnOff_Info osdonoff;
            osdonoff.id=eDEVFPGA_B;
            osdonoff.value=1;
            ubus_interface->osd->SetScanListOnOff(osdonoff);
            osdonoff.id=eDEVFPGA_C;
            osdonoff.value=1;
            ubus_interface->osd->SetScanListOnOff(osdonoff);
            blIsHideScanDlg=false;
        }

        if(VinSigStatus.uiSigInId==eVIDSIGIN_SDI2)
        {
            blIsHideScanDlg=true;
            QDBusPendingReply<stRouter> reply = ubus_interface->sigvin->VinSetRouteAfterScan();
            //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
            //所以需要调用waitForFinished来等到Message执行完成
            reply.waitForFinished();
            if (reply.isValid())
            {
                qDebug()<<"VinSetRouteAfterScan"<<reply.value().uiVidIn<<reply.value().uiVidOut;
                if(reply.value().uiVidOut==eVIDSIGOUT_G1)
                {
                    if(reply.value().uiVidIn!=ui->Input_Ref_ComboBox->currentIndex()+1)
                        read_InputSig_ref=true;
                    ui->Input_Ref_ComboBox->setCurrentIndex(reply.value().uiVidIn-1);
                }
            }
            QTimer::singleShot(ui->Scan_Input_Slider->value()*1000, this, SLOT(ScanCompleted()));
        }
    }
}

void Widget::StopScan(uchar status)
{
    if(status==1)
    {
            stOsdOnOff_Info osdonoff;
            osdonoff.id=eDEVFPGA_B;
            osdonoff.value=0;
            ubus_interface->osd->SetScanListOnOff(osdonoff);
            osdonoff.id=eDEVFPGA_C;
            osdonoff.value=0;
            ubus_interface->osd->SetScanListOnOff(osdonoff);
            this->setCursor(Qt::ArrowCursor);
            for(int i=0;i<eVIDSIGIN_SDI2;i++)
                sigvinscan->label_list[i]->setText("");

            stRouter GetRouterId;
            ubus_interface->VidRout_GetRouter(eVIDSIGOUT_G1,&GetRouterId);
            if((GetRouterId.uiVidIn<eVIDSIGIN_DVI_D3) || (GetRouterId.uiVidIn==eVIDSIGIN_HDMI3) || (GetRouterId.uiVidIn>eVIDSIGIN_DVI_D4))
                return;
            if(GetRouterId.uiVidIn!=ui->Input_Ref_ComboBox->currentIndex()+1)
                read_InputSig_ref=true;
            ui->Input_Ref_ComboBox->setCurrentIndex(GetRouterId.uiVidIn-1);
    }
}

void Widget::ScanCompleted()
{
    if(blIsHideScanDlg)
    {
        stOsdOnOff_Info osdonoff;
        osdonoff.id=eDEVFPGA_B;
        osdonoff.value=0;
        ubus_interface->osd->SetScanListOnOff(osdonoff);
        osdonoff.id=eDEVFPGA_C;
        osdonoff.value=0;
        ubus_interface->osd->SetScanListOnOff(osdonoff);
        this->setCursor(Qt::ArrowCursor);
        for(int i=0;i<eVIDSIGIN_SDI2;i++)
            sigvinscan->label_list[i]->setText("");
    }
}

void Widget::Grab_Image_Button()
{
    ui->Grab_Image_pushButton->setEnabled(true);
    ui->Grab_Image_pushButton_2->setEnabled(true);
}

void Widget::VidSigOutPort_GetOnOff(PortStatus OutPortStatus)
{
    ui->Output_Ref_checkBox->setChecked(OutPortStatus.RefCAT6);
    ui->Output_Ref_checkBox_2->setChecked(OutPortStatus.RefDVI);
    ui->Output_Ref_checkBox_3->setChecked(OutPortStatus.RefDP);
    ui->Output_Ref_checkBox_4->setChecked(OutPortStatus.RefSDI);
    ui->Output_live_checkBox->setChecked(OutPortStatus.LIVECAT6);
    ui->Output_live_checkBox_2->setChecked(OutPortStatus.LIVEDVI);
    ui->Output_live_checkBox_3->setChecked(OutPortStatus.LIVEDP);
    ui->Output_live_checkBox_4->setChecked(OutPortStatus.LIVESDI);
}

void Widget::slot_VidSigOutPortSdiType(stOutSig_INFO stSdiStatus)
{
    if(stSdiStatus.gid==eVIDSIGOUT_G1)
    {
        if(stSdiStatus.sigid==0)
            ui->Ref_SDI_1080p_radioButton->setChecked(true);
        if(stSdiStatus.sigid==1)
            ui->Ref_SDI_1080i_radioButton->setChecked(true);
    }

    if(stSdiStatus.gid==eVIDSIGOUT_G2)
    {
        if(stSdiStatus.sigid==0)
            ui->Live_SDI_1080p_radioButton->setChecked(true);
        if(stSdiStatus.sigid==1)
            ui->Live_SDI_1080i_radioButton->setChecked(true);
    }
}

void Widget::GetDevcomm_Net_IP(stDEVCOMM_NET stDevcomm_Net)
{
    if(stDevcomm_Net.uiNetIndex==1)
    {
        Network_Data.strIpAddr[0]=stDevcomm_Net.strIpAddr;
        Network_Data.bIsDHCP[0]=stDevcomm_Net.bIsDHCP;
        Network_Data.strMask[0]=stDevcomm_Net.strMask;
        Network_Data.strGate[0]=stDevcomm_Net.strGate;
        Network_Data.strNDS1[0]=stDevcomm_Net.strNDS1;
        Network_Data.strNDS2[0]=stDevcomm_Net.strNDS2;
        ui->Net1_IP_Edit->setText(stDevcomm_Net.strIpAddr);
        ui->Net1_Mask_Edit->setText(stDevcomm_Net.strMask);
    }else
    {
        Network_Data.strIpAddr[1]=stDevcomm_Net.strIpAddr;
        Network_Data.bIsDHCP[1]=stDevcomm_Net.bIsDHCP;
        Network_Data.strMask[1]=stDevcomm_Net.strMask;
        Network_Data.strGate[1]=stDevcomm_Net.strGate;
        Network_Data.strNDS1[1]=stDevcomm_Net.strNDS1;
        Network_Data.strNDS2[1]=stDevcomm_Net.strNDS2;
        ui->Net2_IP_Edit->setText(stDevcomm_Net.strIpAddr);
        ui->Net2_Mask_Edit->setText(stDevcomm_Net.strMask);
    }
}

void Widget::ComboBox_currentIndexChanged(int index)
{
    QComboBox* comboBox = qobject_cast<QComboBox*>(sender());
    if(comboBox->objectName()=="Input_Ref_ComboBox")
    {
        if(!read_InputSig_ref)
        {
            stRouter_In setRouter;
            setRouter.uiVidIn=ui->Input_Ref_ComboBox->currentIndex()+1;
            setRouter.uiVidOut=eVIDSIGOUT_G1;
            setRouter.socket=0;
            setRouter.cmdid=0;
            ubus_interface->VidRout_SetRouter(setRouter);
        }
        read_InputSig_ref=false;
    }

    if(comboBox->objectName()=="Input_live_ComboBox")
    {
        if(!read_InputSig_live)
        {
            stRouter_In setRouter;
            setRouter.uiVidIn=ui->Input_live_ComboBox->currentIndex()+16;
            setRouter.uiVidOut=eVIDSIGOUT_G2;
            setRouter.socket=0;
            setRouter.cmdid=0;
            ubus_interface->VidRout_SetRouter(setRouter);
        }
        read_InputSig_live=false;
    }
}

void Widget::DateTime_Display()
{
    QDate date;
    QTime time;
    if(datetime.time().second()==59)
    {
        if(datetime.time().minute()==59)
        {
            //date.setDate(datetime.date().year(),datetime.date().month(),datetime.date().day());
            date.setDate(ui->dateTimeEdit->date().year(),ui->dateTimeEdit->date().month(),ui->dateTimeEdit->date().day());
            time.setHMS(datetime.time().hour()+1,0,0);
        }
        else
        {
            //date.setDate(datetime.date().year(),datetime.date().month(),datetime.date().day());
            date.setDate(ui->dateTimeEdit->date().year(),ui->dateTimeEdit->date().month(),ui->dateTimeEdit->date().day());
            time.setHMS(ui->dateTimeEdit->time().hour(),datetime.time().minute()+1,0);
        }
    }else
    {
       //date.setDate(datetime.date().year(),datetime.date().month(),datetime.date().day());
       date.setDate(ui->dateTimeEdit->date().year(),ui->dateTimeEdit->date().month(),ui->dateTimeEdit->date().day());
       time.setHMS(ui->dateTimeEdit->time().hour(),ui->dateTimeEdit->time().minute(),datetime.time().second()+1);
    }

    datetime.setDate(date);
    datetime.setTime(time);

    ui->dateTimeEdit->setDateTime(datetime);
}

void Widget::gt_DP_INFO(int sigid)
{
    gtSCAL_INPUT_DP_INFO DP_Lane_Info;
    DP_Lane_Info.SigInId=Video_Adjust->SigInId;
    DP_Lane_Info.uiLane_ID=0;
    stSCAL_INPUT_DP_INFO DPInfo;

    ubus_interface->VidSigIn_GetDpDbgInfo(DP_Lane_Info, &DPInfo);
    Video_Adjust->dp_adjustment->GetDPLinkTrainingInfo(sigid,DPInfo);
}

void Widget::st_DP_INFO(stSCAL_INPUT_DP_INFO DP_Info)
{
    ubus_interface->sigvin->VinSigSetDpDbgInfo(DP_Info);
    QtConcurrent::run(this,&Widget::GetDPLinkTraining);
}

void Widget::slot_Read_CTmep_Scaing(int CTmep_Scaing)
{
    stVALUE_INFO CTmep_Scaing_Info;
    if(CTmep_Scaing==1)
    {
        CTmep_Scaing_Info.type=Video_Adjust->SigInId;
        CTmep_Scaing_Info.value=1;
        ubus_interface->VidSigIn_GetCTemp(CTmep_Scaing_Info);
    }

    if(CTmep_Scaing==2)
    {
        CTmep_Scaing_Info.type=Video_Adjust->SigInId;
        CTmep_Scaing_Info.value=1;
        ubus_interface->VidSigIn_GetScaling(CTmep_Scaing_Info);
    }
}

void Widget::Test()
{
    for(int i=0;i<eVIDSIGIN_SDI2;i++)
    {
        sigvinscan->setCursor(Qt::BlankCursor);
        sigvinscan->label_list[i]->setCursor(Qt::BlankCursor);
    }
}

void Widget::displayTipsInfo(QString str)
{
    QMessageBox::question(this, tr("Information"), str, QMessageBox::Ok);
}

void Widget::on_OSD_Hide_pushButton_clicked()
{
    stOsdOnOff_Info osdonoff;
    osdonoff.id=eDEVFPGA_B;
    osdonoff.value=0;
    ubus_interface->osd->SetOnOff(osdonoff);
    osdonoff.id=eDEVFPGA_C;
    osdonoff.value=0;
    ubus_interface->osd->SetOnOff(osdonoff);
}

void Widget::OSD_Hide_Mouse()
{
    if(Video_Adjust->mouse_no_work_time.secsTo(QTime::currentTime())>ui->Mouse_Slider->value())
    {
        QApplication::setOverrideCursor(Qt::BlankCursor);
        DisableControlCursor();
    }
}

void Widget::Hide_Message()
{
    mutex.lock();
    if(nDisplaySmallOsdCount==1)
    {
        stOsdOnOff_Info smallosdonoff;
        smallosdonoff.id=eDEVFPGA_B;
        smallosdonoff.value=0;
        ubus_interface->osd->SetSmallOsdOnOff(smallosdonoff);
        smallosdonoff.id=eDEVFPGA_C;
        smallosdonoff.value=0;
        ubus_interface->osd->SetSmallOsdOnOff(smallosdonoff);
    }
    nDisplaySmallOsdCount--;
    mutex.unlock();
}

void Widget::GetDPLinkTraining()
{
    //Video_Adjust->dp_adjustment->Lane_Num_comboBox->setEnabled(false);
    Video_Adjust->dp_adjustment->Submit_toolButton->setEnabled(false);
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    Video_Adjust->dp_adjustment->Prompt_Label->setPalette(pe);
    Video_Adjust->dp_adjustment->Prompt_Label->setText("Set DP Success !!! DP Link Training Again...");
    QThread::msleep( 6000 );
    gt_DP_INFO(1);
    QThread::msleep( 13000 );
    Video_Adjust->dp_adjustment->Prompt_Label->setText("DP Link Training Finished");
   // Video_Adjust->dp_adjustment->Lane_Num_comboBox->setEnabled(true);
    Video_Adjust->dp_adjustment->Submit_toolButton->setEnabled(true);
    QThread::msleep( 1000 );
    Video_Adjust->dp_adjustment->Prompt_Label->setText(" ");
}

void Widget::on_tabWidget_currentChanged(int index)
{
    if(nTabIndex==VIDEO_SETTING_INDEX)
        ubus_interface->VinDispSetAnalogModeDebug(0);

    stRouter GetRouterId;
    uchar uOnOff;
    uchar uTime;
    switch (index) {
    case VIDEO_LIVE_INDEX:
        ubus_interface->VidRout_GetRouter(eVIDSIGOUT_G2,&GetRouterId);
        if(GetRouterId.uiVidIn!=ui->Input_live_ComboBox->currentIndex()+16)
            read_InputSig_live=true;
        ui->Input_live_ComboBox->setCurrentIndex(GetRouterId.uiVidIn-16);
        break;;
    case VIDEO_SETTING_INDEX:

        ubus_interface->VinDispSetAnalogModeDebug(1);
        getVideoSettingParameters();

        switch (Video_Adjust->SigInId) {
        case eVIDSIGIN_DVI_A1:
        case eVIDSIGIN_DVI_A2:
        case eVIDSIGIN_S_VIDEO1:
        case eVIDSIGIN_S_VIDEO2:
        case eVIDSIGIN_CVBS:
           ui->groupBox_13->setEnabled(true);
           ui->groupBox_14->setEnabled(true);
           if((Video_Adjust->SigInId==eVIDSIGIN_S_VIDEO1) || (Video_Adjust->SigInId==eVIDSIGIN_S_VIDEO2) || (Video_Adjust->SigInId==eVIDSIGIN_CVBS))
           {
               ui->AutoAdjustButton->setEnabled(false);
               ui->HTotalSlider->setEnabled(false);
               ui->HTotalspinBox->setEnabled(false);
           }else {
               ui->AutoAdjustButton->setEnabled(true);
               ui->HTotalSlider->setEnabled(true);
               ui->HTotalspinBox->setEnabled(true);
           }
           break;
        default:
           ui->groupBox_13->setEnabled(false);
           ui->groupBox_14->setEnabled(false);
           break;
        }

        break;
    case NETWORK_INDEX:
        getNetworkParameters();
        break;
    case SYSTEM_INDEX:
        getSystemParameters();
        break;
    default:
        break;
    }
    nTabIndex=index;
}

void Widget::slotGetAnalogOverlay(int index)
{
    stSCAL_ANALOG_INPUT_PARAMS stScalAnalogInputParams;
    stVStart stHStartValue,stVStartValue;
    switch (index) {
    case OVERLAY_MODES:
        Video_Adjust->dlgOverlayModes->displayLoadProgress(tr("Loading..."));
        Video_Adjust->dlgOverlayModes->show();
        QtConcurrent::run(this,&Widget::setAnalogOverlayData);
        //ubus_interface->VinDispGetAnalogOverlay(&OverlayModeCount,&stValue);
        //Video_Adjust->dlgOverlayModes->displayTableData(nCount,nIndex,stValue);
        break;
    case NEW_OVERLAY_MODES:
        ubus_interface->VinDispGetAnalogInputParams(&stScalAnalogInputParams);
        ubus_interface->VinSigIn_GetHStart(Video_Adjust->SigInId,&stHStartValue);
        ubus_interface->VinSigIn_GetVStart(Video_Adjust->SigInId,&stVStartValue);
//        Video_Adjust->dlgNewOverlay->setTableData(stScalAnalogInputParams,stHStartValue,stVStartValue);
//        Video_Adjust->dlgNewOverlay->show();
        break;
    case CLEAR_OVERLAY_MODES:
        ubus_interface->VinDispClearAnalogModeIndexTable();
        break;
    }
}

void Widget::slotSetRouteNotice(uchar)
{
    display_message->Message_label->setText(" ");
}

void Widget::slotSetSwtOutput(uchar ucOnOff)
{
    if(ucOnOff==0)
    {
        ui->Switch_Output_Button->setStyleSheet("background-color:rgb(0,117,255)");
        ui->Switch_Output_Button_2->setStyleSheet("background-color:rgb(0,117,255)");
    }else {
        ui->Switch_Output_Button->setStyleSheet("background-color:rgb(240,240,240)");
        ui->Switch_Output_Button_2->setStyleSheet("background-color:rgb(240,240,240)");
    }
}
void Widget::setAnalogOverlayData()
{

    stAnalogOverlayCount OverlayModeCount;
    stSCAL_ANALOG_MODE_PARAMS_Index_Array stValue;
    ubus_interface->VinDispGetAnalogOverlay(&OverlayModeCount,&stValue);
    emit emitSetOverlayModesData(OverlayModeCount.nCount,OverlayModeCount.nCnrrNum,stValue);
    //Video_Adjust->dlgOverlayModes->displayTableData(OverlayModeCount.nCount,OverlayModeCount.nCnrrNum,stValue);
}

bool Widget::getVideoSettingParameters()
{
    stVIDSIGIN_STATUS_ARRAY stSigStatus;
    ubus_interface->VinSigGetStatus(nRefCurrSigId,&stSigStatus);
    qDebug()<<"OSD:"<<nRefCurrSigId<<stSigStatus[0].bIsValid<<stSigStatus[0].uiSigInId<<stSigStatus[0].uiFrameHActive<<stSigStatus[0].uiFrameVActive;
    if(!stSigStatus[0].bIsValid)
    {
        switch (nRefCurrSigId) {
        case eVIDSIGIN_DVI_A1:
        case eVIDSIGIN_DVI_A2:
            stSigStatus[0].uiFrameHActive=640;
            stSigStatus[0].uiFrameVActive=480;
            break;
        case eVIDSIGIN_S_VIDEO1:
        case eVIDSIGIN_S_VIDEO2:
        case eVIDSIGIN_CVBS:
            stSigStatus[0].uiFrameHActive=640;
            stSigStatus[0].uiFrameVActive=240;
            break;
        default:
            break;
        }
    }else
    {
        if(stSigStatus[0].uiFrameHActive==0)
            stSigStatus[0].uiFrameHActive=600;

        if(stSigStatus[0].uiFrameVActive==0)
            stSigStatus[0].uiFrameVActive=200;
    }

    ui->HActiveSlider->setValue(stSigStatus[0].uiFrameHActive);
    if(stSigStatus[0].bIsInterLace)
    {
        ui->InterlacecheckBox->setChecked(true);
        ui->VActiveSlider->setValue(stSigStatus[0].uiFrameVActive*2);
        ui->NameEdit->setText(QString("%1_%2").arg(stSigStatus[0].uiFrameHActive).arg(stSigStatus[0].uiFrameVActive*2));
    }else {
        ui->InterlacecheckBox->setChecked(false);
        ui->VActiveSlider->setValue(stSigStatus[0].uiFrameVActive);
        ui->NameEdit->setText(QString("%1_%2").arg(stSigStatus[0].uiFrameHActive).arg(stSigStatus[0].uiFrameVActive));
    }


    gtFrequency_INFO stFrequency;
    if(stSigStatus[0].bIsValid==1)
        ubus_interface->VidSigIn_GetFrequency(nRefCurrSigId,&stFrequency);
    if((stSigStatus[0].bIsValid==0) || (stFrequency.minvlaue>=stFrequency.maxvlaue) || (stFrequency.currtvalue<stFrequency.minvlaue) || (stFrequency.currtvalue>stFrequency.maxvlaue))
    {
        stFrequency.currtvalue=600;
        stFrequency.minvlaue=600;
        stFrequency.maxvlaue=4000;
    }

    if(stFrequency.currtvalue != ui->HTotalSlider->value())
        read_HTotal=true;
    if((stFrequency.minvlaue!=ui->HTotalSlider->minimum()) ||(stFrequency.maxvlaue!=ui->HTotalSlider->maximum()))
        read_HTotal=true;
    ui->HTotalSlider->setMinimum(stFrequency.minvlaue);
    ui->HTotalSlider->setMaximum(stFrequency.maxvlaue);
    ui->HTotalspinBox->setMinimum(stFrequency.minvlaue);
    ui->HTotalspinBox->setMaximum(stFrequency.maxvlaue);
    QThread::msleep(50);
    ui->HTotalSlider->setValue(stFrequency.currtvalue);

    stVStart stHVStartValue;
    if(stSigStatus[0].bIsValid==1)
        ubus_interface->VinSigIn_GetHStart(nRefCurrSigId,&stHVStartValue);
    if((stSigStatus[0].bIsValid==0) || (stHVStartValue.nMinValue>=stHVStartValue.nMaxValue) || (stHVStartValue.nVStartValue<stHVStartValue.nMinValue) || (stHVStartValue.nVStartValue>stHVStartValue.nMaxValue))
    {
        stHVStartValue.nVStartValue=0;
        stHVStartValue.nMinValue=0;
        stHVStartValue.nMaxValue=400;
    }
    if(stHVStartValue.nVStartValue != ui->HStartSlider->value())
        read_HStart=true;
    if((stHVStartValue.nMinValue!=ui->HStartSlider->minimum()) ||(stHVStartValue.nMaxValue!=ui->HStartSlider->maximum()))
        read_HStart=true;
    ui->HStartSlider->setMinimum(stHVStartValue.nMinValue);
    ui->HStartSlider->setMaximum(stHVStartValue.nMaxValue);
    ui->HStartspinBox->setMinimum(stHVStartValue.nMinValue);
    ui->HStartspinBox->setMaximum(stHVStartValue.nMaxValue);
    ui->HStartSlider->setValue(stHVStartValue.nVStartValue);

    if(stSigStatus[0].bIsValid==1)
        ubus_interface->VinSigIn_GetVStart(nRefCurrSigId,&stHVStartValue);
    if((stSigStatus[0].bIsValid==0) || (stHVStartValue.nMinValue>=stHVStartValue.nMaxValue) || (stHVStartValue.nVStartValue<stHVStartValue.nMinValue) || (stHVStartValue.nVStartValue>stHVStartValue.nMaxValue))
    {
        stHVStartValue.nVStartValue=0;
        stHVStartValue.nMinValue=0;
        stHVStartValue.nMaxValue=400;
    }

    if(stHVStartValue.nVStartValue != ui->VStartSlider->value())
        read_VStart=true;
    if((stHVStartValue.nMinValue!=ui->VStartSlider->minimum()) ||(stHVStartValue.nMaxValue!=ui->VStartSlider->maximum()))
        read_VStart=true;
    ui->VStartSlider->setMinimum(stHVStartValue.nMinValue);
    ui->VStartSlider->setMaximum(stHVStartValue.nMaxValue);
    ui->VStartspinBox->setMinimum(stHVStartValue.nMinValue);
    ui->VStartspinBox->setMaximum(stHVStartValue.nMaxValue);
    ui->VStartSlider->setValue(stHVStartValue.nVStartValue);

    stSCAL_ANALOG_INPUT_PARAMS stScalAnalogInputParams;
    ubus_interface->VinDispGetAnalogInputParams(&stScalAnalogInputParams);
    ui->labelHFreq->setText(QString("H-Freq: %1 KHz").arg(QString::number((double)stScalAnalogInputParams.uiH_Freq/10, 'f', 1)));
    ui->labelVFreq->setText(QString("V-Freq: %1 Hz").arg(QString::number((double)stScalAnalogInputParams.uiV_Freq/10, 'f', 1)));
    ui->labelVTotal->setText(QString("V-Total: %1 lines").arg(stScalAnalogInputParams.uiV_Total));

    if(stSigStatus[0].bIsInterLace)
        ui->labelVTotal->setText(QString("V-Total: %1 lines").arg(stScalAnalogInputParams.uiV_Total*2+1));
    else
        ui->labelVTotal->setText(QString("V-Total: %1 lines").arg(stScalAnalogInputParams.uiV_Total));

}

bool Widget::setVideoSetting(int nMode)
{
    stSCAL_ANALOG_MODE_PARAMS stScalAnalogModeParams;
    int nResult;
    stScalAnalogModeParams.PresetName=ui->NameEdit->text();
    QString str;
    str=ui->labelHFreq->text();
    str.chop(4);
    stScalAnalogModeParams.uiH_Freq=str.remove(0,8).toDouble()*10;
    str=ui->labelVFreq->text(); 
    str.chop(3);
    stScalAnalogModeParams.uiV_Freq=str.remove(0,8).toDouble()*10;
    str=ui->labelVTotal->text();
    str.chop(6);
    stScalAnalogModeParams.uiV_Total=str.remove(0,9).toInt();

    stScalAnalogModeParams.uiH_Active=ui->HActivespinBox->value();
    stScalAnalogModeParams.uiV_Active=ui->VActivespinBox->value();
    stScalAnalogModeParams.uiH_Total=ui->HTotalspinBox->value();
    stScalAnalogModeParams.uiH_Start=ui->HStartspinBox->value();
    stScalAnalogModeParams.uiV_Start=ui->VStartspinBox->value();
    stScalAnalogModeParams.uiValidPortFlag=0;

    if(ui->InterlacecheckBox->isChecked())
    {
        stScalAnalogModeParams.ModeType=4;
        stScalAnalogModeParams.uiV_Total=(stScalAnalogModeParams.uiV_Total-1)/2;
        stScalAnalogModeParams.uiV_Active=(stScalAnalogModeParams.uiV_Active+1)/2;
    }
    else
       stScalAnalogModeParams.ModeType=0;

   stSCAL_ANALOG_INPUT_PARAMS stScalAnalogInputParams;
   stVIDSIGIN_STATUS_ARRAY stSigStatus;
    switch (nMode) {
    case DebugOverlayData:
       ubus_interface->VinSigGetStatus(nRefCurrSigId,&stSigStatus);
//       if(stScalAnalogModeParams.uiH_Total<stScalAnalogModeParams.uiH_Active)
//       {
//           QMessageBox::warning(this, tr("Warning"), QString(tr("The value of H-Total should be greater than H-Active!")), QMessageBox::Ok);
//           return false;
//       }
       ubus_interface->VinDispDebugAnalogParams(stScalAnalogModeParams);
//       QThread::msleep(500);
//       ubus_interface->VinDispGetAnalogInputParams(&stScalAnalogInputParams);
//       ui->labelHFreq->setText(QString("H-Freq: %1 KHz").arg(QString::number((double)stScalAnalogInputParams.uiH_Freq/10, 'f', 1)));
//       ui->labelVFreq->setText(QString("V-Freq: %1 Hz").arg(QString::number((double)stScalAnalogInputParams.uiV_Freq/10, 'f', 1)));
//       if(stSigStatus[0].bIsInterLace)
//            ui->labelVTotal->setText(QString("V-Total: %1 lines").arg(stScalAnalogInputParams.uiV_Total*2+1));
//       else
//           ui->labelVTotal->setText(QString("V-Total: %1 lines").arg(stScalAnalogInputParams.uiV_Total));
        break;
    case SaveOverlayData:
       if(stScalAnalogModeParams.PresetName.count()>18)
       {
            QMessageBox::warning(this, tr("Warning"), QString(tr("Name is too long,the maximum length is 18!")), QMessageBox::Ok);
             return false;
       }
       ubus_interface->VinDispSetAnalogParams(stScalAnalogModeParams,&nResult);
       if(nResult==-3)
           QMessageBox::warning(this, tr("Warning"), QString(tr("No space for another mode params! Max new mode num :60")), QMessageBox::Ok);
       else if(nResult==-2)
           QMessageBox::warning(this, tr("Warning"), QString(tr("wrong args. [74 <= HF <= 1700, 230 <= VF <= 2000,200 <= VTotal <= 1600]")), QMessageBox::Ok);
       else if(nResult==-1)
           QMessageBox::warning(this, tr("Warning"), QString(tr("Save Fail! I2C Communication error")), QMessageBox::Ok);
       else if(nResult==0)
           QMessageBox::warning(this, tr("Information"), QString(tr("Save success")), QMessageBox::Ok);
       else if(nResult==1)
           QMessageBox::warning(this, tr("Information"), QString(tr("Current mode params already exits!")), QMessageBox::Ok);
        break;
    default:
        break;
    }

    return true;
}

bool Widget::getSystemParameters()
{
    ubus_interface->client_getWorkTime();
    ubus_interface->client_getCalibTime();
    ubus_interface->client_getNetMac(2);
    ubus_interface->client_getNetMac(1);
    ubus_interface->DevVers_GetDev_SN(eDEVSN_DEV);
    ubus_interface->DevVers_GetDev_Ver(eDEVVER_LINUX_APP);
    ubus_interface->DevVers_GetDev_Ver(eDEVVER_SCAL_A2796);
    ubus_interface->DevVers_GetDev_Ver(eDEVVER_SCAL_B2796);
    ubus_interface->DevVers_GetDev_Ver(eDEVVER_MCU_SW);
    ubus_interface->DevVers_GetDev_Ver(eDEVVER_FPGA1_FW);
    ubus_interface->DevVers_GetDev_Ver(eDEVVER_SCAL_C32626);
    ubus_interface->DevVers_GetDev_Ver(eDEVVER_HARDWARE);
    ubus_interface->DevVers_GetDev_Ver(eDEVVER_FPGA2_FW);
    ubus_interface->DevVers_GetDev_Ver(eDEVVER_FPGA5_FW);
    ubus_interface->DevVers_GetDev_Ver(eDEVVER_MCU_SUB_SW);
}

bool Widget::getNetworkParameters()
{
    ubus_interface->client_getNetIp(1);
    ubus_interface->client_getNetIp(2);
    ubus_interface->client_GetCmdNetPort();
    ubus_interface->client_GetCmdNetSelect();
    ubus_interface->client_getDicommSvrInfo(1);
    ubus_interface->client_getDicommSvrInfo(2);
}

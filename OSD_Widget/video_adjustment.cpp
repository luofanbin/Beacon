#include "video_adjustment.h"
#include<QMouseEvent>
#include<QToolButton>
#include<QMessageBox>
//#include "ui_video_adjustment.h"

VideoAdjustment::VideoAdjustment(QWidget *parent) :QWidget(parent)//,ui(new Ui::Video_Adjustment)
{
    setupUi(this);

    QIcon close_button_ico(":/image/close.png");
    this->toolButton->setIcon(close_button_ico);

    this->Display_DICOM_RadioButton->setHidden(true);
    dp_adjustment=new DpAdjustment();
    connect(dp_adjustment,SIGNAL(st_DP_Info(stSCAL_INPUT_DP_INFO)),this,SLOT(st_DP_Info(stSCAL_INPUT_DP_INFO)));
    connect(dp_adjustment,SIGNAL(gt_DP_Info(int)),this,SLOT(gt_DP_Info(int)));

    this->setFixedSize(1024,768);
    //dlgNewOverlay=new NewOverlayMode();
    dlgOverlayModes=new OverlayModes();
    this->H_Start_Slider->hide();
    this->H_start_spinBox->hide();
    this->V_Start_Slider->hide();
    this->V_start_spinBox->hide();
    this->label_45->hide();
    this->label_46->hide();
    signal_connect_slot();
    slider_instaneventfiliter();
}

VideoAdjustment::~VideoAdjustment()
{
    //delete ui;
}

int VideoAdjustment::doubleToInt(double d)
{
    double intPart = floor(d);
    if ((d - intPart) >= (double)0.5)
    {
        return (intPart + 1);
    }
    else
    {
        return intPart;
    }
}

bool VideoAdjustment::eventFilter(QObject *obj, QEvent *event)
{
    int dur,pos;
    double dbPos;

    if(obj==this->Brightness_Slider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =this->Brightness_Slider->maximum() - this->Brightness_Slider->minimum();
                pos = this->Brightness_Slider->minimum() + dur * ((double)mouseEvent->x() / this->Brightness_Slider->width());
                if(pos != this->Brightness_Slider->sliderPosition())
                {
                    this->Brightness_Slider->setValue(pos);
                }
            }
        }
    }else if(obj==this->Contrast_Slider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =this->Contrast_Slider->maximum() - this->Contrast_Slider->minimum();
                pos = this->Contrast_Slider->minimum() + dur * ((double)mouseEvent->x() / this->Contrast_Slider->width());
                if(pos != this->Contrast_Slider->sliderPosition())
                {
                    this->Contrast_Slider->setValue(pos);
                }
            }
        }
    }else if(obj==this->Color_Slider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =this->Color_Slider->maximum() - this->Color_Slider->minimum();
                pos = this->Color_Slider->minimum() + dur * ((double)mouseEvent->x() / this->Color_Slider->width());
                if(pos != this->Color_Slider->sliderPosition())
                {
                    this->Color_Slider->setValue(pos);
                }
            }
        }
    }else if(obj==this->Hue_Slider)
    {
        if(this->Hue_Slider->isEnabled())
        {
            if (event->type()==QEvent::MouseButtonRelease)           //判断类型
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton)	//判断左键
                {
                    dur =this->Hue_Slider->maximum() - this->Hue_Slider->minimum();
                    pos = this->Hue_Slider->minimum() + dur * ((double)mouseEvent->x() / this->Hue_Slider->width());
                    if(pos != this->Hue_Slider->sliderPosition())
                    {
                        this->Hue_Slider->setValue(pos);
                    }
                }
            }
        }
    }else if(obj==this->Sharpness_Slider)
    {
        if (event->type()==QEvent::MouseButtonRelease)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                dur =this->Sharpness_Slider->maximum() - this->Sharpness_Slider->minimum();
                pos = this->Sharpness_Slider->minimum() + dur * ((double)mouseEvent->x() / this->Sharpness_Slider->width());
                if(pos != this->Sharpness_Slider->sliderPosition())
                {
                     this->Sharpness_Slider->setValue(pos);
                }
            }
        }
    }else if(obj==this->Noise_Slider)
    {
        if(this->Noise_Slider->isEnabled())
        {
            if (event->type()==QEvent::MouseButtonRelease)           //判断类型
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton)	//判断左键
                {
                    dur =this->Noise_Slider->maximum() - this->Noise_Slider->minimum();
                    pos = this->Noise_Slider->minimum() + dur * ((double)mouseEvent->x() / this->Noise_Slider->width());
                    if(pos != this->Noise_Slider->sliderPosition())
                    {
                        this->Noise_Slider->setValue(pos);
                    }
                }
            }
        }
    }else if(obj==this->Phase_Slider)
    {
        if(this->Phase_Slider->isEnabled())
        {
            if (event->type()==QEvent::MouseButtonRelease)           //判断类型
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton)	//判断左键
                {
                    dur =this->Phase_Slider->maximum() - this->Phase_Slider->minimum();
                    pos = this->Phase_Slider->minimum() + dur * ((double)mouseEvent->x() / this->Phase_Slider->width());
                    if(pos != this->Phase_Slider->sliderPosition())
                    {
                        this->Phase_Slider->setValue(pos);
                    }
                }
            }
        }
    }else if(obj==this->Frequency_Slider)
    {
        if(this->Frequency_Slider->isEnabled())
        {
            if (event->type()==QEvent::MouseButtonRelease)           //判断类型
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton)	//判断左键
                {
                    dur =this->Frequency_Slider->maximum() - this->Frequency_Slider->minimum();
                    pos = this->Frequency_Slider->minimum() + dur * ((double)mouseEvent->x() / this->Frequency_Slider->width());
                    if(pos != this->Frequency_Slider->sliderPosition())
                    {
                        this->Frequency_Slider->setValue(pos);
                    }
                }
            }
        }
    }else if(obj==this->Clampwidth_Slider)
    {
        if(this->Clampwidth_Slider->isEnabled())
        {
            if (event->type()==QEvent::MouseButtonRelease)           //判断类型
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton)	//判断左键
                {
                    dur =this->Clampwidth_Slider->maximum() - this->Clampwidth_Slider->minimum();
                    pos = this->Clampwidth_Slider->minimum() + dur * ((double)mouseEvent->x() / this->Clampwidth_Slider->width());
                    if(pos != this->Clampwidth_Slider->sliderPosition())
                    {
                        this->Clampwidth_Slider->setValue(pos);
                    }
                }
            }
        }
    }else if(obj==this->Bandwidth_Slider)
    {
        if(this->Bandwidth_Slider->isEnabled())
        {
            if (event->type()==QEvent::MouseButtonRelease)           //判断类型
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton)	//判断左键
                {
                    dur =this->Bandwidth_Slider->maximum() - this->Bandwidth_Slider->minimum();
                    pos = this->Bandwidth_Slider->minimum() + dur * ((double)mouseEvent->x() / this->Bandwidth_Slider->width());
                    if(pos != this->Bandwidth_Slider->sliderPosition())
                    {
                        this->Bandwidth_Slider->setValue(pos);
                    }
                }
            }
        }
    }else if(obj==this->Red_Slider)
    {
        if(this->Color_RGB_RadioButton->isChecked())
        {
            if (event->type()==QEvent::MouseButtonRelease)           //判断类型
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton)	//判断左键
                {
                    dur =this->Red_Slider->maximum() - this->Red_Slider->minimum();
                    pos = this->Red_Slider->minimum() + dur * ((double)mouseEvent->x() / this->Red_Slider->width());
                    if(pos != this->Red_Slider->sliderPosition())
                    {
                        this->Red_Slider->setValue(pos);
                    }
                }
            }
        }
    }else if(obj==this->Green_Slider)
    {
        if(this->Color_RGB_RadioButton->isChecked())
        {
            if (event->type()==QEvent::MouseButtonRelease)           //判断类型
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton)	//判断左键
                {
                    dur =this->Green_Slider->maximum() - this->Green_Slider->minimum();
                    pos = this->Green_Slider->minimum() + dur * ((double)mouseEvent->x() / this->Green_Slider->width());
                    if(pos != this->Green_Slider->sliderPosition())
                    {
                        this->Green_Slider->setValue(pos);
                    }
                }
            }
        }
    }else if(obj==this->Blue_Slider)
    {
        if(this->Color_RGB_RadioButton->isChecked())
        {
            if (event->type()==QEvent::MouseButtonRelease)           //判断类型
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton)	//判断左键
                {
                    dur =this->Blue_Slider->maximum() - this->Blue_Slider->minimum();
                    pos = this->Blue_Slider->minimum() + dur * ((double)mouseEvent->x() / this->Blue_Slider->width());
                    if(pos != this->Blue_Slider->sliderPosition())
                    {
                        this->Blue_Slider->setValue(pos);
                    }
                }
            }
        }
    }else if(obj==this->Zoom_Slider)
    {
        if(this->Scaling_Adjust_RadioButton->isChecked())
        {
            if (event->type()==QEvent::MouseButtonRelease)           //判断类型
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton)	//判断左键
                {
                    dur =this->Zoom_Slider->maximum() - this->Zoom_Slider->minimum();
                    pos = this->Zoom_Slider->minimum() + dur * ((double)mouseEvent->x() / this->Zoom_Slider->width());
                    if(pos != this->Zoom_Slider->sliderPosition())
                    {
                        this->Zoom_Slider->setValue(pos);
                    }
                }
            }
        }
    }else if(obj==this->H_Scaling_Slider)
    {
        if(this->Scaling_Adjust_RadioButton->isChecked())
        {
            if (event->type()==QEvent::MouseButtonRelease)           //判断类型
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton)	//判断左键
                {
                    dur =this->H_Scaling_Slider->maximum() - this->H_Scaling_Slider->minimum();
                    pos = this->H_Scaling_Slider->minimum() + dur * ((double)mouseEvent->x() / this->H_Scaling_Slider->width());
                    if(pos != this->H_Scaling_Slider->sliderPosition())
                    {
                        this->H_Scaling_Slider->setValue(pos);
                    }
                }
            }
        }
    }else if(obj==this->ColorTemp_Slider)
    {
        if(this->Color_Temp_RadioButton->isChecked())
        {
            if (event->type()==QEvent::MouseButtonRelease)           //判断类型
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton)	//判断左键
                {
                    dur =this->ColorTemp_Slider->maximum() - this->ColorTemp_Slider->minimum();
                    dbPos = this->ColorTemp_Slider->minimum() + dur * ((double)mouseEvent->x() / this->ColorTemp_Slider->width());
                    if(dbPos != this->ColorTemp_Slider->sliderPosition())
                    {
                        pos=dbPos+0.5;
                        this->ColorTemp_Slider->setValue(pos);
                    }
                }
            }
        }
    }else if(obj==this->H_Start_Slider)
    {
        if(this->H_Start_Slider->isEnabled())
        {
            if (event->type()==QEvent::MouseButtonRelease)           //判断类型
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton)	//判断左键
                {
                    dur =this->H_Start_Slider->maximum() - this->H_Start_Slider->minimum();
                    pos = this->H_Start_Slider->minimum() + dur * ((double)mouseEvent->x() / this->H_Start_Slider->width());
                    if(pos != this->H_Start_Slider->sliderPosition())
                    {
                        this->H_Start_Slider->setValue(pos);
                    }
                }
            }
        }
    }else if(obj==this->V_Start_Slider)
    {
        if(this->V_Start_Slider->isEnabled())
        {
            if (event->type()==QEvent::MouseButtonRelease)           //判断类型
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

                if (mouseEvent->button() == Qt::LeftButton)	//判断左键
                {
                    dur =this->V_Start_Slider->maximum() - this->V_Start_Slider->minimum();
                    pos = this->V_Start_Slider->minimum() + dur * ((double)mouseEvent->x() / this->V_Start_Slider->width());
                    if(pos != this->V_Start_Slider->sliderPosition())
                    {
                        this->V_Start_Slider->setValue(pos);
                    }
                }
            }
        }
    }
    mouse_no_work_time=QTime::currentTime();
    return QObject::eventFilter(obj,event);
}

void VideoAdjustment::EnableControlCursor()
{
    this->Dither_CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->DP_Adjust_Button->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Brightness_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Brightness_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Contrast_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Contrast_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Color_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Color_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Hue_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Hue_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Sharpness_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Sharpness_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Noise_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Noise_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Phase_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Phase_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Frequency_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Frequency_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Clampwidth_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Clampwidth_doubleSpinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Bandwidth_Auto_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Bandwidth_Manual_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Bandwidth_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Bandwidth_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Color_Native_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Color_RGB_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Color_Temp_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Red_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Red_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Green_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Green_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Blue_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Blue_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    //this->ColorTemp_comboBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->ColorTemp_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->ColorTemp_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Display_Native_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Display_DICOM_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Display_Gamma_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Gamma_comboBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Scaling_Native_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Scaling_Full_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Scaling_Best_Fit_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Scaling_Adjust_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Scaling_FourToThree_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Automatic_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Zoom_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Zoom_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Auto_Button_1->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Auto_Button_2->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Auto_Button_3->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Auto_Button_4->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Restore_Curr_Preset_Button->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Next_Preset_Button->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Save_Preset_Button->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->Restore_Default_Preset_Button->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->H_Scaling_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->H_Scaling_doubleSpinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    this->H_Start_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->H_start_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->V_Start_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->V_start_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    this->OverlayModesButton->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    //dp_adjustment->Lane_Num_comboBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    dp_adjustment->Voltage_Level_checkBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    dp_adjustment->Voltage_Level_checkBox_2->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    dp_adjustment->Voltage_Level_checkBox_3->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    dp_adjustment->Voltage_Level_checkBox_4->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    dp_adjustment->Emphasis_Level_checkBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    dp_adjustment->Emphasis_Level_checkBox_2->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    dp_adjustment->Emphasis_Level_checkBox_3->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    dp_adjustment->Emphasis_Level_checkBox_4->setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

void VideoAdjustment::DisableControlCursor()
{
    this->Dither_CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->DP_Adjust_Button->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Brightness_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Brightness_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Contrast_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Contrast_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Color_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Color_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Hue_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Hue_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Sharpness_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Sharpness_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Noise_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Noise_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Phase_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Phase_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Frequency_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Frequency_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Clampwidth_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Clampwidth_doubleSpinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Bandwidth_Auto_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Bandwidth_Manual_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Bandwidth_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Bandwidth_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Color_Native_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Color_RGB_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Color_Temp_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Red_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Red_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Green_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Green_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Blue_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Blue_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->ColorTemp_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->ColorTemp_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Display_Native_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Display_DICOM_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Display_Gamma_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Gamma_comboBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Scaling_Native_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Scaling_Full_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Scaling_Best_Fit_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Scaling_Adjust_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Scaling_FourToThree_RadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Automatic_radioButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Zoom_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Zoom_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Auto_Button_1->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Auto_Button_2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Auto_Button_3->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Auto_Button_4->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Restore_Curr_Preset_Button->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Next_Preset_Button->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Save_Preset_Button->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->Restore_Default_Preset_Button->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->H_Scaling_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->H_Scaling_doubleSpinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    this->H_Start_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->H_start_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->V_Start_Slider->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->V_start_spinBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    this->OverlayModesButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    //dp_adjustment->Lane_Num_comboBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    dp_adjustment->Voltage_Level_checkBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    dp_adjustment->Voltage_Level_checkBox_2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    dp_adjustment->Voltage_Level_checkBox_3->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    dp_adjustment->Voltage_Level_checkBox_4->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    dp_adjustment->Emphasis_Level_checkBox->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    dp_adjustment->Emphasis_Level_checkBox_2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    dp_adjustment->Emphasis_Level_checkBox_3->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    dp_adjustment->Emphasis_Level_checkBox_4->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

bool VideoAdjustment::isAnalogSignal(int nSigId)
{
    bool bl_isAnalogSignal;
    switch (nSigId) {
    case eVIDSIGIN_DVI_A1:
    case eVIDSIGIN_DVI_A2:
    case eVIDSIGIN_S_VIDEO1:
    case eVIDSIGIN_S_VIDEO2:
    case eVIDSIGIN_CVBS:
    case eVIDSIGIN_SDI1:
    case eVIDSIGIN_SDI2:
        bl_isAnalogSignal=true;
        break;
    case eVIDSIGIN_DVI_D3:
    case eVIDSIGIN_DP2:
    case eVIDSIGIN_DVI_D1:
    case eVIDSIGIN_DVI_D2:
    case eVIDSIGIN_HDMI1:
    case eVIDSIGIN_HDMI2:
    case eVIDSIGIN_DP1:
        bl_isAnalogSignal=false;
        break;
    }

    return bl_isAnalogSignal;
}

void VideoAdjustment::slider_instaneventfiliter()
{
    this->Brightness_Slider->installEventFilter(this);
    this->Contrast_Slider->installEventFilter(this);
    this->Color_Slider->installEventFilter(this);
    this->Hue_Slider->installEventFilter(this);
    this->Sharpness_Slider->installEventFilter(this);
    this->Noise_Slider->installEventFilter(this);
    this->Phase_Slider->installEventFilter(this);
    this->Frequency_Slider->installEventFilter(this);
    this->Clampwidth_Slider->installEventFilter(this);
    this->Bandwidth_Slider->installEventFilter(this);
    this->Red_Slider->installEventFilter(this);
    this->Green_Slider->installEventFilter(this);
    this->Blue_Slider->installEventFilter(this);
    this->Zoom_Slider->installEventFilter(this);
    this->ColorTemp_Slider->installEventFilter(this);
    this->H_Scaling_Slider->installEventFilter(this);
    this->H_Start_Slider->installEventFilter(this);
    this->V_Start_Slider->installEventFilter(this);
}

void VideoAdjustment::signal_connect_slot()
{
    connect(this->Brightness_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->Contrast_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->Color_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->Hue_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->Sharpness_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->Noise_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->Phase_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->Frequency_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->Clampwidth_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->Bandwidth_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->Red_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->Green_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->Blue_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->Zoom_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->ColorTemp_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->H_Scaling_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->H_Start_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));
    connect(this->V_Start_Slider,SIGNAL(valueChanged(int)),this,SLOT(Slider_Value_Changed(int)));



    connect(this->Brightness_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->Contrast_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->Color_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->Hue_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->Sharpness_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->Noise_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->Phase_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->Frequency_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->Bandwidth_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->Red_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->Green_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->Blue_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->Zoom_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->ColorTemp_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->H_start_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));
    connect(this->V_start_spinBox,SIGNAL(valueChanged(int)),this,SLOT(spinBox_Valie_changed(int)));

    connect(this->Clampwidth_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(Double_spinBox_Valie_changed(double)));
    connect(this->H_Scaling_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(Double_spinBox_Valie_changed(double)));

    connect(this->Dither_CheckBox,SIGNAL(clicked()),this,SLOT(CheckBox_StateChanged()));

    connect(this->Bandwidth_Auto_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(this->Bandwidth_Manual_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(this->Color_Native_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(this->Color_RGB_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(this->Color_Temp_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(this->Display_Native_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(this->Display_DICOM_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(this->Display_Gamma_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(this->Scaling_Native_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(this->Scaling_Best_Fit_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(this->Scaling_Full_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(this->Scaling_Adjust_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(this->Scaling_FourToThree_RadioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));
    connect(this->Automatic_radioButton,SIGNAL(clicked(bool)),this,SLOT(RadioButton_Clicked()));

    //connect(this->ColorTemp_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(ComboBox_currentIndexChanged(int)));
    connect(this->Gamma_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(ComboBox_currentIndexChanged(int)));

    connect(this->Auto_Button_1,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));
    connect(this->Auto_Button_2,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));
    connect(this->Auto_Button_3,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));
    connect(this->Auto_Button_4,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));
    connect(this->Restore_Curr_Preset_Button,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));
    connect(this->Next_Preset_Button,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));
    connect(this->Save_Preset_Button,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));
    connect(this->Restore_Default_Preset_Button,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));
    connect(this->DP_Adjust_Button,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));
    connect(this->OverlayModesButton,SIGNAL(clicked(bool)),this,SLOT(pushButton_Clicked()));

    connect(this->toolButton,SIGNAL(clicked(bool)),this,SLOT(ToolButton_Clicked()));
}

void VideoAdjustment::SetBrightnessSliderValue(stVALUE_INFO stValue)
{
    if(stValue.value==this->Brightness_Slider->value())
        this->read_Brightness=false;
    else
         this->read_Brightness=true;
    this->Brightness_Slider->setValue(stValue.value);
}

void VideoAdjustment::SetContrastSliderValue(stVALUE_INFO stValue)
{
    if(stValue.value==this->Contrast_Slider->value())
        this->read_Contrast=false;
    else
        this->read_Contrast=true;
    this->Contrast_Slider->setValue(stValue.value);
}

void VideoAdjustment::SetColorSliderValue(stVALUE_INFO stValue)
{
    if(stValue.value==this->Color_Slider->value())
        this->read_Color=false;
    else
        this->read_Color=true;
    this->Color_Slider->setValue(stValue.value);
}

void VideoAdjustment::SetHueSliderValue(stVALUE_INFO stValue)
{
    if(stValue.value==this->Hue_Slider->value())
        this->read_Hue=false;
    else
        this->read_Hue=true;
    this->Hue_Slider->setValue(stValue.value);
}

void VideoAdjustment::SetSharpnessSliderValue(stVALUE_INFO stValue)
{
    if(stValue.value==this->Sharpness_Slider->value())
        this->read_Sharpness=false;
    else
        this->read_Sharpness=true;
    this->Sharpness_Slider->setValue(stValue.value);
}

void VideoAdjustment::SetNoiseSliderValue(stVALUE_INFO stValue)
{
    if(stValue.value==this->Noise_Slider->value())
        this->read_Noise=false;
    else
        this->read_Noise=true;
    this->Noise_Slider->setValue(stValue.value);
}

void VideoAdjustment::SetPhaseSliderValue(stVALUE_INFO stValue)
{
    if(stValue.value==this->Phase_Slider->value())
        this->read_Phase=false;
    else
        this->read_Phase=true;
    this->Phase_Slider->setValue(stValue.value);
}

void VideoAdjustment::SetClampwidthSliderValue(stVALUE_INFO stValue)
{
    if(stValue.value==this->Clampwidth_Slider->value())
        this->read_Clampwidth=false;
    else
        this->read_Clampwidth=true;
    this->Clampwidth_Slider->setValue(stValue.value);

}

void VideoAdjustment::SetVFrequencyLabelValue(stVALUE_INFO stValue)
{
    QString str=QString("Vertical Frequency:%1").arg(stValue.value);
    this->VFrequency_Label->setText(str);
}

void VideoAdjustment::SetHFrequencyLabelValue(stVALUE_INFO stValue)
{
    QString str=QString("Horizontal Frequency:%1").arg(stValue.value);
    this->HFrequency_Label->setText(str);
}

void VideoAdjustment::SetGammaControlValue(stVALUE_INFO stValue)
{
    if(stValue.value==DISP_GAMMA_NATIVE)
    {
        this->Display_Native_RadioButton->setChecked(true);
        this->Gamma_comboBox->setDisabled(true);
        if(this->Gamma_comboBox->currentIndex()!=14)
            this->read_gamma=true;
        this->Gamma_comboBox->setCurrentIndex(14);
    }/*else if(stValue.value==DISP_GAMMA_DICOM)
    {
        this->Display_DICOM_RadioButton->setChecked(true);
        this->Gamma_comboBox->setDisabled(true);
    }*/
    else {
        if(stValue.value!=this->Gamma_comboBox->currentIndex()+1)
            this->read_gamma=true;
        this->Display_Gamma_RadioButton->setChecked(true);
        this->Gamma_comboBox->setEnabled(true);
        this->Gamma_comboBox->setCurrentIndex(stValue.value-1);
    }
}

void VideoAdjustment::SetBandwidthControlValue(stVALUE_INFO stValue)
{
    if(stValue.value==-1)
    {
        this->Bandwidth_Auto_RadioButton->setChecked(true);
        this->Bandwidth_Slider->setEnabled(false);
        this->Bandwidth_spinBox->setEnabled(false);
        this->label_35->setEnabled(false);
    }
    else {
        this->Bandwidth_Manual_RadioButton->setChecked(true);
        this->Bandwidth_Slider->setEnabled(true);
        this->Bandwidth_spinBox->setEnabled(true);
        this->label_35->setEnabled(true);
        if(stValue.value!=this->Bandwidth_Slider->value())
            this->read_Bandwidth=true;
        this->Bandwidth_Slider->setValue(stValue.value);
    }
}

void VideoAdjustment::SetFmtPNControlValue(stVALUE_INFO stValue)
{
    if(stValue.value==1)
    {
        this->label_29->setEnabled(true);
        this->Hue_Slider->setEnabled(true);
        this->Hue_spinBox->setEnabled(true);
    }else {
        this->label_29->setEnabled(false);
        this->Hue_Slider->setEnabled(false);
        this->Hue_spinBox->setEnabled(false);
    }
}

void VideoAdjustment::SetControlIsEnable(int SigInId,bool blIsValid)
{
    if(SigInId==eVIDSIGIN_CVBS || SigInId==eVIDSIGIN_S_VIDEO1 || SigInId==eVIDSIGIN_S_VIDEO2
      || SigInId==eVIDSIGIN_DVI_A1 || SigInId==eVIDSIGIN_DVI_A2)
    {
        this->label_35->setEnabled(true);
        this->Bandwidth_Auto_RadioButton->setEnabled(true);
        this->Bandwidth_Manual_RadioButton->setEnabled(true);
        this->Bandwidth_Slider->setEnabled(true);
        this->Bandwidth_spinBox->setEnabled(true);
        this->OverlayModesButton->setEnabled(true);
        this->Automatic_radioButton->setEnabled(true);
        this->H_Start_Slider->setEnabled(true);
        this->H_start_spinBox->setEnabled(true);
        this->label_45->setEnabled(true);
        this->V_Start_Slider->setEnabled(true);
        this->V_start_spinBox->setEnabled(true);
        this->label_46->setEnabled(true);
        if(SigInId==eVIDSIGIN_DVI_A1 || SigInId==eVIDSIGIN_DVI_A2)
        {
            this->label_32->setEnabled(true);
            this->Phase_Slider->setEnabled(true);
            this->Phase_spinBox->setEnabled(true);
            this->label_33->setEnabled(true);
            this->Frequency_Slider->setEnabled(true);
            this->Frequency_spinBox->setEnabled(true);
            this->Auto_Button_1->setEnabled(true);
            this->Auto_Button_2->setEnabled(true);
            this->Auto_Button_3->setEnabled(true);
            this->Auto_Button_4->setEnabled(true);
            this->label_31->setEnabled(false);
            this->Noise_Slider->setEnabled(false);
            this->Noise_spinBox->setEnabled(false);
//            this->label_29->setEnabled(false);
//            this->Hue_Slider->setEnabled(false);
//            this->Hue_spinBox->setEnabled(false);
            this->label_34->setEnabled(true);
            this->Clampwidth_Slider->setEnabled(true);
            this->Clampwidth_doubleSpinBox->setEnabled(true);
        }
        else
        {
            this->label_31->setEnabled(true);
            this->Noise_Slider->setEnabled(true);
            this->Noise_spinBox->setEnabled(true);
            this->label_32->setEnabled(false);
            this->Phase_Slider->setEnabled(false);
            this->Phase_spinBox->setEnabled(false);
            this->label_33->setEnabled(false);
            this->Frequency_Slider->setEnabled(false);
            this->Frequency_spinBox->setEnabled(false);
            this->Auto_Button_1->setEnabled(false);
            this->Auto_Button_2->setEnabled(false);
            this->Auto_Button_3->setEnabled(false);
            this->Auto_Button_4->setEnabled(false);
            this->label_34->setEnabled(false);
            this->Clampwidth_Slider->setEnabled(false);
            this->Clampwidth_doubleSpinBox->setEnabled(false);
            //ubus_interface->VidSigIn_GetFmtPN(ui->Input_Ref_ComboBox->currentIndex()+1);
        }

    }
    else
    {
        this->H_Start_Slider->setEnabled(false);
        this->H_start_spinBox->setEnabled(false);
        this->label_45->setEnabled(false);
        this->V_Start_Slider->setEnabled(false);
        this->V_start_spinBox->setEnabled(false);
        this->label_46->setEnabled(false);
        this->OverlayModesButton->setEnabled(false);
        this->Automatic_radioButton->setEnabled(false);
        this->label_34->setEnabled(false);
        this->Clampwidth_Slider->setEnabled(false);
        this->Clampwidth_doubleSpinBox->setEnabled(false);
        this->label_35->setEnabled(false);
        this->Bandwidth_Auto_RadioButton->setEnabled(false);
        this->Bandwidth_Manual_RadioButton->setEnabled(false);
        this->Bandwidth_Slider->setEnabled(false);
        this->Bandwidth_spinBox->setEnabled(false);
        this->label_31->setEnabled(false);
        this->Noise_Slider->setEnabled(false);
        this->Noise_spinBox->setEnabled(false);
        this->label_32->setEnabled(false);
        this->Phase_Slider->setEnabled(false);
        this->Phase_spinBox->setEnabled(false);
        this->label_33->setEnabled(false);
        this->Frequency_Slider->setEnabled(false);
        this->Frequency_spinBox->setEnabled(false);
        this->Auto_Button_1->setEnabled(false);
        this->Auto_Button_2->setEnabled(false);
        this->Auto_Button_3->setEnabled(false);
        this->Auto_Button_4->setEnabled(false);
//        this->label_29->setEnabled(false);
//        this->Hue_Slider->setEnabled(false);
//        this->Hue_spinBox->setEnabled(false);
    }

//    if(isAnalogSignal(SigInId))
//    {
//        this->Color_Slider->setEnabled(true);
//        this->Color_spinBox->setEnabled(true);
//        this->label_28->setEnabled(true);
//    }else
//    {
//        this->Color_Slider->setEnabled(false);
//        this->Color_spinBox->setEnabled(false);
//        this->label_28->setEnabled(false);
//    }

    if(SigInId==eVIDSIGIN_DP1 || SigInId==eVIDSIGIN_DP2 || SigInId==eVIDSIGIN_DP3)
        this->DP_Adjust_Button->setEnabled(true);
    else
        this->DP_Adjust_Button->setEnabled(false);

//    if(!blIsValid)
//    {
//        this->OverlayModesButton->setEnabled(false);
//        this->NewModesButton->setEnabled(false);
//        this->ClearModesButton->setEnabled(false);
//    }
}

void VideoAdjustment::SetInformationControlInfo(stVIDSIGIN_STATUS VidSigInStatus,QString SigInName)
{
    QString str;
    if(VidSigInStatus.bIsValid==1)
    {
        str=SigInName;
        this->Input_Label->setText(str);
        if(VidSigInStatus.bIsInterLace==1)
            str=QString("Resolution: %1 x %2i").arg(VidSigInStatus.uiFrameHActive).arg(VidSigInStatus.uiFrameVActive*2);
        else
            str=QString("Resolution: %1 x %2").arg(VidSigInStatus.uiFrameHActive).arg(VidSigInStatus.uiFrameVActive);
        this->Resolution_Label->setText(str);
        str.clear();
        str=QString("Vertical Frequency: %1.%2 Hz").arg(VidSigInStatus.uiFrameVFreqP10/10).arg(VidSigInStatus.uiFrameVFreqP10%10);
        this->VFrequency_Label->setText(str);
        str.clear();
        str=QString("Horizontal Frequency: %1.%2 KHz").arg(VidSigInStatus.uiFrameHFreqP10K/10).arg(VidSigInStatus.uiFrameHFreqP10K%10);
        this->HFrequency_Label->setText(str);
        str.clear();
        str=QString("Pixel Clock: %1.%2 MHz").arg(VidSigInStatus.uiPixelClkP10M/10).arg(VidSigInStatus.uiPixelClkP10M%10);
        this->Pixel_Clock_label->setText(str);
        str.clear();
    }else
    {
        str=SigInName;
        this->Input_Label->setText(str);
        str.clear();
        str=QString("Resolution: %1 x %2").arg(0).arg(0);
        this->Resolution_Label->setText(str);
        str.clear();
        str=QString("Vertical Frequency: %1.%2 Hz").arg(0).arg(0);
        this->VFrequency_Label->setText(str);
        str.clear();
        str=QString("Horizontal Frequency: %1.%2 KHz").arg(0).arg(0);
        this->HFrequency_Label->setText(str);
        str.clear();
        str=QString("Pixel Clock: %1.%2 MHz").arg(0).arg(0);
        this->Pixel_Clock_label->setText(str);

        if(this->Dither_CheckBox->isChecked())
            this->read_Dither=true;
        else
            this->read_Dither=false;
        this->Dither_CheckBox->setChecked(false);

        if(this->Brightness_Slider->value()==0)
            this->read_Brightness=false;
        else
            this->read_Brightness=true;
        this->Brightness_Slider->setValue(0);

        if(this->Contrast_Slider->value()==0)
            this->read_Contrast=false;
        else
            this->read_Contrast=true;
        this->Contrast_Slider->setValue(0);

        if(this->Color_Slider->value()==0)
            this->read_Color=false;
        else
            this->read_Color=true;
        this->Color_Slider->setValue(0);

        if(this->Hue_Slider->value()==0)
            this->read_Hue=false;
        else
            this->read_Hue=true;
        this->Hue_Slider->setValue(0);

        if(this->Sharpness_Slider->value()==0)
            this->read_Sharpness=false;
        else
            this->read_Sharpness=true;
        this->Sharpness_Slider->setValue(0);

        if(this->Noise_Slider->value()==0)
            this->read_Noise=false;
        else
            this->read_Noise=true;
        this->Noise_Slider->setValue(0);

        if(this->Phase_Slider->value()==0)
            this->read_Phase=false;
        else
            this->read_Phase=true;
        this->Phase_Slider->setValue(0);

        if(this->H_Start_Slider->value()==0)
            this->read_HStart=false;
        else
            this->read_HStart=true;
        this->H_Start_Slider->setValue(0);

        if(this->V_Start_Slider->value()==0)
            this->read_VStart=false;
        else
            this->read_VStart=true;
        this->V_Start_Slider->setValue(0);

        if(this->Frequency_Slider->value()==0)
            this->read_Frequency=false;
        else
            this->read_Frequency=true;
        this->Frequency_Slider->setValue(0);

        if(this->Bandwidth_Slider->value()==0)
            this->read_Bandwidth=false;
        else
            this->read_Bandwidth=true;
        this->Bandwidth_Slider->setValue(0);
        this->Bandwidth_Auto_RadioButton->setChecked(false);
        this->Bandwidth_Manual_RadioButton->setChecked(false);

        this->Color_Native_RadioButton->setChecked(false);
        this->Color_RGB_RadioButton->setChecked(false);
        this->Color_Temp_RadioButton->setChecked(false);
        //Video_Adjust->ColorTemp_comboBox->setEnabled(false);

        if(this->Red_Slider->value()==0)
            this->read_ColorTemp_R=false;
        else
            this->read_ColorTemp_R=true;
        this->Red_Slider->setValue(0);
        this->Red_Slider->setEnabled(false);

        if(this->Green_Slider->value()==0)
            this->read_ColorTemp_G=false;
        else
            this->read_ColorTemp_G=true;
        this->Green_Slider->setValue(0);
        this->Green_Slider->setEnabled(false);

        if(this->Blue_Slider->value()==0)
            this->read_ColorTemp_B=false;
        else
            this->read_ColorTemp_B=true;
        this->Blue_Slider->setValue(0);
        this->Blue_Slider->setEnabled(false);

        this->Display_Native_RadioButton->setChecked(false);
        this->Display_DICOM_RadioButton->setChecked(false);
        this->Display_Gamma_RadioButton->setChecked(false);
        this->Gamma_comboBox->setEnabled(false);
    }
}

void VideoAdjustment::SetHStartSliderValue(stHVStart stValue,int nMinVale,int nMaxValue)
{
    if(stValue.HVStartValue != this->H_Start_Slider->value())
        this->read_HStart=true;
    if((nMinVale!=this->H_Start_Slider->minimum()) ||(nMaxValue!=this->H_Start_Slider->maximum()))
        this->read_HStart=true;

    this->H_start_spinBox->setMinimum(nMinVale);
    this->H_start_spinBox->setMaximum(nMaxValue);
    this->H_Start_Slider->setMinimum(nMinVale);
    this->H_Start_Slider->setMaximum(nMaxValue);
    QThread::msleep( 200 );
    this->H_Start_Slider->setValue(stValue.HVStartValue);
}

void VideoAdjustment::SetVStartSliderValue(stHVStart stValue,int nMinVale,int nMaxValue)
{  
    if(stValue.HVStartValue != this->V_Start_Slider->value())
        this->read_VStart=true;
    if((nMinVale!=this->V_Start_Slider->minimum()) ||(nMaxValue!=this->V_Start_Slider->maximum()))
        this->read_VStart=true;

    this->V_start_spinBox->setMinimum(nMinVale);
    this->V_start_spinBox->setMaximum(nMaxValue);
    this->V_Start_Slider->setMinimum(nMinVale);
    this->V_Start_Slider->setMaximum(nMaxValue);
    QThread::msleep( 200 );
    this->V_Start_Slider->setValue(stValue.HVStartValue);
}

void VideoAdjustment::SetAutomaticValue(int val)
{
    if(val==0)
        this->Automatic_radioButton->setChecked(true);


    if(val==1)
        this->Automatic_radioButton->setChecked(false);
}

void VideoAdjustment::SetFrequencySliderValue(gtFrequency_INFO gtFrequency)
{
    if(gtFrequency.currtvalue != this->Frequency_Slider->value())
        this->read_Frequency=true;
    if((gtFrequency.minvlaue!=this->Frequency_Slider->minimum()) ||(gtFrequency.maxvlaue!=this->Frequency_Slider->maximum()))
        this->read_Frequency_Scope=true;

    this->label_33->setEnabled(true);
    this->Frequency_Slider->setEnabled(true);
    this->Frequency_spinBox->setEnabled(true);
    this->Frequency_Slider->setMinimum(gtFrequency.minvlaue);
    this->Frequency_Slider->setMaximum(gtFrequency.maxvlaue);
    this->Frequency_spinBox->setMinimum(gtFrequency.minvlaue);
    this->Frequency_spinBox->setMaximum(gtFrequency.maxvlaue);
    QThread::msleep( 200 );
    this->Frequency_Slider->setValue(gtFrequency.currtvalue);
}

void VideoAdjustment::SetColorTempControlValue(stDISP_COLORTEMP stColorTemp)
{
    if(stColorTemp.uiCTempVal==DISP_CTEMP_NATIVE)
   {
        this->Color_Native_RadioButton->setEnabled(true);
        this->Color_RGB_RadioButton->setEnabled(true);
        this->Color_Temp_RadioButton->setEnabled(true);
        this->Color_Native_RadioButton->setChecked(true);
//        Video_Adjust->ColorTemp_comboBox->setDisabled(true);
        this->ColorTemp_Slider->setDisabled(true);
        this->ColorTemp_spinBox->setDisabled(true);
        this->Red_Slider->setDisabled(true);
        this->Red_spinBox->setDisabled(true);
        this->Green_Slider->setDisabled(true);
        this->Green_spinBox->setDisabled(true);
        this->Blue_Slider->setDisabled(true);
        this->Blue_spinBox->setDisabled(true);
        this->Red_Slider->setValue(stColorTemp.uiCTR);
        this->Red_spinBox->setValue(stColorTemp.uiCTR);
        this->Green_Slider->setValue(stColorTemp.uiCTG);
        this->Green_spinBox->setValue(stColorTemp.uiCTG);
        this->Blue_Slider->setValue(stColorTemp.uiCTB);
        this->Blue_spinBox->setValue(stColorTemp.uiCTB);
   }
    else if(stColorTemp.uiCTempVal==DISP_CTEMP_RGB)
   {
        this->Color_Native_RadioButton->setEnabled(true);
        this->Color_RGB_RadioButton->setEnabled(true);
        this->Color_Temp_RadioButton->setEnabled(true);
        if(stColorTemp.uiCTR==this->Red_Slider->value())
            this->read_ColorTemp_R=false;
        else
            this->read_ColorTemp_R=true;

        if(stColorTemp.uiCTG==this->Green_Slider->value())
            this->read_ColorTemp_G=false;
        else
            this->read_ColorTemp_G=true;

        if(stColorTemp.uiCTB==this->Blue_Slider->value())
            this->read_ColorTemp_B=false;
        else
            this->read_ColorTemp_B=true;

       this->Color_RGB_RadioButton->setChecked(true);
       this->Red_Slider->setValue(stColorTemp.uiCTR);
       this->Green_Slider->setValue(stColorTemp.uiCTG);
       this->Blue_Slider->setValue(stColorTemp.uiCTB);
//       Video_Adjust->ColorTemp_comboBox->setDisabled(true);
       this->ColorTemp_Slider->setDisabled(true);
       this->ColorTemp_spinBox->setDisabled(true);
       this->Red_Slider->setEnabled(true);
       this->Red_spinBox->setEnabled(true);
       this->Green_Slider->setEnabled(true);
       this->Green_spinBox->setEnabled(true);
       this->Blue_Slider->setEnabled(true);
       this->Blue_spinBox->setEnabled(true);
   }else
   {
        this->Color_Native_RadioButton->setEnabled(true);
        this->Color_RGB_RadioButton->setEnabled(true);
        this->Color_Temperature_Group->setEnabled(true);
        this->Color_Temp_RadioButton->setChecked(true);
        if(stColorTemp.uiCTempVal!=(this->ColorTemp_spinBox->value()/500-6))
            this->read_ColorTemp_Temp=true;
        //Video_Adjust->ColorTemp_comboBox->setEnabled(true);
        //Video_Adjust->ColorTemp_comboBox->setCurrentIndex(stColorTemp.uiCTempVal-2);
        this->ColorTemp_Slider->setEnabled(true);
        this->ColorTemp_spinBox->setEnabled(true);
        this->ColorTemp_Slider->setValue(stColorTemp.uiCTempVal-2);
        this->Red_Slider->setValue(stColorTemp.uiCTR);
        this->Red_spinBox->setValue(stColorTemp.uiCTR);
        this->Green_Slider->setValue(stColorTemp.uiCTG);
        this->Green_spinBox->setValue(stColorTemp.uiCTG);
        this->Blue_Slider->setValue(stColorTemp.uiCTB);
        this->Blue_spinBox->setValue(stColorTemp.uiCTB);
        this->Red_Slider->setDisabled(true);
        this->Red_spinBox->setDisabled(true);
        this->Green_Slider->setDisabled(true);
        this->Green_spinBox->setDisabled(true);
        this->Blue_Slider->setDisabled(true);
        this->Blue_spinBox->setDisabled(true);
    }
}

void VideoAdjustment::SetScalingControlValue(stVIDGOUT_SCAL stScaling)
{
    if(stScaling.uiScalVal==VIDGOUT_SCALVAL_NATIVE)
    {
        this->Scaling_Native_RadioButton->setChecked(true);
        this->Zoom_Slider->setDisabled(true);
        this->Zoom_spinBox->setDisabled(true);
        this->H_Scaling_Slider->setDisabled(true);
        this->H_Scaling_doubleSpinBox->setDisabled(true);
    }
    else if(stScaling.uiScalVal==VIDGOUT_SCALVAL_BESTFIT)
    {
        this->Scaling_Best_Fit_RadioButton->setChecked(true);
        this->Zoom_Slider->setDisabled(true);
        this->Zoom_spinBox->setDisabled(true);
        this->H_Scaling_Slider->setDisabled(true);
        this->H_Scaling_doubleSpinBox->setDisabled(true);
    }
    else if(stScaling.uiScalVal==VIDGOUT_SCALVAL_FULL)
    {
        this->Scaling_Full_RadioButton->setChecked(true);
        this->Zoom_Slider->setDisabled(true);
        this->Zoom_spinBox->setDisabled(true);
        this->H_Scaling_Slider->setDisabled(true);
        this->H_Scaling_doubleSpinBox->setDisabled(true);
    }else if(stScaling.uiScalVal==VIDGOUT_SCALVAL_FourToThree)
    {
        this->Scaling_FourToThree_RadioButton->setChecked(true);
        this->Zoom_Slider->setDisabled(true);
        this->Zoom_spinBox->setDisabled(true);
        this->H_Scaling_Slider->setDisabled(true);
        this->H_Scaling_doubleSpinBox->setDisabled(true);
    }
    else {
        if(stScaling.uiAdjVal!=this->Zoom_Slider->value())
            this->read_Scaling_Zoom=true;
        if(stScaling.uiFramHth!=this->H_Scaling_Slider->value())
            this->read_H_Scaling=true;

        this->Scaling_Adjust_RadioButton->setChecked(true);
        this->Zoom_Slider->setEnabled(true);
        this->Zoom_spinBox->setEnabled(true);
        this->H_Scaling_Slider->setEnabled(true);
        this->H_Scaling_doubleSpinBox->setEnabled(true);
        this->Zoom_Slider->setValue(stScaling.uiAdjVal);
        this->H_Scaling_Slider->setValue(stScaling.uiFramHth);
    }
}

void VideoAdjustment::Slider_Value_Changed(int value)
{
    QSlider* Slider = qobject_cast<QSlider*>(sender());
    if(Slider->objectName()=="Brightness_Slider")
    {
        this->Brightness_spinBox->setValue(value);
    }else if(Slider->objectName()=="Contrast_Slider")
    {
        this->Contrast_spinBox->setValue(value);
    }else if(Slider->objectName()=="Color_Slider")
    {
        this->Color_spinBox->setValue(value);
    }else if(Slider->objectName()=="Hue_Slider")
    {
        this->Hue_spinBox->setValue(value);
    }else if(Slider->objectName()=="Sharpness_Slider")
    {
        this->Sharpness_spinBox->setValue(value);
    }else if(Slider->objectName()=="Noise_Slider")
    {
        this->Noise_spinBox->setValue(value);
    }else if(Slider->objectName()=="Phase_Slider")
    {
        this->Phase_spinBox->setValue(value);
    }else if(Slider->objectName()=="Frequency_Slider")
    {
        this->Frequency_spinBox->setValue(value);
    }else if(Slider->objectName()=="H_Start_Slider")
    {
        this->H_start_spinBox->setValue(value);
    }else if(Slider->objectName()=="V_Start_Slider")
    {
        this->V_start_spinBox->setValue(value);
    }else if(Slider->objectName()=="Clampwidth_Slider")
    {
        this->Clampwidth_doubleSpinBox->setValue((double)value/10);
    }else if(Slider->objectName()=="Bandwidth_Slider")
    {
        this->Bandwidth_spinBox->setValue(value);
    }else if(Slider->objectName()=="Red_Slider")
    {
        if(this->Color_RGB_RadioButton->isChecked())
            this->Red_spinBox->setValue(value);
    }else if(Slider->objectName()=="Green_Slider")
    {
        if(this->Color_RGB_RadioButton->isChecked())
            this->Green_spinBox->setValue(value);
    }else if(Slider->objectName()=="Blue_Slider")
    {
        if(this->Color_RGB_RadioButton->isChecked())
            this->Blue_spinBox->setValue(value);
    }else if(Slider->objectName()=="Zoom_Slider")
    {
        if(this->Scaling_Adjust_RadioButton->isChecked())
            this->Zoom_spinBox->setValue(value);
    }else if(Slider->objectName()=="H_Scaling_Slider")
    {
        if(this->Scaling_Adjust_RadioButton->isChecked())
        {
            qDebug()<<"H_Scaling_Slider:"<<value;
            double temValue=(double)this->H_Scaling_Slider->value()/1000;
            this->H_Scaling_doubleSpinBox->setValue(temValue);
        }
    }else if(Slider->objectName()=="ColorTemp_Slider")
    {
        if(this->Color_Temp_RadioButton->isChecked())
        {
           qDebug()<<"================"<<value;
            this->ColorTemp_spinBox->setValue((value+8)*500);
        }
    }
}

void VideoAdjustment::spinBox_Valie_changed(int value)
{
    QSpinBox* SpinBox = qobject_cast<QSpinBox*>(sender());
    stVALUE_INFO stValue;
    if(SpinBox->objectName()=="Brightness_spinBox")
    {
        this->Brightness_Slider->setValue(value);
        if(!read_Brightness)
        {
            stValue.type=this->SigInId;
            stValue.value=value;
            emit Set_Value(LIGHTNESS,stValue);
        }
        read_Brightness=false;
    }else if(SpinBox->objectName()=="Contrast_spinBox")
    {
        this->Contrast_Slider->setValue(value);
        if(!read_Contrast)
        {
            stValue.type=this->SigInId;
            stValue.value=value;
            emit Set_Value(CONTRAST,stValue);
        }
        read_Contrast=false;
    }else if(SpinBox->objectName()=="Color_spinBox")
    {
        this->Color_Slider->setValue(value);
        if(!read_Color)
        {
            stValue.type=this->SigInId;
            stValue.value=value;
            emit Set_Value(COLOR,stValue);

        }
        read_Color=false;
    }else if(SpinBox->objectName()=="Hue_spinBox")
    {
        this->Hue_Slider->setValue(value);
        if(!read_Hue)
        {
            stValue.type=this->SigInId;
            stValue.value=value;
            emit Set_Value(HUE,stValue);

        }
        read_Hue=false;
    }else if(SpinBox->objectName()=="Sharpness_spinBox")
    {
        this->Sharpness_Slider->setValue(value);
        if(!read_Sharpness)
        {
            stValue.type=this->SigInId;
            stValue.value=value;
            emit Set_Value(SHARPNESS,stValue);
        }
        read_Sharpness=false;
    }else if(SpinBox->objectName()=="Noise_spinBox")
    {
        this->Noise_Slider->setValue(value);
        if(!read_Noise)
        {
            stValue.type=this->SigInId;
            stValue.value=value;
            emit Set_Value(NOISEREDUCTION,stValue);
        }
        read_Noise=false;
    }else if(SpinBox->objectName()=="Phase_spinBox")
    {
        this->Phase_Slider->setValue(value);
        if(!read_Phase)
        {
            stValue.type=this->SigInId;
            stValue.value=value;
            emit Set_Value(PHASE,stValue);
        }
        read_Phase=false;
    }else if(SpinBox->objectName()=="H_start_spinBox")
    {
        this->H_Start_Slider->setValue(value);
        if(!read_HStart)
        {
            stValue.type=this->SigInId;
            stValue.value=value;
            emit Set_Value(H_START,stValue);
        }
        read_HStart=false;
    }else if(SpinBox->objectName()=="V_start_spinBox")
    {
        this->V_Start_Slider->setValue(value);
        if(!read_VStart)
        {
            stValue.type=this->SigInId;
            stValue.value=value;
            emit Set_Value(V_START,stValue);
        }
        read_VStart=false;
    }else if(SpinBox->objectName()=="Frequency_spinBox")
    {
        this->Frequency_Slider->setValue(value);
        if(!read_Frequency_Scope)
        {
            if(!read_Frequency)
            {
                stValue.type=this->SigInId;
                stValue.value=value;
                emit Set_Value(FREQUENCY,stValue);
            }
            read_Frequency=false;
        }
        read_Frequency_Scope=false;
    }else if(SpinBox->objectName()=="Bandwidth_spinBox")
    {
        this->Bandwidth_Slider->setValue(value);
        if(!read_Bandwidth)
        {
            stValue.type=this->SigInId;
            stValue.value=value;
            emit Set_Value(BANDWIDTH,stValue);
        }
        read_Bandwidth=false;
    }else if(SpinBox->objectName()=="Red_spinBox")
    {
        this->Red_Slider->setValue(value);
        if(this->Color_RGB_RadioButton->isChecked() && !read_ColorTemp_R)
        {
            stDISP_COLORTEMP stColorTemp;
            stColorTemp.uiDispSigId=this->SigInId;
            stColorTemp.uiCTempVal=DISP_CTEMP_RGB;
            stColorTemp.uiCTR=this->Red_spinBox->value();
            stColorTemp.uiCTG=this->Green_spinBox->value();
            stColorTemp.uiCTB=this->Blue_spinBox->value();
            emit Set_ColorTemp(stColorTemp);
        }
        read_ColorTemp_R=false;
    }else if(SpinBox->objectName()=="Green_spinBox")
    {
        this->Green_Slider->setValue(value);
        if(this->Color_RGB_RadioButton->isChecked() && !read_ColorTemp_G)
        {
            stDISP_COLORTEMP stColorTemp;
            stColorTemp.uiDispSigId=this->SigInId;
            stColorTemp.uiCTempVal=DISP_CTEMP_RGB;
            stColorTemp.uiCTR=this->Red_spinBox->value();
            stColorTemp.uiCTG=this->Green_spinBox->value();
            stColorTemp.uiCTB=this->Blue_spinBox->value();
            emit Set_ColorTemp(stColorTemp);

        }
        read_ColorTemp_G=false;
    }else if(SpinBox->objectName()=="Blue_spinBox")
    {
        this->Blue_Slider->setValue(value);
        if(this->Color_RGB_RadioButton->isChecked() && !read_ColorTemp_B)
        {
            stDISP_COLORTEMP stColorTemp;
            stColorTemp.uiDispSigId=this->SigInId;
            stColorTemp.uiCTempVal=DISP_CTEMP_RGB;
            stColorTemp.uiCTR=this->Red_spinBox->value();
            stColorTemp.uiCTG=this->Green_spinBox->value();
            stColorTemp.uiCTB=this->Blue_spinBox->value();
            emit Set_ColorTemp(stColorTemp);

        }
        read_ColorTemp_B=false;
    }else if(SpinBox->objectName()=="ColorTemp_spinBox")
    {
        this->ColorTemp_Slider->setValue((value/500)-8);
        if(this->Color_Temp_RadioButton->isChecked() && !read_ColorTemp_Temp)
        {
            stDISP_COLORTEMP stColorTemp;
            stColorTemp.uiDispSigId=this->SigInId;
            stColorTemp.uiCTempVal=value/500-6;
            stColorTemp.uiCTR=0;
            stColorTemp.uiCTG=0;
            stColorTemp.uiCTB=0;
            emit Set_ColorTemp(stColorTemp);

        }
        read_ColorTemp_Temp=false;
    }else if(SpinBox->objectName()=="Zoom_spinBox")
    {
        this->Zoom_Slider->setValue(value);
        stVIDGOUT_SCAL stScaling;
        if(this->Scaling_Adjust_RadioButton->isChecked() && !read_Scaling_Zoom)
        {
            stScaling.uiSigId=this->SigInId;
            stScaling.uiScalVal=VIDGOUT_SCALVAL_ADJUST;
            stScaling.uiAdjVal=this->Zoom_spinBox->value();
            stScaling.uiFramHth=this->H_Scaling_Slider->value();
            stScaling.uiFramWid=0;
            emit Set_SCaling(stScaling);

        }
        read_Scaling_Zoom=false;
    }
}

void VideoAdjustment::Double_spinBox_Valie_changed(double value)
{
    QDoubleSpinBox* Double_SpinBox = qobject_cast<QDoubleSpinBox*>(sender());

    if(Double_SpinBox->objectName()=="Clampwidth_doubleSpinBox")
    {
        this->Clampwidth_Slider->setValue((int)(value*10));
        if(!read_Clampwidth)
        {
            stVALUE_INFO stValue;
            stValue.type=this->SigInId;
            stValue.value=this->Clampwidth_Slider->value();
            emit Set_Value(CLAMPWIDTH,stValue);
        }
        read_Clampwidth=false;
    }

    if(Double_SpinBox->objectName()=="H_Scaling_doubleSpinBox")
    {
        int n_value=doubleToInt(value*1000);
        this->H_Scaling_Slider->setValue(n_value);
        qDebug()<<this->H_Scaling_Slider->value();
        stVIDGOUT_SCAL stScaling;
        if(this->Scaling_Adjust_RadioButton->isChecked() && !read_H_Scaling)
        {
            stScaling.uiSigId=this->SigInId;
            stScaling.uiScalVal=VIDGOUT_SCALVAL_ADJUST;
            stScaling.uiAdjVal=this->Zoom_spinBox->value();
            stScaling.uiFramHth=this->H_Scaling_Slider->value();
            stScaling.uiFramWid=0;
            emit Set_SCaling(stScaling);

        }
        read_H_Scaling=false;
    }
}

void VideoAdjustment::CheckBox_StateChanged()
{
    QCheckBox* checkBox = qobject_cast<QCheckBox*>(sender());
    if(checkBox->objectName()=="Dither_CheckBox")
    {
                stVALUE_INFO stValue;
                stValue.type=this->SigInId;
                if(this->Dither_CheckBox->isChecked())
                    stValue.value=1;
                else
                    stValue.value=0;
                emit Set_Value(DITHER,stValue);
    }
}

void VideoAdjustment::RadioButton_Clicked()
{
    QRadioButton* radiobutton = qobject_cast<QRadioButton*>(sender());

     if(radiobutton->objectName()=="Bandwidth_Auto_RadioButton")
     {
             this->label_35->setEnabled(false);
             this->Bandwidth_Slider->setEnabled(false);
             this->Bandwidth_spinBox->setEnabled(false);
             stVALUE_INFO stValue;
             stValue.type=this->SigInId;
             stValue.value=-1;
             emit Set_Value(BANDWIDTH,stValue);

     }else if(radiobutton->objectName()=="Bandwidth_Manual_RadioButton")
     {
         this->label_35->setEnabled(true);
         this->Bandwidth_Slider->setEnabled(true);
         this->Bandwidth_spinBox->setEnabled(true);

         stVALUE_INFO stValue;
         stValue.type=this->SigInId;
         stValue.value=this->Bandwidth_spinBox->value();
         emit Set_Value(BANDWIDTH,stValue);
     }else if(radiobutton->objectName()=="Color_Native_RadioButton")
     {
             this->ColorTemp_Slider->setEnabled(false);
             this->ColorTemp_spinBox->setEnabled(false);
             this->label_37->setEnabled(false);
             this->label_38->setEnabled(false);
             this->label_39->setEnabled(false);
             this->Red_Slider->setEnabled(false);
             this->Red_spinBox->setEnabled(false);
             this->Green_Slider->setEnabled(false);
             this->Green_spinBox->setEnabled(false);
             this->Blue_Slider->setEnabled(false);
             this->Blue_spinBox->setEnabled(false);
             stDISP_COLORTEMP stColorTemp;
             stColorTemp.uiDispSigId=this->SigInId;
             stColorTemp.uiCTempVal=DISP_CTEMP_NATIVE;
             stColorTemp.uiCTR=this->Red_spinBox->value();
             stColorTemp.uiCTG=this->Green_spinBox->value();
             stColorTemp.uiCTB=this->Blue_spinBox->value();
             emit Set_ColorTemp(stColorTemp);

     }else if(radiobutton->objectName()=="Color_RGB_RadioButton")
     {
         this->ColorTemp_Slider->setEnabled(false);
         this->ColorTemp_spinBox->setEnabled(false);
         this->label_37->setEnabled(true);
         this->label_38->setEnabled(true);
         this->label_39->setEnabled(true);
         this->Red_Slider->setEnabled(true);
         this->Red_spinBox->setEnabled(true);
         this->Green_Slider->setEnabled(true);
         this->Green_spinBox->setEnabled(true);
         this->Blue_Slider->setEnabled(true);
         this->Blue_spinBox->setEnabled(true);
//         stDISP_COLORTEMP stColorTemp;
//         stColorTemp.uiDispSigId=this->SigInId;
//         stColorTemp.uiCTempVal=DISP_CTEMP_NATIVE;
//         stColorTemp.uiCTR=this->Red_spinBox->value();
//         stColorTemp.uiCTG=this->Green_spinBox->value();
//         stColorTemp.uiCTB=this->Blue_spinBox->value();
//         emit Set_ColorTemp(stColorTemp);
         emit Read_CTmep_Scaing(1);
     }else if(radiobutton->objectName()=="Color_Temp_RadioButton")
     {
         this->ColorTemp_Slider->setEnabled(true);
         this->ColorTemp_spinBox->setEnabled(true);
         this->label_37->setEnabled(false);
         this->label_38->setEnabled(false);
         this->label_39->setEnabled(false);
         this->Red_Slider->setEnabled(false);
         this->Red_spinBox->setEnabled(false);
         this->Green_Slider->setEnabled(false);
         this->Green_spinBox->setEnabled(false);
         this->Blue_Slider->setEnabled(false);
         this->Blue_spinBox->setEnabled(false);
         stDISP_COLORTEMP stColorTemp;
         stColorTemp.uiDispSigId=this->SigInId;
         stColorTemp.uiCTempVal=this->ColorTemp_spinBox->value()/500-6;
         stColorTemp.uiCTR=this->Red_spinBox->value();
         stColorTemp.uiCTG=this->Green_spinBox->value();
         stColorTemp.uiCTB=this->Blue_spinBox->value();
         emit Set_ColorTemp(stColorTemp);
     }else if(radiobutton->objectName()=="Display_Native_RadioButton")
     {
         this->Gamma_comboBox->setEnabled(false);
         stVALUE_INFO stValue;
         stValue.type=this->SigInId;
         stValue.value=DISP_GAMMA_NATIVE;
         emit Set_Value(GAMMA,stValue);
     }else if(radiobutton->objectName()=="Display_DICOM_RadioButton")
     {
         this->Gamma_comboBox->setEnabled(false);
         stVALUE_INFO stValue;
         stValue.type=this->SigInId;
         stValue.value=DISP_GAMMA_DICOM;
         emit Set_Value(GAMMA,stValue);
     }else if(radiobutton->objectName()=="Display_Gamma_RadioButton")
     {
         this->Gamma_comboBox->setEnabled(true);
         stVALUE_INFO stValue;
         stValue.type=this->SigInId;
         stValue.value=this->Gamma_comboBox->currentIndex()+1;
         emit Set_Value(GAMMA,stValue);
     }else if(radiobutton->objectName()=="Scaling_Native_RadioButton")
     {
         this->label_41->setEnabled(false);
         this->Zoom_Slider->setEnabled(false);
         this->Zoom_spinBox->setEnabled(false);
         this->label_42->setEnabled(false);
         this->H_Scaling_Slider->setEnabled(false);
         this->H_Scaling_doubleSpinBox->setEnabled(false);
         stVIDGOUT_SCAL stScaling;
         stScaling.uiSigId=this->SigInId;
         stScaling.uiScalVal=VIDGOUT_SCALVAL_NATIVE;
         stScaling.uiAdjVal=0;
         stScaling.uiFramHth=0;
         stScaling.uiFramWid=0;
         emit Set_SCaling(stScaling);
     }else if(radiobutton->objectName()=="Scaling_Best_Fit_RadioButton")
     {
         this->label_41->setEnabled(false);
         this->Zoom_Slider->setEnabled(false);
         this->Zoom_spinBox->setEnabled(false);
         this->label_42->setEnabled(false);
         this->H_Scaling_Slider->setEnabled(false);
         this->H_Scaling_doubleSpinBox->setEnabled(false);
         stVIDGOUT_SCAL stScaling;
         stScaling.uiSigId=this->SigInId;
         stScaling.uiScalVal=VIDGOUT_SCALVAL_BESTFIT;
         stScaling.uiAdjVal=0;
         stScaling.uiFramHth=0;
         stScaling.uiFramWid=0;
         emit Set_SCaling(stScaling);
     }else if(radiobutton->objectName()=="Scaling_Full_RadioButton")
     {
         this->label_41->setEnabled(false);
         this->Zoom_Slider->setEnabled(false);
         this->Zoom_spinBox->setEnabled(false);
         this->label_42->setEnabled(false);
         this->H_Scaling_Slider->setEnabled(false);
         this->H_Scaling_doubleSpinBox->setEnabled(false);
         stVIDGOUT_SCAL stScaling;
         stScaling.uiSigId=this->SigInId;
         stScaling.uiScalVal=VIDGOUT_SCALVAL_FULL;
         stScaling.uiAdjVal=0;
         stScaling.uiFramHth=0;
         stScaling.uiFramWid=0;
         emit Set_SCaling(stScaling);
     }else if(radiobutton->objectName()=="Scaling_Adjust_RadioButton")
     {
         this->label_41->setEnabled(true);
         this->Zoom_Slider->setEnabled(true);
         this->Zoom_spinBox->setEnabled(true);
         this->label_42->setEnabled(true);
         this->H_Scaling_Slider->setEnabled(true);
         this->H_Scaling_doubleSpinBox->setEnabled(true);
//         stVIDGOUT_SCAL stScaling;
//         if(this->SigInId<eVIDSIGIN_DP3)
//             stScaling.uiSigId=eVIDSIGOUT_G1;
//         else
//             stScaling.uiSigId=eVIDSIGOUT_G2;

//             stScaling.uiScalVal=VIDGOUT_SCALVAL_ADJUST;
//             stScaling.uiAdjVal=this->Zoom_spinBox->value();
//             stScaling.uiFramHth=0;
//             stScaling.uiFramWid=0;
//             emit Set_SCaling(stScaling);
         emit Read_CTmep_Scaing(2);
     }else if(radiobutton->objectName()=="Scaling_FourToThree_RadioButton")
     {
         this->label_41->setEnabled(false);
         this->Zoom_Slider->setEnabled(false);
         this->Zoom_spinBox->setEnabled(false);
         this->label_42->setEnabled(false);
         this->H_Scaling_Slider->setEnabled(false);
         this->H_Scaling_doubleSpinBox->setEnabled(false);
         stVIDGOUT_SCAL stScaling;
         stScaling.uiSigId=this->SigInId;
         stScaling.uiScalVal=VIDGOUT_SCALVAL_FourToThree;
         stScaling.uiAdjVal=0;
         stScaling.uiFramHth=0;
         stScaling.uiFramWid=0;
         emit Set_SCaling(stScaling);
     }else if(radiobutton->objectName()=="Automatic_radioButton")
     {
           emit emitSetOverlayCtrlMethod(0);
           this->Automatic_radioButton->setChecked(true);
     }
}

void VideoAdjustment::ComboBox_currentIndexChanged(int index)
{
    QComboBox* comboBox = qobject_cast<QComboBox*>(sender());

    if(comboBox->objectName()=="ColorTemp_comboBox")
    {
//        if(!read_ColorTemp_Temp)
//        {
//            stDISP_COLORTEMP stColorTemp;
//            stColorTemp.uiDispSigId=this->SigInId;
//            stColorTemp.uiCTempVal=this->ColorTemp_comboBox->currentIndex()+2;
//            stColorTemp.uiCTR=0;
//            stColorTemp.uiCTG=0;
//            stColorTemp.uiCTB=0;
//            emit Set_ColorTemp(stColorTemp);
//        }
//        read_ColorTemp_Temp=false;
    }else if (comboBox->objectName()=="Gamma_comboBox")
    {
        if(!read_gamma)
        {
            stVALUE_INFO stValue;
            stValue.type=this->SigInId;
            stValue.value=this->Gamma_comboBox->currentIndex()+1;
            emit Set_Value(GAMMA,stValue);
            //qDebug()<<"OSD SetGamma:"<<stValue.type<<stValue.value;
        }
        read_gamma=false;
    }
}

void VideoAdjustment::pushButton_Clicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    QPalette pa1;
    pa1.setColor(QPalette::WindowText,Qt::red);
    this->labelSetAuto->setPalette(pa1);
    if(button->objectName()=="Auto_Button_1")
    {
        DisableControlCursor();
        this->labelSetAuto->setText("     Auto Setup is active.Please wait");
        stAuto_INFO stValue_Info;
        stValue_Info.uiSigInId=this->SigInId;
        stValue_Info.DISP_PARAM_INDEX=DISP_PARAM_RESOLUT;
        stValue_Info.uiValue=1;
        emit Set_AutoSetup(stValue_Info);
    }else if(button->objectName()=="Auto_Button_2"){
        DisableControlCursor();
        this->labelSetAuto->setText("     Auto Setup is active.Please wait");
        stAuto_INFO stValue_Info;
        stValue_Info.uiSigInId=this->SigInId;
        stValue_Info.DISP_PARAM_INDEX=DISP_PARAM_PHASE;
        stValue_Info.uiValue=1;
        emit Set_AutoSetup(stValue_Info);
    }else if(button->objectName()=="Auto_Button_3"){
        DisableControlCursor();
        this->labelSetAuto->setText("     Auto Setup is active.Please wait");
        stAuto_INFO stValue_Info;
        stValue_Info.uiSigInId=this->SigInId;
        stValue_Info.DISP_PARAM_INDEX=DISP_PARAM_GAINOFFSET;
        stValue_Info.uiValue=1;
        emit Set_AutoSetup(stValue_Info);
    }else if(button->objectName()=="Auto_Button_4"){
        DisableControlCursor();
        this->labelSetAuto->setText("     Auto Setup is active.Please wait");
        stAuto_INFO stValue_Info;
        stValue_Info.uiSigInId=this->SigInId;
        stValue_Info.DISP_PARAM_INDEX=DISP_PARAM_GEOMETY;
        stValue_Info.uiValue=1;
        emit Set_AutoSetup(stValue_Info);
    }else if(button->objectName()=="Restore_Curr_Preset_Button"){
        emit Set_PresetCfg(0);
    }else if(button->objectName()=="Next_Preset_Button"){
        emit Set_PresetCfg(1);
    }else if(button->objectName()=="Save_Preset_Button"){
        emit Set_PresetCfg(2);
    }else if(button->objectName()=="Restore_Default_Preset_Button"){
        emit Set_PresetCfg(3);
    }else if(button->objectName()=="DP_Adjust_Button"){
        emit Get_DP_Info(1);
        dp_adjustment->blIsSendSetDp=false;
        dp_adjustment->init();
        dp_adjustment->enableCheckBox();
        connect(dp_adjustment->timer, SIGNAL(timeout()), dp_adjustment, SLOT(slot_DpInfoHide()));
        dp_adjustment->timer->start(13000);
    }else if(button->objectName()=="OverlayModesButton"){
        emit emitSetOverlayCtrlMethod(1);
        this->Automatic_radioButton->setChecked(false);
        emit emitOverlayModes(OVERLAY_MODES);        
    }else if(button->objectName()=="NewModesButton"){
        emit emitOverlayModes(NEW_OVERLAY_MODES);
    }else if(button->objectName()=="ClearModesButton"){
        QMessageBox::StandardButton result= QMessageBox::information(this, "ToolTips", "Confirm to clear data OverlayModes!",QMessageBox::Yes|QMessageBox::No);
        switch (result)
        {
        case QMessageBox::Yes:
            emit emitOverlayModes(CLEAR_OVERLAY_MODES);
            break;
        case QMessageBox::No:
            break;
        default:
            break;
        }

    }
}

void VideoAdjustment::ToolButton_Clicked()
{
    QToolButton* button = qobject_cast<QToolButton*>(sender());
    if(button->objectName()=="toolButton")
        this->hide();
}

void VideoAdjustment::st_DP_Info(stSCAL_INPUT_DP_INFO DP_Info)
{
    DP_Info.SigInId=this->SigInId;
    emit Set_DP_Info(DP_Info);
}

void VideoAdjustment::gt_DP_Info(int sigid)
{
    emit Get_DP_Info(sigid);
}


#include "qspotlightsetting.h"
#include "ui_qspotlightsetting.h"
#include <QColorDialog>
#include "spotlightwidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLayout>
#include <QDebug>
#include "userdefine.h"


QSpotlightSetting::QSpotlightSetting(QWidget *parent) :
                                                        QDialog(parent),mp_colorSpotlight(NULL),
                                                        mp_colorLasterpen(NULL),mp_colorFindMouse(NULL),
                                                        mp_SpotlightRadius(NULL),mp_LasterpenRadius(NULL),
                                                        mp_watordropRadius(NULL),mp_SpotlightShortcutKey(NULL),
                                                        mp_ReadModeShortcutKey(NULL),mp_LasterpenShortcutKey(NULL),
                                                        mp_FindMouseShortcutKey(NULL),mp_ScreenshotShortcutKey(NULL),
ui(new Ui::QSpotlightSetting)
{
ui->setupUi(this);
ControlLayout();
ui->radioButtonNormal->setChecked(true);
ui->sliderSpotLight->setRange(40,300);
ui->sliderLasterPen->setRange(15,60);
ui->sliderWatordrop->setRange(15,60);
ui->sliderActiveValue->setRange(10,250);
connect(ui->pushButtonOK,SIGNAL(clicked()),this,SLOT(setLanguage()));
connect(ui->colorSpotlight,SIGNAL(clicked()),this,SLOT(setSpotlightColor()));
connect(ui->colorLasterpen,SIGNAL(clicked()),this,SLOT(setLasterpenColor()));
connect(ui->colorWatordrop,SIGNAL(clicked()),this,SLOT(setWatordropColor()));
connect(ui->RestoreDefaultpushButton,SIGNAL(clicked()),this,SLOT(RestoreDefaultSettings()));

connect(ui->sliderSpotLight,SIGNAL(valueChanged(int)),this,SLOT(setSpotlightValue(int)));
connect(ui->sliderLasterPen,SIGNAL(valueChanged(int)),this,SLOT(setLasterpenValue(int)));
connect(ui->sliderWatordrop,SIGNAL(valueChanged(int)),this,SLOT(setWatordropValue(int)));
connect(ui->sliderActiveValue,SIGNAL(valueChanged(int)),this,SLOT(setActiveValue(int)));

connect(m_SpotlightShortcutKey,SIGNAL(textChanged(QString)),this,SLOT(setSpotlightShortcutKey(QString)));
connect(m_ReadmodeShortcutKey,SIGNAL(textChanged(QString)),this,SLOT(setReadodeShortcutKey(QString)));
connect(m_LasterpenShortcutKey,SIGNAL(textChanged(QString)),this,SLOT(setLasterpenShortcutKey(QString)));
connect(m_FindMouseShortcutKey,SIGNAL(textChanged(QString)),this,SLOT(setFindmouseShortcutKey(QString)));
connect(m_ScreenshotShortcutKey,SIGNAL(textChanged(QString)),this,SLOT(setScreenshotShortcutKey(QString)));
connect(m_MagnifyingShortcutKey,SIGNAL(textChanged(QString)),this,SLOT(setMagnifyingShortcutKey(QString)));

connect(this,SIGNAL(close()),this,SLOT(close()));
this->setWindowTitle(tr("Setting"));
setAttribute(Qt::WA_QuitOnClose, false);
setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
//showColorButton();
#if 0
QPalette pal =ui->pushButtonLasterColor->palette();
pal.setColor(QPalette::Button, Qt::red);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
//pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
ui->pushButtonLasterColor->setPalette(pal);
QColor _color=QColor(255,0,0);
ui->pushButtonLasterColor->setStyleSheet(QString("background-color:%1").arg(_color.name()));;



QPalette pal = startBtn.palette();              //startBtn是我已经定义好的QPushButton对象
pal.setColor(QPalette::ButtonText, Qt::red);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
pal.setColor(QPalette::Button, Qt::green);
#endif
}

QSpotlightSetting::~QSpotlightSetting()
{
delete ui;



}

void QSpotlightSetting::ControlLayout()
{
    QHBoxLayout *LanguageLayout=new QHBoxLayout;
    LanguageLayout->addWidget(ui->label_11);
    LanguageLayout->addWidget(ui->LanguagecomboBox);
    LanguageLayout->addWidget(ui->pushButtonOK);

    QGridLayout *RudiusLayout=new QGridLayout;
    RudiusLayout->addWidget(ui->label,0,0,1,1);
    RudiusLayout->addWidget(ui->sliderSpotLight,0,1,1,1);
    RudiusLayout->addWidget(ui->label_2,1,0,1,1);
    RudiusLayout->addWidget(ui->sliderLasterPen,1,1,1,1);
    RudiusLayout->addWidget(ui->label_6,2,0,1,1);
    RudiusLayout->addWidget(ui->sliderWatordrop,2,1,1,1);
     RudiusLayout->addWidget(ui->label_active_value,3,0,1,1);
     RudiusLayout->addWidget(ui->sliderActiveValue,3,1,1,1);

    QGridLayout *ColorLayout=new QGridLayout;
    ColorLayout->addWidget(ui->label_3,0,0,1,1);
    ColorLayout->addWidget(ui->colorSpotlight,0,1,1,1);
    ColorLayout->addWidget(ui->label_4,1,0,1,1);
    ColorLayout->addWidget(ui->colorLasterpen,1,1,1,1);
    ColorLayout->addWidget(ui->label_5,2,0,1,1);
    ColorLayout->addWidget(ui->colorWatordrop,2,1,1,1);

    QGridLayout *ShortcutKeyLayout=new QGridLayout;
    m_SpotlightShortcutKey=new LineEditShortcutKey(this);
    m_ReadmodeShortcutKey=new LineEditShortcutKey(this);
    m_LasterpenShortcutKey=new LineEditShortcutKey(this);
    m_FindMouseShortcutKey=new LineEditShortcutKey(this);
    m_ScreenshotShortcutKey=new LineEditShortcutKey(this);
    m_MagnifyingShortcutKey=new LineEditShortcutKey(this);
    ShortcutKeyLayout->addWidget(ui->label_7,0,0,1,1);
    ShortcutKeyLayout->addWidget(m_SpotlightShortcutKey,0,1,1,1);
    ShortcutKeyLayout->addWidget(ui->label_8,1,0,1,1);
    ShortcutKeyLayout->addWidget(m_ReadmodeShortcutKey,1,1,1,1);
    ShortcutKeyLayout->addWidget(ui->label_9,2,0,1,1);
    ShortcutKeyLayout->addWidget(m_LasterpenShortcutKey,2,1,1,1);
    ShortcutKeyLayout->addWidget(ui->label_10,3,0,1,1);
    ShortcutKeyLayout->addWidget(m_FindMouseShortcutKey,3,1,1,1);
    ShortcutKeyLayout->addWidget(ui->label_12,4,0,1,1);
    ShortcutKeyLayout->addWidget(m_ScreenshotShortcutKey,4,1,1,1);
    ShortcutKeyLayout->addWidget(ui->label_13,5,0,1,1);
    ShortcutKeyLayout->addWidget(m_MagnifyingShortcutKey,5,1,1,1);

    QHBoxLayout *ReadmodeSetLayout=new QHBoxLayout;
    //SignalComboBox =new QCheckboxCombo(this);
    ReadmodeSetLayout->addWidget(ui->label_14);
    ReadmodeSetLayout->addWidget(ui->radioButtonNormal);
    ReadmodeSetLayout->addWidget(ui->radioButtonLeft);
    ReadmodeSetLayout->addWidget(ui->radioButtonRight);
    //ReadmodeSetLayout->addWidget(SignalComboBox);

    QHBoxLayout *HBoxLayout=new QHBoxLayout;
    HBoxLayout->addStretch();
    HBoxLayout->addWidget(ui->RestoreDefaultpushButton);

    QGridLayout *mainLayout=new QGridLayout(this);
    mainLayout->addLayout(LanguageLayout,0,0,1,1);
    mainLayout->addLayout(RudiusLayout,1,0,1,1);
    mainLayout->addLayout(ColorLayout,2,0,1,1);
    mainLayout->addLayout(ShortcutKeyLayout,3,0,1,1);
    mainLayout->addLayout(ReadmodeSetLayout,4,0,1,1);
    mainLayout->addLayout(HBoxLayout,5,0,1,1);
    this->setLayout(mainLayout);
}
void QSpotlightSetting::setSpotlightColor()
{
    QTranslator SysTranslator;
    QString strColorDialogName;
    int nLanguageType=ui->LanguagecomboBox->currentIndex();
    switch (nLanguageType) {
    case ENGLISH:
        qApp->removeTranslator(&SysTranslator);
        strColorDialogName=QString("Color dialog");
        break;
    case CHINESE:
        SysTranslator.load(":/system/Resources/qt_zh_CN.qm");
        qApp->installTranslator(&SysTranslator);
        strColorDialogName=QString("颜色对话框");
        break;
    default:
        break;
    }

    QColor cColor;
    if(mp_colorSpotlight!=NULL)
    cColor= QColorDialog::getColor(*mp_colorSpotlight, this,
                                          strColorDialogName,
                                          QColorDialog::ShowAlphaChannel);
    if(cColor.isValid())
    {
        *mp_colorSpotlight=cColor;
    //m_colorSpotlight=QColor(255,0,0);
        showColorButton();
    }
    return ;
    QColorDialog *m_pColor = new QColorDialog(this);
//  QColorDialog m_pColor;
 //  m_pColor->setCurrentColor(m_color);
  m_pColor->show();
 //   connect(m_pColor,SIGNAL(currentColorChanged(QColor)),this,SLOT(ShowColor(QColor)));//显示当前选中颜色的效果
 //   connect(m_pColor,SIGNAL(colorSelected(QColor)),this,SLOT(SetColor(QColor)));//OK信号连接
    //rejected信号会在QColorDialog框关闭或按Cancel按钮时发出，可通过绑定该信号来进行Cancel信号过滤
  //  connect(m_pColor,SIGNAL(rejected()),this,SLOT(SetColor_1()));
}
void QSpotlightSetting::setLasterpenColor()
{
    QTranslator SysTranslator;
    QString strColorDialogName;
    int nLanguageType=ui->LanguagecomboBox->currentIndex();
    switch (nLanguageType) {
    case ENGLISH:
        qApp->removeTranslator(&SysTranslator);
        strColorDialogName=QString("Color dialog");
        break;
    case CHINESE:
        SysTranslator.load(":/system/Resources/qt_zh_CN.qm");
        qApp->installTranslator(&SysTranslator);
        strColorDialogName=QString("颜色对话框");
        break;
    default:
        break;
    }

    QColor cColor;
    if(mp_colorLasterpen!=NULL)
        cColor=QColorDialog::getColor(*mp_colorLasterpen, this,
                                              strColorDialogName,
                                              QColorDialog::ShowAlphaChannel);

    if(cColor.isValid())
    {
        *mp_colorLasterpen=cColor;
        //m_colorSpotlight=QColor(255,0,0);
        showColorButton();
    }
}
void QSpotlightSetting::setWatordropColor()
{
    QTranslator SysTranslator;
    QString strColorDialogName;
    int nLanguageType=ui->LanguagecomboBox->currentIndex();
    switch (nLanguageType) {
    case ENGLISH:
        qApp->removeTranslator(&SysTranslator);
        strColorDialogName=QString("Color dialog");
        break;
    case CHINESE:
        SysTranslator.load(":/system/Resources/qt_zh_CN.qm");
        qApp->installTranslator(&SysTranslator);
        strColorDialogName=QString("颜色对话框");
        break;
    default:
        break;
    }

    QColor cColor;
    if(mp_colorFindMouse!=NULL)
          cColor = QColorDialog::getColor(*mp_colorFindMouse, this,
                                              strColorDialogName,
                                              QColorDialog::ShowAlphaChannel);
    if(cColor.isValid())
    {
        *mp_colorFindMouse=cColor;
        //m_colorSpotlight=QColor(255,0,0);
        showColorButton();
    }
}
void QSpotlightSetting::showColorButton()
{
    if(mp_colorSpotlight!=NULL)
     ui->colorSpotlight->setStyleSheet(QString("background-color:%1").arg(mp_colorSpotlight->name()));;
   if(mp_colorLasterpen!=NULL)
    ui->colorLasterpen->setStyleSheet(QString("background-color:%1").arg(mp_colorLasterpen->name()));;
   if(mp_colorFindMouse!=NULL)
       ui->colorWatordrop->setStyleSheet(QString("background-color:%1").arg(mp_colorFindMouse->name()));;
}

void QSpotlightSetting::ReTranslateUi(int nIndex)
{
    this->setWindowTitle(tr("Setting"));
    ui->label->setText(tr("Spotlight Radius:"));
    ui->label_2->setText(tr("Lasterpen Radius:"));
    ui->label_6->setText(tr("FindMouse Radius:"));
    ui->label_3->setText(tr("Spotlight Color:"));
    ui->label_4->setText(tr("Lasterpen Color:"));
    ui->label_5->setText(tr("FindMouse Color:"));
    ui->label_7->setText(tr("Spotlight Shortcut Key:"));
    ui->label_8->setText(tr("Readmode Shortcut  Key:"));
    ui->label_9->setText(tr("Lasterpen Shortcut Key:"));
    ui->label_10->setText(tr("FindMouse Shortcut Key:"));
    ui->label_12->setText(tr("Screenshot Shortcut Key:"));
    ui->label_13->setText(tr("Magnifying Shortcut Key:"));
    ui->label_11->setText(tr("Language Type:"));
    ui->label_active_value->setText(tr("Active value:"));

    ui->label_14->setText(tr("Readmode Setting:"));
    QStringList strLanguageType;
    strLanguageType<<tr("English")<<tr("Chinese");
    ui->LanguagecomboBox->clear();
    ui->LanguagecomboBox->addItems(strLanguageType);
    ui->LanguagecomboBox->setCurrentIndex(nIndex);

    ui->pushButtonOK->setText(tr("OK"));
    ui->RestoreDefaultpushButton->setText(tr("Restore default settings"));

    ui->radioButtonNormal->setText(tr("Normal"));
    ui->radioButtonLeft->setText(tr("Left"));
    ui->radioButtonRight->setText(tr("Right"));
}
void QSpotlightSetting::setItermColor(EmDesktopModeType type,QColor *color)
{
    switch (type) {

    case DESKTOP_MODE_SPOLIGHT:
        mp_colorSpotlight=color;
        break;
    case  DESKTOP_MODE_ACTIVE:
        //m_bEnableReadMode=blEnable;
        break;
    case DESKTOP_MODE_LASERPEN:
        mp_colorLasterpen=color;
        break;
    case  DESKTOP_MODE_WATORDROP:
        mp_colorFindMouse=color;
        break;
    case DESKTOP_MODE_NULL:
    default:
        return ;
    }
    showColorButton();
}
void QSpotlightSetting::setItermRadius(EmDesktopModeType type,int  *pRadius)
{

    switch (type) {

    case DESKTOP_MODE_SPOLIGHT:
        mp_SpotlightRadius=pRadius;
        ui->sliderSpotLight->setValue(*mp_SpotlightRadius);
        break;
    case  DESKTOP_MODE_ACTIVE:
        //m_bEnableReadMode=blEnable;
        break;

    case DESKTOP_MODE_LASERPEN:
        mp_LasterpenRadius=pRadius;
        ui->sliderLasterPen->setValue(*mp_LasterpenRadius);
        break;
  case  DESKTOP_MODE_WATORDROP:
      mp_watordropRadius=pRadius;
      ui->sliderWatordrop->setValue(*mp_watordropRadius);
        break;
    case DESKTOP_MODE_NULL:
    default:
        return ;
    }
}

void QSpotlightSetting::setItermShortcutKey(EmDesktopModeType type, QString *pstrShortcutKey)
{
    switch (type) {

    case DESKTOP_MODE_SPOLIGHT:
        mp_SpotlightShortcutKey=pstrShortcutKey;
        m_SpotlightShortcutKey->setText(*mp_SpotlightShortcutKey);
        break;
    case  DESKTOP_MODE_ACTIVE:
        mp_ReadModeShortcutKey=pstrShortcutKey;
        m_ReadmodeShortcutKey->setText(*mp_ReadModeShortcutKey);
        break;

    case DESKTOP_MODE_LASERPEN:
        mp_LasterpenShortcutKey=pstrShortcutKey;
        m_LasterpenShortcutKey->setText(*mp_LasterpenShortcutKey);
        break;
    case  DESKTOP_MODE_WATORDROP:
        mp_FindMouseShortcutKey=pstrShortcutKey;
        m_FindMouseShortcutKey->setText(*mp_FindMouseShortcutKey);
        break;
    case  DESKTOP_MODE_SCREENSHOT:
          mp_ScreenshotShortcutKey=pstrShortcutKey;
          m_ScreenshotShortcutKey->setText(*mp_ScreenshotShortcutKey);
          break;
    case  DESKTOP_MODE_MAGNIFYING:
          mp_MagnifyingShortcutKey=pstrShortcutKey;
          m_MagnifyingShortcutKey->setText(*mp_MagnifyingShortcutKey);
          break;
    case DESKTOP_MODE_NULL:
    default:
        return ;
    }
}
void QSpotlightSetting::setActiveValuePoint(int *pValue)
{
    mp_ActiveModeValue=pValue;
}
void QSpotlightSetting::setSpotlightValue(int nValue)
{
    if(mp_SpotlightRadius!=NULL)
        *mp_SpotlightRadius=nValue;

}
void QSpotlightSetting::setLasterpenValue(int nValue)
{
    if(mp_LasterpenRadius!=NULL)
        *mp_LasterpenRadius=nValue;


}void QSpotlightSetting::setWatordropValue(int nValue)
{
    if(mp_watordropRadius!=NULL)
        *mp_watordropRadius=nValue;


}
void QSpotlightSetting::setActiveValue(int nValue)
{
    if(mp_ActiveModeValue!=NULL)
        *mp_ActiveModeValue=nValue;


}
void QSpotlightSetting::setSpotlightShortcutKey(QString strValue)
{
    if(mp_SpotlightShortcutKey!=NULL)
        *mp_SpotlightShortcutKey=strValue;

    emit sigKeyChange(DESKTOP_MODE_SPOLIGHT,strValue);
}

void QSpotlightSetting::setReadodeShortcutKey(QString strValue)
{
    if(mp_ReadModeShortcutKey!=NULL)
        *mp_ReadModeShortcutKey=strValue;

    emit sigKeyChange(DESKTOP_MODE_ACTIVE,strValue);
}

void QSpotlightSetting::setLasterpenShortcutKey(QString strValue)
{
    if(mp_LasterpenShortcutKey!=NULL)
        *mp_LasterpenShortcutKey=strValue;

    emit sigKeyChange(DESKTOP_MODE_LASERPEN,strValue);
}

void QSpotlightSetting::setFindmouseShortcutKey(QString strValue)
{
    if(mp_FindMouseShortcutKey!=NULL)
        *mp_FindMouseShortcutKey=strValue;

    emit sigKeyChange(DESKTOP_MODE_WATORDROP,strValue);
}

void QSpotlightSetting::setScreenshotShortcutKey(QString strValue)
{
    if(mp_ScreenshotShortcutKey!=NULL)
        *mp_ScreenshotShortcutKey=strValue;

    emit sigKeyChange(DESKTOP_MODE_SCREENSHOT,strValue);
}

void QSpotlightSetting::setMagnifyingShortcutKey(QString strValue)
{
    if(mp_MagnifyingShortcutKey!=NULL)
        *mp_MagnifyingShortcutKey=strValue;

    emit sigKeyChange(DESKTOP_MODE_MAGNIFYING,strValue);
}

void QSpotlightSetting::RestoreDefaultSettings()
{
    int nLanguageType=ui->LanguagecomboBox->currentIndex();
    QTranslator LanguageTranslator;

    switch (nLanguageType) {
    case ENGLISH:
        LanguageTranslator.load(":/system/Resources/translation_en.qm");
        break;
    case CHINESE:
        LanguageTranslator.load(":/system/Resources/translation_ch.qm");
        break;
    default:
        break;
    }
    qApp->installTranslator(&LanguageTranslator);

    QApplication::setQuitOnLastWindowClosed(false);
    QMessageBox messageBox(QMessageBox::NoIcon,
                               tr("Restore default settings"), tr("Do you want to restore the default settings?"),
                               QMessageBox::Yes | QMessageBox::No, NULL);
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setButtonText(QMessageBox::Yes, QString(tr("Yes")));
    messageBox.setButtonText(QMessageBox::No, QString(tr("No")));
    int result=messageBox.exec();
    switch (result)
    {
    case QMessageBox::Yes:
        ui->sliderSpotLight->setValue(100);
        ui->sliderLasterPen->setValue(15);
        ui->sliderWatordrop->setValue(15);
        *mp_colorSpotlight=QColor(0, 0, 0, 80);
        *mp_colorLasterpen=QColor(255, 0, 0, 80);
        *mp_colorFindMouse=QColor(255, 120, 0, 150);
        showColorButton();
        m_SpotlightShortcutKey->setStyleSheet("color:black;");
        m_SpotlightShortcutKey->setText("Ctrl+Shift+S");
        m_ReadmodeShortcutKey->setStyleSheet("color:black;");
        m_ReadmodeShortcutKey->setText("Ctrl+Shift+A");
        m_LasterpenShortcutKey->setStyleSheet("color:black;");
        m_LasterpenShortcutKey->setText("Ctrl+Shift+L");
        m_FindMouseShortcutKey->setStyleSheet("color:black;");
        m_FindMouseShortcutKey->setText("Ctrl+Shift+F");
        m_ScreenshotShortcutKey->setStyleSheet("color:black;");
        m_ScreenshotShortcutKey->setText("Ctrl+Shift+D");
        m_MagnifyingShortcutKey->setStyleSheet("color:black;");
        m_MagnifyingShortcutKey->setText("Ctrl+Shift+M");
        break;
    case QMessageBox::No:
        break;
    default:
        break;
    }
}

void QSpotlightSetting::close()
{
    this->deleteLater();
}




void QSpotlightSetting::setSigName(QVector<QString> rvtStringDeviceSN)
{
//    if(rvtStringDeviceSN.size()<6)
//    {
//        SignalComboBox->setEnabled(false);
//        return;
//    }
//    else
//        SignalComboBox->setEnabled(true);
    //SignalComboBox->clear();
//    int n=0;
//    for(int i=0;i<rvtStringDeviceSN.size();i+=2)
//    {
//         SignalComboBox->addItem(QString("%1. ").arg(n)+rvtStringDeviceSN.at(i));
//         n++;
//    }
//    SignalComboBox->setCurrentText(" ");
}

void QSpotlightSetting::setLanguageType(int nIndex)
{
    QTranslator LanguageTranslator;

    switch (nIndex) {
    case ENGLISH:
        LanguageTranslator.load(":/system/Resources/translation_en.qm");
        break;
    case CHINESE:
        LanguageTranslator.load(":/system/Resources/translation_ch.qm");
        break;
    default:
        break;
    }
    qApp->installTranslator(&LanguageTranslator);
    ReTranslateUi(nIndex);
    //emit languageKeyPress(nLanguageType);
    //g_nLanguageType=nLanguageType;
}

int QSpotlightSetting::getReadModeSignal()
{
    if(ui->radioButtonLeft->isChecked())
        return 0;

    if(ui->radioButtonRight->isChecked())
        return 1;

    if(ui->radioButtonNormal->isChecked())
        return 2;

    return 0;
}

void QSpotlightSetting::setLanguage()
{
    int nLanguageType=ui->LanguagecomboBox->currentIndex();
    QTranslator LanguageTranslator;

    switch (nLanguageType) {
    case ENGLISH:
        LanguageTranslator.load(":/system/Resources/translation_en.qm");
        break;
    case CHINESE:
        LanguageTranslator.load(":/system/Resources/translation_ch.qm");
        break;
    default:
        break;
    }
    qApp->installTranslator(&LanguageTranslator);    
    ReTranslateUi(nLanguageType);
    emit languageKeyPress(nLanguageType);
    g_nLanguageType=nLanguageType;
}

void QSpotlightSetting::setShutcutHotKeyFail(EmDesktopModeType emType)
{
    QString steText;
    switch (emType) {

    case DESKTOP_MODE_SPOLIGHT:
        m_SpotlightShortcutKey->setStyleSheet("color:red;");
        break;
    case  DESKTOP_MODE_ACTIVE:
        m_ReadmodeShortcutKey->setStyleSheet("color:red;");
        break;

    case DESKTOP_MODE_LASERPEN:
        m_LasterpenShortcutKey->setStyleSheet("color:red;");
        break;
    case  DESKTOP_MODE_WATORDROP:
        m_FindMouseShortcutKey->setStyleSheet("color:red;");
        break;
    case  DESKTOP_MODE_SCREENSHOT:
        m_ScreenshotShortcutKey->setStyleSheet("color:red;");
        break;
    case  DESKTOP_MODE_MAGNIFYING:
        m_MagnifyingShortcutKey->setStyleSheet("color:red;");
        break;
    case DESKTOP_MODE_NULL:
    default:
        return ;
    }
}




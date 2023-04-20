#include "basicluminance_baseline_i.h"
#include "ui_basicluminance_baseline_i.h"

BasicLuminance_Baseline_I::BasicLuminance_Baseline_I(QWidget *parent) :
    BasicDocument(parent),
    ui(new Ui::BasicLuminance_Baseline_I)
{
    ui->setupUi(this);
     ui->BasicLum_comboBox->clear();
    ui->BasicLum_comboBox->addItems(g_strListResult);
    mp_GroupAmbient=new QButtonGroup(this);
    mp_GroupAmbient->addButton(ui->radioLamb,0);
    mp_GroupAmbient->addButton(ui->radioIllminance,1);
    ui->radioLamb->setChecked(true);

    connect(ui->llluminanceE0_lineEdit,SIGNAL(textEdited(QString)),this,SLOT(editIIluminanceE0(QString)));
    connect(ui->RD_lineEdit,SIGNAL(textEdited(QString)),this,SLOT(editDiffusionCoefficient(QString)));
    connect(ui->Labm_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(editLamb(QString)));
}

BasicLuminance_Baseline_I::~BasicLuminance_Baseline_I()
{
    delete ui;
}

void BasicLuminance_Baseline_I::ui_init()
{
        ui->llluminanceE0_lineEdit->clear();
        ui->Dateils_textEdit->setText(tr("Ambient luminance (Lamb): Method A: measured\
                                         in the center of the display, all displays \
                                         switched off. Method B: calculated from E0."));
        ui->RD_lineEdit->clear();
        ui->Labm_lineEdit->clear();
        ui->Labm_lineEdit->setEnabled(false);
        ui->L_min_lineEdit->clear();
        ui->L_max_lineEdit->setEnabled(false);
        ui->Lmin_lineEdit->setText("0.0000");
        ui->Lmin_lineEdit->setEnabled(false);
        ui->Lmax_lineEdit->setText("0.0000");
        ui->Lmax_lineEdit->setEnabled(false);      
        ui->LumRatio_lineEdit->setText("0.0000");
        ui->LumRatio_lineEdit->setEnabled(false);
        ui->SafetyFactor_lineEdit->setText("0.0000");
        ui->SafetyFactor_lineEdit->setEnabled(false);
        ui->BasicLum_comboBox->setCurrentIndex(0);
}

Basic_Luminance_Data BasicLuminance_Baseline_I::getData()
{


    double db_ambient=0;
    if(mp_GroupAmbient->checkedId()==0)
    {
        db_ambient=ui->Labm_lineEdit->text().toDouble();

    }
    else
    {
        db_ambient=ui->llluminanceE0_lineEdit->text().toDouble();
        db_ambient*=ui->RD_lineEdit->text().toDouble();

    }
    ui->Labm_lineEdit->setText(QString::number(db_ambient,'f',6));
    Basic_Luminance_Data BasicLuminanceInfo;
    BasicLuminanceInfo.llluminanceE0=ui->llluminanceE0_lineEdit->text().toDouble();
    BasicLuminanceInfo.details=ui->Dateils_textEdit->toPlainText();
    BasicLuminanceInfo.DiffusionCoefficient=ui->RD_lineEdit->text().toDouble();
    BasicLuminanceInfo.Lamb=ui->Labm_lineEdit->text().toDouble();
    BasicLuminanceInfo.DisplayLuminanceMin=ui->Lmin_lineEdit->text().toDouble();
    BasicLuminanceInfo.DisplayLuminanceMax=ui->Lmax_lineEdit->text().toDouble();
    BasicLuminanceInfo.BasicLuminanceIndex=ui->BasicLum_comboBox->currentIndex();
    BasicLuminanceInfo.AmbientType=mp_GroupAmbient->checkedId();



    return BasicLuminanceInfo;
}
void  BasicLuminance_Baseline_I::initialOtherValue()
{
    double db_ambient=0;
    if(mp_GroupAmbient->checkedId()==0)
    {
        db_ambient=ui->Labm_lineEdit->text().toDouble();

    }
    else
    {
        db_ambient=ui->llluminanceE0_lineEdit->text().toDouble();
        db_ambient*=ui->RD_lineEdit->text().toDouble();

    }

    Basic_Luminance_Data basic_lumin=getData();
    ui->L_min_lineEdit->setText(QString::number(basic_lumin.DisplayLuminanceMin+db_ambient,'f',2));
    ui->L_max_lineEdit->setText(QString::number(basic_lumin.DisplayLuminanceMax+db_ambient,'f',2));
    if(basic_lumin.DisplayLuminanceMin+db_ambient>0.001)
    {
    ui->LumRatio_lineEdit->setText(QString::number((basic_lumin.DisplayLuminanceMax+db_ambient)/(basic_lumin.DisplayLuminanceMin+db_ambient),'f',4));
    ui->SafetyFactor_lineEdit->setText(QString::number(db_ambient/basic_lumin.DisplayLuminanceMin,'f',4));
    }
    else {
        ui->LumRatio_lineEdit->setText("");
        ui->SafetyFactor_lineEdit->setText("");

    }
}
void BasicLuminance_Baseline_I::setData(Basic_Luminance_Data *BasicLuminanceInfo,EmReportQaType  ReportQaType)
{
    ui->llluminanceE0_lineEdit->setText(QString::number(BasicLuminanceInfo->llluminanceE0,'f',2));
    ui->Dateils_textEdit->setText(BasicLuminanceInfo->details);
    ui->RD_lineEdit->setText(QString::number(BasicLuminanceInfo->DiffusionCoefficient,'f',6));
    ui->Labm_lineEdit->setText(QString::number(BasicLuminanceInfo->Lamb,'f',4));

    ui->Lmin_lineEdit->setText(QString::number(BasicLuminanceInfo->DisplayLuminanceMin,'f',3));
    ui->Lmax_lineEdit->setText(QString::number(BasicLuminanceInfo->DisplayLuminanceMax,'f',3));
    ui->BasicLum_comboBox->setCurrentIndex(BasicLuminanceInfo->BasicLuminanceIndex);
    if(mp_GroupAmbient->button(BasicLuminanceInfo->AmbientType)!=NULL)
       mp_GroupAmbient->button(BasicLuminanceInfo->AmbientType)->setChecked(true);;

    switch (ReportQaType) {
    case QA_ACCEPTANCE:
    case QA_ACCEPTANCE_NEW:
        ui->labelRequirements->setText(tr("Lmax>=170.0 r'>=250.0 a<0.4"));
        break;
    case QA_CONSTANCY:
    case QA_CONSTANCY_NEW:
        ui->labelRequirements->setText(tr("r'>=250.0 a<0.4"));
        break;
    default:
        break;
    }
    initialOtherValue();
    getQaResult(getDocument()->CheckCondition);
    return;
}
bool BasicLuminance_Baseline_I::getQaResult(StQaCheckCondition &stQaCondition)
{
    if(!stQaCondition.checkDataStatus())
        return false;
    Basic_Luminance_Data BasicLuminanceInfo=getData();
     ui->BasicLum_comboBox->setCurrentIndex(2);
    if( ui->LumRatio_lineEdit->text().toDouble()<stQaCondition.dbContrast)
        return false;
    if( ui->SafetyFactor_lineEdit->text().toDouble()>=stQaCondition.dbSafeCoefficient)
        return false;
    if( ui->L_max_lineEdit->text().toDouble()<stQaCondition.dbLuminaceMax)
        return false;

 ui->BasicLum_comboBox->setCurrentIndex(1);
 return true;
}

void BasicLuminance_Baseline_I::editIIluminanceE0(QString strE0)
{
    double db_ambient=0;
    if(mp_GroupAmbient->checkedId()==1)
    {
        db_ambient=strE0.toDouble();
        db_ambient*=ui->RD_lineEdit->text().toDouble();
        ui->Labm_lineEdit->setText(QString::number(db_ambient,'f',6));
    }
}

void BasicLuminance_Baseline_I::editDiffusionCoefficient(QString strRD)
{
    double db_ambient=0;
    if(mp_GroupAmbient->checkedId()==1)
    {
        db_ambient=ui->llluminanceE0_lineEdit->text().toDouble();
        db_ambient*=strRD.toDouble();
        ui->Labm_lineEdit->setText(QString::number(db_ambient,'f',6));
    }
}

void BasicLuminance_Baseline_I::editLamb(QString strLamb)
{
    double db_ambient=strLamb.toDouble();
    initialOtherValue();
    emit changedLamb(db_ambient);
}

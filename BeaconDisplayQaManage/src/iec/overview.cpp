#include "overview.h"
#include<QDebug>
#include<QGridLayout>
#include<QHBoxLayout>
#include<QVBoxLayout>

Overview::Overview(QWidget *parent) :  BasicDocument(parent)
{
    ui_layout();
}

void Overview::ui_layout()
{
        QString str_lable[]={""
                             ,tr("Visual evaluation:")
                             , tr("Basic luminance:")
                             , tr("Luinance deviation:")
                             ,tr("Luminance response:")}  ;

        p_formLayout=new QFormLayout;
        for(int i=0;i<5;i++)
         {
            p_coutom_lable[i]=new My_Coutom_Lable(this);
            p_Label[i]=new QLabel(this);
            if(i==0)
               p_coutom_lable[i]->text=QString("<b>%1</b>").arg(tr("Display 1"));
            else
               p_coutom_lable[i]->text=QString("<b>%1</b>").arg(tr("in test"));

               p_coutom_lable[i]->nIndex=i;

            p_coutom_lable[i]->setText(p_coutom_lable[i]->text);
            p_Label[i]->setText(QString("<b>%1</b>").arg(str_lable[i]));
            p_formLayout->addRow(p_Label[i],p_coutom_lable[i]);
            connect(p_coutom_lable[i],SIGNAL(send_click_signal(int)),this,SIGNAL(send_click_signal(int)));
         }
         p_formLayout->setSpacing(20);
         p_formLayout->setLabelAlignment(Qt::AlignRight);


         QHBoxLayout *p_combobox_layout=new QHBoxLayout;
         Overall_Test_Result_Box=new QComboBox(this);
         Overall_Test_Result_Box->addItems(g_strListResult);
         p_combobox_layout->addWidget(Overall_Test_Result_Box);
         p_combobox_layout->addStretch();
         p_formLayout->addRow(tr("<b>Overall test result:</b>"),p_combobox_layout);

         Test_Comment_TextEdit=new QTextEdit(this);
      //   Test_Comment_TextEdit->setGeometry(220,425,500,100);
         Test_Comment_TextEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
         p_formLayout->addRow(tr("<b>Reason comment:</b>"),Test_Comment_TextEdit);

       //  p_formLayout->setVerticalSpacing(30);
         p_formLayout->setMargin(60);
         setLayout(p_formLayout);

}


void Overview::resizeEvent(QResizeEvent *event)
{
   // Line1->setGeometry(5,270,this->width()-5,2);
}

StQaResult Overview::GetData()
{
    StQaResult OverviewInfo;
    OverviewInfo.strResult=Overall_Test_Result_Box->currentText();
   // OverviewInfo.AutoTestCommentIndex=Auto_Test_Comment_Box->currentIndex();
    OverviewInfo.strReason=Test_Comment_TextEdit->toPlainText();
    return OverviewInfo;
}

void Overview::SetData(StQaResult *OverviewInfo)
{
    updatePageContent();
    Overall_Test_Result_Box->setCurrentText(OverviewInfo->strResult);
    Test_Comment_TextEdit->setText( OverviewInfo->strReason);

    return;
}
bool Overview::getQaResult(StQaCheckCondition &stQaCondition)
{
    if(!stQaCondition.checkDataStatus())
        return false;

    return true;
}

void Overview::updatePageContent()
{
    p_coutom_lable[INDEX_LUMINANCE_DEVIATION]->setHidden(true);
    p_Label[INDEX_LUMINANCE_DEVIATION]->setHidden(true);
    p_formLayout->removeWidget(p_Label[INDEX_LUMINANCE_DEVIATION]);
    p_formLayout->removeWidget(p_coutom_lable[INDEX_LUMINANCE_DEVIATION]);
    StIecReport* p_iec_report=getDocument();
    switch (p_iec_report->ReportQaType)
    {
    case QA_ACCEPTANCE:
    case QA_ACCEPTANCE_NEW:
        p_formLayout->insertRow(INDEX_LUMINANCE_DEVIATION,p_Label[INDEX_LUMINANCE_DEVIATION],p_coutom_lable[INDEX_LUMINANCE_DEVIATION]);
        p_coutom_lable[INDEX_LUMINANCE_DEVIATION]->setHidden(false);
        p_Label[INDEX_LUMINANCE_DEVIATION]->setHidden(false);
        break;
    }
}

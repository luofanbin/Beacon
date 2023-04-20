#include "qtg18result.h"
#include"qwidget.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include<QPushButton>
#include<QStackedLayout>
#include<QStackedWidget>
#include<QFormLayout>
#include "userdefine.h"
QTg18Result::QTg18Result( EmTg18Type emType,QWidget *parent) :m_emTgImageType(emType),QWidget(parent),m_blAutoTestLN(false)
{

parent=this;
    QString str_name[QA_TG18_END];

    str_name[QA_TG18_OIQ_NORMAL]=QString(tr("Overall image quality"));

#ifdef USG_QA_TG18_MP
           str_name[QA_TG18_MP]=  QString(tr( "ALL grayscales are visible and distinguishable"));//MP
#endif
                          str_name[QA_TG18_CT]= QString( tr("All squares and half moons are visible"));//CT
                          str_name[QA_TG18_UN80]=QString( tr("Homogeneous gray without dark or bright shades"));//un80
                          str_name[QA_TG18_UN10]=QString( tr("Homogeneous gray without changes in colour    "));//un80
                          str_name[QA_TG18_CHEST]=QString( tr("Clinical evaluation for the TG18-CH,TG-18-KN"));//un80
                          str_name[QA_TG18_UN80_CONSTANCY]=QString( tr("Look for non-uniformities"));//un80
    QStringList str_list= tr("- -,Ok,Failed").simplified().split(",");

    QString str_name_uniform[9]={tr("top left"),
                                tr("top mid"),
                                tr("top right"),
                                tr("mid left"),
                                 tr("center"),
                                tr("mid right"),
                                tr("bottom left"),
                                tr("bottom mid"),
                                tr("bottom right")} ;
    switch (m_emTgImageType) 
    {
    case QA_TG18_OIQ_NORMAL:
   #ifdef USG_QA_TG18_MP
    case QA_TG18_MP:
   #endif
    case QA_TG18_CT:
    case QA_TG18_UN80:
    case QA_TG18_CHEST:
    case  QA_TG18_UN80_CONSTANCY:
    {
        QLabel *p_lable=new QLabel();
        p_lable->setText(str_name[m_emTgImageType]);
        mp_ComboBoxResult[0]=new QComboBox(parent);
        mp_ComboBoxResult[0]->addItems(str_list);
          mp_ComboBoxResult[0]->installEventFilter(parent);
          if(m_emTgImageType!=QA_TG18_UN80)
          {
              QHBoxLayout *main_laout=new QHBoxLayout;
              main_laout->addStretch();
              main_laout->addWidget(p_lable);
              main_laout->addWidget(mp_ComboBoxResult[0]);
              main_laout->addStretch();
              this->setLayout(main_laout);
          }
          else {
              QLabel *p_lable2=new QLabel();
              p_lable2->setText(str_name[m_emTgImageType+1]);
              mp_ComboBoxResult[1]=new QComboBox(parent);
              mp_ComboBoxResult[1]->addItems(str_list);
                mp_ComboBoxResult[1]->installEventFilter(parent);

              QHBoxLayout *layout_left=new QHBoxLayout;
              QHBoxLayout *layout_right=new QHBoxLayout;
              layout_left->addWidget(p_lable);
              layout_right->addWidget(p_lable2);
              layout_left->addWidget(mp_ComboBoxResult[0]);
              layout_right->addWidget(mp_ComboBoxResult[1]);
              QVBoxLayout *main_right=new QVBoxLayout;
              //main_right->addStretch();
              main_right->addLayout(layout_left);
              main_right->addLayout(layout_right);
                main_right->setMargin(0);
              //main_right->addStretch();
              mp_LineEditData[0]=new QLineEdit();
              mp_LineEditData[1]=new QLineEdit();
              mp_LineEditData[0]->setFixedWidth(35);
               mp_LineEditData[1]->setFixedWidth(35);
              QLabel *p_lable3=new QLabel(tr("num type B pixel faults"));
              QLabel *p_lable4=new QLabel(tr("num type C pixel faults"));

               QVBoxLayout *main_left=new QVBoxLayout;
               QHBoxLayout *left_up=new QHBoxLayout;
               QHBoxLayout *right_up=new QHBoxLayout;
               //main_bottom->addStretch();
               left_up->addWidget(p_lable3);

               left_up->addWidget(mp_LineEditData[0]);

               right_up->addWidget(p_lable4);
               right_up->addWidget(mp_LineEditData[1]);
               //main_bottom->addStretch();
                //main_bottom->setMargin(0);
               main_left->setMargin(0);
               main_left->addLayout(left_up);
               main_left->addLayout(right_up);
              QHBoxLayout *main_laout=new QHBoxLayout;
             main_laout->setMargin(0);
             main_laout->addStretch();
              main_laout->addLayout(main_left);
               main_laout->addLayout(main_right);
               main_laout->addStretch();
              this->setLayout(main_laout);
          }
        
    }
     break;
     case QA_TG18_UN10:
        {

            mp_LineEditData[0]=new QLineEdit();
            mp_LineEditData[1]=new QLineEdit();
           mp_LineEditData[0]->setFixedWidth(35);
            mp_LineEditData[1]->setFixedWidth(35);
            QLabel *p_lable3=new QLabel(tr("num type A pixel faults"));
            QLabel *p_lable4=new QLabel(tr("num type C pixel faults"));

            QHBoxLayout *main_laout=new QHBoxLayout;
            main_laout->addStretch();
            main_laout->addWidget(p_lable3);
            main_laout->addWidget(mp_LineEditData[0]);
            main_laout->addWidget(p_lable4);
            main_laout->addWidget(mp_LineEditData[1]);
            main_laout->addStretch();

            this->setLayout(main_laout);
        }
 break;
    case QA_TG18_LN:
        {
            mp_stackItermLuminance=new  QStackedLayout;
            mp_sensorButton=new QPushButton(tr("Messure"));
            mp_sensorButton->setFixedHeight(20);
            connect(mp_sensorButton,SIGNAL(clicked()),SLOT(getSensorData()));
            mp_AutoRead=new QCheckBox ;
            mp_AutoRead->setText(tr("Auto Messure"));
            mp_AutoRead->setChecked(true);
            for (int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
            {
                QWidget *p_widget=new QWidget(this);
               // p_widget->show();
                mp_LineEditData[i]=new QLineEdit();
                mp_LineEditData[i]->setFixedWidth(90);
                mp_LineEditData[i]->setFixedHeight(20);
                mp_LineEditData[i+DICOM_GSDF_GRAYSCALE_NUMBER]=new QLineEdit();
                mp_LineEditData[i+DICOM_GSDF_GRAYSCALE_NUMBER]->setFixedWidth(90);
                mp_LineEditData[i+DICOM_GSDF_GRAYSCALE_NUMBER]->setFixedHeight(20);
                mp_LineEditData[i+2*DICOM_GSDF_GRAYSCALE_NUMBER]=new QLineEdit();
                mp_LineEditData[i+2*DICOM_GSDF_GRAYSCALE_NUMBER]->setFixedWidth(90);
                mp_LineEditData[i+2*DICOM_GSDF_GRAYSCALE_NUMBER]->setFixedHeight(20);
                //QPushButton *button_sensor=new QPushButton(tr("Messure"));
                QLabel *p_lable=new QLabel(tr("method near L"));
                QString str_lable=QString(tr("method near L%1 lv:")).arg(i+1);
                p_lable->setText(str_lable);
                QLabel *p_lableX=new QLabel(tr("x:"));
                QLabel *p_lableY=new QLabel(tr("y:"));
                p_lable->setAlignment(Qt::AlignRight);
                p_lableX->setAlignment(Qt::AlignRight);
                p_lableY->setAlignment(Qt::AlignRight);
                QVBoxLayout *vertcal_laout=new QVBoxLayout;
                QHBoxLayout *ln_laout=new QHBoxLayout;
                ln_laout->addWidget(p_lable);
                ln_laout->addWidget(mp_LineEditData[i]);
                QHBoxLayout *x_laout=new QHBoxLayout;
                x_laout->addWidget(p_lableX);
                x_laout->addWidget(mp_LineEditData[i+DICOM_GSDF_GRAYSCALE_NUMBER]);
                QHBoxLayout *y_laout=new QHBoxLayout;
                y_laout->addWidget(p_lableY);
                y_laout->addWidget(mp_LineEditData[i+2*DICOM_GSDF_GRAYSCALE_NUMBER]);
                vertcal_laout->addLayout(ln_laout);
                vertcal_laout->addLayout(x_laout);
                vertcal_laout->addLayout(y_laout);

//                QHBoxLayout *main_laout=new QHBoxLayout;
//                vertcal_laout->setMargin(0);
//                main_laout->addStretch();
//                main_laout->addLayout(vertcal_laout);
//                main_laout->addWidget(button_sensor);

//                main_laout->addStretch();
//                main_laout->setMargin(0);
                p_widget->setLayout(vertcal_laout);
               mp_stackItermLuminance->addWidget(p_widget);
              //connect(button_sensor,SIGNAL(clicked()),SLOT(getSensorData()));
            }
            QVBoxLayout *vertical_layout_test=new QVBoxLayout;
            vertical_layout_test->addWidget(mp_sensorButton);
            vertical_layout_test->addWidget(mp_AutoRead);

            QHBoxLayout *main_layout_test=new QHBoxLayout;
            main_layout_test->addStretch();
            main_layout_test->addLayout(mp_stackItermLuminance);
           main_layout_test->addLayout(vertical_layout_test);
           main_layout_test->addStretch();
           main_layout_test->setMargin(0);
            this->setLayout(main_layout_test);
            mp_stackItermLuminance->setCurrentIndex(0);

        }
        break;
     case QA_TG18_UNL80:
     case QA_TG18_UNL10:
            {
                mp_stackItermLuminance=new  QStackedLayout;
                for (int i=0;i<9;i++) {
                    QWidget *p_widget=new QWidget(this);
                    // p_widget->show();
                    mp_LineEditData[i]=new QLineEdit();
                    mp_LineEditData[i]->setFixedWidth(90);
                    mp_LineEditData[i]->setFixedHeight(20);
                    mp_LineEditData[i+DICOM_GSDF_GRAYSCALE_NUMBER]=new QLineEdit();
                    mp_LineEditData[i+DICOM_GSDF_GRAYSCALE_NUMBER]->setFixedWidth(90);
                    mp_LineEditData[i+DICOM_GSDF_GRAYSCALE_NUMBER]->setFixedHeight(20);
                    mp_LineEditData[i+2*DICOM_GSDF_GRAYSCALE_NUMBER]=new QLineEdit();
                    mp_LineEditData[i+2*DICOM_GSDF_GRAYSCALE_NUMBER]->setFixedWidth(90);
                    mp_LineEditData[i+2*DICOM_GSDF_GRAYSCALE_NUMBER]->setFixedHeight(20);
                    QLabel *p_lable=new QLabel(tr("method near L"));
                    QPushButton *button_sensor=new QPushButton(tr("Messure"));
                    button_sensor->setFixedWidth(75);
                    button_sensor->setFixedHeight(20);
                    p_lable->setText(tr("Method ")+str_name_uniform[i]+tr(" lv:"));
                    QLabel *p_lableX=new QLabel(tr("x:"));
                    QLabel *p_lableY=new QLabel(tr("y:"));
                    QLabel *p_lable1=new QLabel();
                    QLabel *p_lable2=new QLabel();
                    p_lable1->setFixedWidth(75);
                    p_lable1->setFixedHeight(20);
                    p_lable2->setFixedWidth(75);
                    p_lable2->setFixedHeight(20);

                    p_lable->setAlignment(Qt::AlignRight);
                    p_lableX->setAlignment(Qt::AlignRight);
                    p_lableY->setAlignment(Qt::AlignRight);

                    QVBoxLayout *vertcal_laout=new QVBoxLayout;
                    QHBoxLayout *ln_laout=new QHBoxLayout;
                    ln_laout->addWidget(p_lable);
                    ln_laout->addWidget(mp_LineEditData[i]);
                    ln_laout->addWidget(button_sensor);
                    QHBoxLayout *x_laout=new QHBoxLayout;
                    x_laout->addWidget(p_lableX);
                    x_laout->addWidget(mp_LineEditData[i+DICOM_GSDF_GRAYSCALE_NUMBER]);
                    x_laout->addWidget(p_lable1);
                    QHBoxLayout *y_laout=new QHBoxLayout;
                    y_laout->addWidget(p_lableY);
                    y_laout->addWidget(mp_LineEditData[i+2*DICOM_GSDF_GRAYSCALE_NUMBER]);
                    y_laout->addWidget(p_lable2);
                    vertcal_laout->addLayout(ln_laout);
                    vertcal_laout->addLayout(x_laout);
                    vertcal_laout->addLayout(y_laout);

                    QHBoxLayout *main_laout=new QHBoxLayout;
                    main_laout->addStretch();
                    main_laout->addLayout(vertcal_laout);
//                    main_laout->addWidget(mp_LineEditData[i]);
//                    main_laout->addWidget(mp_LineEditData[i+DICOM_GSDF_GRAYSCALE_NUMBER]);
//                    main_laout->addWidget(mp_LineEditData[i+2*DICOM_GSDF_GRAYSCALE_NUMBER]);
//                     main_laout->addWidget(button_sensor);
                    main_laout->addStretch();
                    p_widget->setLayout(main_laout);

                    mp_stackItermLuminance->addWidget(p_widget);

                     connect(button_sensor,SIGNAL(clicked()),SLOT(getSensorData()));
                }

                this->setLayout(mp_stackItermLuminance);
                 mp_stackItermLuminance->setCurrentIndex(0);

            }
        break;
        case QA_TG18_ANG:
            {
             QLabel *p_lable[9];
             QFormLayout *p_formlayout[3];
             p_formlayout[0]=new QFormLayout;
             p_formlayout[1]=new QFormLayout;
             p_formlayout[2]=new QFormLayout;
            for (int i=0;i<9;i++)
                {

                    mp_LineEditData[i]=new QLineEdit();
                    mp_LineEditData[i]->setFixedWidth(75);
                    p_lable[i]=new QLabel(str_name_uniform[i]);
                  p_formlayout[i%3]->addRow( p_lable[i],mp_LineEditData[i]);

                }

          QHBoxLayout *main_laout=new QHBoxLayout;
          main_laout->addLayout(p_formlayout[0]);
          main_laout->addLayout(p_formlayout[1]);
          main_laout->addLayout(p_formlayout[2]);
          main_laout->setMargin(0);
          this->setLayout(main_laout);
            }
          break;
    default:
        break;

    }



}
bool QTg18Result::setStackItermIndex(bool blForward)
{
    int n_step=1;
    if(QA_TG18_LN<=m_emTgImageType && m_emTgImageType<=QA_TG18_UNL10)
    {
        //代表5点中的，0,2,4,6,8
        if(!m_blNinePoint)
        {
            if(QA_TG18_UNL80==m_emTgImageType ||QA_TG18_UNL10==m_emTgImageType)
                n_step=2;
        }

        if(blForward)
        {
            if(mp_stackItermLuminance->currentIndex()==(mp_stackItermLuminance->count()-1))
                return false;

            mp_stackItermLuminance->setCurrentIndex(mp_stackItermLuminance->currentIndex()+n_step);
        }
        else
        {
            if(mp_stackItermLuminance->currentIndex()==0)
                return false;
            mp_stackItermLuminance->setCurrentIndex(mp_stackItermLuminance->currentIndex()-n_step);

        }

        return true;

    }
    else
        return false;


}
 int QTg18Result::getStackItermCurrent()
{
     if(QA_TG18_LN<=m_emTgImageType && m_emTgImageType<=QA_TG18_UNL10)
         return mp_stackItermLuminance->currentIndex();
     return -1;

 }
  bool  QTg18Result::getTg18Data(StTg18Result &stResult)
 {
      if(stResult.emType!=m_emTgImageType)
          return false;


      switch (stResult.emType)
      {
           case QA_TG18_OIQ_NORMAL:
           case QA_TG18_CT:
           case QA_TG18_CHEST:
         case QA_TG18_UN80_CONSTANCY:
              {
               stResult.dataResult.nResult[0]=mp_ComboBoxResult[0]->currentIndex();
              }
             break;
          case QA_TG18_UN80:
              {
              stResult.dataResult.nResult[0]=mp_ComboBoxResult[0]->currentIndex();
              stResult.dataResult.nResult[1]=mp_ComboBoxResult[1]->currentIndex();
              stResult.dataResult.nResult[2]=mp_LineEditData[0]->text().toInt();
              stResult.dataResult.nResult[3]=mp_LineEditData[1]->text().toInt();
                         }
          break;
          case QA_TG18_UN10:
             {
              stResult.dataResult.nResult[0]=mp_LineEditData[0]->text().toInt();
              stResult.dataResult.nResult[1]=mp_LineEditData[1]->text().toInt();
             }
          break;
          case QA_TG18_LN:
             {
              for (int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
              {
                  stResult.dataResult.dbLuminace[i]=mp_LineEditData[i]->text().toDouble();
                  stResult.dataResult.dbLuminace[i+DICOM_GSDF_GRAYSCALE_NUMBER]=mp_LineEditData[i+DICOM_GSDF_GRAYSCALE_NUMBER]->text().toDouble();
                  stResult.dataResult.dbLuminace[i+2*DICOM_GSDF_GRAYSCALE_NUMBER]=mp_LineEditData[i+2*DICOM_GSDF_GRAYSCALE_NUMBER]->text().toDouble();
              }

             }
          break;
          case QA_TG18_UNL80:
            {
              for (int i=0;i<9;i++)
              {
                  stResult.dataResult.dbLuminace[i]=mp_LineEditData[i]->text().toDouble();
                  stResult.dataResult.dbLuminace[i+DICOM_GSDF_GRAYSCALE_NUMBER]=mp_LineEditData[i+DICOM_GSDF_GRAYSCALE_NUMBER]->text().toDouble();
                  stResult.dataResult.dbLuminace[i+2*DICOM_GSDF_GRAYSCALE_NUMBER]=mp_LineEditData[i+2*DICOM_GSDF_GRAYSCALE_NUMBER]->text().toDouble();
              }


            }
          break;
          case QA_TG18_ANG:
              {
                  for (int i=0;i<9;i++)
                  {
                      stResult.dataResult.nResult[i]=mp_LineEditData[i]->text().toInt();
                  }
              }
           break;
          defalt:
              return false;
              break;
        }
        return true;
  }

  void QTg18Result::getSensorData()
  {
      StCieLvxy stLvxy;
      stLvxy.dbLumin=0;
emit testNextPosition(TEST_HIDE);
  Sleep(200);
  Sleep(100);
      emit getSensorData(stLvxy);
      emit testNextPosition(TEST_SHOW);
      int n_iterm=mp_stackItermLuminance->currentIndex();
      double db_coordinate_u,db_coordinate_v;
      if(n_iterm>=0)
      {
          db_coordinate_u=4*stLvxy.dbX/(12*stLvxy.dbY-2*stLvxy.dbX+3);
          db_coordinate_v=9*stLvxy.dbY/(12*stLvxy.dbY-2*stLvxy.dbX+3);
          mp_LineEditData[n_iterm]->setText(QString::number(stLvxy.dbLumin, 'f', 4));
          mp_LineEditData[n_iterm+DICOM_GSDF_GRAYSCALE_NUMBER]->setText(QString::number(db_coordinate_u, 'f', 4));
          mp_LineEditData[n_iterm+2*DICOM_GSDF_GRAYSCALE_NUMBER]->setText(QString::number(db_coordinate_v, 'f', 4));
      }
      Sleep(500);

 emit testNextPosition(TEST_NEXT);
if(m_emTgImageType==QA_TG18_LN && stLvxy.dbLumin>0.0001 )
{
    if(mp_AutoRead->isChecked() && n_iterm<17)
         getSensorData();
}

  }
  void QTg18Result::Sleep(int msec)
  {
      QTime dieTime = QTime::currentTime().addMSecs(msec);
      while( QTime::currentTime() < dieTime )
          QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
  }

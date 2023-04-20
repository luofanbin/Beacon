#include "AutoHideWidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include<QLabel>
#include <QStyle>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QApplication>
#include <QDesktopWidget>
#include<QStackedLayout>
#include <QtAlgorithms>
#include<QDebug>
AutoHideWidget::AutoHideWidget(int nDisplay,QWidget *parent)
    : QWidget(parent)
    , m_mouseMovePoint(0, 0)
    , m_bMousePressed(false)
    , m_enDriection(None)
    , m_bIsAutoHide(false)
      ,m_bShowAnimation(true)

     // ,m_PageControl(QDialogButtonBox::Cancel);
{
     this->setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint|Qt::FramelessWindowHint);
  //this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
       //   this->setWindowModality(Qt::WindowModal);
       //    this->setAttribute(Qt::WA_DeleteOnClose);
    m_PageControl.setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
   m_PageControl.button(QDialogButtonBox::Ok)->hide();





     mp_butForward=new QPushButton(">");
     mp_butBackward=new QPushButton("<");;
      m_PageControl.addButton(mp_butBackward,QDialogButtonBox::ActionRole);
     m_PageControl.addButton(mp_butForward,QDialogButtonBox::ActionRole);

      m_PageControl.setCenterButtons(true);
    QPoint pos = QWidget::mapToGlobal(this->pos()); //获取activeX窗口在桌面上的绝对位置
    QRect deskRt = QApplication::desktop()->screenGeometry(nDisplay);
    m_nDesktopWidth =deskRt.width();// QApplication::desktop()->width();
    m_nPositionY=deskRt.y();
    move(deskRt.topLeft());
    resize(m_nDesktopWidth, 50);
    init();

     //hideWidget();
     m_bIsAutoHide=true;
     checkButtonStatus();
     connect(&m_PageControl,SIGNAL(clicked(QAbstractButton*)),this,SLOT(ClieckButtonBox(QAbstractButton*)));
 //    connect(this ,SIGNAL(testNextPosition()),mp_butForward,SIGNAL(clicked()));
    //  resize(m_nDesktopWidth, 50);
}

AutoHideWidget::~AutoHideWidget()
{

}

void AutoHideWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(m_cBackgroundColor);
    painter.setPen(pen);
    painter.drawLine(rect().left(),rect().bottom(),rect().right(),rect().bottom());
}

void AutoHideWidget::init()
{
    m_pTitleWidget = new QWidget(this);
    m_pTitleWidget->setFixedHeight(120);
  //  m_pTitleWidget->setStyleSheet("background-color: #25A7E9;");
    m_pTitleWidget->installEventFilter(this);

    QHBoxLayout *pTitleLayout = new QHBoxLayout;
    QVBoxLayout *p_center_layout=new QVBoxLayout;

       mp_stackTg18Result=new QStackedLayout;
       for (int i=0;i<QA_TG18_END;i++)
       {
           mp_Tg18Result[i]=new QTg18Result((EmTg18Type)i,this);
           mp_Tg18Result[i]->installEventFilter(m_pTitleWidget);
           mp_stackTg18Result->addWidget(mp_Tg18Result[i]);
           connect( mp_Tg18Result[i],SIGNAL(getSensorData(StCieLvxy& )),this,SIGNAL(getSensorData(StCieLvxy& )));
           connect( mp_Tg18Result[i],SIGNAL(testNextPosition(int)),this,SLOT(testNextPosition(int)));

       }

    pTitleLayout->addStretch();
    p_center_layout->addLayout(mp_stackTg18Result);
    p_center_layout->addWidget(&m_PageControl);
    pTitleLayout->addLayout(p_center_layout);
   pTitleLayout->addStretch();
    m_pTitleWidget->setLayout(pTitleLayout);
    mp_stackTg18Result->setCurrentIndex(0);
     mp_butBackward->hide();

    QVBoxLayout *pMainlayout = new QVBoxLayout;

    pMainlayout->addWidget(m_pTitleWidget);

    this->setLayout(pMainlayout);
}

void AutoHideWidget::isAutoHide()
{
    QPoint pos = this->pos();
//qDebug()<<pos;
    m_bIsAutoHide = true;

  #if 0 //可以自动隐藏四周
    if (pos.x() < 2)
    {
        m_enDriection = Left;
    }
    else if (pos.y() < 2)
    {
        m_enDriection = Up;
    }
    else if (this->pos().x() + this->width() > m_nDesktopWidth - 2)
    {
        m_enDriection = Right;
    }
#else  //只允许停靠顶部
    if (pos.y() < 2)
        {
            m_enDriection = Left;
        }
#endif
    else
    {
        m_enDriection = None;
        m_bIsAutoHide = false;
    }
}

void AutoHideWidget::hideWidget()
{
//qDebug()<<"hide widget begin"<<this->rect();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    if(m_bShowAnimation)
        animation->setDuration(100);
    else
        animation->setDuration(0);
    animation->setStartValue(QRect(this->pos(), this->size()));

    QRect rcEnd;
    if (m_enDriection & Up)
    {
        rcEnd = QRect(this->x(),this->height() + 2, this->size().width(), this->rect().height());
    }
    else if (m_enDriection & Left)
    {
        rcEnd = QRect(-this->width() + 2, this->y(), this->size().width(), this->rect().height());
    }
    else if (m_enDriection & Right)
    {
        rcEnd = QRect(m_nDesktopWidth - 2, this->y(), this->size().width(), this->rect().height());
    }
   // resize(m_nDesktopWidth, 50);
    rcEnd = QRect(this->x(), m_nPositionY-this->height()+1, m_nDesktopWidth, 50);
    animation->setEndValue(rcEnd);
    animation->start();
    m_cBackgroundColor=QColor(0,0,0);
    update();
   // qDebug()<<"hide widget end"<<this->rect();
}

void AutoHideWidget::showWidget()
{
//qDebug()<<"show widget begin"<<this->rect();
    QPoint pos = this->pos();

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    if(m_bShowAnimation)
       animation->setDuration(100);
    else
        animation->setDuration(0);
    animation->setStartValue(QRect(pos, this->size()));

    QRect rcEnd;
    if (m_enDriection & Up)
    {
        rcEnd = QRect(this->x(), 0, this->size().width(), this->rect().height());
    }
    else if (m_enDriection & Left)
    {
        rcEnd = QRect(0, this->y(), this->size().width(), this->rect().height());
    }
    else if (m_enDriection & Right)
    {
        rcEnd = QRect(m_nDesktopWidth - this->width(),this->y(), this->size().width(), this->rect().height());
    }
   // rcEnd = QRect(m_nDesktopWidth - 2, this->y(), m_nDesktopWidth, 50);
  //  parentWidget()->x()
     rcEnd = QRect(this->x(), m_nPositionY, m_nDesktopWidth, 50);
  //  rcEnd = QRect(0, 0, 1360, 50);
    animation->setEndValue(rcEnd);
    animation->start();
    m_cBackgroundColor=QColor(220,220,220);
    update();
  //  qDebug()<<"show widget end "<<this->rect();
}

bool AutoHideWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (m_pTitleWidget == watched)
    {
        QMouseEvent *pMouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (pMouseEvent != NULL)
        {
/*
            if (pMouseEvent->type() == QEvent::MouseButtonPress)
            {
                if (pMouseEvent->button() == Qt::LeftButton)
                {
                    m_bMousePressed = true;
                    m_mouseMovePoint = pMouseEvent->pos();
                }
            }
            else if (m_bMousePressed && pMouseEvent->type() == QEvent::MouseMove)
            {
                if (!this->isMaximized())
                {
                    QPoint movePoint = pMouseEvent->globalPos();
                    this->move(movePoint - m_mouseMovePoint);
                }
            }
            else if (pMouseEvent->type() == QEvent::MouseButtonRelease)
            {
                m_bMousePressed = false;
            }
            */
        }
    }

    return QWidget::eventFilter(watched, event);
}

bool AutoHideWidget::event(QEvent *event)
{
//qDebug()<<"event widget begin"<<this->rect();
    if (m_bMousePressed && event->type() == QEvent::Move)
    {
        QMoveEvent *pMoveEvent = dynamic_cast<QMoveEvent *>(event);

        if (pMoveEvent != NULL)
        {
            QPoint pos = pMoveEvent->pos();
            if (pos.x() < 0)
            {
                pos.setX(0);
            }
            if (pos.y() < 0)
            {
                pos.setY(0);
            }
            if (pos.x() + this->width() > m_nDesktopWidth)
            {
                pos.setX(m_nDesktopWidth - this->width());
            }

            event->ignore();
            this->move(pos);
        }
    }
  //  qDebug()<<"event widget end "<<this->rect();
    return QWidget::event(event);
}

void AutoHideWidget::leaveEvent(QEvent *event)
{

  //  if(this->geometry().contains(this->mapFromGlobal(QCursor::pos())))
    if(this->geometry().contains(QCursor::pos()))
        return;
//qDebug()<<"leaveEvent"<<this->geometry()<<this->mapFromGlobal(QCursor::pos())<<QCursor::pos();
    isAutoHide();
    if (m_bIsAutoHide)
    {
        hideWidget();
    }
}

void AutoHideWidget::enterEvent(QEvent *event)
{
    //qDebug()<<"enterEvent"<<this->rect();
    if (m_bIsAutoHide)
    {
        showWidget();
    }
}
#include"QMessageBox"
void AutoHideWidget::checkButtonStatus()
{





      int  n_tg_type=mp_stackTg18Result->currentIndex();

  if(m_vectorTG18Item.size()!=1)
    {
      QVector<EmTg18Type>::iterator iterm_find=qFind(m_vectorTG18Item.begin(),m_vectorTG18Item.end(),(EmTg18Type)n_tg_type);

      if(iterm_find==m_vectorTG18Item.begin())
           mp_butBackward->hide();
      else
          mp_butBackward->show();


      mp_butForward->show();
     if(m_vectorTG18Item.end()-iterm_find<=1)
     {

         switch (n_tg_type) {
         case QA_TG18_UNL80:
             if(mp_Tg18Result[n_tg_type]->getStackItermCurrent()==8 )
                mp_butForward->hide();
             break;
         case QA_TG18_LN:
             if(mp_Tg18Result[n_tg_type]->getStackItermCurrent()==17)
                   mp_butForward->hide();
             break;
         default:
              mp_butForward->hide();
             break;

         }


     }

/*
       //  if(n_tg_type==QA_TG18_UNL10 )

         {
             if(mp_Tg18Result[n_tg_type]->getStackItermCurrent()==8)
                  mp_butForward->hide();
              else
                  mp_butForward->show();

         }
         */


    }else
  {
        mp_butForward->hide();
        mp_butBackward->hide();
      //  m_PageControl.button(QDialogButtonBox::Ok)->show();

        if(n_tg_type==QA_TG18_UNL80
            ||n_tg_type==QA_TG18_LN  )
        {
            mp_butForward->show();
            mp_butBackward->show();
             if(mp_Tg18Result[n_tg_type]->getStackItermCurrent()==0)
                mp_butBackward->hide();
             else if(mp_Tg18Result[n_tg_type]->getStackItermCurrent()==8 && n_tg_type==QA_TG18_UNL80)
                 mp_butForward->hide();
             else if(mp_Tg18Result[n_tg_type]->getStackItermCurrent()==17 && n_tg_type==QA_TG18_LN)
                 mp_butForward->hide();

        }


  }



  if(mp_butForward->isHidden())
      m_PageControl.button(QDialogButtonBox::Ok)->show();
  else
      m_PageControl.button(QDialogButtonBox::Ok)->hide();


}
void AutoHideWidget::ClieckButtonBox(QAbstractButton *button)
{
    if(button== m_PageControl.button(QDialogButtonBox::Cancel) )
    {
       // QRect rect_client(1920,0,1280,1024);
     //  setGeometry(rect_client);
       emit reportResult(false);
      //  QMessageBox::information(this, "INFORMATION","Cancel");
    }
    else if(button== m_PageControl.button(QDialogButtonBox::Ok))
    {
     emit reportResult(true);
    }
    int n_iterm_current=mp_stackTg18Result->currentIndex();

    if(QA_TG18_LN<=n_iterm_current && n_iterm_current<=QA_TG18_UNL10)
    {
        if((mp_Tg18Result[n_iterm_current]->setStackItermIndex(button== mp_butForward)) ||
            n_iterm_current==QA_TG18_UNL80 &&m_vectorTG18Item.size()==1)
        {
            emit changeTg18Type((EmTg18Type)n_iterm_current,mp_Tg18Result[n_iterm_current]->getStackItermCurrent());
            checkButtonStatus();
            return;
        }



    }
    int  n_tg_type=mp_stackTg18Result->currentIndex();


    QVector<EmTg18Type>::iterator iterm_find=qFind(m_vectorTG18Item.begin(),m_vectorTG18Item.end(),(EmTg18Type)n_tg_type);

    if(button== mp_butBackward ){

       if(iterm_find!=m_vectorTG18Item.begin())
           mp_stackTg18Result->setCurrentIndex(*--iterm_find);


    }
    if(button== mp_butForward ){


        if(m_vectorTG18Item.end()-iterm_find>1)
          mp_stackTg18Result->setCurrentIndex(*++iterm_find);



    }
    n_iterm_current=mp_stackTg18Result->currentIndex();
     emit changeTg18Type((EmTg18Type)n_iterm_current,0);
     checkButtonStatus();
}
void AutoHideWidget::initQaIterm(EmTg18Type emType,EmTg18MethodType emMethod)
{
    m_vectorTG18Item.clear();
    if(emMethod==QA_METHOD_SINGLE)
        m_vectorTG18Item.push_back(emType);

    else if (emMethod==QA_METHOD_ACCEPTANCE_VISIBLE ||emMethod==QA_METHOD_ACCEPTANCE_ALL)
    {

      m_vectorTG18Item.push_back(QA_TG18_OIQ_NORMAL);
    #ifdef USG_QA_TG18_MP
      m_vectorTG18Item.push_back(QA_TG18_MP);

    #endif
        m_vectorTG18Item.push_back(QA_TG18_CT);
        m_vectorTG18Item.push_back(QA_TG18_UN80);
        m_vectorTG18Item.push_back(QA_TG18_UN10);
        if(emMethod==QA_METHOD_ACCEPTANCE_ALL)
        {
         m_vectorTG18Item.push_back(QA_TG18_LN);
         m_vectorTG18Item.push_back(QA_TG18_UNL80);
         m_vectorTG18Item.push_back(QA_TG18_ANG);
        }


    } else if (emMethod== QA_METHOD_CONSTANCY_VISIBLE ||emMethod== QA_METHOD_CONSTANCY_ALL)
    {

      m_vectorTG18Item.push_back(QA_TG18_OIQ_NORMAL);

        m_vectorTG18Item.push_back(QA_TG18_UN80_CONSTANCY);
        if(emMethod==QA_METHOD_CONSTANCY_ALL)
        {
         m_vectorTG18Item.push_back(QA_TG18_LN);


        }


    }
    else if(emMethod==QA_METHOD_CLINICAL_ALL)
    {
        m_vectorTG18Item.push_back(QA_TG18_MAM01);
        m_vectorTG18Item.push_back(QA_TG18_MAM02);
        m_vectorTG18Item.push_back(QA_TG18_KNEE);
        m_vectorTG18Item.push_back(QA_TG18_CHEST);         
    }else if(emMethod==QA_METHOD_CLINICAL_PART)
    {
        m_vectorTG18Item.push_back(QA_TG18_KNEE);
        m_vectorTG18Item.push_back(QA_TG18_CHEST);
    }
    mp_stackTg18Result->setCurrentIndex(emType);
    checkButtonStatus();

}

 bool AutoHideWidget::getTg18Data(StTg18Result &stResult)
{

         if(stResult.emType<QA_TG18_END)
     {
             return mp_Tg18Result[stResult.emType]->getTg18Data(stResult);
     }

 }
 void AutoHideWidget::setPointNumber(bool blNinePoint)
 {

     mp_Tg18Result[QA_TG18_UNL80]->setPointNumber(blNinePoint);
      mp_Tg18Result[QA_TG18_UNL10]->setPointNumber(blNinePoint);
 }
 void AutoHideWidget::testNextPosition(int nType)
 {

    // QMessageBox::information(this, "INFORMATION","Cancel");
    switch (nType)
    {
    case QTg18Result::TEST_HIDE :
        m_bShowAnimation=false;
         hideWidget();
            break;
    case QTg18Result::TEST_SHOW :

        showWidget();
        m_bShowAnimation=true;
        break;
    case QTg18Result::TEST_NEXT :
        if(mp_butForward->isVisible())
            ClieckButtonBox(mp_butForward);
        break;

    }

 }

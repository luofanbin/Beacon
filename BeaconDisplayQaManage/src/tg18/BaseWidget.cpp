#include "BaseWidget.h"
#include <QDebug>

BaseWidget::BaseWidget(QWidget *parent) :
  QWidget(parent)
{
  //�����ޱ߿�͸��
 // setWindowFlags(Qt::FramelessWindowHint);//�ޱ߿�
  //setAttribute(Qt::WA_TranslucentBackground);//����͸��

  m_areaMovable = geometry();
  m_bPressed = false;
}

void BaseWidget::mousePressEvent(QMouseEvent *e)
{
  //������

  if(e->button() == Qt::LeftButton)
  {
  m_ptPress = e->pos();
  qDebug() << pos() << e->pos() << m_ptPress;
  m_bPressed = m_areaMovable.contains(m_ptPress);
  }
}

void BaseWidget::mouseMoveEvent(QMouseEvent *e)
{

    return;
    if(this->isFullScreen())
       return;

  if(m_bPressed)
  {
  qDebug() << pos() << e->pos() << m_ptPress;
  move(pos() + e->pos() - m_ptPress);
  }
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *)
{
  m_bPressed = false;
}

//������갴�µ�����
void BaseWidget::setAreaMovable(const QRect rt)
{
  if(m_areaMovable != rt)
  {
  m_areaMovable = rt;
  }
}
void BaseWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
   // this->isFullScreen()
    if(this->isFullScreen())
        this->showNormal();
        else
       this->showFullScreen();
    qDebug()<<"CButton::mouseDoubleClickEvent"<<endl;
}

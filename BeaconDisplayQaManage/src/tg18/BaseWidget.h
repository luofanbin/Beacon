//ͷ�ļ���BaseWidget.h
#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include <QMouseEvent>

//�̳���QWidget���Զ��崰�ڣ����������Ҽ��Կɣ����ڲ��ƶ������϶�����
class BaseWidget : public QWidget
{
  Q_OBJECT
public:
  explicit BaseWidget(QWidget *parent = 0);

  //������갴�¿��ƶ����ڵ��������Ӵ����б������ø�����
  void setAreaMovable(const QRect rt);

protected:
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void mouseDoubleClickEvent(QMouseEvent *event);

private:
  QRect m_areaMovable;//���ƶ����ڵ��������ֻ���ڸ������²����ƶ�����
  bool m_bPressed;//��갴�±�־���������Ҽ���
  QPoint m_ptPress;//��갴�µĳ�ʼλ��
};

#endif // BASEWIDGET_H

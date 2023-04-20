#ifndef TESTIMAGE_H
#define TESTIMAGE_H

#include <QWidget>
#include "BaseWidget.h"
#include <QPainter>
#include <QDialog>
#include "AutoHideWidget.h"
#include "visualtest.h"
#include "userdefine.h"
namespace Ui {
class TestImage;
}

class TestImage : public QDialog
{
    Q_OBJECT



public:


    explicit TestImage(QWidget *parent = nullptr);
    ~TestImage();
StQaResult m_QaResult;
void setTg18Type(EmTg18Type emType,EmTg18MethodType emMethod);
bool getTg18Data(StTg18Result &stResult);
void setDisplayPhysicalProperty(DisplayName_Data displayData);
signals:
     void getSensorData(StCieLvxy &stLvxy);
private:

 void mousePressEvent(QMouseEvent *);
   void paintEvent(QPaintEvent *event);
   void drawTg18Oiq(QPainter &painter);
   void drawTg18Un(QPainter &painter, QColor color);
   void drawTg18Ln(QPainter &painter, int step);
   void drawTg18Ct(QPainter &painter);
   void drawTG18Unl(QPainter &painter, QColor color);
   void drawTg18Ad(QPainter &painter);
   void drawTg18Afc(QPainter &painter);
   void drawTg18Mam02(QPainter &painter);
   void drawTg18Mam01(QPainter &painter);
   void drawTg18Knee(QPainter &painter);
   void drawTg18Chest(QPainter &painter);
   void drawTg18Bn(QPainter &painter, int step);
   void drawTg18Ang(QPainter &painter,double dot_pitch);
   void drawTg18Gd(QPainter &painter);
   void drawTg18Gvn(QPainter &painter, double dot_pitch);
   void drawTg18Gv(QPainter &painter, double dot_pitch);
    AutoHideWidget m_autoHideWidget;
    VisualTest m_visualTestDialg;
     EmTg18Type m_emTg18Type;
     int m_nStep;

     EmTg18MethodType m_emMethodType;
     static int m_nOperatorDisplay;
     static  double m_dbDotPitch;
     static  bool m_blNinePoint;
 private slots:
     void reportResult(bool blOk);
     void changeTg18Type(EmTg18Type emTgType,int nStep);
     void notSelecteSensor();

};

#endif // TESTIMAGE_H

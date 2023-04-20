#ifndef AUTOHIDEWIDGET_H
#define AUTOHIDEWIDGET_H

#include <QWidget>
#include "visualtest.h"
#include "qtg18result.h"
#include "QDialogButtonBox"
#include<QStackedLayout>
#include <QVector>
#include <QPainter>
#include <QColor>
class AutoHideWidget : public QWidget
{
    Q_OBJECT
public:

    enum Direction
    {
        None,
        Up,
        Right,
        Down,
        Left
    };

public:
    bool getTg18Data(StTg18Result &stResult);
    AutoHideWidget(int nDisplay,QWidget *parent = 0);
    void setPointNumber(bool blNinePoint);
    ~AutoHideWidget();
    void paintEvent(QPaintEvent *event);

private:
    void init();
    void isAutoHide();



private:
    QWidget *m_pTitleWidget;
   // QWidget *m_pContentWidget;

    QPoint m_mouseMovePoint;
    bool m_bMousePressed;
    Direction m_enDriection;
    bool m_bIsAutoHide;
    QColor m_cBackgroundColor;
    int m_nDesktopWidth;
    int m_nPositionY;
    QTg18Result *mp_Tg18Result[QA_TG18_END];
    QDialogButtonBox m_PageControl;
    QPushButton *mp_butForward;
    QPushButton *mp_butBackward;
    QStackedLayout *mp_stackTg18Result;
    void checkButtonStatus();
     QVector<EmTg18Type> m_vectorTG18Item;

     bool m_bShowAnimation;

public:
    void initQaIterm(EmTg18Type emType,EmTg18MethodType emMethod);
    bool eventFilter(QObject *watched, QEvent *event);
    bool event(QEvent *event);
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
     void hideWidget();
      void showWidget();
  public slots:

     void  ClieckButtonBox(QAbstractButton *button);

     void testNextPosition(int nType);

     // VisualTest m_VisualTest;
  signals:
      void changeTg18Type(EmTg18Type emTgType,int nStep);
      void reportResult(bool blOk);
      void getSensorData(StCieLvxy &stLvxy);

     // QMap<int,EmTg18Type> m_mapQaTestIterm;


};

#endif // AUTOHIDEWIDGET_H

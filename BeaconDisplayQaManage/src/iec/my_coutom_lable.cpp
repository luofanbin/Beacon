#include "my_coutom_lable.h"
#include<QDebug>

My_Coutom_Lable::My_Coutom_Lable(QWidget* parent):QLabel(parent)
{
    this->setAlignment(Qt::AlignVCenter);
    bl_isMonitorMouse=true;
}

void My_Coutom_Lable::enterEvent(QEvent *e)
{
    if(bl_isMonitorMouse)
    {
        QString tem_text="<u>"+text+"</u>";
        this->setText(tem_text);
    }
}

void My_Coutom_Lable::leaveEvent(QEvent *e)
{
    if(bl_isMonitorMouse)
        this->setText(text);
}

void My_Coutom_Lable::mousePressEvent(QMouseEvent *event)
{
    if(bl_isMonitorMouse)
        emit send_click_signal(nIndex);
}

void My_Coutom_Lable::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont font;
    font.setFamily("宋体");
    font.setPointSize(300);
    font.setBold(true);
    QColor mTextColor=QColor(200,200,200);
    if(blIsDrawOutlined)
    {
        QFontMetrics metrics(font);
        QPainterPath path;
        QPen pen(QColor(0, 0, 0));
        int penwidth = font.pointSize() * 0.05;
        if(penwidth > 6);
        {
            penwidth = 6;
        }
        pen.setWidth(penwidth);
        int len = metrics.width(text);
        int w = width();
        int px = (len - w) / 2;
        if(px < 0)
        {
            px = -px;
        }
        //(px,py)是字体基线的起点位置，在qt助手中查找addText函数可以了解到
        int py = (height() - metrics.height()) / 2 + metrics.ascent();
        if(py < 0)
        {
            py = -py;
        }
        path.addText(px, py, font,text);
        painter.strokePath(path, pen);
        painter.drawPath(path);
        painter.fillPath(path, QBrush(mTextColor));
    }else
    {
        painter.fillRect(rect(),QColor(255,255,255,0));
        emit hideDisplaySN();
    }
}

void My_Coutom_Lable::DrawingCurves()
{
    QGridLayout *main_layout=new QGridLayout(this);

      main_layout->addWidget(&m_CurvePlot,0,0)     ;


      srand(QDateTime::currentDateTime().toTime_t());
      //ui->setupUi(this);

      m_CurvePlot.setInteractions(QCP::iSelectAxes |
                                     QCP::iSelectLegend );
     // m_CurvePlot.xAxis->setRange(-8, 8);
      //m_CurvePlot.yAxis->setRange(-5, 5);
     // m_CurvePlot.axisRect()->setupFullAxesBox();

    //  m_CurvePlot.plotLayout()->insertRow(0);
      QCPTextElement *title = new QCPTextElement(&m_CurvePlot, "Interaction Example", QFont("sans", 17, QFont::Bold));
      m_CurvePlot.plotLayout()->addElement(0, 0, title);

      m_CurvePlot.xAxis->setLabel("x Axis");
      m_CurvePlot.yAxis->setLabel("y Axis");
      m_CurvePlot.legend->setVisible(true);
      QFont legendFont = font();
      legendFont.setPointSize(10);
      m_CurvePlot.legend->setFont(legendFont);
      m_CurvePlot.legend->setSelectedFont(legendFont);
      m_CurvePlot.legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items
      m_CurvePlot.show();
      //addRandomGraph(&m_CurvePlot);

     //  setLayout(main_layout);
  //this->centralWidget()->setLayout(main_layout);
      this->setLayout(main_layout);
}

void My_Coutom_Lable::addRandomGraph(QCustomPlot *pCustomPlot,Contrast_response_Data *data_buffer)
{
    int n = 50; // number of points in graph
    pCustomPlot->clearGraphs();
    CCurvTypeMothed cuver_type;
      cuver_type.WorkDicomCurveData(data_buffer);
      n = 17;
     QVector<double> jnd(n), current(n),sandard(n),sandard_negative(n),sandard_postive(n);
     for (int i=0; i<n; i++)
     {
       jnd[i] = data_buffer->dbAverageJnd[i];
       current[i]=data_buffer->dbDevationCurrent[i];
        sandard[i]=data_buffer->dbDevationStandard[i];
        sandard_negative[i]=sandard[i]*0.9;
        sandard_postive[i]=sandard[i]*1.1;

     }

     int  n_line_style=1;

  /*
  QCPCurve *newCurve = new QCPCurve(m_CurvePlot->xAxis, m_CurvePlot->yAxis);

  newCurve->setName(QString("DICOM"));
    newCurve->setData( jnd, sandard);
   newCurve->setLineStyle(QCPCurve::lsLine);
  newCurve->setScatterSkip(1);


  QCPItemCurve *phaseTracerArrow = new QCPItemCurve(m_CurvePlot);//构造一个带参数线
      // m_CurvePlot->addItem(phaseTracerArrow);//添加到图中
   //    phaseTracerArrow->start->setParentAnchor(phaseTracerText->left);//曲线的开始点为文本的左位置
       phaseTracerArrow->startDir->setParentAnchor(phaseTracerArrow->start);//同步自身的锚点
       phaseTracerArrow->startDir->setCoords(40,0); // x轴偏移40个像素
    //   phaseTracerArrow->end->setParentAnchor(phaseTracer->position);//曲线的结束点为实心圆的位置
       phaseTracerArrow->end->setCoords(80,20 );//偏移
       phaseTracerArrow->endDir->setParentAnchor(phaseTracerArrow->end);//同步自身的锚点
       phaseTracerArrow->endDir->setCoords(160,0 );//偏移
       phaseTracerArrow->setHead(QCPLineEnding::esSpikeArrow);//设置首部形状(箭头)
   //    phaseTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar, (phaseTracerText->bottom->pixelPoint().y() - phaseTracerText->top->pixelPoint().y())*0.85));//设置尾部形状(一条竖线)


  */
     QPen graphPen;
     graphPen.setColor(QColor(0,255,0));
   //  graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);


  #if 1

  pCustomPlot->setAutoAddPlottableToLegend(true);
    pCustomPlot->addGraph();

  pCustomPlot->graph()->setName(QString("DICOM"));
    pCustomPlot->graph()->setData( jnd, sandard);
    pCustomPlot->graph()->setLineStyle((QCPGraph::LineStyle)n_line_style);
   graphPen.setColor(QColor(0,255,0));
  pCustomPlot->graph()->setPen(graphPen);
    pCustomPlot->addGraph();
    pCustomPlot->graph()->setName(QString("Current"));
    pCustomPlot->graph()->setData( jnd, current);
    pCustomPlot->graph()->setLineStyle((QCPGraph::LineStyle)n_line_style);
   graphPen.setColor(QColor(50,50,50));
    pCustomPlot->graph()->setScatterStyle(QCPScatterStyle::ssCircle);
    pCustomPlot->graph()->setPen(graphPen);
    pCustomPlot->addGraph();
    pCustomPlot->graph()->setName(QString("+10%"));
    pCustomPlot->graph()->setData( jnd, sandard_postive);
   pCustomPlot->graph()->setLineStyle((QCPGraph::LineStyle)n_line_style);
    graphPen.setColor(QColor(255,0,0));
  graphPen.setStyle(Qt::DashLine);
  pCustomPlot->graph()->setPen(graphPen);
    pCustomPlot->addGraph();
    pCustomPlot->graph()->setName(QString("-10%"));
    pCustomPlot->graph()->setData( jnd, sandard_negative);
   pCustomPlot->graph()->setLineStyle((QCPGraph::LineStyle)n_line_style);
  pCustomPlot->graph()->setPen(graphPen);
   if (rand()%100 > 50)
  ;//pCustomPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));

  #endif

   //pCustomPlot->yAxis->setScaleType(QCPAxis::stLogarithmic );
   pCustomPlot->rescaleAxes();
    pCustomPlot->xAxis->setRange(0,pCustomPlot->xAxis->range().upper+40);
     pCustomPlot->xAxis->setLabel("JND");

     pCustomPlot->yAxis->setLabel("dL/L for JND");
      pCustomPlot->yAxis->setRange(0,pCustomPlot->yAxis->range().upper);
    //pCustomPlot->xAxis->rescale();
   pCustomPlot->viewport().setX(0);
   pCustomPlot->viewport().setY(0);
   //pCustomPlot->graph()->rescaleValueAxis(false, true);
  //   pCustomPlot->xAxis->setRange();
   //  pCustomPlot->rescaleValueAxis(false, true);
   //   pCustomPlot->rescaleValueAxis(false, true);
    //  pCustomPlot->xAxis->setRange(mPlot->xAxis->range().upper, 100, Qt::AlignRight);



    pCustomPlot->replot();
}

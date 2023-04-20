#include "qluminaceresponse.h"
#include<QGridLayout>
#include<QHBoxLayout>
#include<QtGlobal>
#include<QFormLayout>
#include "testimage.h"
QLuminaceResponse::QLuminaceResponse(QWidget *parent) : QWidget(parent)
{
    QLabel *p_dicom_ln[DICOM_GSDF_GRAYSCALE_NUMBER];
    QLabel *p_dicom_ln_unit[DICOM_GSDF_GRAYSCALE_NUMBER];
    QLabel *p_dicom_ln_unit_two[DICOM_GSDF_GRAYSCALE_NUMBER];
    QString str_temp;
    QGridLayout *p_gsdf_layout=new QGridLayout;
    QLabel *p_lable_temp=new QLabel(tr("Excl amb"));
     p_gsdf_layout->addWidget(p_lable_temp,0,1);
     p_lable_temp=new QLabel(tr("Incl amb"));
     p_gsdf_layout->addWidget(p_lable_temp,0,3);
     QLabel *p_labe=new QLabel(tr("GSDF error"));
     p_labe->setAlignment(Qt::AlignCenter);
     p_gsdf_layout->addWidget(p_labe,0,5);

    for (int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
    {
        mp_GrayscaleLn[i]=new QLineEdit;
        mp_GrayscaleLn[i]->setStyleSheet("background-color:rgba(255,255,255,255)");
        mp_GrayscaleLnInclueAmbient[i]=new QLineEdit;
       mp_GrayscaleLnInclueAmbient[i]->setReadOnly(true);//setEnabled(false);
       mp_GrayscaleLnInclueAmbient[i]->setStyleSheet("background-color:rgba(255,255,255,255)");
        str_temp=QString(tr("LN%1")).arg(i+1,2,10,QChar('0'));
         mp_GrayscaleLn[i]->setAlignment(Qt::AlignRight);
        p_dicom_ln[i]=new QLabel(str_temp);
        p_dicom_ln_unit[i]=new QLabel(tr("cd/m2  "));
       p_dicom_ln_unit_two[i]=new QLabel(tr("cd/m2  "));
        p_gsdf_layout->addWidget(p_dicom_ln[i],i+1,0);
        p_gsdf_layout->addWidget(mp_GrayscaleLn[i],i+1,1);
        p_gsdf_layout->addWidget(p_dicom_ln_unit[i],i+1,2);
        p_gsdf_layout->addWidget(mp_GrayscaleLnInclueAmbient[i],i+1,3);
        p_gsdf_layout->addWidget(p_dicom_ln_unit_two[i],i+1,4);
        if(i>0)
        {
            mp_GrayscaleLnError[i-1]=new QLineEdit("0%");
            mp_GrayscaleLnError[i-1]->setStyleSheet("background-color:rgba(255,255,255,255)");
            mp_GrayscaleLnError[i-1]->setReadOnly(true);
            mp_GrayscaleLnError[i-1]->setAlignment(Qt::AlignRight);
            p_gsdf_layout->addWidget(mp_GrayscaleLnError[i-1],i+1,5);
        }
        else {

        }
    }
     p_labe=new QLabel(tr("Max.GSDF error"));

     p_labe->setAlignment(Qt::AlignRight);
    mp_GrayscaleLnErrorMax=new QLineEdit("0%");
    mp_GrayscaleLnErrorMax->setReadOnly(true);
    mp_GrayscaleLnErrorMax->setAlignment(Qt::AlignRight);
    p_gsdf_layout->addWidget(p_labe,DICOM_GSDF_GRAYSCALE_NUMBER+1,3,1,2);
    p_gsdf_layout->addWidget(mp_GrayscaleLnErrorMax,DICOM_GSDF_GRAYSCALE_NUMBER+1,5);

     p_labe=new QLabel(tr("Measure method for luminance response near"));
     p_labe->setAlignment(Qt::AlignLeft);
    p_gsdf_layout->addWidget(p_labe,DICOM_GSDF_GRAYSCALE_NUMBER+2,0,1,5);

    p_labe=new QLabel(tr("Requirements: GSDF error<=10% Limits"));
    p_labe->setAlignment(Qt::AlignLeft);
    p_gsdf_layout->addWidget(p_labe,DICOM_GSDF_GRAYSCALE_NUMBER+3,0,1,5);

    p_labe=new QLabel(tr("Test images"));
    p_labe->setAlignment(Qt::AlignLeft);
    p_gsdf_layout->addWidget(p_labe,DICOM_GSDF_GRAYSCALE_NUMBER+4,1);

    QPushButton *p_test_ln=new QPushButton(tr("Start"));
    p_gsdf_layout->addWidget(p_test_ln,DICOM_GSDF_GRAYSCALE_NUMBER+4,2,1,2);
    //初始化曲线
    m_CurvePlot.setInteractions(QCP::iSelectAxes |
                                QCP::iSelectLegend );
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

    //QFormLayout *p_center_form =new QFormLayout;

    QVBoxLayout *p_left_layout=new QVBoxLayout;

 QHBoxLayout *p_center=new QHBoxLayout;
 p_center->addStretch();
 p_center->addLayout(p_gsdf_layout);
 p_center->addWidget(&m_CurvePlot);
  p_center->addStretch();
  p_left_layout->addLayout(p_center);
  p_left_layout->addStretch();
  QFrame *p_center_frame=new QFrame;
  p_center->setStretchFactor(p_gsdf_layout, 1);
  p_center->setStretchFactor(&m_CurvePlot, 50);
  p_center_frame->setLayout(p_left_layout);

//  p_gsdf_layout->setFixedSize(300,300);
  p_center_frame->setFixedSize(990,580);
  QHBoxLayout *p_frame_layout=new QHBoxLayout;
  p_frame_layout->addWidget(p_center_frame);
  p_frame_layout->addStretch();
    QVBoxLayout *p_main_layout=new QVBoxLayout;
    p_main_layout->addLayout(p_frame_layout);
    p_main_layout->addStretch();
  //p_center->setStretchFactor(p_gsdf_layout, 1);
 // p_center->setStretchFactor(&m_CurvePlot, 1);
 //   p_center_form->addRow(p_gsdf_layout);
   // p_center_form->addItem(p_gsdf_layout);
   // p_center_form->addLayout(p_gsdf_layout);RR
   //  p_center_form->addWidget(&m_CurvePlot);
#if 0
    p_left_layout->addStretch();
    p_left_layout->addLayout(p_gsdf_layout);
    p_left_layout->addStretch();
    p_main_layout->addStretch();
    p_main_layout->addLayout(p_left_layout);
    p_main_layout->addWidget(&m_CurvePlot,1);
     p_main_layout->addStretch();
    p_main_layout->setStretchFactor(p_left_layout, 1);
    p_main_layout->setStretchFactor(&m_CurvePlot, 2);
#endif
    setLayout(p_main_layout);

    connect(p_test_ln,SIGNAL(clicked()),this,SIGNAL(testLuminace()));
/*
    StQaLuminace data_buffer;
    data_buffer.AmbientLuminace=0;
    data_buffer.dbCurentLuminace[0]=   0.23;
    data_buffer.dbCurentLuminace[1]= 0.68;;
    data_buffer.dbCurentLuminace[2]= 1.45;
    data_buffer.dbCurentLuminace[3]= 2.61;
    data_buffer.dbCurentLuminace[4]= 4.25;
    data_buffer.dbCurentLuminace[5]= 6.48;
    data_buffer.dbCurentLuminace[6]= 9.44;
    data_buffer.dbCurentLuminace[7]= 13.29;
    data_buffer.dbCurentLuminace[8]= 18.22;
    data_buffer.dbCurentLuminace[9]= 24.48;
    data_buffer.dbCurentLuminace[10]= 32.35;
    data_buffer.dbCurentLuminace[11]= 42.19;
    data_buffer.dbCurentLuminace[12]= 54.43;
    data_buffer.dbCurentLuminace[13]= 69.60;
    data_buffer.dbCurentLuminace[14]= 88.34;
    data_buffer.dbCurentLuminace[15]= 111.42;
    data_buffer.dbCurentLuminace[16]= 139.80;
    data_buffer.dbCurentLuminace[17]=174.60;



    data_buffer.dbCurentLuminace[0]=   1;
    data_buffer.dbCurentLuminace[1]= 3;;
    data_buffer.dbCurentLuminace[2]=4;
    data_buffer.dbCurentLuminace[3]= 7;
    data_buffer.dbCurentLuminace[4]= 9;
    data_buffer.dbCurentLuminace[5]= 10;
    data_buffer.dbCurentLuminace[6]= 25;
    data_buffer.dbCurentLuminace[7]= 27;
    data_buffer.dbCurentLuminace[8]= 30;
    data_buffer.dbCurentLuminace[9]=  35;
    data_buffer.dbCurentLuminace[10]= 40;
    data_buffer.dbCurentLuminace[11]= 55;
    data_buffer.dbCurentLuminace[12]= 70;
    data_buffer.dbCurentLuminace[13]= 90;
    data_buffer.dbCurentLuminace[14]= 110;
    data_buffer.dbCurentLuminace[15]= 150;
    data_buffer.dbCurentLuminace[16]=190;
    data_buffer.dbCurentLuminace[17]=240;

    setData(data_buffer);
*/
}
const StQaLuminace QLuminaceResponse::getData( )
{
    updateData(true);
    return m_stQaLuminace;



}
void QLuminaceResponse::setData(const StQaLuminace &stQaData )
{

 /*  QString str="0.2067,0.6738,1.4683,2.6972,4.4466,6.8192,10.0082,14.1431,19.4721,26.0852,34.7008,45.3569,58.6188,75.2183,95.6755,120.6933,151.9785,190.1138";


    QStringList number_str=str.split(",");
    StQaLuminace data_buffer;
    data_buffer.AmbientLuminace=0.3;
    for(int i=0;i<18;i++)
        data_buffer.dbCurentLuminace[i]=number_str.at(i).toDouble();
*/
//stQaData=data_buffer;





    m_stQaLuminace=stQaData;


//    QMessageBox::information(NULL,"iterm",QString("return:%1").arg(n_return));
    updateData(false);

}
void QLuminaceResponse::updateData(bool blUpate)
{
    if(blUpate)//由控键到数组
    {
       // m_stQaLuminace.emCurveValue=CURVE_DICOM;
        for(int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
        {
            m_stQaLuminace.dbCurentLuminace[i]= mp_GrayscaleLn[i]->text().toDouble();

        }

    }
    else//由数组到控键
    {
        Contrast_response_Data   data_buffer;
        data_buffer.stQaData=m_stQaLuminace;
        // data_buffer.strCurverType=stQaData.strCurverType;
        //  data_buffer.AmbientLuminace=stQaData.AmbientLuminace;
        // memcpy(&data_buffer.dbCurentLuminace[0],&stQaData.dbCurentLuminace[0],DICOM_GSDF_GRAYSCALE_NUMBER*sizeof (double));
        CCurvTypeMothed cuver_type;
        if( !cuver_type.WorkDicomCurveData(&data_buffer))
            ;//;
        double db_max=0;
        for (int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++) {
            mp_GrayscaleLnInclueAmbient[i]->setText(QString("%1").arg(data_buffer.dbCurentLuminaceInclueAmbient[i]));
            mp_GrayscaleLn[i]->setText(QString("%1").arg(data_buffer.stQaData.dbCurentLuminace[i]));
            if(i<DICOM_GSDF_GRAYSCALE_NUMBER-1)
            {
                mp_GrayscaleLnError[i]->setText(QString("%1%").arg((int)(data_buffer.dbDevationPercent[i]*100)));
                db_max=qMax(db_max,data_buffer.dbDevationPercent[i]);
            }
        }
        mp_GrayscaleLnErrorMax->setText(QString("%1%").arg((int)(db_max*100)));

        setGsdfGraphData(data_buffer);

    }

}

void QLuminaceResponse::setGsdfGraphData(Contrast_response_Data   data_buffer )
{

    QCustomPlot *pCustomPlot=&m_CurvePlot;
    m_CurvePlot.clearGraphs();
    int n = 50; // number of points in graph


    n = 17;
    QVector<double> jnd(n), current(n),sandard(n),sandard_negative(n),sandard_postive(n);
    for (int i=0; i<n; i++)
    {
        jnd[i] = data_buffer.dbAverageJnd[i];
        current[i]=data_buffer.dbDevationCurrent[i];
        sandard[i]=data_buffer.dbDevationStandard[i];
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

    //  graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);

*/
    QPen graphPen;
    graphPen.setColor(QColor(0,255,0));


#if 1

    pCustomPlot->setAutoAddPlottableToLegend(true);
    pCustomPlot->addGraph();

    pCustomPlot->graph()->setName(QString(tr("DICOM")));
    pCustomPlot->graph()->setData( jnd, sandard);
    pCustomPlot->graph()->setLineStyle((QCPGraph::LineStyle)n_line_style);
    graphPen.setColor(QColor(0,255,0));
    pCustomPlot->graph()->setPen(graphPen);
    pCustomPlot->addGraph();
    pCustomPlot->graph()->setName(QString(tr("Current")));
    pCustomPlot->graph()->setData( jnd, current);
    pCustomPlot->graph()->setLineStyle((QCPGraph::LineStyle)n_line_style);
    graphPen.setColor(QColor(50,50,50));
    pCustomPlot->graph()->setScatterStyle(QCPScatterStyle::ssCircle);
    pCustomPlot->graph()->setPen(graphPen);
    pCustomPlot->addGraph();
    pCustomPlot->graph()->setName(QString(tr("+10%")));
    pCustomPlot->graph()->setData( jnd, sandard_postive);
    pCustomPlot->graph()->setLineStyle((QCPGraph::LineStyle)n_line_style);
    graphPen.setColor(QColor(255,0,0));
    graphPen.setStyle(Qt::DashLine);
    pCustomPlot->graph()->setPen(graphPen);
    pCustomPlot->addGraph();
    pCustomPlot->graph()->setName(QString(tr("-10%")));
    pCustomPlot->graph()->setData( jnd, sandard_negative);
    pCustomPlot->graph()->setLineStyle((QCPGraph::LineStyle)n_line_style);
    pCustomPlot->graph()->setPen(graphPen);
    if (rand()%100 > 50)
        ;//pCustomPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));

#endif


    pCustomPlot->rescaleAxes();
    pCustomPlot->xAxis->setRange(0,pCustomPlot->xAxis->range().upper+40);
    pCustomPlot->xAxis->setLabel(tr("JND"));

    pCustomPlot->yAxis->setLabel(tr("dL/L for JND"));
    pCustomPlot->yAxis->setRange(0,pCustomPlot->yAxis->range().upper);

    pCustomPlot->viewport().setX(0);
    pCustomPlot->viewport().setY(0);
     pCustomPlot->replot();
    //pCustomPlot->xAxis->rescale();
    //pCustomPlot->yAxis->setScaleType(QCPAxis::stLogarithmic );
    //pCustomPlot->graph()->rescaleValueAxis(false, true);
    //   pCustomPlot->xAxis->setRange();
    //  pCustomPlot->rescaleValueAxis(false, true);
    //   pCustomPlot->rescaleValueAxis(false, true);
    //  pCustomPlot->xAxis->setRange(mPlot->xAxis->range().upper, 100, Qt::AlignRight);




}

bool QLuminaceResponse::getQaResult(StQaCheckCondition &stQaCondition)
{
    if(!stQaCondition.checkDataStatus())
        return false;
    StQaLuminace st_qa_luminace=getData();
    for(int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
    {
        if(fabs(m_stQaLuminace.dbCurentLuminace[i])<0.0006)
        {
            stQaCondition.strResult=tr("Please enter QA luminace in the luminance response!");
            return false;
        }

    }


    if( mp_GrayscaleLnErrorMax->text().toDouble()>stQaCondition.dbLuinacneDevation)
        return false;
    return true;
}

void QLuminaceResponse::changedLamb(double dbAmbient)
{
    m_stQaLuminace.AmbientLuminace=dbAmbient;
    updateData(false);
}

#include "createprintpdf.h"
#include <QPdfWriter>
#include <QDir>
#include <QDebug>
#include <QPainter>
#include "ccurvtypemothed.h"
#include "printpreviewwidget.h"
CreatePrintPdf::CreatePrintPdf(QObject *parent) : QObject(parent)
{

}

void CreatePrintPdf::printPreviewPdf(QString strFileName, StIecReport IecReport)
{
    m_IecReport=IecReport;
    QPrinter *printer=new QPrinter;
    printer->setOutputFileName(strFileName);//设置输出路径
    printer->setOutputFormat(QPrinter::PdfFormat);//设置输出格式为pdf
    printer->setPageSize(QPrinter::A4);//设置纸张大小为A4
    printer->setResolution(550);
    printer->setPageMargins(QMarginsF(0, 0, 0, 0)); //边框

    PrintPreviewWidget preview(printer);
    Qt::WindowFlags windowFlag  = Qt::Dialog;
        windowFlag                  |= Qt::WindowMinimizeButtonHint;
        windowFlag                  |= Qt::WindowMaximizeButtonHint;
        windowFlag                  |= Qt::WindowCloseButtonHint;

    preview.setWindowFlags(windowFlag);
    preview.setMinimumSize(1000,600);
    preview.setZoomFactor(1.25);
    switch (m_IecReport.ReportQaType) {
    case QA_ACCEPTANCE:
        connect(&preview, SIGNAL(paintRequested(QPrinter*)),this ,SLOT(generateIECTableA1Pdf(QPrinter*)));
        break;
    case QA_CONSTANCY:
        connect(&preview, SIGNAL(paintRequested(QPrinter*)),this ,SLOT(generateIECTableA2Pdf(QPrinter*)));
        break;
    default:
        break;
    }
    preview.showMaximized();
    preview.exec();

}

void CreatePrintPdf::generateIECTableA1Pdf(QPrinter* printer)
{
    QPainter* painter = new QPainter;
    painter->begin(printer);
    //设置字体

    QPen pen(Qt::black, 2);
    painter->setPen(pen);

    int nPositionX,nPositionY,nWidth=4500,nHeight=4500;
    nPositionX=450;
    nPositionY=700;
    int n_rect_width=nWidth-nPositionX*2;
    int n_rect_height=120;

    QFont font("宋体",12);
    painter->setFont(font);
    QRect rect=QRect(0,425,nWidth,200);
    if(m_IecReport.DisplayInfo.DisplayNameInfo.DispalyColorIndex)
        painter->drawText(rect,Qt::AlignCenter,tr("Acceptance test sample report of a colour diagnostic display"));
    else
        painter->drawText(rect,Qt::AlignCenter,tr("Acceptance test sample report of a monochrome diagnostic display"));
    QFont font1("宋体",9);
    painter->setFont(font1);
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*7);
    drawGeneralTablePart(painter,rect,m_IecReport);

    nPositionY=nPositionY+n_rect_height*7+100;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);

    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawGlobalResultPart(painter,rect,m_IecReport);

    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    SingleItemTestInfo stTestInfo;
    dealSingleItemTestInfo(OVERALL_IMAGE_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*3;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*5);
    dealSingleItemTestInfo(GREYSCALE_RESOLUTION_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*5;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*5);
    dealSingleItemTestInfo(LUMINANCE_RESPONSE_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*5;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    dealSingleItemTestInfo(LUMINANCE_UNIFORMITY_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*3;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    dealSingleItemTestInfo(CHROMATICITY_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("1"));
    printer->newPage();//生成新的一页

    nPositionX=450;
    nPositionY=500;
    n_rect_width=nWidth-nPositionX*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*7);
    dealSingleItemTestInfo(PIXEL_FAULTS_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo,PIXEL_FAULTS_EVALUATION);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*7;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*11);
    dealSingleItemTestInfo(A1_ANGULAR_VIEWING_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*11;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    dealSingleItemTestInfo(CLINICAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    painter->setBrush(Qt::NoBrush);
    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height);
    painter->drawRect(rect);
    rect=QRect(nPositionX+20,nPositionY+25,n_rect_width-20,n_rect_height-25);
    painter->drawText(rect,tr("Quantitative evaluations"));

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*11);
    dealSingleItemTestInfo(A1_BASIC_LUMINANCE_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("2"));
    printer->newPage();//生成新的一页

    nPositionY=500;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*21);
    dealSingleItemTestInfo(A1_LUMINANCE_RESPONSE_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

//    stTestInfo.strRequirement.clear();
//    stTestInfo.strTestResult.clear();
//    nPositionY=nPositionY+n_rect_height*21;
//    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*5);
//    dealSingleItemTestInfo(A1_MULTIPLE_LUMINANCE_EVALUATION,IecReport,stTestInfo);
//    drawSingleItemPart(painter,rect,stTestInfo);
    int nRowNum;
    if(m_IecReport.DisplayInfo.DisplayNameInfo.DispalyColorIndex)
    {
        stTestInfo.strRequirement.clear();
        stTestInfo.strTestResult.clear();
        nPositionY=nPositionY+n_rect_height*21;
        if(m_IecReport.DisplayInfo.LuminanceDeviationInfo.PointNumber==5)
            nRowNum=8;
        else
            nRowNum=12;
        rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*nRowNum);
        dealSingleItemTestInfo(CHROMATICITY_QUANTITATIVE_EVALUATION,m_IecReport,stTestInfo);
        drawSingleItemPart(painter,rect,stTestInfo);
        rect=QRect(0,6000,nWidth,50);
        painter->drawText(rect,Qt::AlignCenter,tr("3"));
    }else
    {
        stTestInfo.strRequirement.clear();
        stTestInfo.strTestResult.clear();
        nPositionY=nPositionY+n_rect_height*21;
        if(m_IecReport.DisplayInfo.LuminanceDeviationInfo.PointNumber==5)
            nRowNum=8;
        else
            nRowNum=12;
        rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*nRowNum);
        dealSingleItemTestInfo(A1_LUMINANCE_UNIFORMITY_EVALUATION,m_IecReport,stTestInfo);
        drawSingleItemPart(painter,rect,stTestInfo);
        rect=QRect(0,6000,nWidth,50);
        painter->drawText(rect,Qt::AlignCenter,tr("3"));
        painter->end();
        return;
    }
//    writer->newPage();//生成新的一页

//    nPositionY=500;
//    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
//    drawHeaderPart(painter,rect);

//    stTestInfo.strRequirement.clear();
//    stTestInfo.strTestResult.clear();
//    nPositionY=nPositionY+n_rect_height*2;
//    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*8);
//    dealSingleItemTestInfo(CHROMATICITY_QUANTITATIVE_EVALUATION,IecReport,stTestInfo);
//    drawSingleItemPart(painter,rect,stTestInfo);

//    stTestInfo.strRequirement.clear();
//    stTestInfo.strTestResult.clear();
//    nPositionY=nPositionY+n_rect_height*2;
//    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*6);
//    dealSingleItemTestInfo(MULTIPLE_CHROMATICITY_QUANTITATIVE_EVALUATION,IecReport,stTestInfo);
//    drawSingleItemPart(painter,rect,stTestInfo);

//    stTestInfo.strRequirement.clear();
//    stTestInfo.strTestResult.clear();
//    nPositionY=nPositionY+n_rect_height*6;
//    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*8);
//    dealSingleItemTestInfo(A1_LUMINANCE_UNIFORMITY_EVALUATION,IecReport,stTestInfo);
//    drawSingleItemPart(painter,rect,stTestInfo);

//    rect=QRect(0,6000,nWidth,50);
//    painter->drawText(rect,Qt::AlignCenter,tr("4"));
    printer->newPage();//生成新的一页

    nPositionY=500;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*2;
    if(m_IecReport.DisplayInfo.LuminanceDeviationInfo.PointNumber==5)
        nRowNum=8;
    else
        nRowNum=12;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*nRowNum);
    dealSingleItemTestInfo(A1_LUMINANCE_UNIFORMITY_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*nRowNum;
    n_rect_height=150;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*22);
    dealSingleItemTestInfo(GREYSCALE_CHROMATICITY_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo,GREYSCALE_CHROMATICITY_EVALUATION);

    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("4"));
    painter->end();
    return;
}

void CreatePrintPdf::generateIECTableA2Pdf(QPrinter* printer)
{
    QPainter* painter = new QPainter;
    painter->begin(printer);

    int nPositionX,nPositionY,nWidth=4500,nHeight=4500;
    QPen pen(Qt::black, 2);
    painter->setPen(pen);

    nPositionX=450;
    nPositionY=700;
    int n_rect_width=nWidth-nPositionX*2;
    int n_rect_height=120;

    QFont font("宋体",12);
    painter->setFont(font);
    QRect rect=QRect(0,425,nWidth,200);
    if(m_IecReport.DisplayInfo.DisplayNameInfo.DispalyColorIndex)
        painter->drawText(rect,Qt::AlignCenter,tr("Constancy test sample report of a colour diagnostic display"));
    else
        painter->drawText(rect,Qt::AlignCenter,tr("Constancy test sample report of a monochrome diagnostic display"));
    QFont font1("宋体",9);
    painter->setFont(font1);
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*7);
    drawGeneralTablePart(painter,rect,m_IecReport);

    nPositionY=nPositionY+n_rect_height*7+100;
    n_rect_height=120;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);

    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawGlobalResultPart(painter,rect,m_IecReport);

    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    SingleItemTestInfo stTestInfo;
    dealSingleItemTestInfo(OVERALL_IMAGE_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*3;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    dealSingleItemTestInfo(LUMINANCE_UNIFORMITY_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*3;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    dealSingleItemTestInfo(CLINICAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("1"));
    printer->newPage();

    nPositionY=500;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);

    painter->setBrush(Qt::NoBrush);
    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height);
    painter->drawRect(rect);
    rect=QRect(nPositionX+20,nPositionY+25,n_rect_width-20,n_rect_height-25);
    painter->drawText(rect,tr("Quantitative evaluations"));

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*10);
    dealSingleItemTestInfo(A2_BASIC_LUMINANCE_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*10;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*21);
    dealSingleItemTestInfo(A2_LUMINANCE_RESPONSE_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("2"));
    if(m_IecReport.DisplayInfo.DisplayNameInfo.DispalyColorIndex)
    {
        printer->newPage();

        nPositionY=500;
        rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
        drawHeaderPart(painter,rect);

        stTestInfo.strRequirement.clear();
        stTestInfo.strTestResult.clear();
        nPositionY=nPositionY+n_rect_height*2;
        n_rect_height=150;
        rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*22);
        dealSingleItemTestInfo(GREYSCALE_CHROMATICITY_EVALUATION,m_IecReport,stTestInfo);
        drawSingleItemPart(painter,rect,stTestInfo,GREYSCALE_CHROMATICITY_EVALUATION);

        rect=QRect(0,6000,nWidth,50);
        painter->drawText(rect,Qt::AlignCenter,tr("3"));

    }
    painter->end();
}

void CreatePrintPdf::generateIECTableA3Pdf(QPrinter* printer)
{
    QPainter* painter = new QPainter;
    painter->begin(printer);
    //设置字体
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(9);

    int nPositionX,nPositionY,nWidth=4500,nHeight=4500;
    QPen pen(Qt::black, 2);
    painter->setPen(pen);
    painter->setFont(font);

    nPositionX=450;
    nPositionY=500;
    int n_rect_width=nWidth-nPositionX*2;
    int n_rect_height=120;

    QRect rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*7);
    drawGeneralTablePart(painter,rect,m_IecReport);

    nPositionY=nPositionY+n_rect_height*7+100;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);

    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawGlobalResultPart(painter,rect,m_IecReport);

    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    SingleItemTestInfo stTestInfo;
    dealSingleItemTestInfo(OVERALL_IMAGE_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*3;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*5);
    dealSingleItemTestInfo(GREYSCALE_RESOLUTION_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*5;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*5);
    dealSingleItemTestInfo(LUMINANCE_RESPONSE_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*5;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    dealSingleItemTestInfo(LUMINANCE_UNIFORMITY_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*3;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    dealSingleItemTestInfo(CHROMATICITY_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*3;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*11);
    dealSingleItemTestInfo(A2_ANGULAR_VIEWING_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*11;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    dealSingleItemTestInfo(CLINICAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("1"));
    printer->newPage();

    nPositionY=500;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);

    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height);
    painter->drawRect(rect);
    rect=QRect(nPositionX+20,nPositionY+25,n_rect_width-20,n_rect_height-25);
    painter->drawText(rect,tr("Quantitative evaluations"));

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*8);
    dealSingleItemTestInfo(A3_BASIC_LUMINANCE_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*8;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*21);
    dealSingleItemTestInfo(A3_LUMINANCE_RESPONSE_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*21;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*5);
    dealSingleItemTestInfo(A3_MULTIPLE_LUMINANCE_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*5;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*8);
    dealSingleItemTestInfo(A3_LUMINANCE_UNIFORMITY_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("2"));
    painter->end();

    return;
}

void CreatePrintPdf::generateIECTableA4Pdf(QPrinter* printer)
{
    QPainter* painter = new QPainter;
    painter->begin(printer);
    //设置字体
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(9);

    int nPositionX,nPositionY,nWidth=4500,nHeight=4500;
    QPen pen(Qt::black, 2);
    painter->setPen(pen);
    painter->setFont(font);

    nPositionX=450;
    nPositionY=500;
    int n_rect_width=nWidth-nPositionX*2;
    int n_rect_height=120;

    QRect rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*7);
    drawGeneralTablePart(painter,rect,m_IecReport);

    nPositionY=nPositionY+n_rect_height*7+100;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);
    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawGlobalResultPart(painter,rect,m_IecReport);

    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    SingleItemTestInfo stTestInfo;
    dealSingleItemTestInfo(OVERALL_IMAGE_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*3;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    dealSingleItemTestInfo(LUMINANCE_UNIFORMITY_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*3;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    dealSingleItemTestInfo(CLINICAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height);
    painter->drawRect(rect);
    rect=QRect(nPositionX+20,nPositionY+25,n_rect_width-20,n_rect_height-25);
    painter->drawText(rect,tr("Quantitative evaluations"));

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*9);
    dealSingleItemTestInfo(A4_BASIC_LUMINANCE_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("1"));
    printer->newPage();

    nPositionY=500;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*21);
    dealSingleItemTestInfo(A4_LUMINANCE_RESPONSE_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("2"));
    painter->end();
    return;
}

void CreatePrintPdf::generateIECTableA5Pdf(QPrinter* printer)
{
    QPainter* painter = new QPainter;
    painter->begin(printer);
    //设置字体
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(9);

    int nPositionX,nPositionY,nWidth=4500,nHeight=4500;
    QPen pen(Qt::black, 2);
    painter->setPen(pen);
    painter->setFont(font);

    nPositionX=450;
    nPositionY=500;
    int n_rect_width=nWidth-nPositionX*2;
    int n_rect_height=120;

    QRect rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*7);
    drawGeneralTablePart(painter,rect,m_IecReport);

    nPositionY=nPositionY+n_rect_height*7+100;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);
    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawGlobalResultPart(painter,rect,m_IecReport);

    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    SingleItemTestInfo stTestInfo;
    dealSingleItemTestInfo(OVERALL_IMAGE_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*3;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*5);
    dealSingleItemTestInfo(GREYSCALE_RESOLUTION_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*5;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*5);
    dealSingleItemTestInfo(LUMINANCE_RESPONSE_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*5;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    dealSingleItemTestInfo(LUMINANCE_UNIFORMITY_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*3;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    dealSingleItemTestInfo(CHROMATICITY_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*3;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    dealSingleItemTestInfo(CLINICAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height);
    painter->drawRect(rect);
    rect=QRect(nPositionX+20,nPositionY+25,n_rect_width-20,n_rect_height-25);
    painter->drawText(rect,tr("Quantitative evaluations"));

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*9);
    dealSingleItemTestInfo(A5_BASIC_LUMINANCE_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("1"));
    printer->newPage();

    nPositionY=500;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*21);
    dealSingleItemTestInfo(A5_LUMINANCE_RESPONSE_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*21;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*5);
    dealSingleItemTestInfo(A1_MULTIPLE_LUMINANCE_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*5;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*8);
    dealSingleItemTestInfo(A1_LUMINANCE_UNIFORMITY_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("2"));
    printer->newPage();

    nPositionY=500;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*2;
    n_rect_height=150;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*22);
    dealSingleItemTestInfo(GREYSCALE_CHROMATICITY_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo,GREYSCALE_CHROMATICITY_EVALUATION);

    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("3"));
    painter->end();
}

void CreatePrintPdf::generateIECTableA6Pdf(QPrinter* printer)
{
    QPainter* painter = new QPainter;
    painter->begin(printer);
    //设置字体
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(9);

    int nPositionX,nPositionY,nWidth=4500,nHeight=4500;
    QPen pen(Qt::black, 2);
    painter->setPen(pen);
    painter->setFont(font);

    nPositionX=450;
    nPositionY=500;
    int n_rect_width=nWidth-nPositionX*2;
    int n_rect_height=120;

    QRect rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*7);
    drawGeneralTablePart(painter,rect,m_IecReport);

    nPositionY=nPositionY+n_rect_height*7+100;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);
    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawGlobalResultPart(painter,rect,m_IecReport);

    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    SingleItemTestInfo stTestInfo;
    dealSingleItemTestInfo(OVERALL_IMAGE_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*3;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*3);
    dealSingleItemTestInfo(LUMINANCE_UNIFORMITY_VISUAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*3;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    dealSingleItemTestInfo(CLINICAL_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height);
    painter->drawRect(rect);
    rect=QRect(nPositionX+20,nPositionY+25,n_rect_width-20,n_rect_height-25);
    painter->drawText(rect,tr("Quantitative evaluations"));

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*9);
    dealSingleItemTestInfo(A6_BASIC_LUMINANCE_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);

    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("1"));
    printer->newPage();

    nPositionY=500;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*2;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*21);
    dealSingleItemTestInfo(A6_LUMINANCE_RESPONSE_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo);


    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("2"));
    printer->newPage();

    nPositionY=500;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*2);
    drawHeaderPart(painter,rect);

    stTestInfo.strRequirement.clear();
    stTestInfo.strTestResult.clear();
    nPositionY=nPositionY+n_rect_height*2;
    n_rect_height=150;
    rect=QRect(nPositionX,nPositionY,n_rect_width,n_rect_height*22);
    dealSingleItemTestInfo(GREYSCALE_CHROMATICITY_EVALUATION,m_IecReport,stTestInfo);
    drawSingleItemPart(painter,rect,stTestInfo,GREYSCALE_CHROMATICITY_EVALUATION);

    rect=QRect(0,6000,nWidth,50);
    painter->drawText(rect,Qt::AlignCenter,tr("3"));
    painter->end();
}

void CreatePrintPdf::drawGeneralTablePart(QPainter *painter, QRect rect, StIecReport IecReport)
{
   QStringList strInfo;
   QDate date=QDate::fromString(IecReport.QaSetupInfo.TestSetupInfo.TestDate,"yyyy-MM-dd");
   QString strMonth;
   switch (date.month()) {
   case JANUARY:
        strMonth=tr("January");
       break;
   case FEBRUARY:
        strMonth=tr("February");
       break;
   case MARCH:
        strMonth=tr("March");
       break;
   case APRIL:
        strMonth=tr("April");
       break;
   case MAY:
        strMonth=tr("May");
       break;
   case JUNE:
        strMonth=tr("June");
       break;
   case JULY:
        strMonth=tr("July");
       break;
   case AUGUST:
        strMonth=tr("Auhust");
       break;
   case SEPTEMBER:
        strMonth=tr("September");
       break;
   case OCTOBER:
        strMonth=tr("October");
       break;
   case NOVEMBER:
        strMonth=tr("November");
       break;
   case DECEMBER:
        strMonth=tr("December");
       break;
   default:
       break;
   }
   QString strType,strOrientation,strDisplayPurpose;
   if(IecReport.DisplayInfo.DisplayNameInfo.DisplayTypeIndex==0)
       strType=tr("LCD");
   if(IecReport.DisplayInfo.DisplayNameInfo.DisplayOrentationIndex==0)
       strOrientation=tr("Landscape");
   else
       strOrientation=tr("Portrait");

   if(IecReport.DisplayInfo.DisplayNameInfo.blIsDiagnostic)
       strDisplayPurpose=tr("Diagnostic");
   else
       strDisplayPurpose=tr("Reviewing");
   strInfo<<tr("General")
          <<tr("Date of test: %1 %2 %3").arg(strMonth).arg(date.day()).arg(date.year())
          <<tr("Test performed by: %1").arg(IecReport.QaSetupInfo.TestSetupInfo.TestCompany)
          //<<tr("Facility: %1").arg("St.John’s facility,Jonathan Street 55,John’s City,John’s Country")
          <<tr("Location: %1").arg(IecReport.WorkstationInfo.Location)
          <<tr("Display: %1,%2,%3").arg(strType).arg(strOrientation).arg(IecReport.DisplayInfo.DisplayNameInfo.SN)
          <<tr("Application: %1,%2").arg(strDisplayPurpose).arg(IecReport.WorkstationInfo.WorkstationName);
   painter->drawRect(rect);
   int n_row_num=6;
   for(int i=0;i<n_row_num;i++)
       painter->drawText(QRect(rect.left()+25,rect.top()+(i*rect.height()/n_row_num),rect.width()-25,rect.height()/n_row_num),Qt::AlignVCenter,strInfo.at(i));

   painter->drawLine(rect.left(),rect.top()+rect.height()/n_row_num,rect.left()+rect.width(),rect.top()+rect.height()/n_row_num);
}

void CreatePrintPdf::drawGlobalResultPart(QPainter *painter, QRect rect, StIecReport IecReport)
{
    QString strResult;
    if(IecReport.OverviewInfo.OverallTestResultIndex==RESULT_OK)
        strResult=tr("OK");
    else
        strResult=tr("Fail");
    double n_offset_width=rect.width()/8.5;
    int n_offset_height=rect.height()/2;
    int nOffsetPosition=35;
    QRect temp_rect=QRect(rect.left(),rect.top(),n_offset_width*7.5,n_offset_height);
    painter->drawRect(temp_rect);
    temp_rect=QRect(rect.left()+nOffsetPosition,rect.top(),n_offset_width*7.5-nOffsetPosition,n_offset_height);
    painter->drawText(temp_rect,Qt::AlignVCenter,tr("Global test result:"));
    temp_rect=QRect(rect.left()+n_offset_width*7.5,rect.top(),n_offset_width+1,n_offset_height);
    painter->drawRect(temp_rect);
     temp_rect=QRect(rect.left()+n_offset_width*7.5+nOffsetPosition,rect.top(),n_offset_width+1-nOffsetPosition,n_offset_height);
    painter->drawText(temp_rect,Qt::AlignVCenter,strResult);

    temp_rect=QRect(rect.left(),rect.top()+n_offset_height,rect.width(),n_offset_height);
    painter->drawRect(temp_rect);
    temp_rect=QRect(rect.left()+nOffsetPosition,rect.top()+n_offset_height,rect.width()-nOffsetPosition,n_offset_height);
    painter->drawText(temp_rect,Qt::AlignVCenter,tr("Visualevaluations"));
}

void CreatePrintPdf::drawSingleItemPart(QPainter *painter, QRect rect, SingleItemTestInfo stTestInfo,SingleItemTestIndex nTsetIndex)
{
   double n_offset_width=rect.width()/8.5;
   double n_offset_height=rect.height()/(stTestInfo.nRequirementBilinear+stTestInfo.nTestResultBilinear);
   QBrush brush=QBrush(QColor(200,200,200));
   QRect temp_rect;
   int nHOffsetPosition=40;
   int nVOffsetPosition=25;
   painter->setBrush(brush);
   temp_rect=QRect(rect.left(),rect.top(),n_offset_width*2.5,rect.height());
   painter->drawRect(temp_rect);
   temp_rect=QRect(rect.left()+nHOffsetPosition,rect.top()+nVOffsetPosition,n_offset_width*2.5,rect.height()-nVOffsetPosition);
   painter->drawText(temp_rect,stTestInfo.strEvaluationMethod);

   temp_rect=QRect(rect.left()+n_offset_width*2.5,rect.top(),n_offset_width*2,rect.height());
   painter->drawRect(temp_rect);
   temp_rect=QRect(rect.left()+n_offset_width*2.5+nHOffsetPosition,rect.top()+nVOffsetPosition,n_offset_width*2-nHOffsetPosition,rect.height()-nVOffsetPosition);
   painter->drawText(temp_rect,stTestInfo.strEquipment);

   temp_rect=QRect(rect.left()+n_offset_width*4.5,rect.top(),n_offset_width*3,n_offset_height*stTestInfo.nRequirementBilinear);
   painter->drawRect(temp_rect);
   double db_rect_height=n_offset_height*stTestInfo.nRequirementBilinear;
   for(int i=0;i<stTestInfo.strRequirement.size();i++)
   {
       if(stTestInfo.strRequirement.size()==1)
       {
           temp_rect=QRect(rect.left()+n_offset_width*4.5+nHOffsetPosition,rect.top()+i*n_offset_height+nVOffsetPosition,n_offset_width*3-nHOffsetPosition,n_offset_height-nVOffsetPosition);
           painter->drawText(temp_rect,stTestInfo.strRequirement.at(i));
       }else
       {
           temp_rect=QRect(rect.left()+n_offset_width*4.5+nHOffsetPosition,rect.top()+i*n_offset_height,n_offset_width*3-nHOffsetPosition,n_offset_height);
           painter->drawText(temp_rect,Qt::AlignVCenter,stTestInfo.strRequirement.at(i));
       }
   }


   painter->setBrush(Qt::NoBrush);
   temp_rect=QRect(rect.left()+n_offset_width*4.5,rect.top()+n_offset_height*stTestInfo.nRequirementBilinear,n_offset_width*3,n_offset_height*stTestInfo.nTestResultBilinear);
   painter->drawRect(temp_rect);
   for(int i=0;i<stTestInfo.strTestResult.size();i++)
   {
       if(stTestInfo.strTestResult.size()==1)
       {
           temp_rect=QRect(rect.left()+n_offset_width*4.5+nHOffsetPosition,rect.top()+db_rect_height+i*n_offset_height+nVOffsetPosition,n_offset_width*3-nHOffsetPosition,n_offset_height-nVOffsetPosition);
           painter->drawText(temp_rect,stTestInfo.strTestResult.at(i));
       }else
       {
           switch (nTsetIndex) {
           case PIXEL_FAULTS_EVALUATION:
               if(i==1)
               {
                   temp_rect=QRect(rect.left()+n_offset_width*4.5+nHOffsetPosition,rect.top()+db_rect_height+i*n_offset_height,n_offset_width*3-nHOffsetPosition,n_offset_height*2);
                   painter->drawText(temp_rect,stTestInfo.strTestResult.at(i));
               }
               else
               {
                   temp_rect=QRect(rect.left()+n_offset_width*4.5+nHOffsetPosition,rect.top()+db_rect_height+i*n_offset_height,n_offset_width*3-nHOffsetPosition,n_offset_height);
                   painter->drawText(temp_rect,Qt::AlignVCenter,stTestInfo.strTestResult.at(i));
               }
               break;
           case GREYSCALE_CHROMATICITY_EVALUATION:
               if(i==0)
                   temp_rect=QRect(rect.left()+n_offset_width*4.5+nHOffsetPosition,rect.top()+db_rect_height,n_offset_width*3-nHOffsetPosition,n_offset_height);
               else if((i>0) && (i<4))
                   temp_rect=QRect(rect.left()+n_offset_width*4.5+nHOffsetPosition,rect.top()+db_rect_height+(i-1)*n_offset_height*1.5+n_offset_height,n_offset_width*3-nHOffsetPosition,n_offset_height*1.5);
               else
                   temp_rect=QRect(rect.left()+n_offset_width*4.5+nHOffsetPosition,rect.top()+db_rect_height+(i+1.5)*n_offset_height,n_offset_width*3-nHOffsetPosition,n_offset_height);
               painter->drawText(temp_rect,Qt::AlignVCenter,stTestInfo.strTestResult.at(i));
               break;
           default:
               temp_rect=QRect(rect.left()+n_offset_width*4.5+nHOffsetPosition,rect.top()+db_rect_height+i*n_offset_height,n_offset_width*3-nHOffsetPosition,n_offset_height);
               painter->drawText(temp_rect,Qt::AlignVCenter,stTestInfo.strTestResult.at(i));
               break;
           }
       }
   }

   temp_rect=QRect(rect.left()+n_offset_width*7.5,rect.top(),n_offset_width,rect.height());
   painter->drawRect(temp_rect);
   temp_rect=QRect(rect.left()+n_offset_width*7.5+nHOffsetPosition,rect.top()+nVOffsetPosition,n_offset_width-nHOffsetPosition,rect.height()-nVOffsetPosition);
   painter->drawText(temp_rect,stTestInfo.strConclusion);
}

void CreatePrintPdf::dealSingleItemTestInfo(SingleItemTestIndex enIndex,StIecReport IecReport, SingleItemTestInfo &stTestInfo)
{
    Visual_Evaluation_Data stVisualEvaluation=IecReport.DisplayInfo.VisualEvaluationInfo;
    StQaLuminace stQaData=IecReport.DisplayInfo.stGrayscaleQaInfo;
    Luminance_Deviation_Data stLuminaceDeviationData=IecReport.DisplayInfo.LuminanceDeviationInfo;
    Basic_Luminance_Data stBasicLuminance=IecReport.DisplayInfo.BasicLuminanceInfo;
    StAngularView stAngularView=IecReport.DisplayInfo.AngularViewInfo;
    StChromaticityEvaluation stChromaticityEvaluation=IecReport.DisplayInfo.ChromaticityEvaluationInfo;
    StGreyscaleChromaticityEvaluation stGreyscaleChromaticity=IecReport.DisplayInfo.GreyscaleChromaticityInfo;
    double dbScore;
    double db_L_Min,db_L_Max;
    double db_deviation=0,db_max_deviation=0,db_std_deviation;
    double *p_data;
    double db_ambient=0;
    Contrast_response_Data  data_buffer;
    data_buffer.stQaData=stQaData;
    CCurvTypeMothed cuver_type;
    double *p_data_u=&stChromaticityEvaluation.dbTopLeftU;
    double *p_data_v=&stChromaticityEvaluation.dbTopLeftV;

    switch (enIndex) {
    case OVERALL_IMAGE_VISUAL_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("Overall image quality \nevaluation\n\n–Verify overall performance");
        stTestInfo.strEquipment=tr("TG18-QC TEST \nPATTERN");
        stTestInfo.strRequirement<<tr("All appearances OK and no defects found");
        stTestInfo.strTestResult<<tr("NO");
        if(stVisualEvaluation.ViasulEvaluationIndex[stVisualEvaluation.OVERALL_QUALITY]==RESULT_OK)
            stTestInfo.strConclusion=tr("OK");
        else
            stTestInfo.strConclusion=tr("Fail");
        break;
    case GREYSCALE_RESOLUTION_VISUAL_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("Greyscale resolution evaluation\n\n–Verify sufficient greyscale\n  resolution based on 8-\n  and 10-bit markers");
        stTestInfo.strEquipment=tr("TG18-MP TEST \nPATTERN");
        stTestInfo.strRequirement<<tr("> 8 Bit");
        stTestInfo.strTestResult<<tr("Resolution matches the 8-bit markers");
        if(stVisualEvaluation.ViasulEvaluationIndex[stVisualEvaluation.GRASCALE_RESOLUTION]==RESULT_OK)
            stTestInfo.strConclusion=tr("OK");
        else
            stTestInfo.strConclusion=tr("Fail");
        break;
     case LUMINANCE_RESPONSE_VISUAL_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("LUMINANCE response evaluation(more complete solution than the corresponding evaluation within overall image quality evaluation)");
        stTestInfo.strEquipment=tr("TG18-CT TEST \nPATTERN");
        stTestInfo.strRequirement<<tr("All squares and half moons are visible");
        stTestInfo.strTestResult<<tr("Yes");
        if(stVisualEvaluation.ViasulEvaluationIndex[stVisualEvaluation.LUMINANCE_RESPOSE]==RESULT_OK)
            stTestInfo.strConclusion=tr("OK");
        else
            stTestInfo.strConclusion=tr("Fail");
        break;
     case LUMINANCE_UNIFORMITY_VISUAL_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("LUMINANCE uniformity evaluation\n\n–Look for non-uniformities");
        stTestInfo.strEquipment=tr("TG18-UN80 TEST \nPATTERN");
        stTestInfo.strRequirement<<tr("No visual non-uniformities detected");
        stTestInfo.strTestResult<<tr("NO");
        if(stVisualEvaluation.ViasulEvaluationIndex[stVisualEvaluation.LUMINCE_UNIFORMITY]==RESULT_OK)
            stTestInfo.strConclusion=tr("OK");
        else
            stTestInfo.strConclusion=tr("Fail");
        break;
     case CHROMATICITY_VISUAL_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("Chromaticity evaluation\n\n–Verify colour uniformity");
        stTestInfo.strEquipment=tr("TG18-UN80 TEST \nPATTERN");
        stTestInfo.strRequirement<<tr("No visual non-uniformities on colour detected");
        stTestInfo.strTestResult<<tr("None");
        if(stVisualEvaluation.ViasulEvaluationIndex[stVisualEvaluation.CHROMATICITY]==RESULT_OK)
            stTestInfo.strConclusion=tr("OK");
        else
            stTestInfo.strConclusion=tr("Fail");
        break;
     case PIXEL_FAULTS_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("Pixel faults evaluation\n\n– Look for dark(TG18-UN80) and bright(TG18-UN10) pixel defects");
        stTestInfo.strEquipment=tr("TG18-UN10 and\nTG18-UN80 TEST \nPATTERN");
        stTestInfo.strRequirement<<tr("type A:<=1")
                                 <<tr("type B:<=1")
                                 <<tr("type C:<=2")
                                 <<tr("None in the same cluster");
        stTestInfo.strTestResult<<tr("Detected pixel faults:")
                                <<tr("%1 type A(<=1),%2 type B(<=1),\n%3 type C(<=2),none in the same\ncluster").arg(
                                      stVisualEvaluation.PixelFaultsData[stVisualEvaluation.PIXEL_FAULTS_TYPE_A]).arg(
                                      stVisualEvaluation.PixelFaultsData[stVisualEvaluation.PIXEL_FAULTS_TYPE_B]).arg(
                                      stVisualEvaluation.PixelFaultsData[stVisualEvaluation.PIXEL_FAULTS_TYPE_C]);
        if(stVisualEvaluation.PixelFaultsData[stVisualEvaluation.PIXEL_FAULTS_TYPE_RESULT]==RESULT_OK)
            stTestInfo.strConclusion=tr("OK");
        else
            stTestInfo.strConclusion=tr("Fail");
        stTestInfo.nRequirementBilinear=4;
        stTestInfo.nTestResultBilinear=3;
        break;
     case A1_ANGULAR_VIEWING_EVALUATION:
     case A2_ANGULAR_VIEWING_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("Angular viewing evaluation\n\n– Verify viewing angle");
        stTestInfo.strEquipment=tr("ANG TEST PATTERN");
        if(enIndex==A1_ANGULAR_VIEWING_EVALUATION)
            dbScore=0.9;
        else
            dbScore=0.75;
        stTestInfo.strRequirement<<tr("SCORE:>=%1").arg(dbScore);
        stTestInfo.strTestResult<<tr("Centre score:%1").arg(stAngularView.nMiddleCenter)
                                <<tr("Top-left score:%1").arg(stAngularView.nTopLeft)
                                <<tr("Top-centre score:%1").arg(stAngularView.nTopMiddle)
                                <<tr("Top-right score:%1").arg(stAngularView.nTopRight)
                                <<tr("Centre-right score:%1").arg(stAngularView.nMiddleRight)
                                <<tr("Bottom-right score:%1").arg(stAngularView.nBottomRight)
                                <<tr("Bottom-centre score:%1").arg(stAngularView.nBottomMiddle)
                                <<tr("Bottom-left score:%1").arg(stAngularView.nBottomLeft)
                                <<tr("Centre-left score:%1").arg(stAngularView.nMiddleLeft)
                                <<tr("SCORE:%1/10").arg(QString::number(stAngularView.dbAverageValue,'f',2));
        if(stAngularView.dbAverageValue/10>=dbScore)
            stTestInfo.strConclusion=tr("OK");
        else
            stTestInfo.strConclusion=tr("Fail");
        stTestInfo.nRequirementBilinear=1;
        stTestInfo.nTestResultBilinear=10;
        break;
     case CLINICAL_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("Clinical evaluation");
        stTestInfo.strEquipment=tr("Clinical TEST PATTERN\nTG18-CH,TG18-KN");
        stTestInfo.strRequirement<<tr("Clinical image sappear OK");
        stTestInfo.strTestResult<<tr("Yes");
        if(stVisualEvaluation.ImageResultIndex==RESULT_OK)
            stTestInfo.strConclusion=tr("OK");
        else
            stTestInfo.strConclusion=tr("Fail");
        stTestInfo.nRequirementBilinear=1;
        stTestInfo.nTestResultBilinear=1;
        break;
     case A1_BASIC_LUMINANCE_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("Basic LUMINANCE evaluation");
        stTestInfo.strEquipment=tr("LUMINANCE meter");
        stTestInfo.strRequirement<<tr("Lmax deviation<±5% of 500 cd/m2")
                                 <<tr("r′>250")
                                 <<tr("a<0.4")
                                 <<tr("Lmax>170 cd/m2");
        if(stBasicLuminance.AmbientType)
            db_ambient=stBasicLuminance.llluminanceE0*stBasicLuminance.DiffusionCoefficient;
        else
            db_ambient=stBasicLuminance.Lamb;
        stTestInfo.strTestResult<<tr("Measured with method A(B.2.1)")
                                <<tr("L′max=%1 cd/m2").arg(QString::number(stBasicLuminance.DisplayLuminanceMax+db_ambient))
                                <<tr("L′min=%1 cd/m2").arg(QString::number(stBasicLuminance.DisplayLuminanceMin+db_ambient))
                                <<tr("Lamb=%1 cd/m2").arg(stBasicLuminance.Lamb)
                                <<tr("Lmax=%1 cd/m2").arg(stBasicLuminance.DisplayLuminanceMax)
                                <<tr("r′=%1").arg(QString::number((stBasicLuminance.DisplayLuminanceMax+db_ambient)/(stBasicLuminance.DisplayLuminanceMin+db_ambient),'f',2))
                                <<tr("a=%1").arg(QString::number(db_ambient/stBasicLuminance.DisplayLuminanceMin,'f',2));
        if(((stBasicLuminance.DisplayLuminanceMax+db_ambient)/(stBasicLuminance.DisplayLuminanceMin+db_ambient)>250)
                && ((db_ambient/stBasicLuminance.DisplayLuminanceMin)<0.4) &&
            (stBasicLuminance.DisplayLuminanceMax>170))
            stTestInfo.strConclusion=tr("OK");
        else
            stTestInfo.strConclusion=tr("Fail");
        stTestInfo.nRequirementBilinear=4;
        stTestInfo.nTestResultBilinear=7;
        break;
    case A2_BASIC_LUMINANCE_EVALUATION:
    case A4_BASIC_LUMINANCE_EVALUATION:
    case A6_BASIC_LUMINANCE_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("Basic LUMINANCE evaluation");
        stTestInfo.strEquipment=tr("LUMINANCE meter,\nILLUMINANCE meter");
        if(stBasicLuminance.AmbientType)
            db_ambient=stBasicLuminance.llluminanceE0*stBasicLuminance.DiffusionCoefficient;
        else
            db_ambient=stBasicLuminance.Lamb;
        if(enIndex==A2_BASIC_LUMINANCE_EVALUATION)
        {
            stTestInfo.strRequirement<<tr("r'>250")
                                    <<tr("a<0.4");
            stTestInfo.strTestResult<<tr("Measured with method C(B.2.3)");
            stTestInfo.nRequirementBilinear=2;
            stTestInfo.nTestResultBilinear=8;
            if(((stBasicLuminance.DisplayLuminanceMax+db_ambient)/(stBasicLuminance.DisplayLuminanceMin+db_ambient)>250)
                    && ((db_ambient/stBasicLuminance.DisplayLuminanceMin)<0.4))
                stTestInfo.strConclusion=tr("OK");
            else
                stTestInfo.strConclusion=tr("Fail");
        }else if(enIndex==A4_BASIC_LUMINANCE_EVALUATION)
        {
            stTestInfo.strRequirement<<tr("r'>100");
            stTestInfo.strTestResult<<tr("Measured with method C(B.2.3)");
            stTestInfo.nRequirementBilinear=1;
            stTestInfo.nTestResultBilinear=8;
            if((stBasicLuminance.DisplayLuminanceMax+db_ambient)/(stBasicLuminance.DisplayLuminanceMin+db_ambient)>100)
                stTestInfo.strConclusion=tr("OK");
            else
                stTestInfo.strConclusion=tr("Fail");
        }else
        {
            stTestInfo.strRequirement<<tr("r'>100");
            stTestInfo.strTestResult<<tr("Measured with method B(B.2.2)");
            stTestInfo.nRequirementBilinear=1;
            stTestInfo.nTestResultBilinear=8;
            if((stBasicLuminance.DisplayLuminanceMax+db_ambient)/(stBasicLuminance.DisplayLuminanceMin+db_ambient)>100)
                stTestInfo.strConclusion=tr("OK");
            else
                stTestInfo.strConclusion=tr("Fail");
        }      
        stTestInfo.strTestResult<<tr("Lmax=%1 cd/m2").arg(stBasicLuminance.DisplayLuminanceMax)
                                <<tr("Lmin=%1 cd/m2").arg(stBasicLuminance.DisplayLuminanceMin)
                                <<tr("E=%1 lux").arg(stBasicLuminance.llluminanceE0)
                                <<tr("Rd=%1").arg(stBasicLuminance.DiffusionCoefficient)
                                <<tr("Lamb=%1 cd/m2").arg(stBasicLuminance.Lamb)
                                <<tr("r'=%1").arg(QString::number((stBasicLuminance.DisplayLuminanceMax+db_ambient)/(stBasicLuminance.DisplayLuminanceMin+db_ambient),'f',2))
                                <<tr("a=%1").arg(QString::number(db_ambient/stBasicLuminance.DisplayLuminanceMin,'f',2));
        break;
     case A3_BASIC_LUMINANCE_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("Basic LUMINANCE evaluation");
        stTestInfo.strEquipment=tr("LUMINANCE meter\nManufacturer X\nInstrument Y–S/N\n98832");
        stTestInfo.strRequirement<<tr("Lmax deviation<±10% of 400 cd/m2")
                                 <<tr("r′>100");
        stTestInfo.strTestResult<<tr("Measured with method A(B.2.1)")
                                <<tr("L′max=418.2 cd/m2")
                                <<tr("L′min=2.01 cd/m2")
                                <<tr("Lamb=1.5 cd/m2")
                                <<tr("r′=208")
                                <<tr("a=0.746");
        stTestInfo.strConclusion=tr("OK");
        stTestInfo.nRequirementBilinear=2;
        stTestInfo.nTestResultBilinear=6;
        break;
    case A5_BASIC_LUMINANCE_EVALUATION:
       stTestInfo.strEvaluationMethod=tr("Basic LUMINANCE evaluation");
       stTestInfo.strEquipment=tr("LUMINANCE meter");
       stTestInfo.strRequirement<<tr("Lmax deviation<±10% of 300 cd/m2")
                                <<tr("r′>100");
       stTestInfo.strTestResult<<tr("Measured with method A(B.2.1)")
                               <<tr("L′max=418.2 cd/m2")
                               <<tr("L′min=2.01 cd/m2")
                               <<tr("Lamb=1.5 cd/m2")
                               <<tr("Lmax=283.8 cd/m2")
                               <<tr("r′=208")
                               <<tr("a=0.746");
       stTestInfo.strConclusion=tr("OK");
       stTestInfo.nRequirementBilinear=2;
       stTestInfo.nTestResultBilinear=7;
       break;
     case A1_LUMINANCE_RESPONSE_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("LUMINANCE response evaluation");
        stTestInfo.strEquipment=tr("LUMINANCE meter");
        stTestInfo.strRequirement<<tr("Max. deviation<15%");
        stTestInfo.strTestResult<<tr("Measured with method C(B.2.1)");
        cuver_type.WorkDicomCurveData(&data_buffer);
        for(int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
        {
            if(i<DICOM_GSDF_GRAYSCALE_NUMBER/2)
                stTestInfo.strTestResult<<tr("L'(LN0%1)=%2 cd/m2").arg(i+1).arg(stQaData.dbCurentLuminace[i]);
            else
                stTestInfo.strTestResult<<tr("L'(LN%1)=%2 cd/m2").arg(i+1).arg(stQaData.dbCurentLuminace[i]);
            if(i<DICOM_GSDF_GRAYSCALE_NUMBER-1)
                db_max_deviation=qMax(db_max_deviation,data_buffer.dbDevationPercent[i]);
        }
        stTestInfo.strTestResult<<tr("Max. deviation=%1%").arg(QString::number(db_max_deviation*100,'f',2));
        if(db_max_deviation*100<15)
            stTestInfo.strConclusion=tr("OK");
        else
            stTestInfo.strConclusion=tr("Fail");
        stTestInfo.nRequirementBilinear=1;
        stTestInfo.nTestResultBilinear=20;
        break;
    case A3_LUMINANCE_RESPONSE_EVALUATION:
    case A5_LUMINANCE_RESPONSE_EVALUATION:
       stTestInfo.strEvaluationMethod=tr("LUMINANCE response evaluation");
       if(enIndex==A3_LUMINANCE_RESPONSE_EVALUATION)
            stTestInfo.strEquipment=tr("LUMINANCE meter\nManufacturer X\nInstrument Y–S/N\n98832");
       else
           stTestInfo.strEquipment=tr("LUMINANCE meter");
       stTestInfo.strRequirement<<tr("Max. deviation<30%");
       stTestInfo.strTestResult<<tr("Measured with method A(B.2.1)");
       cuver_type.WorkDicomCurveData(&data_buffer);
       for(int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
       {
           if(i<DICOM_GSDF_GRAYSCALE_NUMBER/2)
               stTestInfo.strTestResult<<tr("L'(LN0%1)=%2 cd/m2").arg(i+1).arg(QString::number(stQaData.dbCurentLuminace[i],'f'),4);
           else
               stTestInfo.strTestResult<<tr("L'(LN%1)=%2 cd/m2").arg(i+1).arg(QString::number(stQaData.dbCurentLuminace[i],'f'),4);
           if(i<DICOM_GSDF_GRAYSCALE_NUMBER-1)
               db_max_deviation=qMax(db_max_deviation,data_buffer.dbDevationPercent[i]);
       }
       stTestInfo.strTestResult<<tr("Max. deviation=%1%").arg(QString::number(db_max_deviation,'f',2));
       if(db_max_deviation<30)
           stTestInfo.strConclusion=tr("OK");
       else
           stTestInfo.strConclusion=tr("Fail");
       stTestInfo.nRequirementBilinear=1;
       stTestInfo.nTestResultBilinear=20;
       break;
    case A1_MULTIPLE_LUMINANCE_EVALUATION:
    case A3_MULTIPLE_LUMINANCE_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("LUMINANCE evaluation of multiple displays");
        if(enIndex==A1_MULTIPLE_LUMINANCE_EVALUATION)
            stTestInfo.strEquipment=tr("LUMINANCE meter");
        else
            stTestInfo.strEquipment=tr("LUMINANCE meter\nManufacturer X\nInstrument Y–S/N\n98832");
        stTestInfo.strRequirement<<tr("Deviation<10%");
        db_deviation=2*(stLuminaceDeviationData.HLmax-stLuminaceDeviationData.LLmax)/(stLuminaceDeviationData.LLmax+stLuminaceDeviationData.HLmax);
        stTestInfo.strTestResult<<tr("Measured with method A(B.2.1)")
                                <<tr("L′max=%1 cd/m2").arg(stLuminaceDeviationData.HLmax)
                                <<tr("L′max=%1 cd/m2").arg(stLuminaceDeviationData.LLmax)
                                <<tr("Deviation=%").arg(QString::number(db_deviation*100,'f',2));
        if(db_deviation<10)
            stTestInfo.strConclusion=tr("OK");
        else
            stTestInfo.strConclusion=tr("Fail");
        stTestInfo.nRequirementBilinear=1;
        stTestInfo.nTestResultBilinear=4;
        break;
    case CHROMATICITY_QUANTITATIVE_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("Chromaticity evaluation");
        stTestInfo.strEquipment=tr("Colour meter");
        stTestInfo.strRequirement<<tr("Max. deviation<0.02");
        for (int i=0;i<9;i++)
        {

            if((stChromaticityEvaluation.PointNumber==5)&&(i%2==1) )
                continue;

            for(int j=0;j<9;j++)
            {
                if((stChromaticityEvaluation.PointNumber==5)&&(j%2==1) )
                    continue;
                db_deviation=sqrt(pow((p_data_u[j]-p_data_u[i]),2)+pow((p_data_v[j]-p_data_v[i]),2));
                db_max_deviation=qMax(db_max_deviation,db_deviation);
            }
        }
        if(stChromaticityEvaluation.PointNumber==5)
        {
            stTestInfo.strTestResult<<tr("Measured with method B(B.2.2)")
                                <<tr("Top-left u'=%1 v'=%2").arg(stChromaticityEvaluation.dbTopLeftU).arg(stChromaticityEvaluation.dbTopLeftV)
                                <<tr("Top-right u'=%1 v'=%2").arg(stChromaticityEvaluation.dbTopRightU).arg(stChromaticityEvaluation.dbTopRightV)
                                <<tr("Centre u'=%1 v'=%2").arg(stChromaticityEvaluation.dbCenterU).arg(stChromaticityEvaluation.dbCenterV)
                                <<tr("Bottom-right u'=%1 v'=%2").arg(stChromaticityEvaluation.dbBottomRightU).arg(stChromaticityEvaluation.dbBottomRightV)
                                <<tr("Bottom-left u'=%1 v'=%2").arg(stChromaticityEvaluation.dbBottomLeftU).arg(stChromaticityEvaluation.dbBottomLeftV)
                                <<tr("Max. deviation=%1").arg(QString::number(db_max_deviation,'f',4));
            stTestInfo.nTestResultBilinear=7;
        }else
        {
            stTestInfo.strTestResult<<tr("Measured with method B(B.2.2)")
                                <<tr("Top-left u'=%1 v'=%2").arg(stChromaticityEvaluation.dbTopLeftU).arg(stChromaticityEvaluation.dbTopLeftV)
                                <<tr("Top-middle u'=%1 v'=%2").arg(stChromaticityEvaluation.dbTopMiddleU).arg(stChromaticityEvaluation.dbTopMiddleV)
                                <<tr("Top-right u'=%1 v'=%2").arg(stChromaticityEvaluation.dbTopRightU).arg(stChromaticityEvaluation.dbTopRightV)
                                <<tr("Middle-left u'=%1 v'=%2").arg(stChromaticityEvaluation.dbMiddleLeftU).arg(stChromaticityEvaluation.dbMiddleLeftV)
                                <<tr("Centre u'=%1 v'=%2").arg(stChromaticityEvaluation.dbCenterU).arg(stChromaticityEvaluation.dbCenterV)
                                <<tr("Middle-right u'=%1 v'=%2").arg(stChromaticityEvaluation.dbMiddleRightU).arg(stChromaticityEvaluation.dbMiddleRightV)
                                <<tr("Bottom-right u'=%1 v'=%2").arg(stChromaticityEvaluation.dbBottomRightU).arg(stChromaticityEvaluation.dbBottomRightV)
                                <<tr("Bottom-middle u'=%1 v'=%2").arg(stChromaticityEvaluation.dbBottomMiddlU).arg(stChromaticityEvaluation.dbBottomMiddlV)
                                <<tr("Bottom-left u'=%1 v'=%2").arg(stChromaticityEvaluation.dbBottomLeftU).arg(stChromaticityEvaluation.dbBottomLeftV)
                                <<tr("Max. deviation=%1").arg(QString::number(db_max_deviation,'f',4));
            stTestInfo.nTestResultBilinear=11;
        }
        if(db_max_deviation<0.02)
            stTestInfo.strConclusion=tr("OK");
        else
            stTestInfo.strConclusion=tr("Fail");
        stTestInfo.nRequirementBilinear=1;
        break;
    case MULTIPLE_CHROMATICITY_QUANTITATIVE_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("Chromaticity evaluation of multiple displays");
        stTestInfo.strEquipment=tr("Colour meter");
        stTestInfo.strRequirement<<tr("Deviation<0.02");
        stTestInfo.strTestResult<<tr("Measured with method B(B.2.2)")
                                <<tr("Centre u'=%1 v'=%2").arg(stChromaticityEvaluation.dbCenterU).arg(stChromaticityEvaluation.dbCenterV)
                                <<tr("Other display:")
                                <<tr("Centre u'=0.2046 v'=0.4699")
                                <<tr("Deviation=0.0029");
        stTestInfo.strConclusion=tr("OK");
        stTestInfo.nRequirementBilinear=1;
        stTestInfo.nTestResultBilinear=5;
        break;
    case A1_LUMINANCE_UNIFORMITY_EVALUATION:
    case A3_LUMINANCE_UNIFORMITY_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("LUMINANCE uniformity evaluation");
        if(enIndex==A1_LUMINANCE_UNIFORMITY_EVALUATION)
            stTestInfo.strEquipment=tr("LUMINANCE meter");
        else
            stTestInfo.strEquipment=tr("LUMINANCE meter\nManufacturer X\nInstrument Y–S/N\n98832");
        stTestInfo.strRequirement<<tr("Max. deviation<30%");
        p_data=&stLuminaceDeviationData.TopLeftLum;
        db_L_Min=*p_data;
        db_L_Max=*p_data;
        for (int i=0;i<9;i++)
        {
            if((stLuminaceDeviationData.PointNumber==5)&&(i%2==1) )
                continue;
            db_L_Min=qMin(db_L_Min,p_data[i]);
            db_L_Max=qMax(db_L_Max,p_data[i]);
        }
        db_max_deviation=2*(db_L_Max-db_L_Min)/(db_L_Min+db_L_Max);
        if(stLuminaceDeviationData.PointNumber==5)
        {
            stTestInfo.strTestResult<<tr("Measured with method B(B.2.2)")
                                <<tr("Top-left L=%1 cd/m2").arg(stLuminaceDeviationData.TopLeftLum)
                                <<tr("Top-right L=%1 cd/m2").arg(stLuminaceDeviationData.TopRightLum)
                                <<tr("Centre L=%1 cd/m2").arg(stLuminaceDeviationData.CenterLum)
                                <<tr("Bottom-right L=%1 cd/m2").arg(stLuminaceDeviationData.BottomLeftLum)
                                <<tr("Bottom-left L=%1 cd/m2").arg(stLuminaceDeviationData.BottomRightLum)
                                <<tr("Max. deviation=%1%").arg(QString::number(db_max_deviation*100,'f',2));
            stTestInfo.nTestResultBilinear=7;
        }
        else
        {
            stTestInfo.strTestResult<<tr("Measured with method B(B.2.2)")
                                <<tr("Top-left L=%1 cd/m2").arg(stLuminaceDeviationData.TopLeftLum)
                                <<tr("Top-middle L=%1 cd/m2").arg(stLuminaceDeviationData.TopMiddleLum)
                                <<tr("Top-right L=%1 cd/m2").arg(stLuminaceDeviationData.TopRightLum)
                                <<tr("Middle-left L=%1 cd/m2").arg(stLuminaceDeviationData.MiddleLeftLum)
                                <<tr("Centre L=%1 cd/m2").arg(stLuminaceDeviationData.CenterLum)
                                <<tr("Middle-right L=%1 cd/m2").arg(stLuminaceDeviationData.MiddleRightLum)
                                <<tr("Bottom-right L=%1 cd/m2").arg(stLuminaceDeviationData.BottomLeftLum)
                                <<tr("Bottom-middle L=%1 cd/m2").arg(stLuminaceDeviationData.BottomMiddleLum)
                                <<tr("Bottom-left L=%1 cd/m2").arg(stLuminaceDeviationData.BottomRightLum)
                                <<tr("Max. deviation=%1%").arg(QString::number(db_max_deviation*100,'f',2));
            stTestInfo.nTestResultBilinear=11;
        }
        if(db_max_deviation*100<30)
            stTestInfo.strConclusion=tr("OK");
        else
            stTestInfo.strConclusion=tr("Fail");
        stTestInfo.nRequirementBilinear=1;

        break;
    case GREYSCALE_CHROMATICITY_EVALUATION:
        stTestInfo.strEvaluationMethod=tr("Greyscale chromaticity evaluation\n\n"
                                          "NOTE:This device was calibrated according to the GSDF");
        stTestInfo.strEquipment=tr("Colour meter");
        stTestInfo.strRequirement<<tr("Max. deviation<0.01");
        stTestInfo.strTestResult<<tr("Discarded measurements:(L<5 cd/m2)");
        for(int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
        {
            if(stQaData.dbCurentLuminace[i]<5)
               stTestInfo.strTestResult<<tr("LN0%1:L=%2 cd/m2 u’=%3 v’=\n%4").arg(i+1).arg(QString::number(stQaData.dbCurentLuminace[i],'f',2))
                                                                            .arg(QString::number(stGreyscaleChromaticity.dbCurrtCoordinate_u[i],'f',4))
                                                                            .arg(QString::number(stGreyscaleChromaticity.dbCurrtCoordinate_v[i],'f',4));
            else
            {
                db_deviation=sqrt(qPow((stGreyscaleChromaticity.dbCurrtCoordinate_u[i]-stGreyscaleChromaticity.dbCurrtCoordinate_u[DICOM_GSDF_GRAYSCALE_NUMBER-1]),2)+
                        qPow((stGreyscaleChromaticity.dbCurrtCoordinate_v[i]-stGreyscaleChromaticity.dbCurrtCoordinate_v[DICOM_GSDF_GRAYSCALE_NUMBER-1]),2));
                db_max_deviation=db_deviation>db_max_deviation ? db_deviation:db_max_deviation;
                if(stQaData.dbCurentLuminace[i-1]<5)
                    stTestInfo.strTestResult<<tr("Remaining measurements:");
                if(i<DICOM_GSDF_GRAYSCALE_NUMBER/2)
                    stTestInfo.strTestResult<<tr("LN0%1:u’=%2 v'=%3").arg(i+1).arg(QString::number(stGreyscaleChromaticity.dbCurrtCoordinate_u[i],'f',4))
                                              .arg(QString::number(stGreyscaleChromaticity.dbCurrtCoordinate_v[i],'f',4));
                else
                    stTestInfo.strTestResult<<tr("LN%1:u’=%2 v'=%3").arg(i+1).arg(QString::number(stGreyscaleChromaticity.dbCurrtCoordinate_u[i],'f',4))
                                              .arg(QString::number(stGreyscaleChromaticity.dbCurrtCoordinate_v[i],'f',4));
            }
        }
        stTestInfo.strTestResult<<tr("Max. deviation=%1").arg(QString::number(db_max_deviation,'f',4));
        if(db_max_deviation<0.01)
            stTestInfo.strConclusion=tr("OK");
        else
            stTestInfo.strConclusion=tr("Fail");
        stTestInfo.nRequirementBilinear=1;
        stTestInfo.nTestResultBilinear=22.5;
        break;
    case A2_LUMINANCE_RESPONSE_EVALUATION:
    case A4_LUMINANCE_RESPONSE_EVALUATION:
    case A6_LUMINANCE_RESPONSE_EVALUATION:
       stTestInfo.strEvaluationMethod=tr("LUMINANCE response evaluation");
       stTestInfo.strEquipment=tr("LUMINANCE meter,\nILLUMINANCE meter");
       switch (enIndex) {
       case A2_LUMINANCE_RESPONSE_EVALUATION:
           db_std_deviation=15;
           stTestInfo.strTestResult<<tr("Measured with method C(B.2.3)");
           break;
       case A4_LUMINANCE_RESPONSE_EVALUATION:
           db_std_deviation=30;
           stTestInfo.strTestResult<<tr("Measured with method B(B.2.3)");
           break;
       case A6_LUMINANCE_RESPONSE_EVALUATION:
           db_std_deviation=30;
           stTestInfo.strTestResult<<tr("Measured with method B(B.2.2)");
           break;
       }
       stTestInfo.strRequirement<<tr("Max. deviation<%1%").arg(QString::number(db_std_deviation,'f',0));
       cuver_type.WorkDicomCurveData(&data_buffer);
       for(int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
       {
           if(i<DICOM_GSDF_GRAYSCALE_NUMBER/2)
               stTestInfo.strTestResult<<tr("L(LN0%1)=%2 cd/m2").arg(i+1).arg(stQaData.dbCurentLuminace[i]);
           else
               stTestInfo.strTestResult<<tr("L(LN%1)=%2 cd/m2").arg(i+1).arg(stQaData.dbCurentLuminace[i]);
           if(i<DICOM_GSDF_GRAYSCALE_NUMBER-1)
               db_max_deviation=qMax(db_max_deviation,data_buffer.dbDevationPercent[i]);
       }
       stTestInfo.strTestResult<<tr("Max. deviation=%1%").arg(QString::number(db_max_deviation*100,'f',2));
       if(db_max_deviation*100<db_std_deviation)
           stTestInfo.strConclusion=tr("OK");
       else
           stTestInfo.strConclusion=tr("Fail");
       stTestInfo.nRequirementBilinear=1;
       stTestInfo.nTestResultBilinear=20;
       break;
    default:
        break;
    }
}

void CreatePrintPdf::drawHeaderPart(QPainter *painter, QRect rect)
{
    painter->drawRect(rect);
    QStringList strList;
    strList<<tr("Evaluation method")<<tr("Equipment,tools")<<tr("Requirement")<<tr("Conclusion");
    int n_column_num=4;
    QBrush brush=QBrush(QColor(200,200,200));
    QRect temp_rect;
    double n_offset_width=rect.width()/8.5;
    int n_offset_height=rect.height()/2;
    for(int i=0;i<n_column_num;i++)
    {
        switch (i) {
        case 0:
            painter->setBrush(brush);
            temp_rect=QRect(rect.left(),rect.top(),n_offset_width*2.5,n_offset_height);
            painter->drawRect(temp_rect);
            painter->drawText(temp_rect,Qt::AlignHCenter|Qt::AlignVCenter,strList.at(i));

            temp_rect=QRect(rect.left(),rect.top()+n_offset_height,n_offset_width*2.5,n_offset_height);
            painter->drawRect(temp_rect);
            break;
        case 1:
            painter->setBrush(brush);
            temp_rect=QRect(rect.left()+n_offset_width*2.5,rect.top(),n_offset_width*2,n_offset_height);
            painter->drawRect(temp_rect);
            painter->drawText(temp_rect,Qt::AlignHCenter|Qt::AlignVCenter,strList.at(i));

            temp_rect=QRect(rect.left()+n_offset_width*2.5,rect.top()+n_offset_height,n_offset_width*2,n_offset_height);
            painter->drawRect(temp_rect);
            break;
        case 2:
            painter->setBrush(brush);
            temp_rect=QRect(rect.left()+n_offset_width*4.5,rect.top(),n_offset_width*3,n_offset_height);
            painter->drawRect(temp_rect);
            painter->drawText(temp_rect,Qt::AlignHCenter|Qt::AlignVCenter,strList.at(i));

            painter->setBrush(Qt::NoBrush);
            temp_rect=QRect(rect.left()+n_offset_width*4.5,rect.top()+n_offset_height,n_offset_width*3,n_offset_height);
            painter->drawRect(temp_rect);
            painter->drawText(temp_rect,Qt::AlignHCenter|Qt::AlignVCenter,tr("Test result"));
            break;
        case 3:
            painter->setBrush(Qt::NoBrush);
            temp_rect=QRect(rect.left()+n_offset_width*7.5,rect.top(),n_offset_width,n_offset_height);
            painter->drawRect(temp_rect);
            painter->drawText(temp_rect,Qt::AlignHCenter|Qt::AlignVCenter,strList.at(i));

            temp_rect=QRect(rect.left()+n_offset_width*7.5,rect.top()+n_offset_height,n_offset_width,n_offset_height);
            painter->drawRect(temp_rect);
            painter->drawRect(temp_rect);
            break;
        default:
            break;
        }
    }
}


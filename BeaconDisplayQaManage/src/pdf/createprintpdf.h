#ifndef CREATEPRINTPDF_H
#define CREATEPRINTPDF_H

#include <QObject>
#include <QPainter>
#include <QMainWindow>
#include <QPrinter>
#include "userdefine.h"

typedef struct SingleItemTestInfo_tag
{
    QString strEvaluationMethod;
    QString strEquipment;
    QStringList strRequirement;
    QStringList strTestResult;
    QString strConclusion;
    double nRequirementBilinear;
    double nTestResultBilinear;
    SingleItemTestInfo_tag()
    {
        strEvaluationMethod="";
        strEquipment="";
        //strRequirement="";
        //strTestResult="";
        strConclusion="";
        nRequirementBilinear=1;
        nTestResultBilinear=1;
    }
}SingleItemTestInfo;

typedef enum
{
    TEST_INDEX_START,
    OVERALL_IMAGE_VISUAL_EVALUATION,
    GREYSCALE_RESOLUTION_VISUAL_EVALUATION,
    LUMINANCE_RESPONSE_VISUAL_EVALUATION,
    LUMINANCE_UNIFORMITY_VISUAL_EVALUATION,
    CHROMATICITY_VISUAL_EVALUATION,
    PIXEL_FAULTS_EVALUATION,
    A1_ANGULAR_VIEWING_EVALUATION,
    A2_ANGULAR_VIEWING_EVALUATION,
    CLINICAL_EVALUATION,
    A1_BASIC_LUMINANCE_EVALUATION,
    A2_BASIC_LUMINANCE_EVALUATION,
    A3_BASIC_LUMINANCE_EVALUATION,
    A4_BASIC_LUMINANCE_EVALUATION,
    A5_BASIC_LUMINANCE_EVALUATION,
    A6_BASIC_LUMINANCE_EVALUATION,
    A1_LUMINANCE_RESPONSE_EVALUATION,
    A2_LUMINANCE_RESPONSE_EVALUATION,
    A3_LUMINANCE_RESPONSE_EVALUATION,
    A4_LUMINANCE_RESPONSE_EVALUATION,
    A5_LUMINANCE_RESPONSE_EVALUATION,
    A6_LUMINANCE_RESPONSE_EVALUATION,
    A1_MULTIPLE_LUMINANCE_EVALUATION,
    A3_MULTIPLE_LUMINANCE_EVALUATION,
    CHROMATICITY_QUANTITATIVE_EVALUATION,
    MULTIPLE_CHROMATICITY_QUANTITATIVE_EVALUATION,
    A1_LUMINANCE_UNIFORMITY_EVALUATION,
    A3_LUMINANCE_UNIFORMITY_EVALUATION,
    GREYSCALE_CHROMATICITY_EVALUATION,
}SingleItemTestIndex;

typedef enum
{
    JANUARY=1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
}enMonthIndex;

class CreatePrintPdf : public QObject
{
    Q_OBJECT
public:
    explicit CreatePrintPdf(QObject *parent = 0);

    void printPreviewPdf(QString strFileName, StIecReport IecReport);
    void drawGeneralTablePart(QPainter* painter,QRect rect,StIecReport IecReport);
    void drawHeaderPart(QPainter* painter,QRect rect);
    void drawGlobalResultPart(QPainter* painter,QRect rect,StIecReport IecReport);
    void drawSingleItemPart(QPainter* painter,QRect rect,SingleItemTestInfo stTestInfo,SingleItemTestIndex nTsetIndex=TEST_INDEX_START);
    void dealSingleItemTestInfo(SingleItemTestIndex enIndex,StIecReport IecReport,SingleItemTestInfo &stTestInfo);
signals:


private slots:
     void generateIECTableA1Pdf(QPrinter* printer);
     void generateIECTableA2Pdf(QPrinter* printer);
     void generateIECTableA3Pdf(QPrinter* printer);
     void generateIECTableA4Pdf(QPrinter* printer);
     void generateIECTableA5Pdf(QPrinter* printer);
     void generateIECTableA6Pdf(QPrinter* printer);

private:    
    QString strFileName;
    StIecReport m_IecReport;
};

#endif // CREATEPRINTPDF_H

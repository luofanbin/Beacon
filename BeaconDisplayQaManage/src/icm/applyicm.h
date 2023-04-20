#ifndef APPLYICM_H
#define APPLYICM_H
#include<QVector>
#include"userdefine.h"
#include <QSettings>
#define DISPLAY_CUVER_ITEM_COUNT 256
#define DISPLAY_LUT_MAX  65280
#define DEUBG_MOD_NO_CUSTOM_CURRENT
typedef QVector<StructGamma> vtTableGamma;
typedef struct __GAMMA_LUMI_TABLE__
{
    StructGamma stColorGamma;
    StCieLvxy stColorLumi;
    StCieLvxy stStandardLumi;

}GammaAndLumiTable;
class applyIcm
{
public:
    applyIcm();
    virtual bool applyLutTable(vtTableGamma &vtTable)=0;
    bool outputFile(vtTableGamma &vtTable);
    bool inputFile(vtTableGamma &vtTable);
    bool applyTenLutTable(GammaAndLumiTable* pTableArray);

};

#endif // APPLYICM_H

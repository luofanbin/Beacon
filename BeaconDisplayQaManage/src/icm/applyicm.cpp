#include "applyicm.h"
#include "QFile"
#include "QDataStream"
#include<QtGlobal>
#include<QDebug>
applyIcm::applyIcm()
{
}
bool applyIcm::outputFile(vtTableGamma &vtTable)
{

    QFile file("current_lut.lut");

       file.open(QIODevice::WriteOnly);

       QDataStream out(&file);

       int n_count=vtTable.size();
       qint32 gamma_r,gamma_g,gamma_b;
       out<<n_count;
       for(int i=0;i<n_count;i++)
       {
           gamma_r=vtTable[i].lgGammaR;
           gamma_g=vtTable[i].lgGammaG;
           gamma_b=vtTable[i].lgGammaB;
           out<<gamma_r<<gamma_g<<gamma_b;
       }

       file.flush();
       file.close();
}

bool applyIcm::inputFile(vtTableGamma &vtTable)
{
    vtTable.clear();
    QFile file("current_lut.lut");

       file.open(QIODevice::ReadOnly);

       QDataStream input(&file);
        qint32 gamma_r,gamma_g,gamma_b;

       int n_count=vtTable.size();
       StructGamma st_current_gamma;
       input>>n_count;
       for(int i=0;i<n_count;i++)
       {
            input>>gamma_r>>gamma_g>>gamma_b;
           st_current_gamma.lgGammaR=gamma_r;
           st_current_gamma.lgGammaG=gamma_g;
           st_current_gamma.lgGammaB=gamma_b;
           vtTable.push_back(st_current_gamma);
       }

       file.flush();

       file.close();

}
 bool applyIcm::applyTenLutTable(GammaAndLumiTable* pTableArray)
 {
     vtTableGamma vt_gamma_table;
     StructGamma st_gamma_current;
     long lg_max=DISPLAY_LUT_MAX;


     for(int i=0;i<DISPLAY_CUVER_ITEM_COUNT;i++)
     {
         st_gamma_current=pTableArray[i].stColorGamma;
         st_gamma_current.lgGammaR=1.0*st_gamma_current.lgGammaR/1020*lg_max;
        st_gamma_current.lgGammaG=1.0*st_gamma_current.lgGammaG/1020*lg_max;
         st_gamma_current.lgGammaB=1.0*st_gamma_current.lgGammaB/1020*lg_max;
         st_gamma_current.lgGammaR=qMin(lg_max,st_gamma_current.lgGammaR);
         st_gamma_current.lgGammaG=qMin(st_gamma_current.lgGammaG,lg_max);
         st_gamma_current.lgGammaB=qMin(st_gamma_current.lgGammaB,lg_max);




           vt_gamma_table.push_back(st_gamma_current);

     }


     applyLutTable(vt_gamma_table);

 }

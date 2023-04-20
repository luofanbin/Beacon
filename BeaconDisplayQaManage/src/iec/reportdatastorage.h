#ifndef REPORTDATASTORAGE_H
#define REPORTDATASTORAGE_H
#include"userdefine.h"

class ReportDataStorage
{
public:
    ReportDataStorage(StIecReport* pReportData=NULL);
    virtual bool UpdateData(bool blUpdata);
protected:
    StIecReport* mp_stIecReportData;
};

#endif // REPORTDATASTORAGE_H

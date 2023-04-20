#ifndef APPLYWINDOWSICM_H
#define APPLYWINDOWSICM_H
#include "applyicm.h"
class applyWindowsIcm : public applyIcm
{
public:
    applyWindowsIcm();
     virtual bool applyLutTable(vtTableGamma &vtTable);
};

#endif // APPLYWINDOWSICM_H

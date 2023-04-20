#include "basicdocument.h"


BasicDocument::BasicDocument(QWidget* parent):QWidget(parent),mp_Parent((BasicDocument*)parent),mp_stIecReport(NULL)
{
   if(mp_Parent==NULL)
      mp_stIecReport=new StIecReport;
   else
       mp_stIecReport=mp_Parent->getDocument();

}
StIecReport* BasicDocument::getDocument()
{

        return mp_stIecReport;
}

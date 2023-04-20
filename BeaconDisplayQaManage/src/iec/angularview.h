#ifndef ANGULARVIEW_H
#define ANGULARVIEW_H

#include <QWidget>
#include "userdefine.h"
#include "testimage.h"
namespace Ui {
class AngularView;
}

class AngularView : public QWidget
{
    Q_OBJECT

public:
    explicit AngularView(QWidget *parent = nullptr);
    ~AngularView();
    StAngularView getData();
    void setData(StAngularView *pAngularViewInfo);
  bool getQaResult(StQaCheckCondition &stQaCondition);
void getDataFromTestImage(TestImage* pTestImage);
public slots:
void QaVisibleTest();
signals:
    void  checkQaResult();
private:
    Ui::AngularView *ui;
};

#endif // ANGULARVIEW_H

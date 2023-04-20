#ifndef TESTSETUP_H
#define TESTSETUP_H

#include <QWidget>
#include "userdefine.h"

namespace Ui {
class TestSetup;
}


class TestSetup : public QWidget
{
    Q_OBJECT

public:
    explicit TestSetup(QWidget *parent = 0);
    ~TestSetup();
    void ui_init();
    Test_Setup_Data GetData();
    void SetData(Test_Setup_Data *TestSetupInfo);
    bool getQaResult(StQaCheckCondition &stQaCondition);


private:
    Ui::TestSetup *ui;
};

#endif // TESTSETUP_H

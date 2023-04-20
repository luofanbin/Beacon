#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <QWidget>
#include "userdefine.h"

namespace Ui {
class Workstation;
}


class Workstation : public QWidget
{
    Q_OBJECT

public:
    explicit Workstation(QWidget *parent = 0);
    ~Workstation();
    void ui_init();
    Workstation_Data GetData();
    void SetData(Workstation_Data *WorkstationPageInfo);
    bool getQaResult(StQaCheckCondition &stQaCondition);
private:
    Ui::Workstation *ui;
};

#endif // WORKSTATION_H

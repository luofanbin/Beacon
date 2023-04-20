#ifndef SIGVINSCANINFO_H
#define SIGVINSCANINFO_H
#include<QDialog>
#include "ui_sigvinscaninfo.h"
namespace Ui {
class Dialog;
}

class SigVinScanInfo:public QDialog,public Ui_Dialog
{
     Q_OBJECT
public:
    SigVinScanInfo(QWidget *parent=0);
    void setMouseHide();
    QList<QLabel *> label_list;

private:
    Ui::Dialog *ui;
};

#endif // SIGVINSCANINFO_H

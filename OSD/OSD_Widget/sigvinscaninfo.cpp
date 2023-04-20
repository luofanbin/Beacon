#include "sigvinscaninfo.h"

SigVinScanInfo::SigVinScanInfo(QWidget *parent):QDialog(parent),ui(new Ui::Dialog)
{
    setupUi(this);

    label_list<<this->label_2<<this->label_3<<this->label_4<<this->label_5<<this->label_6<<this->label_7\
              <<this->label_8<<this->label_9<<this->label_10<<this->label_11<<this->label_12<<this->label_13\
             <<this->label_14<<this->label_15;
}

void SigVinScanInfo::setMouseHide()
{
    this->setCursor(Qt::BlankCursor);
    this->label_2->setCursor(Qt::BlankCursor);
    this->label_3->setCursor(Qt::BlankCursor);
    this->label_4->setCursor(Qt::BlankCursor);
    this->label_5->setCursor(Qt::BlankCursor);
    this->label_6->setCursor(Qt::BlankCursor);
    this->label_7->setCursor(Qt::BlankCursor);
    this->label_8->setCursor(Qt::BlankCursor);
    this->label_9->setCursor(Qt::BlankCursor);
    this->label_10->setCursor(Qt::BlankCursor);
    this->label_11->setCursor(Qt::BlankCursor);
    this->label_12->setCursor(Qt::BlankCursor);
    this->label_13->setCursor(Qt::BlankCursor);
    this->label_14->setCursor(Qt::BlankCursor);
    this->label_15->setCursor(Qt::BlankCursor);
    this->label_16->setCursor(Qt::BlankCursor);
}


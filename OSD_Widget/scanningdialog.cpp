#include "scanningdialog.h"
#include "ui_scanningdialog.h"

ScanningDialog::ScanningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScanningDialog)
{
    ui->setupUi(this);
    this->setCursor(Qt::BlankCursor);
    label_list<<ui->label_2<<ui->label_3<<ui->label_4<<ui->label_5<<ui->label_6<<ui->label_7\
              <<ui->label_8<<ui->label_9<<ui->label_10<<ui->label_11<<ui->label_12<<ui->label_13\
             <<ui->label_14<<ui->label_15;
}

void ScanningDialog::setMouseHide()
{
    this->setCursor(Qt::BlankCursor);
    ui->label_2->setCursor(Qt::BlankCursor);
    ui->label_3->setCursor(Qt::BlankCursor);
    ui->label_4->setCursor(Qt::BlankCursor);
    ui->label_5->setCursor(Qt::BlankCursor);
    ui->label_6->setCursor(Qt::BlankCursor);
    ui->label_7->setCursor(Qt::BlankCursor);
    ui->label_8->setCursor(Qt::BlankCursor);
    ui->label_9->setCursor(Qt::BlankCursor);
    ui->label_10->setCursor(Qt::BlankCursor);
    ui->label_11->setCursor(Qt::BlankCursor);
    ui->label_12->setCursor(Qt::BlankCursor);
    ui->label_13->setCursor(Qt::BlankCursor);
    ui->label_14->setCursor(Qt::BlankCursor);
    ui->label_15->setCursor(Qt::BlankCursor);
    ui->label_16->setCursor(Qt::BlankCursor);
}

ScanningDialog::~ScanningDialog()
{
    delete ui;
}

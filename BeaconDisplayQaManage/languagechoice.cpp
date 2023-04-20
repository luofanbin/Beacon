#include "languagechoice.h"
#include "ui_languagechoice.h"
#include <QDebug>
int nLanguageType;
LanguageChoice::LanguageChoice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LanguageChoice)
{
    ui->setupUi(this);
    nLanguageType=0;
    this->setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);
    this-> setFixedSize(200,80);
    show();
    exec();
}

LanguageChoice::~LanguageChoice()
{
    delete ui;
}

void LanguageChoice::on_OkButton_clicked()
{
   nLanguageType=ui->comboBox->currentIndex();
   close();
}

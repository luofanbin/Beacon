#include "mainframestack.h"
#include "ui_mainframestack.h"

MainFrameStack::MainFrameStack(QWidget *parent) :
QStackedWidget(parent),
ui(new Ui::MainFrameStack)
{
ui->setupUi(this);
}

MainFrameStack::~MainFrameStack()
{
delete ui;
}

#include "messages.h"

DisplayMessages::DisplayMessages(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    this->setCursor(Qt::BlankCursor);
    this->show();
}

DisplayMessages::~DisplayMessages()
{

}

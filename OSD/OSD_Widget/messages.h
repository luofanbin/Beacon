#ifndef MESSAGES_H
#define MESSAGES_H

#include <QDialog>
#include "ui_messages.h"

class DisplayMessages : public QDialog,public Ui_Messages
{
    Q_OBJECT

public:
    DisplayMessages(QWidget *parent =0);
    ~DisplayMessages();
};

#endif // MESSAGES_H

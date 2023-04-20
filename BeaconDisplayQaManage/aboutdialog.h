#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
Q_OBJECT

public:
explicit AboutDialog(QWidget *parent = nullptr);
~AboutDialog();
    void ReTranslateUi();

private:
    void paintEvent(QPaintEvent *event);
Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H

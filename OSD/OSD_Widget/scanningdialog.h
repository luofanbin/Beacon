#ifndef SCANNINGDIALOG_H
#define SCANNINGDIALOG_H

#include <QDialog>
#include<QLabel>
namespace Ui {
class ScanningDialog;
}

class ScanningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScanningDialog(QWidget *parent = nullptr);
    ~ScanningDialog();
    void setMouseHide();
    QList<QLabel *> label_list;

private:
    Ui::ScanningDialog *ui;
};

#endif // SCANNINGDIALOG_H

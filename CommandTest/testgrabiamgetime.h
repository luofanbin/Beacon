#ifndef TESTGRABIAMGETIME_H
#define TESTGRABIAMGETIME_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class TestGrabIamgeTime;
}

class TestGrabIamgeTime : public QDialog
{
    Q_OBJECT

public:
    explicit TestGrabIamgeTime(QWidget *parent = 0);
    ~TestGrabIamgeTime();

    QLabel *GrabIamgeStartLable;
    QLabel *GrabIamgeStopLable;
    QLabel *SaveCount1Lable,*SaveCount2Lable,*SaveCount3Lable;
    QPushButton *GrabIamgeButton;

private slots:
    void on_GrabImageButton_clicked();

signals:
    void emitSendGrabImage();

private:
    Ui::TestGrabIamgeTime *ui;

};

#endif // TESTGRABIAMGETIME_H

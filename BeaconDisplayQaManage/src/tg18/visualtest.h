#ifndef VISUALTEST_H
#define VISUALTEST_H

#include <QWidget>
#include "userdefine.h"
namespace Ui {
class VisualTest;
}

class VisualTest : public QWidget
{
    Q_OBJECT

public:
    StQaResult m_QaResult;
    explicit VisualTest(QWidget *parent = nullptr);
    ~VisualTest();
 signals:
    void CommandOk(bool blOk);
private:
    Ui::VisualTest *ui;
  private slots:
     void EnableCommand(int index);
     void on_lineEdit_name_textChanged(const QString &arg1);
     void CheckConfirmStatus();
     void on_lineEdit_reason_textChanged(const QString &arg1);
     void on_pushButton_OK_clicked();
     void on_pushButton_cance_clicked();
};

#endif // VISUALTEST_H

#ifndef MAINFRAMESTACK_H
#define MAINFRAMESTACK_H

#include <QStackedWidget>

namespace Ui {
class MainFrameStack;
}

class MainFrameStack : public QStackedWidget
{
Q_OBJECT

public:
explicit MainFrameStack(QWidget *parent = nullptr);
~MainFrameStack();

private:
Ui::MainFrameStack *ui;
};

#endif // MAINFRAMESTACK_H

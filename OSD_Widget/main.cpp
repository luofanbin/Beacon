#include "widget.h"
#include <QApplication>
#include<QFont>
#include <signal.h>

void OnSignal(int sign){

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    signal(SIGINT,SIG_IGN);
    return a.exec();
}

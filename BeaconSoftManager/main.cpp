
#include <QApplication>
#include "userdefine.h"
#include "spotlightwidget.h"
#include <QDebug>
#include<QVector>
#include "systemtray.h"
#include "qspotlightsetting.h"
#include<QStyleFactory>
#include <QObject>
#include<QMessageBox>

#include <QTextStream>

int main(int argc, char *argv[])
{
    // QApplication::setStyle(QStyleFactory::create());
//read3Dlut_2796();
//get3DlutData();
  //getInputData();
  //  getOutputData();
  //  get3DlutData();
  //  testApplyIcmm();
   // return 1;


   // QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);//设置此项时，电脑放大125%、150%，此时读取的显示器分辨率缩小一半
    QApplication a(argc, argv);

    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);


    QFont font = a.font();
    font.setPointSize(9);//字体大小
    //font.setFamily("SimSun");//微软雅黑字体
    a.setFont(font);

    testRegexCapture();
    QStringList keyList = QStyleFactory::keys();

    for(int i = 0; i < keyList.length(); i++)
    {
        qDebug(keyList.at(i).toUtf8());
    }
    QApplication::setStyle(QStyleFactory::create("Fusion"));
  /// windowsvista
    qDebug()<<"end style";
    QString str_test="\"eeee\"";

QDesktopWidget *mydesk = QApplication::desktop();

    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        QMessageBox::critical(

                    NULL,
                    "Unable to load database",
                    "This demo needs the SQLITE driver"
                    );
  // MainWindow w;
  //  w.show();

#if 1
     QCoreApplication::setOrganizationName("BEACON");
     QCoreApplication::setOrganizationDomain("ww.BEACON.com");
     QCoreApplication::setApplicationName(QObject::tr("BeaconDisplayQAManager"));
#endif


          SystemTray soft_test;

//          if(!soft_test.checkSoftwareFunction())
//          {
//              QMessageBox::warning(NULL,QObject::tr("Warning"),QObject::tr("Have no authority to use this software!" ));
//              return 0;
//          }

          QString path = QDir::temp().absoluteFilePath("BeaconDisplayQaManage.lock");
          QLockFile lockFile(path);

          bool isLock = lockFile.isLocked();
              // bool QLockFile::tryLock(int timeout = 0)
              // tryLock尝试创建锁定文件。此函数如果获得锁，则返回true; 否则返回false。
              // 如果另一个进程（或另一个线程）已经创建了锁文件，则此函数将最多等待timeout毫秒
           if (!lockFile.tryLock(100))
           {
               QMessageBox msgBox;
               msgBox.setIcon(QMessageBox::Warning);
               msgBox.setText("The application is already running.\n"
                      "Allowed to run only one instance of the application.");
               msgBox.exec();
               return 1;
           }

          SpotlightWidget wp;

          a.connect(&soft_test,SIGNAL(shutcutHotKeyPress(EmDesktopModeType ,bool)),&wp,SLOT(shutcutHotKeyPress(EmDesktopModeType ,bool)));
          a.connect(&soft_test,SIGNAL(setSetting()),&wp,SIGNAL(setSetting()));
          a.connect(&soft_test,SIGNAL(setShutcutHotKeyFail(EmDesktopModeType)),&wp,SIGNAL(setShutcutHotKeyFail(EmDesktopModeType)));
          a.connect(&wp,SIGNAL(sigKeyChange(EmDesktopModeType,QString)),&soft_test,SLOT(setGlobalShortcut(EmDesktopModeType ,QString)));
          a.connect(&wp,SIGNAL(languageKeyPress(int)),&soft_test,SLOT(setLanguage(int)));
          a.connect(&soft_test,SIGNAL(setEnableControlPIP(bool,int)),&wp,SLOT(setEnableControlPIP(bool,int)));
          a.connect(&soft_test,SIGNAL(reconfigureDisplayInfo()),&wp,SLOT(reconfigureDisplayInfo()));
          a.connect(&wp,SIGNAL(setEnableControlPIPAction(bool)),&soft_test,SLOT(setActionControlPIP(bool)));
          wp.SendShortcutKeySig();
          soft_test.hide();//初始化时，主窗口隐藏，便于观察效果


          a.connect(&soft_test, &SystemTray::closeApp,&a,[&](){
//          TerminateProcess(pi.hProcess,0);
//          CloseHandle(pi.hProcess);
//          CloseHandle(pi.hThread);
            a.quit();
          });
          return a.exec();


//#endif

}

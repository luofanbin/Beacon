#include "mainwindow.h"
#include <QApplication>
#include "userdefine.h"
#include "dialogmulitescreen.h"
#include "testimage.h"
#include "qmultscreen.h"
#include "qluminaceresponse.h"
#include "databasecontrol.h"
#include "spotlightwidget.h"
#include <QDebug>
#include<QVector>
#include "systemtray.h"
#include "qspotlightsetting.h"
#include<QStyleFactory>
#include <QObject>
#include "languagechoice.h"
#include "userdefine.h"
#include<QMessageBox>

#include <QTextStream>







int main(int argc, char *argv[])
{

   // QApplication::setStyle(QStyleFactory::create());
//read3Dlut_2796();
//get3DlutData();
  //getInputData();
  //  getOutputData();
    get3DlutData();
  //  testApplyIcmm();
   // return 1;



    QApplication a(argc, argv);

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
     DatabaseControl data_control;
     data_control.initDb();
  // MainWindow w;
  //  w.show();

     


SystemTray soft_test;
if(!soft_test.checkSoftwareFunction())
{
    QMessageBox::warning(NULL,QObject::tr("Warning"),QObject::tr("Have no authority to use this software!" ));
   return 0;
}


#if 1
     QCoreApplication::setOrganizationName("BEACON");
     QCoreApplication::setOrganizationDomain("ww.BEACON.com");
     QCoreApplication::setApplicationName(QObject::tr("BeaconDisplayQAManager"));
#endif


  //    QLuminaceResponse dlg;
  /*
      DialogMuliteScreen dlg;

    dlg.showMaximized();
    dlg.show();
*/
     // dlg.show();

#if 0
  //SystemTray w;
  SpotlightWidget wp;

  a.connect(&soft_test,SIGNAL(shutcutHotKeyPress(EmDesktopModeType ,bool)),&wp,SLOT(shutcutHotKeyPress(EmDesktopModeType ,bool)));
  a.connect(&soft_test,SIGNAL(setSetting()),&wp,SIGNAL(setSetting()));
  a.connect(&soft_test,SIGNAL(setShutcutHotKeyFail(EmDesktopModeType)),&wp,SIGNAL(setShutcutHotKeyFail(EmDesktopModeType)));
  a.connect(&wp,SIGNAL(sigKeyChange(EmDesktopModeType,QString)),&soft_test,SLOT(setGlobalShortcut(EmDesktopModeType ,QString)));
  a.connect(&soft_test, SIGNAL(closeApp()), &a, SLOT(quit()));
  a.connect(&wp,SIGNAL(languageKeyPress(int)),&soft_test,SLOT(setLanguage(int)));
  wp.SendShortcutKeySig();
  soft_test.hide();//初始化时，主窗口隐藏，便于观察效果
#else
     /*
    LanguageChoice p;
   QTranslator *LanguageTranslator = new QTranslator();
   switch (nLanguageType) {
   case English:
       LanguageTranslator->load(":/system/Resources/translation_en.qm");
       break;
   case Chinese:
       LanguageTranslator->load(":/system/Resources/translation_ch.qm");
       break;
   default:
       break;
   }
   qApp->installTranslator(LanguageTranslator);
*/
   MainWindow w;
   // TestImage w(1);
    // w.setTg18Type(QA_TG18_OIQ_NORMAL,QA_METHOD_VISIBLE);
     // w.setTg18Type(QA_TG18_OIQ_EVERY,QA_METHOD_SINGLE);
   //  QRect deskRt = QApplication::desktop()->screenGeometry(1);
   //  qDebug()<<deskRt;


   //  w.setGeometry(deskRt);
     // w.showFullScreen();
// w.setGeometry(deskRt);
  //w.setGeometry(deskRt);
  w.show();
   // int res = dlg.exec();
#endif
    return a.exec();
}




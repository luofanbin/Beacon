#ifndef DILOGREPORTHISTORY_H
#define DILOGREPORTHISTORY_H
#include <QtWidgets>
#include <QDialog>
#include <QtSql>
#include "qsqlqueryrelatinaltablemodel.h"
#include "userdefine.h"
#include "createprintpdf.h"
namespace Ui {
class DilogReportHistory;
}

class DilogReportHistory : public QDialog
{
    Q_OBJECT

public:
    void updateDataBase();
    explicit DilogReportHistory(QWidget *parent = nullptr);
    ~DilogReportHistory();
Ui::DilogReportHistory *ui;
  signals:

      void showQaIecReportTest(StIecReport &);
private:

    QSqlQueryRelatinalTableModel *model;
       int authorIdx, genreIdx;


    private slots:
         void showTg18Qa();
         void on_buttonDisplayManage_clicked();
         void  rowDoubleClicked(const QModelIndex &index) ;
         void  rowClicked(const QModelIndex &index) ;
         void addNewAcceptance();
         void addNewConstancy();
         void printPdf();
         void inputGamma();

};

#endif // DILOGREPORTHISTORY_H

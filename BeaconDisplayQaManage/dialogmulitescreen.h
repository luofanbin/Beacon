#ifndef DIALOGMULITESCREEN_H
#define DIALOGMULITESCREEN_H

#include <QDialog>
#include "qmultscreen.h"
#include<QTableView>
#include<QPushButton>
#include "qsqlqueryrelatinaltablemodel.h"
#include <QDialogButtonBox>
#include "my_coutom_lable.h"
class DialogMuliteScreen : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMuliteScreen(QWidget *parent = nullptr);
    ~DialogMuliteScreen();

private:
   // Ui::DialogMuliteScreen *ui;
    QMultScreen *mp_Screen;
    QTableView *mp_Table;
    QSqlQueryRelatinalTableModel* mp_model;
    QDialogButtonBox *mp_buttonBox;
    void initialDatabase();
    void identificationDisplay();
    QVector<QDialog *> m_IdentificationDisplayDlg;
public slots:
    void ClieckButtonBox(QAbstractButton *button);
    void selectDisplay(const QModelIndex &newSelection,const QModelIndex &oldSelection);
    void setIdentificationDisplayDlgHide();
};

#endif // DIALOGMULITESCREEN_H

#include "dialogmulitescreen.h"
#include "ui_dialogmulitescreen.h"
#include<QVBoxLayout>
#include<QPushButton>
#include "testimage.h"
#include<QStandardItemModel>
#include<QLabel>
#include "checkdelegate.h"
#include<QMessageBox>
//#include <QApplication>
DialogMuliteScreen::DialogMuliteScreen(QWidget *parent) :
    QDialog(parent)
 {

    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowMinMaxButtonsHint;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    mp_Screen=new QMultScreen();
    mp_Table=new QTableView();
    mp_buttonBox=new QDialogButtonBox;
    mp_buttonBox->setStandardButtons(QDialogButtonBox::Reset|QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    mp_buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));//将buttonbox中的ok 变成汉化
    mp_buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    mp_buttonBox->button(QDialogButtonBox::Reset)->setText(tr("Identification"));
    mp_model = new QSqlQueryRelatinalTableModel();

     CheckBoxDelegate *ck = new CheckBoxDelegate(/*&tb*/);


     mp_Table->setModel(mp_model);
     mp_Table->setItemDelegate(ck);
     mp_Table->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式
     mp_Table->setSelectionMode(QAbstractItemView::SingleSelection);
     mp_Table->setAutoFillBackground(true);
     mp_Table->setSortingEnabled(false);
     mp_Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     mp_Table->setShowGrid(true);

 //    mp_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);    // Initialize the Author combo box:

     initialDatabase();

     QModelIndex index = mp_Table->selectionModel()->currentIndex();
     mp_Screen->nCurrActiveScreenId=index.row();
     mp_Screen->update();

     QLabel *p_lable=new QLabel;
     p_lable->setText("test");//获取屏幕数量

      //  QPushButton *button2 = new QPushButton("Two");
     QVBoxLayout *main_layout=new QVBoxLayout;
 //main_layout->addWidget(mp_Table);
    // mp_Screen->setMinimumSize (450, 600 );
     main_layout->addWidget(mp_Screen);
       main_layout->addWidget(mp_Table);
       main_layout->addWidget(mp_buttonBox);

        main_layout->setStretchFactor(mp_Screen, 1);
         main_layout->setStretchFactor(mp_Table, 1);

      main_layout->addSpacing(2);

      this->setLayout(main_layout);

     this->setMinimumSize(800,600);
     this->setMinimumSize(600,400);

      for(int i=0;i<mp_Screen->m_vtScreen.size();i++)
      {
          QDialog *p_currt_display=new QDialog;
          //设置窗口全透明
          p_currt_display->setWindowFlags(Qt::FramelessWindowHint);
          //m_IdentificationDisplayDlg->setWindowOpacity(1);
          p_currt_display->setAttribute(Qt::WA_TranslucentBackground,true);
          My_Coutom_Lable *displayIdLable=new My_Coutom_Lable(p_currt_display);
          displayIdLable->setAlignment(Qt::AlignCenter);
          displayIdLable->bl_isMonitorMouse=false;
          displayIdLable->text=QString("%1").arg(i+1);
          displayIdLable->blIsDrawOutlined=true;
          QGridLayout *pLayout = new QGridLayout();
          pLayout->addWidget(displayIdLable, 0, 0, 1, 1);
          p_currt_display->setLayout(pLayout);
          p_currt_display->setModal(true);
          QRect temp_rect=mp_Screen->m_vtScreen.at(i).rectScreen;
          p_currt_display->setGeometry(temp_rect.left(),temp_rect.top(),temp_rect.width(),temp_rect.height());

          m_IdentificationDisplayDlg.push_back(p_currt_display);
      }

  //

   //   void
   //   currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
//mp_Table->selectRow(0);
      connect(mp_buttonBox,SIGNAL(clicked(QAbstractButton*)),this,SLOT(ClieckButtonBox(QAbstractButton*)));
      connect(mp_Table->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex &,const QModelIndex &)),this, SLOT(selectDisplay(const QModelIndex &,const QModelIndex &)));
      connect(mp_Screen,&QMultScreen::currentActiveScrrenIdChanged,[=](int nRow) {mp_Table->selectRow(nRow);});
}
void DialogMuliteScreen::initialDatabase()
{
    mp_model->setTable("Display_Table");
    //  mp_model->setEditStrategy(QSqlTableModel::OnFieldChange);
    mp_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //  ui->ReportTableView->setSortingEnabled(true);
    // Remember the indexes of the columns:
//
    //  QString  str_sql=QString( "select  * from Display_Table order by id  limit 1").arg(mp_Screen->getScreenNumber());

    //  QSqlQuery query(str_sql);
    //   mp_model->setQuery(query);
    //   model->setHorizontalHeaderLabels(labels);
    // model->setRowCount(10);
    // model->setColumnCount(5);
    //   mp_model.set

    if (!mp_model->select()) {

        return;
   }

    if(mp_model->rowCount()<mp_Screen->getScreenNumber())
    {
        for(int i=mp_model->rowCount();i<mp_Screen->getScreenNumber();i++)
        {
            QString  str_sql=QString("insert into Display_Table(Operated,No, Diagnostic,DisplayName,Manufacturer,Model_name,Serial_No,Diagonal,Color) values(\"\",%1, \"\",\"\",\"\",\"\",\"\",\"\",\"\")").arg(i+1);
            QSqlQuery query(str_sql);
            mp_model->setQuery(query);
        }
        mp_model->submitAll();

        mp_model->setTable("Display_Table");
       // str_sql=QString( "select  * from Display_Table order by id  limit %1").arg(mp_Screen->getScreenNumber());
       // QSqlQuery query(str_sql);
       // mp_model->setQuery(query);
        mp_model->select();

    }
mp_model->setFilter(QString( "No <%1").arg(mp_Screen->getScreenNumber()+1));
//mp_model->setHeaderData(mp_model->fieldIndex("Model_name"), Qt::Horizontal, tr("Model name"));
    mp_model->setHeaderData(mp_model->fieldIndex("Model_name"), Qt::Horizontal, tr("Model name"));
    mp_model->setHeaderData(mp_model->fieldIndex("Serial_No"), Qt::Horizontal, tr("Serial no"));
    mp_Table->setColumnHidden(mp_model->fieldIndex("id"), true);
    int n_table_select=0;
    bool bl_is_avtive=false;
    for(int i=0;i< mp_model->rowCount();i++)
    {
         QString str_iterm= mp_model->data(mp_model->index(i,1)).toString();
         if(bl_is_avtive)
            mp_model->setData(mp_model->index(i, 1), " ");
         if((str_iterm.compare("Actived")==0) && (!bl_is_avtive))
         {
             n_table_select=i;
             bl_is_avtive=true;
         }
    }
    mp_Table->selectRow(n_table_select);
    if(mp_model->rowCount()==1)
    {
        mp_model->setData(mp_model->index(0, 1), "Actived");
        mp_model->submitAll();
    }
}

void DialogMuliteScreen::identificationDisplay()
{
    for(int i=0;i<mp_Screen->m_vtScreen.size();i++)
    {
       m_IdentificationDisplayDlg.at(i)->show();
    }
    QTimer::singleShot(2000,this, SLOT(setIdentificationDisplayDlgHide()));
}
DialogMuliteScreen::~DialogMuliteScreen()
{
   // delete ui;
}
void DialogMuliteScreen::ClieckButtonBox(QAbstractButton *button)
{
    if(button== mp_buttonBox->button(QDialogButtonBox::Reset) ){
      //initialDatabase();
       identificationDisplay();
    }

    if(button== mp_buttonBox->button(QDialogButtonBox::Ok) ){
        bool ok=mp_model->submitAll();
        this->accept();
    }
    if(button== mp_buttonBox->button(QDialogButtonBox::Cancel) ){
        this->reject();
    }
}
void DialogMuliteScreen::selectDisplay(const QModelIndex &newSelection,const QModelIndex &oldSelection)
{

    QString str_iterm= mp_model->data(mp_model->index(newSelection.row(),1)).toString();
    mp_model->setData(mp_model->index(newSelection.row(), 1), "Actived");
    if(oldSelection.row()>=0)
    {

     mp_model->setData(mp_model->index(oldSelection.row(), 1), "");
    }

    mp_Screen->nCurrActiveScreenId=newSelection.row();
    mp_Screen->update();
}

void DialogMuliteScreen::setIdentificationDisplayDlgHide()
{
    for(int i=0;i<mp_Screen->m_vtScreen.size();i++)
    {
       m_IdentificationDisplayDlg.at(i)->hide();
    }
}

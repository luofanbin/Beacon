#ifndef PRINTPREVIEWWIDGET_H
#define PRINTPREVIEWWIDGET_H

#include <QMainWindow>
#include <QPrinter>
#include <QPrintPreviewWidget>
#include <QActionGroup>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPrintDialog>
#include <QDialog>
class PrintPreviewWidget : public QDialog
{
    Q_OBJECT
public:
    explicit PrintPreviewWidget(QWidget *parent = 0);
    explicit PrintPreviewWidget(QPrinter *_printer, QWidget *parent = Q_NULLPTR,
                                 Qt::WindowFlags flags = Qt::WindowFlags());
public slots:
    void _q_fit(QAction *action);
    void _q_zoomIn();
    void _q_zoomOut();
    void _q_navigate(QAction *action);
    void _q_setMode(QAction *action);
    void _q_pageNumEdited();
    void _q_save();
    void _q_pageSetup();
    void _q_previewChanged();
    void _q_zoomFactorChanged();
    void setZoomFactor(qreal zoomFactor);
    void init(QPrinter *_printer = 0);
    void populateScene();
    void layoutPages();
    void setupActions();
    void updateNavActions();
    void setFitting(bool on);
    bool isFitting();
    void updatePageNumLabel();
    void updateZoomFactor();
signals:

Q_SIGNALS:
    void paintRequested(QPrinter *_printer);



public slots:

private:
     // widgets:
     QLineEdit *pageNumEdit;
     QLabel *pageNumLabel;
     QComboBox *zoomFactor;

     // actions:
     QActionGroup* navGroup;
     QAction *nextPageAction;
     QAction *prevPageAction;
     QAction *firstPageAction;
     QAction *lastPageAction;

     QActionGroup* fitGroup;
     QAction *fitWidthAction;
     QAction *fitPageAction;

     QActionGroup* zoomGroup;
     QAction *zoomInAction;
     QAction *zoomOutAction;

     QActionGroup* orientationGroup;
     QAction *portraitAction;
     QAction *landscapeAction;

     QActionGroup* modeGroup;
     QAction *singleModeAction;
     QAction *facingModeAction;
     QAction *overviewModeAction;

     QActionGroup *printerGroup;
     QAction *printAction;
     QAction *pageSetupAction;

     QPrintPreviewWidget *m_pPreviewWidget;
     QPrinter *printer;

     QPrintDialog *printDialog;
     bool ownPrinter;
     bool initialized;
};

#endif // PRINTPREVIEWWIDGET_H

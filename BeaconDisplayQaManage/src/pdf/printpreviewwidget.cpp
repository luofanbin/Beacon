#include "printpreviewwidget.h"
#include <QAction>
#include <QGridLayout>
#include <QToolBar>
#include <QPrintPreviewDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QCoreApplication>
#include <QDebug>
#include <QToolButton>
#include <QFileDialog>
namespace {
class QPrintPreviewMainWindow : public QMainWindow
{
public:
    QPrintPreviewMainWindow(QWidget *parent) : QMainWindow(parent) {}
    QMenu *createPopupMenu() Q_DECL_OVERRIDE { return 0; }
};

class ZoomFactorValidator : public QDoubleValidator
{
public:
    ZoomFactorValidator(QObject* parent)
        : QDoubleValidator(parent) {}
    ZoomFactorValidator(qreal bottom, qreal top, int decimals, QObject *parent)
        : QDoubleValidator(bottom, top, decimals, parent) {}

    State validate(QString &input, int &pos) const Q_DECL_OVERRIDE
    {
        bool replacePercent = false;
        if (input.endsWith(QLatin1Char('%'))) {
            input = input.left(input.length() - 1);
            replacePercent = true;
        }
        State state = QDoubleValidator::validate(input, pos);
        if (replacePercent)
            input += QLatin1Char('%');
        const int num_size = 4;
        if (state == Intermediate) {
            int i = input.indexOf(QLocale::system().decimalPoint());
            if ((i == -1 && input.size() > num_size)
                || (i != -1 && i > num_size))
                return Invalid;
        }
        return state;
    }
};

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    LineEdit(QWidget* parent = 0)
        : QLineEdit(parent)
    {
        setContextMenuPolicy(Qt::NoContextMenu);
        connect(this, SIGNAL(returnPressed()), SLOT(handleReturnPressed()));
    }

protected:
    void focusInEvent(QFocusEvent *e) Q_DECL_OVERRIDE
    {
        origText = text();
        QLineEdit::focusInEvent(e);
    }

    void focusOutEvent(QFocusEvent *e) Q_DECL_OVERRIDE
    {
        if (isModified() && !hasAcceptableInput())
            setText(origText);
        QLineEdit::focusOutEvent(e);
    }

private slots:
    void handleReturnPressed()
    {
        origText = text();
    }

private:
    QString origText;
};
} // anonymous namespace

PrintPreviewWidget::PrintPreviewWidget(QWidget *parent) : QDialog(parent)
{

}

PrintPreviewWidget::PrintPreviewWidget(QPrinter *_printer, QWidget *parent, Qt::WindowFlags flags)
{
    init(_printer);
}

void PrintPreviewWidget::_q_fit(QAction *action)
{
    setFitting(true);
    if (action == fitPageAction)
        m_pPreviewWidget->fitInView();
    else
        m_pPreviewWidget->fitToWidth();
}

void PrintPreviewWidget::_q_zoomIn()
{
    setFitting(false);
    m_pPreviewWidget->zoomIn();
    updateZoomFactor();
}

void PrintPreviewWidget::_q_zoomOut()
{
    setFitting(false);
    m_pPreviewWidget->zoomOut();
    updateZoomFactor();
}

void PrintPreviewWidget::_q_navigate(QAction *action)
{
    int curPage = m_pPreviewWidget->currentPage();
    if (action == prevPageAction)
        m_pPreviewWidget->setCurrentPage(curPage - 1);
    else if (action == nextPageAction)
        m_pPreviewWidget->setCurrentPage(curPage + 1);
    else if (action == firstPageAction)
        m_pPreviewWidget->setCurrentPage(1);
    else if (action == lastPageAction)
        m_pPreviewWidget->setCurrentPage(m_pPreviewWidget->pageCount());
    updateNavActions();
}

void PrintPreviewWidget::_q_setMode(QAction *action)
{
    if (action == overviewModeAction) {
        m_pPreviewWidget->setViewMode(QPrintPreviewWidget::AllPagesView);
        setFitting(false);
        fitGroup->setEnabled(false);
        navGroup->setEnabled(false);
        pageNumEdit->setEnabled(false);
        pageNumLabel->setEnabled(false);
    } else if (action == facingModeAction) {
        m_pPreviewWidget->setViewMode(QPrintPreviewWidget::FacingPagesView);
    } else {
        m_pPreviewWidget->setViewMode(QPrintPreviewWidget::SinglePageView);
    }
    if (action == facingModeAction || action == singleModeAction) {
        fitGroup->setEnabled(true);
        navGroup->setEnabled(true);
        pageNumEdit->setEnabled(true);
        pageNumLabel->setEnabled(true);
        setFitting(true);
    }
}

void PrintPreviewWidget::_q_pageNumEdited()
{
    bool ok = false;
    int res = pageNumEdit->text().toInt(&ok);
    if (ok)
        m_pPreviewWidget->setCurrentPage(res);
}

void PrintPreviewWidget::_q_save()
{
    if (printer->outputFormat() != QPrinter::NativeFormat) {
        QString title = QCoreApplication::translate("QPrintPreviewDialog", "Export to PDF");
        QString suffix = QLatin1String(".pdf");
        QString fileName = QFileDialog::getSaveFileName(this, title, printer->outputFileName(),
                                                        QLatin1Char('*') + suffix);
        if (!fileName.isEmpty()) {
            if (QFileInfo(fileName).suffix().isEmpty())
                fileName.append(suffix);
            printer->setOutputFileName(fileName);
        }
        if (!printer->outputFileName().isEmpty())
            m_pPreviewWidget->print();
       this->accept();
        return;
    }
}

void PrintPreviewWidget::_q_pageSetup()
{
//    PrintPreviewWidget pageSetup(printer, this);
//    if (pageSetup.exec() == QDialog::Accepted) {
//        // update possible orientation changes
//        if (m_pPreviewWidget->orientation() == QPrinter::Portrait) {
//            portraitAction->setChecked(true);
//            m_pPreviewWidget->setPortraitOrientation();
//        }else {
//            landscapeAction->setChecked(true);
//            m_pPreviewWidget->setLandscapeOrientation();
//        }
    //    }
}

void PrintPreviewWidget::_q_previewChanged()
{
    updateNavActions();
    updatePageNumLabel();
    updateZoomFactor();
}

void PrintPreviewWidget::_q_zoomFactorChanged()
{
    QString text = zoomFactor->lineEdit()->text();
    bool ok;
    qreal factor = text.remove(QLatin1Char('%')).toFloat(&ok);
    factor = qMax(qreal(1.0), qMin(qreal(1000.0), factor));
    if (ok) {
        m_pPreviewWidget->setZoomFactor(factor/100.0);
        zoomFactor->setEditText(QString::fromLatin1("%1%").arg(factor));
        setFitting(false);
    }
}

void PrintPreviewWidget::setZoomFactor(qreal zoomFactor)
{
    m_pPreviewWidget->setZoomFactor(zoomFactor);
}

void PrintPreviewWidget::init(QPrinter *_printer)
{
    if (_printer) {
        m_pPreviewWidget = new QPrintPreviewWidget(_printer, this);
        printer = _printer;
    } else {
        ownPrinter = true;
        printer = new QPrinter;
        m_pPreviewWidget = new QPrintPreviewWidget(printer, this);
    }
    QObject::connect(m_pPreviewWidget, SIGNAL(paintRequested(QPrinter*)), this, SIGNAL(paintRequested(QPrinter*)));
    QObject::connect(m_pPreviewWidget, SIGNAL(previewChanged()), this, SLOT(_q_previewChanged()));
    setupActions();

    pageNumEdit = new QLineEdit;
    pageNumEdit->setAlignment(Qt::AlignRight);
    pageNumEdit->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    pageNumLabel = new QLabel;
    QObject::connect(pageNumEdit, SIGNAL(editingFinished()), this, SLOT(_q_pageNumEdited()));

    zoomFactor = new QComboBox;
    zoomFactor->setEditable(true);
    zoomFactor->setMinimumContentsLength(7);
    zoomFactor->setInsertPolicy(QComboBox::NoInsert);
    QLineEdit *zoomEditor = new QLineEdit;
    zoomEditor->setValidator(new ZoomFactorValidator(1, 1000, 1, zoomEditor));
    zoomFactor->setLineEdit(zoomEditor);
    static const short factorsX2[] = { 25, 50, 100, 200, 250, 300, 400, 800, 1600 };
    for (auto factorX2 : factorsX2)
        zoomFactor->addItem(QPrintPreviewDialog::tr("%1%").arg(factorX2 / 2.0));
    QObject::connect(zoomFactor->lineEdit(), SIGNAL(editingFinished()),
                     this, SLOT(_q_zoomFactorChanged()));
    QObject::connect(zoomFactor, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(_q_zoomFactorChanged()));

    QPrintPreviewMainWindow *mw = new QPrintPreviewMainWindow(this);
    QToolBar *toolbar = new QToolBar(mw);
    toolbar->addAction(printAction);
    toolbar->addSeparator();
    toolbar->addAction(fitWidthAction);
    toolbar->addAction(fitPageAction);
    toolbar->addSeparator();
    toolbar->addWidget(zoomFactor);
    toolbar->addAction(zoomOutAction);
    toolbar->addAction(zoomInAction);
    toolbar->addSeparator();
    toolbar->addAction(portraitAction);
    toolbar->addAction(landscapeAction);
    toolbar->addSeparator();
    //toolbar->addAction(firstPageAction);
    toolbar->addAction(prevPageAction);

    // this is to ensure the label text and the editor text are
    // aligned in all styles - the extra QVBoxLayout is a workaround
    // for bug in QFormLayout
    QWidget *pageEdit = new QWidget(toolbar);
    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->setContentsMargins(0, 0, 0, 0);
#ifdef Q_OS_MAC
    // We query the widgets about their size and then we fix the size.
    // This should do the trick for the laying out part...
    QSize pageNumEditSize, pageNumLabelSize;
    pageNumEditSize = pageNumEdit->minimumSizeHint();
    pageNumLabelSize = pageNumLabel->minimumSizeHint();
    pageNumEdit->resize(pageNumEditSize);
    pageNumLabel->resize(pageNumLabelSize);
#endif
    QFormLayout *formLayout = new QFormLayout;
#ifdef Q_OS_MAC
    // We have to change the growth policy in Mac.
    formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
#endif
    formLayout->setWidget(0, QFormLayout::LabelRole, pageNumEdit);
    formLayout->setWidget(0, QFormLayout::FieldRole, pageNumLabel);
    vboxLayout->addLayout(formLayout);
    vboxLayout->setAlignment(Qt::AlignVCenter);
    pageEdit->setLayout(vboxLayout);
    toolbar->addWidget(pageEdit);

    toolbar->addAction(nextPageAction);
    //toolbar->addAction(lastPageAction);
    //toolbar->addSeparator();
    //toolbar->addAction(singleModeAction);
    //toolbar->addAction(facingModeAction);
    //toolbar->addAction(overviewModeAction);
    //toolbar->addSeparator();
    //toolbar->addAction(pageSetupAction);

    // Cannot use the actions' triggered signal here, since it doesn't autorepeat
    QToolButton *zoomInButton = static_cast<QToolButton *>(toolbar->widgetForAction(zoomInAction));
    QToolButton *zoomOutButton = static_cast<QToolButton *>(toolbar->widgetForAction(zoomOutAction));
    zoomInButton->setAutoRepeat(true);
    zoomInButton->setAutoRepeatInterval(200);
    zoomInButton->setAutoRepeatDelay(200);
    zoomOutButton->setAutoRepeat(true);
    zoomOutButton->setAutoRepeatInterval(200);
    zoomOutButton->setAutoRepeatDelay(200);
    QObject::connect(zoomInButton, SIGNAL(clicked()), this, SLOT(_q_zoomIn()));
    QObject::connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(_q_zoomOut()));

    mw->addToolBar(toolbar);
    mw->setCentralWidget(m_pPreviewWidget);
    // QMainWindows are always created as top levels, force it to be a
    // plain widget
    mw->setParent(this, Qt::Widget);

    QVBoxLayout *topLayout = new QVBoxLayout;
    topLayout->addWidget(mw);
    topLayout->setMargin(0);
    this->setLayout(topLayout);

    QString caption = QCoreApplication::translate("QPrintPreviewDialog", "Print Preview");
    if (!printer->docName().isEmpty())
        caption += QLatin1String(": ") + printer->docName();
    this->setWindowTitle(caption);

    if (!printer->isValid()
#if defined(Q_OS_WIN) || defined(Q_OS_MAC)
        || printer->outputFormat() != QPrinter::NativeFormat
#endif
        )
        pageSetupAction->setEnabled(false);
    m_pPreviewWidget->setFocus();
}

void PrintPreviewWidget::populateScene()
{

}

void PrintPreviewWidget::layoutPages()
{

}

static inline void qt_setupActionIcon(QAction *action, QLatin1String name)
{
    QLatin1String imagePrefix(":/system/Resources/images/");
    QIcon icon;
    icon.addFile(imagePrefix + name + QLatin1String("-24.png"), QSize(24, 24));
    icon.addFile(imagePrefix + name + QLatin1String("-32.png"), QSize(32, 32));
    action->setIcon(icon);
}

void PrintPreviewWidget::setupActions()
{
    // Navigation
    navGroup = new QActionGroup(this);
    navGroup->setExclusive(false);
    nextPageAction = navGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "Next page"));
    prevPageAction = navGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "Previous page"));
    firstPageAction = navGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "First page"));
    lastPageAction = navGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "Last page"));
    qt_setupActionIcon(nextPageAction, QLatin1String("go-next"));
    qt_setupActionIcon(prevPageAction, QLatin1String("go-previous"));
    qt_setupActionIcon(firstPageAction, QLatin1String("go-first"));
    qt_setupActionIcon(lastPageAction, QLatin1String("go-last"));
    QObject::connect(navGroup, SIGNAL(triggered(QAction*)), this, SLOT(_q_navigate(QAction*)));


    fitGroup = new QActionGroup(this);
    fitWidthAction = fitGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "Fit width"));
    fitPageAction = fitGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "Fit page"));
    fitWidthAction->setObjectName(QLatin1String("fitWidthAction"));
    fitPageAction->setObjectName(QLatin1String("fitPageAction"));
    fitWidthAction->setCheckable(true);
    fitPageAction->setCheckable(true);
    qt_setupActionIcon(fitWidthAction, QLatin1String("fit-width"));
    qt_setupActionIcon(fitPageAction, QLatin1String("fit-page"));
    QObject::connect(fitGroup, SIGNAL(triggered(QAction*)), this, SLOT(_q_fit(QAction*)));

    // Zoom
    zoomGroup = new QActionGroup(this);
    zoomInAction = zoomGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "Zoom in"));
    zoomOutAction = zoomGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "Zoom out"));
    qt_setupActionIcon(zoomInAction, QLatin1String("zoom-in"));
    qt_setupActionIcon(zoomOutAction, QLatin1String("zoom-out"));

    // Portrait/Landscape
    orientationGroup = new QActionGroup(this);
    portraitAction = orientationGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "Portrait"));
    landscapeAction = orientationGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "Landscape"));
    portraitAction->setCheckable(true);
    landscapeAction->setCheckable(true);
    qt_setupActionIcon(portraitAction, QLatin1String("layout-portrait"));
    qt_setupActionIcon(landscapeAction, QLatin1String("layout-landscape"));
    QObject::connect(portraitAction, SIGNAL(triggered(bool)), m_pPreviewWidget, SLOT(setPortraitOrientation()));
    QObject::connect(landscapeAction, SIGNAL(triggered(bool)), m_pPreviewWidget, SLOT(setLandscapeOrientation()));

    // Display mode
    modeGroup = new QActionGroup(this);
    singleModeAction = modeGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "Show single page"));
    facingModeAction = modeGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "Show facing pages"));
    overviewModeAction = modeGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "Show overview of all pages"));
    qt_setupActionIcon(singleModeAction, QLatin1String("view-page-one"));
    qt_setupActionIcon(facingModeAction, QLatin1String("view-page-sided"));
    qt_setupActionIcon(overviewModeAction, QLatin1String("view-page-multi"));
    singleModeAction->setObjectName(QLatin1String("singleModeAction"));
    facingModeAction->setObjectName(QLatin1String("facingModeAction"));
    overviewModeAction->setObjectName(QLatin1String("overviewModeAction"));

    singleModeAction->setCheckable(true);
    facingModeAction->setCheckable(true);
    overviewModeAction->setCheckable(true);
    QObject::connect(modeGroup, SIGNAL(triggered(QAction*)), this, SLOT(_q_setMode(QAction*)));

    // Print
    printerGroup = new QActionGroup(this);
    printAction = printerGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "Save"));
    pageSetupAction = printerGroup->addAction(QCoreApplication::translate("QPrintPreviewDialog", "Page setup"));
    qt_setupActionIcon(printAction, QLatin1String("save"));
    qt_setupActionIcon(pageSetupAction, QLatin1String("page-setup"));
    QObject::connect(printAction, SIGNAL(triggered(bool)), this, SLOT(_q_save()));
    QObject::connect(pageSetupAction, SIGNAL(triggered(bool)), this, SLOT(_q_pageSetup()));

    // Initial state:
    fitPageAction->setChecked(true);
    singleModeAction->setChecked(true);
    if (m_pPreviewWidget->orientation() == QPrinter::Portrait)
        portraitAction->setChecked(true);
    else
        landscapeAction->setChecked(true);
}

void PrintPreviewWidget::updateNavActions()
{
    int curPage = m_pPreviewWidget->currentPage();
    int numPages = m_pPreviewWidget->pageCount();
    nextPageAction->setEnabled(curPage < numPages);
    prevPageAction->setEnabled(curPage > 1);
    firstPageAction->setEnabled(curPage > 1);
    lastPageAction->setEnabled(curPage < numPages);
    pageNumEdit->setText(QString::number(curPage));
}

void PrintPreviewWidget::setFitting(bool on)
{
    if (isFitting() == on)
        return;
    fitGroup->setExclusive(on);
    if (on) {
        QAction* action = fitWidthAction->isChecked() ? fitWidthAction : fitPageAction;
        action->setChecked(true);
        if (fitGroup->checkedAction() != action) {
            // work around exclusitivity problem
            fitGroup->removeAction(action);
            fitGroup->addAction(action);
        }
    } else {
        fitWidthAction->setChecked(false);
        fitPageAction->setChecked(false);
    }
}

bool PrintPreviewWidget::isFitting()
{
    return (fitGroup->isExclusive()
            && (fitWidthAction->isChecked() || fitPageAction->isChecked()));
}

void PrintPreviewWidget::updatePageNumLabel()
{
    int numPages = m_pPreviewWidget->pageCount();
    int maxChars = QString::number(numPages).length();
    pageNumLabel->setText(QString::fromLatin1("/ %1").arg(numPages));
    int cyphersWidth = this->fontMetrics().width(QString().fill(QLatin1Char('8'), maxChars));
    int maxWidth = pageNumEdit->minimumSizeHint().width() + cyphersWidth;
    pageNumEdit->setMinimumWidth(maxWidth);
    pageNumEdit->setMaximumWidth(maxWidth);
    pageNumEdit->setValidator(new QIntValidator(1, numPages, pageNumEdit));
}

void PrintPreviewWidget::updateZoomFactor()
{
     zoomFactor->lineEdit()->setText(QString().sprintf("%.1f%%", m_pPreviewWidget->zoomFactor()*100));
}


#include "screenshot.h"
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QApplication>
#include <QClipboard>
#include <QScreen>
#include <QFileDialog>
#include <QTime>
#include <QtMath>
#include <QDebug>

// 选中矩形8个拖拽点小矩形的宽高;
#define STRETCH_RECT_WIDTH                      6
#define STRETCH_RECT_HEIGHT                     6

// 矩形选中区边框宽度;
#define SELECT_RECT_BORDER_WIDTH                1

// 选中矩形信息矩形的宽高;
#define SELECT_RECT_INFO_WIDTH                  75
#define SELECT_RECT_INFO_HEIGHT                 20

// 选区矩形的右下顶点放大图的宽高;
#define END_POINT_RECT_WIDTH                    122
#define END_POINT_RECT_HEIGHT                   122
#define END_POINT_IMAGE_HEIGHT                  90


ScreenShot::ScreenShot(QWidget *parent)
    : QWidget(parent)
    , m_currentCaptureState(InitCapture)
    , m_bIsFunKeyVisible(false)
    , m_bIsFirstSelected(false)
    , m_bIsSelBarForTextVisible(false)
    , m_bIsSelBarForBrushVisible(false)
    , m_bIsSelBarForArrowsVisible(false)
    , m_bIsSelBarForEllipseVisible(false)
    , m_bIsSelBarForRectangleVisible(false)
    , m_bIsStartPaint(false)
    , m_paintState(NotStartPaint)
    , m_bIsPaintMousePress(false)
    , m_bIsAddToContainer(false)
    ,m_bIsDrawEndPointImage(true)
{
    initialize();
    initStretchRect();
    loadBackgroundPixmap(QPoint(0,0));

    //绑定功能栏
    funKey = new FunctionKey(this);
    connect(funKey->submit,&MyButton::clicked,this,&ScreenShot::onSubmitButtonClicked);
    connect(funKey->cancel,&MyButton::clicked,this,&ScreenShot::onCancelButtonClicked);
    connect(funKey->save,&MyButton::clicked,this,&ScreenShot::onSaveButtonClicked);
    connect(funKey->text,&MyButton::clicked,this,&ScreenShot::onTextButtonClicked);
    connect(funKey->brush,&MyButton::clicked,this,&ScreenShot::onBrushButtonClicked);
    connect(funKey->arrows,&MyButton::clicked,this,&ScreenShot::onArrowsButtonClicked);
    connect(funKey->ellipse,&MyButton::clicked,this,&ScreenShot::onEllipseButtonClicked);
    connect(funKey->rectangle,&MyButton::clicked,this,&ScreenShot::onRectangleButtonClicked);
    connect(funKey->revocation,&MyButton::clicked,this,&ScreenShot::onRevocationButtonClicked);
    funKey->hide();

    selBar_Text = new SelectionBar(this);
    selBar_Text->smallDot->hide();
    selBar_Text->mediumDot->hide();
    selBar_Text->bigDot->hide();
    selBar_Text->fontLabel->show();
    selBar_Text->fontSize->show();
    selBar_Text->hide();
    selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/red_selected.png);}");
    selBar_Text->fontSize->setCurrentIndex(5);
    connect(selBar_Text->black,&MyButton::clicked,this,[=](){textPenColorType=Black;onTextPenColorChanged();});
    connect(selBar_Text->white,&MyButton::clicked,this,[=](){textPenColorType=White;onTextPenColorChanged();});
    connect(selBar_Text->dimgrey,&MyButton::clicked,this,[=](){textPenColorType=DimGrey;onTextPenColorChanged();});
    connect(selBar_Text->grey,&MyButton::clicked,this,[=](){textPenColorType=Grey;onTextPenColorChanged();});
    connect(selBar_Text->maroon,&MyButton::clicked,this,[=](){textPenColorType=Maroon;onTextPenColorChanged();});
    connect(selBar_Text->red,&MyButton::clicked,this,[=](){textPenColorType=Red;onTextPenColorChanged();});
    connect(selBar_Text->orange,&MyButton::clicked,this,[=](){textPenColorType=Orange;onTextPenColorChanged();});
    connect(selBar_Text->yellow,&MyButton::clicked,this,[=](){textPenColorType=Yellow;onTextPenColorChanged();});
    connect(selBar_Text->green,&MyButton::clicked,this,[=](){textPenColorType=Green;onTextPenColorChanged();});
    connect(selBar_Text->yellowgreen,&MyButton::clicked,this,[=](){textPenColorType=YellowGreen;onTextPenColorChanged();});
    connect(selBar_Text->mediumblue,&MyButton::clicked,this,[=](){textPenColorType=MediumBlue;onTextPenColorChanged();});
    connect(selBar_Text->dodgerblue,&MyButton::clicked,this,[=](){textPenColorType=DodgerBlue;onTextPenColorChanged();});
    connect(selBar_Text->purple,&MyButton::clicked,this,[=](){textPenColorType=Purple;onTextPenColorChanged();});
    connect(selBar_Text->magenta,&MyButton::clicked,this,[=](){textPenColorType=Magenta;onTextPenColorChanged();});
    connect(selBar_Text->teal,&MyButton::clicked,this,[=](){textPenColorType=Teal;onTextPenColorChanged();});
    connect(selBar_Text->turquoise,&MyButton::clicked,this,[=](){textPenColorType=Turquoise;onTextPenColorChanged();});
    connect(selBar_Text->fontSize,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(onTextFontSizeChanged(const QString &)));

    selBar_Brush = new SelectionBar(this);
    selBar_Brush->hide();
    connect(selBar_Brush->black,&MyButton::clicked,this,[=](){brushPenColorType=Black;onBrushPenColorChanged();});
    connect(selBar_Brush->white,&MyButton::clicked,this,[=](){brushPenColorType=White;onBrushPenColorChanged();});
    connect(selBar_Brush->dimgrey,&MyButton::clicked,this,[=](){brushPenColorType=DimGrey;onBrushPenColorChanged();});
    connect(selBar_Brush->grey,&MyButton::clicked,this,[=](){brushPenColorType=Grey;onBrushPenColorChanged();});
    connect(selBar_Brush->maroon,&MyButton::clicked,this,[=](){brushPenColorType=Maroon;onBrushPenColorChanged();});
    connect(selBar_Brush->red,&MyButton::clicked,this,[=](){brushPenColorType=Red;onBrushPenColorChanged();});
    connect(selBar_Brush->orange,&MyButton::clicked,this,[=](){brushPenColorType=Orange;onBrushPenColorChanged();});
    connect(selBar_Brush->yellow,&MyButton::clicked,this,[=](){brushPenColorType=Yellow;onBrushPenColorChanged();});
    connect(selBar_Brush->green,&MyButton::clicked,this,[=](){brushPenColorType=Green;onBrushPenColorChanged();});
    connect(selBar_Brush->yellowgreen,&MyButton::clicked,this,[=](){brushPenColorType=YellowGreen;onBrushPenColorChanged();});
    connect(selBar_Brush->mediumblue,&MyButton::clicked,this,[=](){brushPenColorType=MediumBlue;onBrushPenColorChanged();});
    connect(selBar_Brush->dodgerblue,&MyButton::clicked,this,[=](){brushPenColorType=DodgerBlue;onBrushPenColorChanged();});
    connect(selBar_Brush->purple,&MyButton::clicked,this,[=](){brushPenColorType=Purple;onBrushPenColorChanged();});
    connect(selBar_Brush->magenta,&MyButton::clicked,this,[=](){brushPenColorType=Magenta;onBrushPenColorChanged();});
    connect(selBar_Brush->teal,&MyButton::clicked,this,[=](){brushPenColorType=Teal;onBrushPenColorChanged();});
    connect(selBar_Brush->turquoise,&MyButton::clicked,this,[=](){brushPenColorType=Turquoise;onBrushPenColorChanged();});
    connect(selBar_Brush->smallDot,&MyButton::clicked,this,[=](){brushPenWeightType=Small;onBrushPenWeightChanged();});
    connect(selBar_Brush->mediumDot,&MyButton::clicked,this,[=](){brushPenWeightType=Medium;onBrushPenWeightChanged();});
    connect(selBar_Brush->bigDot,&MyButton::clicked,this,[=](){brushPenWeightType=Big;onBrushPenWeightChanged();});

    selBar_Arrows = new SelectionBar(this);
    selBar_Arrows->hide();
    connect(selBar_Arrows->black,&MyButton::clicked,this,[=](){arrowPenColorType=Black;onArrowPenColorChanged();});
    connect(selBar_Arrows->white,&MyButton::clicked,this,[=](){arrowPenColorType=White;onArrowPenColorChanged();});
    connect(selBar_Arrows->dimgrey,&MyButton::clicked,this,[=](){arrowPenColorType=DimGrey;onArrowPenColorChanged();});
    connect(selBar_Arrows->grey,&MyButton::clicked,this,[=](){arrowPenColorType=Grey;onArrowPenColorChanged();});
    connect(selBar_Arrows->maroon,&MyButton::clicked,this,[=](){arrowPenColorType=Maroon;onArrowPenColorChanged();});
    connect(selBar_Arrows->red,&MyButton::clicked,this,[=](){arrowPenColorType=Red;onArrowPenColorChanged();});
    connect(selBar_Arrows->orange,&MyButton::clicked,this,[=](){arrowPenColorType=Orange;onArrowPenColorChanged();});
    connect(selBar_Arrows->yellow,&MyButton::clicked,this,[=](){arrowPenColorType=Yellow;onArrowPenColorChanged();});
    connect(selBar_Arrows->green,&MyButton::clicked,this,[=](){arrowPenColorType=Green;onArrowPenColorChanged();});
    connect(selBar_Arrows->yellowgreen,&MyButton::clicked,this,[=](){arrowPenColorType=YellowGreen;onArrowPenColorChanged();});
    connect(selBar_Arrows->mediumblue,&MyButton::clicked,this,[=](){arrowPenColorType=MediumBlue;onArrowPenColorChanged();});
    connect(selBar_Arrows->dodgerblue,&MyButton::clicked,this,[=](){arrowPenColorType=DodgerBlue;onArrowPenColorChanged();});
    connect(selBar_Arrows->purple,&MyButton::clicked,this,[=](){arrowPenColorType=Purple;onArrowPenColorChanged();});
    connect(selBar_Arrows->magenta,&MyButton::clicked,this,[=](){arrowPenColorType=Magenta;onArrowPenColorChanged();});
    connect(selBar_Arrows->teal,&MyButton::clicked,this,[=](){arrowPenColorType=Teal;onArrowPenColorChanged();});
    connect(selBar_Arrows->turquoise,&MyButton::clicked,this,[=](){arrowPenColorType=Turquoise;onArrowPenColorChanged();});
    connect(selBar_Arrows->smallDot,&MyButton::clicked,this,[=](){arrowPenWeightType=Small;onArrowPenWeightChanged();});
    connect(selBar_Arrows->mediumDot,&MyButton::clicked,this,[=](){arrowPenWeightType=Medium;onArrowPenWeightChanged();});
    connect(selBar_Arrows->bigDot,&MyButton::clicked,this,[=](){arrowPenWeightType=Big;onArrowPenWeightChanged();});

    selBar_Ellipse = new SelectionBar(this);
    selBar_Ellipse->hide();
    connect(selBar_Ellipse->black,&MyButton::clicked,this,[=](){ellipsePenColorType=Black;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->white,&MyButton::clicked,this,[=](){ellipsePenColorType=White;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->dimgrey,&MyButton::clicked,this,[=](){ellipsePenColorType=DimGrey;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->grey,&MyButton::clicked,this,[=](){ellipsePenColorType=Grey;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->maroon,&MyButton::clicked,this,[=](){ellipsePenColorType=Maroon;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->red,&MyButton::clicked,this,[=](){ellipsePenColorType=Red;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->orange,&MyButton::clicked,this,[=](){ellipsePenColorType=Orange;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->yellow,&MyButton::clicked,this,[=](){ellipsePenColorType=Yellow;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->green,&MyButton::clicked,this,[=](){ellipsePenColorType=Green;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->yellowgreen,&MyButton::clicked,this,[=](){ellipsePenColorType=YellowGreen;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->mediumblue,&MyButton::clicked,this,[=](){ellipsePenColorType=MediumBlue;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->dodgerblue,&MyButton::clicked,this,[=](){ellipsePenColorType=DodgerBlue;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->purple,&MyButton::clicked,this,[=](){ellipsePenColorType=Purple;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->magenta,&MyButton::clicked,this,[=](){ellipsePenColorType=Magenta;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->teal,&MyButton::clicked,this,[=](){ellipsePenColorType=Teal;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->turquoise,&MyButton::clicked,this,[=](){ellipsePenColorType=Turquoise;onEllipsePenColorChanged();});
    connect(selBar_Ellipse->smallDot,&MyButton::clicked,this,[=](){ellipsePenWeightType=Small;onEllipsePenWeightChanged();});
    connect(selBar_Ellipse->mediumDot,&MyButton::clicked,this,[=](){ellipsePenWeightType=Medium;onEllipsePenWeightChanged();});
    connect(selBar_Ellipse->bigDot,&MyButton::clicked,this,[=](){ellipsePenWeightType=Big;onEllipsePenWeightChanged();});

    selBar_Rectangle = new SelectionBar(this);
    selBar_Rectangle->hide();
    connect(selBar_Rectangle->black,&MyButton::clicked,this,[=](){rectPenColorType=Black;onRectPenColorChanged();});
    connect(selBar_Rectangle->white,&MyButton::clicked,this,[=](){rectPenColorType=White;onRectPenColorChanged();});
    connect(selBar_Rectangle->dimgrey,&MyButton::clicked,this,[=](){rectPenColorType=DimGrey;onRectPenColorChanged();});
    connect(selBar_Rectangle->grey,&MyButton::clicked,this,[=](){rectPenColorType=Grey;onRectPenColorChanged();});
    connect(selBar_Rectangle->maroon,&MyButton::clicked,this,[=](){rectPenColorType=Maroon;onRectPenColorChanged();});
    connect(selBar_Rectangle->red,&MyButton::clicked,this,[=](){rectPenColorType=Red;onRectPenColorChanged();});
    connect(selBar_Rectangle->orange,&MyButton::clicked,this,[=](){rectPenColorType=Orange;onRectPenColorChanged();});
    connect(selBar_Rectangle->yellow,&MyButton::clicked,this,[=](){rectPenColorType=Yellow;onRectPenColorChanged();});
    connect(selBar_Rectangle->green,&MyButton::clicked,this,[=](){rectPenColorType=Green;onRectPenColorChanged();});
    connect(selBar_Rectangle->yellowgreen,&MyButton::clicked,this,[=](){rectPenColorType=YellowGreen;onRectPenColorChanged();});
    connect(selBar_Rectangle->mediumblue,&MyButton::clicked,this,[=](){rectPenColorType=MediumBlue;onRectPenColorChanged();});
    connect(selBar_Rectangle->dodgerblue,&MyButton::clicked,this,[=](){rectPenColorType=DodgerBlue;onRectPenColorChanged();});
    connect(selBar_Rectangle->purple,&MyButton::clicked,this,[=](){rectPenColorType=Purple;onRectPenColorChanged();});
    connect(selBar_Rectangle->magenta,&MyButton::clicked,this,[=](){rectPenColorType=Magenta;onRectPenColorChanged();});
    connect(selBar_Rectangle->teal,&MyButton::clicked,this,[=](){rectPenColorType=Teal;onRectPenColorChanged();});
    connect(selBar_Rectangle->turquoise,&MyButton::clicked,this,[=](){rectPenColorType=Turquoise;onRectPenColorChanged();});
    connect(selBar_Rectangle->smallDot,&MyButton::clicked,this,[=](){rectPenWeightType=Small;onRectPenWeightChanged();});
    connect(selBar_Rectangle->mediumDot,&MyButton::clicked,this,[=](){rectPenWeightType=Medium;onRectPenWeightChanged();});
    connect(selBar_Rectangle->bigDot,&MyButton::clicked,this,[=](){rectPenWeightType=Big;onRectPenWeightChanged();});

    //设置画笔默认宽度为3
    brushPen.setWidth(3);
    selBar_Brush->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot_selected.png);}");
    arrowPen.setWidth(3);
    selBar_Arrows->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot_selected.png);}");
    ellipsePen.setWidth(3);
    selBar_Ellipse->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot_selected.png);}");
    rectPen.setWidth(3);
    selBar_Rectangle->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot_selected.png);}");

    m_textEdit = new QTextEdit(this);
    m_textEdit->installEventFilter(this);
    connect(m_textEdit,SIGNAL(textChanged()),this,SLOT(onTextChanged()));
    m_textEdit->hide();
    m_textEdit->resize(90,90);
    QPalette p1=m_textEdit->palette();
    p1.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    m_textEdit->setPalette(p1);
    m_textEdit->setStyleSheet("QTextEdit{background-image:url(:/pic/barIcon/textEditImage.png);}"
                              "QTextEdit{font-family:'Microsoft YaHei';}"
                              "QTextEdit{ border: 2px solid #ff0000;}");
    m_textEdit->setFontPointSize(14);
    m_textEdit->setTextColor(QColor(255,0,0));

    textPen.setColor(QColor(255,0,0));
    textFont.setPointSize(14);
    textFont.setFamily("Microsoft YaHei");
    textFont.setWeight(QFont::Normal);

    textFontSize = 14;
}

void ScreenShot::initialize()
{
    this->setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setWindowState(Qt::WindowActive | Qt::WindowFullScreen);
    this->setMouseTracking(true);
}

void ScreenShot::initStretchRect()
{
    m_stretchRectState = NotSelect;
    m_topLeftRect = QRect(0, 0, 0, 0);
    m_topRightRect = QRect(0, 0, 0, 0);
    m_bottomLeftRect = QRect(0, 0, 0, 0);
    m_bottomRightRect = QRect(0, 0, 0, 0);

    m_leftCenterRect = QRect(0, 0, 0, 0);
    m_topCenterRect = QRect(0, 0, 0, 0);
    m_rightCenterRect = QRect(0, 0, 0, 0);
    m_bottomCenterRect = QRect(0, 0, 0, 0);
}

//程序运行时捕获当前屏幕
void ScreenShot::loadBackgroundPixmap(QPoint mousePosition,bool isMouseMove)
{
    QPoint coursePoint;
    coursePoint = QCursor::pos();//获取当前光标的位置
    QRect currRect;
    QDesktopWidget * deskTop = QApplication::desktop();
    QPoint startPoint;
    int nWidth=0,nHeight=0;

    int nMonitorNum = deskTop->screenCount();
    startPoint.setX(deskTop->screenGeometry(0).x());
    startPoint.setY(deskTop->screenGeometry(0).y());
    for(int i=0;i<nMonitorNum;i++)
    {
        currRect= deskTop->screenGeometry(i);
        startPoint.setY(qMin(startPoint.y(),currRect.y()));
        nWidth+=currRect.width();
        nHeight=qMax(nHeight,currRect.height());

        if((coursePoint.x()>=currRect.x()) && (coursePoint.x()<=currRect.right())
          && (coursePoint.y()>=currRect.y())  && (coursePoint.y()<=currRect.bottom()))
            m_nCurrMonitor=i;
    }

    this->setGeometry(startPoint.x(),startPoint.y(),nWidth,nHeight);
    QScreen * screen = QGuiApplication::primaryScreen();
    m_loadPixmap = screen->grabWindow(QApplication::desktop()->winId(),startPoint.x(),startPoint.y(),nWidth,nHeight); //抓取当前屏幕的图片;
    m_screenwidth = m_loadPixmap.width();
    m_screenheight = m_loadPixmap.height();

    update();
}

// 根据beginPoint , endPoint 获取当前选中的矩形;
QRect ScreenShot::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
    int x, y, width, height;
    width = qAbs(beginPoint.x() - endPoint.x());
    height = qAbs(beginPoint.y() - endPoint.y());
    x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
    y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

    QRect selectedRect = QRect(x, y, width, height);
    // 避免宽或高为零时拷贝截图有误;
    // 可以看QQ截图，当选取截图宽或高为零时默认为2;
    if (selectedRect.width() == 0)
    {
        selectedRect.setWidth(1);
    }
    if (selectedRect.height() == 0)
    {
        selectedRect.setHeight(1);
    }

    return selectedRect;
}

void ScreenShot::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_stretchRectState = getStrethRectState(event->pos());
        if (m_currentCaptureState == InitCapture)
        {
            m_currentCaptureState = BeginCaptureImage;
            m_beginPoint = event->pos();

            m_bIsFirstSelected = false;
        }
        // 是否在拉伸的小矩形中;
        else if (m_stretchRectState != NotSelect)
        {
            hideAllSelBar();//隐藏所有选择栏
            m_currentCaptureState = BeginMoveStretchRect;
            // 当前鼠标在拖动选中区顶点时,设置鼠标当前状态;
            setStretchCursorStyle(m_stretchRectState);
            m_beginMovePoint = event->pos();

            if(m_bIsFunKeyVisible)//拖拽时隐藏功能栏
            {
                funKey->hide();
                m_currentSelectRect = getSelectRect();//更新位置，防止功能栏与截图区域移动不同步
                m_bIsFunKeyVisible = false;
            }
        }
        else if(m_paintState == NotStartPaint)
        {
            // 是否在选中的矩形中;
            if (isPressPointInSelectRect(event->pos()))
            {
                if(!m_bIsStartPaint)
                {
                    m_currentCaptureState = BeginMoveCaptureArea;
                    m_beginMovePoint = event->pos();

                    if(m_bIsFunKeyVisible)//拖拽时隐藏功能栏
                    {
                        funKey->hide();
                        m_currentSelectRect = getSelectRect();//更新位置，防止功能栏与截图区域移动不同步
                        m_bIsFunKeyVisible = false;
                    }
                }
            }
        } 
        else if(m_paintState != NotStartPaint)
        {
            if (isPressPointInSelectRect(event->pos()))
            {
                if(!m_bIsPaintMousePress)
                {
                    m_bIsPaintMousePress = true;
                    m_beginPaintPoint = event->pos();
                    m_endPaintPoint = event->pos();
                    if(m_paintState != Texts)
                    {
                        if(m_textEdit->isVisible())
                        {
                            m_textEdit->clear();
                            m_textEdit->hide();
                        }
                    }
                    else
                    {
                        if(m_textEdit->toPlainText().size())
                        {
                            textRect=QRect(QPoint(m_textEdit->x()+5,m_textEdit->y()+5),
                                           QSize(m_textEdit->width(),m_textEdit->height()));
                            texts = m_textEdit->toPlainText();
                        }
                        m_textEdit->move(m_beginPaintPoint);
                        if(m_textEdit->isVisible())
                            m_textEdit->hide();
                        else
                            m_textEdit->show();
                        m_textEdit->clear();
                    }
                }
            }
        }
    }

    return QWidget::mousePressEvent(event);
}

void ScreenShot::mouseMoveEvent(QMouseEvent *event)
{
    QDesktopWidget * deskTop = QApplication::desktop();
    int nMonitorNum = deskTop->screenCount();
    QRect currRect;
    for(int i=0;i<nMonitorNum;i++)
    {
        currRect= deskTop->screenGeometry(i);

        if((event->pos().x()>=currRect.x()) && (event->pos().x()<=currRect.right())
          && (event->pos().y()>=currRect.y())  && (event->pos().y()<=currRect.bottom()) && (m_nCurrMonitor!=i))
        {
            m_nCurrMonitor=i;
            update();
        }
    }

    if (m_currentCaptureState == BeginCaptureImage)
    {
        m_endPoint = event->pos();
        update();
    }
    else if (m_currentCaptureState == BeginMoveCaptureArea)
    {
        m_endMovePoint = event->pos();
        update();
    }
    else if (m_currentCaptureState == BeginMoveStretchRect)
    {
        m_endMovePoint = event->pos();
        update();
        // 当前鼠标在拖动选中区顶点时,在鼠标未停止移动前，一直保持鼠标当前状态;
    }
    else if(m_paintState != NotStartPaint && m_bIsPaintMousePress)
    {
        if(m_paintState == Lines)
        {
            m_endPaintPoint = event->pos();
            curLines.push_back(QLine(m_beginPaintPoint,m_endPaintPoint));
            m_beginPaintPoint = m_endPaintPoint;
            update();
        }
        else
        {
            m_endPaintPoint = event->pos();
            update();
        }
    }

    // 根据鼠标是否在选中区域内设置鼠标样式;
    StretchRectState stretchRectState = getStrethRectState(event->pos());
    if (stretchRectState != NotSelect)
    {
        setStretchCursorStyle(stretchRectState);
    }
    else if (isPressPointInSelectRect(event->pos()))
    {
        //当选择绘画功能时，取消选中矩形移动时的图标
        if(!m_bIsStartPaint)
            setCursor(Qt::SizeAllCursor);
        else
            setCursor(Qt::CrossCursor);
    }
    else if (!isPressPointInSelectRect(event->pos()) && m_currentCaptureState != BeginMoveCaptureArea)
    {
        setCursor(Qt::ArrowCursor);
    }

    if(m_bIsDrawEndPointImage)
    {
        m_bIsFunKeyVisible=false;
        update();
    }

    return QWidget::mouseMoveEvent(event);
}

void ScreenShot::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if (m_currentCaptureState == BeginCaptureImage)
        {
            m_currentCaptureState = FinishCaptureImage;
            m_endPoint = event->pos();

            moveFunKey();
            update();
        }
        else if (m_currentCaptureState == BeginMoveCaptureArea)
        {
            m_currentCaptureState = FinishMoveCaptureArea;
            m_endMovePoint = event->pos();

            moveFunKey();
            update();
        }
        else if (m_currentCaptureState == BeginMoveStretchRect)
        {
            m_currentCaptureState = FinishMoveStretchRect;
            m_endMovePoint = event->pos();

            moveFunKey();
            update();
        }
        else if(m_paintState != NotStartPaint && m_bIsPaintMousePress)
        {
            m_endPaintPoint = event->pos();
            m_bIsPaintMousePress = false;
            m_bIsAddToContainer = true;
            update();
        }

        m_bIsDrawEndPointImage=false;
    }

    return QWidget::mouseReleaseEvent(event);
}

// 当前鼠标坐标是否在选取的矩形区域内;
bool ScreenShot::isPressPointInSelectRect(QPoint mousePressPoint)
{
    QRect selectRect = getRect(m_beginPoint, m_endPoint);
    if (selectRect.contains(mousePressPoint))
    {
        return true;
    }

    return false;
}

void ScreenShot::keyPressEvent(QKeyEvent *event)
{
    //Esc键取消截图
    if(event->key() == Qt::Key_Escape)
    {
        this->hide();
        //this->close();
    }
    //回车键完成截图，将图片复制到剪切板
    else if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        onSubmitButtonClicked();
    }
    //Ctrl+S组合键保存截取图片
    else if(event->key() == Qt::Key_S && event->modifiers() == Qt::ControlModifier)
    {
        onSaveButtonClicked();
    }
    //Ctrl+Z组合键撤销上一次绘图
    else if(event->key() == Qt::Key_Z && event->modifiers() == Qt::ControlModifier)
    {
        if(!rectsContainer.isEmpty())
        {
            rectsContainer.pop_back();
            update();
        }
    }
}

void ScreenShot::paintEvent(QPaintEvent *event)
{
    m_painter.begin(this); //进行重绘;

    QColor shadowColor = QColor(0, 0, 0, 120); //阴影颜色设置;
    m_painter.drawPixmap(0, 0, m_loadPixmap);//将背景图片画到窗体上;
    //m_painter.fillRect(m_loadPixmap.rect(), shadowColor); //画影罩效果;

    QDesktopWidget * deskTop = QApplication::desktop();
    int nMonitorNum = deskTop->screenCount();
    QRect currRect;
    for(int i=0;i<nMonitorNum;i++)
    {
        currRect= deskTop->screenGeometry(i);
        if(m_nCurrMonitor==i)
        {
            m_painter.fillRect(currRect, QColor(0, 0, 0, 0));
            m_painter.setPen(QPen(QColor(0 , 174 , 255), 3, Qt::SolidLine, Qt::FlatCap));//设置画笔;
            m_painter.drawRect(currRect.x(),currRect.y(),currRect.width()-3,currRect.height()-3);
            m_currentSelectRect=currRect;
        }
        else
            m_painter.fillRect(currRect, shadowColor);
    }

    m_painter.setPen(QPen(QColor(0 , 174 , 255), 1, Qt::SolidLine, Qt::FlatCap));//设置画笔;
    switch (m_currentCaptureState)
    {
    case InitCapture:
        break;
    case BeginCaptureImage:
    case FinishCaptureImage:
    case BeginMoveCaptureArea:
    case FinishMoveCaptureArea:
    case BeginMoveStretchRect:
    case FinishMoveStretchRect:
    {
        m_painter.fillRect(deskTop->screenGeometry(m_nCurrMonitor), shadowColor);
        m_currentSelectRect = getSelectRect();
        m_painter.fillRect(m_currentSelectRect,QColor(0, 0, 0, 0));
        drawCaptureImage();
        break;
    }
    }

    m_painter.setPen(getPen());
    m_painter.setFont(textFont);
    if(m_paintState != NotStartPaint)
    {
        rect = getPaintRect();
        switch (m_paintState)
        {
        case Arrows:
            drawArrow(m_beginPaintPoint,m_endPaintPoint);
            break;
        case Ellipses:
            m_painter.drawEllipse(rect);
            break;
        case Rectangles:
            m_painter.drawRect(rect);
            break;
        case Lines:
            m_painter.drawLines(curLines);
            break;
        default:
            break;
        }
    }
    if(m_bIsAddToContainer)
    {
        m_bIsAddToContainer = false;
        PaintContainer PC;
        PC.paintType = m_paintState;
        switch (m_paintState)
        {
        case Arrows:
        {
            PC.beginPoint = m_beginPaintPoint;
            PC.endPoint = m_endPaintPoint;
        }
            break;
        case Ellipses:
        {
            PC.rect = rect;
        }
            break;
        case Rectangles:
        {
            PC.rect = rect;
        }
            break;
        case Lines:
        {
            PC.lines = curLines;
            curLines.clear();
        }
            break;
        case Texts:
        {
            PC.text = texts;
            PC.rect = textRect;
            PC.font = m_painter.font();
            texts.clear();
        }
            break;
        default:
            break;
        }
        PC.pen = m_painter.pen();
        rectsContainer.push_back(PC);

        if(rectsContainer.rbegin()->paintType == PaintState::Texts &&
                rectsContainer.rbegin()->text.isEmpty())
            rectsContainer.pop_back();

        m_beginPaintPoint = QPoint(0,0);//重置
        m_endPaintPoint = QPoint(0,0);
    }
    for(PaintContainer pc : rectsContainer)
    {
        switch (pc.paintType)
        {
        case Arrows:
            m_painter.setPen(pc.pen);
            drawArrow(pc.beginPoint,pc.endPoint);
            break;
        case Ellipses:
            m_painter.setPen(pc.pen);
            m_painter.drawEllipse(pc.rect);
            break;
        case Rectangles:
            m_painter.setPen(pc.pen);
            m_painter.drawRect(pc.rect);
            break;
        case Lines:
            m_painter.setPen(pc.pen);
            m_painter.drawLines(pc.lines);
            break;
        case Texts:
            m_painter.setPen(pc.pen);
            m_painter.setFont(pc.font);
            m_painter.drawText(pc.rect,pc.text);
            break;
        default:
            break;
        }
    }

    if(!m_bIsFirstSelected)
    {
        drawSelectRectInfo();
    }

    if(!m_bIsFunKeyVisible && !m_bIsFirstSelected)
    {
        drawEndPointImage();
    }

    m_painter.end();  //重绘结束;

    return QWidget::paintEvent(event);
}

//过滤QTextEdit的Ctrl+Z组合键的功能
bool ScreenShot::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == m_textEdit)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_Z && keyEvent->modifiers() == Qt::ControlModifier)
            {
                onRevocationButtonClicked();
                return true;
            }
        }
    }

    return QWidget::eventFilter(obj, event);
}

/*
* 槽函数 点击确定按钮执行
* 将当前截图复制到剪切板
*/
void ScreenShot::onSubmitButtonClicked()
{
    m_textEdit->hide();//隐藏文本框，防止文本框出现在图片中
    QRect rect = getSelectRect();
    QPixmap capture = this->grab(rect);
    clip = QApplication::clipboard();
    clip->setPixmap(capture);
    this->hide();
    //this->close();
}

/*
* 槽函数 点击保存按钮执行
* 将当前截图保存到本地文件
*/
void ScreenShot::onSaveButtonClicked()
{
    m_textEdit->hide();//隐藏文本框，防止文本框出现在图片中
    QRect rect = getSelectRect();
    QPixmap capture = this->grab(rect);
    //获取当前年月日及时间，作为图片的默认名
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString strDefaultSaveName; /*= QString::number(date.year()) + "-" +QString::number(date.month())
            + "-" + QString::number(date.day()) + "_" + QString::number(time.hour()) + "-" +
            QString::number(time.minute()) + "-" + QString::number(time.second());*/
    //年-月-日_时-分-秒.png
    QString fileName = QFileDialog::getSaveFileName(this,
          tr("save picture"), strDefaultSaveName, tr("PNG Files(*.png);;JPG Files(*.jpg);;BMP Files(*.bmp)"));
    if(!fileName.isNull())
    {
        capture.save(fileName);
        this->hide();
        //this->close();
    }
}

void ScreenShot::onCancelButtonClicked()
{
    this->hide();
    //this->close();
}

//撤回操作
void ScreenShot::onRevocationButtonClicked()
{
    if(m_textEdit->isVisible())
    {
        m_textEdit->clear();
        m_textEdit->hide();
        update();
    }
    else if(!rectsContainer.isEmpty())
    {
        rectsContainer.pop_back();
        update();
    }
}

//写入文字
void ScreenShot::onTextButtonClicked()
{
    if(!selBar_Text->isVisible())
        hideAllSelBar();
    m_bIsSelBarForTextVisible = ! m_bIsSelBarForTextVisible;
    if(m_bIsSelBarForTextVisible)
    {
        selBar_Text->move(funKey->pos().x(),funKey->pos().y()+33);
        selBar_Text->show();
        m_bIsStartPaint = true;
        m_paintState = Texts;
        resetFunKeyState();
        funKey->text->setStyleSheet("QPushButton{border-image:url(:/pic/icon/type_selected.png);}");
    }
    else
    {
        selBar_Text->hide();
        m_bIsStartPaint = false;
        m_paintState = NotStartPaint;
        resetFunKeyState();
        funKey->text->setStyleSheet("QPushButton{border-image:url(:/pic/icon/type.png);}"
                                "QPushButton:hover{border-image:url(:/pic/icon/type_selected.png);}");
    }
    m_beginPaintPoint = QPoint(0,0);//重置
    m_endPaintPoint = QPoint(0,0);
}

//画笔
void ScreenShot::onBrushButtonClicked()
{
    if(!selBar_Brush->isVisible())
        hideAllSelBar();
    m_bIsSelBarForBrushVisible = ! m_bIsSelBarForBrushVisible;
    if(m_bIsSelBarForBrushVisible)
    {
        selBar_Brush->move(funKey->pos().x(),funKey->pos().y()+33);
        selBar_Brush->show();
        m_bIsStartPaint = true;
        m_paintState = Lines;
        resetFunKeyState();
        funKey->brush->setStyleSheet("QPushButton{border-image:url(:/pic/icon/brush_selected.png);}");
    }
    else
    {
        selBar_Brush->hide();
        m_bIsStartPaint = false;
        m_paintState = NotStartPaint;
        resetFunKeyState();
        funKey->brush->setStyleSheet("QPushButton{border-image:url(:/pic/icon/brush.png);}"
                                "QPushButton:hover{border-image:url(:/pic/icon/brush_selected.png);}");
    }
    m_beginPaintPoint = QPoint(0,0);//重置
    m_endPaintPoint = QPoint(0,0);
}

//画箭头
void ScreenShot::onArrowsButtonClicked()
{
    if(!selBar_Arrows->isVisible())
        hideAllSelBar();
    m_bIsSelBarForArrowsVisible = ! m_bIsSelBarForArrowsVisible;
    if(m_bIsSelBarForArrowsVisible)
    {
        selBar_Arrows->move(funKey->pos().x(),funKey->pos().y()+33);
        selBar_Arrows->show();
        m_bIsStartPaint = true;
        m_paintState = Arrows;
        resetFunKeyState();
        funKey->arrows->setStyleSheet("QPushButton{border-image:url(:/pic/icon/arrows_selected.png);}");
    }
    else
    {
        selBar_Arrows->hide();
        m_bIsStartPaint = false;
        m_paintState = NotStartPaint;
        resetFunKeyState();
        funKey->arrows->setStyleSheet("QPushButton{border-image:url(:/pic/icon/arrows.png);}"
                                "QPushButton:hover{border-image:url(:/pic/icon/arrows_selected.png);}");
    }
    m_beginPaintPoint = QPoint(0,0);//重置
    m_endPaintPoint = QPoint(0,0);
}

//画椭圆
void ScreenShot::onEllipseButtonClicked()
{
    if(!selBar_Ellipse->isVisible())
        hideAllSelBar();
    m_bIsSelBarForEllipseVisible = ! m_bIsSelBarForEllipseVisible;
    if(m_bIsSelBarForEllipseVisible)
    {
        selBar_Ellipse->move(funKey->pos().x(),funKey->pos().y()+33);
        selBar_Ellipse->show();
        m_bIsStartPaint = true;
        m_paintState = Ellipses;
        resetFunKeyState();
        funKey->ellipse->setStyleSheet("QPushButton{border-image:url(:/pic/icon/ellipse_selected.png);}");
    }
    else
    {
        selBar_Ellipse->hide();
        m_bIsStartPaint = false;
        m_paintState = NotStartPaint;
        resetFunKeyState();
        funKey->ellipse->setStyleSheet("QPushButton{border-image:url(:/pic/icon/ellipse.png);}"
                                "QPushButton:hover{border-image:url(:/pic/icon/ellipse_selected.png);}");
    }
    m_beginPaintPoint = QPoint(0,0);//重置
    m_endPaintPoint = QPoint(0,0);
}

//画矩形
void ScreenShot::onRectangleButtonClicked()
{
    if(!selBar_Rectangle->isVisible())
        hideAllSelBar();
    m_bIsSelBarForRectangleVisible = ! m_bIsSelBarForRectangleVisible;
    if(m_bIsSelBarForRectangleVisible)
    {
        selBar_Rectangle->move(funKey->pos().x(),funKey->pos().y()+33);
        selBar_Rectangle->show();
        m_bIsStartPaint = true;
        m_paintState = Rectangles;
        resetFunKeyState();
        funKey->rectangle->setStyleSheet("QPushButton{border-image:url(:/pic/icon/rectangle_selected.png);}");
    }
    else
    {
        selBar_Rectangle->hide();
        m_bIsStartPaint = false;
        m_paintState = NotStartPaint;
        resetFunKeyState();
        funKey->rectangle->setStyleSheet("QPushButton{border-image:url(:/pic/icon/rectangle.png);}"
                                "QPushButton:hover{border-image:url(:/pic/icon/rectangle_selected.png);}");
    }
    m_beginPaintPoint = QPoint(0,0);//重置
    m_endPaintPoint = QPoint(0,0);
}

//更新输入框的大小
void ScreenShot::onTextChanged()
{
    QString str = m_textEdit->toPlainText();
    QStringList strList = str.split('\n');
    int maxsize(0),counts(2);
    for(auto i:strList)
    {
        if(i.size()>maxsize)
            maxsize = i.size();//计算每行最大字符数
        counts++;//计算行数
    }

    if(maxsize*(textFontSize+10)<90 && counts*(textFontSize+15)<90)
        m_textEdit->resize(90,90);
    else
        m_textEdit->resize((maxsize+1)*(textFontSize+10)+50,counts*(textFontSize+15)+50);
}

void ScreenShot::onTextPenColorChanged()
{
    switch(textPenColorType)
    {
    case Black:
        textPen.setColor(QColor(0,0,0));
        m_textEdit->setTextColor(QColor(0,0,0));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/black_selected.png);}");
        break;
    case White:
        textPen.setColor(QColor(255,255,255));
        m_textEdit->setTextColor(QColor(255,255,255));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/white_selected.png);}");
        break;
    case DimGrey:
        textPen.setColor(QColor(105,105,105));
        m_textEdit->setTextColor(QColor(105,105,105));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/dimgrey_selected.png);}");
        break;
    case Grey:
        textPen.setColor(QColor(128,128,128));
        m_textEdit->setTextColor(QColor(128,128,128));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/grey_selected.png);}");
        break;
    case Maroon:
        textPen.setColor(QColor(128,0,0));
        m_textEdit->setTextColor(QColor(128,0,0));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/maroon_selected.png);}");
        break;
    case Red:
        textPen.setColor(QColor(255,0,0));
        m_textEdit->setTextColor(QColor(255,0,0));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/red_selected.png);}");
        break;
    case Orange:
        textPen.setColor(QColor(255,165,0));
        m_textEdit->setTextColor(QColor(255,165,0));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/orange_selected.png);}");
        break;
    case Yellow:
        textPen.setColor(QColor(255,255,0));
        m_textEdit->setTextColor(QColor(255,255,0));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/yellow_selected.png);}");
        break;
    case Green:
        textPen.setColor(QColor(0,128,0));
        m_textEdit->setTextColor(QColor(0,128,0));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/green_selected.png);}");
        break;
    case YellowGreen:
        textPen.setColor(QColor(154,205,50));
        m_textEdit->setTextColor(QColor(154,205,50));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/yellowgreen_selected.png);}");
        break;
    case MediumBlue:
        textPen.setColor(QColor(0,0,205));
        m_textEdit->setTextColor(QColor(0,0,205));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/mediumblue_selected.png);}");
        break;
    case DodgerBlue:
        textPen.setColor(QColor(30,144,255));
        m_textEdit->setTextColor(QColor(30,144,255));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/dodgerblue_selected.png);}");
        break;
    case Purple:
        textPen.setColor(QColor(128,0,128));
        m_textEdit->setTextColor(QColor(128,0,128));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/purple_selected.png);}");
        break;
    case Magenta:
        textPen.setColor(QColor(255,0,255));
        m_textEdit->setTextColor(QColor(255,0,255));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/magenta_selected.png);}");
        break;
    case Teal:
        textPen.setColor(QColor(0,128,128));
        m_textEdit->setTextColor(QColor(0,128,128));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/teal_selected.png);}");
        break;
    case Turquoise:
        textPen.setColor(QColor(64,224,208));
        m_textEdit->setTextColor(QColor(64,224,208));
        selBar_Text->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/turquoise_selected.png);}");
        break;
    }
}

void ScreenShot::onTextFontSizeChanged(const QString& text)
{
    textFontSize = text.toInt();
    textFont.setPointSize(textFontSize);
    m_textEdit->setFontPointSize(textFontSize);
}

void ScreenShot::onBrushPenColorChanged()
{
    switch(brushPenColorType)
    {
    case Black:
        brushPen.setColor(QColor(0,0,0));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/black_selected.png);}");
        break;
    case White:
        brushPen.setColor(QColor(255,255,255));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/white_selected.png);}");
        break;
    case DimGrey:
        brushPen.setColor(QColor(105,105,105));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/dimgrey_selected.png);}");
        break;
    case Grey:
        brushPen.setColor(QColor(128,128,128));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/grey_selected.png);}");
        break;
    case Maroon:
        brushPen.setColor(QColor(128,0,0));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/maroon_selected.png);}");
        break;
    case Red:
        brushPen.setColor(QColor(255,0,0));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/red_selected.png);}");
        break;
    case Orange:
        brushPen.setColor(QColor(255,165,0));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/orange_selected.png);}");
        break;
    case Yellow:
        brushPen.setColor(QColor(255,255,0));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/yellow_selected.png);}");
        break;
    case Green:
        brushPen.setColor(QColor(0,128,0));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/green_selected.png);}");
        break;
    case YellowGreen:
        brushPen.setColor(QColor(154,205,50));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/yellowgreen_selected.png);}");
        break;
    case MediumBlue:
        brushPen.setColor(QColor(0,0,205));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/mediumblue_selected.png);}");
        break;
    case DodgerBlue:
        brushPen.setColor(QColor(30,144,255));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/dodgerblue_selected.png);}");
        break;
    case Purple:
        brushPen.setColor(QColor(128,0,128));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/purple_selected.png);}");
        break;
    case Magenta:
        brushPen.setColor(QColor(255,0,255));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/magenta_selected.png);}");
        break;
    case Teal:
        brushPen.setColor(QColor(0,128,128));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/teal_selected.png);}");
        break;
    case Turquoise:
        brushPen.setColor(QColor(64,224,208));
        selBar_Brush->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/turquoise_selected.png);}");
        break;
    }
}

void ScreenShot::onBrushPenWeightChanged()
{
    switch(brushPenWeightType)
    {
    case Small:
    {
        brushPen.setWidth(1);
        selBar_Brush->smallDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/smalldot_selected.png);}");
        selBar_Brush->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/middledot_selected.png);}");
        selBar_Brush->bigDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/bigdot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/bigdot_selected.png);}");
    }
        break;
    case Medium:
    {
        brushPen.setWidth(3);
        selBar_Brush->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot_selected.png);}");
        selBar_Brush->smallDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/smalldot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/smalldot_selected.png);}");
        selBar_Brush->bigDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/bigdot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/bigdot_selected.png);}");
    }
        break;
    case Big:
    {
        brushPen.setWidth(5);
        selBar_Brush->bigDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/bigdot_selected.png);}");
        selBar_Brush->smallDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/smalldot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/smalldot_selected.png);}");
        selBar_Brush->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/middledot_selected.png);}");
    }
        break;
    }
}

void ScreenShot::onArrowPenColorChanged()
{
    switch(arrowPenColorType)
    {
    case Black:
        arrowPen.setColor(QColor(0,0,0));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/black_selected.png);}");
        break;
    case White:
        arrowPen.setColor(QColor(255,255,255));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/white_selected.png);}");
        break;
    case DimGrey:
        arrowPen.setColor(QColor(105,105,105));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/dimgrey_selected.png);}");
        break;
    case Grey:
        arrowPen.setColor(QColor(128,128,128));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/grey_selected.png);}");
        break;
    case Maroon:
        arrowPen.setColor(QColor(128,0,0));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/maroon_selected.png);}");
        break;
    case Red:
        arrowPen.setColor(QColor(255,0,0));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/red_selected.png);}");
        break;
    case Orange:
        arrowPen.setColor(QColor(255,165,0));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/orange_selected.png);}");
        break;
    case Yellow:
        arrowPen.setColor(QColor(255,255,0));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/yellow_selected.png);}");
        break;
    case Green:
        arrowPen.setColor(QColor(0,128,0));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/green_selected.png);}");
        break;
    case YellowGreen:
        arrowPen.setColor(QColor(154,205,50));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/yellowgreen_selected.png);}");
        break;
    case MediumBlue:
        arrowPen.setColor(QColor(0,0,205));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/mediumblue_selected.png);}");
        break;
    case DodgerBlue:
        arrowPen.setColor(QColor(30,144,255));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/dodgerblue_selected.png);}");
        break;
    case Purple:
        arrowPen.setColor(QColor(128,0,128));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/purple_selected.png);}");
        break;
    case Magenta:
        arrowPen.setColor(QColor(255,0,255));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/magenta_selected.png);}");
        break;
    case Teal:
        arrowPen.setColor(QColor(0,128,128));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/teal_selected.png);}");
        break;
    case Turquoise:
        arrowPen.setColor(QColor(64,224,208));
        selBar_Arrows->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/turquoise_selected.png);}");
        break;
    }
}

void ScreenShot::onArrowPenWeightChanged()
{
    switch(arrowPenWeightType)
    {
    case Small:
    {
        arrowPen.setWidth(1);
        selBar_Arrows->smallDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/smalldot_selected.png);}");
        selBar_Arrows->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/middledot_selected.png);}");
        selBar_Arrows->bigDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/bigdot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/bigdot_selected.png);}");
    }
        break;
    case Medium:
    {
        arrowPen.setWidth(3);
        selBar_Arrows->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot_selected.png);}");
        selBar_Arrows->smallDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/smalldot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/smalldot_selected.png);}");
        selBar_Arrows->bigDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/bigdot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/bigdot_selected.png);}");
    }
        break;
    case Big:
    {
        arrowPen.setWidth(5);
        selBar_Arrows->bigDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/bigdot_selected.png);}");
        selBar_Arrows->smallDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/smalldot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/smalldot_selected.png);}");
        selBar_Arrows->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/middledot_selected.png);}");
    }
        break;
    }
}

void ScreenShot::onEllipsePenColorChanged()
{
    switch(ellipsePenColorType)
    {
    case Black:
        ellipsePen.setColor(QColor(0,0,0));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/black_selected.png);}");
        break;
    case White:
        ellipsePen.setColor(QColor(255,255,255));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/white_selected.png);}");
        break;
    case DimGrey:
        ellipsePen.setColor(QColor(105,105,105));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/dimgrey_selected.png);}");
        break;
    case Grey:
        ellipsePen.setColor(QColor(128,128,128));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/grey_selected.png);}");
        break;
    case Maroon:
        ellipsePen.setColor(QColor(128,0,0));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/maroon_selected.png);}");
        break;
    case Red:
        ellipsePen.setColor(QColor(255,0,0));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/red_selected.png);}");
        break;
    case Orange:
        ellipsePen.setColor(QColor(255,165,0));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/orange_selected.png);}");
        break;
    case Yellow:
        ellipsePen.setColor(QColor(255,255,0));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/yellow_selected.png);}");
        break;
    case Green:
        ellipsePen.setColor(QColor(0,128,0));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/green_selected.png);}");
        break;
    case YellowGreen:
        ellipsePen.setColor(QColor(154,205,50));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/yellowgreen_selected.png);}");
        break;
    case MediumBlue:
        ellipsePen.setColor(QColor(0,0,205));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/mediumblue_selected.png);}");
        break;
    case DodgerBlue:
        ellipsePen.setColor(QColor(30,144,255));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/dodgerblue_selected.png);}");
        break;
    case Purple:
        ellipsePen.setColor(QColor(128,0,128));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/purple_selected.png);}");
        break;
    case Magenta:
        ellipsePen.setColor(QColor(255,0,255));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/magenta_selected.png);}");
        break;
    case Teal:
        ellipsePen.setColor(QColor(0,128,128));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/teal_selected.png);}");
        break;
    case Turquoise:
        ellipsePen.setColor(QColor(64,224,208));
        selBar_Ellipse->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/turquoise_selected.png);}");
        break;
    }
}

void ScreenShot::onEllipsePenWeightChanged()
{
    switch(ellipsePenWeightType)
    {
    case Small:
    {
        ellipsePen.setWidth(1);
        selBar_Ellipse->smallDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/smalldot_selected.png);}");
        selBar_Ellipse->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/middledot_selected.png);}");
        selBar_Ellipse->bigDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/bigdot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/bigdot_selected.png);}");
    }
        break;
    case Medium:
    {
        ellipsePen.setWidth(3);
        selBar_Ellipse->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot_selected.png);}");
        selBar_Ellipse->smallDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/smalldot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/smalldot_selected.png);}");
        selBar_Ellipse->bigDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/bigdot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/bigdot_selected.png);}");
    }
        break;
    case Big:
    {
        ellipsePen.setWidth(5);
        selBar_Ellipse->bigDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/bigdot_selected.png);}");
        selBar_Ellipse->smallDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/smalldot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/smalldot_selected.png);}");
        selBar_Ellipse->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/middledot_selected.png);}");
    }
        break;
    }
}

void ScreenShot::onRectPenWeightChanged()
{
    switch(rectPenWeightType)
    {
    case Small:
    {
        rectPen.setWidth(1);
        selBar_Rectangle->smallDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/smalldot_selected.png);}");
        selBar_Rectangle->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/middledot_selected.png);}");
        selBar_Rectangle->bigDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/bigdot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/bigdot_selected.png);}");
    }
        break;
    case Medium:
    {
        rectPen.setWidth(3);
        selBar_Rectangle->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot_selected.png);}");
        selBar_Rectangle->smallDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/smalldot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/smalldot_selected.png);}");
        selBar_Rectangle->bigDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/bigdot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/bigdot_selected.png);}");
    }
        break;
    case Big:
    {
        rectPen.setWidth(5);
        selBar_Rectangle->bigDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/bigdot_selected.png);}");
        selBar_Rectangle->smallDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/smalldot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/smalldot_selected.png);}");
        selBar_Rectangle->mediumDot->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/middledot.png);}"
                                    "QPushButton:hover{border-image:url(:/pic/barIcon/middledot_selected.png);}");
    }
        break;
    }
}

void ScreenShot::onRectPenColorChanged()
{
    switch(rectPenColorType)
    {
    case Black:
        rectPen.setColor(QColor(0,0,0));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/black_selected.png);}");
        break;
    case White:
        rectPen.setColor(QColor(255,255,255));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/white_selected.png);}");
        break;
    case DimGrey:
        rectPen.setColor(QColor(105,105,105));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/dimgrey_selected.png);}");
        break;
    case Grey:
        rectPen.setColor(QColor(128,128,128));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/grey_selected.png);}");
        break;
    case Maroon:
        rectPen.setColor(QColor(128,0,0));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/maroon_selected.png);}");
        break;
    case Red:
        rectPen.setColor(QColor(255,0,0));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/red_selected.png);}");
        break;
    case Orange:
        rectPen.setColor(QColor(255,165,0));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/orange_selected.png);}");
        break;
    case Yellow:
        rectPen.setColor(QColor(255,255,0));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/yellow_selected.png);}");
        break;
    case Green:
        rectPen.setColor(QColor(0,128,0));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/green_selected.png);}");
        break;
    case YellowGreen:
        rectPen.setColor(QColor(154,205,50));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/yellowgreen_selected.png);}");
        break;
    case MediumBlue:
        rectPen.setColor(QColor(0,0,205));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/mediumblue_selected.png);}");
        break;
    case DodgerBlue:
        rectPen.setColor(QColor(30,144,255));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/dodgerblue_selected.png);}");
        break;
    case Purple:
        rectPen.setColor(QColor(128,0,128));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/purple_selected.png);}");
        break;
    case Magenta:
        rectPen.setColor(QColor(255,0,255));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/magenta_selected.png);}");
        break;
    case Teal:
        rectPen.setColor(QColor(0,128,128));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/teal_selected.png);}");
        break;
    case Turquoise:
        rectPen.setColor(QColor(64,224,208));
        selBar_Rectangle->color->setStyleSheet("QPushButton{border-image:url(:/pic/barIcon/turquoise_selected.png);}");
        break;
    }
}

// 根据当前截取状态获取当前选中的截图区域;
QRect ScreenShot::getSelectRect()
{
    if (m_currentCaptureState == BeginCaptureImage || m_currentCaptureState == FinishCaptureImage)
    {
        return getRect(m_beginPoint, m_endPoint);
    }
    else if (m_currentCaptureState == BeginMoveCaptureArea || m_currentCaptureState == FinishMoveCaptureArea)
    {
        return getMoveRect();
    }
    else if (m_currentCaptureState == BeginMoveStretchRect || m_currentCaptureState == FinishMoveStretchRect)
    {
        return getStretchRect();
    }

    return QRect(0, 0, 0, 0);
}

// 绘制当前选中的截图区域;
void ScreenShot::drawCaptureImage()
{
    m_capturePixmap = m_loadPixmap.copy(m_currentSelectRect);
    m_painter.drawPixmap(m_currentSelectRect.topLeft(), m_capturePixmap);
    m_painter.drawRect(m_currentSelectRect);
    drawStretchRect();
}

// 绘制选中矩形各拖拽点小矩形;
void ScreenShot::drawStretchRect()
{
    QColor color = QColor(0, 174, 255);
    // 四个角坐标;
    QPoint topLeft = m_currentSelectRect.topLeft();
    QPoint topRight = m_currentSelectRect.topRight();
    QPoint bottomLeft = m_currentSelectRect.bottomLeft();
    QPoint bottomRight = m_currentSelectRect.bottomRight();
    // 四条边中间点坐标;
    QPoint leftCenter = QPoint(topLeft.x(), (topLeft.y() + bottomLeft.y()) / 2);
    QPoint topCenter = QPoint((topLeft.x() + topRight.x()) / 2, topLeft.y());
    QPoint rightCenter = QPoint(topRight.x(), leftCenter.y());
    QPoint bottomCenter = QPoint(topCenter.x(), bottomLeft.y());

    m_topLeftRect = QRect(topLeft.x() - STRETCH_RECT_WIDTH / 2, topLeft.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_topRightRect = QRect(topRight.x() - STRETCH_RECT_WIDTH / 2, topRight.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomLeftRect = QRect(bottomLeft.x() - STRETCH_RECT_WIDTH / 2, bottomLeft.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomRightRect = QRect(bottomRight.x() - STRETCH_RECT_WIDTH / 2, bottomRight.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);

    m_leftCenterRect = QRect(leftCenter.x() - STRETCH_RECT_WIDTH / 2, leftCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_topCenterRect = QRect(topCenter.x() - STRETCH_RECT_WIDTH / 2, topCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_rightCenterRect = QRect(rightCenter.x() - STRETCH_RECT_WIDTH / 2, rightCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomCenterRect = QRect(bottomCenter.x() - STRETCH_RECT_WIDTH / 2, bottomCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);

    m_painter.fillRect(m_topLeftRect, color);
    m_painter.fillRect(m_topRightRect, color);
    m_painter.fillRect(m_bottomLeftRect, color);
    m_painter.fillRect(m_bottomRightRect, color);
    m_painter.fillRect(m_leftCenterRect, color);
    m_painter.fillRect(m_topCenterRect, color);
    m_painter.fillRect(m_rightCenterRect, color);
    m_painter.fillRect(m_bottomCenterRect, color);
}

// 获取移动后,当前选中的矩形;
QRect ScreenShot::getMoveRect()
{
    // 通过getMovePoint方法先检查当前是否移动超出屏幕;
    QPoint movePoint = getMovePoint();
    QPoint beginPoint = m_beginPoint + movePoint;
    QPoint endPoint = m_endPoint + movePoint;
    // 结束移动选区时更新当前m_beginPoint , m_endPoint,防止下一次操作时截取的图片有问题;
    if (m_currentCaptureState == FinishMoveCaptureArea)
    {
        m_beginPoint = beginPoint;
        m_endPoint = endPoint;
        m_beginMovePoint = QPoint(0, 0);
        m_endMovePoint = QPoint(0, 0);
    }
    return getRect(beginPoint, endPoint);
}

QPoint ScreenShot::getMovePoint()
{
    QPoint movePoint = m_endMovePoint - m_beginMovePoint;
    QRect currentRect = getRect(m_beginPoint, m_endPoint);
    // 检查当前是否移动超出屏幕;

    //移动选区是否超出屏幕左边界;
    if (currentRect.topLeft().x() + movePoint.x() < 0)
    {
        movePoint.setX(0 - currentRect.topLeft().x());
    }
    //移动选区是否超出屏幕上边界;
    if (currentRect.topLeft().y() + movePoint.y() < 0)
    {
        movePoint.setY(0 - currentRect.topLeft().y());
    }
    //移动选区是否超出屏幕右边界;
    if (currentRect.bottomRight().x() + movePoint.x() > m_screenwidth)
    {
        movePoint.setX(m_screenwidth - currentRect.bottomRight().x());
    }
    //移动选区是否超出屏幕下边界;
    if (currentRect.bottomRight().y() + movePoint.y() > m_screenheight)
    {
        movePoint.setY(m_screenheight - currentRect.bottomRight().y());
    }

    return movePoint;
}

// 获取当前鼠标位于哪一个拖拽顶点;
StretchRectState ScreenShot::getStrethRectState(QPoint point)
{
    StretchRectState stretchRectState = NotSelect;
    if (m_topLeftRect.contains(point))
    {
        stretchRectState = TopLeftRect;
    }
    else if (m_topCenterRect.contains(point))
    {
        stretchRectState = TopCenterRect;
    }
    else if (m_topRightRect.contains(point))
    {
        stretchRectState = TopRightRect;
    }
    else if (m_rightCenterRect.contains(point))
    {
        stretchRectState = RightCenterRect;
    }
    else if (m_bottomRightRect.contains(point))
    {
        stretchRectState = BottomRightRect;
    }
    else if (m_bottomCenterRect.contains(point))
    {
        stretchRectState = BottomCenterRect;
    }
    else if (m_bottomLeftRect.contains(point))
    {
        stretchRectState = BottomLeftRect;
    }
    else if (m_leftCenterRect.contains(point))
    {
        stretchRectState = LeftCenterRect;
    }

    return stretchRectState;
}

// 设置鼠标停在拖拽定点处的样式;
void ScreenShot::setStretchCursorStyle(StretchRectState stretchRectState)
{
    switch (stretchRectState)
    {
    case NotSelect:
        setCursor(Qt::ArrowCursor);
        break;
    case TopLeftRect:
    case BottomRightRect:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case TopRightRect:
    case BottomLeftRect:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case LeftCenterRect:
    case RightCenterRect:
        setCursor(Qt::SizeHorCursor);
        break;
    case TopCenterRect:
    case BottomCenterRect:
        setCursor(Qt::SizeVerCursor);
        break;
    }
}

// 获取拖拽后的矩形选中区域;
QRect ScreenShot::getStretchRect()
{
    QRect stretchRect;
    QRect currentRect = getRect(m_beginPoint, m_endPoint);
    switch (m_stretchRectState)
    {
    case NotSelect:
        stretchRect = getRect(m_beginPoint, m_endPoint);
        break;
    case TopLeftRect:
        {
            stretchRect = getRect(currentRect.bottomRight(), m_endMovePoint);
        }
        break;
    case TopRightRect:
        {
            QPoint beginPoint = QPoint(currentRect.topLeft().x(), m_endMovePoint.y());
            QPoint endPoint = QPoint(m_endMovePoint.x(), currentRect.bottomRight().y());
            stretchRect = getRect(beginPoint, endPoint);
        }
        break;
    case BottomLeftRect:
        {
            QPoint beginPoint = QPoint(m_endMovePoint.x() , currentRect.topLeft().y());
            QPoint endPoint = QPoint(currentRect.bottomRight().x(), m_endMovePoint.y());
            stretchRect = getRect(beginPoint, endPoint);
        }
        break;
    case BottomRightRect:
        {
            stretchRect = getRect(currentRect.topLeft(), m_endMovePoint);
        }
        break;
    case LeftCenterRect:
        {
            QPoint beginPoint = QPoint(m_endMovePoint.x(), currentRect.topLeft().y());
            stretchRect = getRect(beginPoint, currentRect.bottomRight());
        }
        break;
    case TopCenterRect:
    {
        QPoint beginPoint = QPoint(currentRect.topLeft().x(), m_endMovePoint.y());
        stretchRect = getRect(beginPoint, currentRect.bottomRight());
    }
        break;
    case RightCenterRect:
    {
        QPoint endPoint = QPoint(m_endMovePoint.x(), currentRect.bottomRight().y());
        stretchRect = getRect(currentRect.topLeft(), endPoint);
    }
        break;
    case BottomCenterRect:
    {
        QPoint endPoint = QPoint(currentRect.bottomRight().x(), m_endMovePoint.y());
        stretchRect = getRect(currentRect.topLeft(), endPoint);
    }
        break;
    default:
    {
        stretchRect = getRect(m_beginPoint , m_endPoint );
    }
        break;
    }

    // 拖动结束更新 m_beginPoint , m_endPoint;
    if (m_currentCaptureState == FinishMoveStretchRect)
    {
        m_beginPoint = stretchRect.topLeft();
        m_endPoint = stretchRect.bottomRight();

        //取消当前截图状态，防止在绘图时鼠标移动产生一个神奇的bug
        m_currentCaptureState = FinishCaptureImage;
    }

    return stretchRect;
}

// 绘制选中矩形信息;
void ScreenShot::drawSelectRectInfo()
{
    int posX, posY;
    QPoint topLeftPoint = m_currentSelectRect.topLeft();

    posX = topLeftPoint.x() + SELECT_RECT_BORDER_WIDTH;
    if (topLeftPoint.y() > SELECT_RECT_INFO_HEIGHT)
    {
        posY = topLeftPoint.y() - SELECT_RECT_INFO_HEIGHT - SELECT_RECT_BORDER_WIDTH;
    }
    else
    {
        posY = topLeftPoint.y() + SELECT_RECT_BORDER_WIDTH;
    }
    topLeftPoint = QPoint(posX, posY);

    QColor backColor = QColor(0, 0, 0, 160);
    m_painter.fillRect(QRect(topLeftPoint, QSize(SELECT_RECT_INFO_WIDTH, SELECT_RECT_INFO_HEIGHT)), backColor);

    // 当前选中矩形的宽高信息;
    QString selectRectSizeInfo = QString("%1×%2").arg(m_currentSelectRect.width()).arg(m_currentSelectRect.height());
    int fontWidth = this->fontMetrics().width(selectRectSizeInfo);
    QFont font;
    font.setPointSize(9);
    m_painter.setFont(font);
    m_painter.setPen(QPen(Qt::white));
    m_painter.drawText(QPoint(topLeftPoint.x() + (SELECT_RECT_INFO_WIDTH - fontWidth) / 2, topLeftPoint.y() + 14), selectRectSizeInfo);
}

// 绘制鼠标拖拽时选区矩形的右下顶点的放大图;
void ScreenShot::drawEndPointImage()
{
    int posX, posY;
    QPoint topLeftPoint = QCursor::pos();

    // 5、25 分别为鼠标所在点距离放大图的X轴、Y轴距离;
    //当放大图片区域超出右边屏幕时;
    if (topLeftPoint.x() + END_POINT_RECT_WIDTH + 5 > m_screenwidth)
    {
        // 这里暂时未考虑到双屏幕（多屏幕）;
        if (topLeftPoint.x() > m_screenwidth)
        {
            posX = m_screenwidth - END_POINT_RECT_WIDTH - 5;
        }
        else
        {
            posX = topLeftPoint.x() - END_POINT_RECT_WIDTH - 5;
        }
    }
    else
    {
        posX = topLeftPoint.x() + 5;
    }

    // 当放大图片区域超出屏幕下方时;
    if (topLeftPoint.y() + END_POINT_RECT_HEIGHT + 25 > m_screenheight)
    {
        posY = topLeftPoint.y() - END_POINT_RECT_HEIGHT - 25;
    }
    // 当鼠标未屏幕下方，正常显示时;
    else
    {
        posY = topLeftPoint.y() + 25;
    }

    topLeftPoint = QPoint(posX, posY);

    // 绘制放大图;
    QPixmap endPointImage = m_loadPixmap.copy(QRect(QCursor::pos().x() - 15, QCursor::pos().y() - 11, 30, 22)).scaled(END_POINT_RECT_WIDTH, END_POINT_IMAGE_HEIGHT);
    m_painter.drawPixmap(topLeftPoint, endPointImage);

    // 绘制十字坐标;
    m_painter.setPen(QPen(QColor(0, 180, 255 , 180), 4));
    // 竖线;
    m_painter.drawLine(QPoint(topLeftPoint.x() + END_POINT_RECT_WIDTH / 2, topLeftPoint.y() + 2), QPoint(topLeftPoint.x() + END_POINT_RECT_WIDTH / 2, topLeftPoint.y() + END_POINT_IMAGE_HEIGHT - 2));
    // 横线;
    m_painter.drawLine(QPoint(topLeftPoint.x() + 2 , topLeftPoint.y() + END_POINT_IMAGE_HEIGHT / 2), QPoint(topLeftPoint.x() + END_POINT_RECT_WIDTH - 2 , topLeftPoint.y() + END_POINT_IMAGE_HEIGHT / 2));

    m_painter.setPen(QPen(Qt::white, 3));
    m_painter.drawRect(QRect(QPoint(topLeftPoint.x() + 1 , topLeftPoint.y() + 1), QSize(END_POINT_RECT_WIDTH - 2, END_POINT_IMAGE_HEIGHT - 2)));
    m_painter.setPen(QPen(Qt::black, 1));
    m_painter.drawRect(QRect(topLeftPoint, QSize(END_POINT_RECT_WIDTH, END_POINT_IMAGE_HEIGHT)));

    // 绘制放大图信息;
    topLeftPoint = QPoint(topLeftPoint.x(), topLeftPoint.y() + END_POINT_IMAGE_HEIGHT);
    QColor backColor = QColor(0, 0, 0, 160);
    m_painter.fillRect(QRect(topLeftPoint, QSize(END_POINT_RECT_WIDTH, END_POINT_RECT_HEIGHT - END_POINT_IMAGE_HEIGHT)), backColor);
    // 当前选中矩形的宽高信息;
    QString selectRectSizeInfo = QString("%1×%2").arg(m_currentSelectRect.width()).arg(m_currentSelectRect.height());
    QImage image = m_loadPixmap.toImage();
    QColor endPointColor = image.pixel(QCursor::pos());
    QString selectPointRGBInfo = QString("RGB:(%1,%2,%3)").arg(endPointColor.red()).arg(endPointColor.green()).arg(endPointColor.blue());
    QFont font;
    font.setPointSize(8);
    m_painter.setFont(font);
    m_painter.setPen(Qt::white);
    m_painter.drawText(QPoint(topLeftPoint.x() + 6, topLeftPoint.y() + 14), selectRectSizeInfo);
    m_painter.drawText(QPoint(topLeftPoint.x() + 6, topLeftPoint.y() + 27), selectPointRGBInfo);
}

void ScreenShot::moveFunKey()
{
    if(!m_bIsFunKeyVisible)
    {//功能栏移动
        m_currentSelectRect = getSelectRect();//更新位置，防止功能栏与截图区域移动不同步
        if(m_currentSelectRect.bottom() <= m_screenheight - 90)
        {
            funKey->move(m_currentSelectRect.bottomRight().x()-funKey->width()-1,
                         m_currentSelectRect.bottomRight().y()+3);
        }
        else if(m_currentSelectRect.bottom() > (m_screenheight -90) && m_currentSelectRect.top()>50)
        {
            funKey->move(m_currentSelectRect.topRight().x()-funKey->width()-1,
                         m_currentSelectRect.topRight().y()-funKey->height()-3);
        }
        else
        {
            funKey->move(m_currentSelectRect.topRight().x()-funKey->width()-1,
                         m_currentSelectRect.topRight().y());
        }
        m_bIsFunKeyVisible = true;
        funKey->show();
    }
}

//隐藏所有选择栏
void ScreenShot::hideAllSelBar()
{
    m_bIsSelBarForTextVisible = false;
    m_bIsSelBarForBrushVisible = false;
    m_bIsSelBarForArrowsVisible = false;
    m_bIsSelBarForEllipseVisible = false;
    m_bIsSelBarForRectangleVisible = false;

    selBar_Text->hide();
    selBar_Brush->hide();
    selBar_Arrows->hide();
    selBar_Ellipse->hide();
    selBar_Rectangle->hide();
}

//重置所有功能栏图标状态
void ScreenShot::resetFunKeyState()
{
    funKey->text->setStyleSheet("QPushButton{border-image:url(:/pic/icon/type.png);}"
                            "QPushButton:hover{border-image:url(:/pic/icon/type_selected.png);}");
    funKey->brush->setStyleSheet("QPushButton{border-image:url(:/pic/icon/brush.png);}"
                            "QPushButton:hover{border-image:url(:/pic/icon/brush_selected.png);}");
    funKey->arrows->setStyleSheet("QPushButton{border-image:url(:/pic/icon/arrows.png);}"
                            "QPushButton:hover{border-image:url(:/pic/icon/arrows_selected.png);}");
    funKey->ellipse->setStyleSheet("QPushButton{border-image:url(:/pic/icon/ellipse.png);}"
                            "QPushButton:hover{border-image:url(:/pic/icon/ellipse_selected.png);}");
    funKey->rectangle->setStyleSheet("QPushButton{border-image:url(:/pic/icon/rectangle.png);}"
                            "QPushButton:hover{border-image:url(:/pic/icon/rectangle_selected.png);}");
}

//获取当前绘图矩形
QRect ScreenShot::getPaintRect()
{
    int x = m_beginPaintPoint.x()>m_endPaintPoint.x()?m_endPaintPoint.x():m_beginPaintPoint.x();
    int y = m_beginPaintPoint.y()>m_endPaintPoint.y()?m_endPaintPoint.y():m_beginPaintPoint.y();
    int width = qAbs(m_beginPaintPoint.x()-m_endPaintPoint.x());
    int height = qAbs(m_beginPaintPoint.y()-m_endPaintPoint.y());

    QRect rect(x,y,width,height);
    return rect;
}

//实现绘制箭头
void ScreenShot::drawArrow(QPoint startpoint, QPoint endpoint)
{
    double par=15.0;
    double slopy=qAtan2((endpoint.y()-startpoint.y()),(endpoint.x()-startpoint.x()));
    double cosy=qCos(slopy);
    double siny=qSin(slopy);
    QPoint point1 = QPoint(endpoint.x() + int(-par*cosy - (par / 2.0*siny)), endpoint.y() + int(-par*siny + (par / 2.0*cosy)));
    QPoint point2 = QPoint(endpoint.x() + int(-par*cosy + (par / 2.0*siny)), endpoint.y() - int(par / 2.0*cosy + par*siny));
    QPoint points[3]={endpoint,point1,point2};
    m_painter.setRenderHint(QPainter::Antialiasing,true);

    m_painter.drawPolygon(points,3);
    int offsetx=int(par*siny/3);
    int offsety=int(par*cosy/3);
    QPoint point3,point4;
    point3 = QPoint(endpoint.x() + int(-par*cosy - (par / 2.0*siny)) + offsetx, endpoint.y() + int(-par*siny + (par / 2.0*cosy)) - offsety);
    point4 = QPoint(endpoint.x() + int(-par*cosy + (par / 2.0*siny) - offsetx), endpoint.y() - int(par / 2.0*cosy + par*siny) + offsety);
    QPoint arrbodypoints[3]={startpoint,point3,point4};
    m_painter.drawPolygon(arrbodypoints,3);
}

QPen ScreenShot::getPen()
{
    QPen pen;

    switch (m_paintState)
    {
    case Texts:
        pen = textPen;
        break;
    case Lines:
        pen = brushPen;
        break;
    case Arrows:
        pen = arrowPen;
        break;
    case Ellipses:
        pen = ellipsePen;
        break;
    case Rectangles:
        pen = rectPen;
        break;
    default:
        break;
    }

    return pen;
}

#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QVector>
#include <QTextEdit>
#include "functionkey.h"
#include "selectionbar.h"

enum CaptureState{
    InitCapture = 0,
    BeginCaptureImage,
    FinishCaptureImage,
    BeginMoveCaptureArea,
    FinishMoveCaptureArea,
    BeginMoveStretchRect,
    FinishMoveStretchRect,
}; //进行截屏的状态;

enum StretchRectState{
    NotSelect = 0,
    TopLeftRect,
    TopRightRect,
    BottomLeftRect,
    BottomRightRect,
    LeftCenterRect,
    TopCenterRect,
    RightCenterRect,
    BottomCenterRect
};// 当前鼠标所在顶点状态;

enum PaintState{
    NotStartPaint = 0,
    Rectangles,
    Ellipses,
    Arrows,
    Texts,
    Lines
};//绘图状态

enum PenColorType{
    Black = 1,
    White,
    DimGrey,
    Grey,
    Maroon,
    Red,
    Orange,
    Yellow,
    Green,
    YellowGreen,
    MediumBlue,
    DodgerBlue,
    Purple,
    Magenta,
    Teal,
    Turquoise
};//选择栏颜色类型

enum PenWeightType{
    Small = 1,
    Medium = 3,
    Big = 5
};//线粗细类型

struct PaintContainer
{
    PaintState paintType;
    QPoint beginPoint;
    QPoint endPoint;
    QRect rect;
    QVector<QLineF> lines;
    QString text;
    QPen pen;
    QFont font;
};//绘图容器

class ScreenShot : public QWidget
{
    Q_OBJECT

public:
    ScreenShot(QWidget *parent = nullptr);

    void initialize();
    void initStretchRect();
    void loadBackgroundPixmap(QPoint mousePosition,bool isMouseMove=false);//捕获当前屏幕
    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);//获取选择矩形窗口
    QRect getMoveRect();
    QRect getStretchRect();
    bool isPressPointInSelectRect(QPoint mousePressPoint);
    QRect getSelectRect();
    QPoint getMovePoint();
    StretchRectState getStrethRectState(QPoint point);
    void setStretchCursorStyle(StretchRectState stretchRectState);
    void drawCaptureImage(double dbScX,double dbScY);
    void drawStretchRect();
    void drawSelectRectInfo();
    void drawEndPointImage();
    void moveFunKey();
    void hideAllSelBar();//隐藏所有的选择栏
    void resetFunKeyState();//重置所有的功能栏
    QRect getPaintRect();//获取绘图的矩形区域
    void drawArrow(QPoint startpoint, QPoint endpoint);//绘制箭头
    QPen getPen();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

Q_SIGNALS:

public slots:
    void onSubmitButtonClicked();
    void onSaveButtonClicked();
    void onCancelButtonClicked();
    void onRevocationButtonClicked();
    void onTextButtonClicked();
    void onBrushButtonClicked();
    void onArrowsButtonClicked();
    void onEllipseButtonClicked();
    void onRectangleButtonClicked();
    void onTextChanged();
    void onTextPenColorChanged();
    void onTextFontSizeChanged(const QString& text);
    void onBrushPenColorChanged();
    void onBrushPenWeightChanged();
    void onArrowPenColorChanged();
    void onArrowPenWeightChanged();
    void onEllipsePenColorChanged();
    void onEllipsePenWeightChanged();
    void onRectPenColorChanged();
    void onRectPenWeightChanged();

signals:
    void activationScreenshot();
private:
    QPixmap m_loadPixmap, m_capturePixmap;
    QClipboard * clip;//剪切板
    int m_screenwidth;
    int m_screenheight;
    // 保存确定选取的坐标点;
    QPoint m_beginPoint, m_endPoint;
    QPoint m_beginMovePoint, m_endMovePoint;
    QPainter m_painter;
    CaptureState m_currentCaptureState;// 保存当前截图状态;
    QRect m_currentSelectRect;// 当前选择区域矩形;
    // 选中矩形8个顶点小矩形;
    QRect m_topLeftRect, m_topRightRect, m_bottomLeftRect, m_bottomRightRect;
    QRect m_leftCenterRect, m_topCenterRect, m_rightCenterRect, m_bottomCenterRect;
    // 当前鼠标所在顶点状态;
    StretchRectState m_stretchRectState;

    FunctionKey * funKey;//注册功能栏
    bool m_bIsFunKeyVisible;//功能栏是否可见
    bool m_bIsFirstSelected;//是否是第一次选择区域

    SelectionBar * selBar_Text;//注册线条粗细及颜色选择栏
    bool m_bIsSelBarForTextVisible;
    PenColorType textPenColorType;
    PenWeightType textPenWeightType;
    QPen textPen;
    QFont textFont;
    SelectionBar * selBar_Brush;//注册线条粗细及颜色选择栏
    bool m_bIsSelBarForBrushVisible;
    PenColorType brushPenColorType;
    PenWeightType brushPenWeightType;
    QPen brushPen;
    SelectionBar * selBar_Arrows;//注册线条粗细及颜色选择栏
    bool m_bIsSelBarForArrowsVisible;
    PenColorType arrowPenColorType;
    PenWeightType arrowPenWeightType;
    QPen arrowPen;
    SelectionBar * selBar_Ellipse;//注册线条粗细及颜色选择栏
    bool m_bIsSelBarForEllipseVisible;
    PenColorType ellipsePenColorType;
    PenWeightType ellipsePenWeightType;
    QPen ellipsePen;
    SelectionBar * selBar_Rectangle;//注册线条粗细及颜色选择栏
    bool m_bIsSelBarForRectangleVisible;
    PenColorType rectPenColorType;
    PenWeightType rectPenWeightType;
    QPen rectPen;

    bool m_bIsStartPaint;

    PaintState m_paintState;//绘图状态
    QPoint m_beginPaintPoint,m_endPaintPoint;//绘图点
    bool m_bIsPaintMousePress;//画图的时候鼠标左键是否按下
    bool m_bIsAddToContainer;//画的图是否添加入容器中
    QRect rectTem;
    QVector<PaintContainer> rectsContainer;//矩形容器
    QVector<QLineF> curLines;
    QTextEdit * m_textEdit;
    QString texts;
    QRect textRect;
    int textFontSize;

    int m_nCurrMonitor;
    bool m_bIsDrawEndPointImage;

    int m_nScreenX,m_nScreenY;

    QVector<QRect> saveRectList;
    int nMaxTextWidth,nMaxTextHeight;

};
#endif // SCREENSHOT_H

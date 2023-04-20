#ifndef QMULTSCREEN_H
#define QMULTSCREEN_H

#include <QFrame>
#include<QDialog>
#include<QVector>
#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QMouseEvent>
class QMultScreen : public QFrame
{
    Q_OBJECT
    typedef struct
    {
        QRect rectScreen;
        QColor colorBackground;
        bool blDiagnosis;

    }StScreen;
public:
    explicit QMultScreen(QWidget *parent = nullptr);
    ~QMultScreen();
    int getScreenNumber(){return m_vtScreen.size();};
     // void paintEvent(QPaintEvent *event);
    int nCurrActiveScreenId;//记录当前屏幕的id
    QVector<StScreen> m_vtScreen;
signals:
    void currentActiveScrrenIdChanged(int);
public slots:
private:

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);


};

#endif // QMULTSCREEN_H

﻿#ifndef BUTTONTOOL_H
#define BUTTONTOOL_H

#include <QWidget>

class QVBoxLayout;
class QHBoxLayout;
class QPushButton;

class ButtonTool : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonTool(QWidget *parent = nullptr);
    ~ButtonTool();

public:
    enum STATE {CUT, LAMP, SAVE,ADD,REDUCE,SWITCH, CLOSE};

    void InitButtons(QStringList buttons = {"CutButton", "LampButton", "SaveButton", "CloseButton"});

    void SetLampToolTip(bool lamp);
    void SetAddZoomRatio(double dbZoomRatio);
    void SetReduceZoomRatio(double dbZoomRatio);

private:
    void InitUi( void );
    void InitProperty( void );

    void SetCutToolTip();
    void SetSaveToolTip();
    void SetCloseToolTip();
    void SetSwitchTip();

protected:

signals:
    void clicked(STATE);

private:
    QVBoxLayout *m_pRootLayout;
    QWidget *m_pRootWidget;
    QHBoxLayout *m_pRootWidgetLayout;
    QList<QPushButton*> m_qButtons;
    QStringList m_qButtonList;

};

#endif // BUTTONTOOL_H

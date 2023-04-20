#ifndef DATABASECONTROL_WATERDROP_H
#define DATABASECONTROL_WATERDROP_H

#include <QtWidgets/QWidget>
#include <QVariantAnimation>

class WaterDrop : public QWidget
{
    Q_OBJECT

public:
    WaterDrop(QWidget *parent = Q_NULLPTR);
    ~WaterDrop();
    void show();
    void move(const QPoint &point);
    void setColor(QColor color);

private:
    void paintEvent(QPaintEvent *event);
public slots:
    void onRaduisChanged(QVariant value);

private:
    QVariantAnimation* m_waterDropAnimation;
    // ˮ�α仯�İ뾶;
    int m_animationRadius;
    // ˮ�ε���ɫ;
    QColor m_waterDropColor;
};
#endif

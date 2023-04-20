#include "WaterDrop.h"
#include <QPainter>

// ˮ�εİ뾶;
#define WATER_DROP_RADIUS 15

WaterDrop::WaterDrop(QWidget *parent)
    : QWidget(parent)
    , m_waterDropAnimation(NULL)
    , m_animationRadius(20)
    , m_waterDropColor(QColor(255, 120, 0, 150))    // Ĭ��Ϊ�ٻ�ɫ;
{
    this->setFixedSize(QSize(WATER_DROP_RADIUS * 2, WATER_DROP_RADIUS *2));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);

    // �ؼ���ʾ��رպ��Զ�ɾ��;
    this->setAttribute(Qt::WA_DeleteOnClose);

    m_waterDropAnimation = new QVariantAnimation(this);
}

WaterDrop::~WaterDrop()
{
}

void WaterDrop::move(const QPoint &point)
{
    // ����Ҫ��������ĵ�ת��ΪԲ�ĵ�����;
    QPoint translatePoint = point - QPoint(WATER_DROP_RADIUS, WATER_DROP_RADIUS);
   // __super::move(translatePoint);
}

void WaterDrop::show()
{
    //__super::show();
    // ͨ�������಻�Ͻ����ػ�;
    m_waterDropAnimation->setStartValue(0);
    m_waterDropAnimation->setEndValue(WATER_DROP_RADIUS);
    m_waterDropAnimation->setDuration(350);

    connect(m_waterDropAnimation, &QVariantAnimation::valueChanged, this, &WaterDrop::onRaduisChanged);
    connect(m_waterDropAnimation, &QVariantAnimation::finished, this, &WaterDrop::close);
    m_waterDropAnimation->start();

}
// ����ˮ�ε���ɫ;
void WaterDrop::setColor(QColor color)
{
    m_waterDropColor = color;
}
// ��������ˮ�ε��Ч��;
void WaterDrop::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_waterDropColor));

    // ˼·�����Ȼ���һ���̶���С��ԲA��Ȼ�����ͬһԲ�ĵ�͸����ԲB��Ȼ��ͨ����������ԲB�İ뾶��0������WATER_DROP_RADIUS�����¸��ǹ̶���ԲA;
    QPainterPath waterDropPath;
    waterDropPath.addEllipse(QPoint(WATER_DROP_RADIUS, WATER_DROP_RADIUS), WATER_DROP_RADIUS, WATER_DROP_RADIUS);
    QPainterPath hidePath;
    hidePath.addEllipse(QPoint(WATER_DROP_RADIUS, WATER_DROP_RADIUS), m_animationRadius, m_animationRadius);

    waterDropPath -= hidePath;
    painter.drawPath(waterDropPath);
}

void WaterDrop::onRaduisChanged(QVariant value)
{
    // ��������ԲB�İ뾶ֵ,���ػ�;
    m_animationRadius = value.toInt();
    update();
}

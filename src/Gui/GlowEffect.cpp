// **************************************************************************
// Tianchi share library for Qt (C++)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵�����ɷ���clicked�źŵ�Label����
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2012.08.23   roywillow   ԭ��
// 2013.04.22   XChinux     �޸�
//
// ==========================================================================
/// @file GlowEffect.cpp �ɷ����QGraphicsEffect
// ==========================================================================
#include "Gui/GlowEffect.h"
#include <QPainter>
#include <QPixmap>

QT_BEGIN_NAMESPACE
// in src/qtbase/src/widgets/effects/qpixmapfilter.cpp
extern Q_DECL_IMPORT void qt_blurImage(QImage &blurImage, qreal radius, 
        bool quality, int transposed = 0);
QT_END_NAMESPACE

TIANCHI_BEGIN_NAMESPACE

QT_USE_NAMESPACE

class GlowEffectPrivate
{
    Q_DECLARE_PUBLIC(GlowEffect)
public:
    explicit GlowEffectPrivate(GlowEffect *qptr);
    ~GlowEffectPrivate();
    GlowEffect *q_ptr;

    int radius;
    QColor color;
};

GlowEffectPrivate::GlowEffectPrivate(GlowEffect *qptr) : q_ptr(qptr)
{
}

GlowEffectPrivate::~GlowEffectPrivate()
{
}

GlowEffect::GlowEffect(QObject *parent) :
    QGraphicsEffect(parent), d_ptr(new GlowEffectPrivate(this)) 
{
    d_ptr->radius = 0;
    d_ptr->color = QColor(255, 255, 255, 255);
}

GlowEffect::~GlowEffect()
{
    delete d_ptr;
}

void GlowEffect::setRadius(int radius)
{
    Q_D(GlowEffect);
    d->radius = radius;
    updateBoundingRect();
    update();
}

void GlowEffect::setGlowColor(const QColor &color)
{
    Q_D(GlowEffect);
    d->color = color;
    update();
}

QRectF GlowEffect::boundingRectFor(const QRectF &sourceRect) const
{
    Q_D(const GlowEffect);
    QRectF tmp(sourceRect);
    tmp.setBottomRight(tmp.bottomRight() 
            + QPointF(d->radius * 2, d->radius * 2));
    return tmp;
}

void GlowEffect::draw(QPainter *painter)
{
    Q_D(GlowEffect);
    if (!d->radius)
    {
        drawSource(painter);
        return;
    }
    QPixmap source = sourcePixmap();
    QImage sourceBlured(source.size() + QSize(d->radius * 2, d->radius * 2), 
            QImage::Format_ARGB32_Premultiplied);
    sourceBlured.fill(0);
    QPainter tmpPainter(&sourceBlured);
    tmpPainter.drawPixmap(d->radius, d->radius, source);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    tmpPainter.fillRect(sourceBlured.rect(), d->color);
    tmpPainter.end();
    QT_PREPEND_NAMESPACE(qt_blurImage(sourceBlured, d->radius, true));
    painter->drawImage(0, 0, sourceBlured);
    painter->drawImage(0, 0, sourceBlured);
    painter->drawPixmap(d->radius, d->radius, source);
}

void GlowEffect::sourceChanged(ChangeFlags flags)
{
    Q_UNUSED(flags)
    updateBoundingRect();
    update();
}

#include "moc_GlowEffect.cpp"

TIANCHI_END_NAMESPACE

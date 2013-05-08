// **************************************************************************
// Tianchi share library for Qt (C++)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：发光效果的QGraphicsEffect
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2012.08.23   roywillow   原创
// 2013.04.22   XChinux     修改
//
// ==========================================================================
/// @file GlowEffect.cpp 可发光的QGraphicsEffect
// ==========================================================================
#include <tianchi/gui/tcgloweffect.h>
#include <QPainter>
#include <QPixmap>

// in src/qtbase/src/widgets/effects/qpixmapfilter.cpp
extern Q_DECL_IMPORT void qt_blurImage(QImage &blurImage, qreal radius, 
        bool quality, int transposed = 0);

class TcGlowEffectPrivate
{
    Q_DECLARE_PUBLIC(TcGlowEffect)
public:
    explicit TcGlowEffectPrivate(TcGlowEffect *qptr);
    ~TcGlowEffectPrivate();
    TcGlowEffect* const q_ptr;

    int radius;
    QColor color;
};

TcGlowEffectPrivate::TcGlowEffectPrivate(TcGlowEffect *qptr) : q_ptr(qptr)
{
}

TcGlowEffectPrivate::~TcGlowEffectPrivate()
{
}

TcGlowEffect::TcGlowEffect(QObject *parent) 
    : QGraphicsEffect(parent), d_ptr(new TcGlowEffectPrivate(this))
{
    d_ptr->radius = 0;
    d_ptr->color = QColor(255, 255, 255, 255);
}

TcGlowEffect::~TcGlowEffect()
{
    delete d_ptr;
}

void TcGlowEffect::setRadius(int radius)
{
    Q_D(TcGlowEffect);
    d->radius = radius;
    updateBoundingRect();
    update();
}

void TcGlowEffect::setGlowColor(const QColor &color)
{
    Q_D(TcGlowEffect);
    d->color = color;
    update();
}

QRectF TcGlowEffect::boundingRectFor(const QRectF &sourceRect) const
{
    Q_D(const TcGlowEffect);
    QRectF tmp(sourceRect);
    tmp.setBottomRight(tmp.bottomRight()
            + QPointF(d->radius * 2, d->radius * 2));
    return tmp;
}

void TcGlowEffect::draw(QPainter *painter)
{
    Q_D(TcGlowEffect);
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
    qt_blurImage(sourceBlured, d->radius, true);
    painter->drawImage(0, 0, sourceBlured);
    painter->drawImage(0, 0, sourceBlured);
    painter->drawPixmap(d->radius, d->radius, source);
}

void TcGlowEffect::sourceChanged(ChangeFlags flags)
{
    Q_UNUSED(flags)
    updateBoundingRect();
    update();
}

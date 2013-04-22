// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：可发出clicked信号的Label部件
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2012.08.23   roywillow   原创
// 2013.04.17   XChinux     修改
//
// ==========================================================================
/// @file GlowEffect.h 发光效果的QGraphicsEffect
// ==========================================================================
/**
 *
 * Usage: 
 *  GlowEffect *effect = new GlowEffect(this);
 *  effect->setRadius(5);
 *  effect->setGlowColor(Qt::blue);
 *  lbl->setGraphicsEffect(effect);
 */
#ifndef TIANCHI_GLOWEFFECT_H
#define TIANCHI_GLOWEFFECT_H

#include <Global.h>
#include <QGraphicsEffect>

TIANCHI_BEGIN_HEADER
TIANCHI_BEGIN_NAMESPACE

class GlowEffectPrivate;

QT_USE_NAMESPACE


class TIANCHI_API GlowEffect : public QGraphicsEffect
{
    Q_OBJECT
public:
    GlowEffect(QObject *parent = 0);
    virtual ~GlowEffect();
    /**
     * set radius
     * @param   int radius
     */
    void setRadius(int radius);
    /**
     * set glow color
     * @param   QColor  color
     */
    void setGlowColor(const QColor &color);
    virtual QRectF boundingRectFor(const QRectF &sourceRect) const;
protected:
    virtual void draw(QPainter *painter);
    virtual void sourceChanged(ChangeFlags flags);
private:
    Q_DISABLE_COPY(GlowEffect)
    Q_DECLARE_PRIVATE(GlowEffect)
    GlowEffectPrivate *d_ptr;

};

TIANCHI_END_NAMESPACE
TIANCHI_END_HEADER

#endif // GLOWEFFECT_H

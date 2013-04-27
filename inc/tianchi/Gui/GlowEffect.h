// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵��������Ч����QGraphicsEffect
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2012.08.23   roywillow   ԭ��
// 2013.04.22   XChinux     �޸�
//
// ==========================================================================
/// @file GlowEffect.h ����Ч����QGraphicsEffect
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

#include <tianchi/Global.h>
#include <QGraphicsEffect>

namespace Tianchi
{
class GlowEffectPrivate;

class TIANCHI_API GlowEffect : public QGraphicsEffect
{
    Q_OBJECT
public:
    GlowEffect(QObject *parent = 0);
    virtual ~GlowEffect();

    /// @brief set radius
    /// @param [in] int radius
    void setRadius(int radius);
    /// @brief set glow color
    /// @param [in] QColor  color
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

}

typedef ::Tianchi::GlowEffect TcGlowEffect;
#endif // GLOWEFFECT_H

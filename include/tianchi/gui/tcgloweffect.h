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
#ifndef TIANCHI_TCGLOWEFFECT_H
#define TIANCHI_TCGLOWEFFECT_H

#include <tianchi/tcglobal.h>
#include <QGraphicsEffect>

class TcGlowEffectPrivate;

/// @brief ����Ч����QGraphicsEffect
/// @par ʾ��:
/// @code
/// GlowEffect *effect = new GlowEffect(this);
/// effect->setRadius(5);
/// effect->setGlowColor(Qt::blue);
/// lbl->setGraphicsEffect(effect);
/// @endcode
/// @see setLogFile
class TIANCHI_API TcGlowEffect : public QGraphicsEffect
{
    Q_OBJECT
public:
    TcGlowEffect(QObject *parent = 0);
    virtual ~TcGlowEffect();

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
    Q_DISABLE_COPY(TcGlowEffect)
    Q_DECLARE_PRIVATE(TcGlowEffect)
    TcGlowEffectPrivate* const d_ptr;
};

#endif // GLOWEFFECT_H

// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵���������Label,���ʱ�Զ�����ַ
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.18   XChinux     ����
//
// ==========================================================================
/// @file MarqueeLabel.h �����Label,���ʱ�Զ�����ַ
// ==========================================================================
#ifndef TIANCHI_MARQUEELABEL_H
#define TIANCHI_MARQUEELABEL_H

#include <tianchi/Global.h>

#include <QLabel>

QT_BEGIN_NAMESPACE
class QEvent;
class QResizeEvent;
QT_END_NAMESPACE

TIANCHI_BEGIN_NAMESPACE

class MarqueeLabelPrivate;

QT_USE_NAMESPACE

/// @brief �������MarqueeLabel,���ʱ�Զ�����ַ
/// @author XChinux XChinux@163.com
/// @date 2013-04-18
class TIANCHI_API MarqueeLabel : public QLabel
{
    Q_OBJECT
public:
    MarqueeLabel(QWidget * parent = 0, Qt::WindowFlags f = 0);
    MarqueeLabel(const QString &text, QWidget *parent = 0, 
            Qt::WindowFlags f = 0);
    virtual ~MarqueeLabel();
public Q_SLOTS:
    void setText(const QString &text);
protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void enterEvent(QEvent *event);
private:
    Q_DISABLE_COPY(MarqueeLabel)
    Q_DECLARE_PRIVATE(MarqueeLabel)
    Q_PRIVATE_SLOT(d_func(), void _q_openLink(const QString &))
    MarqueeLabelPrivate *d_ptr;
};

TIANCHI_END_NAMESPACE

#if 0
class TIANCHI_API TcMarqueeLabel : 
    public TIANCHI_PREPEND_NAMESPACE(MarqueeLabel)
{
    Q_OBJECT
public:
    TcMarqueeLabel(QT_PREPEND_NAMESPACE(QWidget) * parent = 0, 
            QT_PREPEND_NAMESPACE(Qt)::WindowFlags f = 0)
        : TIANCHI_PREPEND_NAMESPACE(MarqueeLabel)(parent, f)
    {
    }

    TcMarqueeLabel(const QT_PREPEND_NAMESPACE(QString) &text, 
            QT_PREPEND_NAMESPACE(QWidget) *parent = 0, 
            QT_PREPEND_NAMESPACE(Qt)::WindowFlags f = 0)
        : TIANCHI_PREPEND_NAMESPACE(MarqueeLabel)(text, parent, f)
    {
    }
};
#endif
typedef TIANCHI_PREPEND_NAMESPACE(MarqueeLabel) TcMarqueeLabel;

#endif

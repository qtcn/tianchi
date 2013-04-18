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
// 2013.04.18   XChinux     ����
//
// ==========================================================================
/// @file MarqueeLabel.h �����Label,���ʱ�Զ�����ַ
// ==========================================================================
#ifndef TIANCHI_MARQUEELABEL_H
#define TIANCHI_MARQUEELABEL_H

#include <Global.h>
#include <QLabel>


TIANCHI_BEGIN_HEADER
TIANCHI_BEGIN_NAMESPACE

QT_USE_NAMESPACE

class QT_PREPEND_NAMESPACE(QResizeEvent);
class MarqueeLabelPrivate;

/// @brief �������MarqueeLabel,���ʱ�Զ�����ַ
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

TIANCHI_END_HEADER
TIANCHI_END_NAMESPACE


#endif

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
// 2013.05.19   XChinux     �޸�ԭ�ƶ�Labelλ�õ�ʵ��Ϊʹ��contentsMargin��ʵ��
//
// ==========================================================================
/// @file MarqueeLabel.h �����Label,���ʱ�Զ�����ַ
// ==========================================================================
#ifndef TIANCHI_TCMARQUEELABEL_H
#define TIANCHI_TCMARQUEELABEL_H

#include <tianchi/tcglobal.h>

#include <QLabel>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class TcMarqueeLabelPrivate;
/// @brief �������MarqueeLabel,���ʱ�Զ�����ַ
/// @author XChinux XChinux@163.com
/// @date 2013-04-18
class TIANCHI_API TcMarqueeLabel : public QLabel
{
    Q_OBJECT
public:
    TcMarqueeLabel(QWidget * parent = 0, Qt::WindowFlags f = 0);
    TcMarqueeLabel(const QString &text, QWidget *parent = 0, 
            Qt::WindowFlags f = 0);
    virtual ~TcMarqueeLabel();
protected:
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void timerEvent(QTimerEvent *event);
    virtual void paintEvent(QPaintEvent *event);
private:
    Q_DISABLE_COPY(TcMarqueeLabel)
    Q_DECLARE_PRIVATE(TcMarqueeLabel)
    Q_PRIVATE_SLOT(d_func(), void _q_openLink(const QString &))
    TcMarqueeLabelPrivate* const d_ptr;
};

#endif

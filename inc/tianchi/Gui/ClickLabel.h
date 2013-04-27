// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵�����ɷ���clicked�źŵ�Label����
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.17   XChinux     ����
//
// ==========================================================================
/// @file ClickLabel.h �ɷ���clicked�źŵ�Label����
// ==========================================================================
#ifndef TIANCHI_CLICKLABEL_H
#define TIANCHI_CLICKLABEL_H

#include <tianchi/Global.h>
#include <QLabel>

TIANCHI_BEGIN_NAMESPACE

class ClickLabelPrivate;

QT_USE_NAMESPACE

/// @brief emit clicked() signal's label while mouse clicked
class TIANCHI_API ClickLabel : public QLabel
{
    Q_OBJECT
public:
    ClickLabel(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ClickLabel(const QString &text, QWidget *parent = 0, 
            Qt::WindowFlags f = 0);
    virtual ~ClickLabel();
Q_SIGNALS:
    /// @brief emit when mouse click label
    void clicked();
protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
private:
    Q_DISABLE_COPY(ClickLabel)
    Q_DECLARE_PRIVATE(ClickLabel)
    ClickLabelPrivate *d_ptr;
};

TIANCHI_END_NAMESPACE

#if 0
class TIANCHI_API TcClickLabel : public TIANCHI_PREPEND_NAMESPACE(ClickLabel)
{
    Q_OBJECT
public:
    TcClickLabel(QT_PREPEND_NAMESPACE(QWidget) *parent = 0, 
            QT_PREPEND_NAMESPACE(Qt)::WindowFlags f = 0)
        : TIANCHI_PREPEND_NAMESPACE(ClickLabel)(parent, f)
    {
    }

    TcClickLabel(const QT_PREPEND_NAMESPACE(QString) &text, 
            QT_PREPEND_NAMESPACE(QWidget) *parent = 0, 
            QT_PREPEND_NAMESPACE(Qt)::WindowFlags f = 0)
        : TIANCHI_PREPEND_NAMESPACE(text, parent, f)
    {
    }
};
#endif
typedef TIANCHI_PREPEND_NAMESPACE(ClickLabel) TcClickLabel;

#endif

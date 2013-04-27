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
// 2013.04.17   XChinux     ����
//
// ==========================================================================
/// @file ClickLabel.h �ɷ���clicked�źŵ�Label����
// ==========================================================================
#include <tianchi/Gui/ClickLabel.h>
#include <QPoint>
#include <QMouseEvent>

namespace Tianchi
{
class ClickLabelPrivate
{
    Q_DECLARE_PUBLIC(ClickLabel)
public:
    explicit ClickLabelPrivate(ClickLabel *qptr);
    ~ClickLabelPrivate();
    QPoint pos;
    ClickLabel *q_ptr;
};

ClickLabelPrivate::ClickLabelPrivate(ClickLabel *qptr) : q_ptr(qptr)
{
}

ClickLabelPrivate::~ClickLabelPrivate()
{
}

ClickLabel::ClickLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f), d_ptr(new ClickLabelPrivate(this))
{
}

ClickLabel::ClickLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f), d_ptr(new ClickLabelPrivate(this))
{
}

ClickLabel::~ClickLabel()
{
    delete d_ptr;
}

void ClickLabel::mousePressEvent(QMouseEvent *e)
{
    QLabel::mousePressEvent(e);

    Q_D(ClickLabel);
    if (e->button() == Qt::LeftButton)
    {
        d->pos = e->pos();
    }
}

void ClickLabel::mouseReleaseEvent(QMouseEvent *e)
{
    QLabel::mouseReleaseEvent(e);

    Q_D(ClickLabel);
    if (e->button() == Qt::LeftButton)
    {
        if (e->pos() == d->pos)
        {
            Q_EMIT clicked();
        }
    }
}
}
#include "moc_ClickLabel.cpp"

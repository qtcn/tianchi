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
/// @file tcclicklabel.cpp �ɷ���clicked�źŵ�Label����
// ==========================================================================
#include <tianchi/gui/tcclicklabel.h>
#include <QPoint>
#include <QMouseEvent>

class TcClickLabelPrivate
{
    Q_DECLARE_PUBLIC(TcClickLabel)
public:
    explicit TcClickLabelPrivate(TcClickLabel *qptr);
    ~TcClickLabelPrivate();
    QPoint pos;
    TcClickLabel* const q_ptr;
};

TcClickLabelPrivate::TcClickLabelPrivate(TcClickLabel *qptr) : q_ptr(qptr)
{
}

TcClickLabelPrivate::~TcClickLabelPrivate()
{
}

TcClickLabel::TcClickLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f), d_ptr(new TcClickLabelPrivate(this))
{
}

TcClickLabel::TcClickLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f), d_ptr(new TcClickLabelPrivate(this))
{
}

TcClickLabel::~TcClickLabel()
{
    delete d_ptr;
}

void TcClickLabel::mousePressEvent(QMouseEvent *e)
{
    QLabel::mousePressEvent(e);

    Q_D(TcClickLabel);
    if (e->button() == Qt::LeftButton)
    {
        d->pos = e->pos();
    }
}

void TcClickLabel::mouseReleaseEvent(QMouseEvent *e)
{
    QLabel::mouseReleaseEvent(e);

    Q_D(TcClickLabel);
    if (e->button() == Qt::LeftButton)
    {
        if (e->pos() == d->pos)
        {
            Q_EMIT clicked();
        }
    }
}

#include "moc_tcclicklabel.cpp"

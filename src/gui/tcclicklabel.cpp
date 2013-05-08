// **************************************************************************
// Tianchi share library for Qt (C++)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：可发出clicked信号的Label部件
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.17   XChinux     建立
//
// ==========================================================================
/// @file ClickLabel.h 可发出clicked信号的Label部件
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

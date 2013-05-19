// **************************************************************************
// Tianchi share library for Qt (C++)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵���������Label, ���ʱ�Զ�����ַ
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.18   XChinux     ����
//
// ==========================================================================
/// @file MarqueeLabel.cpp �����Label, ���ʱ�Զ�����ַ
// ==========================================================================
#include <tianchi/gui/tcmarqueelabel.h>
#include <QUrl>
#include <QResizeEvent>
#include <QtConcurrentRun>
#include <QDesktopServices>

class TcMarqueeLabelPrivate
{
    Q_DECLARE_PUBLIC(TcMarqueeLabel)
public:
    explicit TcMarqueeLabelPrivate(TcMarqueeLabel *qptr);
    ~TcMarqueeLabelPrivate();

    void _q_openLink(const QString &url);
    TcMarqueeLabel* const q_ptr;

    int marqueeMargin;
    int timerId;
    const int interval;
};

TcMarqueeLabelPrivate::TcMarqueeLabelPrivate(TcMarqueeLabel *qptr)
    : q_ptr(qptr), marqueeMargin(0), timerId(0), interval(10)
{
}

TcMarqueeLabelPrivate::~TcMarqueeLabelPrivate()
{
}

void TcMarqueeLabelPrivate::_q_openLink(const QString &url)
{
    QtConcurrent::run(QDesktopServices::openUrl, QUrl(url));
}

TcMarqueeLabel::TcMarqueeLabel(QWidget * parent, Qt::WindowFlags f)
    : QLabel(parent, f), d_ptr(new TcMarqueeLabelPrivate(this))
{
    Q_D(TcMarqueeLabel);
    d->marqueeMargin = width();
    d->timerId = startTimer(d->interval);

    connect(this, SIGNAL(linkActivated(const QString &)),
            this, SLOT(_q_openLink(const QString &)));
}

TcMarqueeLabel::TcMarqueeLabel(const QString &text, QWidget *parent,
        Qt::WindowFlags f )
    : QLabel(text, parent, f), d_ptr(new TcMarqueeLabelPrivate(this))
{
    Q_D(TcMarqueeLabel);
    d->marqueeMargin = width();
    d->timerId = startTimer(d->interval);

    connect(this, SIGNAL(linkActivated(const QString &)),
            this, SLOT(_q_openLink(const QString &)));
}


TcMarqueeLabel::~TcMarqueeLabel()
{
    if (d_ptr->timerId != 0)
    {
        killTimer(d_ptr->timerId);
        d_ptr->timerId = 0;
    }
    delete d_ptr;
}

void TcMarqueeLabel::enterEvent(QEvent *event)
{
    QLabel::enterEvent(event);

    Q_D(TcMarqueeLabel);
    if (d->timerId != 0)
    {
        killTimer(d->timerId);
        d->timerId = 0;
    }
}

void TcMarqueeLabel::leaveEvent(QEvent *event)
{
    QLabel::leaveEvent(event);
    Q_D(TcMarqueeLabel);
    if (d->timerId == 0)
    {
        d->timerId = startTimer(d->interval);
    }
}

void TcMarqueeLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);

    int w = event->size().width();

    Q_D(TcMarqueeLabel);
    if (d->marqueeMargin > w)
    {
        d->marqueeMargin = w;
        update();
    }
}

void TcMarqueeLabel::timerEvent(QTimerEvent *event)
{
    QLabel::timerEvent(event);
    Q_D(TcMarqueeLabel);
    if (d->timerId != 0 && event->timerId() == d->timerId)
    {
        d->marqueeMargin--;
        if (d->marqueeMargin < 0 && -d->marqueeMargin > sizeHint().width())
        {
            d->marqueeMargin = width();
        }
        update();
    }
}

void TcMarqueeLabel::paintEvent(QPaintEvent *event)
{
    Q_D(TcMarqueeLabel);
    setContentsMargins(d->marqueeMargin, 0, 0, 0);
    QLabel::paintEvent(event);
    //setContentsMargins(0, 0, 0, 0);
}

#include "moc_tcmarqueelabel.cpp"

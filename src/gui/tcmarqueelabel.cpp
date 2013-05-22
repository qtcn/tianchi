// **************************************************************************
// Tianchi share library for Qt (C++)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：跑马灯Label, 点击时自动打开网址
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.18   XChinux     建立
// 2013.05.19   XChinux     修改原移动Label位置的实现为使用contentsMargin来实现
// 2013.05.22   XChinux     增加interval active属性及相关信号和槽函数
// ==========================================================================
/// @file MarqueeLabel.cpp 跑马灯Label, 点击时自动打开网址
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
    int interval;
    bool active;
    bool mouseIn;
};

TcMarqueeLabelPrivate::TcMarqueeLabelPrivate(TcMarqueeLabel *qptr)
    : q_ptr(qptr), marqueeMargin(0), timerId(0), interval(10), active(false),
    mouseIn(false)
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

    connect(this, SIGNAL(linkActivated(const QString &)),
            this, SLOT(_q_openLink(const QString &)));
}

TcMarqueeLabel::TcMarqueeLabel(const QString &text, QWidget *parent,
        Qt::WindowFlags f )
    : QLabel(text, parent, f), d_ptr(new TcMarqueeLabelPrivate(this))
{
    Q_D(TcMarqueeLabel);
    d->marqueeMargin = width();

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

int TcMarqueeLabel::interval() const
{
    Q_D(const TcMarqueeLabel);
    return d->interval;
}

// interval必须大于0
void TcMarqueeLabel::setInterval(int interval)
{
    if (interval < 1)
    {
        return;
    }
    Q_D(TcMarqueeLabel);
    if (d->interval != interval)
    {
        d->interval = interval;
        if (d->timerId != 0)
        {
            killTimer(d->timerId);
            d->timerId = startTimer(d->interval);
        }
        Q_EMIT intervalChanged(interval);
    }
}

void TcMarqueeLabel::start()
{
    Q_D(TcMarqueeLabel);
    if (!d->active)
    {
        d->active = true;
        Q_EMIT activeChanged(true);
    }
    if (!d->mouseIn)
    {
        if (d->timerId == 0)
        {
            d->timerId = startTimer(d->interval);
        }
        // 恢复移动,恢复contentsMargins
        setContentsMargins(0, 0, 0, 0);
    }
}

void TcMarqueeLabel::stop()
{
    Q_D(TcMarqueeLabel);
    if (d->active)
    {
        d->active = false;
        Q_EMIT activeChanged(false);
    }
    if (!d->mouseIn)
    {
        if (d->timerId != 0)
        {
            killTimer(d->timerId);
            d->timerId = 0;
        }
        // 停止移动,强制变更contentsMargins,使richText的链接位置正确
        setContentsMargins(d->marqueeMargin, 0, 0, 0);
    }
}

bool TcMarqueeLabel::isActive() const
{
    Q_D(const TcMarqueeLabel);
    return d->active;
}

void TcMarqueeLabel::setActive(bool active)
{
    Q_D(TcMarqueeLabel);
    if (d->active != active)
    {
        if (active)
        {
            start();
        }
        else
        {
            stop();
        }
    }
}

void TcMarqueeLabel::reset()
{
    Q_D(TcMarqueeLabel);
    if (d->timerId != 0)
    {
        killTimer(d->timerId);
        d->timerId = 0;
    }
    if (d->active)
    {
        d->active = false;
        Q_EMIT activeChanged(false);
    }
    d->marqueeMargin = 0;
    setContentsMargins(0, 0, 0, 0);
    update();
}

void TcMarqueeLabel::enterEvent(QEvent *event)
{
    Q_D(TcMarqueeLabel);
    d->mouseIn = true;
    if (d->active)
    {
        if (d->timerId != 0)
        {
            killTimer(d->timerId);
            d->timerId = 0;
        }
        setContentsMargins(d->marqueeMargin, 0, 0, 0);
    }
    QLabel::enterEvent(event);
}

void TcMarqueeLabel::leaveEvent(QEvent *event)
{
    Q_D(TcMarqueeLabel);
    d->mouseIn = false;
    if (d->active)
    {
        if (d->timerId == 0)
        {
            d->timerId = startTimer(d->interval);
        }
        setContentsMargins(0, 0, 0, 0);
    }
    QLabel::leaveEvent(event);
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

    // 如果当前处于静止状态，则无需恢复contentsMargins
    // 这样就解决了richText链接位置显示不正确的问题
    if (d->timerId != 0)
    {
        setContentsMargins(0, 0, 0, 0);
    }
}

#include "moc_tcmarqueelabel.cpp"

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
// 2013.04.18   XChinux     建立
//
// ==========================================================================
/// @file MarqueeLabel.cpp 跑马灯Label,点击时自动打开网址
// ==========================================================================
#include "Gui/MarqueeLabel.h"
#include <QUrl>
#include <QtConcurrentRun>
#include <QResizeEvent>
#include <QDesktopServices>
#include <QPropertyAnimation>

TIANCHI_BEGIN_NAMESPACE

QT_USE_NAMESPACE

class MarqueeLabelPrivate
{
    Q_DECLARE_PUBLIC(MarqueeLabel)
public:
    explicit MarqueeLabelPrivate(MarqueeLabel *qptr);
    ~MarqueeLabelPrivate();

    void _q_openLink(const QString &url);

    QPropertyAnimation *animation;
    MarqueeLabel *q_ptr;
};

MarqueeLabelPrivate::MarqueeLabelPrivate(MarqueeLabel *qptr) : q_ptr(qptr) 
{
    animation = new QPropertyAnimation(q_ptr, "geometry", q_ptr);
    QObject::connect(q_ptr, SIGNAL(linkActivated(const QString &)),
            q_ptr, SLOT(_q_openLink(const QString &)));
}


MarqueeLabelPrivate::~MarqueeLabelPrivate()
{
    delete animation;
}


void MarqueeLabelPrivate::_q_openLink(const QString &url)
{
    QtConcurrent::run(QDesktopServices::openUrl, QUrl(url));
}

MarqueeLabel::MarqueeLabel(QWidget * parent, Qt::WindowFlags f)
    : QLabel(parent, f), d_ptr(new MarqueeLabelPrivate(this))
{
    setOpenExternalLinks(false);
}

MarqueeLabel::MarqueeLabel(const QString &text, QWidget *parent, 
        Qt::WindowFlags f )
    : QLabel(text, parent, f), d_ptr(new MarqueeLabelPrivate(this))
{
    setOpenExternalLinks(false);
}


MarqueeLabel::~MarqueeLabel()
{
    delete d_ptr;
}

void MarqueeLabel::leaveEvent(QEvent *event)
{
    Q_D(MarqueeLabel);
    d->animation->resume();

    QLabel::leaveEvent(event);
}

void MarqueeLabel::enterEvent(QEvent *event)
{
    Q_D(MarqueeLabel);
    d->animation->pause();
    QLabel::enterEvent(event);
}

void MarqueeLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);

    Q_D(MarqueeLabel);
    disconnect(d->animation, SIGNAL(finished()), d->animation, SLOT(start()));
    d->animation->stop();

    int iWidth = sizeHint().width();
    int iParentWidth = parentWidget() ? parentWidget()->width() : 600;
    int iHeight = event->size().height();
    connect(d->animation, SIGNAL(finished()), d->animation, SLOT(start()));

    d->animation->setDuration(10000);
    d->animation->setStartValue(QRect(iParentWidth, 0, iWidth, iHeight));
    d->animation->setEndValue(QRect(-iWidth, 0, iWidth, iHeight));
    d->animation->start();
}


void MarqueeLabel::setText(const QString &text)
{
    Q_D(MarqueeLabel);
    disconnect(d->animation, SIGNAL(finished()), d->animation, SLOT(start()));
    d->animation->stop();
    QLabel::setText(text);

    int iWidth = sizeHint().width();
    int iParentWidth = parentWidget() ? parentWidget()->width() : 600;
    int iHeight = height();
    connect(d->animation, SIGNAL(finished()), d->animation, SLOT(start()));
    d->animation->setDuration(10000);
    d->animation->setStartValue(QRect(iParentWidth, 0, iWidth, iHeight));
    d->animation->setEndValue(QRect(-iWidth, 0, iWidth, iHeight));
    d->animation->start();
}

#include "moc_MarqueeLabel.cpp"

TIANCHI_END_NAMESPACE

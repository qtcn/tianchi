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
#include <QtConcurrentRun>
#include <QResizeEvent>
#include <QDesktopServices>
#include <QPropertyAnimation>

class TcMarqueeLabelPrivate
{
    Q_DECLARE_PUBLIC(TcMarqueeLabel)
public:
    explicit TcMarqueeLabelPrivate(TcMarqueeLabel *qptr);
    ~TcMarqueeLabelPrivate();

    void _q_openLink(const QString &url);

    QPropertyAnimation *animation;
    TcMarqueeLabel* const q_ptr;
};

TcMarqueeLabelPrivate::TcMarqueeLabelPrivate(TcMarqueeLabel *qptr)
    : q_ptr(qptr)
{
    animation = new QPropertyAnimation(q_ptr, "geometry", q_ptr);
    QObject::connect(q_ptr, SIGNAL(linkActivated(const QString &)),
            q_ptr, SLOT(_q_openLink(const QString &)));
}


TcMarqueeLabelPrivate::~TcMarqueeLabelPrivate()
{
    delete animation;
}


void TcMarqueeLabelPrivate::_q_openLink(const QString &url)
{
    QtConcurrent::run(QDesktopServices::openUrl, QUrl(url));
}

TcMarqueeLabel::TcMarqueeLabel(QWidget * parent, Qt::WindowFlags f)
    : QLabel(parent, f), d_ptr(new TcMarqueeLabelPrivate(this))
{
    setOpenExternalLinks(false);
}

TcMarqueeLabel::TcMarqueeLabel(const QString &text, QWidget *parent,
        Qt::WindowFlags f )
    : QLabel(text, parent, f), d_ptr(new TcMarqueeLabelPrivate(this))
{
    setOpenExternalLinks(false);
}


TcMarqueeLabel::~TcMarqueeLabel()
{
    delete d_ptr;
}

void TcMarqueeLabel::leaveEvent(QEvent *event)
{
    Q_D(TcMarqueeLabel);
    d->animation->resume();

    QLabel::leaveEvent(event);
}

void TcMarqueeLabel::enterEvent(QEvent *event)
{
    Q_D(TcMarqueeLabel);
    d->animation->pause();
    QLabel::enterEvent(event);
}

void TcMarqueeLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);

    Q_D(TcMarqueeLabel);
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


void TcMarqueeLabel::setText(const QString &text)
{
    Q_D(TcMarqueeLabel);
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

#include "moc_tcmarqueelabel.cpp"

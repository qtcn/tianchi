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
// 2013.05.19   XChinux     �޸�ԭ�ƶ�Labelλ�õ�ʵ��Ϊʹ��contentsMargin��ʵ��
// 2013.05.22   XChinux     ����interval active���Լ�����źźͲۺ���
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
    int interval;
    bool active;
    bool mouseIn;
    TcMarqueeLabel::Direction direction;
};

TcMarqueeLabelPrivate::TcMarqueeLabelPrivate(TcMarqueeLabel *qptr)
    : q_ptr(qptr), marqueeMargin(0), timerId(0), interval(10), active(false),
    mouseIn(false), direction(TcMarqueeLabel::RightToLeft)
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
    d->marqueeMargin = 0;

    connect(this, SIGNAL(linkActivated(const QString &)),
            this, SLOT(_q_openLink(const QString &)));
}

TcMarqueeLabel::TcMarqueeLabel(const QString &text, QWidget *parent,
        Qt::WindowFlags f )
    : QLabel(text, parent, f), d_ptr(new TcMarqueeLabelPrivate(this))
{
    Q_D(TcMarqueeLabel);
    d->marqueeMargin = 0;

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

// interval�������0
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
    bool bActiveChanged = false;
    if (!d->active)
    {
        d->active = true;
        bActiveChanged = true;
    }
    if (!d->mouseIn)
    {
        if (d->timerId == 0)
        {
            d->timerId = startTimer(d->interval);
        }
        // �ָ��ƶ�,�ָ�contentsMargins
        setContentsMargins(0, 0, 0, 0);
    }

    if (bActiveChanged)
    {
        Q_EMIT activeChanged(d->active);
    }
}

void TcMarqueeLabel::stop()
{
    Q_D(TcMarqueeLabel);
    bool bActiveChanged = false;
    if (d->active)
    {
        d->active = false;
        bActiveChanged = true;
    }
    if (!d->mouseIn)
    {
        if (d->timerId != 0)
        {
            killTimer(d->timerId);
            d->timerId = 0;
        }
        // ֹͣ�ƶ�,ǿ�Ʊ��contentsMargins,ʹrichText������λ����ȷ
        switch (d->direction)
        {
            case RightToLeft:
                setContentsMargins(d->marqueeMargin, 0, 0, 0);
                break;
            case BottomToTop:
            default:
                setContentsMargins(0, d->marqueeMargin, 0, 0);
        }
    }

    if (bActiveChanged)
    {
        Q_EMIT activeChanged(d->active);
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
    if (d->active == active)
    {
        return;
    }
    if (active)
    {
        start();
    }
    else
    {
        stop();
    }
}

TcMarqueeLabel::Direction TcMarqueeLabel::direction() const
{
    Q_D(const TcMarqueeLabel);
    return d->direction;
}

void TcMarqueeLabel::setDirection(TcMarqueeLabel::Direction direction)
{
    Q_D(TcMarqueeLabel);
    if (d->direction == direction)
    {
        return;
    }
    d->direction = direction;
    switch (direction)
    {
        case RightToLeft:
            setAlignment(Qt::AlignLeft 
                    | (alignment() & Qt::AlignVertical_Mask));
            break;
        case BottomToTop:
        default:
            setAlignment(Qt::AlignTop
                    | (alignment() & Qt::AlignHorizontal_Mask));
    }
    d->marqueeMargin = 0;
    setContentsMargins(0, 0, 0, 0);
    update();

    Q_EMIT directionChanged(direction);
}

void TcMarqueeLabel::setAlignment(Qt::Alignment align)
{
    Q_D(TcMarqueeLabel);
    switch (d->direction)
    {
        case RightToLeft:
            QLabel::setAlignment(Qt::AlignLeft 
                    | (align & Qt::AlignVertical_Mask));
            break;
        case BottomToTop:
        default:
            QLabel::setAlignment(Qt::AlignTop
                    | (align & Qt::AlignHorizontal_Mask));
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
    bool bActiveChanged = false;
    if (d->active)
    {
        d->active = false;
        bActiveChanged = true;
    }
    d->marqueeMargin = 0;
    setContentsMargins(0, 0, 0, 0);
    update();

    if (bActiveChanged)
    {
        Q_EMIT activeChanged(d->active);
    }
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
        switch (d->direction)
        {
            case RightToLeft:
                setContentsMargins(d->marqueeMargin, 0, 0, 0);
                break;
            case BottomToTop:
            default:
                setContentsMargins(0, d->marqueeMargin, 0, 0);
        }
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

    Q_D(TcMarqueeLabel);
    int w;
    switch (d->direction)
    {
        case RightToLeft:
            w = event->size().width();
            break;
        case BottomToTop:
        default:
            w = event->size().height();
    }
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
        int w, w2;
        switch (d->direction)
        {
            case RightToLeft:
                w = sizeHint().width();
                w2 = width();
                break;
            case BottomToTop:
            default:
                w = sizeHint().height();
                w2 = height();
        }
        if (d->marqueeMargin < 0 && -d->marqueeMargin > w)
        {
            d->marqueeMargin = w2;
        }
        update();
    }
}

void TcMarqueeLabel::paintEvent(QPaintEvent *event)
{
    Q_D(TcMarqueeLabel);
    switch (d->direction)
    {
        case RightToLeft:
            setContentsMargins(d->marqueeMargin, 0, 0, 0);
            break;
        case BottomToTop:
        default:
            setContentsMargins(0, d->marqueeMargin, 0, 0);
    }
    QLabel::paintEvent(event);

    // �����ǰ���ھ�ֹ״̬��������ָ�contentsMargins
    // �����ͽ����richText����λ����ʾ����ȷ������
    if (d->timerId != 0)
    {
        setContentsMargins(0, 0, 0, 0);
    }
}

#include "moc_tcmarqueelabel.cpp"

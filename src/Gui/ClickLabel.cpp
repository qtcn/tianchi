#include <Gui/ClickLabel.h>
#include <QPoint>
#include <QMouseEvent>

TIANCHI_BEGIN_NAMESPACE

QT_USE_NAMESPACE

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
            emit clicked();
        }
    }
}

#include "moc_ClickLabel.cpp"

TIANCHI_END_NAMESPACE

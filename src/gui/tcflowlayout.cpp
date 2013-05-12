// **************************************************************************
// Tianchi share library for Qt (C++)
// ��ع���Դ���
// ��Ȩ���� (C) Qt Project����ع���Դ��⿪����
// ��ȨЭ�飺LGPL
// **************************************************************************
// �ĵ�˵�����ɷ���clicked�źŵ�Label����
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.21   XChinux     �޸���Qt examples&demos���flowlayoutʾ��
//
// ==========================================================================
/// @file FlowLayout.cpp ��ʽ����FlowLayout
// ==========================================================================
#include <tianchi/gui/tcflowlayout.h>
#include <QStyle>
#include <QWidget>

class TcFlowLayoutPrivate
{
    Q_DECLARE_PUBLIC(TcFlowLayout)
public:
    explicit TcFlowLayoutPrivate(TcFlowLayout *qptr);
    ~TcFlowLayoutPrivate();

    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

    QList<QLayoutItem *> itemList;
    int m_hSpace;
    int m_vSpace;

    TcFlowLayout* const q_ptr;
};

TcFlowLayoutPrivate::TcFlowLayoutPrivate(TcFlowLayout *qptr) : q_ptr(qptr)
{
}

TcFlowLayoutPrivate::~TcFlowLayoutPrivate()
{
}

TcFlowLayout::TcFlowLayout(QWidget *parent, int margin, int hSpacing,
        int vSpacing)
    : QLayout(parent), d_ptr(new TcFlowLayoutPrivate(this))
{
    d_ptr->m_hSpace = hSpacing;
    d_ptr->m_vSpace = vSpacing;

    setContentsMargins(margin, margin, margin, margin);
}

TcFlowLayout::TcFlowLayout(int margin, int hSpacing, int vSpacing)
    : d_ptr(new TcFlowLayoutPrivate(this))
{
    d_ptr->m_hSpace = hSpacing;
    d_ptr->m_vSpace = vSpacing;

    setContentsMargins(margin, margin, margin, margin);
}

TcFlowLayout::~TcFlowLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;

    delete d_ptr;
}

void TcFlowLayout::addItem(QLayoutItem *item)
{
    Q_D(TcFlowLayout);
    d->itemList.append(item);
}

int TcFlowLayout::horizontalSpacing() const
{
    Q_D(const TcFlowLayout);

    if (d->m_hSpace >= 0)
    {
        return d->m_hSpace;
    }
    else
    {
        return d->smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
    }
}

int TcFlowLayout::verticalSpacing() const
{
    Q_D(const TcFlowLayout);

    if (d->m_vSpace >= 0)
    {
        return d->m_vSpace;
    }
    else
    {
        return d->smartSpacing(QStyle::PM_LayoutVerticalSpacing);
    }
}

int TcFlowLayout::count() const
{
    Q_D(const TcFlowLayout);
    return d->itemList.size();
}

QLayoutItem *TcFlowLayout::itemAt(int index) const
{
    Q_D(const TcFlowLayout);
    return d->itemList.value(index);
}

QLayoutItem *TcFlowLayout::takeAt(int index)
{
    Q_D(TcFlowLayout);
    if (index >= 0 && index < d->itemList.size())
        return d->itemList.takeAt(index);
    else
        return 0;
}

Qt::Orientations TcFlowLayout::expandingDirections() const
{
    return 0;
}

bool TcFlowLayout::hasHeightForWidth() const
{
    return true;
}

int TcFlowLayout::heightForWidth(int width) const
{
    Q_D(const TcFlowLayout);
    int height = d->doLayout(QRect(0, 0, width, 0), true);
    return height;
}

void TcFlowLayout::setGeometry(const QRect &rect)
{
    Q_D(TcFlowLayout);
    QLayout::setGeometry(rect);
    d->doLayout(rect, false);
}

QSize TcFlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize TcFlowLayout::minimumSize() const
{
    Q_D(const TcFlowLayout);
    QSize size;
    QLayoutItem *item;
    foreach (item, d->itemList)
        size = size.expandedTo(item->minimumSize());
    size += QSize(2*margin(), 2*margin());
    return size;
}

int TcFlowLayoutPrivate::doLayout(const QRect &rect, bool testOnly) const
{
    Q_Q(const TcFlowLayout);
    int left, top, right, bottom;
    q->getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;
    QLayoutItem *item;
    foreach (item, itemList)
    {
        QWidget *wid = item->widget();
        int spaceX = q->horizontalSpacing();
        if (spaceX == -1)
            spaceX = wid->style()->layoutSpacing(
                    QSizePolicy::PushButton, QSizePolicy::PushButton,
                    Qt::Horizontal);
        int spaceY = q->verticalSpacing();
        if (spaceY == -1)
            spaceY = wid->style()->layoutSpacing(
                    QSizePolicy::PushButton, QSizePolicy::PushButton,
                    Qt::Vertical);
        int nextX = x + item->sizeHint().width() + spaceX;
        if (nextX - spaceX > effectiveRect.right() && lineHeight > 0)
        {
            x = effectiveRect.x();
            y = y + lineHeight + spaceY;
            nextX = x + item->sizeHint().width() + spaceX;
            lineHeight = 0;
        }
        if (!testOnly)
            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));
        x = nextX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
    }
    return y + lineHeight - rect.y() + bottom;
}

int TcFlowLayoutPrivate::smartSpacing(QStyle::PixelMetric pm) const
{
    Q_Q(const TcFlowLayout);
    QObject *parent = q->parent();
    if (!parent)
    {
        return -1;
    }
    else if (parent->isWidgetType())
    {
        QWidget *pw = static_cast<QWidget *>(parent);
        return pw->style()->pixelMetric(pm, 0, pw);
    }
    else
    {
        return static_cast<QLayout *>(parent)->spacing();
    }
}

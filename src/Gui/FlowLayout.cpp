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
// 2013.04.21   XChinux     建立
//
// ==========================================================================
/// @file FlowLayout.cpp 流式布局FlowLayout
// ==========================================================================
#include <tianchi/Gui/FlowLayout.h>
#include <QStyle>
#include <QWidget>

TIANCHI_BEGIN_NAMESPACE

QT_USE_NAMESPACE

class FlowLayoutPrivate
{
    Q_DECLARE_PUBLIC(FlowLayout)
public:
    explicit FlowLayoutPrivate(FlowLayout *qptr);
    ~FlowLayoutPrivate();

    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

    QList<QLayoutItem *> itemList;
    int m_hSpace;
    int m_vSpace;

    FlowLayout *q_ptr;
};

FlowLayoutPrivate::FlowLayoutPrivate(FlowLayout *qptr) : q_ptr(qptr)
{
}

FlowLayoutPrivate::~FlowLayoutPrivate()
{
}

FlowLayout::FlowLayout(QWidget *parent, int margin, int hSpacing,
        int vSpacing)
    : QLayout(parent), d_ptr(new FlowLayoutPrivate(this))
{
    d_ptr->m_hSpace = hSpacing;
    d_ptr->m_vSpace = vSpacing;

    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::FlowLayout(int margin, int hSpacing, int vSpacing)
    : d_ptr(new FlowLayoutPrivate(this))
{
    d_ptr->m_hSpace = hSpacing;
    d_ptr->m_vSpace = vSpacing;

    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::~FlowLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;

    delete d_ptr;
}

void FlowLayout::addItem(QLayoutItem *item)
{
    Q_D(FlowLayout);
    d->itemList.append(item);
}

int FlowLayout::horizontalSpacing() const
{
    Q_D(const FlowLayout);

    if (d->m_hSpace >= 0)
    {
        return d->m_hSpace;
    }
    else
    {
        return d->smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
    }
}

int FlowLayout::verticalSpacing() const
{
    Q_D(const FlowLayout);

    if (d->m_vSpace >= 0)
    {
        return d->m_vSpace;
    }
    else
    {
        return d->smartSpacing(QStyle::PM_LayoutVerticalSpacing);
    }
}

int FlowLayout::count() const
{
    Q_D(const FlowLayout);
    return d->itemList.size();
}

QLayoutItem *FlowLayout::itemAt(int index) const
{
    Q_D(const FlowLayout);
    return d->itemList.value(index);
}

QLayoutItem *FlowLayout::takeAt(int index)
{
    Q_D(FlowLayout);
    if (index >= 0 && index < d->itemList.size())
        return d->itemList.takeAt(index);
    else
        return 0;
}

Qt::Orientations FlowLayout::expandingDirections() const
{
    return 0;
}

bool FlowLayout::hasHeightForWidth() const
{
    return true;
}

int FlowLayout::heightForWidth(int width) const
{
    Q_D(const FlowLayout);
    int height = d->doLayout(QRect(0, 0, width, 0), true);
    return height;
}

void FlowLayout::setGeometry(const QRect &rect)
{
    Q_D(FlowLayout);
    QLayout::setGeometry(rect);
    d->doLayout(rect, false);
}

QSize FlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize FlowLayout::minimumSize() const
{
    Q_D(const FlowLayout);
    QSize size;
    QLayoutItem *item;
    foreach (item, d->itemList)
        size = size.expandedTo(item->minimumSize());
    size += QSize(2*margin(), 2*margin());
    return size;
}

int FlowLayoutPrivate::doLayout(const QRect &rect, bool testOnly) const
{
    Q_Q(const FlowLayout);
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

int FlowLayoutPrivate::smartSpacing(QStyle::PixelMetric pm) const
{
    Q_Q(const FlowLayout);
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

TIANCHI_END_NAMESPACE

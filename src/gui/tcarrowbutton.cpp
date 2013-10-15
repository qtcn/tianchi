// 文档说明：实现中间带有三角箭头的button
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.10.14   younghz     建立
// 2013.10.15   XChinux     格式化代码
// ==========================================================================
/// @file tcarrowbutton.cpp 实现中间带有三角箭头的button
// ==========================================================================

#include <tianchi/gui/tcarrowbutton.h>

#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QEvent>
#include <QApplication>

static const int MaxNum = 3;
static const int Spacing = 1;

class TcArrowButtonPrivate
{
    Q_DECLARE_PUBLIC(TcArrowButton)
public:

    explicit TcArrowButtonPrivate(TcArrowButton *qptr);
    ~TcArrowButtonPrivate();

    TcArrowButton* const q_ptr;

    int num;
    Qt::ArrowType arrowType;

    ////////////////////////////////////////
    void drawButtonLabel(QPainter *p);
    /// @brief 绘制箭头
    void drawArrow(QPainter *, const QRect &, Qt::ArrowType) const;
    QRect labelRect() const;
    /// @brief 箭头大小
    QSize arrowSize(Qt::ArrowType, const QSize &boundingSize ) const;
};

TcArrowButtonPrivate::TcArrowButtonPrivate(TcArrowButton *qptr) : q_ptr(qptr)
{
}

TcArrowButtonPrivate::~TcArrowButtonPrivate()
{
}


//绘制button风格的一些参数
static QStyleOptionButton styleOpt(const TcArrowButton* btn)
{
    QStyleOptionButton option;
    option.init(btn);
    //一个normal button
    option.features = QStyleOptionButton::None;
    if (btn->isFlat())
    {
        option.features |= QStyleOptionButton::Flat;
    }
    if (btn->menu())
    {
        option.features |= QStyleOptionButton::HasMenu;
    }
    if (btn->autoDefault() || btn->isDefault())
    {
        option.features |= QStyleOptionButton::AutoDefaultButton;
    }
    if (btn->isDefault())
    {
        option.features |= QStyleOptionButton::DefaultButton;
    }
    if (btn->isDown())
    {
        option.state |= QStyle::State_Sunken;
    }
    if (!btn->isFlat() && !btn->isDown())
    {
        option.state |= QStyle::State_Raised;
    }

    return option;
}

TcArrowButton::TcArrowButton(int num, Qt::ArrowType arrowType, 
        QWidget *parent)
    : QPushButton(parent), d_ptr(new TcArrowButtonPrivate(this))
{
    //按钮中箭头的数量在1~3之间
    d_ptr->num = qBound(1, num, MaxNum);
    d_ptr->arrowType = arrowType;

    setAutoRepeat(true);
    setAutoDefault(false);

    //设置箭头的policy
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

//析构函数
TcArrowButton::~TcArrowButton()
{
    delete d_ptr;
}

QRect TcArrowButtonPrivate::labelRect() const//{{{
{
    const int m = 2;


    Q_Q(const TcArrowButton);
    //将一个和平台相关的按钮尺寸赋予r
    QRect r = q->rect();
    r.setRect(r.x() + m, r.y() + m, r.width() - 2 * m, r.height() - 2 * m);

    //按钮按下时
    if (q->isDown())
    {
        QStyleOptionButton option = styleOpt(q);
        const int ph = q->style()->pixelMetric(
            QStyle::PM_ButtonShiftHorizontal, &option, q);
        const int pv = q->style()->pixelMetric(
            QStyle::PM_ButtonShiftVertical, &option, q);

        r.translate(ph, pv);
    }

    return r;
}//}}}

void TcArrowButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    QPainter painter(this);

    Q_D(TcArrowButton);
    d->drawButtonLabel(&painter);
}

void TcArrowButtonPrivate::drawButtonLabel(QPainter *painter)//{{{
{
    //判断是否是up/downArrow
    const bool isVertical = this->arrowType == Qt::UpArrow ||
        this->arrowType == Qt::DownArrow;

    //配置按钮的大小
    const QRect r = this->labelRect();
    QSize boundingSize = this->labelRect().size();
    if (isVertical)
    {
        boundingSize.transpose();//将width和hight的值交换
    }

    //配置按钮上箭头的大小
    const int w = (boundingSize.width() - (MaxNum - 1) * Spacing) / MaxNum;

    QSize arrow = this->arrowSize(Qt::RightArrow, 
            QSize(w, boundingSize.height()));

    if (isVertical)
    {
        arrow.transpose();
    }

    QRect contentsSize;
    if (this->arrowType == Qt::LeftArrow || this->arrowType == Qt::RightArrow)
    {
        contentsSize.setWidth(this->num * arrow.width()
            + (this->num - 1 ) * Spacing);
        contentsSize.setHeight(arrow.height());
    }
    else
    {
        contentsSize.setWidth(arrow.width());
        contentsSize.setHeight(this->num * arrow.height()
            + (this->num - 1 ) * Spacing);
    }

    QRect arrowRect(contentsSize);
    arrowRect.moveCenter(r.center());
    arrowRect.setSize(arrow);

    painter->save();
    for (int i = 0; i < this->num; i++)
    {
        this->drawArrow(painter, arrowRect, this->arrowType);

        int dx = 0;
        int dy = 0;

        if (isVertical)
        {
            dy = arrow.height() + Spacing;
        }
        else
        {
            dx = arrow.width() + Spacing;
        }

        arrowRect.translate(dx, dy);
    }
    painter->restore();

    Q_Q(TcArrowButton);
    if (q->hasFocus())
    {
        QStyleOptionFocusRect option;
        option.init(q);
        option.backgroundColor = q->palette().color(QPalette::Window);

        q->style()->drawPrimitive(QStyle::PE_FrameFocusRect,
            &option, painter, q);
    }
}//}}}

void TcArrowButtonPrivate::drawArrow(QPainter *painter,
    const QRect &r, Qt::ArrowType arrowType1) const//{{{
{
    QPolygon pa(3);

    switch (arrowType1)
    {
        case Qt::UpArrow:
            pa.setPoint(0, r.bottomLeft());
            pa.setPoint(1, r.bottomRight());
            pa.setPoint(2, r.center().x(), r.top());
            break;
        case Qt::DownArrow:
            pa.setPoint(0, r.topLeft());
            pa.setPoint(1, r.topRight());
            pa.setPoint(2, r.center().x(), r.bottom());
            break;
        case Qt::RightArrow:
            pa.setPoint(0, r.topLeft());
            pa.setPoint(1, r.bottomLeft());
            pa.setPoint(2, r.right(), r.center().y());
            break;
        case Qt::LeftArrow:
            pa.setPoint(0, r.topRight());
            pa.setPoint(1, r.bottomRight());
            pa.setPoint(2, r.left(), r.center().y());
            break;
        default:
            break;
    }

    Q_Q(const TcArrowButton);
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);
    painter->setBrush(q->palette().brush(QPalette::ButtonText));
    painter->drawPolygon(pa);

    painter->restore();
}//}}}

QSize TcArrowButtonPrivate::arrowSize(Qt::ArrowType arrowType1,
    const QSize &boundingSize) const//{{{
{
    QSize bs = boundingSize;
    if (arrowType1 == Qt::UpArrow || arrowType1 == Qt::DownArrow)
    {
        bs.transpose();
    }

    const int MinLen = 2;
    const QSize sz = bs.expandedTo(QSize(MinLen, 2 * MinLen - 1)); // minimum

    int w = sz.width();
    int h = 2 * w - 1;

    if (h > sz.height())
    {
        h = sz.height();
        w = (h + 1) / 2;
    }

    QSize arrSize(w, h);
    if (arrowType1 == Qt::UpArrow || arrowType1 == Qt::DownArrow)
    {
        arrSize.transpose();
    }

    return arrSize;
}//}}}


#include "moc_tcarrowbutton.cpp"

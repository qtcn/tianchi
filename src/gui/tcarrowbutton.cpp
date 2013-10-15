// �ĵ�˵����ʵ���м�������Ǽ�ͷ��button
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.10.14   younghz     ����
// 2013.10.15   XChinux     ��ʽ������
// ==========================================================================
/// @file tcarrowbutton.cpp ʵ���м�������Ǽ�ͷ��button
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
    /// @brief ���Ƽ�ͷ
    void drawArrow(QPainter *, const QRect &, Qt::ArrowType) const;
    QRect labelRect() const;
    /// @brief ��ͷ��С
    QSize arrowSize(Qt::ArrowType, const QSize &boundingSize ) const;
};

TcArrowButtonPrivate::TcArrowButtonPrivate(TcArrowButton *qptr) : q_ptr(qptr)
{
}

TcArrowButtonPrivate::~TcArrowButtonPrivate()
{
}


//����button����һЩ����
static QStyleOptionButton styleOpt(const TcArrowButton* btn)
{
    QStyleOptionButton option;
    option.init(btn);
    //һ��normal button
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
    //��ť�м�ͷ��������1~3֮��
    d_ptr->num = qBound(1, num, MaxNum);
    d_ptr->arrowType = arrowType;

    setAutoRepeat(true);
    setAutoDefault(false);

    //���ü�ͷ��policy
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

//��������
TcArrowButton::~TcArrowButton()
{
    delete d_ptr;
}

QRect TcArrowButtonPrivate::labelRect() const//{{{
{
    const int m = 2;


    Q_Q(const TcArrowButton);
    //��һ����ƽ̨��صİ�ť�ߴ縳��r
    QRect r = q->rect();
    r.setRect(r.x() + m, r.y() + m, r.width() - 2 * m, r.height() - 2 * m);

    //��ť����ʱ
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
    //�ж��Ƿ���up/downArrow
    const bool isVertical = this->arrowType == Qt::UpArrow ||
        this->arrowType == Qt::DownArrow;

    //���ð�ť�Ĵ�С
    const QRect r = this->labelRect();
    QSize boundingSize = this->labelRect().size();
    if (isVertical)
    {
        boundingSize.transpose();//��width��hight��ֵ����
    }

    //���ð�ť�ϼ�ͷ�Ĵ�С
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

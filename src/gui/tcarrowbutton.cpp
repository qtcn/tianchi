// 文档说明：实现中间带有三角箭头的button
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.10.14  younghz
// ==========================================================================
/// @file tcarrowbutton.cpp 实现中间带有三角箭头的button
// ==========================================================================

#include <tianchi/gui/tcarrowbutton.h>

#include <qpainter.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qevent.h>
#include <qapplication.h>

static const int MaxNum = 3;
static const int Spacing = 1;

class TcArrowButton::PrivateData
{
public:
    int num;
    Qt::ArrowType arrowType;
};

//绘制button风格的一些参数
static QStyleOptionButton styleOpt( const TcArrowButton* btn )
{
    QStyleOptionButton option;
    option.init( btn );
    //一个normal button
    option.features = QStyleOptionButton::None;
    if ( btn->isFlat() )
        option.features |= QStyleOptionButton::Flat;
    if ( btn->menu() )
        option.features |= QStyleOptionButton::HasMenu;
    if ( btn->autoDefault() || btn->isDefault() )
        option.features |= QStyleOptionButton::AutoDefaultButton;
    if ( btn->isDefault() )
        option.features |= QStyleOptionButton::DefaultButton;
    if ( btn->isDown() )
        option.state |= QStyle::State_Sunken;
    if ( !btn->isFlat() && !btn->isDown() )
        option.state |= QStyle::State_Raised;

    return option;
}

TcArrowButton::TcArrowButton( int num,
        Qt::ArrowType arrowType, QWidget *parent ):
    QPushButton( parent )
{
    d_data = new PrivateData;
    //按钮中箭头的数量在1~3之间
    d_data->num = qBound( 1, num, MaxNum );
    d_data->arrowType = arrowType;

    setAutoRepeat( true );
    setAutoDefault( false );

    //设置箭头的policy
    setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );

}

//析构函数
TcArrowButton::~TcArrowButton()
{
    delete d_data;
    d_data = NULL;
}

QRect TcArrowButton::labelRect() const
{
    const int m = 2;

    //将一个和平台相关的按钮尺寸赋予r
    QRect r = rect();
    r.setRect( r.x() + m, r.y() + m,
        r.width() - 2 * m, r.height() - 2 * m );

    //按钮按下时
    if ( isDown() )
    {
        QStyleOptionButton option = styleOpt( this );
        const int ph = style()->pixelMetric(
            QStyle::PM_ButtonShiftHorizontal, &option, this );
        const int pv = style()->pixelMetric(
            QStyle::PM_ButtonShiftVertical, &option, this );

        r.translate( ph, pv );
    }

    return r;
}

void TcArrowButton::paintEvent( QPaintEvent *event )
{
    QPushButton::paintEvent( event );
    QPainter painter( this );
    drawButtonLabel( &painter );
}

void TcArrowButton::drawButtonLabel( QPainter *painter )
{
    //判断是否是up/downArrow
    const bool isVertical = d_data->arrowType == Qt::UpArrow ||
        d_data->arrowType == Qt::DownArrow;

    //配置按钮的大小
    const QRect r = labelRect();
    QSize boundingSize = labelRect().size();
    if ( isVertical )
        boundingSize.transpose();//将width和hight的值交换

    //配置按钮上箭头的大小
    const int w =
        ( boundingSize.width() - ( MaxNum - 1 ) * Spacing ) / MaxNum;

    QSize arrow = arrowSize( Qt::RightArrow,
        QSize( w, boundingSize.height() ) );

    if ( isVertical )
        arrow.transpose();

    QRect contentsSize;
    if ( d_data->arrowType == Qt::LeftArrow || d_data->arrowType == Qt::RightArrow )
    {
        contentsSize.setWidth( d_data->num * arrow.width()
            + ( d_data->num - 1 ) * Spacing );
        contentsSize.setHeight( arrow.height() );
    }
    else
    {
        contentsSize.setWidth( arrow.width() );
        contentsSize.setHeight( d_data->num * arrow.height()
            + ( d_data->num - 1 ) * Spacing );
    }

    QRect arrowRect( contentsSize );
    arrowRect.moveCenter( r.center() );
    arrowRect.setSize( arrow );

    painter->save();
    for ( int i = 0; i < d_data->num; i++ )
    {
        drawArrow( painter, arrowRect, d_data->arrowType );

        int dx = 0;
        int dy = 0;

        if ( isVertical )
            dy = arrow.height() + Spacing;
        else
            dx = arrow.width() + Spacing;

        arrowRect.translate( dx, dy );
    }
    painter->restore();

    if ( hasFocus() )
    {
        QStyleOptionFocusRect option;
        option.init( this );
        option.backgroundColor = palette().color( QPalette::Window );

        style()->drawPrimitive( QStyle::PE_FrameFocusRect,
            &option, painter, this );
    }
}

void TcArrowButton::drawArrow( QPainter *painter,
    const QRect &r, Qt::ArrowType arrowType ) const
{
    QPolygon pa( 3 );

    switch ( arrowType )
    {
        case Qt::UpArrow:
            pa.setPoint( 0, r.bottomLeft() );
            pa.setPoint( 1, r.bottomRight() );
            pa.setPoint( 2, r.center().x(), r.top() );
            break;
        case Qt::DownArrow:
            pa.setPoint( 0, r.topLeft() );
            pa.setPoint( 1, r.topRight() );
            pa.setPoint( 2, r.center().x(), r.bottom() );
            break;
        case Qt::RightArrow:
            pa.setPoint( 0, r.topLeft() );
            pa.setPoint( 1, r.bottomLeft() );
            pa.setPoint( 2, r.right(), r.center().y() );
            break;
        case Qt::LeftArrow:
            pa.setPoint( 0, r.topRight() );
            pa.setPoint( 1, r.bottomRight() );
            pa.setPoint( 2, r.left(), r.center().y() );
            break;
        default:
            break;
    }

    painter->save();

    painter->setRenderHint( QPainter::Antialiasing, true );
    painter->setPen( Qt::NoPen );
    painter->setBrush( palette().brush( QPalette::ButtonText ) );
    painter->drawPolygon( pa );

    painter->restore();
}

QSize TcArrowButton::arrowSize( Qt::ArrowType arrowType,
    const QSize &boundingSize ) const
{
    QSize bs = boundingSize;
    if ( arrowType == Qt::UpArrow || arrowType == Qt::DownArrow )
        bs.transpose();

    const int MinLen = 2;
    const QSize sz = bs.expandedTo(
        QSize( MinLen, 2 * MinLen - 1 ) ); // minimum

    int w = sz.width();
    int h = 2 * w - 1;

    if ( h > sz.height() )
    {
        h = sz.height();
        w = ( h + 1 ) / 2;
    }

    QSize arrSize( w, h );
    if ( arrowType == Qt::UpArrow || arrowType == Qt::DownArrow )
        arrSize.transpose();

    return arrSize;
}



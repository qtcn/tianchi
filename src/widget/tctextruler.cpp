#include <QPainter>
#include <QMouseEvent>

#include <tianchi/widget/tctextruler.h>

static const QColor BgStartColor(221,221,221);
static const QColor BgStopColor(230,230,230);
static const QColor TextColor = QColor(89,89,89);
static const QColor MarkColor(165,165,165);
static const QColor IndicatorBrush(30,30,30);
static const int MaxHeight = 30;
static const int LongMarkLength = 7;
static const int ShortMarkLength = 5;
static const int TextMarkSpace = 1;
static const int IndicatorLength = 10;
static const int Top = 0;

class TcTextRuler::PrivateData {
public:
    PrivateData(): textWidth(0), column(0), mousePressed(false){}
    float textWidth;
    int column;
    bool mousePressed;
};

TcTextRuler::TcTextRuler(QWidget *parent) :
    QWidget(parent)
{
    mData = new PrivateData();
    mData->textWidth = fontMetrics().width('A') * 2;
    setFixedHeight(MaxHeight);
    setMouseTracking(true);
}

TcTextRuler::~TcTextRuler()
{
    delete mData;
}

void TcTextRuler::setTextWidth(float textWidth)
{
    mData->textWidth = textWidth;
    update();
}

void TcTextRuler::setColumn(int column)
{
    mData->column = column;
    update();
}

void TcTextRuler::enterEvent(QEvent *)
{
    setCursor(Qt::IBeamCursor);
}

void TcTextRuler::leaveEvent(QEvent *)
{
    unsetCursor();
}

void TcTextRuler::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawBg(&painter);
    drawMarks(&painter);
    drawIndicator(&painter);
}

void TcTextRuler::mousePressEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton) {
        mData->mousePressed = true;
        mData->column = (int)e->pos().x() / mData->textWidth;
        update();
    }
}

void TcTextRuler::mouseMoveEvent(QMouseEvent *e)
{
    if (mData->mousePressed) {
        int xPos = e->pos().x();
        if (xPos < 0 || xPos > width()) {
           return;
        }
        setColumn(xPos/mData->textWidth);
    }
}

void TcTextRuler::mouseReleaseEvent(QMouseEvent *)
{
    mData->mousePressed = false;
}

void TcTextRuler::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QLinearGradient bgGradient(rect().topLeft(), rect().bottomLeft());
    bgGradient.setColorAt(0.0, BgStartColor);
    bgGradient.setColorAt(1.0, BgStopColor);
    painter->setBrush(bgGradient);

    painter->drawRect(rect());
    painter->restore();
}

void TcTextRuler::drawMarks(QPainter *painter)
{
    painter->save();
    qreal initX = 0;
    int counter = 0;
    while (initX < width()) {
        if (counter++%5 == 0) {
            // draw long mark
            painter->setPen(MarkColor);
            QPointF upperPoint(initX, height() - LongMarkLength);
            QPointF bottomPoint(initX, height());
            painter->drawLine(upperPoint, bottomPoint);

            // draw text
            painter->setPen(TextColor);
            const QString text = tr("%1").arg(counter - 1);
            int textWidth = fontMetrics().width(text);
            QPointF textPoint(initX - textWidth/2, upperPoint.y() - TextMarkSpace);
            if (textPoint.x() <= 0) {
                textPoint.setX(0);
            } else if (textPoint.x() + textWidth > width()) {
                textPoint.setX(width() - textWidth);
            }
            painter->drawText(textPoint, text);
        } else {
            // draw short mark
            painter->setPen(MarkColor);
            QPointF upperPoint(initX, height() - ShortMarkLength);
            QPointF bottomPoint(initX, height());
            painter->drawLine(upperPoint, bottomPoint);
        }

        // increment initX
        initX += mData->textWidth;
    }
    painter->restore();
}

void TcTextRuler::drawIndicator(QPainter *painter)
{
    painter->setPen(IndicatorBrush);
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setBrush(IndicatorBrush);
    int pivotXPos = mData->column * mData->textWidth;
    QPointF topLeft(pivotXPos - IndicatorLength/2, Top);
    QPointF topRight(pivotXPos + IndicatorLength/2, Top);
    QPointF bottomPoint(pivotXPos, IndicatorLength);
    QPolygonF polygon;
    polygon.push_back(topLeft);
    polygon.push_back(topRight);
    polygon.push_back(bottomPoint);
    painter->drawPolygon(polygon);
    painter->restore();

#if 0
    painter->save();
    QPointF lineEndPot(pivotXPos, height());
    painter->drawLine(bottomPoint, lineEndPot);
    painter->restore();
#endif
}

#ifndef TCTEXTRULER_H
#define TCTEXTRULER_H

#include <QWidget>
#include <tianchi/tcglobal.h>

class QPainter;
class QMouseEvent;
class TIANCHI_API TcTextRuler : public QWidget
{
    Q_OBJECT
public:
    explicit TcTextRuler(QWidget *parent = 0);
    ~TcTextRuler();

public slots:
    void setTextWidth(float textWidth);
    void setColumn(int column);

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    void drawBg(QPainter* painter);
    void drawMarks(QPainter* painter);
    void drawIndicator(QPainter* painter);

    class PrivateData;
    PrivateData* mData;
};

#endif // TCTEXTRULER_H

// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：QTreeWidget 控件扩展
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.10.18   kimtaikee   建立
// ==========================================================================
/// @file tctextruler.h
// ==========================================================================

#ifndef TCTEXTRULER_H
#define TCTEXTRULER_H

#include <tianchi/tcglobal.h>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QPainter;
class QMouseEvent;
QT_END_NAMESPACE

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

// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：可发出clicked信号的Label部件
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.17   XChinux     建立
//
// ==========================================================================
/// @file tcclicklabel.h 可发出clicked信号的Label部件
// ==========================================================================
#ifndef TIANCHI_TCCLICKLABEL_H
#define TIANCHI_TCCLICKLABEL_H

#include <tianchi/tcglobal.h>
#include <QLabel>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class TcClickLabelPrivate;

/// @brief emit clicked() signal's label while mouse clicked
class TIANCHI_API TcClickLabel : public QLabel
{
    Q_OBJECT
public:
    TcClickLabel(QWidget *parent = 0, Qt::WindowFlags f = 0);
    TcClickLabel(const QString &text, QWidget *parent = 0, 
            Qt::WindowFlags f = 0);
    virtual ~TcClickLabel();
Q_SIGNALS:
    /// @brief emit when mouse click label
    void clicked();
protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
private:
    Q_DISABLE_COPY(TcClickLabel)
    Q_DECLARE_PRIVATE(TcClickLabel)
    TcClickLabelPrivate* const d_ptr;
};

#endif

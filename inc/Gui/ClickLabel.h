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
/// @file ClickLabel.h 可发出clicked信号的Label部件
// ==========================================================================
#ifndef TIANCHI_CLICKLABEL_H
#define TIANCHI_CLICKLABEL_H

#include <Global.h>
#include <QLabel>

TIANCHI_BEGIN_HEADER

TIANCHI_BEGIN_NAMESPACE

class ClickLabelPrivate;

QT_USE_NAMESPACE

/// @brief emit clicked() signal's label while mouse clicked
class TIANCHI_API ClickLabel : public QLabel
{
    Q_OBJECT
public:
    ClickLabel(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ClickLabel(const QString &text, QWidget *parent = 0, 
            Qt::WindowFlags f = 0);
    virtual ~ClickLabel();
Q_SIGNALS:
    /// @brief emit when mouse click label
    void clicked();
protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
private:
    Q_DISABLE_COPY(ClickLabel)
    Q_DECLARE_PRIVATE(ClickLabel)
    ClickLabelPrivate *d_ptr;
};

TIANCHI_END_NAMESPACE

TIANCHI_END_HEADER

#endif

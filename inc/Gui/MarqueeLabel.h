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
// 2013.04.18   XChinux     建立
//
// ==========================================================================
/// @file MarqueeLabel.h 跑马灯Label,点击时自动打开网址
// ==========================================================================
#ifndef TIANCHI_MARQUEELABEL_H
#define TIANCHI_MARQUEELABEL_H

#include <Global.h>
#include <QLabel>

QT_BEGIN_NAMESPACE
class QEvent;
class QResizeEvent;
QT_END_NAMESPACE

TIANCHI_BEGIN_HEADER
TIANCHI_BEGIN_NAMESPACE

class MarqueeLabelPrivate;

QT_USE_NAMESPACE

/// @brief 跑马灯类MarqueeLabel,点击时自动打开网址
class TIANCHI_API MarqueeLabel : public QLabel
{
    Q_OBJECT
public:
    MarqueeLabel(QWidget * parent = 0, Qt::WindowFlags f = 0);
    MarqueeLabel(const QString &text, QWidget *parent = 0, 
            Qt::WindowFlags f = 0);
    virtual ~MarqueeLabel();
public Q_SLOTS:
    void setText(const QString &text);
protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void enterEvent(QEvent *event);
private:
    Q_DISABLE_COPY(MarqueeLabel)
    Q_DECLARE_PRIVATE(MarqueeLabel)
    Q_PRIVATE_SLOT(d_func(), void _q_openLink(const QString &))
    MarqueeLabelPrivate *d_ptr;

};

TIANCHI_END_HEADER
TIANCHI_END_NAMESPACE


#endif

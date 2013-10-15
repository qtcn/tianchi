// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：截屏对话框
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.10.11   XChinux     建立
//
// ==========================================================================
/// @file tcscreencutdialog.h 截屏对话框
// ==========================================================================
#ifndef TIANCHI_TCSCREENCUTDIALOG_H
#define TIANCHI_TCSCREENCUTDIALOG_H

#include <tianchi/tcglobal.h>
#include <QPixmap>
#include <QDialog>

class QMouseEvent;
class QPaintEvent;
class TcScreenCutDialogPrivate;

/// @brief  screen cut dialog
/// @code
///     TcScreenCutDialog dlg;
///     dlg.exec();
///     QPixmap image = dlg.getPixmap();
/// @endcode
class TIANCHI_API TcScreenCutDialog : public QDialog
{
    Q_OBJECT
public:
    TcScreenCutDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
    virtual ~TcScreenCutDialog();
    /// @brief  get cutted screen pixmap
    QPixmap getPixmap() const;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
private:
    Q_DISABLE_COPY(TcScreenCutDialog)
    Q_DECLARE_PRIVATE(TcScreenCutDialog)
    TcScreenCutDialogPrivate* const d_ptr;
};

#endif

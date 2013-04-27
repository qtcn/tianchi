// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：流式布局FlowLayout
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.21   XChinux     建立
//
// ==========================================================================
/// @file FlowLayout.h 流式布局FlowLayout
// ==========================================================================
#ifndef TIANCHI_FLOWLAYOUT_H
#define TIANCHI_FLOWLAYOUT_H

#include <tianchi/Global.h>
#include <QLayout>

namespace Tianchi
{
class FlowLayoutPrivate;

/// @brief 流式布局FlowLayout
class TIANCHI_API FlowLayout : public QLayout
{
public:
    FlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1,
            int vSpacing = -1);
    FlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);
    virtual ~FlowLayout();

    void addItem(QLayoutItem *item);
    int horizontalSpacing() const;
    int verticalSpacing() const;
    Qt::Orientations expandingDirections() const;
    bool hasHeightForWidth() const;
    int heightForWidth(int) const;
    int count() const;
    QLayoutItem *itemAt(int index) const;
    QSize minimumSize() const;
    void setGeometry(const QRect &rect);
    QSize sizeHint() const;
    QLayoutItem *takeAt(int index);

private:
    Q_DISABLE_COPY(FlowLayout)
    Q_DECLARE_PRIVATE(FlowLayout)
    FlowLayoutPrivate *d_ptr;
};
}

typedef ::Tianchi::FlowLayout TcFlowLayout;

#endif

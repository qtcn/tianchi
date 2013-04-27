// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：允许为空的日期选择控件
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.10   圣域天子    建立
//
// ==========================================================================
/// @file DateEdit.h 允许为空的日期选择控件
// ==========================================================================
#ifndef TIANCHI_DATEEDIT_H
#define TIANCHI_DATEEDIT_H

#include <tianchi/Global.h>

#include <QComboBox>
#include <QCalendarWidget>

namespace Tianchi
{
/// @brief 可以输入或显示为空的日期选择控件
/// @author 圣域天子 Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API DateEdit : public QComboBox
{
    Q_OBJECT

    Q_PROPERTY(QDate date READ date WRITE setDate RESET unsetDate)

private Q_SLOTS:
    void calendarClicked(QDate);

private:
    QCalendarWidget *m_calendar;

protected:
    void focusInEvent(QFocusEvent *e);
    void mousePressEvent(QMouseEvent *e);

public:
    DateEdit(QWidget *parent = 0);
    virtual ~DateEdit();

    QDate date() const;
    void setDate(QDate value);
    void unsetDate();

    inline void setDate(QDateTime value) { setDate(value.date()); }
};

}

typedef ::Tianchi::DateEdit TcDateEdit;

#endif

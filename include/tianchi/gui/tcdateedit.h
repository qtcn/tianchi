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
#ifndef TIANCHI_TCDATEEDIT_H
#define TIANCHI_TCDATEEDIT_H

#include <tianchi/tcglobal.h>

#include <QComboBox>
#include <QCalendarWidget>

/// @brief 可以输入或显示为空的日期选择控件
/// @author 圣域天子 Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API TcDateEdit : public QComboBox
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
    TcDateEdit(QWidget *parent = 0);
    virtual ~TcDateEdit();

    QDate date() const;
    void setDate(QDate value);
    void unsetDate();

    inline void setDate(QDateTime value) { setDate(value.date()); }
};

#endif

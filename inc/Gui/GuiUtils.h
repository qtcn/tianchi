// ********************************************************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// ********************************************************************************************************************
// 文档说明：GUI相关常用单元
// ====================================================================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------------------------------------------------
// 2013.04.15   圣域天子    建立
//
// ====================================================================================================================
/// @file GuiUtils.h GUI相关常用单元
#ifndef TIANCHI_GUIUTILS_H
#define TIANCHI_GUIUTILS_H

#include "Global.h"

#if defined(QT_GUI_LIB)
#include <QWidget>
#include <QCursor>

TIANCHI_BEGIN_NAMESPACE

QT_USE_NAMESPACE

/// @brief 光标形态变化类的根类，一般不直接使用
/// @see class CursorWait
/// @see class CursorBusy
class TIANCHI_API CursorCustom
{
protected:
    CursorCustom(QWidget* parent, Qt::CursorShape shape)
    {
        m_parent = parent;
        m_cursor = m_parent->cursor();
        m_parent->setCursor(QCursor(shape));
    }
    virtual ~CursorCustom()
    {
        m_parent->setCursor(m_cursor);
    }
    QWidget* m_parent;
    QCursor  m_cursor;
};

/// @brief 等待光标的设置和自动恢复处理类
/// @par 示例:
/// @code
/// void myForm::onClick()
/// {
///     CursorWait wait; // 自动变成等待光标
///
///     ... 处理代码 ...
///
/// } // 退出块时，wait 被释放，使光标自动恢复为原先的光标形态
/// @endcode
/// @see class CursorBusy
class TIANCHI_API CursorWait : public CursorCustom
{
public:
    CursorWait(QWidget* parent)
        : CursorCustom(parent, Qt::WaitCursor)
    {
    }
};

/// @brief 后台忙光标的设置和自动恢复处理类
/// @par 示例:
/// @code
/// void myForm::onClick()
/// {
///     CursorBusy busy; // 自动变成后台忙光标
///
///     ... 处理代码 ...
///
///
/// } // 退出块时，busy 被释放，使光标自动恢复为原先的光标形态
/// @endcode
/// @see class CursorBusy
class TIANCHI_API CursorBusy : public CursorCustom
{
public:
    CursorBusy(QWidget* parent)
        : CursorCustom(parent, Qt::BusyCursor)
    {
    }
};

TIANCHI_END_NAMESPACE

#endif // QT_GUI_LIB

#endif // TIANCHI_GUIUTILS_H

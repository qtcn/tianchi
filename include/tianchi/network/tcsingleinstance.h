// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：应用程序单实例类
//          使用了 QLocalSocket / QLocalServer 方式实现，为本地多实例应用间通
//          讯保留扩展的可能。
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.19   圣域天子    建立
//
// ==========================================================================
// @file SingleInstance.h 应用程序单实例类
// ==========================================================================
#ifndef TIANCHI_TCSINGLEINSTANCE_H
#define TIANCHI_TCSINGLEINSTANCE_H

#include <tianchi/tcglobal.h>

#include <QLocalSocket>
#include <QLocalServer>

/// @brief 应用程序单实例类
/// @par 示例:
/// @code
/// #include "Network/SingleInstance.h"
///
/// int main(int argc, char *argv[])
/// {
///     QApplication app(argc, argv);
///
///     TcSingleInstance si(app, "myApp");
///
///     if ( si.first() )
///     {
///         // 首次运行
///     }else
///     {
///         // 已存在其它实例
///     }
///     ...
/// }
/// @endcode
/// @author 圣域天子 Jonix@qtcn.org
/// @date 2013-04-19
class TIANCHI_API TcSingleInstance
{
public:
    /// @brief 初始化方法
    /// @param [in] instanceName 识别是否重复开启的实例名称
    TcSingleInstance(QString instanceName)
    {
        init(0, instanceName);
    }
    /// @brief 初始化方法
    /// @param [in] parent app对象
    /// @param [in] instanceName 识别是否重复开启的实例名称
    TcSingleInstance(QObject* parent, QString instanceName)
    {
        init(parent, instanceName);
    }
    /// @brief 是否首次运行的实例
    /// @return true: 首次运行的实例
    bool first() const { return m_first; }

protected:
    bool            m_first;        ///< 首次运行实例
    QString         m_instanceName; ///< 实例名称
    QLocalSocket    m_localSocket;  ///< 外访 socket 句柄
    QLocalServer*   m_localServer;  ///< 受访 socket 句柄

private:
    void init(QObject* parent, QString instanceName);
};

#endif // TIANCHI_SINGLEINSTANCE_H

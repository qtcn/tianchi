// ********************************************************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// ********************************************************************************************************************
// 文档说明：应用程序单实例类
//          使用了 QLocalSocket / QLocalServer 方式实现，为本地多实例应用间通讯保留扩展的可能。
// ====================================================================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------------------------------------------------
// 2013.04.19   圣域天子    建立
//
// ====================================================================================================================
/// @file SingleInstance.h 应用程序单实例类
// ====================================================================================================================
#ifndef TIANCHI_SINGLEINSTANCE_H
#define TIANCHI_SINGLEINSTANCE_H

#include "Global.h"

#include <QLocalSocket>
#include <QLocalServer>

TIANCHI_BEGIN_NAMESPACE

/// @brief 应用程序单实例类
/// @par 示例:
/// @code
/// #include "Network/SingleInstance.h"
///
/// int main(int argc, char *argv[])
/// {
///     QApplication app(argc, argv);
///
///     TIANCHI::SingleInstance si(app, "myApp");
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
class TIANCHI_API SingleInstance
{
public:
    SingleInstance(QString instanceName)
    {
        init(0, instanceName);
    }
    SingleInstance(QObject* parent, QString instanceName)
    {
        init(parent, instanceName);
    }
    bool first() const { return m_first; }

protected:
    bool            m_first;
    QString         m_instanceName;
    QLocalSocket    m_localSocket;
    QLocalServer*   m_localServer;

    void init(QObject* parent, QString instanceName);
};

TIANCHI_END_NAMESPACE

#endif // TIANCHI_SINGLEINSTANCE_H

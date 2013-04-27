// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：与操作系统相关
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.10   圣域天子    建立
//
// ==========================================================================
/// @file OS.h 与操作系统相关
#ifndef TIANCHI_OS_H
#define TIANCHI_OS_H

#include <tianchi/Global.h>
#include <QString>

namespace Tianchi
{
/// @brief 与操作系统相关的操作类
/// @author 圣域天子 Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API OS
{
public:
    /// @brief 取操作系统名称，仅支持 Windows
    static QString name();

    /// @brief 取操作系统的语言，仅支持 Windows
    static QString language();

    /// @brief Windows 域用户登录，仅支持 Windows
    /// @param [in] Domain Windows 域名或本机机器名
    /// @param [in] UserID 域用户名或本机用户名
    /// @param [in] Password 用户密码
    /// @return true 登录成功
    /// @return false 登录失败
    static bool login(const QString& Domain, const QString& UserID, 
            const QString& Password);
};
}

typedef ::Tianchi::OS TcOS;

#endif // TIANCHI_OS_H

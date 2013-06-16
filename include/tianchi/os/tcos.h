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
// 2013.06.16   XChinux     修改name()方法,增加读取Linux发行版内容
// ==========================================================================
/// @file OS.h 与操作系统相关
#ifndef TIANCHI_TCOS_H
#define TIANCHI_TCOS_H

#include <tianchi/tcglobal.h>
#include <QString>

/// @brief 与操作系统相关的操作类
/// @author 圣域天子 Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API TcOS
{
public:
    /// @brief 取操作系统名称，支持Windows和Linux
    /// @note Windows从注册表中获取,Linux从依次从/etc下的os-release 
    ///       lsb-release, *-release文件获取
    static QString name();

    /// @brief 取操作系统的语言，仅支持 Windows
    /// @note 仅支持 Windows
    static QString language();

    /// @brief Windows 域用户登录，仅支持 Windows
    /// @param [in] Domain Windows 域名或本机机器名
    /// @param [in] UserID 域用户名或本机用户名
    /// @param [in] Password 用户密码
    /// @return true 登录成功
    /// @return false 登录失败
    /// @note 仅支持 Windows
    static bool login(const QString& Domain, const QString& UserID, 
            const QString& Password);
};

#endif // TIANCHI_TCOS_H

// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：SQL Server 相关应用
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.18   XChinux    建立
//
// ==========================================================================
/// @file MSSQL.h SQL Server 相关应用
#ifndef TIANCHI_TCMSSQL_H
#define TIANCHI_TCMSSQL_H

#include <tianchi/tcglobal.h>
#include <QStringList>

/// @brief 读取 ODBC 驱动和版本信息
/// @author XChinux XChinux@163.com
/// @date 2013-04-18
class TIANCHI_API TcMSSQL
{
public:
    /// @brief 读取 ODBC 驱动和版本信息
    /// @date 2013-04-18
    /// @return  以 / 分隔版本号和驱动名称:<br>
    ///     10.00/SQL Server Native Client 10.0<br>
    ///     09.00/SQL Native Client<br>
    ///     03.50/SQL Server<br>
    static QStringList availableODBCDrivers();
};

#endif

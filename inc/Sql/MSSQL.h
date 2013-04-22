// ********************************************************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// ********************************************************************************************************************
// 文档说明：SQL Server 相关应用
// ====================================================================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------------------------------------------------
// 2013.04.18   XChinux    建立
//
// ====================================================================================================================
/// @file MSSQL.h SQL Server 相关应用
#ifndef TIANCHI_SQL_MSSQL_H
#define TIANCHI_SQL_MSSQL_H

#include <Global.h>
#include <QStringList>

TIANCHI_BEGIN_HEADER
TIANCHI_BEGIN_NAMESPACE

QT_USE_NAMESPACE


/// @brief 读取 ODBC 驱动和版本信息
/// @author XChinux XChinux@163.com
/// @date 2013-04-18
class TIANCHI_API MSSQL
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

TIANCHI_END_HEADER
TIANCHI_END_NAMESPACE

#endif

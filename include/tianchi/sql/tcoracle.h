// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：Oracle 相关应用
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.06.04   XChinux     建立
// 2013.06.04   XChinux     增加ODBCDSN()函数
//
// ==========================================================================
/// @file MSSQL.h SQL Server 相关应用
#ifndef TIANCHI_TCORACLE_H
#define TIANCHI_TCORACLE_H

#include <tianchi/tcglobal.h>
#include <QStringList>

/// @brief 读取 ODBC 驱动和版本信息
/// @author XChinux XChinux@163.com
/// @date 2013-04-18
class TIANCHI_API TcOracle
{
public:
    /// @brief 读取 ODBC 驱动和版本信息
    /// @date 2013-04-18
    /// @return  以 / 分隔版本号和驱动名称:<br>
    ///     11.2.0.3/Oracle in instantclient_11_2<br>
    ///     11.2.0.2/Oracle in XE<br>
    static QStringList availableODBCDrivers();
    /// @brief  构造ODBC DSN字符串
    /// @date 2013-06-04
    /// @param  driver  可用ODBC驱动名称
    /// @param  tns     TNS Service Name
    /// @param  user    连接用户名
    /// @param  pass    连接密码
    /// @return 返回DSN字符串
    static QString ODBCDSN(const QString &driver,
            const QString &tns,
            const QString &user = QString(),
            const QString &pass = QString());
};

#endif

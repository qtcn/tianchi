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
// 2021.12.18   XChinux     add Qt6 support
// ==========================================================================
/// @file tcoracle.cpp SQL Server 相关应用

#include <tianchi/sql/tcoracle.h>
#include <tianchi/file/tcfile.h>
#include <QSettings>
#include <algorithm>
/**
 * get Oracle ODBC drivers name and version, every item such as:
 * -------------------------------------------------------------
 *     10.00/SQL Server Native Client 10.0
 *     09.00/SQL Native Client
 *     03.50/SQL Server
 * -------------------------------------------------------------
 * @author  XChinux<XChinux@163.com>
 * @final   2013-04-18
 * @return  QStringList         desc sorted ver/drivername lists
 */
QStringList TcOracle::availableODBCDrivers()
{
    QStringList slDrivers;
#ifdef Q_OS_WIN
    QSettings  sts("HKEY_LOCAL_MACHINE\\SOFTWARE\\ODBC\\ODBCINST.INI"
            "\\ODBC Drivers", QSettings::NativeFormat);
    QStringList slKeys = sts.allKeys();

    QStringList slKeys2;
    for (int i = slKeys.size() - 1; i > -1; i--)
    {
        if (slKeys[i].left(7) == "Oracle ")
        {
            slKeys2 << slKeys[i];
        }
    }
    slKeys2.removeDuplicates();
    QListIterator<QString> it(slKeys2);

    while (it.hasNext())
    {
        QString strV = it.next();
        if (sts.value(strV).toString() == "Installed")
        {
            QSettings sts2("HKEY_LOCAL_MACHINE\\SOFTWARE\\ODBC\\ODBCINST.INI\\"
                + strV, QSettings::NativeFormat);
            strV.prepend(TcFile::fileVersion(
                        sts2.value("Driver").toString()) + "/");
            slDrivers << strV;
        }
    }
    std::sort(slDrivers.begin(), slDrivers.end(), std::greater<QString>());
#endif
    return slDrivers;
}

/// @brief  构造ODBC DSN字符串
/// @author XChinux<XChinux@163.com>
/// @final  2013-06-04
/// @param  driver  可用ODBC驱动名称
/// @param  tns     TNS Service Name
/// @param  user    连接用户名
/// @param  pass    连接密码
/// @return 返回DSN字符串
QString TcOracle::ODBCDSN(const QString &driver,
            const QString &tns,
            const QString &user /*= QString() */,
            const QString &pass /*= QString()*/)
{
    QString strDSN = QString("DRIVER={%1};DBQ=%2;SERVER=%2")
        .arg(driver).arg(tns);
    if (!user.isEmpty())
    {
        strDSN += ";UID=" + user;
    }
    if (!pass.isEmpty())
    {
        strDSN += ";PWD=" + pass;
    }
    return strDSN;
}

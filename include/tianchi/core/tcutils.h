// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：常用功能函数
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.10   圣域天子    建立
// 2013.09.25   XChinux     增加getLocationFromIP()函数
// 2021.12.18   XChinux     增加Qt6支持
// ==========================================================================
// @file tctils.h 常用功能函数
// ==========================================================================
#ifndef TIANCHI_TCUTILS_H
#define TIANCHI_TCUTILS_H

#include <tianchi/tcglobal.h>

#ifdef QT_WIDGETS_LIB
    #include <QMessageBox>
#endif

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#else
#include <QTextCodec>
#endif
#include <QVariant>

#include <QDateTime>

#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QComboBox>

#include <QThread>

/// @brief 操作模式的标识常量
struct TcOperMode
{
const static int Append = 1; ///< 添加或新建
const static int Change = 2; ///< 修改
const static int Delete = 4; ///< 删除

const static int CopyCell   = 301; ///< 复制一个单元格
const static int CopyCells  = 302; ///< 复制多个单元格
const static int CopyColumn = 303; ///< 复制列
const static int CopyLine   = 304; ///< 复制行
const static int CopyTable  = 305; ///< 复制一张表，默认表示含标题
};

/// @brief 常用小功能综合函数集
/// @author 圣域天子 Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API TcUtils
{
public:
    /// @brief 把 key=value 结构的文本转换为 map 结构
    static QHash<QString, QString> StringToMap(const QString& mapStrings);
    /// @brief 把 key=value 结构的文本转换为 map 结构
    static QHash<QString, QString> StringToMap(const QStringList& mapStrings);

    /// @brief 类型转字符代码
    static char typeFrom(QVariant::Type type);
    /// @brief 类型转字符代码
    static char typeFrom(const QVariant& v)
    {
        return typeFrom(v.type());
    }

    const static qint64 JULIAN_DAY = 2415019;
    /// @brief 转换字符串为日期时间
    static QDateTime toDateTime(const QString& text);
    /// @brief 转换数据为日期时间
    static QDateTime toDateTime(double timeDouble);

    /// @brief 返回18位身位证的最后一位校验码
    static char getIDCardVerifyCode(const QByteArray& id);

    /// @brief 取编译日期和时间，调用处的代码必须重新编译
    static QDateTime complieDateTime(const QString& complieDate, const QString& complieTime);

    static QByteArray addField(const QString& key, const QVariant& value);
    static QHash<QString, QByteArray> byFields(const QByteArray& fieldBytes);

    /// @brief  使用qqwry.dat库从IP地址获取所在地区名称
    /// @param  ip_addr         IP地址
    /// @param  qqwry_dat_file  qqwry.dat文件路径
    /// @return                 返回IP地址所在地区名称
    static QString getLocationFromIP(const QString &ip_addr, 
            const QString &qqwry_dat_file);
};

#endif // TIANCHI_UTILS_H

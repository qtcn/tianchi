// ********************************************************************************************************************
// Tianchi share library for Qt (C++)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// ********************************************************************************************************************
// 文档说明：常用功能函数
// ====================================================================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------------------------------------------------
// 2013.04.10   圣域天子    建立
//
// ====================================================================================================================
/// @file Utils.h 常用功能函数
// ====================================================================================================================
#ifndef TIANCHI_UTILS_H
#define TIANCHI_UTILS_H

#include "Global.h"

#ifdef QT_WIDGETS_LIB
    #include <QMessageBox>
#endif

#include <QTextCodec>
#include <QVariant>

#include <QDateTime>

#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QComboBox>

#include <QThread>


TIANCHI_BEGIN_NAMESPACE

/// @brief 操作模式的标识常量
namespace OperMode
{
const int Append = 1; ///< 添加或新建
const int Change = 2; ///< 修改
const int Delete = 4; ///< 删除
};

/// @brief 常用小功能综合函数集
class TIANCHI_API Utils
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

    /// @brief 返回当前时间字符串：yyyy-MM-dd HH:mm:ss.zzz
    static QString YYYY_MM_DD_HH_MM_SS_ZZZ();
    /// @brief 返回当前时间字符串：yyyy-MM-dd HH:mm:ss
    static QString YYYY_MM_DD_HH_MM_SS();
    /// @brief 转换字符串为日期时间
    static QDateTime toDateTime(const QString& text);

    /// @brief 返回18位身位证的最后一位校验码
    static char getIDCardVerifyCode(const QByteArray& id);

    /// @brief 取编译日期和时间，调用处的代码必须重新编译
    static QDateTime complieDateTime(const QString& complieDate, const QString& time);

};

TIANCHI_END_NAMESPACE


#endif // TIANCHI_UTILS_H

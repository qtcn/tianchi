// ********************************************************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// ********************************************************************************************************************
// 文档说明：字符串功能增强与扩展
// ====================================================================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------------------------------------------------
// 2013.04.16   圣域天子    建立
//
// ====================================================================================================================
/// @file String.h 字符串功能增强与扩展
#ifndef TIANCHI_STRING_H
#define TIANCHI_STRING_H

#include "Global.h"

#include <QString>
#include <QStringList>

TIANCHI_BEGIN_NAMESPACE

/// @brief 字符串功能增强与扩展
/// @author 圣域天子 Jonix@qtcn.org
/// @date 2013-04-16
class TIANCHI_API String
{
public:
    String();

    /// @brief 截取字符串的首部分
    /// @param [in,out] str 被截取的字符串
    /// @param [in] split 字符串的分隔符
    /// @return 截取出的字符串
    /// @note 分隔符将被丢弃，不含分隔符时截取整个字符串，被截取的字符串将被修改
    static QByteArray   first(QByteArray& str, const QByteArray& split="\t");

    /// @brief 在字符串序列中查到一个字符串
    /// @note 未来可能会删除
    /// @see findOf
    static int find(const QStringList& ss, const QString& s);

    /// @brief 在字符串序列中查到一个字符串
    /// @note 未来可能会删除
    /// @see find
    static int findOf(const QStringList& list, const QString& key);

    /// @brief 判断一个字符串的合部工部分是否存在于一个字符串队列中
    /// @param [in] findText 需要查找的子字符串
    /// @param [in] filters 被查找的字符串队列
    /// @return true 存在
    /// @return false 不存在
    static bool filter(const QString& findText, const QStringList& filters);

    /// @brief 从一个字符串队列中返回指定索引行的字符串
    /// @param [in] strings 字符串队列，以"\n"作为分隔
    /// @param [in] index 需要返回的索引行，从 0 开始
    /// @return 索引行的字符串，索引值越界时返回空字符串
    static QString getTextByIndex(const char* strings, int index);

    /// @brief 分割中文全名中的姓氏、名字和英文名
    static int  splitHumanName(QString full, QString& sur, QString& real, QString& english);

};

/// @brief 字符串集功能增强与扩展
/// @author 圣域天子 Jonix@qtcn.org
/// @date 2013-04-16
class TIANCHI_API StringList : public QStringList
{
public:
    /// @brief 装入一个文本文件的全部内容
    /// @param [in] fileName 路径文件名
    /// @return 操作成功
    bool loadFrom(const QString& fileName);
    /// @brief 保存当前内容到一个文本文件中
    /// @param [in] fileName 路径文件名
    /// @return 操作成功
    bool saveTo(const QString& fileName);
};

TIANCHI_END_NAMESPACE

#endif // TIANCHI_STRING_H

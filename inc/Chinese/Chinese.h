// ********************************************************************************************************************
// Tianchi share library for Qt (C++)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// ********************************************************************************************************************
// 文档说明： 汉语相关处理
// ====================================================================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------------------------------------------------
// 2013.04.15   圣域天子    建立
//
// ====================================================================================================================
/// @file Chinese.h 汉语相关处理
#ifndef TIANCHI_CHINESE_H
#define TIANCHI_CHINESE_H

#include "Global.h"

#include <QString>

TIANCHI_BEGIN_NAMESPACE

/// 汉语相关处理类
class TIANCHI_API Chinese
{
public:
    /// 混合字符时，转换中不过滤英数符号等
    /// @param [in] Str 汉字字符串
    /// @param [in] Tonality 是否把音调转换成拼音
    /// @return 汉语拼音
    static QString toChars(const QString& Str, bool Tonality=false);
    /// 取得多个汉字的全拼音
    /// @param [in] Str 汉字字符串
    /// @param [in] Tonality 是否把音调转换成拼音
    /// @return 汉语拼音
    static QString toPinyin(const QString& Str, bool Tonality=false);
    /// 取得多个汉字的首字母
    /// @param [in] HzString 汉字字符串
    /// @return 每个汉字拼音的首字符
    static QString firstPinyins(const QString& HzString);
};

TIANCHI_END_NAMESPACE

#endif // TIANCHI_CHINESE_H

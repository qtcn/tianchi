// **************************************************************************
// Tianchi share library for Qt (C++)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明： 汉语相关处理
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.15   圣域天子    建立
//
// ==========================================================================
/// @file Chinese.h 汉语相关处理
#ifndef TIANCHI_CHINESE_H
#define TIANCHI_CHINESE_H

#include <tianchi/Global.h>

#include <QString>

namespace Tianchi
{
/// @brief 汉语相关处理类
/// @note 此类仅限在 Windows 下有效，使用时需要在 .pro 文件中加上 LIB += -lole32
class TIANCHI_API Chinese
{
public:
    /// 取得多个汉字的首字母
    /// @param [in] HzString 汉字字符串
    /// @return 每个汉字拼音的首字符
    /// @par 示例:
    /// @code
    /// qDebug()<<TIANCHI::Chinese::firstPinyins(QS("中华人民共和国"));
    /// > zhrmghg
    ///
    /// qDebug()<<TIANCHI::Chinese::firstPinyins(QS("中华大地Qt论坛 - www.qtcn.org"));
    /// > zhddlt
    ///
    /// @endcode
    static QString firstPinyins(const QString& HzString);

    /// 取得多个汉字的全部拼音
    /// @param [in] Str 汉字字符串
    /// @param [in] Tonality 音调不转换成拼音
    /// @return 汉语拼音
    /// @par 示例:
    /// @code
    /// 含音调的输出
    /// qDebug()<<TIANCHI::Chinese::toPinyin(QS("中华人民共和国"), true);
    /// > zhōnghuárénmíngònghéguó
    /// 不含音调的输出
    ///
    /// qDebug()<<TIANCHI::Chinese::toPinyin(QS("中华人民共和国"), false);
    /// > zhonghuarenmingongheguo
    ///
    /// qDebug()<<TIANCHI::Chinese::toPinyin(QS("中华大地Qt论坛 - www.qtcn.org"));
    /// > zhonghuadadiluntan
    ///
    /// @endcode
    static QString toPinyin(const QString& Str, bool Tonality=false);

    /// 混合字符时，转换中不过滤英数符号等
    /// @param [in] Str 汉字字符串
    /// @param [in] Tonality 音调不转换成拼音
    /// @return 汉字的首字母
    /// @par 示例:
    /// @code
    /// qDebug()<<TIANCHI::Chinese::toChars(QS("中华大地Qt论坛 - www.qtcn.org"), true);
    /// > zhōnghuádàdìQtlùntán - www.qtcn.org
    ///
    /// qDebug()<<TIANCHI::Chinese::toChars(QS("中华大地Qt论坛 - www.qtcn.org"));
    /// > zhonghuadadiQtluntan - www.qtcn.org
    ///
    /// @endcode
    static QString toChars(const QString& Str, bool Tonality=false);
};

}

typedef ::Tianchi::Chinese TcChinese;

#endif // TIANCHI_CHINESE_H

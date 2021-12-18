// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：公共单元，此单元不使用 namespace Tianchi
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.15   圣域天子    建立
// 2021.12.18   XChinux     增加Qt6支持
// ==========================================================================
/// @file Common.h 公共单元
#ifndef TIANCHI_TCCOMMON_H
#define TIANCHI_TCCOMMON_H

#include <tianchi/tcglobal.h>

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#else
#include <QTextCodec>
#endif

#include <QDateTime>

#ifdef QT_WIDGETS_LIB
    #include <QMessageBox>
#endif

#if defined(QT_DEBUG)
    #include <iostream>
    using namespace std;
#endif

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#else
/// @brief 设置字符集，使用汉字前应该为 "GBK"
/// @param [in] name 字符集名称
/// @par 示例:
/// @code
/// int main(int argc, char *argv[])
/// {
///     QApplication app(argc, argv);
///     // 先为应用程序设置字符集
///     initQS("GBK");
///
///     ...
/// }
/// void MyFunction()
/// {
///
///     qDebug()<<QS("显示为汉字，而不是乱码！");
///
/// }
/// @endcode
/// @return 全局字符集对象
/// @author 圣域天子 Jonix@qtcn.org
/// @date 2013-05-06
QTextCodec* initQS(const QByteArray& name="GBK");
#endif

/// @brief 汉字字符集转换
/// @param [in] s 汉字常量，或 char* 型的变量
/// @par 示例:
/// @code
/// int main(int argc, char *argv[])
/// {
///     QApplication app(argc, argv);
///     // 先为应用程序设置字符集
///     initQS("GBK");
///
///     ...
/// }
/// void MyFunction()
/// {
///
///     qDebug()<<QS("显示为汉字，而不是乱码！");
///
/// }
/// @endcode
/// @return 转换后的汉字字符串类型
/// @author 圣域天子 Jonix@qtcn.org
/// @date 2013-04-15
inline QString QS(const char* s)
{
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    return QStringDecoder(QStringConverter::System).decode(QByteArray(s));
#else
    return QTextCodec::codecForLocale()->toUnicode(s);
#endif
}

/// @brief 取最大值
#define max(a,b)    (((a) > (b)) ? (a) : (b))
/// @brief 取最小值
#define min(a,b)    (((a) < (b)) ? (a) : (b))
/// @brief 分支逻辑判断
inline int     iif(bool logic, int v1, int v2=0) { return logic ? v1 : v2; }
/// @brief 分支逻辑判断
inline QString iif(bool logic, const QString& v1, const QString& v2="") { return logic ? v1 : v2; }

#ifdef QT_WIDGETS_LIB
/// @brief 显示文本对话框
/// @param [in] 显示的文字
/// @see class QMessageBox
inline void MsgBox(const QString& s)
{
    QMessageBox::information(NULL, "", s);
}
#endif
#define TC_FREE(x)  {delete x; x=NULL;}
#if defined(QT_DEBUG)
    /// @brief 调试信息快速显示类
    /// @param [in] file 源文件名
    /// @param [in] line 行位置
    /// @param [in] text 显示文本内容
    inline void debug_out(const char* file, int line, const QString& text="")
    {
        cout<<QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss->").toLocal8Bit().data()<<file<<"("<<line<<"): "<<text.toLocal8Bit().data()<<endl;
    }
    /// @brief 调试信息快速显示类
    /// @param [in] file 源文件名
    /// @param [in] line 行位置
    /// @param [in] value 显示数值
    inline void debug_out(const char* file, int line, int value)
    {
        debug_out(file, line, QString::number(value));
    }

    /// @brief 为了方便运行时调试显示当前文件和行号，用于运行时跟踪执行步骤。
    #define DEBUG_STEP    debug_out(__FILE__, __LINE__);
    /// @brief 为了方便运行时调试设置的宏
    #define DEBUG_OUT(x)  debug_out(__FILE__, __LINE__, x);
#else
    /// @brief 为了方便运行时调试显示当前文件和行号，用于运行时跟踪执行步骤。
    #define DEBUG_STEP
    /// @brief 为了方便运行时调试设置的宏
    #define DEBUG_OUT(x)
#endif

/// @brief 返回当前时间字符串：yyyy-MM-dd HH:mm:ss.zzz
QString YYYY_MM_DD_HH_MM_SS_ZZZ();
/// @brief 返回当前时间字符串：yyyy-MM-dd HH:mm:ss
QString YYYY_MM_DD_HH_MM_SS();

#endif // TIANCHI_COMMON_H

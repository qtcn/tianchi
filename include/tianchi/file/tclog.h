// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：简单的 Log 输出类
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.10   圣域天子    建立
//
// ==========================================================================
/// @file LogTiny.h 简单的 Log 输出类
// ==========================================================================
#ifndef TIANCHI_TCLOG_H
#define TIANCHI_TCLOG_H

#include <tianchi/tcglobal.h>

#include <QString>

/// @brief 简单的文本文件输出日志。
/// @author 圣域天子 Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API TcLog
{
public:
    /// @brief 指定全路径的执行文件名，自动设置与执行文件同目录、同名，且后缀为 .log 的日志文件。
    /// @param [in] AppFile 执行文件名。
    /// @par 示例:
    /// @code
    /// QApplication app(argc, argv);
    ///
    /// TcLog log;
    ///
    /// // 建议把执行文件名作为参数
    /// log.setAppFile(app.applicationFilePath());
    /// @endcode
    /// @see setLogFile
    void setAppFile(const QString& AppFile);

    /// @brief 指定全路径的日志文件名。
    /// @param [in] LogFile 日志文件名。
    /// @par 示例:
    /// @code
    /// log.setLogFile("C:\\Temp\\app.log");
    /// @endcode
    /// @see setAppFile
    void setLogFile(const QString& LogFile);

    /// @brief 写日志
    /// @param [in] S 日志内容。
    /// @param [in] SourceName 源文件名，建议用__FILE__作为参数。
    /// @param [in] SourceLine 源文件行，建议用__LINE__作为参数。
    void write(const QString& S, const QString& SourceName="", int SourceLine=0);

    /// @brief 调试模式(Debug)下输出日志，在 Release 模式下没有作用。
    /// @param [in] S 日志内容。
    /// @param [in] SourceName 源文件名，建议用__FILE__作为参数。
    /// @param [in] SourceLine 源文件行，建议用__LINE__作为参数。
    inline void debug(const QString& S, const QString& SourceName="", int SourceLine=0)
    {
      #ifdef _DEBUG
        write(S, SourceName, SourceLine);
      #endif
    }

private:
    QString m_FileName;
};

/// @brief 向日志输出代码所在文件和行号，用于运行时跟踪执行步骤。
//#define Log_Step Log.write("<<STEP>>", __FILE__, __LINE__);

/// @brief 调试模式下输出日志，自动添加代码所在文件和行号。
//#ifdef _DEBUG
//    #define Debug_Log(s)   Log.write(s, __FILE__, __LINE__);
//#else
//    #define Debug_Log(s)
//#endif


#endif // TIANCHI_LOGTINY_H

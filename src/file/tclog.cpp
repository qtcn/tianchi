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
// 2021.12.18   XChinux     add Qt6 support
// ==========================================================================
/// @file LogTiny.cpp 简单的 Log 输出类
// ==========================================================================

#include <tianchi/file/tclog.h>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QTextStream>

///**
// * @brief Tianchi::Log 全局 Log4Qt 实例，可在应用程序中直接使用。
// */
//Log4Qt Log;
void TcLog::setAppFile(const QString& AppFile)
{
    QFileInfo fi(AppFile);
    m_FileName = fi.absolutePath() + QDir::separator() + fi.baseName() + ".log";
}

void TcLog::setLogFile(const QString& LogFile)
{
    m_FileName = LogFile;
}

void TcLog::write(const QString& S, const QString& SourceName, int SourceLine)
{
    if (!m_FileName.isEmpty())
    {
        QFileInfo fi(m_FileName);
        QFile f(m_FileName);
        QDir dir(fi.absoluteDir());
        if (!dir.exists())
        {
            dir.mkpath(fi.absolutePath());
        }
        if (dir.exists() && f.open(QFile::Text | QFile::Append))
        {
            QString line = S;
            if (!SourceName.isEmpty())
            {
                line.append("\t");
                line.append(SourceName);
                if (SourceLine > 0)
                {
                    line.append(":");
                    line.append(QString::number(SourceLine));
                }
            }
            QTextStream out(&f);
            out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz")
                << "\t" << line.trimmed() 
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
                << Qt::endl
#else
                << endl
#endif
                ;

            f.close();
        }
    }
}

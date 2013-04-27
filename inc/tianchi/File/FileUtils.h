// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：文件操作常用处理类
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.15   圣域天子    建立
//
// ==========================================================================
/// @file FileUtils.h 文件操作常用处理类
// ==========================================================================
#ifndef TIANCHI_FILEUTILS_H
#define TIANCHI_FILEUTILS_H

#include <tianchi/Global.h>

#include <QString>

TIANCHI_BEGIN_NAMESPACE

QT_USE_NAMESPACE

/// @brief 文件操作常用处理类
/// @author 圣域天子 Jonix@qtcn.org
/// @date 2013-04-15
class TIANCHI_API FileUtils
{
public:
    /// @brief 装载文本文件
    static bool loadFromFile(QString& context, const QString& filename);

    /// @brief 在指定目录中返回一个临时文件名
    /// @return 返回临时文件名，注意不创建该文件
    /// @note 此方法不会自动创建文件
    static QString uniqueFileName(const QString& dir, 
            const QString& fileTemplate, const QString& suffix="");

    /// @brief 取执行文件的版本，仅支持 Windows
    /// @param [in] exeFile 包含版本信息的文件名(.exe, .dll等)
    /// @return 版本信息(xxx.xxx.xxx.xxx)
    static QString fileVersion(const QString& exeFile);

    /// @brief 从目录及子目录中检索出所有文件名
    static QStringList searchFiles(const QString& path);
};

TIANCHI_END_NAMESPACE
#if 0
class TIANCHI_API TcFileUtils : public TIANCHI_PREPEND_NAMESPACE(FileUtils)
{
};
#endif
typedef TIANCHI_PREPEND_NAMESPACE(FileUtils) TcFileUtils;

#endif // TIANCHI_FILEUTILS_H

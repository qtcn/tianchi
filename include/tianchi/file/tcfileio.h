// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：一些文件复制和提取功能
// ==========================================================================
// 开发日志：
// 日期         人员                   说明
// --------------------------------------------------------------------------
// 2013.05.24   cnhemiya@gmail.com    建立
//
// ==========================================================================
/// @file tcfileio.h 一些文件复制和提取功能
// ==========================================================================

#ifndef TIANCHI_TCFILEIO_H
#define TIANCHI_TCFILEIO_H

#include <QString>
#include <QStringList>
#include <QIODevice>
#include <tianchi/tcglobal.h>

/// @brief 一些文件复制和提取功能的类
/// @author cnhemiya@gmail.com
/// @date 2013-05-24
class TIANCHI_API TcFileIO
{
public:

	/// @brief 复制文件
	/// @param fromFile 源文件名
	/// @param toFile 目的文件名
	/// @param bufferSize 缓冲大小，默认是 defaultBufferSize
	/// @see defaultBufferSize
	/// @return 复制的数据大小
	static qint64 copy(const QString &fromFile, const QString &toFile,
					   qint64 bufferSize = defaultBufferSize);

	/// @brief 复制文件
	/// @param fromFile 源文件名
	/// @param toFile 目的文件名
	/// @param fromFileOffset 源文件相对于文件开始处的偏移量
	/// @param copySize 复制的大小，默认是 -1，复制到源文件结尾处
	/// @param bufferSize 缓冲大小，默认是 defaultBufferSize
	/// @see defaultBufferSize
	/// @return 复制的数据大小
	static qint64 copy(const QString &fromFile, const QString &toFile,
					   qint64 fromFileOffset, qint64 copySize = -1,
					   qint64 bufferSize = defaultBufferSize);

	/// @brief 从源文件追加复制到目的文件结尾处
	/// @param fromFile 源文件名
	/// @param toFile 目的文件名
	/// @param bufferSize 缓冲大小，默认是 defaultBufferSize
	/// @see defaultBufferSize
	/// @return 追加复制的数据大小
	static qint64 append(const QString &fromFile, const QString &toFile,
						 qint64 bufferSize = defaultBufferSize);

	/// @brief 从源文件追加复制到目的文件结尾处
	/// @param fromFile 源文件名
	/// @param toFile 目的文件名
	/// @param fromFileOffset 源文件相对于文件开始处的偏移量
	/// @param appendSize 追加复制的大小，默认是 -1，复制到源文件结尾处
	/// @param bufferSize 缓冲大小，默认是 defaultBufferSize
	/// @see defaultBufferSize
	/// @return 追加复制的数据大小
	static qint64 append(const QString &fromFile, const QString &toFile,
						 qint64 fromFileOffset, qint64 appendSize = -1,
						 qint64 bufferSize = defaultBufferSize);

	/// @brief 按字节分解文件
	/// @param fromFile 源文件名
	/// @param toDir 目的文件夹
	/// @param splitSize 分解后单个文件大小
	/// @param bufferSize 缓冲大小，默认是 defaultBufferSize
	/// @see defaultBufferSize
	/// @return 分解后的文件个数
	/// @par 示例:
	/// @code
	/// 如果源文件是 d:\123.iso，目的文件夹是d:\11，
	/// 分解后的文件名是123.iso.1,123.iso.2,...这种形式
	/// @endcode
	static int split(const QString &fromFile, const QString &toDir,
						qint64 splitSize, qint64 bufferSize = defaultBufferSize);

	/// @brief 按字节合并文件
	/// @param fromFileList 源文件列表
	/// @param toFile 目的文件名
	/// @param bufferSize 缓冲大小，默认是 defaultBufferSize
	/// @see defaultBufferSize
	/// @return 合并的数据
	static qint64 join(const QStringList &fromFileList, const QString &toFile,
						qint64 bufferSize = defaultBufferSize);

	/// @brief 生成指定字符填充的“大笨蛋”文档，常用于光盘映像
	/// @param fileName 生成的文件名
	/// @param fileSize 文件大小
	/// @param fill 填充字符，默认 0x00
	/// @param bufferSize 缓冲大小，默认是 defaultBufferSize
	/// @see defaultBufferSize
	/// @return 生成的数据大小
	static qint64 makeDummyFile(const QString &fileName, qint64 fileSize,
								const char fill = 0x00,
								qint64 bufferSize = defaultBufferSize);

	/// @brief 1KB = 1024
	static const int KB;

	/// @brief 1MB = 1024 * 1024 = 1048576
	static const int MB;

	/// @brief 1GB = 1024 * 1024 * 1024 = 1073741824
	static const int GB;

	/// @brief 默认的缓冲大小 4MB
	static const int defaultBufferSize;

private:
	// 提取源文件数据到目的文件
	static qint64 dump(const QString &fromFile, const QString &toFile,
					   QIODevice::OpenMode fromOpenMode, QIODevice::OpenMode toOpenMode,
					   qint64 fromFileOffset, qint64 toFileOffset,
					   qint64 dumpSize, qint64 bufferSize);

	// 写入数据
	static qint64 write(QIODevice &from, QIODevice &to, qint64 writeSize, qint64 bufferSize);
};

#endif // TIANCHI_TCFILEIO_H

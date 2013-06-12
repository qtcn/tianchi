// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵����һЩ�ļ����ƺ���ȡ����
// ==========================================================================
// ������־��
// ����         ��Ա                   ˵��
// --------------------------------------------------------------------------
// 2013.05.24   cnhemiya@gmail.com    ����
//
// ==========================================================================
/// @file tcfileio.h һЩ�ļ����ƺ���ȡ����
// ==========================================================================

#ifndef TIANCHI_TCFILEIO_H
#define TIANCHI_TCFILEIO_H

#include <QString>
#include <QStringList>
#include <QIODevice>
#include <tianchi/tcglobal.h>

/// @brief һЩ�ļ����ƺ���ȡ���ܵ���
/// @author cnhemiya@gmail.com
/// @date 2013-05-24
class TIANCHI_API TcFileIO
{
public:

	/// @brief �����ļ�
	/// @param fromFile Դ�ļ���
	/// @param toFile Ŀ���ļ���
	/// @param bufferSize �����С��Ĭ���� defaultBufferSize
	/// @see defaultBufferSize
	/// @return ���Ƶ����ݴ�С
	static qint64 copy(const QString &fromFile, const QString &toFile,
					   qint64 bufferSize = defaultBufferSize);

	/// @brief �����ļ�
	/// @param fromFile Դ�ļ���
	/// @param toFile Ŀ���ļ���
	/// @param fromFileOffset Դ�ļ�������ļ���ʼ����ƫ����
	/// @param copySize ���ƵĴ�С��Ĭ���� -1�����Ƶ�Դ�ļ���β��
	/// @param bufferSize �����С��Ĭ���� defaultBufferSize
	/// @see defaultBufferSize
	/// @return ���Ƶ����ݴ�С
	static qint64 copy(const QString &fromFile, const QString &toFile,
					   qint64 fromFileOffset, qint64 copySize = -1,
					   qint64 bufferSize = defaultBufferSize);

	/// @brief ��Դ�ļ�׷�Ӹ��Ƶ�Ŀ���ļ���β��
	/// @param fromFile Դ�ļ���
	/// @param toFile Ŀ���ļ���
	/// @param bufferSize �����С��Ĭ���� defaultBufferSize
	/// @see defaultBufferSize
	/// @return ׷�Ӹ��Ƶ����ݴ�С
	static qint64 append(const QString &fromFile, const QString &toFile,
						 qint64 bufferSize = defaultBufferSize);

	/// @brief ��Դ�ļ�׷�Ӹ��Ƶ�Ŀ���ļ���β��
	/// @param fromFile Դ�ļ���
	/// @param toFile Ŀ���ļ���
	/// @param fromFileOffset Դ�ļ�������ļ���ʼ����ƫ����
	/// @param appendSize ׷�Ӹ��ƵĴ�С��Ĭ���� -1�����Ƶ�Դ�ļ���β��
	/// @param bufferSize �����С��Ĭ���� defaultBufferSize
	/// @see defaultBufferSize
	/// @return ׷�Ӹ��Ƶ����ݴ�С
	static qint64 append(const QString &fromFile, const QString &toFile,
						 qint64 fromFileOffset, qint64 appendSize = -1,
						 qint64 bufferSize = defaultBufferSize);

	/// @brief ���ֽڷֽ��ļ�
	/// @param fromFile Դ�ļ���
	/// @param toDir Ŀ���ļ���
	/// @param splitSize �ֽ�󵥸��ļ���С
	/// @param bufferSize �����С��Ĭ���� defaultBufferSize
	/// @see defaultBufferSize
	/// @return �ֽ����ļ�����
	/// @par ʾ��:
	/// @code
	/// ���Դ�ļ��� d:\123.iso��Ŀ���ļ�����d:\11��
	/// �ֽ����ļ�����123.iso.1,123.iso.2,...������ʽ
	/// @endcode
	static int split(const QString &fromFile, const QString &toDir,
						qint64 splitSize, qint64 bufferSize = defaultBufferSize);

	/// @brief ���ֽںϲ��ļ�
	/// @param fromFileList Դ�ļ��б�
	/// @param toFile Ŀ���ļ���
	/// @param bufferSize �����С��Ĭ���� defaultBufferSize
	/// @see defaultBufferSize
	/// @return �ϲ�������
	static qint64 join(const QStringList &fromFileList, const QString &toFile,
						qint64 bufferSize = defaultBufferSize);

	/// @brief ����ָ���ַ����ġ��󱿵����ĵ��������ڹ���ӳ��
	/// @param fileName ���ɵ��ļ���
	/// @param fileSize �ļ���С
	/// @param fill ����ַ���Ĭ�� 0x00
	/// @param bufferSize �����С��Ĭ���� defaultBufferSize
	/// @see defaultBufferSize
	/// @return ���ɵ����ݴ�С
	static qint64 makeDummyFile(const QString &fileName, qint64 fileSize,
								const char fill = 0x00,
								qint64 bufferSize = defaultBufferSize);

	/// @brief 1KB = 1024
	static const int KB;

	/// @brief 1MB = 1024 * 1024 = 1048576
	static const int MB;

	/// @brief 1GB = 1024 * 1024 * 1024 = 1073741824
	static const int GB;

	/// @brief Ĭ�ϵĻ����С 4MB
	static const int defaultBufferSize;

private:
	// ��ȡԴ�ļ����ݵ�Ŀ���ļ�
	static qint64 dump(const QString &fromFile, const QString &toFile,
					   QIODevice::OpenMode fromOpenMode, QIODevice::OpenMode toOpenMode,
					   qint64 fromFileOffset, qint64 toFileOffset,
					   qint64 dumpSize, qint64 bufferSize);

	// д������
	static qint64 write(QIODevice &from, QIODevice &to, qint64 writeSize, qint64 bufferSize);
};

#endif // TIANCHI_TCFILEIO_H

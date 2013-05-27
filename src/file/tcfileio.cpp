#include <tianchi/file/tcfileio.h>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QIODevice>
#include <QFileInfo>


const int TcFileIO::KB = 1024; // KB 1024
const int TcFileIO::MB = 1048576; // MB 1024*1024
const int TcFileIO::GB = 1073741824; // GB 1024*1024*1024
const int TcFileIO::defaultBufferSize = 4 * TcFileIO::MB; // 4MB 4*1024*1024


qint64 TcFileIO::copy(const QString &fromFile, const QString &toFile, qint64 bufferSize)
{
	return dump(fromFile, toFile, QIODevice::ReadOnly, QIODevice::WriteOnly,
				0, 0, -1, bufferSize);
}

qint64 TcFileIO::copy(const QString &fromFile, const QString &toFile, qint64 fromFileOffset,
				   qint64 copySize, qint64 bufferSize)
{
	return dump(fromFile, toFile, QIODevice::ReadOnly, QIODevice::WriteOnly,
				fromFileOffset, 0, copySize, bufferSize);
}

qint64 TcFileIO::append(const QString &fromFile, const QString &toFile, qint64 bufferSize)
{
	return dump(fromFile, toFile, QIODevice::ReadOnly, QIODevice::Append,
				0, 0, -1, bufferSize);
}

qint64 TcFileIO::append(const QString &fromFile, const QString &toFile, qint64 fromFileOffset,
					   qint64 appendSize, qint64 bufferSize)
{
	return dump(fromFile, toFile, QIODevice::ReadOnly, QIODevice::Append,
				fromFileOffset, 0, appendSize , bufferSize);
}

int TcFileIO::split(const QString &fromFile, const QString &toDir, qint64 splitSize,
					qint64 bufferSize)
{
	QDir to_dir(toDir);

	if (!to_dir.exists())
		to_dir.mkpath(toDir);

	int file_count = 0;
	QFile from_file(fromFile);
	qint64 from_size = from_file.size();
	QString to_file;
	QString from_file_name(QFileInfo(fromFile).fileName());
	qint64 write_size;

	while (from_size > 0)
	{
		write_size = from_size > splitSize ? splitSize : from_size;
		to_file = toDir + "/" + from_file_name + "." + QString::number(file_count + 1);
		dump(fromFile, to_file, QIODevice::ReadOnly, QIODevice::WriteOnly,
						splitSize * file_count, 0, write_size, bufferSize);
		from_size -= write_size;
		file_count++;
	}

	return file_count;
}

qint64 TcFileIO::unite(const QStringList &fromFileList, const QString &toFile, qint64 bufferSize)
{
	int size = fromFileList.size();
	qint64 file_size = 0;
	qint64 dump_size = 0;

	for (int i = 0; i < size; i++)
	{
		dump_size = dump(fromFileList[i], toFile, QIODevice::ReadOnly, QIODevice::Append,
			 0, 0, -1, bufferSize);
		file_size += dump_size != -1 ? dump_size : 0;
	}

	return file_size;
}

qint64 TcFileIO::makeDummyFile(const QString &fileName, qint64 fileSize, const char fill,
							 qint64 bufferSize)
{
	QFile file(fileName);
	QByteArray data(bufferSize, fill);
	qint64 write_size = bufferSize;
	qint64 sum_write_size = 0;

	try
	{
		file.open(QIODevice::WriteOnly);

		while(fileSize > 0)
		{
			write_size = fileSize < bufferSize ? fileSize: bufferSize;
			write_size = file.write(data.data(), write_size);
			fileSize -= write_size;
			sum_write_size += write_size;
		}
	}
	catch(...)
	{
		file.close();
		return -1;
	}

	file.close();
	return sum_write_size;
}

qint64 TcFileIO::dump(const QString &fromFile, const QString &toFile,
					QIODevice::OpenMode fromOpenMode, QIODevice::OpenMode toOpenMode,
					qint64 fromFileOffset, qint64 toFileOffset,
					qint64 dumpSize, qint64 bufferSize)
{
	QFile from(fromFile);
	QFile to(toFile);
	qint64 sum_read_size = 0;

	try
	{
		from.open(fromOpenMode);
		to.open(toOpenMode);
		from.seek(fromFileOffset);

		if (toOpenMode != QIODevice::Append)
			to.seek(toFileOffset);

		sum_read_size = write(from, to, dumpSize, bufferSize);
	}
	catch(...)
	{
		from.close();
		to.close();
		return -1;
	}

	from.close();
	to.close();
	return sum_read_size;
}

qint64 TcFileIO::write(QIODevice &from, QIODevice &to, qint64 writeSize,
					qint64 bufferSize)
{
	QByteArray data(bufferSize, 0x00);
	qint64 read_size = 0;
	qint64 ready_read_size = bufferSize;
	qint64 sum_read_size = 0;

	while (!from.atEnd())
	{
		if (writeSize > -1)
		{
			ready_read_size = writeSize < bufferSize ? writeSize: bufferSize;
			writeSize -= ready_read_size;
		}

		read_size = from.read(data.data(), ready_read_size);
		to.write(data.data(), read_size);
		sum_read_size += read_size;

		if (writeSize == 0)
			break;
	}

	return sum_read_size;
}

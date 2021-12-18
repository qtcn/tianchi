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
// 2013.06.14   XChinux     为loadFromFile()函数增加codec参数
// 2021.12.18   XChinux     add Qt6 support
// ==========================================================================
/// @file FileUtils.cpp 文件操作常用处理类
// ==========================================================================
#include <tianchi/file/tcfile.h>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#if defined(Q_OS_WIN)
  #include <windows.h>
#endif

bool TcFile::loadFromFile(QString &context, const QString &filename,
        const QString &codec /* = QString() */)
{
    bool ret = false;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
       QTextStream in(&file);
       if (!codec.isEmpty())
       {
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
           // TODO 系统自动识别内容编码，若要自定义需要调用void QTextStream::setEncoding(QStringConverter::Encoding encoding)
#else
           in.setCodec(codec.toLatin1().data());
#endif
       }
       context = in.readAll();
       ret = true;
       file.close();
    }
    return ret;
}

QString TcFile::uniqueFileName(const QString &dir, 
        const QString &fileTemplate, 
        const QString &suffix /* = QString() */)
{
    QString fileDir    = dir;
    QString filePrefix = fileTemplate;
    QString fileSuffix = suffix;

    QFileInfo f;
    if (fileDir.isEmpty())
    {
        f.setFile(fileTemplate);
        fileDir    = f.absoluteDir().absolutePath();
        fileSuffix = f.suffix();
        if (!fileSuffix.isEmpty())
        {
            filePrefix = filePrefix.mid(0, 
                    filePrefix.length() - fileSuffix.length() - 1);
        }
    }
    if (fileSuffix.isEmpty())
    {
        f.setFile(fileTemplate);
        fileSuffix = f.suffix();
        if (!fileSuffix.isEmpty())
        {
            filePrefix = filePrefix.mid(0, 
                    filePrefix.length() - fileSuffix.length() - 1);
        }
    }
    QString ret = fileDir + QDir::separator() + filePrefix + "." + fileSuffix;
    f.setFile(ret);
    int index = 2;
    while (f.exists())
    {
        ret = fileDir + QDir::separator() + filePrefix 
            + "(" + QString::number(index++) + ")." + fileSuffix;
        f.setFile(ret);
    }
    return ret;
}

QString TcFile::fileVersion(const QString&  exeFile)
{
    QString ret;

#if defined(Q_OS_WIN)
    int size = GetFileVersionInfoSize(exeFile.toStdWString().c_str(), NULL);
    if (size > 0)
    {
        char* data = new char[size +1];
        if (GetFileVersionInfo(exeFile.toStdWString().c_str(), 0, size, data))
        {
            VS_FIXEDFILEINFO* fileInfo;
            unsigned int      fileInfoSize = 0;
            if (VerQueryValue(data, L"\\", (void**)&fileInfo, &fileInfoSize))
            {
                int vMajor  = HIWORD(fileInfo->dwFileVersionMS);
                int vMinor  = LOWORD(fileInfo->dwFileVersionMS);
                int Release = HIWORD(fileInfo->dwFileVersionLS);
                int vBuild  = LOWORD(fileInfo->dwFileVersionLS);
                ret.append(QString::number(vMajor)).append(".")
                        .append(QString::number(vMinor)).append(".")
                        .append(QString::number(Release)).append(".")
                        .append(QString::number(vBuild));
            }
        }
        delete [] data;
    }
#else
    Q_UNUSED(exeFile)
#endif
    return ret;
}

QStringList TcFile::searchFiles(const QString& path)
{
    QStringList ret;
    // 这个函数可以执行任何任务，
    // 这里只是简单地输出各个文件（夹）的名字
    QDir dir(path);
    QStringList
    list = dir.entryList(QDir::Dirs, QDir::Name);
    for (QStringList::Iterator it = list.begin(); it != list.end(); it++)
    {
        if ("." != *it && ".." != *it)
        {
            ret.append(searchFiles(path + QDir::separator() + *it));
        }
    }
    list = dir.entryList(QDir::Files, QDir::Name);
    for (QStringList::Iterator it = list.begin(); it != list.end(); it++)
    {
        ret.append(*it);
    }
    return ret;
}

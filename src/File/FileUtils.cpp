#include "File/FileUtils.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

TIANCHI_BEGIN_NAMESPACE

bool FileUtils::loadFromFile(QString& context, const QString& filename)
{
    bool ret = false;
    QFile file(filename);
    if ( file.open(QIODevice::ReadOnly) )
    {
       QTextStream in(&file);
       context = in.readAll();
       ret = true;
       file.close();
    }
    return ret;
}

QString FileUtils::uniqueFileName(const QString& dir, const QString& fileTemplate, const QString& suffix)
{
    QString fileDir    = dir;
    QString filePrefix = fileTemplate;
    QString fileSuffix = suffix;

    QFileInfo f;
    if ( fileDir == "" )
    {
        f.setFile(fileTemplate);
        fileDir    = f.absoluteDir().absolutePath();
        fileSuffix = f.suffix();
        if ( ! fileSuffix.isEmpty() )
        {
            filePrefix = filePrefix.mid(0, filePrefix.length()-fileSuffix.length()-1);
        }
    }
    if ( fileSuffix == "" )
    {
        f.setFile(fileTemplate);
        fileSuffix = f.suffix();
        if ( ! fileSuffix.isEmpty() )
        {
            filePrefix = filePrefix.mid(0, filePrefix.length()-fileSuffix.length()-1);
        }
    }
    QString ret = fileDir + QDir::separator() + filePrefix + "." + fileSuffix;
    f.setFile(ret);
    int index = 2;
    while(f.exists())
    {
        ret = fileDir + QDir::separator() + filePrefix + "("+QString::number(index++)+")."+fileSuffix;
        f.setFile(ret);
    }
    return ret;
}

QString FileUtils::fileVersion(const QString& exeFile)
{
    QString ret = "";

  #if defined(TC_OS_WIN32_CXX_MSC_BCB)
    int size = GetFileVersionInfoSize(exeFile.toStdWString().c_str(), NULL);
    if ( size >0 )
    {
        char* data = new char[size +1];
        if ( GetFileVersionInfo(exeFile.toStdWString().c_str(), 0, size, data) )
        {
            VS_FIXEDFILEINFO* fileInfo;
            unsigned int      fileInfoSize = 0;
            if ( VerQueryValue(data, L"\\", (void**)&fileInfo, &fileInfoSize) )
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
        delete data;
    }
  #endif
    return ret;
}

TIANCHI_END_NAMESPACE


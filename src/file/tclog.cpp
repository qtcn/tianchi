#include <tianchi/file/tclog.h>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QTextStream>

///**
// * @brief Tianchi::Log ȫ�� Log4Qt ʵ��������Ӧ�ó�����ֱ��ʹ�á�
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
                << "\t" << line.trimmed() <<endl;

            f.close();
        }
    }
}

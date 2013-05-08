#include <tianchi/core/tcstring.h>

#include <QTextCodec>
#include <QFile>
#include <QTextStream>

TcString::TcString()
{
}

QByteArray TcString::first(QByteArray& str, const QByteArray& split)
{
    QByteArray ret;
    int endOf = str.indexOf(split);
    if ( endOf == 0 )
    {
        str.remove(0, 1);
    }
    else
    if ( endOf > 0 )
    {
        ret = str.left(endOf);
        str.remove(0, endOf +1);
    }
    else
    {
        ret = str;
    }

    return ret;
}

int TcString::find(const QStringList& ss, const QString& s)
{
    int ret = -1;
    for( int i=0;i<ss.count();i++ )
    {
        if ( ss.at(i).compare(s) == 0 )
        {
            ret = i;
            break;
        }
    }
    return ret;
}

int TcString::findOf(const QStringList& list, const QString& key)
{
    int ret = -1;
    for( int i=0;i<list.count();i++ )
    {
        if ( list.at(i).trimmed().compare(key.trimmed(), Qt::CaseInsensitive)==0 )
        {
            ret = i;
            break;
        }
    }
    return ret;
}

bool TcString::filter(const QString& text, const QStringList& filters)
{
    bool ret = filters.count() <= 0;
    foreach(QString s, filters)
    {
        s = s.trimmed();
        if ( ! s.isEmpty() )
        {
            if ( text.indexOf(s, Qt::CaseInsensitive) >= 0 )
            {
                ret = true;
                break;
            }
        }
    }
    return ret;
}

/// 分解姓名（单、复姓、英文）
int TcString::splitHumanName(QString full, QString& sur, QString& real, QString& english)
{
    QString surs = QTextCodec::codecForLocale()->toUnicode(
                               "欧阳\n太史\n端木\n上官\n司马\n东方\n独孤\n南宫\n万俟\n"
                               "闻人\n夏侯\n诸葛\n尉迟\n公羊\n赫连\n澹台\n皇甫\n宗政\n"
                               "濮阳\n公冶\n太叔\n申屠\n公孙\n慕容\n仲孙\n钟离\n长孙\n"
                               "宇文\n司徒\n鲜于\n司空\n闾丘\n子车\n亓官\n司寇\n巫马\n"
                               "公西\n颛孙\n壤驷\n公良\n漆雕\n乐正\n宰父\n谷梁\n拓跋\n"
                               "夹谷\n轩辕\n令狐\n段干\n百里\n呼延\n东郭\n南门\n羊舌\n"
                               "微生\n公户\n公玉\n公仪\n梁丘\n公仲\n公上\n公门\n公山\n"
                               "公坚\n左丘\n公伯\n西门\n公祖\n第五\n公乘\n贯丘\n公皙\n"
                               "南荣\n东里\n东宫\n仲长\n子书\n子桑\n即墨\n达奚\n褚师\n");
    QStringList doubleSurnames = surs.split("\n");

    full = full.trimmed();

    int ret = 0;
    if ( ! full.isEmpty() )
    {
        if ( full.length() != full.toLocal8Bit().length() )
        {// 汉字
            foreach(QString s, doubleSurnames)
            {
                if ( ! s.isEmpty() && full.startsWith(s) )
                {
                    sur = s;
                    ret = 2;
                    break;
                }
            }
            if ( ret != 2 )
            {
                sur = full.mid(0, 1);
                ret = 1;
            }
            real = full.mid(sur.length());
        }else
        {// 英文名
            QStringList ss = full.split(" ", QString::SkipEmptyParts);
            english = "";
            for( int i=0;i<ss.count();i++ )
            {
                QString t = ss.at(i);
                if ( i == ss.count()-1 )
                {
                    sur = t;
                }else
                {
                    english += t + " ";
                }
            }
            english = english.trimmed();

            ret = 3;
        }
    }
    return ret;
}

QString TcString::getTextByIndex(const char* strings, int index)
{
    QStringList ss = QTextCodec::codecForLocale()->toUnicode(strings).split("\n", QString::SkipEmptyParts);
    return ss.at(index);
}

// class StringList
TcStringList::TcStringList()
{
    #if defined(Q_OS_WIN)
        m_lineBreak = "\r\n";
    #elif defined(Q_OS_LINUX)
        m_lineBreak = "\n";
    #elif defined(Q_OS_MAC)
        m_lineBreak = "\r";
    #else
        m_lineBreak = "\n";
    #endif
}

bool TcStringList::loadFrom(const QString& fileName)
{
    bool ret = false;
    QFile f(fileName);
    if ( f.open(QFile::Text | QFile::ReadOnly) )
    {
        clear();
        QTextStream in(&f);
        while(!in.atEnd())
        {
            this->append(in.readLine());
        }
        f.close();
        ret = false;
    }
    return ret;
}

bool TcStringList::saveTo(const QString& fileName)
{
    bool ret = false;
    QFile f(fileName);
    if ( f.open(QFile::Text | QFile::WriteOnly) )
    {
        QTextStream out(&f);
        foreach(QString s, *this)
        {
            out<<s<<lineBreak();
        }
        f.close();
    }
    return ret;
}

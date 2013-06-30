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
    return ss.indexOf(s);
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

/// �ֽ��������������ա�Ӣ�ģ�
int TcString::splitHumanName(QString full, QString& sur, QString& real, QString& english)
{
    QString surs = QTextCodec::codecForLocale()->toUnicode(
                               "ŷ��\n̫ʷ\n��ľ\n�Ϲ�\n˾��\n����\n����\n�Ϲ�\n��ٹ\n"
                               "����\n�ĺ�\n���\nξ��\n����\n����\n�̨\n�ʸ�\n����\n"
                               "���\n��ұ\n̫��\n����\n����\nĽ��\n����\n����\n����\n"
                               "����\n˾ͽ\n����\n˾��\n����\n�ӳ�\n����\n˾��\n����\n"
                               "����\n���\n����\n����\n���\n����\n�׸�\n����\n�ذ�\n"
                               "�й�\n��ԯ\n���\n�θ�\n����\n����\n����\n����\n����\n"
                               "΢��\n����\n����\n����\n����\n����\n����\n����\n��ɽ\n"
                               "����\n����\n����\n����\n����\n����\n����\n����\n���\n"
                               "����\n����\n����\n�ٳ�\n����\n��ɣ\n��ī\n����\n��ʦ\n");
    QStringList doubleSurnames = surs.split("\n");

    full = full.trimmed();

    int ret = 0;
    if ( ! full.isEmpty() )
    {
        if ( full.length() != full.toLocal8Bit().length() )
        {// ����
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
        {// Ӣ����
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

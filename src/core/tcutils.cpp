#include <tianchi/core/tcutils.h>

#include <QTextCodec>
#include <QDateTime>
#include <QFileInfo>
#include <QDir>

#include <QSettings>

#if defined(Q_OS_WIN)
  #include <windows.h>
#endif

#include <QMessageBox>

#include <iostream>
using namespace std;

QHash<QString, QString> TcUtils::StringToMap(const QString& mapStrings)
{
    QStringList strings = mapStrings.split("\n", QString::SkipEmptyParts);

    return StringToMap(strings);
}

QHash<QString, QString> TcUtils::StringToMap(const QStringList& mapStrings)
{
    QHash<QString, QString> ret;

    foreach(QString s, mapStrings)
    {
        QString key;
        QString value;
        int pos = s.indexOf("=");
        if ( pos >= 0 )
        {
            key = s.mid(0, pos).trimmed();
            value = s.mid(pos+1).trimmed();
            if ( ! key.isEmpty() && ! value.isEmpty() )
            {
                ret[key] = value;
            }
        }
    }
    return ret;
}

char TcUtils::typeFrom(QVariant::Type type)
{
    char c = '\0';
    if ( type == QVariant::Int
      || type == QVariant::UInt
      || type == QVariant::LongLong
      || type == QVariant::ULongLong )
    {
        c = 'i';
    }else
    if ( type == QVariant::Double )
    {
        c = 'n';
    }else
    if ( type == QVariant::String )
    {
        c = 's';
    }else
    if ( type == QVariant::Date
      || type == QVariant::Time
      || type == QVariant::DateTime )
    {
        c = 't';
    }else
    if ( type == QVariant::Date
      || type == QVariant::Time
      || type == QVariant::DateTime )
    {
        c = 't';
    }else
    if ( type == QVariant::ByteArray )
    {
         c = 'm';
    }else
    {

    }
    return c;
}

QDateTime TcUtils::toDateTime(const QString& text)
{
    QDateTime ret = QDateTime();
    switch(text.length())
    {
    case 23:
        ret.fromString(text, "yyyy-MM-dd HH:mm:ss.zzz");
        break;
    case 19:
        ret.fromString(text, "yyyy-MM-dd HH:mm:ss");
        break;
    case 16:
        ret.fromString(text, "yyyy-MM-dd HH:mm");
        break;
    case 14:
        ret.fromString(text, "yyyyMMddHHmmss");
        break;
    case 10:
        ret.fromString(text, "yyyy-MM-dd");
        break;
    case  8:
        ret.fromString(text, "HH:mm:ss");
        break;
    case  7:
        ret.fromString(text, "yyyy/MM");
        break;
    case  6:
        ret.fromString(text, "HHmmss");
        break;
    case  5:
        if ( text.at(2) == '/'
          || text.at(2) == '-' )
        {
            ret.fromString(text, "MM/dd");
        }else
        if ( text.at(2) == ':' )
        {
            ret.fromString(text, "HH:mm");
        }
        break;
    case  4:
        ret.fromString(text, "yyyy");
        break;
    case  2:
        ret.fromString(text, "dd");
        break;
    case  1:
        ret.fromString(text, "d");
        break;
    }
    return ret;
}

QDateTime TcUtils::toDateTime(double timeDouble)
{
    int    days    = int(timeDouble);
    double seconds = timeDouble - days;

    //const qint64 OF_JULIAN_DAY = 2415019;
    QDate date = QDate::fromJulianDay(JULIAN_DAY + days);
    QTime time(0, 0, 0, 0);
    time = time.addSecs(seconds * 86400.0);
    return QDateTime(date, time);
}

char TcUtils::getIDCardVerifyCode(const QByteArray& id)
{
    char ret = '\0';
    if ( id.length() >= 17 )
    {
        // 加权乘积求和除以11的余数所对应的校验数
        const char verifyMap[] = "10X98765432";
        // 加权因子
        const int factor[] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2, 1 };

        int Sum = 0;  //加权乘积求和
        for( int i=0;i<17;i++ )
        {
            char c = id[i];

            Sum += (c-'0') * factor[i]; // 加权乘积求和
        }
        ret = verifyMap[Sum % 11]; // 取模
    }
    return ret;
}

QDateTime TcUtils::complieDateTime(const QString& complieDate, const QString& complieTime)
{
    QString DateString = complieDate;
    QString Year  = DateString.right(4);
    QString Month = DateString.left(3).toUpper();
    QString Day   = DateString.mid(4, 2);
    QString TimeString = complieTime;
    QString Hour   = TimeString.left(2);
    QString Minute = TimeString.mid(3, 2);
    QString Second = TimeString.right(2);
    const QString MonthString[12] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                                      "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
    unsigned int MonthValue;
    for( MonthValue=0;MonthValue<sizeof(MonthString);MonthValue++ )
    {
        if ( Month == MonthString[MonthValue] )
        {
            MonthValue++;
            break;
        }
    }
    return QDateTime(QDate(Year.toInt(), MonthValue, Day.toInt()),
                     QTime(Hour.toInt(), Minute.toInt(), Second.toInt()));
}

QByteArray TcUtils::addField(const QString& key, const QVariant& value)
{
    QByteArray bytes = value.toByteArray();

    return QByteArray()
            .append(key.toLower()).append('\0')
            .append(typeFrom(value.type())).append('\0')
            .append(QByteArray::number(bytes.length())).append('\0')
            .append(bytes);
}

QHash<QString, QByteArray> TcUtils::byFields(const QByteArray& fieldBytes)
{
    QHash<QString, QByteArray>  ret;

    int pos1 = 0;
    int pos2 = fieldBytes.indexOf('\0');
    while(pos2>=0)
    {
        QString key = fieldBytes.mid(pos1, pos2);
        pos1 = fieldBytes.indexOf('\0', ++pos2);
        QString type = fieldBytes.mid(pos2, pos1-pos2);
        pos2 = fieldBytes.indexOf('\0', ++pos1);
        int len = fieldBytes.mid(pos1, pos2-pos1).toInt();
        QByteArray value = fieldBytes.mid(++pos2, len);
        pos1 = pos2+len;
        ret[key] = value;
        pos2 = fieldBytes.indexOf('\0', pos1);
    }
    return ret;
}

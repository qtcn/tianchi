#include <tianchi/core/tccommon.h>

QTextCodec* initQS(const QByteArray& name)
{
    QTextCodec* textCodec=QTextCodec::codecForName(name);
    QTextCodec::setCodecForLocale(textCodec);
    return textCodec;
}

QString YYYY_MM_DD_HH_MM_SS_ZZZ()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
}

QString YYYY_MM_DD_HH_MM_SS()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
}


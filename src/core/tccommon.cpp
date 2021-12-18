// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：公共单元，此单元不使用 namespace Tianchi
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.15   圣域天子    建立
// 2021.12.18   XChinux     add Qt6 support
// ==========================================================================
/// @file Common.cpp 公共单元

#include <tianchi/core/tccommon.h>

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#else
QTextCodec* initQS(const QByteArray& name)
{
    QTextCodec* textCodec=QTextCodec::codecForName(name);
    QTextCodec::setCodecForLocale(textCodec);
    return textCodec;
}
#endif

QString YYYY_MM_DD_HH_MM_SS_ZZZ()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
}

QString YYYY_MM_DD_HH_MM_SS()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
}


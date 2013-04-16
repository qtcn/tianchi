// ********************************************************************************************************************
// Tianchi share library for Qt (C++)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// ********************************************************************************************************************
// 文档说明：常用功能函数
// ====================================================================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------------------------------------------------
// 2013.04.11   cnhemiya    建立

// ====================================================================================================================
#ifndef TIANCHI_GLOBAL_H
#define TIANCHI_GLOBAL_H

#include <QtGlobal>

// 编译 dll 时请在 .pro 中添加：
// DEFINES += TIANCHI_EXPORT

// 编译 exe 并引入 dll 时请在 .pro 中添加：
// DEFINES += TIANCHI_IMPORT

// 直接引入源码编译时，不要定义 TIANCHI_EXPORT 或 TIANCHI_IMPORT
// DEFINES -= TIANCHI_EXPORT
// DEFINES -= TIANCHI_IMPORT

#if defined(TIANCHI_EXPORT)
#   define TIANCHI_API Q_DECL_EXPORT
#elif defined(TIANCHI_IMPORT)
#   define TIANCHI_API Q_DECL_IMPORT
#else
#   define TIANCHI_API
#endif

#ifndef TIANCHI_VERSION
#   define TIANCHI_VERSION 0x000002
#endif

// 名字空间，如果名字空间有冲突修改 Tianchi 就可以
#ifndef TIANCHI_NAMESPACE
#   define TIANCHI_NAMESPACE Tianchi
#   define TIANCHI_BEGIN_NAMESPACE namespace TIANCHI_NAMESPACE {
#   define TIANCHI_END_NAMESPACE } // namespace TIANCHI_NAMESPACE
#endif

// 常用操作系统预定义
// Q_OS_WIN
// Q_OS_WIN32
// Q_OS_WIN64
// Q_OS_WINCE

// Q_OS_LINUX

// Q_OS_MAC

// 常用编译器预定义
// _MSC_VER
// __GNUC__
// __BORLANDC__

// 类型
//#ifndef TC_TYPE_DEFINE
//#   define TC_TYPE_DEFINE
//typedef tcint8      char;
//typedef tcint16     short;
//typedef tcint32     long;
//typedef tcint64     long long;
//typedef tcuint8     unsigned char;
//typedef tcuint16    unsigned short;
//typedef tcuint32    unsigned long;
//typedef tcuint64    unsigned long long;
//#endif

#endif // TIANCHI_GLOBAL_H

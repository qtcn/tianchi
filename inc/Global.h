// **************************************************************************
// Tianchi share library for Qt (C++)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：常用功能函数
// ==========================================================================
// 开发日志：
// 日期         人员        说明
// --------------------------------------------------------------------------
// 2013.04.11   cnhemiya    建立
// 2013.04.17   XChinux     参照Qt/qglobal.h文件重写Global.h
// ==========================================================================
// 注意事项:
// 1. 编译Tianchi共享库或Tianchi静态库时请在 .pro 中添加：
//      DEFINES += TIANCHI_BUILD_LIB
// 2. 如果编译Tianchi库时要自定义名字空间,则在.pro中添加:
//      DEFINES += TIANCHI_NAMESPACE=mynamespace
//    如未定义TIANCHI_NAMESPACE,则默认定义为Tianchi
// 3. TIANCHI_EXPORT与TIANCHI_API同义
// 4. 如果要编译Tianchi静态库,则在.pro中添加:
//      DEFINES += TIANCHI_STATIC
// ==========================================================================

#ifndef TIANCHI_GLOBAL_H
#define TIANCHI_GLOBAL_H

#ifndef __cplusplus
#    error "Tianchi library only support C++ Compilers"
#endif


/**
 * TIANCHI_NAMESPACE 应该在.pro中定义,但为了防止名字冲突,这里强制定义
 */
#ifndef TIANCHI_NAMESPACE
#   define TIANCHI_NAMESPACE Tianchi
#endif


#include <QtCore/qglobal.h>


#define TIANCHI_VERSION_STR   "0.0.1"
/*
   TIANCHI_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define TIANCHI_VERSION 0x000001
/*
   can be used like #if (TIANCHI_VERSION >= TIANCHI_VERSION_CHECK(4, 4, 0))
*/
#define TIANCHI_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

#if !defined(TIANCHI_NAMESPACE) // user namespace, copy from qglobal.h

# define TIANCHI_PREPEND_NAMESPACE(name) ::name
# define TIANCHI_USE_NAMESPACE
# define TIANCHI_BEGIN_NAMESPACE
# define TIANCHI_END_NAMESPACE
# define TIANCHI_BEGIN_INCLUDE_NAMESPACE
# define TIANCHI_END_INCLUDE_NAMESPACE
#ifndef TIANCHI_BEGIN_MOC_NAMESPACE
# define TIANCHI_BEGIN_MOC_NAMESPACE
#endif
#ifndef TIANCHI_END_MOC_NAMESPACE
# define TIANCHI_END_MOC_NAMESPACE
#endif
# define TIANCHI_FORWARD_DECLARE_CLASS(name) class name;
# define TIANCHI_FORWARD_DECLARE_STRUCT(name) struct name;
# define TIANCHI_MANGLE_NAMESPACE(name) name

#else /* user namespace */

# define TIANCHI_PREPEND_NAMESPACE(name) ::TIANCHI_NAMESPACE::name
# define TIANCHI_USE_NAMESPACE using namespace ::TIANCHI_NAMESPACE;
# define TIANCHI_BEGIN_NAMESPACE namespace TIANCHI_NAMESPACE {
# define TIANCHI_END_NAMESPACE }
# define TIANCHI_BEGIN_INCLUDE_NAMESPACE }
# define TIANCHI_END_INCLUDE_NAMESPACE namespace TIANCHI_NAMESPACE {
#ifndef TIANCHI_BEGIN_MOC_NAMESPACE
# define TIANCHI_BEGIN_MOC_NAMESPACE TIANCHI_USE_NAMESPACE
#endif
#ifndef TIANCHI_END_MOC_NAMESPACE
# define TIANCHI_END_MOC_NAMESPACE
#endif
# define TIANCHI_FORWARD_DECLARE_CLASS(name) \
    TIANCHI_BEGIN_NAMESPACE class name; TIANCHI_END_NAMESPACE \
    using TIANCHI_PREPEND_NAMESPACE(name);

# define TIANCHI_FORWARD_DECLARE_STRUCT(name) \
    TIANCHI_BEGIN_NAMESPACE struct name; TIANCHI_END_NAMESPACE \
    using TIANCHI_PREPEND_NAMESPACE(name);

# define TIANCHI_MANGLE_NAMESPACE0(x) x
# define TIANCHI_MANGLE_NAMESPACE1(a, b) a##_##b
# define TIANCHI_MANGLE_NAMESPACE2(a, b) TIANCHI_MANGLE_NAMESPACE1(a,b)
# define TIANCHI_MANGLE_NAMESPACE(name) TIANCHI_MANGLE_NAMESPACE2( \
        TIANCHI_MANGLE_NAMESPACE0(name), TIANCHI_MANGLE_NAMESPACE0(TIANCHI_NAMESPACE))

namespace TIANCHI_NAMESPACE {}

#endif /* user namespace */


#define TIANCHI_BEGIN_HEADER
#define TIANCHI_END_HEADER

TIANCHI_BEGIN_HEADER
TIANCHI_BEGIN_NAMESPACE


#if defined(TIANCHI_SHARED) || !defined(TIANCHI_STATIC)
#  ifdef TIANCHI_STATIC
#    error "Both TIANCHI_SHARED and TIANCHI_STATIC defined, please make up your mind"
#  endif
#  ifndef TIANCHI_SHARED
#    define TIANCHI_SHARED
#  endif
#  if defined(TIANCHI_BUILD_LIB)
#    define TIANCHI_EXPORT Q_DECL_EXPORT
#  else
#    define TIANCHI_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define TIANCHI_EXPORT
#endif

TIANCHI_EXPORT const char *tianchiVersion() Q_DECL_NOTHROW;
TIANCHI_EXPORT bool tianchiSharedBuild() Q_DECL_NOTHROW;

TIANCHI_END_NAMESPACE
TIANCHI_END_HEADER

#define TIANCHI_API TIANCHI_EXPORT

#endif // TIANCHI_GLOBAL_H

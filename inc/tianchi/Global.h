// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵�������ù��ܺ���
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.11   cnhemiya    ����
// 2013.04.17   XChinux     ����Qt/qglobal.h�ļ���дGlobal.h
// ==========================================================================
// ע������:
// 1. ����Tianchi DLLʱ���� .pro ����ӣ�
//      DEFINES += TIANCHI_EXPORT
// 2. ʹ��Tianchi DLLʱ����.pro�����
//      DEFINES += TIANCHI_IMPORT
// ==========================================================================

#ifndef TIANCHI_GLOBAL_H
#define TIANCHI_GLOBAL_H


/**
 * TIANCHI_NAMESPACE Ӧ����.pro�ж���,��Ϊ�˷�ֹ���ֳ�ͻ,����ǿ�ƶ���
 */
#ifndef TIANCHI_NAMESPACE
/// @brief ����ع���Դ��⡷ͳһ�����ֿռ�(namespace)
#   define TIANCHI Tianchi
/// @brief ����ع���Դ��⡷ͳһ�����ֿռ�(namespace)
#   define TIANCHI_NAMESPACE Tianchi
#else
#   define TIANCHI TIANCHI_NAMESPACE
#endif


#include <QtCore/qglobal.h>

#ifndef __cplusplus
#    error "Tianchi library only support C++ Compilers"
#endif


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

#else /* user namespace */

# define TIANCHI_PREPEND_NAMESPACE(name) ::TIANCHI_NAMESPACE::name
# define TIANCHI_USE_NAMESPACE using namespace ::TIANCHI_NAMESPACE;
/// @brief ����ع���Դ��⡷ͳһ�����ֿռ�(namespace)��ʼ
# define TIANCHI_BEGIN_NAMESPACE namespace TIANCHI_NAMESPACE {
/// @brief ����ع���Դ��⡷ͳһ�����ֿռ�(namespace)����
# define TIANCHI_END_NAMESPACE }

namespace TIANCHI_NAMESPACE {}

#endif /* user namespace */


#if defined(TIANCHI_EXPORT)
#  define TIANCHI_API Q_DECL_EXPORT
#elif defined(TIANCHI_IMPORT)
#  define TIANCHI_API Q_DECL_IMPORT
#else
#  define TIANCHI_API
#endif


#endif // TIANCHI_GLOBAL_H

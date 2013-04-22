// ********************************************************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// ********************************************************************************************************************
// �ĵ�˵�����ļ��������ô�����
// ====================================================================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------------------------------------------------
// 2013.04.15   ʥ������    ����
//
// ====================================================================================================================
/// @file FileUtils.h �ļ��������ô�����
// ====================================================================================================================
#ifndef TIANCHI_FILEUTILS_H
#define TIANCHI_FILEUTILS_H

#include "Global.h"

#include <QString>

TIANCHI_BEGIN_NAMESPACE

/// @brief �ļ��������ô�����
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-15
class TIANCHI_API FileUtils
{
public:
    /// @brief װ���ı��ļ�
    static bool loadFromFile(QString& context, const QString& filename);

    /// @brief ��ָ��Ŀ¼�з���һ����ʱ�ļ���
    /// @return ������ʱ�ļ�����ע�ⲻ�������ļ�
    /// @note �˷��������Զ������ļ�
    static QString uniqueFileName(const QString& dir, const QString& fileTemplate, const QString& suffix="");

    /// @brief ȡִ���ļ��İ汾����֧�� Windows
    /// @param [in] exeFile �����汾��Ϣ���ļ���(.exe, .dll��)
    /// @return �汾��Ϣ(xxx.xxx.xxx.xxx)
    static QString fileVersion(const QString& exeFile);

    /// @brief ��Ŀ¼����Ŀ¼�м����������ļ���
    static QStringList searchFiles(const QString& path);
};

TIANCHI_END_NAMESPACE

#endif // TIANCHI_FILEUTILS_H

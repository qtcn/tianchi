// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵�����ļ��������ô�����
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.15   ʥ������    ����
// 2013.06.14   XChinux     ΪloadFromFile()��������codec����
// ==========================================================================
/// @file FileUtils.h �ļ��������ô�����
// ==========================================================================
#ifndef TIANCHI_TCFILE_H
#define TIANCHI_TCFILE_H

#include <tianchi/tcglobal.h>

#include <QString>

/// @brief �ļ��������ô�����
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-15
class TIANCHI_API TcFile
{
public:
    /// @brief װ���ı��ļ�,����codecָ����ȡ�ı���,��Ϊ��,��Ԥ��
    static bool loadFromFile(QString &context, const QString &filename, 
            const QString &codec = QString());

    /// @brief ��ָ��Ŀ¼�з���һ����ʱ�ļ���
    /// @return ������ʱ�ļ�����ע�ⲻ�������ļ�
    /// @note �˷��������Զ������ļ�
    static QString uniqueFileName(const QString &dir, 
            const QString &fileTemplate, const QString &suffix= QString());

    /// @brief ȡִ���ļ��İ汾����֧�� Windows
    /// @param [in] exeFile �����汾��Ϣ���ļ���(.exe, .dll��)
    /// @return �汾��Ϣ(xxx.xxx.xxx.xxx)
    static QString fileVersion(const QString& exeFile);

    /// @brief ��Ŀ¼����Ŀ¼�м����������ļ���
    static QStringList searchFiles(const QString& path);
};

#endif // TIANCHI_TCFILE_H

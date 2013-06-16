// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵���������ϵͳ���
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.10   ʥ������    ����
// 2013.06.16   XChinux     �޸�name()����,���Ӷ�ȡLinux���а�����
// ==========================================================================
/// @file OS.h �����ϵͳ���
#ifndef TIANCHI_TCOS_H
#define TIANCHI_TCOS_H

#include <tianchi/tcglobal.h>
#include <QString>

/// @brief �����ϵͳ��صĲ�����
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API TcOS
{
public:
    /// @brief ȡ����ϵͳ���ƣ�֧��Windows��Linux
    /// @note Windows��ע����л�ȡ,Linux�����δ�/etc�µ�os-release 
    ///       lsb-release, *-release�ļ���ȡ
    static QString name();

    /// @brief ȡ����ϵͳ�����ԣ���֧�� Windows
    /// @note ��֧�� Windows
    static QString language();

    /// @brief Windows ���û���¼����֧�� Windows
    /// @param [in] Domain Windows �����򱾻�������
    /// @param [in] UserID ���û����򱾻��û���
    /// @param [in] Password �û�����
    /// @return true ��¼�ɹ�
    /// @return false ��¼ʧ��
    /// @note ��֧�� Windows
    static bool login(const QString& Domain, const QString& UserID, 
            const QString& Password);
};

#endif // TIANCHI_TCOS_H

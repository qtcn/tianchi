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
//
// ==========================================================================
/// @file OS.h �����ϵͳ���
#ifndef TIANCHI_OS_H
#define TIANCHI_OS_H

#include <tianchi/Global.h>
#include <QString>

namespace Tianchi
{
/// @brief �����ϵͳ��صĲ�����
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API OS
{
public:
    /// @brief ȡ����ϵͳ���ƣ���֧�� Windows
    static QString name();

    /// @brief ȡ����ϵͳ�����ԣ���֧�� Windows
    static QString language();

    /// @brief Windows ���û���¼����֧�� Windows
    /// @param [in] Domain Windows �����򱾻�������
    /// @param [in] UserID ���û����򱾻��û���
    /// @param [in] Password �û�����
    /// @return true ��¼�ɹ�
    /// @return false ��¼ʧ��
    static bool login(const QString& Domain, const QString& UserID, 
            const QString& Password);
};
}

typedef ::Tianchi::OS TcOS;

#endif // TIANCHI_OS_H

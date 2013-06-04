// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵����Oracle ���Ӧ��
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.06.04   XChinux     ����
// 2013.06.04   XChinux     ����ODBCDSN()����
//
// ==========================================================================
/// @file MSSQL.h SQL Server ���Ӧ��
#ifndef TIANCHI_TCORACLE_H
#define TIANCHI_TCORACLE_H

#include <tianchi/tcglobal.h>
#include <QStringList>

/// @brief ��ȡ ODBC �����Ͱ汾��Ϣ
/// @author XChinux XChinux@163.com
/// @date 2013-04-18
class TIANCHI_API TcOracle
{
public:
    /// @brief ��ȡ ODBC �����Ͱ汾��Ϣ
    /// @date 2013-04-18
    /// @return  �� / �ָ��汾�ź���������:<br>
    ///     11.2.0.3/Oracle in instantclient_11_2<br>
    ///     11.2.0.2/Oracle in XE<br>
    static QStringList availableODBCDrivers();
    /// @brief  ����ODBC DSN�ַ���
    /// @date 2013-06-04
    /// @param  driver  ����ODBC��������
    /// @param  tns     TNS Service Name
    /// @param  user    �����û���
    /// @param  pass    ��������
    /// @return ����DSN�ַ���
    static QString ODBCDSN(const QString &driver,
            const QString &tns,
            const QString &user = QString(),
            const QString &pass = QString());
};

#endif

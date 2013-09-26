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
// 2013.04.10   ʥ������    ����
// 2013.09.25   XChinux     ����getLocationFromIP()����
//
// ==========================================================================
// @file tctils.h ���ù��ܺ���
// ==========================================================================
#ifndef TIANCHI_TCUTILS_H
#define TIANCHI_TCUTILS_H

#include <tianchi/tcglobal.h>

#ifdef QT_WIDGETS_LIB
    #include <QMessageBox>
#endif

#include <QTextCodec>
#include <QVariant>

#include <QDateTime>

#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QComboBox>

#include <QThread>

/// @brief ����ģʽ�ı�ʶ����
struct TcOperMode
{
const static int Append = 1; ///< ��ӻ��½�
const static int Change = 2; ///< �޸�
const static int Delete = 4; ///< ɾ��

const static int CopyCell   = 301; ///< ����һ����Ԫ��
const static int CopyCells  = 302; ///< ���ƶ����Ԫ��
const static int CopyColumn = 303; ///< ������
const static int CopyLine   = 304; ///< ������
const static int CopyTable  = 305; ///< ����һ�ű�Ĭ�ϱ�ʾ������
};

/// @brief ����С�����ۺϺ�����
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-10
class TIANCHI_API TcUtils
{
public:
    /// @brief �� key=value �ṹ���ı�ת��Ϊ map �ṹ
    static QHash<QString, QString> StringToMap(const QString& mapStrings);
    /// @brief �� key=value �ṹ���ı�ת��Ϊ map �ṹ
    static QHash<QString, QString> StringToMap(const QStringList& mapStrings);

    /// @brief ����ת�ַ�����
    static char typeFrom(QVariant::Type type);
    /// @brief ����ת�ַ�����
    static char typeFrom(const QVariant& v)
    {
        return typeFrom(v.type());
    }

    const static qint64 JULIAN_DAY = 2415019;
    /// @brief ת���ַ���Ϊ����ʱ��
    static QDateTime toDateTime(const QString& text);
    /// @brief ת������Ϊ����ʱ��
    static QDateTime toDateTime(double timeDouble);

    /// @brief ����18λ��λ֤�����һλУ����
    static char getIDCardVerifyCode(const QByteArray& id);

    /// @brief ȡ�������ں�ʱ�䣬���ô��Ĵ���������±���
    static QDateTime complieDateTime(const QString& complieDate, const QString& complieTime);

    static QByteArray addField(const QString& key, const QVariant& value);
    static QHash<QString, QByteArray> byFields(const QByteArray& fieldBytes);

    /// @brief  ʹ��qqwry.dat���IP��ַ��ȡ���ڵ�������
    /// @param  ip_addr         IP��ַ
    /// @param  qqwry_dat_file  qqwry.dat�ļ�·��
    /// @return                 ����IP��ַ���ڵ�������
    static QString getLocationFromIP(const QString &ip_addr, 
            const QString &qqwry_dat_file);
};

#endif // TIANCHI_UTILS_H

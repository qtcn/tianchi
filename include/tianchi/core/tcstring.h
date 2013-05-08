// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵�����ַ���������ǿ����չ
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.16   ʥ������    ����
//
// ==========================================================================
/// @file String.h �ַ���������ǿ����չ
#ifndef TIANCHI_TCSTRING_H
#define TIANCHI_TCSTRING_H

#include <tianchi/tcglobal.h>

#include <QString>
#include <QStringList>

/// @brief �ַ���������ǿ����չ
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-16
class TIANCHI_API TcString
{
public:
    TcString();

    /// @brief ��ȡ�ַ������ײ���
    /// @param [in,out] str ����ȡ���ַ���
    /// @param [in] split �ַ����ķָ���
    /// @return ��ȡ�����ַ���
    /// @note �ָ������������������ָ���ʱ��ȡ�����ַ���������ȡ���ַ��������޸�
    static QByteArray   first(QByteArray& str, const QByteArray& split="\t");

    /// @brief ���ַ��������в鵽һ���ַ���
    /// @note δ�����ܻ�ɾ��
    /// @see findOf
    static int find(const QStringList& ss, const QString& s);

    /// @brief ���ַ��������в鵽һ���ַ���
    /// @note δ�����ܻ�ɾ��
    /// @see find
    static int findOf(const QStringList& list, const QString& key);

    /// @brief �ж�һ���ַ����ĺϲ��������Ƿ������һ���ַ���������
    /// @param [in] findText ��Ҫ���ҵ����ַ���
    /// @param [in] filters �����ҵ��ַ�������
    /// @return true ����
    /// @return false ������
    static bool filter(const QString& findText, const QStringList& filters);

    /// @brief ��һ���ַ��������з���ָ�������е��ַ���
    /// @param [in] strings �ַ������У���"\n"��Ϊ�ָ�
    /// @param [in] index ��Ҫ���ص������У��� 0 ��ʼ
    /// @return �����е��ַ���������ֵԽ��ʱ���ؿ��ַ���
    static QString getTextByIndex(const char* strings, int index);

    /// @brief �ָ�����ȫ���е����ϡ����ֺ�Ӣ����
    static int  splitHumanName(QString full, QString& sur, QString& real, QString& english);

};

/// @brief �ַ�����������ǿ����չ
/// @author ʥ������ Jonix@qtcn.org
/// @date 2013-04-16
class TIANCHI_API TcStringList : public QStringList
{
public:
    TcStringList();
    /// @brief װ��һ���ı��ļ���ȫ������
    /// @param [in] fileName ·���ļ���
    /// @return true �����ɹ�
    bool loadFrom(const QString& fileName);
    /// @brief ���浱ǰ���ݵ�һ���ı��ļ���
    /// @param [in] fileName ·���ļ���
    /// @return true �����ɹ�
    bool saveTo(const QString& fileName);

    /// @brief �����ı��ļ����н�β��
    inline QString lineBreak() const
    {
        return m_lineBreak;
    }
    /// @brief �����ı��ļ����н�β��
    inline void lineBreak(const QString& value)
    {
        m_lineBreak = value;
    }

private:
    QString m_lineBreak;
};

#endif // TIANCHI_STRING_H

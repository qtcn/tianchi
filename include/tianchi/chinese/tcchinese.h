// **************************************************************************
// Tianchi share library for Qt (C++)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵���� ������ش���
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.04.15   ʥ������    ����
//
// ==========================================================================
/// @file Chinese.h ������ش���
#ifndef TIANCHI_TCCHINESE_H
#define TIANCHI_TCCHINESE_H

#include <tianchi/tcglobal.h>

#include <QString>

/// @brief ������ش�����
/// @note ��������� Windows ����Ч��ʹ��ʱ��Ҫ�� .pro �ļ��м��� LIB += -lole32
class TIANCHI_API TcChinese
{
public:
    /// ȡ�ö�����ֵ�����ĸ
    /// @param [in] HzString �����ַ���
    /// @return ÿ������ƴ�������ַ�
    /// @par ʾ��:
    /// @code
    /// qDebug()<<TIANCHI::Chinese::firstPinyins(QS("�л����񹲺͹�"));
    /// > zhrmghg
    ///
    /// qDebug()<<TIANCHI::Chinese::firstPinyins(QS("�л����Qt��̳ - www.qtcn.org"));
    /// > zhddlt
    ///
    /// @endcode
    static QString firstPinyins(const QString& HzString);

    /// ȡ�ö�����ֵ�ȫ��ƴ��
    /// @param [in] Str �����ַ���
    /// @param [in] Tonality ������ת����ƴ��
    /// @return ����ƴ��
    /// @par ʾ��:
    /// @code
    /// �����������
    /// qDebug()<<TIANCHI::Chinese::toPinyin(QS("�л����񹲺͹�"), true);
    /// > zh��nghu��r��nm��ng��ngh��gu��
    /// �������������
    ///
    /// qDebug()<<TIANCHI::Chinese::toPinyin(QS("�л����񹲺͹�"), false);
    /// > zhonghuarenmingongheguo
    ///
    /// qDebug()<<TIANCHI::Chinese::toPinyin(QS("�л����Qt��̳ - www.qtcn.org"));
    /// > zhonghuadadiluntan
    ///
    /// @endcode
    static QString toPinyin(const QString& Str, bool Tonality=false);

    /// ����ַ�ʱ��ת���в�����Ӣ�����ŵ�
    /// @param [in] Str �����ַ���
    /// @param [in] Tonality ������ת����ƴ��
    /// @return ���ֵ�����ĸ
    /// @par ʾ��:
    /// @code
    /// qDebug()<<TIANCHI::Chinese::toChars(QS("�л����Qt��̳ - www.qtcn.org"), true);
    /// > zh��nghu��d��d��Qtl��nt��n - www.qtcn.org
    ///
    /// qDebug()<<TIANCHI::Chinese::toChars(QS("�л����Qt��̳ - www.qtcn.org"));
    /// > zhonghuadadiQtluntan - www.qtcn.org
    ///
    /// @endcode
    static QString toChars(const QString& Str, bool Tonality=false);

    /// �������ַ���ΪӢ��
    /// @param [in] Str �����ַ���
    /// @param [in] style ʹ��Ӣ��ϰ�߼������ں�������ǰ
    /// @param [in] capitalization ����ֻ������ĸ��д
    /// @param [in] hyphenatedname ���Ǹ���
    /// @return ����Ӣ����ʽ
    /// @par ʾ��:
    /// @code
    /// qDebug()<<TIANCHI::Chinese::toEnglishName(QS("���"), true, false, false);
    /// > Haizhi Yang
    ///
    /// qDebug()<<TIANCHI::Chinese::toEnglishName(QS("���"), false, false, false);
    /// > Yang Haizhi
    ///
    /// qDebug()<<TIANCHI::Chinese::toEnglishName(QS("���"), true, true, false);
    /// > Haizhi YANG
    ///
    /// qDebug()<<TIANCHI::Chinese::toEnglishName(QS("�����"), true, false, true);
    /// > Liang Zhuge
    ///
    /// @endcode
    static QString toEnglishName(const QString& Str, bool style=false, bool capitalization=false,
        bool hyphenatedname= false);

};

#endif // TIANCHI_CHINESE_H

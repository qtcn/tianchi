// *****************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// *****************************************************************************
// �ĵ�˵���������ʹ�á�ģ���࣬���磺��������򿪵��ļ�
// =============================================================================
// ������־��
// ����         ��Ա        ˵��
// -----------------------------------------------------------------------------
// 2013-10-11   cnhemiya    ����
//
// =============================================================================
/// @file tcrecentuse.hpp
// =============================================================================
/// @brief "���ʹ��"ģ���࣬���磺��������򿪵��ļ���Ĭ�����10��
/// @author cnhemiya@gmail.com
/// @date 2013-10-11
/// @par ʾ��:
/// @code
/// int main()
/// {
///     TcRecentUse<int> ru;
///
///     for (int i=0; i<5; i++)
/// 	    ru.append(i);
///
///     for (int i = 0; i < ru.size(); i++)
///     {
/// 	    cout << ru[i] << endl;
///     }
///
///     cout << "Hello World!" << endl;
///     return 0;
/// }
/// @endcode

#ifndef TCRECENTUSE_HPP
#define TCRECENTUSE_HPP

#include <QList>

/// @brief �����ʹ�á�ģ����
/// @author cnhemiya
/// @date 2013-10-11
template<typename T> class TcRecentUse
{
public:
    /// @brief ʹ�õ�list����
    typedef QList<T> ListType;

    /// @brief TcRecentUse ���캯��
    /// @param ���������Ĭ��10��-1��������
    TcRecentUse(int n = 10): m_noMaxFlag(-1), m_defaultMax(10)
    {
        setMax(n);
    }

    /// @brief �������
    /// @param ����
    void append(const T &value)
    {
        checkFull();
        m_list.push_front(value);
    }

    /// @brief ɾ������
    /// @param ����
    void remove(const T &value)
    {
        m_list.removeOne(value);
    }

    /// @brief �������
    void clear()
    {
        m_list.clear();
    }

    /// @brief ���� m_list ������
    /// @return ListType ��������
    const ListType& list() const
    {
        return m_list;
    }

    /// @brief �Ѿ��洢��������
    /// @return �Ѿ��洢��������
    int size() const
    {
        return m_list.size();
    }

    /// @brief ���� m_max ������
    /// @return ���洢��������
    int max() const
    {
        return m_max;
    }

    /// @brief ���� m_max д����
    /// @param ���洢��������
    void setMax(int n)
    {
        m_max = n >= m_noMaxFlag ? n : m_defaultMax;
        checkFull();
    }

    /// @brief ��ȡλ��Ϊ i �ĳ�������
    /// @param ��ȡλ��
    /// @return ��ȡλ��Ϊ i ������
    const T& at(int i) const
    {
        return m_list[i];
    }

    /// @brief ��ȡλ��Ϊ i ������
    /// @param ��ȡλ��
    /// @return ��ȡλ��Ϊ i ������
    T& at(int i)
    {
        return m_list[i];
    }

    /// @brief ��ȡλ��Ϊ i �ĳ������ݣ�operator [] ���������
    /// @param ��ȡλ��
    /// @return ��ȡλ��Ϊ i ������
    const T& operator [](int i) const
    {
        return m_list[i];
    }

    /// @brief ��ȡλ��Ϊ i �����ݣ�operator [] ���������
    /// @param ��ȡλ��
    /// @return ��ȡλ��Ϊ i ������
    T& operator [](int i)
    {
        return m_list[i];
    }

private:
    /// @brief ��� m_list.size() �Ƿ񳬹� m_max �趨
    void checkFull()
    {
        if (m_max != m_noMaxFlag)
        {
            while (m_max <= m_list.size())
            {
                m_list.pop_back();
            }
        }
    }

    /// @brief ���� m_list ��Ҫ�Ǵ洢����
    ListType m_list;

    /// @brief ���洢����
    int m_max;

    /// @brief �����Ʊ�ǣ�-1
    const int m_noMaxFlag;

    /// @brief Ĭ�����������10
    const int m_defaultMax;
};

#endif // TCRECENTUSE_HPP

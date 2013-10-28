// *****************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// *****************************************************************************
// 文档说明：“最近使用”模版类，例如：用于最近打开的文件
// =============================================================================
// 开发日志：
// 日期         人员        说明
// -----------------------------------------------------------------------------
// 2013-10-11   cnhemiya    建立
//
// =============================================================================
/// @file tcrecentuse.hpp
// =============================================================================
/// @brief "最近使用"模版类，例如：用于最近打开的文件，默认最大10个
/// @author cnhemiya@gmail.com
/// @date 2013-10-11
/// @par 示例:
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

#ifndef TIANCHI_TCRECENTUSE_HPP
#define TIANCHI_TCRECENTUSE_HPP

#include <QList>

/// @brief “最近使用”模版类
/// @author cnhemiya
/// @date 2013-10-11
template<typename T> class TcRecentUse
{
public:
    /// @brief 使用的list类型
    typedef QList<T> ListType;

    /// @brief TcRecentUse 构造函数
    /// @param 最大数量，默认10，-1是无限制
    TcRecentUse(int n = 10): m_noMaxFlag(-1), m_defaultMax(10)
    {
        setMax(n);
    }

    /// @brief 添加数据
    /// @param 数据
    void append(const T &value)
    {
        checkFull();
        m_list.push_front(value);
    }

    /// @brief 删除数据
    /// @param 数据
    void remove(const T &value)
    {
        m_list.removeOne(value);
    }

    /// @brief 清空数据
    void clear()
    {
        m_list.clear();
    }

    /// @brief 属性 m_list 读函数
    /// @return ListType 类型链表
    const ListType& list() const
    {
        return m_list;
    }

    /// @brief 已经存储多少数据
    /// @return 已经存储多少数据
    int size() const
    {
        return m_list.size();
    }

    /// @brief 属性 m_max 读函数
    /// @return 最大存储多少数据
    int max() const
    {
        return m_max;
    }

    /// @brief 属性 m_max 写函数
    /// @param 最大存储多少数据
    void setMax(int n)
    {
        m_max = n >= m_noMaxFlag ? n : m_defaultMax;
        checkFull();
    }

    /// @brief 读取位置为 i 的常量数据
    /// @param 读取位置
    /// @return 读取位置为 i 的数据
    const T& at(int i) const
    {
        return m_list[i];
    }

    /// @brief 读取位置为 i 的数据
    /// @param 读取位置
    /// @return 读取位置为 i 的数据
    T& at(int i)
    {
        return m_list[i];
    }

    /// @brief 读取位置为 i 的常量数据，operator [] 运算符重载
    /// @param 读取位置
    /// @return 读取位置为 i 的数据
    const T& operator [](int i) const
    {
        return m_list[i];
    }

    /// @brief 读取位置为 i 的数据，operator [] 运算符重载
    /// @param 读取位置
    /// @return 读取位置为 i 的数据
    T& operator [](int i)
    {
        return m_list[i];
    }

private:
    /// @brief 检查 m_list.size() 是否超过 m_max 设定
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

    /// @brief 属性 m_list 主要是存储数据
    ListType m_list;

    /// @brief 最大存储数量
    int m_max;

    /// @brief 无限制标记，-1
    const int m_noMaxFlag;

    /// @brief 默认最大数量，10
    const int m_defaultMax;
};

#endif // TC_TCRECENTUSE_HPP

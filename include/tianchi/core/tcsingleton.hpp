// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵������ָ��ʵ�ֵĵ���ģʽ��ģ����
// ==========================================================================
// ������־��
// ����         ��Ա                   ˵��
// --------------------------------------------------------------------------
// 2013.05.25   cnhemiya@gmail.com    ����
//
// ==========================================================================
/// @file tcsingleton.hpp ��ָ��ʵ�ֵĵ���ģʽ��ģ����
// ==========================================================================
/// @brief ��ָ��ʵ�ֵĵ���ģʽ��ģ����
/// @author cnhemiya@gmail.com
/// @date 2013-05-25
/// @par ʾ��:
/// @code
/// .h�ļ�
///
/// class demo
/// {
/// public:
/// 	int value;
/// }
///
/// typedef TcSingleton<demo> demo_singleton;
///
/// .cpp�ļ�
///
/// ��ʼ����
/// TC_SINGLETON_INIT(demo)
/// @endcode

#ifndef TIANCHI_TCSINGLETON_HPP
#define TIANCHI_TCSINGLETON_HPP

#include <cassert>

template<typename T>
class TcSingleton
{
	typedef TcSingleton<T> this_type;

public:
	/// @brief ���캯��
	TcSingleton()
	{
		if (m_count == 0)
			m_pointer = new T;

		++m_count;
	}

	/// @brief ���캯��
	TcSingleton(const this_type &)
	{
		++m_count;
	}

	/// @brief ��������
	~TcSingleton()
	{
		--m_count;

		if (m_count == 0)
		{
			delete m_pointer;
			m_pointer = 0;
		}
	}

	/// @brief ���� T *
	inline T * get() const
	{
		assert(m_pointer != 0);
		return m_pointer;
	}

	/// @brief operator *
	inline const T & operator *() const
	{
		assert(m_pointer != 0);
		return *m_pointer;
	}

	/// @brief operator ->
	inline T * operator ->() const
	{
		assert(m_pointer != 0);
		return m_pointer;
	}

	/// @brief operator =
	inline this_type & operator =(const this_type &)
	{
		return *this;
	}

private:
	static T *m_pointer;
	static int m_count;
};

/// @brief ��ʼ����
#define TC_SINGLETON_INIT(__t) \
template<> int TcSingleton< __t >::m_count = 0; \
template<> __t * TcSingleton< __t >::m_pointer = 0;


#endif // TIANCHI_TCSINGLETON_HPP

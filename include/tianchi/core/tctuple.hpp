// **************************************************************************
// Tianchi C++ library for Qt (open source)
// 天池共享源码库
// 版权所有 (C) 天池共享源码库开发组
// 授权协议：请阅读天池共享源码库附带的授权协议
// **************************************************************************
// 文档说明：简单的 Tuple(元组) 模版类, 提供2~10个类型参数的模版
// ==========================================================================
// 开发日志：
// 日期         人员                   说明
// --------------------------------------------------------------------------
// 2013.05.25   cnhemiya@gmail.com    建立
//
// ==========================================================================
/// @file tctuple.hpp 简单的 Tuple(元组) 模版类, 提供2~10个类型参数的模版
// ==========================================================================
/// @brief 简单的 Tuple(元组) 模版类, 提供2~10个类型参数的模版
/// @author cnhemiya@gmail.com
/// @date 2013-05-25
/// @par 示例:
/// @code
/// int main()
/// {
///		TcTuple<int, double> demo;
///		demo.set0(99);
///		demo.set1(3.14);
///		cout << demo.get0() << endl;
///		cout << demo.get1() << endl;
/// }
/// @endcode

#ifndef TIANCHI_TCTUPLE_HPP
#define TIANCHI_TCTUPLE_HPP


namespace _tc_tuple_ns_
{

class null_type{ /* none */ };

}

template<typename T0 = _tc_tuple_ns_::null_type,
		 typename T1 = _tc_tuple_ns_::null_type,
		 typename T2 = _tc_tuple_ns_::null_type,
		 typename T3 = _tc_tuple_ns_::null_type,
		 typename T4 = _tc_tuple_ns_::null_type,
		 typename T5 = _tc_tuple_ns_::null_type,
		 typename T6 = _tc_tuple_ns_::null_type,
		 typename T7 = _tc_tuple_ns_::null_type,
		 typename T8 = _tc_tuple_ns_::null_type,
		 typename T9 = _tc_tuple_ns_::null_type>
class TcTuple;

template<typename T0, typename T1>
class TcTuple<T0, T1,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type>
{
	typedef TcTuple<T0, T1> this_type;

public:
	TcTuple(){ /* none */ }

	TcTuple(const T0 &v0, const T1 &v1)
	{
		set(v0, v1);
	}

	TcTuple(const this_type &ref)
	{
		set(ref);
	}

	inline const this_type & operator =(const this_type &ref)
	{
		set(ref);
		return *this;
	}

	inline bool operator ==(const this_type &ref) const
	{
		return ((m_v0 == ref.m_v0) &&
				 (m_v1 == ref.m_v1));
	}

	inline bool operator !=(const this_type &ref) const
	{
		return !((*this) == ref);
	}

	inline void set(const this_type &ref)
	{
		set(ref.m_v0, ref.m_v1);
	}

	inline void set(const T0 &v0, const T1 &v1)
	{
		m_v0 = v0;
		m_v1 = v1;
	}

	inline void set0(const T0 &v0)
	{
		m_v0 = v0;
	}

	inline T0 & get0()
	{
		return m_v0;
	}

	inline void set1(const T1 &v1)
	{
		m_v1 = v1;
	}

	inline T1 & get1()
	{
		return m_v1;
	}

private:
	T0 m_v0;
	T1 m_v1;
};


template<typename T0, typename T1, typename T2>
class TcTuple<T0, T1, T2,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type>
{
	typedef TcTuple<T0, T1, T2> this_type;

public:
	TcTuple(){ /* none */ }

	TcTuple(const T0 &v0, const T1 &v1, const T2 &v2)
	{
		set(v0, v1, v2);
	}

	TcTuple(const this_type &ref)
	{
		set(ref);
	}

	inline const this_type & operator =(const this_type &ref)
	{
		set(ref);
		return *this;
	}

	inline bool operator ==(const this_type &ref) const
	{
		return ((m_v0 == ref.m_v0) &&
				(m_v1 == ref.m_v1) &&
				(m_v2 == ref.m_v2));
	}

	inline bool operator !=(const this_type &ref) const
	{
		return !((*this) == ref);
	}

	inline void set(const this_type &ref)
	{
		set(ref.m_v0, ref.m_v1, ref.m_v2);
	}

	inline void set(const T0 &v0, const T1 &v1, const T2 &v2)
	{
		m_v0 = v0;
		m_v1 = v1;
		m_v2 = v2;
	}

	inline void set0(const T0 &v0)
	{
		m_v0 = v0;
	}

	inline const T0 & get0() const
	{
		return m_v0;
	}

	inline void set1(const T1 &v1)
	{
		m_v1 = v1;
	}

	inline const T1 & get1() const
	{
		return m_v1;
	}

	inline void set2(const T2 &v2)
	{
		m_v2 = v2;
	}

	inline const T2 & get2() const
	{
		return m_v2;
	}

private:
	T0 m_v0;
	T1 m_v1;
	T2 m_v2;
};


template<typename T0, typename T1, typename T2, typename T3>
class TcTuple<T0, T1, T2, T3,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type>
{
	typedef TcTuple<T0, T1, T2, T3> this_type;

public:
	TcTuple(){ /* none */ }

	TcTuple(const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3)
	{
		set(v0, v1, v2, v3);
	}

	TcTuple(const this_type &ref)
	{
		set(ref);
	}

	inline const this_type & operator =(const this_type &ref)
	{
		set(ref);
		return *this;
	}

	inline bool operator ==(const this_type &ref) const
	{
		return ((m_v0 == ref.m_v0) &&
				(m_v1 == ref.m_v1) &&
				(m_v2 == ref.m_v2) &&
				(m_v3 == ref.m_v3));
	}

	inline bool operator !=(const this_type &ref) const
	{
		return !((*this) == ref);
	}

	inline void set(const this_type &ref)
	{
		set(ref.m_v0, ref.m_v1, ref.m_v2, ref.m_v3);
	}

	inline void set(const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3)
	{
		m_v0 = v0;
		m_v1 = v1;
		m_v2 = v2;
		m_v3 = v3;
	}

	inline void set0(const T0 &v0)
	{
		m_v0 = v0;
	}

	inline const T0 & get0() const
	{
		return m_v0;
	}

	inline void set1(const T1 &v1)
	{
		m_v1 = v1;
	}

	inline const T1 & get1() const
	{
		return m_v1;
	}

	inline void set2(const T2 &v2)
	{
		m_v2 = v2;
	}

	inline const T2 & get2() const
	{
		return m_v2;
	}

	inline void set3(const T3 &v3)
	{
		m_v3 = v3;
	}

	inline const T3 & get3() const
	{
		return m_v3;
	}

private:
	T0 m_v0;
	T1 m_v1;
	T2 m_v2;
	T3 m_v3;
};


template<typename T0, typename T1, typename T2, typename T3,
		 typename T4>
class TcTuple<T0, T1, T2, T3, T4,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type>
{
	typedef TcTuple<T0, T1, T2, T3, T4> this_type;

public:
	TcTuple(){ /* none */ }

	TcTuple(const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4)
	{
		set(v0, v1, v2, v3, v4);
	}

	TcTuple(const this_type &ref)
	{
		set(ref);
	}

	inline const this_type & operator =(const this_type &ref)
	{
		set(ref);
		return *this;
	}

	inline bool operator ==(const this_type &ref) const
	{
		return ((m_v0 == ref.m_v0) &&
				(m_v1 == ref.m_v1) &&
				(m_v2 == ref.m_v2) &&
				(m_v3 == ref.m_v3) &&
				(m_v4 == ref.m_v4));
	}

	inline bool operator !=(const this_type &ref) const
	{
		return !((*this) == ref);
	}

	inline void set(const this_type &ref)
	{
		set(ref.m_v0, ref.m_v1, ref.m_v2, ref.m_v3, ref.m_v4);
	}

	inline void set(const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3,
					const T4 &v4)
	{
		m_v0 = v0;
		m_v1 = v1;
		m_v2 = v2;
		m_v3 = v3;
		m_v4 = v4;
	}

	inline void set0(const T0 &v0)
	{
		m_v0 = v0;
	}

	inline const T0 & get0() const
	{
		return m_v0;
	}

	inline void set1(const T1 &v1)
	{
		m_v1 = v1;
	}

	inline const T1 & get1() const
	{
		return m_v1;
	}

	inline void set2(const T2 &v2)
	{
		m_v2 = v2;
	}

	inline const T2 & get2() const
	{
		return m_v2;
	}

	inline void set3(const T3 &v3)
	{
		m_v3 = v3;
	}

	inline const T3 & get3() const
	{
		return m_v3;
	}

	inline void set4(const T4 &v4)
	{
		m_v4 = v4;
	}

	inline const T4 & get4() const
	{
		return m_v4;
	}

private:
	T0 m_v0;
	T1 m_v1;
	T2 m_v2;
	T3 m_v3;
	T4 m_v4;
};


template<typename T0, typename T1, typename T2, typename T3,
		 typename T4, typename T5>
class TcTuple<T0, T1, T2, T3, T4, T5,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type>
{
	typedef TcTuple<T0, T1, T2, T3, T4, T5> this_type;

public:
	TcTuple(){ /* none */ }

	TcTuple(const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4,
		  const T5 &v5)
	{
		set(v0, v1, v2, v3, v4, v5);
	}

	TcTuple(const this_type &ref)
	{
		set(ref);
	}

	inline const this_type & operator =(const this_type &ref)
	{
		set(ref);
		return *this;
	}

	inline bool operator ==(const this_type &ref) const
	{
		return ((m_v0 == ref.m_v0) &&
				(m_v1 == ref.m_v1) &&
				(m_v2 == ref.m_v2) &&
				(m_v3 == ref.m_v3) &&
				(m_v4 == ref.m_v4) &&
				(m_v5 == ref.m_v5));
	}

	inline bool operator !=(const this_type &ref) const
	{
		return !((*this) == ref);
	}

	inline void set(const this_type &ref)
	{
		set(ref.m_v0, ref.m_v1, ref.m_v2, ref.m_v3, ref.m_v4, ref.m_v5);
	}

	inline void set(const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3,
					const T4 &v4, const T5 &v5)
	{
		m_v0 = v0;
		m_v1 = v1;
		m_v2 = v2;
		m_v3 = v3;
		m_v4 = v4;
		m_v5 = v5;
	}

	inline void set0(const T0 &v0)
	{
		m_v0 = v0;
	}

	inline const T0 & get0() const
	{
		return m_v0;
	}

	inline void set1(const T1 &v1)
	{
		m_v1 = v1;
	}

	inline const T1 & get1() const
	{
		return m_v1;
	}

	inline void set2(const T2 &v2)
	{
		m_v2 = v2;
	}

	inline const T2 & get2() const
	{
		return m_v2;
	}

	inline void set3(const T3 &v3)
	{
		m_v3 = v3;
	}

	inline const T3 & get3() const
	{
		return m_v3;
	}

	inline void set4(const T4 &v4)
	{
		m_v4 = v4;
	}

	inline const T4 & get4() const
	{
		return m_v4;
	}

	inline void set5(const T5 &v5)
	{
		m_v5 = v5;
	}

	inline const T5 & get5() const
	{
		return m_v5;
	}

private:
	T0 m_v0;
	T1 m_v1;
	T2 m_v2;
	T3 m_v3;
	T4 m_v4;
	T5 m_v5;
};


template<typename T0, typename T1, typename T2, typename T3,
		 typename T4, typename T5, typename T6>
class TcTuple<T0, T1, T2, T3, T4, T5, T6,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type>
{
	typedef TcTuple<T0, T1, T2, T3, T4, T5, T6> this_type;

public:
	TcTuple(){ /* none */ }

	TcTuple(const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4,
		  const T5 &v5, const T6 &v6)
	{
		set(v0, v1, v2, v3, v4, v5, v6);
	}

	TcTuple(const this_type &ref)
	{
		set(ref);
	}

	inline const this_type & operator =(const this_type &ref)
	{
		set(ref);
		return *this;
	}

	inline bool operator ==(const this_type &ref) const
	{
		return ((m_v0 == ref.m_v0) &&
				(m_v1 == ref.m_v1) &&
				(m_v2 == ref.m_v2) &&
				(m_v3 == ref.m_v3) &&
				(m_v4 == ref.m_v4) &&
				(m_v5 == ref.m_v5) &&
				(m_v6 == ref.m_v6));
	}

	inline bool operator !=(const this_type &ref) const
	{
		return !((*this) == ref);
	}

	inline void set(const this_type &ref)
	{
		set(ref.m_v0, ref.m_v1, ref.m_v2, ref.m_v3, ref.m_v4,
			ref.m_v5, ref.m_v6);
	}

	inline void set(const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3,
					const T4 &v4, const T5 &v5, const T6 &v6)
	{
		m_v0 = v0;
		m_v1 = v1;
		m_v2 = v2;
		m_v3 = v3;
		m_v4 = v4;
		m_v5 = v5;
		m_v6 = v6;
	}

	inline void set0(const T0 &v0)
	{
		m_v0 = v0;
	}

	inline const T0 & get0() const
	{
		return m_v0;
	}

	inline void set1(const T1 &v1)
	{
		m_v1 = v1;
	}

	inline const T1 & get1() const
	{
		return m_v1;
	}

	inline void set2(const T2 &v2)
	{
		m_v2 = v2;
	}

	inline const T2 & get2() const
	{
		return m_v2;
	}

	inline void set3(const T3 &v3)
	{
		m_v3 = v3;
	}

	inline const T3 & get3() const
	{
		return m_v3;
	}

	inline void set4(const T4 &v4)
	{
		m_v4 = v4;
	}

	inline const T4 & get4() const
	{
		return m_v4;
	}

	inline void set5(const T5 &v5)
	{
		m_v5 = v5;
	}

	inline const T5 & get5() const
	{
		return m_v5;
	}

	inline void set6(const T6 &v6)
	{
		m_v6 = v6;
	}

	inline const T6 & get6() const
	{
		return m_v6;
	}

private:
	T0 m_v0;
	T1 m_v1;
	T2 m_v2;
	T3 m_v3;
	T4 m_v4;
	T5 m_v5;
	T6 m_v6;
};


template<typename T0, typename T1, typename T2, typename T3,
		 typename T4, typename T5, typename T6, typename T7>
class TcTuple<T0, T1, T2, T3, T4, T5, T6, T7,
		_tc_tuple_ns_::null_type,
		_tc_tuple_ns_::null_type>
{
	typedef TcTuple<T0, T1, T2, T3, T4, T5, T6, T7> this_type;

public:
	TcTuple(){ /* none */ }

	TcTuple(const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4,
		  const T5 &v5, const T6 &v6, const T7 &v7)
	{
		set(v0, v1, v2, v3, v4, v5, v6, v7);
	}

	TcTuple(const this_type &ref)
	{
		set(ref);
	}

	inline const this_type & operator =(const this_type &ref)
	{
		set(ref);
		return *this;
	}

	inline bool operator ==(const this_type &ref) const
	{
		return ((m_v0 == ref.m_v0) &&
				(m_v1 == ref.m_v1) &&
				(m_v2 == ref.m_v2) &&
				(m_v3 == ref.m_v3) &&
				(m_v4 == ref.m_v4) &&
				(m_v5 == ref.m_v5) &&
				(m_v6 == ref.m_v6) &&
				(m_v7 == ref.m_v7));
	}

	inline bool operator !=(const this_type &ref) const
	{
		return !((*this) == ref);
	}

	inline void set(const this_type &ref)
	{
		set(ref.m_v0, ref.m_v1, ref.m_v2, ref.m_v3, ref.m_v4,
			ref.m_v5, ref.m_v6, ref.m_v7);
	}

	inline void set(const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3,
					const T4 &v4, const T5 &v5, const T6 &v6, const T7 &v7)
	{
		m_v0 = v0;
		m_v1 = v1;
		m_v2 = v2;
		m_v3 = v3;
		m_v4 = v4;
		m_v5 = v5;
		m_v6 = v6;
		m_v7 = v7;
	}

	inline void set0(const T0 &v0)
	{
		m_v0 = v0;
	}

	inline const T0 & get0() const
	{
		return m_v0;
	}

	inline void set1(const T1 &v1)
	{
		m_v1 = v1;
	}

	inline const T1 & get1() const
	{
		return m_v1;
	}

	inline void set2(const T2 &v2)
	{
		m_v2 = v2;
	}

	inline const T2 & get2() const
	{
		return m_v2;
	}

	inline void set3(const T3 &v3)
	{
		m_v3 = v3;
	}

	inline const T3 & get3() const
	{
		return m_v3;
	}

	inline void set4(const T4 &v4)
	{
		m_v4 = v4;
	}

	inline const T4 & get4() const
	{
		return m_v4;
	}

	inline void set5(const T5 &v5)
	{
		m_v5 = v5;
	}

	inline const T5 & get5() const
	{
		return m_v5;
	}

	inline void set6(const T6 &v6)
	{
		m_v6 = v6;
	}

	inline const T6 & get6() const
	{
		return m_v6;
	}

	inline void set7(const T7 &v7)
	{
		m_v7 = v7;
	}

	inline const T7 & get7() const
	{
		return m_v7;
	}

private:
	T0 m_v0;
	T1 m_v1;
	T2 m_v2;
	T3 m_v3;
	T4 m_v4;
	T5 m_v5;
	T6 m_v6;
	T7 m_v7;
};


template<typename T0, typename T1, typename T2, typename T3,
		 typename T4, typename T5, typename T6, typename T7,
		 typename T8>
class TcTuple<T0, T1, T2, T3, T4, T5, T6, T7, T8,
		_tc_tuple_ns_::null_type>
{
	typedef TcTuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> this_type;

public:
	TcTuple(){ /* none */ }

	TcTuple(const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4,
		  const T5 &v5, const T6 &v6, const T7 &v7, const T8 &v8)
	{
		set(v0, v1, v2, v3, v4, v5, v6, v7, v8);
	}

	TcTuple(const this_type &ref)
	{
		set(ref);
	}

	inline const this_type & operator =(const this_type &ref)
	{
		set(ref);
		return *this;
	}

	inline bool operator ==(const this_type &ref) const
	{
		return ((m_v0 == ref.m_v0) &&
				(m_v1 == ref.m_v1) &&
				(m_v2 == ref.m_v2) &&
				(m_v3 == ref.m_v3) &&
				(m_v4 == ref.m_v4) &&
				(m_v5 == ref.m_v5) &&
				(m_v6 == ref.m_v6) &&
				(m_v7 == ref.m_v7) &&
				(m_v8 == ref.m_v8));
	}

	inline bool operator !=(const this_type &ref) const
	{
		return !((*this) == ref);
	}

	inline void set(const this_type &ref)
	{
		set(ref.m_v0, ref.m_v1, ref.m_v2, ref.m_v3, ref.m_v4,
			ref.m_v5, ref.m_v6, ref.m_v7, ref.m_v8);
	}

	inline void set(const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3,
					const T4 &v4, const T5 &v5, const T6 &v6, const T7 &v7,
					const T8 &v8)
	{
		m_v0 = v0;
		m_v1 = v1;
		m_v2 = v2;
		m_v3 = v3;
		m_v4 = v4;
		m_v5 = v5;
		m_v6 = v6;
		m_v7 = v7;
		m_v8 = v8;
	}

	inline void set0(const T0 &v0)
	{
		m_v0 = v0;
	}

	inline const T0 & get0() const
	{
		return m_v0;
	}

	inline void set1(const T1 &v1)
	{
		m_v1 = v1;
	}

	inline const T1 & get1() const
	{
		return m_v1;
	}

	inline void set2(const T2 &v2)
	{
		m_v2 = v2;
	}

	inline const T2 & get2() const
	{
		return m_v2;
	}

	inline void set3(const T3 &v3)
	{
		m_v3 = v3;
	}

	inline const T3 & get3() const
	{
		return m_v3;
	}

	inline void set4(const T4 &v4)
	{
		m_v4 = v4;
	}

	inline const T4 & get4() const
	{
		return m_v4;
	}

	inline void set5(const T5 &v5)
	{
		m_v5 = v5;
	}

	inline const T5 & get5() const
	{
		return m_v5;
	}

	inline void set6(const T6 &v6)
	{
		m_v6 = v6;
	}

	inline const T6 & get6() const
	{
		return m_v6;
	}

	inline void set7(const T7 &v7)
	{
		m_v7 = v7;
	}

	inline const T7 & get7() const
	{
		return m_v7;
	}

	inline void set8(const T8 &v8)
	{
		m_v8 = v8;
	}

	inline const T8 & get8() const
	{
		return m_v8;
	}

private:
	T0 m_v0;
	T1 m_v1;
	T2 m_v2;
	T3 m_v3;
	T4 m_v4;
	T5 m_v5;
	T6 m_v6;
	T7 m_v7;
	T8 m_v8;
};

template<typename T0, typename T1, typename T2, typename T3,
		 typename T4, typename T5, typename T6, typename T7,
		 typename T8, typename T9>
class TcTuple
{
	typedef TcTuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> this_type;

public:
	TcTuple(){ /* none */ }

	TcTuple(const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4,
		  const T5 &v5, const T6 &v6, const T7 &v7, const T8 &v8, const T9 &v9)
	{
		set(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
	}

	TcTuple(const this_type &ref)
	{
		set(ref);
	}

	inline const this_type & operator =(const this_type &ref)
	{
		set(ref);
		return *this;
	}

	inline bool operator ==(const this_type &ref) const
	{
		return ((m_v0 == ref.m_v0) &&
				(m_v1 == ref.m_v1) &&
				(m_v2 == ref.m_v2) &&
				(m_v3 == ref.m_v3) &&
				(m_v4 == ref.m_v4) &&
				(m_v5 == ref.m_v5) &&
				(m_v6 == ref.m_v6) &&
				(m_v7 == ref.m_v7) &&
				(m_v8 == ref.m_v8) &&
				(m_v9 == ref.m_v9));
	}

	inline bool operator !=(const this_type &ref) const
	{
		return !((*this) == ref);
	}

	inline void set(const this_type &ref)
	{
		set(ref.m_v0, ref.m_v1, ref.m_v2, ref.m_v3, ref.m_v4,
			ref.m_v5, ref.m_v6, ref.m_v7, ref.m_v8, ref.m_v9);
	}

	inline void set(const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3,
					const T4 &v4, const T5 &v5, const T6 &v6, const T7 &v7,
					const T8 &v8, const T9 &v9)
	{
		m_v0 = v0;
		m_v1 = v1;
		m_v2 = v2;
		m_v3 = v3;
		m_v4 = v4;
		m_v5 = v5;
		m_v6 = v6;
		m_v7 = v7;
		m_v8 = v8;
		m_v9 = v9;
	}

	inline void set0(const T0 &v0)
	{
		m_v0 = v0;
	}

	inline const T0 & get0() const
	{
		return m_v0;
	}

	inline void set1(const T1 &v1)
	{
		m_v1 = v1;
	}

	inline const T1 & get1() const
	{
		return m_v1;
	}

	inline void set2(const T2 &v2)
	{
		m_v2 = v2;
	}

	inline const T2 & get2() const
	{
		return m_v2;
	}

	inline void set3(const T3 &v3)
	{
		m_v3 = v3;
	}

	inline const T3 & get3() const
	{
		return m_v3;
	}

	inline void set4(const T4 &v4)
	{
		m_v4 = v4;
	}

	inline const T4 & get4() const
	{
		return m_v4;
	}

	inline void set5(const T5 &v5)
	{
		m_v5 = v5;
	}

	inline const T5 & get5() const
	{
		return m_v5;
	}

	inline void set6(const T6 &v6)
	{
		m_v6 = v6;
	}

	inline const T6 & get6() const
	{
		return m_v6;
	}

	inline void set7(const T7 &v7)
	{
		m_v7 = v7;
	}

	inline const T7 & get7() const
	{
		return m_v7;
	}

	inline void set8(const T8 &v8)
	{
		m_v8 = v8;
	}

	inline const T8 & get8() const
	{
		return m_v8;
	}

	inline void set9(const T9 &v9)
	{
		m_v9 = v9;
	}

	inline const T9 & get9() const
	{
		return m_v9;
	}

private:
	T0 m_v0;
	T1 m_v1;
	T2 m_v2;
	T3 m_v3;
	T4 m_v4;
	T5 m_v5;
	T6 m_v6;
	T7 m_v7;
	T8 m_v8;
	T9 m_v9;
};


#endif // TIANCHI_TCTUPLE_HPP

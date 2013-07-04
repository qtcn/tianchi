// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵���������־�ȷ����math���װ,bc��ͷ�ĺ�������bcmath��
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.07.04   XChinux     ����
//
// ==========================================================================
/// @file tcmath.h
// ==========================================================================
#ifndef TIANCHI_TCMATH_H
#define TIANCHI_TCMATH_H

#include <tianchi/tcglobal.h>
#include <string>
#include <QString>

class TIANCHI_API TcMath
{
public:
    /// @brief  Returns the sum of two arbitrary precision numbers
    static inline std::string bcadd(const std::string &left, 
            const std::string &right, int scale = -1);

    /// @brief  Returns the difference between two arbitrary precision numbers
    static inline std::string bcsub(const std::string &left, 
            const std::string &right, int scale = -1);

    /// @brief  Returns the multiplication of two arbitrary precision numbers
    static inline std::string bcmul(const std::string &left, 
            const std::string &right, int scale = -1);

    /// @brief  Returns the quotient of two arbitrary precision numbers 
    ///         (division)
    static inline std::string bcdiv(const std::string &left, 
            const std::string &right, int scale = -1);

    /// @brief  Returns the modulus of the two arbitrary precision operands
    static inline std::string bcmod(const std::string &left, 
            const std::string &right);

    /// @brief  Returns the value of an arbitrary precision number raised 
    ///         to the power of another reduced by a modulous
    static inline std::string bcpowmod(const std::string &left, 
            const std::string &right, const std::string &mod, int scale = -1);

    /// @brief  Returns the value of an arbitrary precision number raised 
    ///         to the power of another
    static inline std::string bcpow(const std::string &left, 
            const std::string &right, int scale = -1);

    /// @brief  Returns the square root of an arbitray precision number
    static inline std::string bcsqrt(const std::string &left, int scale = -1);

    /// @brief  Compares two arbitrary precision numbers
    static inline int bccomp(const std::string &left, const std::string &right, 
            int scale = -1);

    /// @brief  Sets default scale parameter for all bc math functions
    static inline bool bcscale(int scale);





    /// @brief  Returns the sum of two arbitrary precision numbers
    static inline QString bcadd(const QString &left, 
            const QString &right, int scale = -1);

    /// @brief  Returns the difference between two arbitrary precision numbers
    static inline QString bcsub(const QString &left, 
            const QString &right, int scale = -1);

    /// @brief  Returns the multiplication of two arbitrary precision numbers
    static inline QString bcmul(const QString &left, 
            const QString &right, int scale = -1);

    /// @brief  Returns the quotient of two arbitrary precision numbers 
    ///         (division)
    static inline QString bcdiv(const QString &left, 
            const QString &right, int scale = -1);

    /// @brief  Returns the modulus of the two arbitrary precision operands
    static inline QString bcmod(const QString &left, 
            const QString &right);

    /// @brief  Returns the value of an arbitrary precision number raised 
    ///         to the power of another reduced by a modulous
    static inline QString bcpowmod(const QString &left, 
            const QString &right, const QString &mod, int scale = -1);

    /// @brief  Returns the value of an arbitrary precision number raised 
    ///         to the power of another
    static inline QString bcpow(const QString &left, 
            const QString &right, int scale = -1);

    /// @brief  Returns the square root of an arbitray precision number
    static inline QString bcsqrt(const QString &left, int scale = -1);

    /// @brief  Compares two arbitrary precision numbers
    static inline int bccomp(const QString &left, const QString &right, 
            int scale = -1);
};

#endif  // TIANCHI_TCMATH_H

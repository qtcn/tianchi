// **************************************************************************
// Tianchi C++ library for Qt (open source)
// ��ع���Դ���
// ��Ȩ���� (C) ��ع���Դ��⿪����
// ��ȨЭ�飺���Ķ���ع���Դ��⸽������ȨЭ��
// **************************************************************************
// �ĵ�˵������QVariantMap��Ϊ�����е�model,ֻ��׷�Ӻ����,���ɲ�����ɾ��
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.07.04   XChinux     ����
//
// ==========================================================================
/// @file tcmath.cpp
// ==========================================================================
#include <tianchi/core/tcmath.h>
#include "../3rdparty/bcmath/bcmath.h"

std::string TcMath::bcadd(const std::string &left, const std::string &right, 
        int scale /*= -1*/)
{
    return ::bcadd(left, right, scale);
}

std::string TcMath::bcsub(const std::string &left, const std::string &right, 
        int scale /*= -1*/)
{
    return ::bcsub(left, right, scale);
}

std::string TcMath::bcmul(const std::string &left, const std::string &right, 
        int scale /*= -1*/)
{
    return ::bcmul(left, right, scale);
}

std::string TcMath::bcdiv(const std::string &left, const std::string &right, 
        int scale /*= -1*/)
{
    return ::bcdiv(left, right, scale);
}

std::string TcMath::bcmod(const std::string &left, const std::string &right)
{
    return ::bcmod(left, right);
}

std::string TcMath::bcpowmod(const std::string &left, const std::string &right, 
        const std::string &mod, int scale /*= -1*/)
{
    return ::bcpowmod(left, right, mod, scale);
}

std::string TcMath::bcpow(const std::string &left, const std::string &right, 
        int scale /*= -1*/)
{
    return ::bcpow(left, right, scale);
}

std::string TcMath::bcsqrt(const std::string &left, int scale /*= -1*/)
{
    return ::bcsqrt(left, scale);
}

int TcMath::bccomp(const std::string &left, const std::string &right, 
        int scale /*= -1*/)
{
    return ::bccomp(left, right, scale);
}

bool TcMath::bcscale(int scale)
{
    return ::bcscale(scale);
}

//--------------------------------------------------------------------------

QString TcMath::bcadd(const QString &left, const QString &right, 
        int scale /*= -1*/)
{
    return QString::fromStdString(
            ::bcadd(left.toStdString(), right.toStdString(), scale));
}

QString TcMath::bcsub(const QString &left, const QString &right, 
        int scale /*= -1*/)
{
    return QString::fromStdString(
            ::bcsub(left.toStdString(), right.toStdString(), scale));
}

QString TcMath::bcmul(const QString &left, const QString &right, 
        int scale /*= -1*/)
{
    return QString::fromStdString(
            ::bcmul(left.toStdString(), right.toStdString(), scale));
}

QString TcMath::bcdiv(const QString &left, const QString &right, 
        int scale /*= -1*/)
{
    return QString::fromStdString(
            ::bcdiv(left.toStdString(), right.toStdString(),scale));
}

QString TcMath::bcmod(const QString &left, const QString &right)
{
    return QString::fromStdString(
            ::bcmod(left.toStdString(), right.toStdString()));
}

QString TcMath::bcpowmod(const QString &left, const QString &right, 
        const QString &mod, int scale /*= -1*/)
{
    return QString::fromStdString(
            ::bcpowmod(left.toStdString(), right.toStdString(), 
                mod.toStdString(), scale));
}

QString TcMath::bcpow(const QString &left, const QString &right, 
        int scale /*= -1*/)
{
    return QString::fromStdString(
            ::bcpow(left.toStdString(), right.toStdString(), scale));
}

QString TcMath::bcsqrt(const QString &left, int scale /*= -1*/)
{
    return QString::fromStdString(::bcsqrt(left.toStdString(), scale));
}

int TcMath::bccomp(const QString &left, const QString &right, 
            int scale /*= -1*/)
{
    return ::bccomp(left.toStdString(), right.toStdString(), scale);
}

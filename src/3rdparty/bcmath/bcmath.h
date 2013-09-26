/* bcmath.h: bcmath library header file. */
/*
    Copyright (C) 2013 XChinux<XChinux@163.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.  (COPYING.LIB)

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to:

      The Free Software Foundation, Inc.
      59 Temple Place, Suite 330
      Boston, MA 02111-1307 USA.
*************************************************************************/


#ifndef BCMATH_H
#define BCMATH_H

#include <string>

std::string bcadd(const std::string &left, 
        const std::string &right, 
        int scale = -1);
std::string bcsub(const std::string &left, 
        const std::string &right, 
        int scale = -1);
std::string bcmul(const std::string &left, 
        const std::string &right, 
        int scale = -1);
std::string bcdiv(const std::string &left, 
        const std::string &right, 
        int scale = -1);
std::string bcmod(const std::string &left, 
        const std::string &right);
std::string bcpowmod(const std::string &left, 
        const std::string &right, 
        const std::string &mod, int scale = -1);
std::string bcpow(const std::string &left, 
        const std::string &right, 
        int scale = -1);
std::string bcsqrt(const std::string &left, 
        int scale = -1);
int bccomp(const std::string &left, 
        const std::string &right, 
        int scale = -1);
bool bcscale(int scale);

#endif /* BCMATH_H */

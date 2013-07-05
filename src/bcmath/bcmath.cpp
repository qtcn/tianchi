/* bcmath.cpp: bcmath library file. */
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

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "bcmath_p.h"
#include "bcmath.h"

/* Convert to bc_num detecting scale */
static void _str2num(bc_num *num, const char *str)
{
    const char *p;
    if (!(p = strchr(str, '.')))
    {
        bc_struct::str2num(num, str, 0);
        return;
    }
    bc_struct::str2num(num, str, strlen(p+1));
}

/* Returns the sum of two arbitrary precision numbers */
std::string bcadd(const std::string &left, const std::string &right, 
        int scale_param /*= -1*/)
{
    bc_num first, second, result;
    int scale = BCG(bc_precision);

    if (scale_param > -1)
    {
        scale = scale_param;
    }

    bc_struct::init_num(&first);
    bc_struct::init_num(&second);
    bc_struct::init_num(&result);
    _str2num(&first, left.c_str());
    _str2num(&second, right.c_str());
    bc_struct::add(first, second, &result, scale);
    
    if (result->n_scale > scale)
    {
        result->n_scale = scale;
    }
	
    char *ret = bc_struct::num2str(result);
    std::string return_value(ret);
    free(ret);
    bc_struct::free_num(&first);
    bc_struct::free_num(&second);
    bc_struct::free_num(&result);
    return return_value;
}

/* Returns the difference between two arbitrary precision numbers */
std::string bcsub(const std::string &left, const std::string &right, 
        int scale_param /*= -1*/)
{
    bc_num first, second, result;
    int scale = BCG(bc_precision);
	
    if (scale_param > -1)
    {
        scale = scale_param;
    }

    bc_struct::init_num(&first);
    bc_struct::init_num(&second);
    bc_struct::init_num(&result);
    _str2num(&first, left.c_str());
    _str2num(&second, right.c_str());
    bc_struct::sub(first, second, &result, scale);

    if (result->n_scale > scale)
    {
        result->n_scale = scale;
    }

    char *ret = bc_struct::num2str(result);
    std::string return_value(ret);
    free(ret);
    bc_struct::free_num(&first);
    bc_struct::free_num(&second);
    bc_struct::free_num(&result);
    return return_value;
}

/* Returns the multiplication of two arbitrary precision numbers */
std::string bcmul(const std::string &left, const std::string &right, 
        int scale_param /*= -1*/)
{
    bc_num first, second, result;
    int scale = scale_param > -1 ? scale_param : BCG(bc_precision);

    bc_struct::init_num(&first);
    bc_struct::init_num(&second);
    bc_struct::init_num(&result);
    _str2num(&first, left.c_str());
    _str2num(&second, right.c_str());
    bc_struct::multiply (first, second, &result, scale);

    if (result->n_scale > scale)
    {
        result->n_scale = scale;
    }

    char *ret = bc_struct::num2str(result);
    std::string return_value(ret); 
    free(ret);
    bc_struct::free_num(&first);
    bc_struct::free_num(&second);
    bc_struct::free_num(&result);
    return return_value;
}

/* Returns the quotient of two arbitrary precision numbers (division) */
std::string bcdiv(const std::string &left, 
        const std::string &right, int scale_param /*= -1*/)
{
    bc_num first, second, result;
    int scale = scale_param > -1 ? scale_param : BCG(bc_precision);

    bc_struct::init_num(&first);
    bc_struct::init_num(&second);
    bc_struct::init_num(&result);
    _str2num(&first, left.c_str());
    _str2num(&second, right.c_str());

    std::string return_value;
    switch (bc_struct::divide(first, second, &result, scale))
    {
        case 0: /* OK */
            if (result->n_scale > scale)
            {
                result->n_scale = scale;
            }
            {
                char *ret = bc_struct::num2str(result);
                return_value = ret;
                free(ret);
            }
            break;
        case -1: /* division by zero */
            std::cerr << "bc math error: Division by zero" << std::endl;
            break;
    }

    bc_struct::free_num(&first);
    bc_struct::free_num(&second);
    bc_struct::free_num(&result);
    return return_value;
}

/* Returns the modulus of the two arbitrary precision operands */
std::string bcmod(const std::string &left, const std::string &right)
{
    bc_num first, second, result;

    bc_struct::init_num(&first);
    bc_struct::init_num(&second);
    bc_struct::init_num(&result);
    bc_struct::str2num(&first, left.c_str(), 0);
    bc_struct::str2num(&second, right.c_str(), 0);
    
    std::string return_value;
    switch (bc_struct::modulo(first, second, &result, 0))
    {
        case 0:
            {
                char *ret = bc_struct::num2str(result);
                return_value =  ret;
                free(ret);
            }
            break;
        case -1:
            std::cerr << "bc math error: Division by zero" << std::endl;
            break;
    }        
	
    bc_struct::free_num(&first);
    bc_struct::free_num(&second);
    bc_struct::free_num(&result);
    return return_value;
}

/* Returns the value of an arbitrary precision number raised to the power of another reduced by a modulous */
std::string bcpowmod(const std::string &left, const std::string &right, 
        const std::string &modulous, int scale_param /*= -1*/)
{
    bc_num first, second, mod, result;
    int scale = scale_param > -1 ? scale_param : BCG(bc_precision);

    bc_struct::init_num(&first);
    bc_struct::init_num(&second);
    bc_struct::init_num(&mod);
    bc_struct::init_num(&result);
    _str2num(&first, left.c_str());
    _str2num(&second, right.c_str());
    _str2num(&mod, modulous.c_str());

    std::string return_value;
    if (bc_struct::raisemod(first, second, mod, &result, scale) != -1)
    {
        if (result->n_scale > scale)
        {
            result->n_scale = scale;
        }
        char *ret = bc_struct::num2str(result);
        return_value = ret;
        free(ret);
    }
    else
    {
        //RETVAL_FALSE;
    }
	
    bc_struct::free_num(&first);
    bc_struct::free_num(&second);
    bc_struct::free_num(&mod);
    bc_struct::free_num(&result);
    return return_value;
}

/* Returns the value of an arbitrary precision number raised to the power of another */
std::string bcpow(const std::string &left, 
        const std::string &right, int scale_param /*= -1*/)
{
    bc_num first, second, result;
    int scale = scale_param > -1 ? scale_param : BCG(bc_precision);

    bc_struct::init_num(&first);
    bc_struct::init_num(&second);
    bc_struct::init_num(&result);
    _str2num(&first, left.c_str());
    _str2num(&second, right.c_str());
    bc_struct::raise (first, second, &result, scale);

    if (result->n_scale > scale)
    {
        result->n_scale = scale;
    }

    char *ret = bc_struct::num2str(result);;
    std::string return_value(ret);
    free(ret);
    bc_struct::free_num(&first);
    bc_struct::free_num(&second);
    bc_struct::free_num(&result);
    return return_value;
}

/* Returns the square root of an arbitray precision number */
std::string bcsqrt(const std::string &left, int scale_param /*= -1*/)
{
    bc_num result;
    int scale = scale_param > -1 ? scale_param : BCG(bc_precision);

    bc_struct::init_num(&result);
    _str2num(&result, left.c_str());
    
    std::string return_value;
    if (bc_struct::sqrt(&result, scale) != 0)
    {
        if (result->n_scale > scale)
        {
            result->n_scale = scale;
        }
        char *ret = bc_struct::num2str(result);
        return_value = ret;
        free(ret);
    }
    else
    {
        std::cerr << "bc math error: Square root of negative number" 
            << std::endl;
    }

    bc_struct::free_num(&result);
    return return_value;
}

/* Compares two arbitrary precision numbers */
int bccomp(const std::string &left, 
        const std::string &right, 
        int scale_param /*= -1*/)
{
    bc_num first, second;
    int scale = scale_param > -1 ? scale_param : BCG(bc_precision);

    bc_struct::init_num(&first);
    bc_struct::init_num(&second);

    bc_struct::str2num(&first, left.c_str(), scale);
    bc_struct::str2num(&second, right.c_str(), scale);
    int return_value = bc_struct::compare(first, second);

    bc_struct::free_num(&first);
    bc_struct::free_num(&second);
    return return_value;
}

/* Sets default scale parameter for all bc math functions */
bool bcscale(int scale)
{
    if (scale > -1)
    {
        BCG(bc_precision) = scale;
        return true;
    }
    return false;
}

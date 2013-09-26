/* output.cpp: bcmath library file. */
/*
    Copyright (C) 1991, 1992, 1993, 1994, 1997 Free Software Foundation, Inc.
    Copyright (C) 2000 Philip A. Nelson
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

    You may contact the author by:
       e-mail:  philnelson@acm.org
      us-mail:  Philip A. Nelson
                Computer Science Department, 9062
                Western Washington University
                Bellingham, WA 98226-9062
       
*************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include "bcmath_p.h"


/* The following routines provide output for bcd numbers package
   using the rules of POSIX bc for output. */

/* This structure is used for saving digits in the conversion process. */
typedef struct stk_rec {
	long  digit;
	struct stk_rec *next;
} stk_rec;

/* The reference string for digits. */
static char ref_str[] = "0123456789ABCDEF";


/* A special output routine for "multi-character digits."  Exactly
   SIZE characters must be output for the value VAL.  If SPACE is
   non-zero, we must output one space before the number.  OUT_CHAR
   is the actual routine for writing the characters. */


void bc_out_long(long val, int size, int space, out_char_fn out_char)
{
    char digits[40];
    int len, ix;

    if (space) out_char(' ');
#ifdef _MSC_VER
    _snprintf_s
#else
    snprintf
#endif
        (digits, sizeof(digits), "%ld", val);
    len = strlen (digits);
    while (size > len)
    {
        out_char('0');
        size--;
    }
    for (ix=0; ix < len; ix++)
        out_char(digits[ix]);
}

/* Output of a bcd number.  NUM is written in base O_BASE using OUT_CHAR
   as the routine to do the actual output of the characters. */
void bc_struct::out_num(bc_num num, int o_base, out_char_fn out_char, 
        int leading_zero)
{
    char *nptr;
    int  index, fdigit, pre_space;
    stk_rec *digits, *temp;
    bc_num int_part, frac_part, base, cur_dig, t_num, max_o_digit;

    /* The negative sign if needed. */
    if (num->n_sign == MINUS) out_char('-');

    /* Output the number. */
    if (num->is_zero())
        out_char('0');
    else
        if (o_base == 10)
        {
	    /* The number is in base 10, do it the fast way. */
            nptr = num->n_value;
            if (num->n_len > 1 || *nptr != 0)
                for (index=num->n_len; index>0; index--)
                    out_char(BCD_CHAR(*nptr++));
            else
                nptr++;

            if (leading_zero && num->is_zero())
                out_char('0');

            /* Now the fraction. */
            if (num->n_scale > 0)
            {
                out_char('.');
                for (index=0; index<num->n_scale; index++)
                    out_char(BCD_CHAR(*nptr++));
            }
        }
        else
        {
	    /* special case ... */
	    if (leading_zero && num->is_zero())
	        out_char('0');

	    /* The number is some other base. */
            digits = NULL;
            bc_struct::init_num(&int_part);
            bc_struct::divide(num, BCG(_one_), &int_part, 0);
            bc_struct::init_num(&frac_part);
            bc_struct::init_num(&cur_dig);
            bc_struct::init_num(&base);
            bc_struct::sub(num, int_part, &frac_part, 0);
            /* Make the INT_PART and FRAC_PART positive. */
            int_part->n_sign = PLUS;
            frac_part->n_sign = PLUS;
            bc_struct::int2num(&base, o_base);
            bc_struct::init_num(&max_o_digit);
            bc_struct::int2num(&max_o_digit, o_base-1);


            /* Get the digits of the integer part and push them on a stack. */
            while (!int_part->is_zero())
            {
                bc_struct::modulo(int_part, base, &cur_dig, 0);
                    /* PHP Change:  malloc() -> emalloc() */
                temp = (stk_rec *) malloc (sizeof(stk_rec));
                if (temp == NULL) bc_struct::out_of_memory();
                temp->digit = cur_dig->to_long();
                temp->next = digits;
                digits = temp;
                bc_struct::divide(int_part, base, &int_part, 0);
            }

            /* Print the digits on the stack. */
            if (digits != NULL)
            {
                /* Output the digits. */
                while (digits != NULL)
                {
                    temp = digits;
                    digits = digits->next;
                    if (o_base <= 16)
                        out_char(ref_str[ (int) temp->digit]);
                    else
                        bc_out_long(temp->digit, max_o_digit->n_len, 1, out_char);
                    free (temp);
                }
            }

            /* Get and print the digits of the fraction part. */
            if (num->n_scale > 0)
            {
                out_char('.');
                pre_space = 0;
                t_num = bc_struct::copy_num(BCG(_one_));
                while (t_num->n_len <= num->n_scale)
                {
                    bc_struct::multiply(frac_part, base, &frac_part, num->n_scale);
                    fdigit = frac_part->to_long();
                    bc_struct::int2num(&int_part, fdigit);
                    bc_struct::sub(frac_part, int_part, &frac_part, 0);
                    if (o_base <= 16)
                        out_char(ref_str[fdigit]);
                    else
                    {
                        bc_out_long(fdigit, max_o_digit->n_len, pre_space, 
                                out_char);
                        pre_space = 1;
                    }
                    bc_struct::multiply(t_num, base, &t_num, 0);
                }
                bc_struct::free_num(&t_num);
            }

            /* Clean up. */
            bc_struct::free_num(&int_part);
            bc_struct::free_num(&frac_part);
            bc_struct::free_num(&base);
            bc_struct::free_num(&cur_dig);
            bc_struct::free_num(&max_o_digit);
        }
}

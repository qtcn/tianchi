/* bcmath_p.h: bcmath library private header.    	*/
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

#ifndef _BCMATH_P_H_
#define _BCMATH_P_H_


typedef void(*out_char_fn)(int);

enum sign {PLUS, MINUS};

struct bc_struct;
typedef bc_struct *bc_num;

struct bc_struct
{
private:
    bc_struct(int length, int scale);
    ~bc_struct();
public:
    sign  n_sign;
    int   n_len;	/* The number of digits before the decimal point. */
    int   n_scale;	/* The number of digits after the decimal point. */
    int   n_refs;     /* The number of pointers to this number. */
    bc_num n_next;	/* Linked list for available list. */
    char *n_ptr;	/* The pointer to the actual storage.
                       If NULL, n_value points to the inside of
                       another number (bc_multiply...) and should
                       not be "freed." */
    char *n_value;	/* The number. Not zero char terminated.
                       May not point to the same place as n_ptr as
                       in the case of leading zeros generated. */

public:
    // new_num allocates a number and sets fields to known values
    static bc_num new_num(int length, int scale);

    // Frees" a bc_num NUM.  Actually decreases reference count and only
    // frees the storage if reference count is zero
    static void free_num(bc_num *num);

    // Make a copy of a number!  Just increments the reference count!
    static bc_num copy_num(bc_num num);

    // Initialize a number NUM by making it a copy of zero.
    static void init_num(bc_num *num);

    // Intitialize the number package!
    static void init_numbers();

    /* Convert strings to bc numbers.  Base 10 only.*/
    static void str2num(bc_num *num, const char *str, int scale);


    /* Convert a numbers to a string.  Base 10 only.*/
    static char *num2str(bc_num num);

    /* Convert an integer VAL to a bc number NUM. */
    static void int2num(bc_num *num, int val);

    /* Convert a number NUM to a long.  The function returns only the integer
       part of the number.  For numbers that are too large to represent as
       a long, this function returns a zero.  This can be detected by checking
       the NUM for zero after having a zero returned. */
    static long num2long(bc_num num);

    /* In some places we need to check if the number NUM is zero. */
    static char is_zero(bc_num num);

    /* In some places we need to check if the number NUM is almost zero.
       Specifically, all but the last digit is 0 and the last digit is 1.
       Last digit is defined by scale. */
    static char is_near_zero(bc_num num, int scale);

    /* In some places we need to check if the number is negative. */
    static char is_neg(bc_num num);

    /* This is the "user callable" routine to compare numbers N1 and N2. */
    static int compare(bc_num n1, bc_num n2);

    /* Take the square root NUM and return it in NUM with SCALE digits
       after the decimal place. */
    static int sqrt(bc_num *num, int scale);

    /* Here is the full add routine that takes care of negative numbers.
       N1 is added to N2 and the result placed into RESULT.  SCALE_MIN
       is the minimum scale for the result. */
    static void add(bc_num n1, bc_num n2, bc_num *result, int scale_min);

    /* Here is the full subtract routine that takes care of negative numbers.
       N2 is subtracted from N1 and the result placed in RESULT.  SCALE_MIN
       is the minimum scale for the result. */
    static void sub(bc_num n1, bc_num n2, bc_num *result, int scale_min);


    /* The multiply routine.  N2 times N1 is put int PROD with the scale of
       the result being MIN(N2 scale+N1 scale, MAX (SCALE, N2 scale, N1 scale)).
       */
    static void multiply(bc_num n1, bc_num n2, bc_num *prod, int scale);

    /* The full division routine. This computes N1 / N2.  It returns
       0 if the division is ok and the result is in QUOT.  The number of
       digits after the decimal point is SCALE. It returns -1 if division
       by zero is tried.  The algorithm is found in Knuth Vol 2. p237. */
    static int divide(bc_num n1, bc_num n2, bc_num *quot, int scale);


    /* Division *and* modulo for numbers.  This computes both NUM1 / NUM2 and
       NUM1 % NUM2  and puts the results in QUOT and REM, except that if QUOT
       is NULL then that store will be omitted.
     */
    static int divmod(bc_num num1, bc_num num2, bc_num *quot, bc_num *rem, int scale);


    /* Modulo for numbers.  This computes NUM1 % NUM2  and puts the
       result in RESULT.   */
    static int modulo(bc_num num1, bc_num num2, bc_num *result,int scale);

    /* Raise NUM1 to the NUM2 power.  The result is placed in RESULT.
       Maximum exponent is LONG_MAX.  If a NUM2 is not an integer,
       only the integer part is used.  */
    static void raise(bc_num num1, bc_num num2, bc_num *result, int scale);

    /* Raise BASE to the EXPO power, reduced modulo MOD.  The result is
       placed in RESULT.  If a EXPO is not an integer,
       only the integer part is used.  */
    static int raisemod(bc_num base, bc_num expo, bc_num mod, bc_num *result, int scale);

    /* Output of a bcd number.  NUM is written in base O_BASE using OUT_CHAR
       as the routine to do the actual output of the characters. */
    static void out_num(bc_num num, int o_base, out_char_fn out_char, int leading_zero);

    /* Prototypes needed for external utility routines. */
    static void out_of_memory(void);



    static void _bc_rm_leading_zeros(bc_num num);
private:
    static int _bc_do_compare(bc_num n1, bc_num n2, int use_sign, int ignore_last);
    static bc_num _bc_do_add(bc_num n1, bc_num n2, int scale_min);
    static bc_num _bc_do_sub(bc_num n1, bc_num n2, int scale_min);
};

struct BCMATH_GLOBALS_TYPE
{
    BCMATH_GLOBALS_TYPE();
    ~BCMATH_GLOBALS_TYPE();
    bc_num _zero_;
    bc_num _one_;
    bc_num _two_;
    int bc_precision;
};

extern BCMATH_GLOBALS_TYPE bcmath_globals;
#define BCG(v) (bcmath_globals.v)


/* The base used in storing the numbers in n_value above.
   Currently this MUST be 10. */

#define BASE 10

/*  Some useful macros and constants. */

#define CH_VAL(c)     (c - '0')
#define BCD_CHAR(d)   (d + '0')

#ifdef MIN
#undef MIN
#undef MAX
#endif
#define MAX(a, b)      ((a)>(b)?(a):(b))
#define MIN(a, b)      ((a)>(b)?(b):(a))
#define ODD(a)        ((a)&1)

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#ifndef LONG_MAX
#define LONG_MAX 0x7ffffff
#endif

#endif

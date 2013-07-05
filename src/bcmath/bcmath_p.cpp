/* bcmath_p.cpp: bcmath library file. */
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
#include <iostream>
#include "bcmath_p.h"

BCMATH_GLOBALS_TYPE bcmath_globals;

BCMATH_GLOBALS_TYPE::BCMATH_GLOBALS_TYPE()
    : _zero_(NULL), _one_(NULL), _two_(NULL), bc_precision(0)
{
    bc_struct::init_numbers();
}

BCMATH_GLOBALS_TYPE::~BCMATH_GLOBALS_TYPE()
{
    bc_struct::free_num(&bcmath_globals._zero_);
    bc_struct::free_num(&bcmath_globals._one_);
    bc_struct::free_num(&bcmath_globals._two_);
}

bc_struct::bc_struct(int length, int scale) : n_sign(PLUS), n_len(length), 
    n_scale(scale), n_refs(1), n_next(NULL), n_ptr(NULL), n_value(NULL)
{
    n_ptr = (char *)malloc(length + scale);
    n_value = n_ptr;
    memset(n_ptr, 0, length + scale);
}

bc_struct::~bc_struct()
{
    if (n_ptr)
    {
        free(n_ptr);
    }
}

// new_num allocates a number and sets fields to known values
bc_num bc_struct::new_num(int length, int scale)
{
    return new bc_struct(length, scale);
}

// Frees" a bc_num NUM.  Actually decreases reference count and only
// frees the storage if reference count is zero
void bc_struct::free_num(bc_num *num)
{
    if (*num == NULL) return;
    (*num)->n_refs--;
    if ((*num)->n_refs == 0)
    {
        delete *num;
    }
    *num = NULL;
}

// Make a copy of a number!  Just increments the reference count!
bc_num bc_struct::copy_num(bc_num num)
{
    num->n_refs++;
    return num;
}

// Initialize a number NUM by making it a copy of zero.
void bc_struct::init_num(bc_num *num)
{
    *num = copy_num(BCG(_zero_));
}

// Intitialize the number package!
void bc_struct::init_numbers()
{
    BCG(_zero_) = new_num(1, 0);
    BCG(_one_)  = new_num(1, 0);
    BCG(_one_)->n_value[0] = 1;
    BCG(_two_)  = new_num(1, 0);
    BCG(_two_)->n_value[0] = 2;
}

/* Convert strings to bc numbers.  Base 10 only.*/
void bc_struct::str2num(bc_num *num, const char *str, int scale)
{
    int digits, strscale;
    char *nptr;
    char zero_int;
    const char *ptr;

    /* Prepare num. */
    bc_struct::free_num(num);

    /* Check for valid number and count digits. */
    ptr = str;
    digits = 0;
    strscale = 0;
    zero_int = FALSE;
    if ((*ptr == '+') || (*ptr == '-'))  ptr++;  /* Sign */
    while (*ptr == '0') ptr++;			/* Skip leading zeros. */
    while (isdigit((int)*ptr)) ptr++, digits++;	/* digits */
    if (*ptr == '.') ptr++;			/* decimal point */
    while (isdigit((int)*ptr)) ptr++, strscale++;	/* digits */
    if ((*ptr != '\0') || (digits+strscale == 0))
    {
        *num = bc_struct::copy_num(BCG(_zero_));
        return;
    }

    /* Adjust numbers and allocate storage and initialize fields. */
    strscale = MIN(strscale, scale);
    if (digits == 0)
    {
        zero_int = TRUE;
        digits = 1;
    }
    *num = bc_struct::new_num(digits, strscale);

    /* Build the whole number. */
    ptr = str;
    if (*ptr == '-')
    {
        (*num)->n_sign = MINUS;
        ptr++;
    }
    else
    {
        (*num)->n_sign = PLUS;
        if (*ptr == '+') ptr++;
    }
    while (*ptr == '0') ptr++;			/* Skip leading zeros. */
    nptr = (*num)->n_value;
    if (zero_int)
    {
        *nptr++ = 0;
        digits = 0;
    }
    for (;digits > 0; digits--)
        *nptr++ = CH_VAL(*ptr++);


    /* Build the fractional part. */
    if (strscale > 0)
    {
        ptr++;  /* skip the decimal point! */
        for (;strscale > 0; strscale--)
            *nptr++ = CH_VAL(*ptr++);
    }
}

/* Convert a numbers to a string.  Base 10 only.*/
char* bc_struct::num2str(bc_num num)
{
  char *str, *sptr;
  char *nptr;
  int  index, signch;

  /* Allocate the string memory. */
  signch = ( num->n_sign == PLUS ? 0 : 1 );  /* Number of sign chars. */
  if (num->n_scale > 0)
    str = (char *) malloc (num->n_len + num->n_scale + (2 + signch));
  else
    str = (char *) malloc (num->n_len + (1 + signch));
  if (str == NULL) bc_struct::out_of_memory();

  /* The negative sign if needed. */
  sptr = str;
  if (signch) *sptr++ = '-';

  /* Load the whole number. */
  nptr = num->n_value;
  for (index=num->n_len; index>0; index--)
    *sptr++ = BCD_CHAR(*nptr++);

  /* Now the fraction. */
  if (num->n_scale > 0)
    {
      *sptr++ = '.';
      for (index=0; index<num->n_scale; index++)
	*sptr++ = BCD_CHAR(*nptr++);
    }

  /* Terminate the string and return it! */
  *sptr = '\0';
  return (str);
}

/* Convert an integer VAL to a bc number NUM. */
void bc_struct::int2num(bc_num *num, int val)
{
  char buffer[30];
  char *bptr, *vptr;
  int  ix = 1;
  char neg = 0;

  /* Sign. */
  if (val < 0)
    {
      neg = 1;
      val = -val;
    }

  /* Get things going. */
  bptr = buffer;
  *bptr++ = val % BASE;
  val = val / BASE;

  /* Extract remaining digits. */
  while (val != 0)
    {
      *bptr++ = val % BASE;
      val = val / BASE;
      ix++; 		/* Count the digits. */
    }

  /* Make the number. */
  bc_struct::free_num(num);
  *num = bc_struct::new_num(ix, 0);
  if (neg) (*num)->n_sign = MINUS;

  /* Assign the digits. */
  vptr = (*num)->n_value;
  while (ix-- > 0)
    *vptr++ = *--bptr;
}

/* Convert a number NUM to a long.  The function returns only the integer
   part of the number.  For numbers that are too large to represent as
   a long, this function returns a zero.  This can be detected by checking
   the NUM for zero after having a zero returned. */
long bc_struct::num2long(bc_num num)
{
  long val;
  char *nptr;
  int  index;

  /* Extract the int value, ignore the fraction. */
  val = 0;
  nptr = num->n_value;
  for (index=num->n_len; (index>0) && (val<=(LONG_MAX/BASE)); index--)
    val = val*BASE + *nptr++;

  /* Check for overflow.  If overflow, return zero. */
  if (index>0) val = 0;
  if (val < 0) val = 0;

  /* Return the value. */
  if (num->n_sign == PLUS)
    return (val);
  else
    return (-val);
}

/* In some places we need to check if the number is negative. */
char bc_struct::is_neg(bc_num num)
{
  return num->n_sign == MINUS;
}

/* In some places we need to check if the number NUM is almost zero.
   Specifically, all but the last digit is 0 and the last digit is 1.
   Last digit is defined by scale. */
char bc_struct::is_near_zero(bc_num num, int scale)
{
  int  count;
  char *nptr;

  /* Error checking */
  if (scale > num->n_scale)
    scale = num->n_scale;

  /* Initialize */
  count = num->n_len + scale;
  nptr = num->n_value;

  /* The check */
  while ((count > 0) && (*nptr++ == 0)) count--;

  if (count != 0 && (count != 1 || *--nptr != 1))
    return FALSE;
  else
    return TRUE;
}

/* In some places we need to check if the number NUM is zero. */
char bc_struct::is_zero(bc_num num)
{
    int  count;
    char *nptr;

    /* Quick check. */
    if (num == BCG(_zero_)) return TRUE;

    /* Initialize */
    count = num->n_len + num->n_scale;
    nptr = num->n_value;

    /* The check */
    while ((count > 0) && (*nptr++ == 0)) count--;

    if (count != 0)
        return FALSE;
    else
        return TRUE;
}

/* Compare two bc numbers.  Return value is 0 if equal, -1 if N1 is less
   than N2 and +1 if N1 is greater than N2.  If USE_SIGN is false, just
   compare the magnitudes. */
int bc_struct::_bc_do_compare(bc_num n1, bc_num n2, int use_sign, int ignore_last)
{
    char *n1ptr, *n2ptr;
    int  count;

    /* First, compare signs. */
    if (use_sign && n1->n_sign != n2->n_sign)
    {
        if (n1->n_sign == PLUS)
            return (1);	/* Positive N1 > Negative N2 */
        else
            return (-1);	/* Negative N1 < Positive N1 */
    }

    /* Now compare the magnitude. */
    if (n1->n_len != n2->n_len)
    {
        if (n1->n_len > n2->n_len)
	{
	    /* Magnitude of n1 > n2. */
	    if (!use_sign || n1->n_sign == PLUS)
	        return (1);
	    else
	        return (-1);
	}
        else
	{
	    /* Magnitude of n1 < n2. */
	    if (!use_sign || n1->n_sign == PLUS)
	        return (-1);
	    else
	        return (1);
	}
    }

    /* If we get here, they have the same number of integer digits.
     check the integer part and the equal length part of the fraction. */
    count = n1->n_len + MIN (n1->n_scale, n2->n_scale);
    n1ptr = n1->n_value;
    n2ptr = n2->n_value;

    while ((count > 0) && (*n1ptr == *n2ptr))
    {
        n1ptr++;
        n2ptr++;
        count--;
    }
    if (ignore_last && count == 1 && n1->n_scale == n2->n_scale)
        return (0);
    if (count != 0)
    {
        if (*n1ptr > *n2ptr)
	{
            /* Magnitude of n1 > n2. */
            if (!use_sign || n1->n_sign == PLUS)
                return (1);
            else
                return (-1);
	}
        else
	{
            /* Magnitude of n1 < n2. */
            if (!use_sign || n1->n_sign == PLUS)
                return (-1);
            else
                return (1);
        }
    }

    /* They are equal up to the last part of the equal part of the fraction. */
    if (n1->n_scale != n2->n_scale)
    {
        if (n1->n_scale > n2->n_scale)
	{
            for (count = n1->n_scale-n2->n_scale; count>0; count--)
	    if (*n1ptr++ != 0)
            {
		/* Magnitude of n1 > n2. */
		if (!use_sign || n1->n_sign == PLUS)
                    return (1);
		else
                    return (-1);
            }
        }
        else
	{
            for (count = n2->n_scale-n1->n_scale; count>0; count--)
            {
                if (*n2ptr++ != 0)
                {
                    /* Magnitude of n1 < n2. */
                    if (!use_sign || n1->n_sign == PLUS)
                        return (-1);
                    else
                        return (1);
                }
            }
	}
    }

    /* They must be equal! */
    return (0);
}

/* This is the "user callable" routine to compare numbers N1 and N2. */
int bc_struct::compare(bc_num n1, bc_num n2)
{
    return _bc_do_compare(n1, n2, TRUE, FALSE);
}

/* Take the square root NUM and return it in NUM with SCALE digits
   after the decimal place. */
int bc_struct::sqrt(bc_num *num, int scale)
{
    int rscale, cmp_res, done;
    int cscale;
    bc_num guess, guess1, point5, diff;

    /* Initial checks. */
    cmp_res = bc_struct::compare(*num, BCG(_zero_));
    if (cmp_res < 0)
        return 0;		/* error */
    else
    {
        if (cmp_res == 0)
	{
            bc_struct::free_num(num);
            *num = bc_struct::copy_num(BCG(_zero_));
            return 1;
        }
    }
    cmp_res = bc_struct::compare(*num, BCG(_one_));
    if (cmp_res == 0)
    {
        bc_struct::free_num(num);
        *num = bc_struct::copy_num(BCG(_one_));
        return 1;
    }

    /* Initialize the variables. */
    rscale = MAX(scale, (*num)->n_scale);
    bc_struct::init_num(&guess);
    bc_struct::init_num(&guess1);
    bc_struct::init_num(&diff);
    point5 = bc_struct::new_num(1,1);
    point5->n_value[1] = 5;


    /* Calculate the initial guess. */
    if (cmp_res < 0)
    {
        /* The number is between 0 and 1.  Guess should start at 1. */
        guess = bc_struct::copy_num(BCG(_one_));
        cscale = (*num)->n_scale;
    }
    else
    {
        /* The number is greater than 1.  Guess should start at 10^(exp/2). */
        bc_struct::int2num(&guess,10);

        bc_struct::int2num(&guess1,(*num)->n_len);
        bc_struct::multiply(guess1, point5, &guess1, 0);
        guess1->n_scale = 0;
        bc_struct::raise(guess, guess1, &guess, 0);
        bc_struct::free_num(&guess1);
        cscale = 3;
    }

    /* Find the square root using Newton's algorithm. */
    done = FALSE;
    while (!done)
    {
        bc_struct::free_num(&guess1);
        guess1 = bc_struct::copy_num (guess);
        bc_struct::divide(*num, guess, &guess, cscale);
        bc_struct::add(guess, guess1, &guess, 0);
        bc_struct::multiply(guess, point5, &guess, cscale);
        bc_struct::sub(guess, guess1, &diff, cscale+1);
        if (bc_struct::is_near_zero(diff, cscale))
        {
            if (cscale < rscale + 1)
                cscale = MIN (cscale*3, rscale+1);
            else
                done = TRUE;
        }
    }

    /* Assign the number and clean up. */
    bc_struct::free_num(num);
    bc_struct::divide(guess,BCG(_one_),num,rscale);
    bc_struct::free_num(&guess);
    bc_struct::free_num(&guess1);
    bc_struct::free_num(&point5);
    bc_struct::free_num(&diff);
    return 1;
}

/* Here is the full add routine that takes care of negative numbers.
   N1 is added to N2 and the result placed into RESULT.  SCALE_MIN
   is the minimum scale for the result. */
void bc_struct::add(bc_num n1, bc_num n2, bc_num *result, int scale_min)
{
    bc_num sum = NULL;
    int cmp_res;
    int res_scale;

    if (n1->n_sign == n2->n_sign)
    {
        sum = _bc_do_add(n1, n2, scale_min);
        sum->n_sign = n1->n_sign;
    }
    else
    {
        /* subtraction must be done. */
        cmp_res = _bc_do_compare(n1, n2, FALSE, FALSE);/* Compare magnitudes. */
        switch (cmp_res)
	{
	case -1:
            /* n1 is less than n2, subtract n1 from n2. */
            sum = _bc_do_sub(n2, n1, scale_min);
            sum->n_sign = n2->n_sign;
            break;
	case  0:
	    /* They are equal! return zero with the correct scale! */
	    res_scale = MAX(scale_min, MAX(n1->n_scale, n2->n_scale));
	    sum = bc_struct::new_num(1, res_scale);
	    memset(sum->n_value, 0, res_scale + 1);
	    break;
	case  1:
	    /* n2 is less than n1, subtract n2 from n1. */
	    sum = _bc_do_sub(n1, n2, scale_min);
	    sum->n_sign = n1->n_sign;
        }
    }

    /* Clean up and return. */
    bc_struct::free_num(result);
    *result = sum;
}

/* Here is the full subtract routine that takes care of negative numbers.
   N2 is subtracted from N1 and the result placed in RESULT.  SCALE_MIN
   is the minimum scale for the result. */
void bc_struct::sub(bc_num n1, bc_num n2, bc_num *result, int scale_min)
{
    bc_num diff = NULL;
    int cmp_res;
    int res_scale;

    if (n1->n_sign != n2->n_sign)
    {
        diff = _bc_do_add (n1, n2, scale_min);
        diff->n_sign = n1->n_sign;
    }
    else
    {
        /* subtraction must be done. */
        /* Compare magnitudes. */
        cmp_res = _bc_do_compare (n1, n2, FALSE, FALSE);
        switch (cmp_res)
	{
	case -1:
            /* n1 is less than n2, subtract n1 from n2. */
	    diff = _bc_do_sub (n2, n1, scale_min);
	    diff->n_sign = (n2->n_sign == PLUS ? MINUS : PLUS);
	    break;
	case  0:
	    /* They are equal! return zero! */
	    res_scale = MAX (scale_min, MAX(n1->n_scale, n2->n_scale));
	    diff = bc_struct::new_num(1, res_scale);
	    memset (diff->n_value, 0, res_scale+1);
	    break;
	case  1:
	    /* n2 is less than n1, subtract n2 from n1. */
	    diff = _bc_do_sub (n1, n2, scale_min);
	    diff->n_sign = n1->n_sign;
	    break;
        }
    }

    /* Clean up and return. */
    bc_struct::free_num(result);
    *result = diff;
}

/* Division *and* modulo for numbers.  This computes both NUM1 / NUM2 and
   NUM1 % NUM2  and puts the results in QUOT and REM, except that if QUOT
   is NULL then that store will be omitted.
 */

int bc_struct::divmod(bc_num num1, bc_num num2, bc_num *quot, bc_num *rem, 
        int scale)
{
  bc_num quotient = NULL;
  bc_num temp;
  int rscale;

  /* Check for correct numbers. */
  if (bc_struct::is_zero(num2)) return -1;

  /* Calculate final scale. */
  rscale = MAX (num1->n_scale, num2->n_scale+scale);
  bc_struct::init_num(&temp);

  /* Calculate it. */
  bc_struct::divide(num1, num2, &temp, scale);
  if (quot)
    quotient = bc_struct::copy_num(temp);
  bc_struct::multiply(temp, num2, &temp, rscale);
  bc_struct::sub(num1, temp, rem, rscale);
  bc_struct::free_num(&temp);

  if (quot)
    {
        bc_struct::free_num(quot);
      *quot = quotient;
    }

  return 0;	/* Everything is OK. */
}


/* Modulo for numbers.  This computes NUM1 % NUM2  and puts the
   result in RESULT.   */

int bc_struct::modulo(bc_num num1, bc_num num2, bc_num *result, int scale)
{
  return divmod(num1, num2, NULL, result, scale);
}

/* Raise NUM1 to the NUM2 power.  The result is placed in RESULT.
   Maximum exponent is LONG_MAX.  If a NUM2 is not an integer,
   only the integer part is used.  */
void bc_struct::raise(bc_num num1, bc_num num2, bc_num *result, int scale)
{
    bc_num temp, power;
    long exponent;
    int rscale;
    int pwrscale;
    int calcscale;
    char neg;

    /* Check the exponent for scale digits and convert to a long. */
    if (num2->n_scale != 0)
        std::cerr << "bc math warn: non-zero scale in exponent" << std::endl;
    exponent = bc_struct::num2long(num2);
    if (exponent == 0 && (num2->n_len > 1 || num2->n_value[0] != 0))
        std::cerr << "bc math error: exponent too large in raise" << std::endl;

    /* Special case if exponent is a zero. */
    if (exponent == 0)
    {
        bc_struct::free_num(result);
        *result = bc_struct::copy_num(BCG(_one_));
        return;
    }

    /* Other initializations. */
    if (exponent < 0)
    {
        neg = TRUE;
        exponent = -exponent;
        rscale = scale;
    }
    else
    {
        neg = FALSE;
        rscale = MIN(num1->n_scale*exponent, MAX(scale, num1->n_scale));
    }

    /* Set initial value of temp.  */
    power = bc_struct::copy_num(num1);
    pwrscale = num1->n_scale;
    while ((exponent & 1) == 0)
    {
        pwrscale = 2 * pwrscale;
        bc_struct::multiply(power, power, &power, pwrscale);
        exponent = exponent >> 1;
    }
    temp = bc_struct::copy_num(power);
    calcscale = pwrscale;
    exponent = exponent >> 1;

    /* Do the calculation. */
    while (exponent > 0)
    {
        pwrscale = 2 * pwrscale;
        bc_struct::multiply(power, power, &power, pwrscale);
        if ((exponent & 1) == 1)
        {
            calcscale = pwrscale + calcscale;
            bc_struct::multiply(temp, power, &temp, calcscale);
        }
        exponent = exponent >> 1;
    }

    /* Assign the value. */
    if (neg)
    {
        bc_struct::divide(BCG(_one_), temp, result, rscale);
        bc_struct::free_num(&temp);
    }
    else
    {
        bc_struct::free_num(result);
        *result = temp;
        if ((*result)->n_scale > rscale)
            (*result)->n_scale = rscale;
    }
    bc_struct::free_num(&power);
}

/* Raise BASE to the EXPO power, reduced modulo MOD.  The result is
   placed in RESULT.  If a EXPO is not an integer,
   only the integer part is used.  */
int bc_struct::raisemod(bc_num base, bc_num expo, bc_num mod, bc_num *result, 
        int scale)
{
    bc_num power, exponent, parity, temp;
    int rscale;

    /* Check for correct numbers. */
    if (bc_struct::is_zero(mod)) return -1;
    if (bc_struct::is_neg(expo)) return -1;

    /* Set initial values.  */
    power = bc_struct::copy_num(base);
    exponent = bc_struct::copy_num(expo);
    temp = bc_struct::copy_num(BCG(_one_));
    bc_struct::init_num(&parity);

    /* Check the base for scale digits. */
    if (base->n_scale != 0)
        std::cerr << "bc math warn: non-zero scale in base" << std::endl;

    /* Check the exponent for scale digits. */
    if (exponent->n_scale != 0)
    {
        std::cerr << "bc math warn: non-zero scale in exponent" << std::endl;
        bc_struct::divide (exponent, BCG(_one_), &exponent, 0); /*truncate */
    }

    /* Check the modulus for scale digits. */
    if (mod->n_scale != 0)
        std::cerr << "bc math warn: non-zero scale in modulus" << std::endl;

    /* Do the calculation. */
    rscale = MAX(scale, base->n_scale);
    while (!bc_struct::is_zero(exponent))
    {
        (void)bc_struct::divmod(exponent, BCG(_two_), &exponent, &parity, 0);
        if (!bc_struct::is_zero(parity))
	{
            bc_struct::multiply(temp, power, &temp, rscale);
            (void)bc_struct::modulo(temp, mod, &temp, scale);
	}

        bc_struct::multiply(power, power, &power, rscale);
        (void)bc_struct::modulo(power, mod, &power, scale);
    }

    /* Assign the value. */
    bc_struct::free_num(&power);
    bc_struct::free_num(&exponent);
    bc_struct::free_num(result);
    bc_struct::free_num(&parity);
    *result = temp;
    return 0;	/* Everything is OK. */
}

/* Prototypes needed for external utility routines. */
void bc_struct::out_of_memory(void)
{
  (void) fprintf (stderr, "bcmath: out of memory!\n");
  exit (1);
}


/* Perform addition: N1 is added to N2 and the value is
   returned.  The signs of N1 and N2 are ignored.
   SCALE_MIN is to set the minimum scale of the result. */

bc_num bc_struct::_bc_do_add(bc_num n1, bc_num n2, int scale_min)
{
  bc_num sum;
  int sum_scale, sum_digits;
  char *n1ptr, *n2ptr, *sumptr;
  int carry, n1bytes, n2bytes;
  int count;

  /* Prepare sum. */
  sum_scale = MAX (n1->n_scale, n2->n_scale);
  sum_digits = MAX (n1->n_len, n2->n_len) + 1;
  sum = bc_struct::new_num(sum_digits, MAX(sum_scale, scale_min));

  /* Zero extra digits made by scale_min. */
  if (scale_min > sum_scale)
    {
      sumptr = (char *) (sum->n_value + sum_scale + sum_digits);
      for (count = scale_min - sum_scale; count > 0; count--)
	*sumptr++ = 0;
    }

  /* Start with the fraction part.  Initialize the pointers. */
  n1bytes = n1->n_scale;
  n2bytes = n2->n_scale;
  n1ptr = (char *) (n1->n_value + n1->n_len + n1bytes - 1);
  n2ptr = (char *) (n2->n_value + n2->n_len + n2bytes - 1);
  sumptr = (char *) (sum->n_value + sum_scale + sum_digits - 1);

  /* Add the fraction part.  First copy the longer fraction.*/
  if (n1bytes != n2bytes)
    {
      if (n1bytes > n2bytes)
	while (n1bytes>n2bytes)
	  { *sumptr-- = *n1ptr--; n1bytes--;}
      else
	while (n2bytes>n1bytes)
	  { *sumptr-- = *n2ptr--; n2bytes--;}
    }

  /* Now add the remaining fraction part and equal size integer parts. */
  n1bytes += n1->n_len;
  n2bytes += n2->n_len;
  carry = 0;
  while ((n1bytes > 0) && (n2bytes > 0))
    {
      *sumptr = *n1ptr-- + *n2ptr-- + carry;
      if (*sumptr > (BASE-1))
	{
	   carry = 1;
	   *sumptr -= BASE;
	}
      else
	carry = 0;
      sumptr--;
      n1bytes--;
      n2bytes--;
    }

  /* Now add carry the longer integer part. */
  if (n1bytes == 0)
    { n1bytes = n2bytes; n1ptr = n2ptr; }
  while (n1bytes-- > 0)
    {
      *sumptr = *n1ptr-- + carry;
      if (*sumptr > (BASE-1))
	{
	   carry = 1;
	   *sumptr -= BASE;
	 }
      else
	carry = 0;
      sumptr--;
    }

  /* Set final carry. */
  if (carry == 1)
    *sumptr += 1;

  /* Adjust sum and return. */
  _bc_rm_leading_zeros (sum);
  return sum;
}


/* Perform subtraction: N2 is subtracted from N1 and the value is
   returned.  The signs of N1 and N2 are ignored.  Also, N1 is
   assumed to be larger than N2.  SCALE_MIN is the minimum scale
   of the result. */
bc_num bc_struct::_bc_do_sub(bc_num n1, bc_num n2, int scale_min)
{
  bc_num diff;
  int diff_scale, diff_len;
  int min_scale, min_len;
  char *n1ptr, *n2ptr, *diffptr;
  int borrow, count, val;

  /* Allocate temporary storage. */
  diff_len = MAX (n1->n_len, n2->n_len);
  diff_scale = MAX (n1->n_scale, n2->n_scale);
  min_len = MIN  (n1->n_len, n2->n_len);
  min_scale = MIN (n1->n_scale, n2->n_scale);
  diff = bc_struct::new_num(diff_len, MAX(diff_scale, scale_min));

  /* Zero extra digits made by scale_min. */
  if (scale_min > diff_scale)
    {
      diffptr = (char *) (diff->n_value + diff_len + diff_scale);
      for (count = scale_min - diff_scale; count > 0; count--)
	*diffptr++ = 0;
    }

  /* Initialize the subtract. */
  n1ptr = (char *) (n1->n_value + n1->n_len + n1->n_scale -1);
  n2ptr = (char *) (n2->n_value + n2->n_len + n2->n_scale -1);
  diffptr = (char *) (diff->n_value + diff_len + diff_scale -1);

  /* Subtract the numbers. */
  borrow = 0;

  /* Take care of the longer scaled number. */
  if (n1->n_scale != min_scale)
    {
      /* n1 has the longer scale */
      for (count = n1->n_scale - min_scale; count > 0; count--)
	*diffptr-- = *n1ptr--;
    }
  else
    {
      /* n2 has the longer scale */
      for (count = n2->n_scale - min_scale; count > 0; count--)
	{
	  val = - *n2ptr-- - borrow;
	  if (val < 0)
	    {
	      val += BASE;
	      borrow = 1;
	    }
	  else
	    borrow = 0;
	  *diffptr-- = val;
	}
    }

  /* Now do the equal length scale and integer parts. */

  for (count = 0; count < min_len + min_scale; count++)
    {
      val = *n1ptr-- - *n2ptr-- - borrow;
      if (val < 0)
	{
	  val += BASE;
	  borrow = 1;
	}
      else
	borrow = 0;
      *diffptr-- = val;
    }

  /* If n1 has more digits then n2, we now do that subtract. */
  if (diff_len != min_len)
    {
      for (count = diff_len - min_len; count > 0; count--)
	{
	  val = *n1ptr-- - borrow;
	  if (val < 0)
	    {
	      val += BASE;
	      borrow = 1;
	    }
	  else
	    borrow = 0;
	  *diffptr-- = val;
	}
    }

  /* Clean up and return. */
  _bc_rm_leading_zeros (diff);
  return diff;
}

/* For many things, we may have leading zeros in a number NUM.
   _bc_rm_leading_zeros just moves the data "value" pointer to the
   correct place and adjusts the length. */
void bc_struct::_bc_rm_leading_zeros(bc_num num)
{
    /* We can move n_value to point to the first non zero digit! */
    while (*num->n_value == 0 && num->n_len > 1)
    {
        num->n_value++;
        num->n_len--;
    }
}

/*
 * CS:APP Data Lab
 *
 * <Kevin Nguyen, kdn433>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */;


#endif
/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
//////////////////////
// 1-point problems //
//////////////////////
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
	//DeMorgan's law was used
  	return ~(~x | ~y);
}
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
	//Shift and not x value to get the value
  	return !((x << 1) | !x);
}
/*
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
	//Create a mask and then reverse it
   	int x = 0xAA;
  	x = (x << 8) + x;
  	x = ~((x << 16) + x);
  	return x;
}
//////////////////////
// 2-point problems //
//////////////////////
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
	//Shift to create a mask then apply it, compare with another (same) mask to note any differences
   	int temp = (0xAA << 8) + 0xAA;
 	temp = (temp << 16) + temp;
 	return !((x & temp) ^ temp);
}
/*
 * isEqual - return 1 if x == y, and 0 otherwise
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
	//straight from the CS429 book itself...
  	return !(x^y);
}
/*
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
	//Variables to use
	unsigned temp = uf;
	unsigned expBits, mantissaBits;
	
	//Get masking onto temp to make positive, shift to get exp bits, and shift to get mantissa bits
	temp = temp & 0x7FFFFFFF;
	expBits = ((uf << 1) >> 24);
	mantissaBits = ((uf << 9) >> 9);
	
	//checks for NaN, else returns the absolute value
	if (expBits == 0xFF && mantissaBits != 0) {
		return uf;
	}
	return temp;
}
/*
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int leastBitPos(int x) {
	//reverse and add one to the mask (complement value) to change all 1's to 0's and vice versa
 	return (x & (~x+1));
}
/*
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
	//Temp variable
	int temp;

	//shift n & m to get max # of shifts available
	n = n << 3;
	m = m << 3;

	//shift to right and pick any differences then mask them with 1's to get positions, temp is a completed mask
	temp = (((x>>n) ^ (x>>m)) & 0xFF);
	
	//shift to left and compare with original and replace to swap out of mask
	return ((x ^ (temp<<n)) ^ (temp<<m));
}
//////////////////////
// 3-point problems //
//////////////////////
/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
	//variables
  	int temp, mask;

	//shift n to get max number of bits to shift	
	n = n << 3;

	//shift the mask and temp to get positioning
	mask = (0xFF<<n);
	temp = (c<<n);

	//right side won't matter, bytes are replaced regardless
	x = ((~mask & x) | temp);
	return x;
}
/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
	//variables
  	int sum = x + y; int temp = 0;

	//xor with the sum to guarantee sign differences with the sum, overflow signs if inputs are same but output is diff
	temp = ((x ^ sum) & (y ^ sum));

	//shift to find sign bit, use ! to get either 0 or 1 results
  	return !(temp >> 31);
}
/*
 * isGreater - if x > y  then return 1, else return 0
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
	//variables to use
	int sum, signx, signy;
	
	//compute sum and sign of x and y separately, compare with negative y
	sum = (x + (~y));
	signy = ((x & sum) | (~y));
	signx = (x | sum);

	//compare signs with & and shift the bits to get sign position
	return !((signx & signy)>>31);
}
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
	//Variables to use
	int lowCheck, highCheck;

	//add x to lower and high limits, sign indicates if value is too low or too high
	lowCheck = ((x + ~0x2F)>>31);
	highCheck = ((~x + 0x3A)>>31);	
	
	return (!lowCheck & !highCheck);
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {
	//Make a mask to manipulate parts of the bits sequence easier
	int temp = (0xFF << 8) + 0xFF;
	temp = (temp << 16) + temp;
	x = x>>n;

	//mask is initially off, but shifting from 32 and reversing it will give correct placement, answer is then found after or and xor
	return (x | (temp<<(32 + ~n))<<1) ^ ((temp<<(32 + ~n))<<1);
}
/*
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int rotateLeft(int x, int n) {
	//variables to use
	int temp1, temp2, mask;

	//Make a mask to manipulate parts of the bits sequence easier
	temp1 = (0xFF << 8) + 0xFF;
	temp1 = (temp1 << 16) + temp1;
	mask = ~(temp1 << n);
	
	//shift original so the mask can be applied properly into position
	temp2 = x << n;

	//combine with mask and recombine all parts shifting as necessary to the correct position
	return ((mask & ((x>>(32 + ~n))>>1)) | temp2);
}
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
  	//Variables to use
	int signBit;
	
	//obtain a neg sign bit and apply 5 times with the neg sign bits, last step is to divide by 8
	signBit = (((x<<2) + x) >> 31);
	return ((((x<<2) + x) + (signBit & 0x07))>>3);
}
//////////////////////
// 4-point problems //
//////////////////////
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
	//Variables to use
	int temp;
	
	//obtain the complement then apply to original, shift to get result on far left
	temp = ~x+1;

	return (((x | temp) >> 31) + 1);
}
/*
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
	//Make a mask of mostly 0's or 1's...logical or arithmetic?
	int mask = (x>>31);
	
	//reapply mask with original and compare differences to get absolute
	return ((x + mask) ^ mask);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	//variables to use
	int sum = 0, oneMask = 0x01;
	
	//..can't figure out a better way for this problem...
        sum = sum + (x & oneMask);
        sum = sum + ((x>>1) & oneMask);
        sum = sum + ((x>>2) & oneMask);
        sum = sum + ((x>>3) & oneMask);
        sum = sum + ((x>>4) & oneMask);
       	sum = sum + ((x>>5) & oneMask);
       	sum = sum + ((x>>6) & oneMask);
       	sum = sum + ((x>>7) & oneMask);
        sum = sum + ((x>>8) & oneMask);
        sum = sum + ((x>>9) & oneMask);
        sum = sum + ((x>>10) & oneMask);
        sum = sum + ((x>>11) & oneMask);
        sum = sum + ((x>>12) & oneMask);
        sum = sum + ((x>>13) & oneMask);
        sum = sum + ((x>>14) & oneMask);
        sum = sum + ((x>>15) & oneMask);
        sum = sum + ((x>>16) & oneMask);
        sum = sum + ((x>>17) & oneMask);
        sum = sum + ((x>>18) & oneMask);
        sum = sum + ((x>>19) & oneMask);
        sum = sum + ((x>>20) & oneMask);
        sum = sum + ((x>>21) & oneMask);
        sum = sum + ((x>>22) & oneMask);
        sum = sum + ((x>>23) & oneMask);
        sum = sum + ((x>>24) & oneMask);
        sum = sum + ((x>>25) & oneMask);
        sum = sum + ((x>>26) & oneMask);
        sum = sum + ((x>>27) & oneMask);
        sum = sum + ((x>>28) & oneMask);
        sum = sum + ((x>>29) & oneMask);
        sum = sum + ((x>>30) & oneMask);
        sum = sum + ((x>>31) & oneMask);
        return sum;
}
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  	return 2; //Too difficult
}
/*
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  	return 2; //Too difficult
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  	return 2; //Too difficult
}

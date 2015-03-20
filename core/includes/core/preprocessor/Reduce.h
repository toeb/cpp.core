/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
 /**
 * \file  core\preprocessor\Reduce.h
 *
 * \brief Declares Reduce macro
 */
#pragma once


#include <core/preprocessor/Variadic.h>


#define DS_REDUCE_1(M, SEPARATOR,X) M(X)
#define DS_REDUCE_2(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_1(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_3(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_2(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_4(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_3(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_5(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_4(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_6(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_5(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_7(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_6(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_8(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_7(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_9(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_8(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_10(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_9(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_N(N, M, SEPARATOR, ...) DS_CONCAT(DS_REDUCE_,N) (M,SEPARATOR,__VA_ARGS__)

/**
 * \brief Reduction of VA args list,  applies macro M to every element and adds SEPARATOR in
 *        between results
 *
 * \example DS_REDUCE(DS_NOOP,+,1,2,3,4,5,6,7) evaluates to 1+2+3+4+5+6+7
 *
 *
 * \param M         The void to process.
 * \param SEPARATOR The separator.
 */
#define DS_REDUCE(M,SEPARATOR,...) DS_REDUCE_N(DS_NUM_ARGS(__VA_ARGS__),M,SEPARATOR,__VA_ARGS__)


#define DS_REDUCE_COMMA_1(M,X) M(X)
#define DS_REDUCE_COMMA_2(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_1(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_3(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_2(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_4(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_3(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_5(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_4(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_6(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_5(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_7(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_6(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_8(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_7(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_9(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_8(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_10(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_9(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_11(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_10(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_12(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_11(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_13(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_12(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_14(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_13(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_15(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_14(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_16(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_15(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_17(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_16(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_18(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_17(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_19(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_18(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_20(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))), DS_REDUCE_COMMA_19(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_N(N, M,  ...) DS_CONCAT(DS_REDUCE_COMMA_,N) (M,__VA_ARGS__)

/**
 * \brief Same as DS_REDUCE except that the comma ',' is used as a separator.  this needs special treatment because the comma would cause DS_REDUCE to fail if passed as SEPARATOR
 *
 */
#define DS_REDUCE_COMMA(M,...) DS_REDUCE_COMMA_N(DS_NUM_ARGS(__VA_ARGS__),M,__VA_ARGS__)


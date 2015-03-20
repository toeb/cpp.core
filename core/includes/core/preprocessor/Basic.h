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
 * \file  core\preprocessor\Basic.h
 *
 * \brief Declares the basic macros which are reused many times in the projects.
 */
#pragma once

#define DS_PREPROCESSOR_ARG_COUNT 20

/**
 * \brief A macro that defines inline .
 *        Subprojects of DS should use this macro to show define a method as inline so the inline directive can be altered more easily
 *
 */
#define DS_INLINE inline

/**
 * \brief A macro that defines expands the passed template argument.
 *        this is often used to enforce correct behaviour in boxed macros
 *
 * \param X The void to process.
 */
#define DS_EXPAND(X) X



/**
 * \brief A macro that stringifies a macro token.
 *
 *  Stringify is boxed, because in particular cases just using the stringifiy operator # alone will not work correclty
 *
 * \param A The void to process.
 */
#define DS_STRINGIFY_(A) # A
#define DS_STRINGIFY__(A) DS_STRINGIFY_(A)
#define DS_STRINGIFY(A) DS_STRINGIFY__(A)


/**
 * \brief A macro for concatenating two Preprocessor Tokens
 *        this is used when A ## B does not work
 *
 * \param A.
 * \param B.
 */
#define DS_CONCAT(A,B) DS_CONCAT_(A,B)
#define DS_CONCAT_(A,B) A ## B
#define DS_CONCAT__(A,B) DS_CONCAT_(A,B)

/**
 * \brief A macro that creates a lambda to concatenate a string using stream out operator <<
 *        evaluates to a std::string
 *
 * \param ARGS  The arguments.
 */
#define DS_INLINE_STRING(ARGS) (std::function<std::string ()>([&]()->std::string {std::ostringstream stream; stream << ARGS; return stream.str(); }) () )

/**
 * \brief A macro that defines no operation (it is replaced by X)
 *
 *
 * \param X The void to process.
 */
#define DS_NOOP(X) DS_EXPAND(X)


/**
 * \brief A macro that defines a template arguments name.
 *
 * \param N number.
 */
#define DS_ARG_NAME(N) DS_CONCAT(A,N)

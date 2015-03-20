/**
 * \file core\preprocessor\Foreach.h
 *
 * \brief declares DS_FOREACH macro and its helper macros.
 */
#pragma once

#include <core/preprocessor/Variadic.h>

#define DS_FOREACH_1(M, X) M(X)
#define DS_FOREACH_2(M, ... )  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_1(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_3(M, ... )  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_2(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_4(M, ... )  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_3(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_5(M, ... )  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_4(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_6(M, ... )  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_5(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_7(M, ... )  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_6(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_8(M, ... )  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_7(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_9(M, ... )  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_8(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_10(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_9(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_11(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_10(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_12(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_11(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_13(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_12(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_14(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_13(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_15(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_14(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_16(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_15(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_17(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_16(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_18(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_17(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_19(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_18(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_20(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_19(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_21(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_20(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_22(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_21(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_23(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_22(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_24(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_23(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_25(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_24(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_26(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_25(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_27(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_26(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_28(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_27(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_29(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_28(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_FOREACH_30(M, ... ) DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) DS_FOREACH_29(M,DS_EXPAND(DS_REST(__VA_ARGS__)))

#define DS_FOREACH_N(N,M,...) DS_CONCAT(DS_FOREACH_,N) (M,__VA_ARGS__)

/**
 * \brief A macro that applies M to every element in the argument list.
 *        Warning: this currently works for max 30 arguments (it is easily extendable)
 *
 * \param M The macro whihc is to be applied
 *
 * \example #define PRINT_OPERATION(X) std::cout << X << std::endl;
 *          DS_FOREACH(PRINT_OPERATION, 1,2,3,4,5) ->  std::cout << 1 << std::endl; std::cout << 2 << std::endl; std::cout << 3 << std::endl; std::cout << 4 << std::endl; std::cout << 5 << std::endl;
 */
#define DS_FOREACH(M, ...) DS_FOREACH_N(DS_NUM_ARGS(__VA_ARGS__),M,__VA_ARGS__)

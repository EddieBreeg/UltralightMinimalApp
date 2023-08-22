#ifndef MACROS_H
#define MACROS_H

#ifndef NDEBUG
#include <iostream>
#include <cassert>

#define TRY_OR_LOG(expr)               \
    try                                \
    {                                  \
        expr;                          \
    }                                  \
    catch (const std::exception &e)    \
    {                                  \
        std::cerr << e.what() << '\n'; \
    }

#define DEBUG_LOG(x) std::cout << x << std::endl
#else
#define DEBUG_LOG(x) (void *)0
#define TRY_OR_LOG(expr) expr
#endif

#endif
#pragma once

#include <cstdlib>
#include <cstdio>
#include <stdexcept>

#define BRED    "\033[1;31m"
#define BGREEN  "\033[1;32m"
#define BYELLOW "\033[1;33m"
#define GREEN   "\033[1;35m"
#define BCYAN   "\033[1;36m"
#define RESET   "\033[0m"

#define VERIFY_CONTRACT(contract, format, ...)                \
    do {                                                      \
        if (!(contract)) {                                    \
            char explanation_str[100];                        \
            snprintf(                                         \
                explanation_str, sizeof(explanation_str),     \
                "[%s:%d] " format,                            \
                __FILE__, __LINE__,                           \
                ##__VA_ARGS__);                               \
                                                              \
            throw std::runtime_error(explanation_str);        \
        }                                                     \
    } while (0)

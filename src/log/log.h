
#ifndef _LOG_H_
#define _LOG_H_
#include <stdio.h>

#ifdef _cplusplus
extern "C" {
#endif

#define __op printf

#define RED(fmt) "\x1b[31m" fmt "\x1b[0m"
#define GREEN(fmt) "\x1b[32m" fmt "\x1b[0m"
#define YELLOW(fmt) "\x1b[33m" fmt "\x1b[0m"

#define log_d(...) __op("D:" __VA_ARGS__)
#define log_i(...) __op(GREEN("I:") __VA_ARGS__)
#define log_w(...) __op(YELLOW("W:") __VA_ARGS__)
#define log_e(...) __op(RED("E:") __VA_ARGS__)
#define log log_d
#define logl(...) log(__VA_ARGS__ "\n")

#ifdef _cplusplus
}
#endif

#endif

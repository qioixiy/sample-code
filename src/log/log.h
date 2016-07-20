#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <sys/time.h>

#ifdef _cplusplus
extern "C" {
#endif

#define __op(...) printf(__VA_ARGS__)

#define RED(fmt) "\x1b[31m" fmt "\x1b[0m"
#define GREEN(fmt) "\x1b[32m" fmt "\x1b[0m"
#define YELLOW(fmt) "\x1b[33m" fmt "\x1b[0m"

#define log_d(...) __op("D:" __VA_ARGS__)
#define log_i(...) __op(GREEN("I:") __VA_ARGS__)
#define log_w(...) __op(YELLOW("W:") __VA_ARGS__)
#define log_e(...) __op(RED("E:") __VA_ARGS__)
    /* line */
#define logl_d(...) log_d(__VA_ARGS__ "\n")
#define logl_i(...) log_i(__VA_ARGS__ "\n")
#define logl_w(...) log_w(__VA_ARGS__ "\n")
#define logl_e(...) log_e(__VA_ARGS__ "\n")

#define log log_d
#define logl logl_d

#ifdef _cplusplus
}
#endif

#endif

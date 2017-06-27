#include <stddef.h>
#include "defer.h"

extern struct defer_func_ctx ctx_stack[10];

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *this_fn, void *call_site) {
    struct defer_func_ctx *ctx = NULL;

    while ((ctx = stack_pop()) != NULL) {
        if (ctx->params_count == 0) {
            ctx->ctx.zp.df();
        } else if (ctx->params_count == 1) {
            ctx->ctx.op.df(ctx->ctx.op.p1);
        } else if (ctx->params_count == 2) {
            ctx->ctx.tp.df(ctx->ctx.tp.p1, ctx->ctx.tp.p2);
        }
    }
}

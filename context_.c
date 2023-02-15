#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#define MEM 64000
#include <stdio.h>
#include <ucontext.h>
#include <stdbool.h>

static ucontext_t ctx;

static void conjecture(int len, void* options, int sz, void (*fn)(void*)) {
    char* st1 = (char*)malloc(len * sz);
    getcontext(&ctx);
    ctx.uc_stack.ss_sp = st1;
    ctx.uc_stack.ss_size = len * sz;
    makecontext(&ctx, (void (*)(void))fn, 1, options);
    setcontext(&ctx);
}

void assert(bool b) {
    if (!b) {
        free(ctx.uc_stack.ss_sp);
        setcontext(&ctx);
    }
}

bool is_prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

bool is_lt_40(int x) {
    return x < 40;
}

int nested(int i) {
    assert(!is_prime(i));
    return i * i;
}

void app(void* c) {
    int* i = (int*)c;
    assert(is_lt_40(*i));
    int x = nested(*i);
    printf("%d\n", x);
}

int main(void) {
    int mynums[] = {11, 23, 42, 39, 55};
    conjecture(5, mynums, sizeof(int), &app);
    return 0;
}

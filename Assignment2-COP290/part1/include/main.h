#ifndef part1


#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#define MEM 64000
#include <stdio.h>
#include <ucontext.h>
#include <stdbool.h>

bool is_lt_40(int x);
bool is_prime(int x);
void assert(bool b);
int nested(int i) ;
void app(void* c) ;
static void conjecture(int len, void* options, int sz, void (*fn)(void*));
int main(void);



#endif
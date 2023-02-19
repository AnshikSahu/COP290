#ifndef THREAD_H
#define THREAD_H

#include "list.h"
#define _XOPEN_SOURCE 600
#include <stddef.h>
#include <stdlib.h>
#include <ucontext.h>
#include <signal.h>
#include <unistd.h>

#define STACK_SIZE 64000

struct list *ThreadList;
ucontext_t *main_context;

void mythread_init();

ucontext_t* mythread_create(void func(void*), void* arg);

void mythread_join();

void mythread_yield();

struct lock {
    ucontext_t* ctx;
};

struct lock* lock_new();

void lock_acquire(struct lock* lk);

int lock_release(struct lock* lk);

#endif
/*#ifndef THREAD_H
#define THREAD_H

#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>

void mythread_init();      // Initialize threads list
ucontext_t* mythread_create(void func(void*), void* arg);  // Create a new thread
void mythread_join();  // Waits for other thread to complete. It is used in case of dependent threads.
void mythread_yield();  // Perform context switching here

struct lock {
	ucontext_t* ctx;
};
struct lock* lock_new();   // return an initialized lock object
void lock_acquire(struct lock* lk);   // Set lock. Yield if lock is acquired by some other thread.
int lock_release(struct lock* lk);   // Release lock

#endif
#ifndef THREAD_H
#define THREAD_H

#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>

void mythread_init();      // Initialize threads list
ucontext_t* mythread_create(void func(void*), void* arg);  // Create a new thread
void mythread_join();  // Waits for other thread to complete. It is used in case of dependent threads.
void mythread_yield();  // Perform context switching here

struct lock {
	ucontext_t* ctx;
};
struct lock* lock_new();   // return an initialized lock object
void lock_acquire(struct lock* lk);   // Set lock. Yield if lock is acquired by some other thread.
int lock_release(struct lock* lk);   // Release lock

#endif
*/
#include "mythread.h"
#include "hm.c"
#include "list.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>

#define STACK_SIZE 8192

typedef struct Thread {
    ucontext_t context;
    void (*func)(void*);
    void *arg;
    struct Thread *next;
} Thread;

Thread *current_thread;
void mythread_init(){
	current_thread = NULL;
}

ucontext_t* mythread_create(void func(void*), void* arg){
    Thread *thread = (Thread*)malloc(sizeof(Thread));
    if (thread == NULL) {
        return NULL;
    }

    thread->func = func;
    thread->arg = arg;
    thread->next = current_thread;

    getcontext(&thread->context);
    thread->context.uc_stack.ss_sp = malloc(STACK_SIZE);
    thread->context.uc_stack.ss_size = STACK_SIZE;
    thread->context.uc_link = &current_thread->context;
    makecontext(&thread->context, (void (*)(void))thread->func,1, thread->arg);

    current_thread = thread;

    return (void*)thread;
}   


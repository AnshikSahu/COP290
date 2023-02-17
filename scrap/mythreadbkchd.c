/**
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
void mythread_join();  // Waits for other thread to complete.
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
#include "list.h"
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
    struct ucontext_t *context;
    void (*func)(void*);
    void *arg;
    struct Thread *next;
} Thread;

struct list *ThreadList;
struct ucontext_t *current_context;

void mythread_init(){
    ThreadList = list_new();
    current_context= NULL;
}

ucontext_t* mythread_create(void func(void*), void* arg){
    Thread *thread = (Thread*)malloc(sizeof(Thread));
    if (thread == NULL) {
        return NULL;
    }

    thread->func = func;
    thread->arg = arg;
    thread->next = ThreadList->head->data;

    getcontext(&thread->context);
    (*(thread->context)).uc_stack.ss_sp = malloc(STACK_SIZE);
    (*(thread->context)).uc_stack.ss_size = STACK_SIZE;
    (*(thread->context)).uc_link = ThreadList->head->data->context;
    makecontext(&thread->context, (void (*)(void))thread->func,1, thread->arg);

    list_add(ThreadList,thread);

    return (void*)thread;
}   

/*void mythread_yield(){
    listentry *prev_ = ThreadList->head;
    listentry *current = ThreadList->head->next;
    if(current_thread=NULL){
        current_thread= prev_thread;
    }
    ThreadList->head = current_thread;
    list_rm(ThreadList,prev_thread);
    list_add(ThreadList,prev_thread);
    current_context = &current_thread->data->context;
    swapcontext(&prev_thread->context, &current_thread->context);
}*/

void mythread_join(){
    ucontext_t *prev_context;
    while (ThreadList->head->next != NULL) {
        prev_context= current_context;
        current_context =ThreadList->head->data->context;
        swapcontext(prev_context, current_context);
        list_rm(ThreadList,ThreadList->head);
    }
}

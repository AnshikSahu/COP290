#include "hm.h"
#define _XOPEN_SOURCE 600
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>
#include <signal.h>
#include <unistd.h>

#define STACK_SIZE 8192

struct list *ThreadList;
ucontext_t *main_context;

void mythread_init(){
    ThreadList = list_new();
    main_context = (ucontext_t*)malloc(8192);
}

ucontext_t* mythread_create(void func(void*), void* arg){
    ucontext_t *context= (ucontext_t*)malloc(sizeof(ucontext_t));
    getcontext(context);
    (*context).uc_stack.ss_sp = malloc(STACK_SIZE);
    (*context).uc_stack.ss_size = STACK_SIZE;
    (*context).uc_link = main_context;
    makecontext(context, (void (*)(void))func,1,arg);
    list_add(ThreadList,context);

    return context;
}

void mythread_join(){
    getcontext(main_context);
    while (ThreadList->head != NULL) {
        swapcontext(main_context, ThreadList->head->data);
        list_rm(ThreadList,ThreadList->head);
        }
    }

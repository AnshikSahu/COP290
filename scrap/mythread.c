#include "mythread.h"
#include "hm.c"
#include "list.c"
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
    printf("Hello");
    (*main_context).uc_stack.ss_sp = (char *)malloc(STACK_SIZE);
    (*main_context).uc_stack.ss_size = STACK_SIZE;
}

ucontext_t* mythread_create(void func(void*), void* arg){
    ucontext_t *context= (ucontext_t*)malloc(STACK_SIZE);
    printf("Hello");
    (*context).uc_stack.ss_sp = malloc(STACK_SIZE);
    (*context).uc_stack.ss_size = STACK_SIZE;
    (*context).uc_link = main_context;
    getcontext(context);
    printf("Hello");
    makecontext(context, (void (*)(void))func,1,arg);
    printf("Hello");
    list_add(ThreadList,context);

    return context;
}

void mythread_join(){
    printf("Hello joining");
    if(ThreadList->head == NULL){
        printf("No threads to join");
    }
    else{
        printf("Hello joining");
    }
    getcontext(main_context);
    while (ThreadList->head != NULL) {
        printf("Hello switching");
        swapcontext(main_context, ThreadList->head->data);
        list_rm(ThreadList,ThreadList->head);
        }
    }

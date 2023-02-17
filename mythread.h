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
    printf("Hello\n");
    main_context = (ucontext_t*)malloc(8192);
}

ucontext_t* mythread_create(void func(void*), void* arg){
    ucontext_t *context= (ucontext_t*)malloc(sizeof(ucontext_t));
    printf("Hello");
    getcontext(context);
    (*context).uc_stack.ss_sp = malloc(STACK_SIZE);
    (*context).uc_stack.ss_size = STACK_SIZE;
    (*context).uc_link = main_context;
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

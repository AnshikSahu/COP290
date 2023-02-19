#include "mythread.h"

#define STACK_SIZE 64000

void mythread_init(){
    ThreadList = list_new();
    main_context = (ucontext_t*)malloc(STACK_SIZE);
}

ucontext_t* mythread_create(void func(void*), void* arg){
    ucontext_t *context= (ucontext_t*)malloc(STACK_SIZE);
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

void mythread_yield(){
    if(ThreadList->head != NULL ){
        if(ThreadList->head->next != NULL){
    ucontext_t* prev_context = (ucontext_t*)malloc(STACK_SIZE);
    prev_context = (ucontext_t*)ThreadList->head->data;
     ucontext_t* next_context = (ucontext_t*)malloc(STACK_SIZE);
    next_context = (ucontext_t*)ThreadList->head->next->data;
    ThreadList->tail->next = ThreadList->head;
    ThreadList->tail = ThreadList->head;
    // struct listentry *l1=ThreadList->head->next;
    list_rm(ThreadList,ThreadList->head);
    ThreadList->tail->next = NULL;
    // while(l1->next != NULL){
    //     l1=l1->next;
    // }
    swapcontext(prev_context,next_context);
    }}
}

struct lock* lock_new(){
    struct lock* lk = (struct lock*)malloc(sizeof(struct lock));
    return lk;
}

void lock_acquire(struct lock* lk){
    while(lk->ctx != NULL){
        mythread_yield();
    }
        lk->ctx = ThreadList->head->data;
}

int lock_release(struct lock* lk){
    lk->ctx = NULL;
        return 1;
}
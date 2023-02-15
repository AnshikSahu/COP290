#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 1024*1024 // 1MB

typedef struct Thread {
    ucontext_t context;
    void (*func)(void*);
    void *arg;
    struct Thread *next;
} Thread;

Thread *current_thread = NULL;
Thread *thread_list = NULL;

void thread_start(void (*func)(void*), void *arg) {
    func(arg);
    current_thread->next->context.uc_link = NULL;
    current_thread = current_thread->next;
    setcontext(&current_thread->context);
}

void* mythread_create(void (*func)(void*), void *arg) {
    Thread *thread = (Thread*)malloc(sizeof(Thread));
    if (thread == NULL) {
        return NULL;
    }

    thread->func = func;
    thread->arg = arg;
    thread->next = thread_list;

    getcontext(&thread->context);
    thread->context.uc_stack.ss_sp = malloc(STACK_SIZE);
    thread->context.uc_stack.ss_size = STACK_SIZE;
    thread->context.uc_link = &current_thread->context;
    makecontext(&thread->context, (void (*)(void))thread_start, 2, thread->func, thread->arg);

    thread_list = thread;

    return (void*)thread;
}

void mythread_join(void *thread_ptr) {
    Thread *thread = (Thread*)thread_ptr;

    while (thread_list != NULL && thread != thread_list) {
        if (thread_list->next == thread) {
            thread_list->next = thread->next;
            break;
        }
        thread_list = thread_list->next;
    }

    if (thread_list == NULL) {
        return;
    }

    current_thread = thread;
    swapcontext(&current_thread->next->context, &current_thread->context);
}

void example_func(void *arg) {
    int n = *(int*)arg;
    printf("Thread %d started\n", n);
    for (int i = 0; i < 100000000; i++);
    printf("Thread %d finished\n", n);
}

int main() {
    int arg1 = 1, arg2 = 2;

    void *thread1 = mythread_create(example_func, &arg1);
    void *thread2 = mythread_create(example_func, &arg2);

    mythread_join(thread1);
    mythread_join(thread2);

    printf("All threads finished\n");

    return 0;
}

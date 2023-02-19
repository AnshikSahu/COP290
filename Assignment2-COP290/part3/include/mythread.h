/**
 * @file mythread.h
 * @brief A simple thread library using ucontext.h in C.
 */

#ifndef THREAD_H
#define THREAD_H

#include<stdio.h>
#define _XOPEN_SOURCE 600
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>

/**
 * @brief Initializes the thread library.
 */

void mythread_init();

/**
 * @brief Creates a new thread.
 * @param func A pointer to the function to be executed in the new thread.
 * @param arg A pointer to the argument to be passed to the function.
 * @return A pointer to the new thread's context.
 */

void* mythread_create(void func(void*), void* arg);

/**
 * @brief Waits for all threads to complete, and removes the context once it is complete. Used in case of dependent threads.
 */

void mythread_join();

/**
 * @brief If there are more than one contexts in the list then switch the context with its successive context.
 */

void mythread_yield();

/**
 * @brief Lock is a flag which checks if some word has been acquired by a context.
 */

struct lock {
	void* c;
};

/**
 * @brief Creates a new lock.
 * 
 * @return A pointer to the new lock.
 */

struct lock* lock_new();

/**
 * @brief Acquires a lock.
 * 
 * If the lock is already owned by another thread, the current thread will be blocked
 * until the lock is released by its owner.
 * 
 * @param lk Pointer to the lock to acquire.
 */

void lock_acquire(struct lock* lk);

/**
 * @brief Releases a context from a lock, if it has been acquired.
 * @param lk Pointer to the lock to release.
 * @return 0 on success, -1 on failure.
 */

int lock_release(struct lock* lk);

#endif

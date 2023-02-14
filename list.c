/*#ifndef LIST_H
#define LIST_H
struct list {
	struct listentry* head;
	struct listentry* tail;
};

struct listentry {
	void *data;
	struct listentry *prev;
	struct listentry *next;
};

void list_rm(struct list* l, struct listentry* e);    // Remove an item from the list
struct listentry* list_add(struct list* l, void* data);  // Add an item to the list
struct list* list_new();  // Return an initialized list
int is_empty(struct list* l);  // Check if list is empty or not
#endif*/
#include "list.h"
#include <stddef.h>
struct list* list_new() {
    struct list* l = malloc(sizeof(struct list));
    l->head = NULL;
    l->tail = NULL;
    return l;
}

struct listentry* list_add(struct list* l, void* data) {
    struct listentry* e = malloc(sizeof(struct listentry));
    e->data = data;
    e->prev = NULL;
    e->next = NULL;
    if (l->head == NULL) {
        l->head = e;
        l->tail = e;
    } else {
        l->tail->next = e;
        e->prev = l->tail;
        l->tail = e;
    }
    return e;
}

void list_rm(struct list* l, struct listentry* e) {
    if (e->prev == NULL) {
        l->head = e->next;
    } else {
        e->prev->next = e->next;
    }
    if (e->next == NULL) {
        l->tail = e->prev;
    } else {
        e->next->prev = e->prev;
    }
    free(e);
}

int is_empty(struct list* l) {
    return l->head == NULL;
}
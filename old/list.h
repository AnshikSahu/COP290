#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct list {
	struct listentry* head;
	struct listentry* tail;
};
struct listentry {
	void *data;
	struct listentry *prev;
	struct listentry *next;
};

struct list* list_new() {
    struct list* l =malloc(sizeof(struct list));
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
        l->head->prev = e;
        e->next = l->head;
        l->head = e;
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
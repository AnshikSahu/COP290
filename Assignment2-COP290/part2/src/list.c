#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



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
        l->head->next = e;
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
}


int is_empty(struct list* l){
	if(l->head==NULL){
		return 1;}
	return 0;
}
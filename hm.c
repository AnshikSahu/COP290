/*#include "list.h"
#include "mythread.h"
#include <stdlib.h>
#define SZ 4096

struct hashmap_element_s {
  char *key;
  void *data;
};

struct hashmap_s {
  struct list* table[SZ];
  struct lock* lk[SZ];
};


int hashmap_create(struct hashmap_s *const out_hashmap);   // Initialize a hashmap
int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data);   // Set value of the key as data in hashmap. You can use any method to resolve conflicts. Also write your own hashing function
void* hashmap_get(struct hashmap_s *const hashmap, const char* key);    // Fetch value of a key from hashmap
void hashmap_iterator(struct hashmap_s* const hashmap, 
                        int (*f)(struct hashmap_element_s *const));  // Execute argument function on each key-value pair in hashmap

int acquire_bucket(struct hashmap_s *const hashmap, const char* key);   // Acquire lock on a hashmap slot
int release_bucket(struct hashmap_s *const hashmap, const char* key);   // Release acquired lock
*/

#include "hm.h"
#include <stdlib.h>
#include <string.h>
unsigned long hash_key(const char* word){
  unsigned long val=0;
  int i;
  for(i=0;i<strlen(word);i++){
    val=(val*37)%SZ+word[i];
  }
  return val%SZ;
}

int hashmap_create(struct hashmap_s *const out_hashmap){
  int i;
  for(i=0;i<SZ;i++){
    out_hashmap->table[i]=list_new();
   /*out_hashmap->lk[i]=lock_create();*/
  }
  return 0;
}

int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data){
  int index=hash_key(key);
  /*lock_acquire(hashmap->lk[index]);*/
  struct hashmap_element_s *new_element=malloc(sizeof(struct hashmap_element_s));
  new_element->key=malloc(sizeof(char)*strlen(key));
  strcpy(new_element->key,key);
  new_element->data=data;
  list_add(hashmap->table[index],new_element);
  /*lock_release(hashmap->lk[index]);*/
  return 0;
}

void* hashmap_get(struct hashmap_s *const hashmap, const char* key){
  int index=hash_key(key);
  /*lock_acquire(hashmap->lk[index]);*/
  struct list* list=hashmap->table[index];
  struct listentry* e;
  for(e=list->head;e!=NULL;e=e->next){
    struct hashmap_element_s *element= e->data;
    if(strcmp(element->key,key)==0){
      /*lock_release(hashmap->lk[index]);*/
      return element->data;
    }
  }
  /*lock_release(hashmap->lk[index]);*/
  return NULL;
}

void hashmap_iterator(struct hashmap_s* const hashmap, int (*f)(struct hashmap_element_s *const)){
  int i;
  for(i=0;i<SZ;i++){
    /*lock_acquire(hashmap->lk[i]);*/
    struct list* list=hashmap->table[i];
    struct listentry* e;
    for(e=list->head;e!=NULL;e=e->next){
      struct hashmap_element_s *element=e->data;
      f(element);
    }
    /*lock_release(hashmap->lk[i]);*/
  }
}

/*int acquire_bucket(struct hashmap_s *const hashmap, const char* key){
  int index=hash_key(key);
  lock_acquire(hashmap->lk[index]);
  return 0;
}

int release_bucket(struct hashmap_s *const hashmap, const char* key){
  int index=hash_key(key);
  lock_release(hashmap->lk[index]);
  return 0;
}*/

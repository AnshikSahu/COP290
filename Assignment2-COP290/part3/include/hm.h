/**
 * @file 
 * @brief Implementation of a hash map data structure.
 */
#include "mythread.h"
#include "list.h" 
#include <stdlib.h>
#include <string.h>
#define SZ 4096

/**
 * @brief A structure representing an element in the hash map.
 * 
 */

struct hashmap_element_s {
  char *key; ///< The key associated with the element.
  void *data; ///< The data associated with the element.
};
/**
 * @brief A structure representing a hash map.
 * 
 */

struct hashmap_s {
  struct list* table[SZ]; ///< An array of linked lists to store the elements.
  struct lock* lk[SZ]; ///< An array of locks whose the ith index stores the state of lock i.e. if it is not locked or if it is, then which context has locked it
};


/**
 * @brief Computes the hash value for a given key.
 * 
 * @param word Takes the word which has to be hashed as input.
 * @return The hash value of the key, type unsigned long.
 */


unsigned long hash_key(const char* word); 

/**
 * @brief Initializes a hash map.
 * 
 * @param out_hashmap out_hashmap A pointer to the hash map to initialize.
 * @return int, 0 on success, -1 on failure.
 */

int hashmap_create(struct hashmap_s *const out_hashmap);

/**
 * @brief Associates a value with a key in a hash map.
 * 
 * @param hashmap The hash map to modify.
 * @param key The key to associate the value with.
 * @param data A pointer to the value to associate with the key.
 * @return int, 0 on success, -1 on failure.
 */

int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data);

/**
 * @brief Retrieves the value associated with a given key in a hash map.
 * 
 * @param hashmap The hashmap to search
 * @param key The key to search for.
 * @return A pointer to the value associated with the key, or NULL if the key is not found, type void*. 
 */

void* hashmap_get(struct hashmap_s *const hashmap, const char* key);

/**
 * @brief Calls a given function for each element in a hash map.
 * @param hashmap The hash map to iterate over.
 * @param f The function to call for each element.
 */

void hashmap_iterator(struct hashmap_s* const hashmap, 
                        int (*f)(struct hashmap_element_s *const));

/**
 * @brief Acquires a lock on a hashmap slot, if the bucket is empty alloctes lock else yields until the existing context in the bucket releases the bucket.
 * @param hashmap The hash map to search.
 * @param key The key of the map which wants to acquire the bucket.
 */

int acquire_bucket(struct hashmap_s *const hashmap, const char* key);

/**
 * @brief The acquired context releases the bucket.
 * @param hashmap The hash map to search.
 * @param key The key of the map which wants to release the bucket.
 */

int release_bucket(struct hashmap_s *const hashmap, const char* key);
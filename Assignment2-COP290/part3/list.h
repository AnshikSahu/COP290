/**
 * @file
 * @brief A simple linked list implementation in C.
 */
#ifndef LIST_H
#define LIST_H

/**
 * @brief A linked list data structure.
 */
struct list {
	struct listentry *head; /**< Pointer to the head of the list. */
	struct listentry *tail; /**< Pointer to the tail of the list. */
};
/**
 * @brief A node in a linked list.
 */
struct listentry {
	void *data; /**< Pointer to the data stored in the node. */
	struct listentry *prev; /**< Pointer to the previous node in the list. */
	struct listentry *next; /**< Pointer to the next node in the list. */
};

/**
 * @brief Removes a node from the list.
 * @param l A pointer to the list to remove the node from.
 * @param e A pointer to the node to be removed.
 */

void list_rm(struct list *l, struct listentry *e);		

/**
 * @brief Adds a new node with the given data to the head of the list.
 * @param l A pointer to the list to add the node to.
 * @param data A pointer to the data to be stored in the new node.
 * @return A pointer to the new node.
 */

struct listentry *list_add(struct list *l, void *data); 	

/**
 * @brief Creates a new, empty list.
 * @return A pointer to the new list.
 */

struct list *list_new();					

/**
 * @brief Checks if a list is empty.
 * @param l A pointer to the list to remove the node from.
 */


int is_empty(struct list *l);					
#endif

/*
 * @author  Vincent Johansson
 * @since   2020-12-22
 *
 */


#ifndef LIST_H
#define LIST_H

#include <stdbool.h>


/**
 * @defgroup module Double Linked List
 *
 * @brief Double linked list
 *
 * A list constructed with double linked nodes.
 *
 * @{
 */


 /**
  * @brief Struct for the nodes.
  *
  * Definition of the struct for the nodes the list is built upon.
  *
  */
struct node
{
    struct node *next;
    struct node *prev;
    char *value;
};


/**
 * @brief Struct for the list.
 *
 * Definition of the list struct containing the head.
 *
 */
typedef struct list
{
    struct node head;
} List;


/**
 * @brief Struct for the list position.
 *
 * Definition of the position struct used to move in the list.
 *
 */
typedef struct list_pos
{
    struct node *node;
} ListPos;


/**
 * @brief Creates an empty list.
 *
 * Creates an empty list with header node.
 *
 * @return Pointer to the list.
 */
List *list_create(void);


/**
 * @brief Destroys the list.
 *
 * Frees the allocated memory for the list.
 *
 * @param *lst Pointer to the list to be destroyed.
 */
void list_destroy(List *lst);


/**
 * @brief Checks if list is empty.
 *
 * Takes given list and checks if it's empty.
 *
 * @param *lst Pointer to the list that is to be checked.
 *
 * @return true if empty, false if not.
 */
bool list_is_empty(const List *lst);


/**
 * @brief Get position of first element.
 *
 * Looks up the position of the first element of the list.
 *
 * @param *lst Pointer to the list that is to be checked.
 *
 * @return Pointer to the first value of the list.
 */
ListPos list_first(List *lst);


/**
 * @brief Get position of the element after the last element.
 *
 * Looks up the position of the element after the last element in the list.
 *
 * @param *lst Pointer to the list that is to be checked.
 *
 * @return Pointer to the element after the last element of the list.
 */
ListPos list_end(List *lst);


/**
 * @brief Check equality between two positions.
 *
 * Checks if the values of two elements are equal.
 *
 * @param p1 Position of the first element.
 * @param p2 Position of the second element.
 *
 * @return true if equal, false if not.
 */
bool list_pos_equal(ListPos p1, ListPos p2);


/**
 * @brief Move pos to next position.
 *
 * Points pos to the next element in the list.
 *
 * @param pos Pointer to the current position in the list.
 *
 * @return Pointer to the new position in the list.
 */
ListPos list_next(ListPos pos);


/**
 * @brief Move pos to previous position.
 *
 * Points pos to the previous element in the list.
 *
 * @param pos Pointer to the current position in the list.
 *
 * @return Pointer to the new position in the list.
 */
ListPos list_prev(ListPos pos);


/**
 * @brief Insert new value in the list.
 *
 * Inserts given value before the current position and returns the
 * position of the new element.
 *
 * @param pos Pointer to the current position in the list.
 * @param *value Pointer to where the value to be inserted is stored.
 *
 * @return Position of the new element.
 */
ListPos list_insert(ListPos pos, const char *value);


/**
 * @brief Remove a value from the list.
 *
 * Removes value at the given position and return the position op
 * the next element in the list.
 *
 * @param pos Pointer to the current position in the list.
 *
 * @return Position of the element after the removed one.
 */
ListPos list_remove(ListPos pos);


// Get the value at the position.
/**
 * @brief Gets the value at given position.
 *
 * Gets the value of the element at the given position in the list.
 *
 * @param pos Pointer to the current position in the list.
 *
 * @return The value of the element at the given position.
 */
const char *list_inspect(ListPos pos);


#endif /* LIST_H */

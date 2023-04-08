/*
 * @author  Vincent Johansson
 * @since   2021-01-04
 *
 */


#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#include "list.h"


/**
 * @defgroup module Queue
 *
 * @brief A queue.
 *
 * A queue implemented with the help of the abstract datatype List.
 *
 * @{
 */


/**
 * @brief Struct for the queue.
 *
 * Definition of the struct for the queue.
 *
 */
typedef struct queue
{
    List *list;
} Queue;


/**
 * @brief Creates an empty queue.
 *
 * Creates an empty queue.
 *
 * @return Pointer to the queue.
 */
Queue *queue_create(void);


/**
 * @brief Destroys the queue.
 *
 * Frees the allocated memory for the queue.
 *
 * @param *q Pointer to the queue to be destroyed.
 */
void queue_destroy(Queue *q);


/**
 * @brief Insert new value in the queue.
 *
 * Inserts given value at the tail of the queue.
 *
 * @param *q Pointer to the queue which the value is to be added to.
 * @param *value Pointer to where the value to be inserted is stored.
 */
void queue_enqueue(Queue *q, const char *value);


/**
 * @brief Remove a value from the queue.
 *
 * Removes value at the front of the queue.
 *
 * @param *q Pointer to the queue from which value is to be removed from.
 *
 * @return Value of the new element in the front of the queue.
 */
char *queue_dequeue(Queue *q);


/**
 * @brief Checks if queue is empty.
 *
 * Takes given queue and checks if it's empty.
 *
 * @param *q Pointer to the queue that is to be checked.
 *
 * @return true if empty, false if not.
 */
bool queue_is_empty(const Queue *q);


#endif /* QUEUE_H */

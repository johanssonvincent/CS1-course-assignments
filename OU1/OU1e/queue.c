/*
 * @author  Vincent Johansson
 * @since   2021-01-04
 *
 */

#include <stdlib.h>
#include "queue.h"

Queue *queue_create(void){
    Queue *q = malloc(sizeof(Queue));
    q->list = list_create();
    return q;
}


void queue_destroy(Queue *q){
    list_destroy(q->list);
    free(q);
}


void queue_enqueue(Queue *q, const char *value){
    list_insert(list_end(q->list), value);
}


char *queue_dequeue(Queue *q){
    ListPos pos = list_remove(list_first(q->list));
    return pos.node->value;
}


bool queue_is_empty(const Queue *q){
    return list_is_empty(q->list);
}

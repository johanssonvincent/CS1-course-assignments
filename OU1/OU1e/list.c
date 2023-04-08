/*
 * @author  Vincent Johansson
 * @since   2020-01-07
 *
 */


#include <stdlib.h>
#include <string.h>
#include "list.h"


static char *clone_string(const char *in){
    size_t len = strlen(in);
    char *out = calloc(len + 1, sizeof(char));
    strcpy(out, in);
    return out;
}


static struct node *make_node(const char *value){
    // Memory allocation for new node.
    struct node *newNode = malloc(sizeof(struct node));

    // Initialization of the new node and assigning the given value to
    // the new node.
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->value = clone_string(value);

    return newNode;
}


List *list_create(void){
    // Memory allocation for the list.
    List *lst = calloc(1, sizeof(struct list));

    // Initialization of the head node.
    lst->head.next = &lst->head;
    lst->head.prev = &lst->head;

    return lst;
}


void list_destroy(List *lst){
    free(lst);
}


bool list_is_empty(const List *lst){
    return (lst->head.next == &lst->head);
}


ListPos list_first(List *lst){
    ListPos pos = {
        .node = lst->head.next
    };
    return pos;
}


ListPos list_end(List *lst){
    ListPos pos = {
        .node = &lst->head
    };
    return pos;
}


bool list_pos_equal(ListPos p1, ListPos p2){
    return (p1.node->value == p2.node->value);
}


ListPos list_next(ListPos pos){
    pos.node = pos.node->next;
    return pos;
}


ListPos list_prev(ListPos pos){
    pos.node = pos.node->prev;
    return pos;
}


ListPos list_insert(ListPos pos, const char *value){
    // Create a new node.
    struct node *node = make_node(value);

    // Find nodes before and after (may be the same node: the head of the list).
    struct node *before = pos.node->prev;
    struct node *after = pos.node;

    // Link to node after.
    node->next = after;
    after->prev = node;

    // Link to node before.
    node->prev = before;
    before->next = node;

    // Return the position of the new element.
    pos.node = node;
    return pos;
}


ListPos list_remove(ListPos pos){
    // Find nodes before and after (may be the same node: the head of the list).
    struct node *before = pos.node->prev;
    struct node *after = pos.node->next;

    // Link nodes before and after.
    before->next = after;
    after->prev = before;

    // Free memory of removed node.
    free(pos.node->value);
    free(pos.node);

    // Set position to next element and return position.
    pos.node = after;
    return pos;
}


const char *list_inspect(ListPos pos){
    return pos.node->value;
}

/*
 * @author  Vincent Johansson
 * @since   2021-01-04
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"

static void add_values(Queue *q){
    char str[2] = "A";
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        str[0] = ch;
        queue_enqueue(q, str);
    }
}

static bool verify_input(Queue *q){
    char str[2] = "B";
    char ch = 'B' - 1;
    bool correct = true;
    while (!queue_is_empty(q)){
        ch += 1;
        str[0] = ch;
        const char *str2 = queue_dequeue(q);
        if(str2 != NULL){
            if (strcmp(str, str2) != 0){
                correct = false;
            }
        }
    }
    if (ch != '[') {
        correct = false;
    }
    return correct;
}

int main(void){

    // Create empty queue.
    Queue *q = queue_create();

    // Add some values.
    add_values(q);

    // Verify input.
    bool input_ok = verify_input(q);
    printf("Test the functioning of the queue ... %s\n", input_ok ? "PASS" : "FAIL");

    // Free all allocated memory.
    queue_destroy(q);
}

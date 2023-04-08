/*
 * @author  Vincent Johansson
 * @since   2021-01-03
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <math.h>

int main(void){

    // Create empty stack.
    Stack *s = stack_create();

    // Fill empty stack with values.
    for(int i = 1; i <= 10; i++){
        stack_push(s, pow(0.5, i));
    }

    // Confirm right values were added.
    for(int i = 10; i > 0; i--){
        if(stack_pop(s) != pow(0.5, i)){
            printf("Test the functioning of the stack ... FAIL\n");
            stack_destroy(s);
            exit(0);
        }
    }

    printf("Test the functioning of the stack ... PASS\n");

    // Free all memory.
    stack_destroy(s);

    return 0;
}

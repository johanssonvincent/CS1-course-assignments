#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *stack_create(void){
    Stack *s = calloc(1,sizeof(Stack));
    s->data = malloc(5*sizeof(double));
    s->data[0] = 0;
    s->capacity = 5;
    s->size = 0;

    return s;
}

void stack_destroy(Stack *s){
    free(s->data);
    free(s);
}

void stack_push(Stack *s, double value){
    if(s->size >= s->capacity){
        s->data = realloc(s->data, (s->capacity*2)*sizeof(double));
        s->capacity = s->capacity*2;
    }
    s->data[s->size] = value;
    s->size++;
}

double stack_pop(Stack *s){
    double value;
    value = s->data[s->size-1];
    s->data[s->size-1] = 0;
    s->size--;

    return value;
}

bool stack_is_empty(const Stack *s){
    if(s->size == 0){
        return true;
    }else{
        return false;
    }
}

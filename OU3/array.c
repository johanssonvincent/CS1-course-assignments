/*
 * @author  Vincent Johansson
 * @since   2019-11-18
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "array.h"

/* ---------------------- External functions ---------------------- */

Array *array_create(int n1, int n2){
    Array *arr = calloc(1,sizeof(Array));
    arr->data = malloc(n1 * n2 * sizeof(int));

    arr->n1 = n1;
    arr->n2 = n2;


    return arr;
}

void array_destroy(Array *arr){
    free(arr->data);
    free(arr);
}

int array_rows(const Array *arr){
    return arr->n1;
}

int array_columns(const Array *arr){
    return arr->n2;
}

int array_get(const Array *arr, int i1, int i2){
    int value;
    value = arr->data[i1 * arr->n2 + i2];

    return value;
}

void array_set(Array *arr, int i1, int i2, int value){
    arr->data[i1 * arr->n2 + i2] = value;
}

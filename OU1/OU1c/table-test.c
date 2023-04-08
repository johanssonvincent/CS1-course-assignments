/*
 * @author  Vincent Johansson
 * @since   2021-01-03
 *
 */


#include <stdio.h>
#include "table.h"

int main(void) {

    int count = 0; // Count for looking up added keys.

    // Create an empty table.
    Table *tab = table_create(200);

    // Insert the key/value pairs (n, -n) for n = 1, 2, ..., 10.
    for(int n = 1; n <= 10; n++){
        table_insert(tab, n, -n);
    }

    // Insert the key/value pairs (n, -n) for n = 101, 102, ..., 110.
    for(int n = 101; n <= 110; n++) {
        table_insert(tab, n, -n);
    }

    // Lookup if keys were added properly.
    for(int n = 1; n <= 200; n++){
        int value;
        int key = n;
        if (table_lookup(tab, key, &value)){
            if(value == -n){
                count++;
            }
        }
    }

    if(count == 20){
        printf("Test the presence of added key/value pairs ... PASS\n");
    }else{
        printf("Test the presence of added key/value pairs ... FAIL\n");
    }

    // Lookup absence of non-added keys.
    count = 200;
    for(int n = 1; n <= 200; n++){
        int value;
        int key = n;
        if (table_lookup(tab, key, &value)){
            if(value == -n){
                count--;
            }
        }
    }

    if(count == 180){
        printf("Test the absence of non-added keys ... PASS\n");
    }else{
        printf("Test the absence of non-added keys ... FAIL\n");
    }

    table_destroy(tab);

    return 0;
}

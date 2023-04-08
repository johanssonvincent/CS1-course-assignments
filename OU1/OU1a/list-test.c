#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"


// Populate the list with A, B, ..., Z.
static void add_values(List *lst)
{
    char str[2] = "A";
    ListPos pos = list_first(lst);
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        str[0] = ch;
        pos = list_insert(pos, str);
        pos = list_next(pos);
    }
}


// Traverse and verify a list in the forward direction.
static bool verify_forwards(List *lst)
{
    char str[2] = "A";
    char ch = 'A' - 1;
    bool correct = true;
    ListPos pos = list_first(lst);
    ListPos end = list_end(lst);
    while (!list_pos_equal(pos, end)) {
        ch += 1;
        str[0] = ch;
        const char *str2 = list_inspect(pos);
        if (strcmp(str, str2) != 0) {
            correct = false;
        }
        pos = list_next(pos);
    }
    if (ch != 'Z') {
        correct = false;
    }
    return correct;
}


// Traverse and verify a list in the backward direction.
static bool verify_backwards(List *lst)
{
    char str[2] = "Z";
    char ch = 'Z' + 1;
    bool correct = true;
    ListPos pos = list_end(lst);
    ListPos first = list_first(lst);
    while (!list_pos_equal(pos, first)) {
        pos = list_prev(pos);
        ch -= 1;
        str[0] = ch;
        const char *str2 = list_inspect(pos);
        if (strcmp(str, str2) != 0) {
            correct = false;
        }
    }
    if (ch != 'A') {
        correct = false;
    }
    return correct;
}


// Remove all the added values from the list.
static void remove_values(List *lst)
{
    ListPos pos = list_first(lst);
    for (char ch = 'A'; ch <= 'Z' && !list_is_empty(lst); ch++) {
        pos = list_remove(pos);
    }
}


// Test program.
int main(void)
{
    // Create an empty list.
    List *lst = list_create();

    // Add some values.
    add_values(lst);

    // Verify the list forwards.
    bool forwards_ok = verify_forwards(lst);
    printf("Test traversal in forward direction ... %s\n", forwards_ok ? "PASS" : "FAIL");

    // Verify the list backwards.
    bool backwards_ok = verify_backwards(lst);
    printf("Test traversal in backward direction ... %s\n", backwards_ok ? "PASS" : "FAIL");

    // Remove all added values.
    remove_values(lst);

    // Verify that the list is empty.
    bool empty_ok = list_is_empty(lst);
    printf("Test removal of all elements ... %s\n", empty_ok ? "PASS" : "FAIL");

    // Clean up allocated resources.
    list_destroy(lst);

    return 0;
}

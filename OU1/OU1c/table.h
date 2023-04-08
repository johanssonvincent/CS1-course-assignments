/*
 * @author  Vincent Johansson
 * @since   2021-01-03
 *
 */


#ifndef TABLE_H
#define TABLE_H


#include <stdbool.h>


/**
 * @defgroup module Table
 *
 * @brief Table implemented as a hashtable.
 *
 * Table implemented with the help of a closed hashing hast table
 * with linear probing.
 *
 * @{
 */


 /**
  * @brief The type for the bucket.
  *
  * Definition of the struct bucket.
  *
  */
struct bucket
{
    int key;
    int value;
    bool used;
};


/**
 * @brief The type for the table.
 *
 * Definition of the struct table.
 *
 */
typedef struct table
{
    // The number of buckets.
    int capacity;
    // The bucket array.
    struct bucket *buckets;
} Table;


/**
 * @brief Creates an empty table.
 *
 * Creates an empty table of given capacity.
 *
 * @param capacity Capacity of the table.
 */
Table *table_create(int capacity);


/**
 * @brief Destroys table.
 *
 * Takes given table *tab and frees all allocated memory.
 *
 * @param *tab Table that is to be destroyed.
 */
void table_destroy(Table *tab);


/**
 * @brief Lookup value for a key, return false if not found.
 *
 * Takes given table *tab and looks up the value for the specified key.
 *
 * @param *tab Table which we wish to collect a value from.
 * @param key Key we wish to collect a value from.
 * @param *value Pointer to where to save the value collected from the key.
 */
bool table_lookup(Table *tab, int key, int *value);


/**
 * @brief Insert a key/value pair and overwrite if key exists.
 *
 * Takes given table *tab and inserts the specified
 * key/value pair.
 *
 * @param *tab Table which we wish to collect a value from.
 * @param key Key we wish to insert a value to.
 * @param value Value that we wish to add to the table.
 */
void table_insert(Table *tab, int key, int value);


#endif /* TABLE_H */

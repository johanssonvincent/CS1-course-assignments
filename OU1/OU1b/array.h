/*
 * @author  Vincent Johansson
 * @since   2021-01-02
 *
 */


#ifndef ARRAY_H
#define ARRAY_H


/**
 * @defgroup module 2D Array
 *
 * @brief 2D array.
 *
 * A 2D array implemented by using a 1D array.
 *
 * @{
 */


/**
 * @brief The struct for the 2d array.
 *
 * Definition of the struct array.
 *
 */
typedef struct array
{
    int n1;
    int n2;
    int *data;
} Array;


/**
 * @brief Creates an empty array.
 *
 * Given positive integers 'n1' and 'n2' representing rows and columns
 * this funciton will create a 2D array with the dimensions
 * specified in 'n1' and 'n2'.
 *
 * @param n1 rows
 * @param n2 columns
 * @return An empty 2D array.
 */
Array *array_create(int n1, int n2);


/**
 * @brief Destroys array.
 *
 * Takes given array *arr and frees all allocated memory.
 *
 * @param *arr Array that is to be destroyed.
 */
void array_destroy(Array *arr);


/**
 * @brief Get the number of rows.
 *
 * Takes given array struct and returns the amount of rows.
 *
 * @param *arr Array which we wish to know the amount of rows from.
 */
int array_rows(const Array *arr);


/**
 * @brief Get the number of columns.
 *
 * Takes given array struct and returns the amount of columns.
 *
 * @param *arr Array which we wish to know the amount of columns from.
 */
int array_columns(const Array *arr);


/**
 * @brief Read a value from the array.
 *
 * Takes given array, and returns the value at row i1, column i2.
 *
 * @param *arr Array which we wish to collect a value from.
 * @param i1 Row value.
 * @param i2 Column value.
 */
int array_get(const Array *arr, int i1, int i2);


/**
 * @brief Insert a value in the array.
 *
 * Takes given array, and adds a given value to the row i1 and column i2.
 *
 * @param *arr The array the value is to be added to.
 * @param i1 Row value.
 * @param i2 Column value.
 * @param value The value that is to be added to the array.
 */
void array_set(Array *arr, int i1, int i2, int value);


#endif /* ARRAY_H */

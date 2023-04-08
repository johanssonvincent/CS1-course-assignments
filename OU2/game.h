/**
 * @defgroup game Game
 *
 * @brief Handles logic of the game 2048.
 *
 * Handles the array containing the game values. Makes different prints
 * relevant to the game board. Handles sliding directions given by user and
 * checks if the game has been won or lost.
 *
 * @author: Kardo Rostam <dv18krm>
 * @author: Vincent Johansson <dv14vjn>
 * @since:  2021-01-04
 *
 * @{
 */


#ifndef GAME_H
#define GAME_H

#include "array.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/**
 * @brief           Starts a new game.
 *
 * Sets a seed for the random number generations. Creates array. Spawns value.
 * Sets the global variable "game_started" to true. This is a safeguard against
 * memory leaks potentially happening during multiple calls to the function.
 *
 * @return          Nothing (void).
 */
void game_new(void);

/**
 * @brief           Return the value of the specified piece (0 if empty).
 *
 * @param row       The rown index.
 * @param column    The column index.
 * @return          The value stored in the array with given indexes.
 */
int game_get_square(int row, int column);

/**
 * @brief           Slide all pieces up.
 *
 * Look for empty slots/zeroes and duplicates (the same as the current value)
 * in the sliding direction. If there are duplicates, it combines the two
 * values together (example 2 + 2 = 4).
 *
 * @return          Nothing (void).
 */
void game_slide_up(void);

/**
 * @brief           Slide all pieces right.
 *
 * Look for empty slots/zeroes and duplicates (the same as the current value)
 * in the sliding direction. If there are duplicates, it combines the two
 * values together (example 2 + 2 = 4).
 *
 * @return          Nothing (void).
 */
void game_slide_right(void);

/**
 * @brief           Slide all pieces down.
 *
 * Look for empty slots/zeroes and duplicates (the same as the current value)
 * in the sliding direction. If there are duplicates, it combines the two
 * values together (example 2 + 2 = 4).
 *
 * @return          Nothing (void).
 */
void game_slide_down(void);

/**
 * @brief           Slide all pieces left.
 *
 * Look for empty slots/zeroes and duplicates (the same as the current value)
 * in the sliding direction. If there are duplicates, it combines the two
 * values together (example 2 + 2 = 4).
 *
 * @return          Nothing (void).
 */
void game_slide_left(void);

/**
 * @brief           Return true if game over (2048 reached or no empty squares).
 *
 * Loops though the array in search of the score 2048 (winning condition). When
 * it is checking if the game is over, it searches for tiles of the same value
 * neighboring the current tile. If there is a neighbor with the same value,
 * the game is not over because a combination is possible. The game is over if
 * these previous conditions is not met.
 *
 * @return          True if game over/win, false if not
 */
bool game_is_game_over(void);


/* GLOBAL VARIABLE DECLARATION - - - - - - - - - - - - - - - - - - - - - - */
extern Array *arr;


#endif // GAME_H

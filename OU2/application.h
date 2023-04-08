/**
 * @defgroup application Application
 *
 * @brief Handles interaction with user playing the game 2048.
 *
 * Starts a new game of 2048 and prints out menu options and board. Takes menu
 * options from user.
 *
 * @author: Kardo Rostam <dv18krm>
 * @author: Vincent Johansson <dv14vjn>
 * @since:  2019-12-05
 *
 * @{
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "game.h"

#include <stdio.h>
#include <stdlib.h>


/**
 * @brief           Starts a new game of 2048 using a memory allocated array.
 *
 * Prints out a menu, board and lets the user decide what to do. The memory is
 * freed if the game is won, lost or canceled through the menu.
 *
 * @return          Nothing (void);
 */
void app_run(void);


#endif // APPLICATION_H

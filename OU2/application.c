/*
 * @author: Kardo Rostam <dv18krm>
 * @author: Vincent Johansson <dv14vjn>
 * @since:  2021-01-04
 */

#include "application.h"


/* PRIVATE FUNCTION DECLARATION - - - - - - - - - - - - - - - - - - - - - - */

/**
 * @brief           Frees memory allocated to array.
 *
 * This function is a private function in "game.c". It is used to reach a global
 * variable of array data structure within the file.
 *
 * @return          Nothing (void).
 */
extern void free_arr_from_board(void);


/**
 * @brief           Gets action from user.
 *
 * Read function "prints_menu" for more information.
 *
 * @return          Action from user.
 */
int get_action(void);


/**
 * @brief           Prints out game menu.
 *
 * The user has the options; 0: Close program, 1: Slide up,
 * 2: Slide right, 3: Slide down, 4: Slide left. If the action is a numeric not
 * recognized, the user may try again. Choosing 0 and closing the program frees
 * up the memory allocated to the array and exits on a EXIT_SUCCESS.
 *
 * @return          Nothing (void).
 */
void print_menu(void);


/**
 * @brief           Prints out a tiles value.
 *
 * Recast zero to four spaces during board print or prints it normally with
 * numeric values.
 *
 * @param pre       String before tile value.
 * @param value     The value within a tile.
 * @param post      String after tile value.
 * @return          Nothing (void).
 */
void print_tile(char const *pre, int value, char const *post);


/**
 * @brief           Prints out the game board.
 *
 * @return          Nothing (void).
 */
void print_board(void);


void app_run(void)
{
    game_new();
    print_board();

    do {

        switch(get_action()) {
            case 0:
                fprintf(stdout, "> Closing program ...\n");
                free_arr_from_board();
                exit(EXIT_SUCCESS);
            break;

            case 1:
                fprintf(stdout, "> Sliding up ...\n");
                game_slide_up();
                print_board();
            break;

            case 2:
                fprintf(stdout, "> Sliding right ...\n");
                game_slide_right();
                print_board();
            break;

            case 3:
                fprintf(stdout, "> Sliding down ...\n");
                game_slide_down();
                print_board();
            break;

            case 4:
                fprintf(stdout, "> Sliding left ...\n");
                game_slide_left();
                print_board();
            break;

            default:
                fprintf(stdout, "> Invalid action, game closing ...\n");
                free_arr_from_board();
                exit(EXIT_FAILURE);
            break;
        }

    } while(1);
}


int get_action(void)
{
    int action = -1;

    print_menu();
    fscanf(stdin, " %d", &action);

    return action;
}


void print_menu(void)
{
    fprintf(stdout, "\nSELECT ACTION\n0: quit\n1: slide up\n2: slide right\n");
    fprintf(stdout, "3: slide down\n4: slide left\n? ");
}


void print_tile(char const *pre, int value, char const *post)
{
    // If the tile value is not empty/zero
    if (value != 0) {
        printf("%s%4d%s", pre, value, post);
    }

    // If the tile value is empty/zero
    else {
        printf("%s    %s", pre, post);
    }
}


void print_board(void)
{
    // Loops through columns
    for (int y = 0 ; y < 4 ; y++) {
        printf("+--------+--------+--------+--------+\n");

        // Loops though the three rows of a square
        for (int i = 0 ; i < 3 ; i++) {

            // When "i" is 1, its the middle row of the square
            if (i == 1) {
                print_tile("|  ", array_get(arr, 0, y),"  ");
                print_tile("|  ", array_get(arr, 1, y),"  ");
                print_tile("|  ", array_get(arr, 2, y),"  ");
                print_tile("|  ", array_get(arr, 3, y),"  |\n");
            }

            else {
                printf("|        |        |        |        |\n");
            }
        }
    }

    printf("+--------+--------+--------+--------+\n");
}


// END OF APPLICATION_C

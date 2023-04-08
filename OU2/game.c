/*
 * @author: Kardo Rostam <dv18krm>
 * @author: Vincent Johansson <dv14vjn>
 * @since:  2021-01-04
 */

#include "game.h"

Array *arr = NULL; // The array containing the values of the game 2048
int open_slots = 16; // Number of open slots
bool game_started = false; // Tells if a game has been started or not

// Sliding directions in a enum
enum {UP, RIGHT, DOWN, LEFT};


/* PRIVATE FUNCTION DECLARATION - - - - - - - - - - - - - - - - - - - - - - */

/**
 * @brief               Spawns a new value on the game board.
 *
 * The function returns when there are no possible room to spawn. If there are
 * room, it sows a rand-seed and gives out a random value zero and the amount
 * of open slots available. Then it “counts” the  open slots until it reached
 * the random number generated (place to spawn is found). There is a 90% chance
 * to spawn a 2, and 10% chance to spawn a 4. Prints the game board if a value
 * has been spawned.
 *
 * @param spawn_amount  Amount of values to spawn.
 * @return              Nothing (void).
 */
void spawn_value(int spawn_amount);


/**
 * @brief          Resets the tracking array.
 *
 * Resets the array used to tracks indexes of slots where a combination is
 * allowed.
 * @param combined  The array containing combination permissions.
 * @return          Nothing (void).
 */
void reset_combination_arr(int *combined);

/**
 * @brief           Combines duplicate values together.
 *
 * Updates amount of open slots remaining in the array.
 *
 * @param x         The row index
 * @param x_mod     Direction modified row index
 * @param y         The column index
 * @param y_mod     Direction modified column index
 * @return          Nothing (void).
 */
void combine_slots(int x, int x_mod, int y, int y_mod);

/**
 * @brief           Locks previous traversed positions for future combinations.
 *
 * During a traversal we record it in a one dimensional array going from index
 * 0 to 3 (this is relative to the sliding direction). If a combination is
 * done, a combination is not allowed previous in the traversal. For example,
 * 4-2-2-0 will be combined to 4-4-0-0 and not 8-0-0-0 with this kind of
 * recording traversal indexes.
 *
 * @param temp          Pointer to index (y or x depending on direction)
 * @param combined      The 1D array to be modified ("locking slots").
 * @param direction     Sliding direction.
 * @return              Nothing (void).
 */
void lock_slots(int *temp, int combined[], int direction);

/**
 * @brief               Sees what actions need to be done after slide.
 *
 * Exits game if the game has been won or lost. If it is still continuing, it
 * spawns need value to the board. If there are no room for spawn, it only
 * prints put the board.
 *
 * @param made_action   A bool revealing if a action was made during slide.
 * @return              Nothing (void).
 */
void check_slide_aftermath(bool made_action);

/**
 * @brief           Frees memory allocated to the array "arr".
 *
 * @return          Nothing (void).
 */
void free_arr_from_board(void);



/* PUBLIC FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - */

void game_new(void)
{
    if (!game_started) {

        // Sets seed
        srand((unsigned) time(0));

        // Create array
        arr = array_create(4, 4);

        // Initialization of the array
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                array_set(arr, i, j, 0);
            }
        }
        spawn_value(2);

        // Sets global boolean to "true" meaning the game has started
        game_started = true;
    }
}

int game_get_square(int row, int column)
{
    return array_get(arr, row, column);
}

void game_slide_up(void)
{
    static int temp = -1; // A temporary index holder to protect the original
    static int combined[4]; // Array to track legit indexes for combinations
    bool made_action = false; // Records if a move or combination was made

    for (int x = 0 ; x < 4 ; x++) {

        // Resets the array allowing combinations everywhere again
        reset_combination_arr(&(*combined));

        for (int y = 1 ; y < 4 ; y++) {

            // Send index value to a temporary variable to protect the original
            temp = y;

            // Checks if a move or combination of values is possible
            while(temp > 0) {

                temp--;

                // To keep the code shorter in width
                int current_val = game_get_square(x, temp);

                // Checks if the current value is zero/empty
                if (current_val == 0) {

                    // Checks if the next value is not zero/empty
                    // "Next value" is relative to slide direction
                    if(game_get_square(x, temp+1) != 0){

                        // Moves "next value" in direction of slide
                        array_set(arr, x, temp, array_get(arr, x, (temp+1)));
                        array_set(arr, x, (temp+1), 0);

                        made_action = true;
                    }
                }

                // Checks if the current value is the same as the next
                else if (current_val == game_get_square(x, (temp+1))) {

                    // Position is allowed for a combination of values
                    if (combined[temp] == 0) {
                        combine_slots(x, x, temp, temp+1);

                        // Locks the previous slots and combined slots
                        lock_slots(&temp, &(*combined), UP);

                        made_action = true;
                    }
                }
            }


        }
    }

    check_slide_aftermath(made_action);
}

void game_slide_right(void)
{
    static int temp = -1; // A temporary index holder to protect the original
    static int combined[4]; // Array to track legit indexes for combinations
    bool made_action = false; // Records if a move or combination was made

    for (int y = 0 ; y < 4 ; y++) {

        // Resets the array allowing combinations everywhere again
        reset_combination_arr(&(*combined));

        for (int x = 2 ; x >= 0 ; x--) {

            // Send index value to a temporary variable to protect the original
            temp = x;

            // Checks if a move or combination of values is possible
            while(temp < 3) {

                temp++;

                // To keep the code shorter in width
                int current_val = game_get_square(temp, y);

                // Checks if the current value is zero/empty
                if (current_val == 0) {

                    // Checks if the next value is not zero/empty
                    // "Next value" is relative to slide direction
                    if(game_get_square(temp-1, y) != 0){

                        // Moves "next value" in direction of slide
                        array_set(arr, temp, y, array_get(arr, (temp-1), y));
                        array_set(arr,(temp-1), y, 0);

                        made_action = true;
                    }
                }

                // Checks if the current value is the same as the next
                else if (current_val == game_get_square((temp-1), y)) {

                    // Position is allowed for a combination of values
                    if (combined[temp] == 0) {
                        combine_slots(temp, temp-1, y, y);

                        // Locks the previous slots and combined slots
                        lock_slots(&temp, &(*combined), RIGHT);

                        made_action = true;
                    }
                }
            }

        }
    }

    check_slide_aftermath(made_action);
}

void game_slide_down(void)
{
    static int temp = -1; // A temporary index holder to protect the original
    static int combined[4]; // Array to track legit indexes for combinations
    bool made_action = false; // Records if a move or combination was made

    for (int x = 0 ; x < 4 ; x++) {

        // Resets the array allowing combinations everywhere again
        reset_combination_arr(&(*combined));

        for (int y = 2 ; y >= 0 ; y--) {

            // Send index value to a temporary variable to protect the original
            temp = y;

            // Checks if a move or combination of values is possible
            while(temp < 3) {

                temp++;

                // To keep the code shorter in width
                int current_val = game_get_square(x, temp);

                // Checks if the current value is zero/empty
                if (current_val == 0) {

                    // Checks if the next value is not zero/empty
                    // "Next value" is relative to slide direction
                    if(game_get_square(x, temp-1) != 0){

                        // Moves "next value" in direction of slide
                        array_set(arr, x, temp, array_get(arr, x, (temp-1)));
                        array_set(arr, x, (temp-1), 0);

                        made_action = true;
                    }
                }

                // Checks if the current value is the same as the next
                else if (current_val == game_get_square(x, (temp-1))) {

                    // Position is allowed for a combination of values
                    if (combined[temp] == 0) {
                        combine_slots(x, x, temp, temp-1);

                        // Locks the previous slots and combined slots
                        lock_slots(&temp, &(*combined), DOWN);

                        made_action = true;
                    }
                }
            }


        }
    }

    check_slide_aftermath(made_action);
}

void game_slide_left(void)
{
    static int temp = -1; // A temporary index holder to protect the original
    static int combined[4]; // Array to track legit indexes for combinations
    bool made_action = false; // Records if a move or combination was made

    for (int y = 0 ; y < 4 ; y++) {

        // Resets the array allowing combinations everywhere again
        reset_combination_arr(&(*combined));

        for (int x = 1 ; x < 4 ; x++) {

            // Send index value to a temporary variable to protect the original
            temp = x;

            // Checks if a move or combination of values is possible
            while(temp > 0) {

                temp--;

                // To keep the code shorter in width
                int current_val = game_get_square(temp, y);

                // Checks if the current value is zero/empty
                if (current_val == 0) {

                    // Checks if the next value is not zero/empty
                    // "Next value" is relative to slide direction
                    if(game_get_square(temp+1, y) != 0){

                        // Moves "next value" in direction of slide
                        array_set(arr, temp, y, array_get(arr, (temp+1), y));
                        array_set(arr, (temp+1), y, 0);

                        made_action = true;
                    }
                }

                // Checks if the current value is the same as the next
                else if (current_val == game_get_square((temp+1), y)) {

                    // Position is allowed for a combination of values
                    if (combined[temp] == 0) {
                        combine_slots(temp, temp+1, y, y);

                        // Locks the previous slots and combined slots
                        lock_slots(&temp, &(*combined), LEFT);

                        made_action = true;
                    }
                }
            }
        }
    }

    check_slide_aftermath(made_action);
}

bool game_is_game_over(void)
{
    // Checks if you have gotten the score 2048 in a square and won
    for (int y = 0 ; y < 4 ; y++) {
        for (int x = 0 ; x < 4 ; x++) {

            // Looks for the win condition
            if (game_get_square(x, y) == 2048) {
                fprintf(stdout, "> You got 2048 and have won the game!\n\n");
                array_destroy(arr);
                return true;
            }

        }
    }

    // Checks if there a square has a neighbor with the same value
    for (int y = 0 ; y < 4 ; y++) {
        for (int x = 0 ; x < 4 ; x++) {

            if (x-1 > -1) {
                if (game_get_square(x, y) == game_get_square(x-1, y)) {
                    return false;
                }
            }

            if (y-1 > -1) {
                if (game_get_square(x, y) == game_get_square(x, y-1)) {
                    return false;
                }
            }

            if (game_get_square(x, y) == game_get_square(x+1, y) ||
                game_get_square(x, y) == game_get_square(x, y+1)) {
                return false;
            }

        }
    }

    // No neighbor with the same value, no further move possible, GAME OVER
    fprintf(stdout, "> No possible moves left. Game over ...\n\n");
    array_destroy(arr);

    return true;
}



/* PRIVATE FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - */

void spawn_value(int spawn_amount)
{
    // There are possible moves and there are no room to spawn
    if (open_slots == 0) {
        return;
    }

    int spawns_done = 0;

    do {
        int count = 0;

        // Gives us the slot (counting empty slots) of where to spawn
        int random_pos = rand() % open_slots;
        int random_spawn = -1;

        for (int y = 0 ; y < 4 ; y++) {
            for (int x = 0 ; x < 4 ; x++) {

                if (game_get_square(x, y) == 0) {
                    count++;
                }

                if (random_pos == (count-1)) {
                    if (game_get_square(x, y) == 0) {

                        random_spawn = rand() % 10;

                        if (random_spawn == 0) {
                            array_set(arr, x, y, 4);
                        }

                        else {
                            array_set(arr, x, y, 2);
                        }

                        spawns_done++;
                        open_slots--;
                    }
                }

            }
        }

    } while(spawns_done < spawn_amount);

}


void reset_combination_arr(int *combined)
{
    // Initiates the array recording combinations to 0
    for (int i = 0 ; i < 4 ; i++) {
        combined[i] = 0;
    }
}

void combine_slots(int x, int x_mod, int y, int y_mod)
{
    // Doubles value (new_value is made to keep rows short)
    int new_value = (array_get(arr, x, y_mod) * 2);
    array_set(arr, x, y, new_value);

    // Declares the moves array position to 0
    array_set(arr, x_mod, y_mod, 0);

    // Registers the new open slot
    open_slots++;
}

void lock_slots(int *temp, int combined[], int direction)
{
    int marker = *(temp);

    if (direction == UP || direction == LEFT) {
        while (marker > -1) {
            combined[marker] = 1;
            marker--;
        }
    }

    else { //direction == UP || direction == LEFT
        while (marker < 4) {
            combined[marker] = 1;
            marker++;
        }
    }

}

void check_slide_aftermath(bool made_action)
{
    if (game_is_game_over()) {
        exit(EXIT_SUCCESS);
    }
    else if (made_action) {
        spawn_value(1);
    }
}

void free_arr_from_board(void)
{
    array_destroy(arr);
}



//END OF GAME_C

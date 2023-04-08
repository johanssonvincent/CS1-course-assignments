#ifndef SEARCH_H
#define SEARCH_H

#include <stdbool.h>

typedef struct state {
  char cells[16];
  char empty;
  char depth;
} State;

typedef void (*push_state_fn)(void *data, State S);
typedef State (*pop_state_fn)(void *data);
typedef bool (*empty_state_fn)(void *data);
typedef int (*max_size_state_fn)(void *data);

State goal_state(void);
void random_moves(State *S, int n);
void generic_search(State start, int max_depth, push_state_fn push, pop_state_fn pop, empty_state_fn empty, max_size_state_fn max_size, void *data);

#endif

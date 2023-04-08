#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "search.h"


/* Return the current time in seconds with high precision. */
static double get_time(void)
{
  struct timeval tv;
  gettimeofday(&tv, 0); 	/* Defined in POSIX (not standard C). */
  return tv.tv_sec + tv.tv_usec * 1e-6;
}


State goal_state(void)
{
  State S = { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 }, 15, 0 };
  return S;
}


static bool is_goal_state(const State *S)
{
  for (int k = 0; k < 15; k++) {
    if (S->cells[k] != k + 1) {
      return false;
    }
  }
  return true;
}


static int adjacent_states(const State *S, State adj[4])
{
  int n = 0;
  const int offsets[4] = { -1, +1, -4, +4 };
  const int empty = S->empty;
  for (int d = 0; d < 4; d++) {
    const int index = empty + offsets[d];
    if (offsets[d] == -1 || offsets[d] == +1) {
      if (index / 4 != empty / 4) {
	continue;
      }
    }
    if (index >= 0 && index <= 15) {
      State T = *S;
      T.cells[empty] = T.cells[index];
      T.cells[index] = 0;
      T.empty = index;
      T.depth += 1;
      adj[n++] = T;
    }
  }
  return n;
}


void random_moves(State *S, int n)
{
  State adj[4];
  for (int k = 0; k < n; k++) {
    int num = adjacent_states(S, adj);
    int index = rand() % num;
    *S = adj[index];
  }
  S->depth -= n;
}


#if 0
static void print_state(const State *S)
{
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      int k = 4 * row + col;
      char c = S->cells[k];
      if (c == 0) {
	printf(" . ");
      } else {
	printf("%2d ", c);
      }
    }
    printf("\n");
  }
  printf("\n");
}
#endif


void generic_search(State start, int max_depth, push_state_fn push, pop_state_fn pop, empty_state_fn empty, max_size_state_fn max_size, void *data)
{
  int states = 1;
  int solutions = 0;

  double T = get_time();
  push(data, start);
  while (!empty(data)) {
    State S = pop(data);
    if (is_goal_state(&S)) {
      solutions++;
    }
    if (S.depth < max_depth) {
      State adj[4];
      int n = adjacent_states(&S, adj);
      for (int k = 0; k < n; k++) {
	push(data, adj[k]);
	states++;
      }
    }
  }
  T = get_time() - T;
  printf("%4d\t%10.6lf\t%12d\t%12d\t%12d\n", max_depth, T, states, solutions, max_size(data));
}

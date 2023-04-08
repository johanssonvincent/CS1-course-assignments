#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "search.h"


/* INTERFACE (STACK) */

typedef struct stack
{
  int    capacity;
  int    size;
  int    sizecount;
  int    mem_usage;
  State *data;
} Stack;

Stack *stack_create(void);
void   stack_destroy(Stack *s);
void   stack_push(Stack *s, State value);
State  stack_pop(Stack *s);
bool   stack_is_empty(const Stack *s);
int    stack_get_max_size(const Stack *s);


/* IMPLEMENTATION (STACK) */

Stack *stack_create(void)
{
  Stack *s = malloc(sizeof(Stack));
  s->capacity = 1024;
  s->size = 0;
  s->sizecount = 0;
  s->mem_usage = 0;
  s->data = malloc(sizeof(State) * s->capacity);
  return s;
}


void stack_destroy(Stack *s)
{
  free(s->data);
  free(s);
}


void stack_push(Stack *s, State value)
{
  if (s->size == s->capacity) {
    s->capacity *= 2;
    s->data = realloc(s->data, sizeof(State) * s->capacity);
  }
  s->data[s->size++] = value;
  s->sizecount++;

  if(s->sizecount > s->mem_usage){
      s->mem_usage = s->sizecount;
  }

}


State stack_pop(Stack *s)
{
  s->sizecount--;
  return s->data[--s->size];
}


bool stack_is_empty(const Stack *s)
{
  return s->size == 0;
}


int stack_get_max_size(const Stack *s)
{
  return s->mem_usage;
}


/* IMPLEMENTATION (DFS) */

struct dfs_data {
  Stack *stack;
};

void dfs_push_state(void *data, State S)
{
  struct dfs_data *p = data;
  stack_push(p->stack, S);
}

State dfs_pop_state(void *data)
{
  struct dfs_data *p = data;
  return stack_pop(p->stack);
}

bool dfs_empty_state(void *data)
{
  struct dfs_data *p = data;
  return stack_is_empty(p->stack);
}

int dfs_max_size(void *data)
{
  struct dfs_data *p = data;
  return stack_get_max_size(p->stack);
}

void dfs_search(State start, int max_depth)
{
  struct dfs_data data = { stack_create() };
  generic_search(start, max_depth, dfs_push_state, dfs_pop_state, dfs_empty_state, dfs_max_size, &data);
  stack_destroy(data.stack);
}


/* MAIN */

int main(void)
{
  printf("EXPERIMENT PÅ STACK\n");
  printf("======================================================================\n\n");
  printf("Det här programmet mäter hur mycket minne som algoritmen DFS behöver\n"
	 "för att räkna antalet lösningar till instanser av 15-pusslet. Det\n"
	 "maximala antalet förflyttningar varieras mellan 1 och 15. Instanserna\n"
	 "är skapade så att de går att lösa. Resultaten skrivs ut i textformat\n"
	 "till stdout med tab-separerade kolumner. Tiden mäts i sekunder. Minnet\n"
	 "mäts i antal element i stacken.\n");
  printf("\n");
  printf("RESULTAT\n");
  printf("======================================================================\n\n");
  printf("%4s\t%10s\t%13s\t%13s\t%12s\n", "max", "tid", "tillstånd", "lösningar", "minne");
  for (int max_depth = 1; max_depth <= 15; max_depth++) {
    srand(max_depth);
    State start = goal_state();
    random_moves(&start, max_depth);
    dfs_search(start, max_depth);
  }
}

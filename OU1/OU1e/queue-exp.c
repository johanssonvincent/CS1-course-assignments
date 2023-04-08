#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "search.h"


/* INTERFACE (QUEUE) */

typedef struct queue
{
  int capacity;
  int size;
  int sizecount;
  int mem_usage;
  int head;
  int tail;
  State *data;
} Queue;

Queue *queue_create(void);
void   queue_destroy(Queue *q);
void   queue_enqueue(Queue *q, State value);
State  queue_dequeue(Queue *q);
bool   queue_is_empty(const Queue *q);
int    queue_get_max_size(const Queue *q);


/* IMPLEMENTATION (QUEUE) */

Queue *queue_create(void)
{
  Queue *q = malloc(sizeof(Queue));
  q->capacity = 1024;
  q->size = 0;
  q->sizecount = 0;
  q->mem_usage = 0;
  q->head = 0;
  q->tail = 0;
  q->data = malloc(sizeof(State) * q->capacity);
  return q;
}


void queue_destroy(Queue *q)
{
  free(q->data);
  free(q);
}


void queue_enqueue(Queue *q, State value)
{
  if (q->size == q->capacity) {
    const int oldcap = q->capacity;
    q->capacity *= 2;
    q->data = realloc(q->data, sizeof(State) * q->capacity);
    if (q->tail <= q->head) {
      const int n = q->size - q->tail;
      for (int k = 1; k <= n; k++) {
	q->data[q->capacity - k] = q->data[oldcap - k];
      }
      q->head = q->capacity - n;
    }
  }
  q->data[q->tail] = value;
  q->size++;
  q->sizecount++;

  if(q->sizecount > q->mem_usage){
      q->mem_usage = q->sizecount;
  }

  q->tail = (q->tail + 1) % q->capacity;
}


State queue_dequeue(Queue *q)
{
  State S = q->data[q->head];
  q->head = (q->head + 1) % q->capacity;
  q->size--;
  q->sizecount--;
  return S;
}


bool queue_is_empty(const Queue *q)
{
  return q->size == 0;
}


int queue_get_max_size(const Queue *q)
{
  return q->mem_usage;
}


/* IMPLEMENTATION (BFS) */

struct bfs_data {
  Queue *queue;
};


static void bfs_push_state(void *data, State S)
{
  struct bfs_data *p = data;
  queue_enqueue(p->queue, S);
}


static State bfs_pop_state(void *data)
{
  struct bfs_data *p = data;
  return queue_dequeue(p->queue);
}


static bool bfs_empty_state(void *data)
{
  struct bfs_data *p = data;
  return queue_is_empty(p->queue);
}


static int bfs_max_size(void *data)
{
  struct bfs_data *p = data;
  return queue_get_max_size(p->queue);
}


static void bfs_search(State start, int max_depth)
{
  struct bfs_data data = { queue_create() };
  generic_search(start, max_depth, bfs_push_state, bfs_pop_state, bfs_empty_state, bfs_max_size, &data);
  queue_destroy(data.queue);
}


/* MAIN */

int main(void)
{
  printf("EXPERIMENT PÅ KÖ\n");
  printf("======================================================================\n\n");
  printf("Det här programmet mäter hur mycket minne som algoritmen BFS behöver\n"
	 "för att räkna antalet lösningar till instanser av 15-pusslet. Det\n"
	 "maximala antalet förflyttningar varieras mellan 1 och 15. Instanserna\n"
	 "är skapade så att de går att lösa. Resultaten skrivs ut i textformat\n"
	 "till stdout med tab-separerade kolumner. Tiden mäts i sekunder. Minnet\n"
	 "mäts i antal element i kön.\n");
  printf("\n");
  printf("RESULTAT\n");
  printf("======================================================================\n\n");
  printf("%4s\t%10s\t%13s\t%13s\t%12s\n", "max", "tid", "tillstånd", "lösningar", "minne");
  for (int max_depth = 1; max_depth <= 15; max_depth++) {
    srand(max_depth);
    State start = goal_state();
    random_moves(&start, max_depth);
    bfs_search(start, max_depth);
  }
}

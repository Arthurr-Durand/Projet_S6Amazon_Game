#ifndef _WORLD_H_
#define _WORLD_H_

#include <stdlib.h>
#include "graph.h"
#include "player.h"
#include "dir.h"

enum type_world {
  SQUARED = 0,
  // DONUT = 1,
  // CLOVER = 2,
  // EIGHT = 3,
};

enum sort { 
  NO_SORT = 0,
  B_QUEEN = 1,
  W_QUEEN = 2,
  BLOCK = 3,
};

struct world_t {
  enum sort* idx ;
  unsigned int width;
};

gsl_spmatrix_uint* graph_init(int m, enum type_world t);

gsl_spmatrix_uint* squared_graph(int m);

struct world_t * world_init(int width);

enum sort world_get(struct world_t* world, unsigned int i);

void world_set(struct world_t* world, unsigned int i, enum sort s);

void free_world(struct world_t * world);

void print_world(struct world_t * world);

void compute_queens_pos(int m, struct world_t* world, int num_queens, unsigned int* queens[NUM_PLAYERS]);

void free_queens(unsigned int* queens[]);

#endif // _WORLD_H_

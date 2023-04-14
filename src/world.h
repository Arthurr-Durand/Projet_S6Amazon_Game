#include "graph.h"
#include <stdlib.h>

enum type_world {
  SQUARED = 0,
  DONUT = 1,
  CLOVER = 2,
  EIGHT = 3,
};

enum sort { 
  NO_SORT = 0,
  W_QUEEN = 1,
  B_QUEEN = 2,
  BLOCK = 3,
};

//
struct world_t {
  enum sort* idx ;
  unsigned int width;
};

gsl_spmatrix_uint* graph_init(int m, enum type_world t);

gsl_spmatrix_uint* squared_graph(int m);

struct world_t * world_init(int width);

void free_world(struct world_t * world);

void print_world(struct world_t * world);




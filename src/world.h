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
  ARROW = 3,
};

//
struct world_t {
  enum sort* idx ;
  int width;
};

gsl_spmatrix_uint * world_init(int m, enum type_world t);

struct world_t * initiate_world(int width);

void free_world(struct world_t * world);

void print_world(struct world_t * world);




#include "graph.h"

enum type_world {
  SQUARED = 0,
  DONUT = 1,
  CLOVER = 2,
  EIGHT = 3,
};

gsl_spmatrix_uint* world_init(int m, enum type_world t);

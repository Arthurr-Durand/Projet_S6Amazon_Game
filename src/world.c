#include "world.h"

struct graph_t * world_init(int m, enum type_world t) {
  gsl_spmatrix_uint* mat = gsl_spmatrix_uint_alloc(n, n);
  for (each edge from i to j)
    gsl_spmatrix_uint_set(mat, i, j, 1);
}


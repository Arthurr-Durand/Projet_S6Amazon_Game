#include "world.h"

gsl_spmatrix_uint* world_init(int m, enum type_world t) {
  gsl_spmatrix_uint* mat;
  switch (t) {
  case SQUARED:
    //mat = squared_world(m);
    break;
  case DONUT:
    //mat = donut_world(m);
    break;
  case CLOVER:
    //mat = clover_world(m);
    break;
  case EIGHT:
    //mat = eight_world(m);
    break;
  }
  return mat;
}

#include "world.h"
#include "dir.h"

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

struct graph_t * squared_world(int m) {
  int width = m*m;
  gsl_spmatrix_uint* mat = gsl_spmatrix_uint_alloc(width, width);
  corners(m, mat);
  for ( int i = 0; i < width*width; i++ ) {
    if ( (i - m < 0) && ( i != 0) && ( i != m - 1)) { 
      gsl_spmatrix_set_uint(matrix, i, i + (m - 1) , DIR_SW);
      gsl_spmatrix_set_uint(matrix, i, i + (m + 1), DIR_SE);
      gsl_spmatrix_set_uint(matrix, i, i - 1, DIR_EAST);      
      gsl_spmatrix_set_uint(matrix, i, i + 1, DIR_WEST);      
      gsl_spmatrix_set_uint(matrix, i, i + m, DIR_SOUTH);      
    }
    if ( ( 
     
       
  }
}

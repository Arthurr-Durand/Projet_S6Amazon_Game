#include "world.h"
#include "dir.h"
struct graph_t * world_init(int m, enum type_world t) {
  gsl_spmatrix_uint* mat = gsl_spmatrix_uint_alloc(m*m, m*m);
  for (each edge from i to j)
    gsl_spmatrix_uint_set(mat, i, j, 1);
}

void corners(int m, gsl_spmatrix_uint* matrix) {
  int corners[4] = {0, m-1, width, witdh + (m - 1)}
  int max_value = (m * m) - 2;
  int width = m * (m - 1);
  for (int k = 0; k < 4; k++) { 
    switch(corners[k]) { 
    case 0:
      gsl_spmatrix_set_uint(matrix, 0, 1, DIR_EAST);
      gsl_spmatrix_set_uint(matrix, 0, 9, DIR_SOUTH);
      gsl_spmatrix_set_uint(matrix, 0, 10, DIR_SE);      
    case m - 1:
      gsl_spmatrix_set_uint(matrix, m - 1, m - 2,DIR_WEST);
      gsl_spmatrix_set_uint(matrix, m - 1, (2 * m) -  1, DIR_SOUTH);
      gsl_spmatrix_set_uint(matrix, m - 1, 2 * (m - 1), DIR_SW);      
    case width:
      gsl_spmatrix_set_uint(matrix, width, width + 1, DIR_EAST);
      gsl_spmatrix_set_uint(matrix, width, width - m, DIR_NORTH);
      gsl_spmatrix_set_uint(matrix, width, width - m + 1, DIR_NE);
    case max_value:
      gsl_spmatrix_set_uint(matrix, max_value, max_value - 1, DIR_NW);
      gsl_spmatrix_set_uint(matrix, max_value, max_value - m, DIR_NORTH);
      gsl_spmatrix_set_uint(matrix, max_value, max_value - (m + 1), DIR_NW);
    }
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


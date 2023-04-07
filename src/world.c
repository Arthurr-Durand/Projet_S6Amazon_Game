#include "world.h"
#include "dir.h"



struct graph_t * squared_world(int m) {
  int width = m*m;
  struct graph_t *graph = malloc(sizeof(graph));
  gsl_spmatrix_uint* mat = gsl_spmatrix_uint_alloc(width, width);
  for (int i = 0; i < m; i++) {
      if ( i % m == 0 ) {
	if ((0 <= i) && (i <= m - 1)) {
	  gsl_spmatrix_uint_set(mat,i + 1,i, DIR_EAST);
	  gsl_spmatrix_uint_set(mat,i + m,i, DIR_SOUTH);
	  gsl_spmatrix_uint_set(mat,i + m + 1,i, DIR_SE);
	}
	else if ( (width - m <= i) && ( i  <= width - 1) ) {
	  gsl_spmatrix_uint_set(mat,i + 1,i, DIR_EAST);
	  gsl_spmatrix_uint_set(mat,i - m,i,DIR_NORTH);
	  gsl_spmatrix_uint_set(mat,i - m - 1,i, DIR_NE);
	}
	else {
	  gsl_spmatrix_uint_set(mat, i + 1,i, DIR_EAST);
	  gsl_spmatrix_uint_set(mat,i + m,i,DIR_SOUTH);
	  gsl_spmatrix_uint_set(mat,i + m + 1,i,DIR_SE);
	  gsl_spmatrix_uint_set(mat,i - m,i,DIR_NORTH);
	  gsl_spmatrix_uint_set(mat,i - m + 1,i,DIR_NE);
	}
      }
      if ( i % m == m - 1 ) {
	if ((0 <= i) && (i <= m - 1)) {
	  gsl_spmatrix_uint_set(mat,i - 1,i, DIR_WEST);
	  gsl_spmatrix_uint_set(mat,i + m,i, DIR_SOUTH);
	  gsl_spmatrix_uint_set(mat,i + m - 1,i, DIR_SW);
	}
	if ((width - m <= i) && ( i <= width - 1)) {
	  gsl_spmatrix_uint_set(mat,i - 1,i,DIR_WEST);
	  gsl_spmatrix_uint_set(mat,i - m,i,DIR_NORTH);
	  gsl_spmatrix_uint_set(mat,i - m - 1,i,DIR_NW);
	}
	else {
	  gsl_spmatrix_uint_set(mat,i - 1,i,DIR_WEST);
	  gsl_spmatrix_uint_set(mat,i + m,i, DIR_SOUTH);
	  gsl_spmatrix_uint_set(mat,i + m - 1,i, DIR_SW);
	  gsl_spmatrix_uint_set(mat,i - m,i,DIR_NORTH);
	  gsl_spmatrix_uint_set(mat,i - m - 1,i,DIR_NW);
	}
      }
      if (( 0 <= i ) && ( i<= m- 1 ) ){
	gsl_spmatrix_uint_set(mat,i - 1,i,DIR_WEST);
	gsl_spmatrix_uint_set(mat,i + 1,i,DIR_EAST);
	gsl_spmatrix_uint_set(mat,i + m,i,DIR_SOUTH);
	gsl_spmatrix_uint_set(mat,i + m - 1,i, DIR_SW);
	gsl_spmatrix_uint_set(mat,i + m + 1,i, DIR_SE);
      }
      if (( width - m <= i) && ( i  <= width - 1 ) ){
	gsl_spmatrix_uint_set(mat,i - 1,i, DIR_WEST);
	gsl_spmatrix_uint_set(mat,i + 1,i,DIR_EAST);
	gsl_spmatrix_uint_set(mat,i - m,i,DIR_NORTH);
	gsl_spmatrix_uint_set(mat,i - m - 1,i, DIR_NW);
	gsl_spmatrix_uint_set(mat,i - m + 1,i, DIR_NE);
      }
      else {
	gsl_spmatrix_uint_set(mat,i - 1,i, DIR_WEST);
	gsl_spmatrix_uint_set(mat,i + 1,i,DIR_EAST);
	gsl_spmatrix_uint_set(mat,i - m,i,DIR_NORTH);
	gsl_spmatrix_uint_set(mat,i - m - 1,i, DIR_NW);
	gsl_spmatrix_uint_set(mat,i - m + 1,i, DIR_NE);
	gsl_spmatrix_uint_set(mat,i + m,i,DIR_SOUTH);
	gsl_spmatrix_uint_set(mat,i + m - 1,i, DIR_SW);
	gsl_spmatrix_uint_set(mat,i + m + 1,i, DIR_SE);
      }
  }
  graph->num_vertices = width;
  graph->t = mat;
  return graph;
}


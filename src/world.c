#include "world.h"
#include "dir.h"



gsl_spmatrix_uint * squared_world(int m) {
  int width = m * m;
  gsl_spmatrix_uint * mat = gsl_spmatrix_uint_alloc(width , width);
  for (int i = 0; i < width; i++) {
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
      else if ( i % m == m - 1 ) {
	if ((0 <= i) && (i <= m - 1)) {
	  gsl_spmatrix_uint_set(mat,i - 1,i, DIR_WEST);
	  gsl_spmatrix_uint_set(mat,i + m,i, DIR_SOUTH);
	  gsl_spmatrix_uint_set(mat,i + m - 1,i, DIR_SW);
	}
	else if ((width - m <= i) && ( i <= width - 1)) {
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
      else  if (( 0 <= i ) && ( i<= m- 1 ) ){
	gsl_spmatrix_uint_set(mat,i - 1,i,DIR_WEST);
	gsl_spmatrix_uint_set(mat,i + 1,i,DIR_EAST);
	gsl_spmatrix_uint_set(mat,i + m,i,DIR_SOUTH);
	gsl_spmatrix_uint_set(mat,i + m - 1,i, DIR_SW);
	gsl_spmatrix_uint_set(mat,i + m + 1,i, DIR_SE);
      }
      else  if (( width - m <= i) && ( i  <= width - 1 ) ){
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

  return mat;
}

gsl_spmatrix_uint* world_init(int m, enum type_world t) {
  gsl_spmatrix_uint* mat;
  switch (t) {
  case SQUARED:
    mat = squared_world(m);
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

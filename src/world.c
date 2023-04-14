#include "world.h"
#include "dir.h"

gsl_spmatrix_uint* graph_init(int m, enum type_world t)
{
  gsl_spmatrix_uint* mat;
  switch (t) {
  case SQUARED:
    mat = squared_graph(m);
    break;
  case DONUT:
    // mat = donut_graph(m);
    break;
  case CLOVER:
    // mat = clover_graph(m);
    break;
  case EIGHT:
    // mat = eight_graph(m);
    break;
  }
  return mat;
}

/*
  Créé une matrice d'adjacence de taille (m*m)*(m*m) 
*/
gsl_spmatrix_uint* squared_graph(int m)
{
  int width = m * m;
  gsl_spmatrix_uint* mat = gsl_spmatrix_uint_alloc(width, width);
  for (int i = 0; i < width; i++) {
    if (i % m == 0) {
      if ((0 <= i) && (i <= m - 1)) {
	gsl_spmatrix_uint_set(mat, i + 1, i, DIR_EAST);
	gsl_spmatrix_uint_set(mat, i + m, i, DIR_SOUTH);
	gsl_spmatrix_uint_set(mat, i + m + 1, i, DIR_SE);
      } else if ((width - m <= i) && (i <= width - 1)) {
	gsl_spmatrix_uint_set(mat, i + 1, i, DIR_EAST);
	gsl_spmatrix_uint_set(mat, i - m, i, DIR_NORTH);
	gsl_spmatrix_uint_set(mat, i - m - 1, i, DIR_NE);
      } else {
	gsl_spmatrix_uint_set(mat, i + 1, i, DIR_EAST);
	gsl_spmatrix_uint_set(mat, i + m, i, DIR_SOUTH);
	gsl_spmatrix_uint_set(mat, i + m + 1, i, DIR_SE);
	gsl_spmatrix_uint_set(mat, i - m, i, DIR_NORTH);
	gsl_spmatrix_uint_set(mat, i - m + 1, i, DIR_NE);
      }
    } else if (i % m == m - 1) {
      if ((0 <= i) && (i <= m - 1)) {
	gsl_spmatrix_uint_set(mat, i - 1, i, DIR_WEST);
	gsl_spmatrix_uint_set(mat, i + m, i, DIR_SOUTH);
	gsl_spmatrix_uint_set(mat, i + m - 1, i, DIR_SW);
      } else if ((width - m <= i) && (i <= width - 1)) {
	gsl_spmatrix_uint_set(mat, i - 1, i, DIR_WEST);
	gsl_spmatrix_uint_set(mat, i - m, i, DIR_NORTH);
	gsl_spmatrix_uint_set(mat, i - m - 1, i, DIR_NW);
      } else {
	gsl_spmatrix_uint_set(mat, i - 1, i, DIR_WEST);
	gsl_spmatrix_uint_set(mat, i + m, i, DIR_SOUTH);
	gsl_spmatrix_uint_set(mat, i + m - 1, i, DIR_SW);
	gsl_spmatrix_uint_set(mat, i - m, i, DIR_NORTH);
	gsl_spmatrix_uint_set(mat, i - m - 1, i, DIR_NW);
      }
    } else if ((0 <= i) && (i <= m - 1)) {
      gsl_spmatrix_uint_set(mat, i - 1, i, DIR_WEST);
      gsl_spmatrix_uint_set(mat, i + 1, i, DIR_EAST);
      gsl_spmatrix_uint_set(mat, i + m, i, DIR_SOUTH);
      gsl_spmatrix_uint_set(mat, i + m - 1, i, DIR_SW);
      gsl_spmatrix_uint_set(mat, i + m + 1, i, DIR_SE);
    } else if ((width - m <= i) && (i <= width - 1)) {
      gsl_spmatrix_uint_set(mat, i - 1, i, DIR_WEST);
      gsl_spmatrix_uint_set(mat, i + 1, i, DIR_EAST);
      gsl_spmatrix_uint_set(mat, i - m, i, DIR_NORTH);
      gsl_spmatrix_uint_set(mat, i - m - 1, i, DIR_NW);
      gsl_spmatrix_uint_set(mat, i - m + 1, i, DIR_NE);
    } else {
      gsl_spmatrix_uint_set(mat, i - 1, i, DIR_WEST);
      gsl_spmatrix_uint_set(mat, i + 1, i, DIR_EAST);
      gsl_spmatrix_uint_set(mat, i - m, i, DIR_NORTH);
      gsl_spmatrix_uint_set(mat, i - m - 1, i, DIR_NW);
      gsl_spmatrix_uint_set(mat, i - m + 1, i, DIR_NE);
      gsl_spmatrix_uint_set(mat, i + m, i, DIR_SOUTH);
      gsl_spmatrix_uint_set(mat, i + m - 1, i, DIR_SW);
      gsl_spmatrix_uint_set(mat, i + m + 1, i, DIR_SE);
    }
  }

  gsl_spmatrix_uint* csr = gsl_spmatrix_uint_compress(mat, GSL_SPMATRIX_CSR);
  gsl_spmatrix_uint_free(mat);

  return csr;
}

/*
  Tableau alloué dynamiquement représentant le plateau jeu qui sera modifié tout au long de la partie
*/
struct world_t * world_init(int width)  {
  int WORLD_SIZE = width * width;
  struct world_t * world = malloc(sizeof(struct world_t));
  world->width = width;
  world->idx = malloc(sizeof(enum sort) * (WORLD_SIZE));

  for (int i = 0; i < WORLD_SIZE; i++) {
    world->idx[i] = 0;
  }

  return world;
}


void compute_queens_pos(int m, struct world_t* world, int num_queens, unsigned int* queens[]) {
  //int test  = (m - (num_queens / 2)) / ((num_queens /2) + 1);
  
  for(int i = 0; i < num_queens / 4; i++) {
    world->idx[2 * i + 1] = 3;
    *queens[0] = 2 * i + 1;
    world->idx[m - 1 - (2 * i + 1)] = 3;
    *queens[0] = m - 1 - (2 * i + 1);
    world->idx[(2 * i + 1) * m] = 3;
    *queens[0] = (2 * i + 1) * m;
    world->idx[(2 * i + 2) * m - 1] = 3;
    *queens[0] = (2 * i + 2) * m - 1;
    
    world->idx[m * m - m + 2 * i + 1] = 2;
    *queens[0] = m * m - m + 2 * i + 1;
    world->idx[m * m - m -  (2 * i + 1) * m] = 2;
    *queens[0] = m * m - m -  (2 * i + 1) * m;
    world->idx[m * m - 1 -  (2 * i + 1) * m] = 2;
    *queens[0] = m * m - 1 -  (2 * i + 1) * m;
    world->idx[m * m - 1 - (2 * i + 1 )] = 2;
    *queens[0] = m * m - 1 - (2 * i + 1 );
  }
}

/*
  free le tableau world alloué dynamiquement 
*/
void free_world(struct world_t * world) {
  free(world->idx);
  free(world);
}

/*
  c'est dans le nom de la fonction XD 
*/
void print_world(struct world_t * world) {
  int size = world->width;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%d ",world->idx[j + i*size]);
    }
    printf("\n");
  }
  printf("\n");
}

void free_queens(unsigned int* queens[]) {
  for(int i = 0; i < 2; i++) {
      free(queens[i]);
  }
}

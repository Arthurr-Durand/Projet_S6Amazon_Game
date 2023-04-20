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
gsl_spmatrix_uint* squared_graph(int size)
{
    gsl_spmatrix_uint* mat = gsl_spmatrix_uint_alloc(size * size, size * size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int index_i_j = i * size + j;
            if (i > 0) {
                gsl_spmatrix_uint_set(mat, index_i_j, (i - 1) * size + j, DIR_NORTH);
                if (j > 0)
                    gsl_spmatrix_uint_set(mat, index_i_j, (i - 1) * size + j - 1, DIR_NW);
                if (j < size - 1)
                    gsl_spmatrix_uint_set(mat, index_i_j, (i - 1) * size + j + 1, DIR_NE);
            }
            if (j > 0)
                gsl_spmatrix_uint_set(mat, index_i_j, i * size + j - 1, DIR_WEST);
            if (j < size - 1)
                gsl_spmatrix_uint_set(mat, index_i_j, i * size + j + 1, DIR_EAST);
            if (i < size - 1) {
                gsl_spmatrix_uint_set(mat, index_i_j, (i + 1) * size + j, DIR_SOUTH);
                if (j > 0)
                    gsl_spmatrix_uint_set(mat, index_i_j, (i + 1) * size + j - 1, DIR_SW);
                if (j < size - 1)
                    gsl_spmatrix_uint_set(mat, index_i_j, (i + 1) * size + j + 1, DIR_SE);
            }
        }
    }

    gsl_spmatrix_uint* csr = gsl_spmatrix_uint_compress(mat, GSL_SPMATRIX_CSR);
    gsl_spmatrix_uint_free(mat);

    return csr;
}

/*
  Tableau alloué dynamiquement représentant le plateau jeu qui sera modifié tout au long de la partie
*/
struct world_t* world_init(int width)
{
    int WORLD_SIZE = width * width;
    struct world_t* world = malloc(sizeof(struct world_t));
    world->width = width;
    world->idx = malloc(sizeof(enum sort) * (WORLD_SIZE));
    for (int i = 0; i < WORLD_SIZE; i++) {
        world->idx[i] = 0;
    }

    return world;
}

/*
  free le tableau world alloué dynamiquement
*/
void free_world(struct world_t* world)
{
    free(world->idx);
    free(world);
}

/*
  c'est dans le nom de la fonction XD
*/
void print_world(struct world_t* world)
{
    int size = world->width;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", world->idx[j + i * size]);
        }
        printf("\n");
    }
    printf("\n");
}

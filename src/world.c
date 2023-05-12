#include "world.h"

gsl_spmatrix_uint* graph_init(int m, enum type_world t)
{
    gsl_spmatrix_uint* mat;
    switch (t) {
    case SQUARED:
        mat = squared_graph(m,0);
        break;
    case DONUT:
        mat = squared_graph(m,1);
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
gsl_spmatrix_uint* squared_graph(int size,int donnut)
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
    if (donnut == 1 ){
        printf("en cours de developpement \n");
    //     int cut = size/2;
    //     int R = cut%2;
    //     int Q = cut/2;
    //     for(int i = Q+R-1;i<size-(R+Q)+1;i++){
    //         for(int j = Q+R-1;j<size-(R+Q)+1;j++){
    //             int index_i_j = i* size + j;
    //             if(i<Q+R){
    //                 if(j>Q+R-1 && j<size-(R+Q))
    //                     gsl_spmatrix_uint_set(mat, index_i_j, (i + 1) * size + j, NO_DIR);
    //                 if(j>Q+R)    
    //                     gsl_spmatrix_uint_set(mat, index_i_j, (i + 1) * size + j - 1, NO_DIR);
    //                 if(j<size-(Q+R)-1)
    //                     gsl_spmatrix_uint_set(mat, index_i_j, (i + 1) * size + j + 1, NO_DIR);
    //             }
    //             if (i>size-(R+Q)-1){
    //                 if (j>Q+R-1 && j<size-(R+Q))
    //                     gsl_spmatrix_uint_set(mat, index_i_j, (i - 1) * size + j, NO_DIR);
    //                 if (j > Q+R)
    //                     gsl_spmatrix_uint_set(mat, index_i_j, (i - 1) * size + j - 1, NO_DIR);
    //                 if (j < size - (R+Q)-1)
    //                     gsl_spmatrix_uint_set(mat, index_i_j, (i - 1) * size + j + 1, NO_DIR);
    //             }
    //             if (j<size-(Q+R))
    //                 gsl_spmatrix_uint_set(mat, index_i_j, i * size + j + 1, NO_DIR);
    //             if (j>Q+R-1)
    //                 gsl_spmatrix_uint_set(mat, index_i_j, i * size + j - 1, NO_DIR);
    //         }
    //     }
    }
    gsl_spmatrix_uint* csr = gsl_spmatrix_uint_compress(mat, GSL_SPMATRIX_CSR);
    gsl_spmatrix_uint_free(mat);

    return csr;
}

enum sort world_get(struct world_t* world, unsigned int i)
{
    return world->idx[i];
}

void world_set(struct world_t* world, unsigned int i, enum sort s)
{
    world->idx[i] = s;
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
        world_set(world, i, NO_SORT);
    }

    return world;
}

void compute_queens_pos(int m, struct world_t* world, int num_queens, unsigned int* queens[NUM_PLAYERS]) {
    //int test  = (m - (num_queens / 2)) / ((num_queens /2) + 1);
  
    for(int i = 0; i < num_queens / 4; i++) {
        world_set(world, 2 * i + 1, B_QUEEN);
        queens[0][4 * i] = 2 * i + 1;
        world_set(world, m - 1 - (2 * i + 1), B_QUEEN);
        queens[0][4 * i + 1] = m - 1 - (2 * i + 1);
        world_set(world, (2 * i + 1) * m, B_QUEEN);
        queens[0][4 * i + 2] = (2 * i + 1) * m;
        world_set(world, (2 * i + 2) * m - 1, B_QUEEN);
        queens[0][4 * i + 3] = (2 * i + 2) * m - 1;
    
        world_set(world, m * m - m + 2 * i + 1, W_QUEEN);
        queens[1][4 * i] = m * m - m + 2 * i + 1;
        world_set(world, m * m - m - (2 * i + 1) * m, W_QUEEN);
        queens[1][4 * i + 1] = m * m - m -  (2 * i + 1) * m;
        world_set(world, m * m - 1 - (2 * i + 1) * m, W_QUEEN);
        queens[1][4 * i + 2] = m * m - 1 -  (2 * i + 1) * m;
        world_set(world, m * m - 1 - (2 * i + 1 ), W_QUEEN);
        queens[1][4 * i + 3] = m * m - 1 - (2 * i + 1 );
    }
}

/*
  free le tableau world alloué dynamiquement
*/
void free_world(struct world_t* world)
{
    free(world->idx);
    free(world);
}

// const char* board_thing[4] = {"\u25A1","\u2686","\u2688","\u2915"};
const char* board_thing[4] = {"\u00B7","\u2655","\u265b","\u25a0"};
// const char* board_thing[4] = {"\u25A1","\u2655","\u265b","\u25a0"};

/*
  c'est dans le nom de la fonction XD
*/
void print_world(struct world_t* world)
{
    int size = world->width;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%s ", board_thing[world_get(world, j + i * size)]);
        }
        printf("\n");
    }
    printf("\n");
}

void free_queens(unsigned int* queens[]) {
    for(int i = 0; i < 2; i++)
        free(queens[i]);
}

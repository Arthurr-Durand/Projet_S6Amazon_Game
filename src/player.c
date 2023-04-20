#include "player.h"
#include "dir.h"
#include "graph.h"
#include "move.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct player_data {
    unsigned int id;
    struct graph_t* graph;
    unsigned int num_queens;
    unsigned int** queens;
};

static struct player_data data;

char const* get_player_name()
{
    const char* bot = "BOTTES de Anton";
    return bot;
}

void initialize(unsigned int player_id, struct graph_t* graph, unsigned int num_queens, unsigned int* queens[NUM_PLAYERS])
{
    data.id = player_id;

    data.num_queens = num_queens;

    data.queens = (unsigned int**)malloc(sizeof(unsigned int*) * NUM_PLAYERS);
    for (unsigned int p = 0; p < NUM_PLAYERS; p++) {
        data.queens[p] = (unsigned int*)malloc(sizeof(unsigned int) * data.num_queens);
        for (unsigned int q = 0; q < data.num_queens; q++)
            data.queens[p][q] = queens[p][q];
    }

    data.graph = malloc(sizeof(struct graph_t));
    data.graph->num_vertices = graph->num_vertices;
    gsl_spmatrix_uint* tmp = gsl_spmatrix_uint_alloc(graph->t->size1, graph->t->size2);
    data.graph->t = gsl_spmatrix_uint_compress(tmp, GSL_SPMATRIX_CSR);
    gsl_spmatrix_uint_memcpy(data.graph->t, graph->t);
    gsl_spmatrix_uint_free(tmp);
}

// unsigned int tiiiiiir(unsigned int pos){
//     unsigned int dir=(rand()%8)+1;
//     int stop =1;
//     while((rand()%sqrt(data.graph->num_vertices)) && (stop != 0)){
//             unsigned int k = data.graph->t[pos][0];
//             //for (unsigned int k = data.graph->p[ligne]; k < data.graph->p[ligne+1] ; k++)
//                 while ((data.graph->t[pos][k] != dir) && (stop!=0)){
//                     if(k >= (data.graph->p[pos+1])){
//                         stop = 0;
//                         k--;
//                     }
//                     k++;
//                 }
//                 // if (pas possible){
//                 //     stop = 0;
//                 // }
//             pos = k ;
//         }
//     return pos;
// }

/*
 * Check if a queen can move in a direction
 *
 * Return the new position (index) if it is accessible
 * Return the queen_position else
 */
unsigned int get_next_postion(unsigned int position, unsigned int dir)
{
    unsigned int new_position = position;
    unsigned int size = sqrt(data.graph->t->size1);

    switch (dir) {
    case DIR_NORTH:
        new_position = new_position - size;
        break;
    case DIR_NE:
        new_position = new_position - size + 1;
        break;
    case DIR_EAST:
        new_position = new_position + 1;
        break;
    case DIR_SE:
        new_position = new_position + size + 1;
        break;
    case DIR_SOUTH:
        new_position = new_position + size;
        break;
    case DIR_SW:
        new_position = new_position + size - 1;
        break;
    case DIR_WEST:
        new_position = new_position - 1;
        break;
    case DIR_NW:
        new_position = new_position - size - 1;
        break;
    default:
        break;
    }

    return new_position;
}

struct move_t play(struct move_t previous_move)
{

    struct move_t next_move;
    unsigned int queen_position;
    unsigned int new_queen_position;
    unsigned int dir;

    unsigned int find = 0;
    for (unsigned int queen_nb = 0; (queen_nb < data.num_queens && !find); queen_nb++) { // For each queen
        queen_position = data.queens[data.id][queen_nb];
        for (int k = data.graph->t->p[queen_position]; k < data.graph->t->p[queen_position + 1] && !find; k++) { // For each accessible directions
            dir = gsl_spmatrix_uint_get(data.graph->t, queen_position, data.graph->t->i[k]);
            new_queen_position = get_next_postion(queen_position, dir);
            if (new_queen_position != queen_position) { // If the position is reachable (no queen + no arrow)
                next_move.queen_src = queen_position;
                next_move.queen_dst = new_queen_position;
                data.queens[data.id][queen_nb] = new_queen_position;
                find = 1;
            }
        }
    }

    next_move.arrow_dst = 0; // TO DO

    return next_move;

    /* ------------------------------------------------------------------------------------------ */

    // unsigned int position = data.queens[data.id][rand() % data.num_queens];

    // next_move.queen_src = line;

    // unsigned int dir = gsl_spmatrix_uint_get(data.graph->t, line, data.graph->t->i[data.graph->t->p[line]]); // direction == premiere elements non nul de la ligne n:ligne

    // printf("%d\n", dir);
    // int max_dep = rand() % (int)sqrt(data.graph->num_vertices-1)+1; // The distance that the tower will try to reach

    // int stop = 1;
    // while (max_dep && stop) {
    //     unsigned int k = data.graph->t[line][0]; // on test tt les k elements de la
    //     // for (unsigned int k = data.graph->p[ligne]; k < data.graph->p[ligne+1] ; k++)
    //     while ((data.graph->t[line][k] != dir) && (stop != 0)) {
    //         if (k >= (data.graph->t[line + 1])) {
    //             stop = 0;
    //             k--;
    //         }
    //         k++;
    //     }
    //     // if (pas possible){  // depend de k
    //     //     stop = 0;
    //     // }
    //     ligne = k;
    //     max_dep--;
    // }
    // next_move.queen_dst=ligne;
    // next_move.arrow_dst= tiiiiiir(ligne);

    /* ------------------------------------------------------------------------------------------ */
}

void finalize()
{
    for (unsigned int p = 0; p < NUM_PLAYERS; p++)
        free(data.queens[p]);
    free(data.queens);
    gsl_spmatrix_uint_free(data.graph->t);
    free(data.graph);
}

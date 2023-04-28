#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "tools.h"

struct player_data {
    unsigned int id;
    struct graph_t* graph;
    unsigned int num_queens;
    unsigned int** queens;
};

static struct player_data data;

char const* get_player_name()
{
    const char* bot = "TOTO";
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
    gsl_spmatrix_uint *tmp = gsl_spmatrix_uint_alloc(data.graph->num_vertices, data.graph->num_vertices);
    data.graph->t = gsl_spmatrix_uint_compress(tmp, GSL_SPMATRIX_CSR);
    gsl_spmatrix_uint_memcpy(data.graph->t, graph->t);
    gsl_spmatrix_uint_free(tmp);
}

//put a random number between 0 and 24 as the new move
struct move_t play(struct move_t previous_move) {
  struct move_t new_move;
  new_move.queen_src = previous_move.queen_dst;
  unsigned int rd1 = rand() % 25;
  unsigned int rd2 = rand() % 25;
  new_move.queen_dst = rd1;
  new_move.arrow_dst = rd2;  
  return new_move;
}

void finalize()
{
    for (unsigned int p = 0; p < NUM_PLAYERS; p++)
        free(data.queens[p]);
    free(data.queens);
    gsl_spmatrix_uint_free(data.graph->t);
    free(data.graph);
}

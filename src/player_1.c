#include "player.h"
#include "dir.h"
#include "graph.h"
#include "move.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "move_server.h"

struct player_data {
    unsigned int id;
    struct graph_t* graph;
    unsigned int num_queens;
    unsigned int** queens;
    unsigned int size;
    unsigned int* world;
};

static struct player_data data;

struct move_t first_move = {-1, -1, -1};

char const* get_player_name()
{
    const char* bot = "ArThUr";

    return bot;
}

void initialize(unsigned int player_id, struct graph_t* graph, unsigned int num_queens, unsigned int* queens[NUM_PLAYERS])
{
    data.id = player_id;

    data.num_queens = num_queens;

    data.queens = malloc(sizeof(unsigned int*) * NUM_PLAYERS);
    for (unsigned int p = 0; p < NUM_PLAYERS; p++) {
        data.queens[p] = malloc(sizeof(unsigned int) * data.num_queens);
        for (unsigned int q = 0; q < data.num_queens; q++) {
            data.queens[p][q] = queens[p][q];
        }
    }

    data.size = graph->t->size1;

    data.world = malloc(sizeof(unsigned int) * data.size);
    for (unsigned int i = 0; i < data.size; i++)
        data.world[i] = 0;
    for (unsigned int i = 0; i < NUM_PLAYERS; i++) {
        for (unsigned int j = 0; j < num_queens; j++) {
            data.world[data.queens[i][j]] = 1;
        }
    }

    data.graph = malloc(sizeof(struct graph_t));
    data.graph->num_vertices = graph->num_vertices;
    gsl_spmatrix_uint* tmp = gsl_spmatrix_uint_alloc(graph->t->size1, graph->t->size2);
    data.graph->t = gsl_spmatrix_uint_compress(tmp, GSL_SPMATRIX_CSR);
    gsl_spmatrix_uint_memcpy(data.graph->t, graph->t);
    gsl_spmatrix_uint_free(tmp);
}

/*
 * Check if a queen can move in a direction
 *
 * Return the new position (index) if it is accessible
 * Return the queen_position else
 */
unsigned int get_next_postion(unsigned int position, unsigned int dir)
{
    unsigned int new_position = position;
    unsigned int size = sqrt(data.size);

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

    return (data.world[new_position]) ? position : new_position;
}

unsigned int tiiir(unsigned int queen_pos)
{
    unsigned int arrow_pos;
    int find = 0;
    for (int k = data.graph->t->p[queen_pos]; k < data.graph->t->p[queen_pos + 1] && !find; k++) { // For each accessible directions
        unsigned int dir = gsl_spmatrix_uint_get(data.graph->t, queen_pos, data.graph->t->i[k]);
        arrow_pos = get_next_postion(queen_pos, dir);
        if (arrow_pos != queen_pos)
            find = 1;
    }

    return arrow_pos;
}

struct move_t play(struct move_t previous_move)
{
    struct move_t next_move;
    unsigned int queen_position;
    unsigned int new_queen_position;

    if (previous_move.queen_src != UINT_MAX) {
        for (unsigned int i = 0; i < data.num_queens; i++) {
            unsigned int* queen = &data.queens[(data.id + 1) % NUM_PLAYERS][i];
            if (*queen == previous_move.queen_src)
                *queen = previous_move.queen_dst;
        }
        data.world[previous_move.queen_src] = 0;
        data.world[previous_move.queen_dst] = 1;
        data.world[previous_move.arrow_dst] = 1;
    }

    unsigned int find = 0;
    for (unsigned int queen_nb = 0; (queen_nb < data.num_queens && !find); queen_nb++) { // For each queen
        queen_position = data.queens[data.id][queen_nb];
        for (int k = data.graph->t->p[queen_position]; k < data.graph->t->p[queen_position + 1] && !find; k++) { // For each accessible directions
            unsigned int dir = gsl_spmatrix_uint_get(data.graph->t, queen_position, data.graph->t->i[k]);
            new_queen_position = get_next_postion(queen_position, dir);   
            if (new_queen_position != queen_position && data.world[new_queen_position] == 0) { // If the position is reachable (no queen + no arrow)
                next_move.queen_src = queen_position;
                next_move.queen_dst = new_queen_position;
                data.queens[data.id][queen_nb] = new_queen_position;
                find = 1;
            }
        }
    }

    data.world[queen_position] = 0;
    data.world[new_queen_position] = 1;

    next_move.arrow_dst = tiiir(new_queen_position);

    data.world[next_move.arrow_dst] = 1;

    return next_move;
}

void finalize()
{
    for (unsigned int p = 0; p < NUM_PLAYERS; p++)
        free(data.queens[p]);
    free(data.queens);
    free(data.world);
    gsl_spmatrix_uint_free(data.graph->t);
    free(data.graph);
}


#include "game.h"

struct player* start_player(struct player* player_1, struct player* player_2)
{
    if (rand() % 2 == 0)
        return player_1;
    return player_2;
}

struct player* compute_next_player(struct player* current, struct player* player_1, struct player* player_2)
{
    if (player_1->color == current->color)
        return player_2;
    return player_1;
}

enum player_color sort_to_player_color(enum sort sort)
{
    return ( sort == B_QUEEN )? BLACK : WHITE;
}

enum sort player_color_to_sort(enum player_color color)
{
    return (color == BLACK ) ? B_QUEEN : W_QUEEN;
}

int am_i_winning(struct world_t* world, struct graph_t* graph, unsigned int id_player, unsigned int** queens, unsigned int queens_num)
{
    for (unsigned int j=0; j<queens_num;j++){
            unsigned int queen_pos = queens[id_player][j];
            unsigned int new_queen_pos = queen_pos;
        for (int k = graph->t->p[queen_pos]; k < graph->t->p[queen_pos + 1]; k++) { 
            unsigned int dir = gsl_spmatrix_uint_get(graph->t, queen_pos, graph->t->i[k]);
            new_queen_pos = exists_neighbor(graph, dir, queen_pos);
            if((world_get(world, new_queen_pos) == NO_SORT) && (new_queen_pos != graph->t->size1))
                return 0;
        }
    }
    return 1;
}

void end_game(struct world_t* world, struct graph_t graph, unsigned int** queens, struct moves_t* moves, struct player player_1, struct player player_2)
{
    free_world(world);
    free_queens(queens);
    free_moves(moves);
    gsl_spmatrix_uint_free(graph.t);
    player_1.finalize();
    player_2.finalize();
}
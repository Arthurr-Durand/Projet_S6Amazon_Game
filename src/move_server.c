#include <stdlib.h>
#include "move_server.h"

struct moves_t* moves_add(struct moves_t* moves, struct move_t move)
{
    moves->t = realloc(moves->t, (moves->current + 2) * sizeof(struct move_t));
    moves->current++;
    moves->t[moves->current] = move;
    return moves;
}

//return if the destination of the arrow or the queuen are out of the world
int not_in_world(unsigned int size, struct move_t new_move) {
    return (new_move.queen_src == new_move.queen_dst || new_move.arrow_dst == new_move.queen_dst ||
	    new_move.queen_src > size ||
	    new_move.queen_dst > size ||
        new_move.arrow_dst > size);
}

void dirs_possible(enum dir_t* dirs, unsigned int src, unsigned int dst)
{
    if (src > dst) {
        for (int i = 0; i < 2; i++) {
            dirs[i] = i + 1;
            dirs[i + 2] = i + 7;
        }
    } else {
        for (int i = 0; i < 4; i++)
            dirs[i] = i + 3;
    }
}

int obstacle(struct graph_t* graph, struct world_t* world, unsigned int src, unsigned int dst)
{
    enum dir_t dirs[4];
    dirs_possible(dirs, src, dst);
    for (unsigned int i = 0; i < 4; i++) {
        unsigned int current = exists_neighbor(graph, dirs[i], src);
        while ((current < graph->num_vertices) && (world->idx[current] == NO_SORT)) {
            if (current == dst)
	            return 0;
            current = exists_neighbor(graph, dirs[i], current);
        }
    }
    return 1;
}

int is_move_valid(struct graph_t* graph, struct world_t* world, struct move_t new_move)
{ 
    return (not_in_world(world->width * world->width, new_move) || obstacle(graph, world, new_move.queen_src, new_move.queen_dst) || ((new_move.queen_src == new_move.arrow_dst) || obstacle(graph, world, new_move.queen_dst, new_move.arrow_dst)));
}

unsigned int exists_neighbor(struct graph_t* graph, enum dir_t dir, unsigned int current) {
    enum dir_t new_dir;
    unsigned int idx;
    for (int k = graph->t->p[current]; k < graph->t->p[current+1]; k++) {
	idx = graph->t->i[k];
	new_dir = gsl_spmatrix_uint_get(graph->t, current, idx);
	if (new_dir == dir) {
	    return idx;
	}
    }
    return graph->num_vertices;
}

void print_move(struct move_t move)
{
	printf("{ %d %d %d }  ", move.queen_src, move.queen_dst, move.arrow_dst);  
}

void print_moves(struct moves_t* moves)
{
    printf("[ ");
    for (unsigned int i = 0; i <= moves->current; i++) {
        print_move(moves->t[i]);
    }
    printf("]\n");
}

void free_moves(struct moves_t* moves)
{
    free(moves->t);
    free(moves);
}

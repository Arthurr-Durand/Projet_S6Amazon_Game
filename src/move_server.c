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
int not_in_world(unsigned int size, struct move_t new_move)
{
    return (new_move.queen_src == new_move.queen_dst || new_move.arrow_dst == new_move.queen_dst ||
	    new_move.queen_src >= size ||
	    new_move.queen_dst >= size ||
        new_move.arrow_dst >= size);
}

/*
 * Simple and easy to read function which returns the direction to go from the src index to the dst index. Returns NO_DIR if it's not possible.
 */
enum dir_t get_direction(int width, int src, int dst)
{
    int dx = dst % width - src % width;
    int dy = dst / width - src / width;
    return (dx == 0 && dy == 0) ? NO_DIR
        : (dx == 0)             ? ((dy > 0) ? DIR_SOUTH : DIR_NORTH)
        : (dy == 0)             ? ((dx > 0) ? DIR_EAST : DIR_WEST)
        : (dx == dy)            ? ((dx > 0) ? DIR_SE : DIR_NW)
        : (dx == -dy)           ? ((dx > 0) ? DIR_NE : DIR_SW)
                                : NO_DIR;
}

int obstacle(struct graph_t* graph, struct world_t* world, unsigned int src, unsigned int dst)
{
    enum dir_t dir = get_direction(sqrt(graph->t->size1), src, dst);
    if (dir == NO_DIR)
        return 1;
    unsigned int current = exists_neighbor(graph, dir, src);
    while ((current < graph->num_vertices) && (world->idx[current] == NO_SORT)) {
        if (current == dst)
	        return 0;
        current = exists_neighbor(graph, dir, current);
    }
    return 1;
}

int is_move_valid(struct graph_t* graph, struct world_t* world, struct move_t new_move) {
    if(!(not_in_world(world->width * world->width, new_move)) && !(obstacle(graph, world, new_move.queen_src, new_move.queen_dst))) { 
        enum sort old_sort = world->idx[new_move.queen_src];
        world->idx[new_move.queen_src] = NO_SORT;
        if (!(obstacle(graph, world, new_move.queen_dst, new_move.arrow_dst))) {
            world->idx[new_move.queen_src] = old_sort;
            return 1;
        }
        world->idx[new_move.queen_src] = old_sort;
    }
  return 0;
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

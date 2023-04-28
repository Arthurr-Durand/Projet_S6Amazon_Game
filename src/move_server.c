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

int obstacle(struct graph_t* graph, struct world_t* world, struct move_t new_move) { 
  unsigned int *dirs = malloc(4 * sizeof(unsigned int));
  dirs_possible(dirs, new_move.queen_src, new_move.queen_dst);
  for(unsigned int i=0; i < 4; i++) {
    
  }
}


int is_move_valid(struct graph_t* graph, struct world_t* world,
	       struct moves_t* moves, struct move_t new_move)
{
  unsigned int size = world->width * world->width;
  if ( not_in_world(size, new_move) || obstacle(graph, world, new_move) )
	//  TO DO || dst are not reachable (not straight line or something between)
	return 0;
    
    moves = moves_add(moves, new_move);
    world->idx[new_move.queen_dst] = world->idx[new_move.queen_src];
    world->idx[new_move.queen_src] = NO_SORT;
    world->idx[new_move.arrow_dst] = BLOCK;
    return 1;
}

void print_moves(struct moves_t* moves)
{
    printf("[ ");
    for (unsigned int i = 0; i <= moves->current; i++) {
	printf("{ %d %d %d }  ", moves->t[i].queen_src, moves->t[i].queen_dst, moves->t[i].arrow_dst);
    }
    printf("]\n");
}

void free_moves(struct moves_t* moves)
{
    free(moves->t);
    free(moves);
}

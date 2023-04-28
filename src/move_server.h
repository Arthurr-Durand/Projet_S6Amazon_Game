#ifndef _MOVE_SERVER_H_
#define _MOVE_SERVER_H_

#include "move.h"
#include "world.h"

struct moves_t* moves_add(struct moves_t* moves, struct move_t move);

int is_move_valid(struct graph_t* graph, struct world_t* world,
	       struct moves_t* moves, struct move_t new_move);

void dirs_possible(unsigned int* dirs, unsigned int src, unsigned int dst);

void print_moves(struct moves_t* moves);

void free_moves(struct moves_t* moves);

#endif // _MOVE_SERVER_H_

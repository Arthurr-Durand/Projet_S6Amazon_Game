#ifndef _MOVE_SERVER_H_
#define _MOVE_SERVER_H_

#include "move.h"
#include "world.h"
#include "dir.h"

struct moves_t* moves_add(struct moves_t* moves, struct move_t move);

int not_in_world(unsigned int size, struct move_t new_move);

enum dir_t get_direction(int size, int src, int dst);

int obstacle(struct graph_t* graph, struct world_t* world, unsigned int src, unsigned int dst);

int is_move_valid(struct graph_t* graph, struct world_t* world, struct move_t new_move);

unsigned int exists_neighbor(struct graph_t* graph, enum dir_t dir, unsigned int current);

void print_move(struct move_t move);

void print_moves(struct moves_t* moves);

void free_moves(struct moves_t* moves);

#endif // _MOVE_SERVER_H_

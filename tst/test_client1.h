#ifndef _TEST_CLIENT_H_
#define _TEST_CLIENT_H_

#include "graph.h"
#include "move.h"
#include "world.h"

int is_queen(unsigned int* queens[], unsigned int num_queens, unsigned int pos);

int is_arrow(unsigned int arrows[], unsigned int arrows_number, unsigned int pos);

void game__test(int width, unsigned int* queens[], unsigned int num_queens, unsigned int arrows[], unsigned int arrows_number);

void get_player_name__test(char const* (*get_player_name)());

void initialize__test(void (*initialize)());

void finalize__test(void (*finalize)());

void play__test(void (*initialize)(), struct move_t (*play)(), void (*finalize)(), void (*initialize2)(), struct move_t (*play2)(), void (*finalize2)());

#endif // _TEST_CLIENT_H_

#ifndef _TEST_GAME_H_
#define _TEST_GAME_H_

#include "world.h"
#include "tools.h"
#include "move_server.h"
#include "game.h"

void start_player__test(struct player* player1, struct player* player2);

void compute_next_player__test(struct player* player1, struct player* player2);

void sort_to_player_color__test();

void player_color_to_sort__test();

void am_i_wining__test();

#endif // _TEST_GAME_H_

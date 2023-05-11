#ifndef _GAME_H_
#define _GAME_H_

#include "move_server.h"
#include "tools.h"

enum player_color {
    BLACK = 0,
    WHITE = 1,
    NB_COLORS = 2,
};

struct player {
    char const* (*get_player_name)(void);
    void (*initialize)(unsigned int, struct graph_t*, unsigned int, unsigned int**);
    struct move_t (*play)(struct move_t);
    void (*finalize)(void);
    enum player_color color;
};

struct player* start_player(struct player* player_1, struct player* player_2);

struct player* compute_next_player(struct player* current, struct player* player_1, struct player* player_2);

enum player_color sort_to_player_color(enum sort sort);

enum sort player_color_to_sort(enum player_color color);

int am_i_winning(struct world_t* world, struct graph_t* graph, unsigned int id_player, unsigned int** queens, unsigned int queens_num);

void end_game(struct world_t* world, struct graph_t graph, unsigned int** queens, struct moves_t* moves, struct player player_1, struct player player_2);


#endif // _GAME_H_
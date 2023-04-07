#include <stdio.h>
#include <stdlib.h>

#include "player.h"

struct player_data {
    unsigned int id;
    struct graph_t* graph;
    unsigned int num_queens;
    unsigned int* queens[NUM_PLAYERS];
};

static struct player_data data;

char const* get_player_name()
{
    const char* bot = "BOTTES de Anton";
    return bot;
}

void initialize(unsigned int player_id, struct graph_t *graph, unsigned int num_queens, unsigned int *queens[NUM_PLAYERS])
{
    data.id = player_id;
    data.graph = graph;
    data.num_queens = num_queens;
    data.queens[NUM_PLAYERS] = queens[NUM_PLAYERS];
}

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "world.h"
#include "tools.h"
#include "move_server.h"
#include "game.h"


void start_player__test(struct player* player1, struct player* player2)
{
    printf("\t%s", __func__);
 
    struct player* current_player = start_player(player1, player2);

    player1->color = (player1->get_player_name() == current_player->get_player_name()) ? BLACK : WHITE;
    player2->color = (player2->get_player_name() == current_player->get_player_name()) ? BLACK : WHITE;
 
    printf("\t\tOK\n");
}

void compute_next_player__test(struct player* player1, struct player* player2)
{
    printf("\t%s", __func__);

    assert(compute_next_player(player1, player1, player2) == player2);
    assert(compute_next_player(player2, player1, player2) == player1);

    printf("\tOK\n");
}

void sort_to_player_color__test()
{
    printf("\t%s", __func__);

    assert(sort_to_player_color(B_QUEEN) == BLACK);
    assert(sort_to_player_color(W_QUEEN) == WHITE);

    printf("\tOK\n");
}

void player_color_to_sort__test()
{
    printf("\t%s", __func__);

    assert(player_color_to_sort(BLACK) == B_QUEEN);
    assert(player_color_to_sort(WHITE) == W_QUEEN);

    printf("\tOK\n");
}

void am_i_wining__test()
{
    printf("\t%s", __func__);

    struct graph_t graph = { 25, graph_init(5, SQUARED) };
    struct world_t* world = world_init(5);
    unsigned int* queens[2];
    queens[0] = malloc(sizeof(unsigned int) * 4);
    queens[1] = malloc(sizeof(unsigned int) * 4);
    queens[0][0] = 1;
    queens[0][1] = 8;
    queens[0][2] = 15;
    queens[0][3] = 18;
    queens[1][0] = 4;
    queens[1][1] = 13;
    queens[1][2] = 17;
    queens[1][3] = 21;
    world_set(world, 3, BLOCK);
    world_set(world, 7, BLOCK);
    world_set(world, 9, BLOCK);
    world_set(world, 10, BLOCK);
    world_set(world, 11, BLOCK);
    world_set(world, 12, BLOCK);
    world_set(world, 14, BLOCK);
    world_set(world, 16, BLOCK);
    world_set(world, 19, BLOCK);
    world_set(world, 20, BLOCK);
    world_set(world, 22, BLOCK);
    world_set(world, 23, BLOCK);
    world_set(world, 1, B_QUEEN);
    world_set(world, 8, B_QUEEN);
    world_set(world, 15, B_QUEEN);
    world_set(world, 18, B_QUEEN);
    world_set(world, 4, W_QUEEN);
    world_set(world, 13, W_QUEEN);
    world_set(world, 17, W_QUEEN);
    world_set(world, 21, W_QUEEN);

    // printf("\n");
    // print_world(world);

    assert(am_i_winning(world, &graph, BLACK, queens, 4) == 0);
    assert(am_i_winning(world, &graph, WHITE, queens, 4) == 1);

    free_world(world);
    free_queens(queens);
    gsl_spmatrix_uint_free(graph.t);

    printf("\t\tOK\n");
}

int main()
{
    printf("%s\n", __FILE__);

    void* player_1;
    struct player iencly;
    
    void* player_2;
    struct player internet;
        
    player_1 = dlopen("./install/client1.so", RTLD_LAZY);
    iencly.get_player_name = dlsym(player_1, "get_player_name" );
    iencly.initialize = dlsym(player_1, "initialize" );
    iencly.play = dlsym(player_1, "play");
    iencly.finalize = dlsym(player_1, "finalize");

    player_2 = dlopen("./install/client2.so", RTLD_LAZY);
    internet.get_player_name = dlsym(player_2, "get_player_name" );
    internet.initialize = dlsym(player_2, "initialize" );
    internet.play = dlsym(player_2, "play");
    internet.finalize = dlsym(player_2, "finalize");

    start_player__test(&iencly, &internet);

    compute_next_player__test(&iencly, &internet);

    sort_to_player_color__test();

    player_color_to_sort__test();

    am_i_wining__test();

    dlclose(player_1);
    dlclose(player_2);

    return EXIT_SUCCESS;
}

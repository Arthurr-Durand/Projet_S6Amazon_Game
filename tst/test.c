#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_client1.h"
#include "test_game.h"
#include "test_move_server.h"
#include "test_world.h"

void test_client1()
{
    printf("test_client1\n");

    void* client;
    char const* (*get_player_name)();
    void (*initialize)();
    struct move_t (*play)();
    void (*finalize)();

    client = dlopen("./install/client1.so", RTLD_LAZY);
    get_player_name = dlsym(client, "get_player_name");
    initialize = dlsym(client, "initialize");
    play = dlsym(client, "play");
    finalize = dlsym(client, "finalize");

    void* client2;
    void (*initialize2)();
    struct move_t (*play2)();
    void (*finalize2)();

    client2 = dlopen("./install/client2.so", RTLD_LAZY);
    initialize2 = dlsym(client2, "initialize");
    play2 = dlsym(client2, "play");
    finalize2 = dlsym(client2, "finalize");

    get_player_name__test(get_player_name);
    initialize__test(initialize);
    finalize__test(finalize);
    play__test(initialize, play, finalize, initialize2, play2, finalize2);

    dlclose(client);

    dlclose(client2);
}

void test_game()
{
    printf("test_game\n");

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
}

void test_move_server()
{
    printf("test_move_server\n");

    moves_add__test();
    not_in_world__test();
    get_direction__test();
    obstacle__test();
    is_move_valid__test();
    exists_neighbor__test();
}

void test_world()
{
    printf("test_world\n");

    world_init__test();
    world_set__test();
    world_get__test();
    compute_queens_pos__test();
}

int main()
{
    test_client1();
    test_game();
    test_move_server();
    test_world();

    return EXIT_SUCCESS;
}

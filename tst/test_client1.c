#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/graph.h"
#include "../src/move.h"
#include "../src/world.h"

#define NUM_PLAYERS 2

void test_get_player_name(char const* (*get_player_name)())
{
    printf("\t%s", __func__);
    assert(!strcmp((*get_player_name)(), "BOTTES de Anton"));
    printf("\tOK\n");
}

void test_initialize(void (*initialize)())
{
    printf("\t%s", __func__);

    unsigned int player_id = 0;

    int width = 3;
    struct graph_t graph = { width * width, graph_init(width, SQUARED) };

    unsigned int num_queens = 2;

    unsigned int* queens[NUM_PLAYERS];
    for (unsigned int i = 0; i < NUM_PLAYERS; i++)
        queens[i] = (unsigned int*)malloc(sizeof(unsigned int) * num_queens);

    queens[0][0] = 0;
    queens[0][1] = 2;
    queens[1][0] = 6;
    queens[1][1] = 8;

    (*initialize)(player_id, &graph, num_queens, queens);

    for (unsigned int i = 0; i < NUM_PLAYERS; i++)
        free(queens[i]);
    gsl_spmatrix_uint_free(graph.t);

    printf("\t\tOK\n");
}

void test_play(struct move_t (*play)())
{
    printf("\t%s", __func__);

    struct move_t previous_move = { 0, 1, 2 };

    struct move_t new_move1 = (*play)(previous_move);
    printf("\nLOG : move from %d to %d.\n", new_move1.queen_src, new_move1.queen_dst);

    struct move_t new_move2 = (*play)(previous_move);
    printf("LOG : move from %d to %d.\n", new_move2.queen_src, new_move2.queen_dst);

    printf("\t\tOK\n");
}

void test_finalize(void (*finalize)())
{
    printf("\t%s", __func__);

    (*finalize)();

    printf("\t\tOK\n");
}

int main()
{
    printf("%s\n", __FILE__);

    void* client;
    char const* (*get_player_name)();
    void (*initialize)();
    struct move_t (*play)();
    void (*finalize)();
    char* error;

    client = dlopen("./install/client1.so", RTLD_LAZY);
    if (!client) {
        fputs(dlerror(), stderr);
        exit(1);
    }

    get_player_name = dlsym(client, "get_player_name");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }

    initialize = dlsym(client, "initialize");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }

    play = dlsym(client, "play");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }

    finalize = dlsym(client, "finalize");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }

    test_get_player_name(get_player_name);
    test_initialize(initialize);
    test_play(play);
    test_finalize(finalize);

    dlclose(client);

    return EXIT_SUCCESS;
}

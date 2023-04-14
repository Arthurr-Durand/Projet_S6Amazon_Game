#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/graph.h"

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

    struct graph_t* graph = malloc(sizeof(struct graph_t));
    graph->num_vertices = 2;
    graph->t = gsl_spmatrix_uint_alloc(3, 3);

    unsigned int num_queens = 1;

    unsigned int* queens[NUM_PLAYERS];
    for (unsigned int i = 0; i < NUM_PLAYERS; i++)
        queens[i] = (unsigned int*)malloc(sizeof(unsigned int));
    queens[0][0] = 1;
    queens[1][0] = 7;

    (*initialize)(player_id, graph, num_queens, queens);

    for (unsigned int i = 0; i < NUM_PLAYERS; i++)
        free(queens[i]);
    gsl_spmatrix_uint_free(graph->t);
    free(graph);

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

    finalize = dlsym(client, "finalize");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }

    test_get_player_name(get_player_name);
    test_initialize(initialize);
    test_finalize(finalize);

    dlclose(client);

    return EXIT_SUCCESS;
}

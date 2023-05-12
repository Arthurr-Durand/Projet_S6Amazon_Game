#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/graph.h"
#include "../src/move.h"
#include "../src/world.h"

#define NUM_PLAYERS 2

int is_queen(unsigned int* queens[], unsigned int num_queens, unsigned int pos)
{
    for (unsigned int i = 0; i < NUM_PLAYERS; i++) {
        for (unsigned int y = 0; y < num_queens; y++) {
            if (queens[i][y] == pos)
                return 1;
        }
    }
    return 0;
}

int is_arrow(unsigned int arrows[], unsigned int arrows_number, unsigned int pos)
{
    for (unsigned int i = 0; i < arrows_number; i++) {
        if (arrows[i] == pos)
            return 1;
    }
    return 0;
}

void game__test(int width, unsigned int* queens[], unsigned int num_queens, unsigned int arrows[], unsigned int arrows_number)
{
    for (int j = 0; j < width; j++) {
        for (int i = 0; i < width; i++) {
            if (is_queen(queens, num_queens, (i + width * j)))
                printf("| ");
            else if (is_arrow(arrows, arrows_number, (i + width * j)))
                printf("X ");
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("\n");
}

void get_player_name__test(char const* (*get_player_name)())
{
    printf("\t%s", __func__);

    assert(!strcmp((*get_player_name)(), "ArThUr"));
    
    printf("\t\tOK\n");
}

void initialize__test(void (*initialize)())
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

void finalize__test(void (*finalize)())
{
    printf("\t%s", __func__);

    (*finalize)();

    printf("\t\t\tOK\n");
}

void play__test(void (*initialize)(), struct move_t (*play)(), void (*finalize)(), void (*initialize2)(), struct move_t (*play2)(), void (*finalize2)())
{
    printf("\t%s", __func__);

    int width = 5;
    struct graph_t graph = { width * width, graph_init(width, SQUARED) };

    unsigned int num_queens = 2;

    unsigned int* queens[NUM_PLAYERS];
    for (unsigned int i = 0; i < NUM_PLAYERS; i++)
        queens[i] = (unsigned int*)malloc(sizeof(unsigned int) * num_queens);

    queens[0][0] = 0;
    queens[0][1] = 4;
    queens[1][0] = 20;
    queens[1][1] = 24;

    (*initialize)(0, &graph, num_queens, queens);
    (*initialize2)(1, &graph, num_queens, queens);

    unsigned int arrows_number = 0;
    unsigned int* arrows = malloc(0);

    struct move_t previous_move = { -1, -1, -1 };
    int max_turn = 5;

    // printf("\n");

    while (max_turn) {
        previous_move = (*play)(previous_move);
        arrows_number++;
        arrows = realloc(arrows, sizeof(unsigned int) * arrows_number);
        arrows[arrows_number - 1] = previous_move.arrow_dst;
        for (unsigned int i = 0; i < NUM_PLAYERS; i++) {
            for (unsigned int y = 0; y < num_queens; y++) {
                if (queens[i][y] == previous_move.queen_src)
                    queens[i][y] = previous_move.queen_dst;
            }
        }

        // printf("Player 0 move queen from (%d) to (%d) and shoot to (%d).\n", previous_move.queen_src, previous_move.queen_dst, previous_move.arrow_dst);
        // print_game(width, queens, num_queens, arrows, arrows_number);

        previous_move = (*play2)(previous_move);
        arrows_number++;
        arrows = realloc(arrows, sizeof(unsigned int) * arrows_number);
        arrows[arrows_number - 1] = previous_move.arrow_dst;
        for (unsigned int i = 0; i < NUM_PLAYERS; i++) {
            for (unsigned int y = 0; y < num_queens; y++) {
                if (queens[i][y] == previous_move.queen_src)
                    queens[i][y] = previous_move.queen_dst;
            }
        }

        // printf("Player 1 move queen from (%d) to (%d) and shoot to (%d).\n", previous_move.queen_src, previous_move.queen_dst, previous_move.arrow_dst);
        // print_game(width, queens, num_queens, arrows, arrows_number);

        max_turn--;
    }

    free(arrows);

    for (unsigned int i = 0; i < NUM_PLAYERS; i++)
        free(queens[i]);
    gsl_spmatrix_uint_free(graph.t);

    (*finalize)();
    (*finalize2)();

    printf("\t\t\tOK\n");
}

int main()
{
    printf("%s\n", __FILE__);

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

    return EXIT_SUCCESS;
}

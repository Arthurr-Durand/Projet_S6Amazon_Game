#include <dlfcn.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "world.h"
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

char const* start_player(char const* player_1, char const* player_2) {
  if (rand() % 2 == 0)
    return player_1;
  return player_2;
}

struct player* compute_next_player(struct moves_t* moves, struct player* player_1, struct player* player_2) {
  if (player_1->color == moves->current)
    return player_1;
  return player_2;
}

int main(int argc, char* argv[])
{
    printf("[-] Server running\n");

    void* player_1;
    struct player iencly;
    /*char const* (*get_player_name_1)(void);
    void (*initialize_1)(unsigned int, struct graph_t*, unsigned int, unsigned int*);
    struct move_t (*play_1)(struct move_t);
    void (*finalize_1)(void);*/
    
    void* player_2;
    struct player internet;
    /*char const* (*get_player_name_2)(void);
    void (*initialize_2)(unsigned int, struct graph_t*, unsigned int, unsigned int*);
    struct move_t (*play_2)(struct move_t);
    void (*finalize_2)(void);*/

    char *error;

    player_1 = dlopen("./install/client1.so", RTLD_LAZY);
    if (!player_1) {
        fputs(dlerror(), stderr);
        exit(1);
    }

    player_2 = dlopen("./install/client2.so", RTLD_LAZY);
    if (!player_1) {
        fputs(dlerror(), stderr);
        exit(1);
    }
    
    iencly.get_player_name = dlsym(player_1, "get_player_name" );
    if ((error = dlerror()) != NULL) {
      fputs(error, stderr);
      exit(1);
    }
    iencly.initialize = dlsym(player_1, "initialize" );
    if ((error = dlerror()) != NULL) {
      fputs(error, stderr);
      exit(1);
    }
    //iencly.play = dlsym(player_1, "play");
    if ((error = dlerror()) != NULL) {
      fputs(error, stderr);
      exit(1);
    }
    iencly.finalize = dlsym(player_1, "finalize");
    if ((error = dlerror()) != NULL) {
      fputs(error, stderr);
      exit(1);
    }

    
    internet.get_player_name = dlsym(player_2, "get_player_name" );
    if ((error = dlerror()) != NULL) {
      fputs(error, stderr);
      exit(1);
    }
    internet.initialize = dlsym(player_2, "initialize" );
    if ((error = dlerror()) != NULL) {
      fputs(error, stderr);
      exit(1);
    }
    //internet.play = dlsym(player_2, "play");
    if ((error = dlerror()) != NULL) {
      fputs(error, stderr);
      exit(1);
    }
    internet.finalize = dlsym(player_2, "finalize");
    if ((error = dlerror()) != NULL) {
      fputs(error, stderr);
      exit(1);
    }
    
    int opt;
    enum type_world w_type = SQUARED;
    unsigned int width = 5;

    while ((opt = getopt(argc, argv, "m:t:")) != -1) {
        switch (opt) {
        case 'm':
            width = atoi(optarg);
            break;
        case 't':
            if (strcmp(optarg, "d") == 0) {
                w_type = DONUT;
            }
            if (strcmp(optarg, "t") == 0) {
                w_type = CLOVER;
            }
            if (strcmp(optarg, "8") == 0) {
                w_type = EIGHT;
            }
            break;
        }
    }

    srand(time(NULL));

    char const* first_player = start_player(iencly.get_player_name(), internet.get_player_name());

    iencly.color = (iencly.get_player_name() == first_player) ? BLACK : WHITE;
    internet.color = (internet.get_player_name() == first_player) ? BLACK : WHITE;

    struct graph_t graph = { width * width, graph_init(width, w_type) };
    struct world_t * world = world_init(width);

    int num_queens = 4*(width/10 + 1);
    unsigned int* queens[NUM_PLAYERS];
    queens[0] = malloc(sizeof(unsigned int) * num_queens);
    queens[1] = malloc(sizeof(unsigned int) * num_queens);
    compute_queens_pos(width, world, num_queens, queens);
    
    iencly.initialize(iencly.color, &graph, num_queens, queens);
    internet.initialize(iencly.color, &graph, num_queens, queens);

    struct move_t move = {-1, -1, -1};
    struct moves_t moves = {&move, BLACK};

    struct player* current_player;
    // while (???)
    current_player = compute_next_player(&moves, &iencly, &internet);
    //move = current_player->play(move);
    moves.current = (moves.current + 1) % NUM_PLAYERS;
    
    free_world(world);
    free_queens(queens);
    gsl_spmatrix_uint_free(graph.t);
    iencly.finalize();
    internet.finalize();
    dlclose(player_1);
    dlclose(player_2);

    return EXIT_SUCCESS;
}

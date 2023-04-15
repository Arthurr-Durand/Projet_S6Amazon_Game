#include <dlfcn.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "world.h"
#include "tools.h"

int main(int argc, char* argv[])
{
    printf("[-] Server running\n");

    void* iencly;
    char const* (*get_player_name_1)(void);
    void (*initialize_1)(unsigned int, struct graph_t*, unsigned int, unsigned int*);
    struct move_t (*play_1)(struct move_t);
    void (*finalize_1)(void);
    
    void* internet;
    char const* (*get_player_name_2)(void);
    void (*initialize_2)(unsigned int, struct graph_t*, unsigned int, unsigned int*);
    struct move_t (*play_2)(struct move_t);
    void (*finalize_2)(void);

    char *error;

    iencly = dlopen("./install/client1.so", RTLD_LAZY);
    if (!iencly) {
        fputs(dlerror(), stderr);
        exit(1);
    }

    internet = dlopen("./install/client2.so", RTLD_LAZY);
    if (!iencly) {
        fputs(dlerror(), stderr);
        exit(1);
    }
    
    get_player_name_1 = dlsym(iencly, "get_player_name" );
    if ((error = dlerror()) != NULL)  {
      fputs(error, stderr);
      exit(1);
    }
    initialize_1 = dlsym(iencly, "initialize" );
    if ((error = dlerror()) != NULL)  {
      fputs(error, stderr);
      exit(1);
    }
    //play_1 = dlsym(iencly, "play");
    if ((error = dlerror()) != NULL)  {
      fputs(error, stderr);
      exit(1);
    }
    finalize_1 = dlsym(iencly, "finalize");
    if ((error = dlerror()) != NULL)  {
      fputs(error, stderr);
      exit(1);
    }

    
    get_player_name_2 = dlsym(internet, "get_player_name" );
    if ((error = dlerror()) != NULL)  {
      fputs(error, stderr);
      exit(1);
    }
    initialize_2 = dlsym(internet, "initialize" );
    if ((error = dlerror()) != NULL)  {
      fputs(error, stderr);
      exit(1);
    }
    //play_2 = dlsym(internet, "play");
    if ((error = dlerror()) != NULL)  {
      fputs(error, stderr);
      exit(1);
    }
    finalize_2 = dlsym(internet, "finalize");
    if ((error = dlerror()) != NULL)  {
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

    char const* player_1 = get_player_name_1();

    char const* player_2 = get_player_name_2();

    printf("%s\n", player_1);
    printf("%s\n", player_2);

    struct graph_t graph = { width * width, graph_init(width, w_type) };

    struct world_t * world = world_init(width);

    int num_queens = 4*(width/10 + 1);

    unsigned int* queens[2];

    queens[0] = malloc(sizeof(unsigned int) * num_queens);
    queens[1] = malloc(sizeof(unsigned int) * num_queens);

    compute_queens_pos(width, world, num_queens, queens);

    free_world(world);

    free_queens(queens);
    
    gsl_spmatrix_uint_free(graph.t);

    dlclose(iencly);

    dlclose(internet);

    return EXIT_SUCCESS;
}

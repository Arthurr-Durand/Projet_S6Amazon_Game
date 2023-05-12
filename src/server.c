#include <dlfcn.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "game.h"

int main(int argc, char* argv[])
{
    printf("[-] Server running\n\n");

    void* player_1;
    struct player iencly;
    
    void* player_2;
    struct player internet;

    char *error;

    printf("[-] Client 1 loading\n");
    
    player_1 = dlopen(argv[argc - 2], RTLD_LAZY);
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
    iencly.play = dlsym(player_1, "play");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }
    iencly.finalize = dlsym(player_1, "finalize");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }

    printf("[-] Client 1 successfully loaded\n\n");

    printf("[-] Client 2 loading\n");
    
    player_2 = dlopen(argv[argc - 1], RTLD_LAZY);
    if (!player_1) {
        fputs(dlerror(), stderr);
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
    internet.play = dlsym(player_2, "play");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }
    internet.finalize = dlsym(player_2, "finalize");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }

    printf("[-] Client 2 successfully loaded\n\n");
    
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
                printf("Le graphe donut n'a pas été implémenté ; le graphe sera carré\n");
            }
            if (strcmp(optarg, "t") == 0) {
                printf("Le graphe trèfle n'a pas été implémenté ; le graphe sera carré\n");
            }
            if (strcmp(optarg, "8") == 0) {
                printf("Le graphe en huit n'a pas été implémenté ; le graphe sera carré\n");
            }
            break;
        }
    }

    srand(time(NULL));

    struct player* current_player = start_player(&iencly, &internet);

    iencly.color = (iencly.get_player_name() == current_player->get_player_name()) ? BLACK : WHITE;
    internet.color = (internet.get_player_name() == current_player->get_player_name()) ? BLACK : WHITE;

    struct graph_t graph = { width * width, graph_init(width, w_type) };
    struct world_t* world = world_init(width);
    
    int num_queens = 4*(width/10 + 1);
    unsigned int* queens[NUM_PLAYERS];
    queens[0] = malloc(sizeof(unsigned int) * num_queens);
    queens[1] = malloc(sizeof(unsigned int) * num_queens);
    compute_queens_pos(width, world, num_queens, queens);
    
    iencly.initialize(iencly.color, &graph, num_queens, queens);
    internet.initialize(internet.color, &graph, num_queens, queens);
    
    struct move_t move = {-1, -1, -1};
    struct moves_t* moves = malloc(sizeof(struct moves_t));
    moves->t = malloc(sizeof(struct move_t));
    moves->t[0] = move;
    moves->current = 0;
    
    current_player = compute_next_player(current_player, &iencly, &internet);
    print_world(world);
    while (!am_i_winning(world, &graph, current_player->color, queens, num_queens)){
        move = current_player->play(move);
        printf("\n%d %d %d\n", move.queen_src, move.queen_dst, move.arrow_dst);
        printf("[-] %s played ", current_player->get_player_name());
        print_move(move);
        printf("\n");

        if (!is_move_valid(&graph, world, move) || (current_player->color != sort_to_player_color(world_get(world, move.queen_src)))){
            printf("[-] %s made an illegal move !\n", current_player->get_player_name());
            current_player = compute_next_player(current_player, &iencly, &internet);
            break;
	    }
        else {
            moves = moves_add(moves, move);
            world_set(world, move.queen_dst, world_get(world, move.queen_src));
            world_set(world, move.queen_src, NO_SORT);
            world_set(world, move.arrow_dst, BLOCK);
            for(int i=0;i<num_queens;i++){
                if(queens[current_player->color][i] == move.queen_src )
                    queens[current_player->color][i]= move.queen_dst;
            }
        }
        print_world(world);
        current_player = compute_next_player(current_player, &iencly, &internet);
    }

    printf("[-] %s as won !\n\n", compute_next_player(current_player, &iencly, &internet)->get_player_name());

    end_game(world, graph, queens, moves, iencly, internet);
    
    printf("[-] Closing client 1\n\n");
    dlclose(player_1);
    printf("[-] Closing client 2\n");
    dlclose(player_2);
    
    return EXIT_SUCCESS;
}

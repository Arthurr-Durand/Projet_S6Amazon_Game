#include <dlfcn.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "world.h"
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

struct player* start_player(struct player* player_1, struct player* player_2)
{
    if (rand() % 2 == 0)
        return player_1;
    return player_2;
}

struct player* compute_next_player(struct player* current, struct player* player_1, struct player* player_2)
{
    if (player_1->color == current->color)
        return player_2;
    return player_1;
}

enum player_color sort_to_player_color(enum sort sort) {
    return ( sort == B_QUEEN )? BLACK : WHITE;
}

enum sort player_color_to_sort(enum player_color color)
{
    return (color == BLACK ) ? B_QUEEN : W_QUEEN;
}

unsigned int get_next_postion(unsigned int position, unsigned int dir, int size)
{
    unsigned int new_position = position;

    switch (dir) {
    case DIR_NORTH:
        new_position = new_position - size;
        break;
    case DIR_NE:
        new_position = new_position - size + 1;
        break;
    case DIR_EAST:
        new_position = new_position + 1;
        break;
    case DIR_SE:
        new_position = new_position + size + 1;
        break;
    case DIR_SOUTH:
        new_position = new_position + size;
        break;
    case DIR_SW:
        new_position = new_position + size - 1;
        break;
    case DIR_WEST:
        new_position = new_position - 1;
        break;
    case DIR_NW:
        new_position = new_position - size - 1;
        break;
    default:
        break;
    }

    return new_position;
}


int am_i_winning(struct world_t* world, struct graph_t* graph, unsigned int id_playeur, unsigned int** queens, unsigned int queens_num){
    for (unsigned int j=0; j<queens_num;j++){
            unsigned int queen_pos = queens[id_playeur][j];
            unsigned int new_queen_pos = queen_pos;
        for (int k = graph->t->p[queen_pos]; k < graph->t->p[queen_pos + 1]; k++) { 
            unsigned int dir = gsl_spmatrix_uint_get(graph->t, queen_pos, graph->t->i[k]);
            new_queen_pos = get_next_postion(queen_pos, dir, world->width);
            if((world->idx[new_queen_pos] == NO_SORT) && (new_queen_pos!=queen_pos))
                return 0;
        } 
    }
    return 1;
}

void end_game(struct world_t* world, struct graph_t graph, unsigned int** queens, struct moves_t* moves, struct player player_1, struct player player_2)
{
    free_world(world);
    free_queens(queens);
    free_moves(moves);
    gsl_spmatrix_uint_free(graph.t);
    player_1.finalize();
    player_2.finalize();
}

int main(int argc, char* argv[])
{
    printf("[-] Server running\n\n");

    void* player_1;
    struct player iencly;
    
    void* player_2;
    struct player internet;

    char *error;

    printf("[-] Client 1 loading\n");
    
    player_1 = dlopen("./install/client1.so", RTLD_LAZY);
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
    
    player_2 = dlopen("./install/client2.so", RTLD_LAZY);
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

        printf("[-] %s played ", current_player->get_player_name());
        print_move(move);
        printf("\n");

        if (!is_move_valid(&graph, world, move) || (current_player->color != sort_to_player_color(world->idx[move.queen_src]))){
            printf("[-] %s made an illegal move !\n", current_player->get_player_name());
            current_player = compute_next_player(current_player, &iencly, &internet);
            break;
	    }
        else {
            moves = moves_add(moves, move);
            world->idx[move.queen_dst] = world->idx[move.queen_src];
            world->idx[move.queen_src] = NO_SORT;
            world->idx[move.arrow_dst] = BLOCK;
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

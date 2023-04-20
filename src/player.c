#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "move.h"
#include "dir.h"
#include "graph.h"
#include "player.h"

struct player_data {
    unsigned int id;
    struct graph_t* graph;
    unsigned int num_queens;
    unsigned int** queens;
};

static struct player_data data;

char const* get_player_name()
{
    const char* bot = "BOTTES de Anton";
    return bot;
}

void initialize(unsigned int player_id, struct graph_t* graph, unsigned int num_queens, unsigned int* queens[NUM_PLAYERS])
{
    data.id = player_id;

    data.num_queens = num_queens;

    data.queens = (unsigned int**)malloc(sizeof(unsigned int*) * NUM_PLAYERS);
    for (unsigned int p = 0; p < NUM_PLAYERS; p++) {
        data.queens[p] = (unsigned int*)malloc(sizeof(unsigned int) * data.num_queens);
        for (unsigned int q = 0; q < data.num_queens; q++)
            data.queens[p][q] = queens[p][q];
    }

    data.graph = malloc(sizeof(struct graph_t));
    data.graph->num_vertices = graph->t->size1 * graph->t->size2;
    gsl_spmatrix_uint *tmp = gsl_spmatrix_uint_alloc(graph->t->size1, graph->t->size2);
    data.graph->t = gsl_spmatrix_uint_compress(tmp, GSL_SPMATRIX_CSR);
    gsl_spmatrix_uint_memcpy(data.graph->t, graph->t);
    gsl_spmatrix_uint_free(tmp);
}

unsigned int rand_seed = (unsigned int)time(NULL);

int get_rand_queen(int queen_number)
{
    return rand()%queen_number;    
}


unsigned int tiiiiiir(unsigned int pos){
    unsigned int dir=(rand()%8)+1;
    int stop =1;
    while((rand()%sqrt(data.graph->num_vertices)) && (stop != 0)){
            unsigned int k = data.graph->t[pos][0];
            //for (unsigned int k = data.graph->p[ligne]; k < data.graph->p[ligne+1] ; k++)  
                while ((data.graph->t[pos][k] != dir) && (stop!=0)){
                    if(k >= (data.graph->p[pos+1])){
                        stop = 0;
                        k--;
                    }
                    k++;
                }
                // if (pas possible){
                //     stop = 0;
                // }
            pos = k ;  
        }
    return pos;
}


struct move_t get_rand_move(void)
{
    struct move_t next_move;
    unsigned int ligne = data.queens[data.id][rand()%data.num_queens];
    next_move.queen_src= ligne;
    unsigned int dir = data.graph->t[ligne][data.graph->t[ligne][0]]; //direction == premiere elements non nul de la ligne n:ligne
    int stop=1;
        while(rand()%sqrt(data.graph->num_vertices) && (stop != 0)){ //condition d'arret
            unsigned int k = data.graph->t[ligne][0]; // on test tt les k elements de la 
            //for (unsigned int k = data.graph->p[ligne]; k < data.graph->p[ligne+1] ; k++)  
                while ((data.graph->t[ligne][k] != dir) && (stop!=0)){
                    if(k >= (data.graph->t[ligne+1])){
                        stop = 0;
                        k--;
                    }
                    k++;
                }
                // if (pas possible){  // depend de k
                //     stop = 0;
                // }
            ligne = k ;  
        }
    next_move.queen_dst=ligne;
    next_move.arrow_dst= tiiiiiir(ligne);
    return next_move;
}

void finalize()
{
    for (unsigned int p = 0; p < NUM_PLAYERS; p++)
        free(data.queens[p]);
    free(data.queens);
    gsl_spmatrix_uint_free(data.graph->t);
    free(data.graph);
}

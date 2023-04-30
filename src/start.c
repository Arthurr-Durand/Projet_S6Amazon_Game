#include <stdlib.h>
#include <time.h>
#include "move.h"
#include "dir.h"
#include "graph.h"
#include "player.h"

unsigned int rand_seed = (unsigned int)time(NULL);

int get_rand_queen(int queen_number)
{
    return rand()%queen_number;    
}


unsigned int tiiiiiir(unsigned int pos){
    unsigned int dir=(rand()%8)+1;
    while((rand()%sqrt(data.graph->num_vertices)) && (stop != 0)){
            unsigned int k = data.graph->p[pos];
            //for (unsigned int k = data.graph->p[ligne]; k < data.graph->p[ligne+1] ; k++)  
                while ((data.graph->ligne[k] != dir) && (stop!=0)){
                    if(k >= (data.graph->p[pos+1])){
                        stop = 0;
                    }
                    k++;
                }
                if (pas possible){
                    stop = 0;
                }
         
            pos = k ;  
 
        }
    return k;
}


struct move_t get_rand_move(void)
{
    struct move_t next_move;
    unsigned int ligne = data.quenns[data.id][rand()%data.num_queens];
    next_move.queen_src= ligne;
    unsigned int dir = data.graph->ligne[data.graph->p[ligne]];
    int stop=1;
        while(rand()%sqrt(data.graph->num_vertices) && (stop != 0)){
            unsigned int k = data.graph->p[ligne];
            //for (unsigned int k = data.graph->p[ligne]; k < data.graph->p[ligne+1] ; k++)  
                while ((data.graph->ligne[k] != dir) && (stop!=0)){
                    if(k >= (data.graph->p[ligne+1])){
                        stop = 0;
                    }
                    k++;
                }
                if (pas possible){  // depend de k
                    stop = 0;
                }
         
            ligne = k ;  
        }
    next_move.queen_dst=ligne;
    next_move.arrow_dst= tiiiiiir(ligne);
    return next_move;
}






    // struct move_t move = previous_move;
    // move.queen_src = previous_move.queen_dst;
    // int p = rand()%(csr->size1) ;
    // enum dir_t d = csr->p[move.queen_src]; //valeure dune case de la colonne dindice previous_move.queen_dst;
    // for(int i=0;i<rand()%(SIZE-(previous_move.queen_src%SIZE));i++){
    //     for(int k=0;k<queens.current;k++){
    //         if(queens.t[k].queen_dst == )//indice ou ya marqué d )
    //             return move;
    //     }
    //     for(int j=0;j<siz)
    //     move.queen_dst = csr      ;//indice de d dans la matrice;
    // }
    // return move;

    

   
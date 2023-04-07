#include <stdlib.h>
#include <time.h>
#include "move.h"
#include "dir.h"

unsigned int rand_seed = (unsigned int)time(NULL);

int get_rand_queen(int queen_number)
{
    return rand()%queen_number;    
}


struct move_t get_rand_move(struct move_t previous_move,struct moves_t queens)
{
    struct move_t move = previous_move;
    move.queen_src = previous_move.queen_dst;
    int p = rand()%(csr->size1) ;
    enum dir_t d = csr->p[move.queen_src]; //valeure dune case de la colonne dindice previous_move.queen_dst;
    for(int i=0;i<rand()%(SIZE-(previous_move.queen_src%SIZE));i++){
        for(int k=0;k<queens.current;k++){me
            if(queens.t[k].queen_dst == )//indice ou ya marqué d )
                return move;
        }
        for(int j=0;j<siz)
        move.queen_dst = csr      ;//indice de d dans la matrice;
    }
    return move;

}
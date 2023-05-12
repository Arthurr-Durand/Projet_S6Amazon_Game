#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "test_move_server.h"

void moves_add__test()
{
    printf("\t%s", __func__);

    struct move_t move = {-1, -1 , -1};
    struct moves_t* moves = malloc(sizeof(struct moves_t));
    moves->t = malloc(sizeof(struct move_t));
    moves->t[0] = move;
    moves->current = 0;
    struct move_t new_move = {2, 5, 7};
    moves = moves_add(moves, new_move);
    assert(moves->current == 1);
    assert(moves->t[moves->current].queen_src == new_move.queen_src);
    assert(moves->t[moves->current].queen_dst == new_move.queen_dst);
    assert(moves->t[moves->current].arrow_dst == new_move.arrow_dst);

    free_moves(moves);

    printf("\t\t\tOK\n");
}

void not_in_world__test()
{
    printf("\t%s", __func__);

    struct move_t move = {-1, -1, -1};
    assert(not_in_world(9, move) == 1);

    move.queen_src = 5;
    move.queen_dst = 3;
    assert(not_in_world(9, move) == 1);

    move.arrow_dst = 2;
    assert(not_in_world(9, move) == 0);

    move.queen_dst = 9;
    assert(not_in_world(9, move) == 1);

    move.queen_dst = 8;
    move.arrow_dst = 5;
    assert(not_in_world(9, move) == 0);

    move.queen_src = 3;
    move.queen_dst = 3;
    move.arrow_dst = 7;
    assert(not_in_world(9, move) == 1);

    move.queen_src = 5;
    move.queen_dst = 2;
    move.arrow_dst = 2;
    assert(not_in_world(9, move) == 1);

    move.queen_dst = -1;
    assert(not_in_world(9, move) == 1);

    printf("\t\tOK\n");
}

void get_direction__test()
{
    printf("\t%s", __func__);

    assert(get_direction(3, 0, 2) == DIR_EAST);
    assert(get_direction(3, 0, 4) == DIR_SE);
    assert(get_direction(3, 0, 3) == DIR_SOUTH);
    assert(get_direction(3, 0, 8) == DIR_SE);
    assert(get_direction(3, 0, 6) == DIR_SOUTH);
    assert(get_direction(3, 0, 5) == NO_DIR);
    assert(get_direction(3, 7, 2) == NO_DIR);
    assert(get_direction(3, 7, 3) == DIR_NW);
    assert(get_direction(3, 7, 6) == DIR_WEST);
    assert(get_direction(3, 7, 5) == DIR_NE);
    assert(get_direction(3, 7, 1) == DIR_NORTH);
    assert(get_direction(3, 2, 6) == DIR_SW);

    printf("\t\tOK\n");
}

void obstacle__test()
{
    printf("\t%s", __func__);

    struct graph_t graph = { 25, graph_init(5, SQUARED) };

    struct world_t* world = world_init(5);

    assert(obstacle(&graph, world, 0, 4) == 0);
    assert(obstacle(&graph, world, 0, 24) == 0);
    assert(obstacle(&graph, world, 0, 8) == 1);

    world_set(world, 10, BLOCK);

    assert(obstacle(&graph, world, 0, 20) == 1);
    assert(obstacle(&graph, world, 15, 5) == 1);

    world_set(world, 18, B_QUEEN);

    assert(obstacle(&graph, world, 22, 14) == 1);
    
    gsl_spmatrix_uint_free(graph.t);
    free_world(world);

    printf("\t\t\tOK\n");
}

void is_move_valid__test()
{
    printf("\t%s", __func__);

    struct graph_t graph = { 25, graph_init(5, SQUARED) };

    struct world_t* world = world_init(5);
    world_set(world, 22, W_QUEEN);

    struct move_t move1 = {2, 17, 5};
    struct move_t move2 = {2, 17, 4};
    struct move_t move3 = {2, 2, 4};
    struct move_t move4 = {0, 24, 20};

    assert(is_move_valid(&graph, world, move1) == 1);
    assert(is_move_valid(&graph, world, move2) == 0);
    assert(is_move_valid(&graph, world, move3) == 0);
    assert(is_move_valid(&graph, world, move4) == 0);

    gsl_spmatrix_uint_free(graph.t);
    free_world(world);

    printf("\t\tOK\n");
}

void exists_neighbor__test()
{
    printf("\t%s", __func__);

    struct graph_t graph = { 25, graph_init(5, SQUARED) };

    assert(exists_neighbor(&graph, DIR_SW, 10) == 25);
    assert(exists_neighbor(&graph, DIR_NE, 5) == 1);
    assert(exists_neighbor(&graph, NO_DIR, 5) == 25);
    assert(exists_neighbor(&graph, DIR_NW, 24) == 18);

    gsl_spmatrix_uint_free(graph.t);

    printf("\t\tOK\n");
}

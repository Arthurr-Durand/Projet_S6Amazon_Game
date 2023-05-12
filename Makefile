GSL_PATH ?= /net/ens/renault/save/gsl-2.6/install
CFLAGS = -std=c99 -Wall -Wextra -fPIC -g3 -I$(GSL_PATH)/include
LDFLAGS = -lm -lgsl -lgslcblas -ldl \
	-L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 \
	-Wl,--rpath=${GSL_PATH}/lib
CC = gcc

all: build

build: client server

server:
	$(CC) $(CFLAGS) -o install/server src/server.c src/world.c src/tools.c src/move_server.c src/game.c $(LDFLAGS)

client:
	$(CC) $(CFLAGS) -shared -o install/client1.so src/player_1.c
	$(CC) $(CFLAGS) -shared -o install/client2.so src/player_2.c

alltests: client
	$(CC) $(CFLAGS) -o install/alltests tst/test.c tst/test_client1.c tst/test_game.c tst/test_move_server.c tst/test_world.c src/game.c src/move_server.c src/world.c src/tools.c $(LDFLAGS) -I src/ -ldl --coverage -lgcov

test: alltests

install: server client test

clean:
	@rm -f *~ src/*~ tst/*~ install/*

.PHONY: client install test clean

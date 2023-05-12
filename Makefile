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

alltests: build
	$(CC) $(CFLAGS) -o install/test_client1 tst/test_client1.c src/move_server.c src/world.c $(LDFLAGS) -I src/ -ldl --coverage -lgcov
	$(CC) $(CFLAGS) -o install/test_game tst/test_game.c src/game.c src/move_server.c src/world.c $(LDFLAGS) -I src/ -ldl --coverage -lgcov
	$(CC) $(CFLAGS) -o install/test_move_server tst/test_move_server.c src/move_server.c src/world.c $(LDFLAGS) -I src/ -ldl --coverage -lgcov
	$(CC) $(CFLAGS) -o install/test_world tst/test_world.c src/world.c $(LDFLAGS) -I src/ -ldl --coverage -lgcov

test: alltests
	./install/test_client1	
	./install/test_game
	./install/test_move_server
	./install/test_world

install: server client test

clean:
	@rm -f *~ src/*~ tst/*~ install/*

.PHONY: client install test clean

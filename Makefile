GSL_PATH ?= /net/ens/renault/save/gsl-2.6/install
CFLAGS = -std=c99 -Wall -Wextra -fPIC -g3 -I$(GSL_PATH)/include
LDFLAGS = -lm -lgsl -lgslcblas -ldl \
	-L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 \
	-Wl,--rpath=${GSL_PATH}/lib
CC = gcc

all: build

build: client server

server:
	$(CC) $(CFLAGS) -o install/server src/server.c -ldl

client:
	mkdir -p install
	$(CC) $(CFLAGS) -shared -o install/client1.so src/player.c
	$(CC) $(CFLAGS) -shared -o install/client2.so src/player.c

alltests:
	$(CC) $(CFLAGS) -o install/alltests tst/test.c -ldl

test: alltests

runtest: test
	./install/alltests

install: server client test

clean:
	@rm -f *~ src/*~ tst/*~ install/*

.PHONY: client install test clean

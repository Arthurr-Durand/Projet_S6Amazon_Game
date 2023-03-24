GSL_PATH ?= /net/ens/renault/save/gsl-2.6/install
CFLAGS = -std=c99 -Wall -Wextra -fPIC -g3 -I$(GSL_PATH)/include
LDFLAGS = -lm -lgsl -lgslcblas -ldl \
	-L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 \
	-Wl,--rpath=${GSL_PATH}/lib
CC = gcc

all: build

build: server client

server:
	$(CC) $(CFLAGS) -o install/server src/server.c -ldl

client:
	$(CC) $(CFLAGS) -shared -o install/client1.so src/player.c

alltests:

test: alltests

install: server client test

clean:
	@rm -f *~ src/*~

.PHONY: client install test clean

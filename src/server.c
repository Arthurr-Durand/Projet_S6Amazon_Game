#include <dlfcn.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "world.h"
#include "tools.h"

int main(int argc, char* argv[])
{
    printf("[-] Server running\n");

    void* handle;

    handle = dlopen("./install/client1.so", RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        exit(1);
    }

    int opt;
    enum type_world w_type = SQUARED;
    unsigned int width = 8;

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

    struct graph_t g = { width * width, world_init(width, w_type) };

    print_gsl_spmatrix_uint(g.t);
    
    gsl_spmatrix_uint_free(g.t);

    dlclose(handle);

    return EXIT_SUCCESS;
}

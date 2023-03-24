
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("[-] Server running");

    void *handle;

    handle = dlopen("./install/client1.so", RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        exit(1);
    }

    dlclose(handle);

    return EXIT_SUCCESS;
}

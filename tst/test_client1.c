#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_get_player_name(char const* (*get_player_name)())
{
    printf("%s", __func__);
    assert(!strcmp((*get_player_name)(), "BOTTES de Anton"));
    printf("\t\tOK\n");
}

int main()
{
    printf("%s\n", __FILE__);

    void* handle;
    char const* (*get_player_name)();
    char* error;

    handle = dlopen("./install/client1.so", RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        exit(1);
    }

    get_player_name = dlsym(handle, "get_player_name");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }

    test_get_player_name(get_player_name);

    dlclose(handle);

    return EXIT_SUCCESS;
}
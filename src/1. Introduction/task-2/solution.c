#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <dlfcn.h>


int (*someSecretFunctionPrototype)(int);


bool init_library(const char* libname, const char* funcname) {
    void *hdl = dlopen(libname, RTLD_LAZY);

    if (NULL == hdl)
        return false;

    someSecretFunctionPrototype = (int (*)(int))dlsym(hdl, funcname);
    
    if (NULL == someSecretFunctionPrototype)
        return false;

    return true;
}


int main(int argc, char** argv) {
    int val = atoi(argv[3]);
    if (init_library(argv[1], argv[2]))
        printf("%d\n", someSecretFunctionPrototype(val));
    else
        printf("Library was not loaded\n");
    return 0;
}

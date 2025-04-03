#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int *pointer = 0;

    printf("Christopher Smith, dereferencing null pointer...\n");
    int nullDereference = *pointer;

    //  Added to silence warning about unused variable, which prevents OS 
    //  compilation
    if (nullDereference == 0) {}

    exit(0);
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main ( int argc, char* argv[]) {
    FILE * fptr;   
    int i = 0;
    printf(" number of arguments given: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf(" argument %d: %s\n", i, argv[i]);
    }

    printf(" *\n\n");

    if (argc != 2) {
        printf(" incorrect number of arguments given\n");
        return 1;
    }

    fptr = fopen(argv[i], "r");

    if (fptr == NULL) {
        printf(" couldn't open file");
        return 0;
    }
}

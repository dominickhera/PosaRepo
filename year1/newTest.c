#include<stdlib.h>
#include<stdio.h>
#include<string.h>
char* getString(char* inFunc);

int main() {
    char inMain[255];
    char* string;
    string = getString(&inMain);
    printf("%s\n", string);
}

char* getString(char* inFunc) {

    strcpy(inFunc, "hello world");
    return inFunc;
}


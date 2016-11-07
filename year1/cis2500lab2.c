#include<stdio.h>
#include<stdlib.h>

int ** createMemory();
void freeMemory(int ** ptr);

int main (int argc, char ** argv) {

    int ** myInt;

    myInt = createMemory();

    for (int i = 0; i < 4; i++){
        for (int k = 0; k < 4; k++){
            myInt[i][k] = k*i;
        }
    }

    for (int i = 0; i < 4; i++){
        for (int k = 0; k < 4; k++) {
            printf("VALUE: %d, %d: %d\n", i,k, myInt[i] [k]);
        }
    }

    for (int i = 0; i < 4; i++){
        for (int k = 0; k < 4; k++){
            printf("PTR: %p\n", &myInt[i] [k]);
        }
    }
    // printf("PTR: %p\n", &myInt);
    //  freeMemory(myInt);
    return 0;
}

int ** createMemory() {
    int ** ptr;

    for (int i = 0; i < 4; i++) {
        ptr[i] = malloc(sizeof(int) * 4);
    }
    return ptr;
}


void freeMemory(int ** ptr){
    for (int i = 0; i < 4; i++) {
        free(ptr[i]);
    }
    free(ptr);
}

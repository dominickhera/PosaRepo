#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int countLines(FILE* fp) {
    char buffer[255];
    int lines = 0;
    while( (fgets(buffer, 255, fp)) != NULL) {
        int length;
        length = strlen(buffer);
        if (buffer[length-1] == '\n') {
            lines++;
            buffer[length-1] = '\0';
        } else {
            printf("didn't read in whole line");
            exit(0);
        }

        printf("%s\n", buffer);
    }
    return lines;

}

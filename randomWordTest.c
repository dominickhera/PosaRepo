#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


char getFileName (char openFile[30]);
char scrambleWord (char word[30], int length);
char processText (char openFile[30]);

int main(void) {
    char word[30];
    char scramble[30];
    char fileName[30];
    int wordLen = strlen(word);
    int i, j;
    srand (time(NULL));
    int randomNumber = 0;
    FILE *ifp;

    getFileName(fileName);
    ifp = fopen(fileName, "r");

    if (ifp == NULL) {
        printf("Sorry, file does not exist");
        return 0;
    }

    while (fscanf(ifp, "%s", word) != EOF){
        wordLen = strlen(word);
        if (wordLen <= 3) {
            printf("%s ", word);
        } else {
            printf("%c", word[0]);
            for (i = 1; i < (wordLen - 2); i++) {
                randomNumber = (rand() % wordLen);
                printf("%c", word[randomNumber]);
            }
            printf("%c", word[wordLen]);
            printf(" ");
        }
    }
    printf("\n");
    return 0;
}

char getFileName (char openFile[30]) {

    printf("enter file name to scramble\n");
    scanf("%s", openFile);

    return openFile[30];
}
/*
   char scambleWord (char word[30], int length) {

   }

   char processText ( ) {

   }*/

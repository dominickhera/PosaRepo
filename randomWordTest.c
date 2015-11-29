#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


char getFileName (char openFile[30]);
char scrambleWord (char word[], int length);
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
        printf("Sorry, file does not exist\n");
        return 0;
    }

    while (fscanf(ifp, "%s", word) != EOF){
        wordLen = strlen(word);
        scrambleWord(word, wordLen);
    }

    /*    while (fscanf(ifp, "%s", word) != EOF){
          wordLen = strlen(word);
          if (wordLen <= 3) {
          printf("%s ", word);
          } else {
          printf("%c", word[0]);
          for (i = 1; i < (wordLen); i++) {
          randomNumber = (rand() % wordLen);
          scramble[i - 1] = word[i];
          word[i] = scramble[i];
          printf("%c", word[i]);
          }
          printf(" ");
          }
          }*/
    printf("\n");
    return 0;
}

char getFileName (char openFile[30]) {

    printf("enter file name to scramble\n");
    scanf("%s", openFile);

    return openFile[30];
}

char scambleWord (char word, int length) {
    int i;
    char letters[length-2];
    if (length <= 3) {
        printf("%s ", word);
    } else {
       //char letters[length-2];  
        for (i = 1; i < (length - 2); i++){
            letters[i] = word[i];
            printf("%c", letters[i]);
	  }
          printf(" ");
          }
}

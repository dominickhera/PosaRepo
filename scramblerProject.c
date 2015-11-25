#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

int getFilename(char fileOpen);
int scrambleWord(char wordThing);
int processText(char textThing);

int main(void) {
int wordLen;
char word[30];
FILE *ifp;
char fileName[50];

getFilename(fileName);
ifp = fopen(fileName, "r");
processText(word);

return 0;
}

int getFileName(char fileName){
char fileOpen[50];

printf("enter filename and extension to scramble.\n");
scanf("%s", fileOpen);

return fileOpen;
}

int processText(char textThing) {
FILE *ifp;
char word[30];
int wordLen;

while (fscanf(ifp, "%s", word) != EOF) {
wordLen = strlen(word);
printf("%s = %d characters\n", word, wordLen);
}

return;
}

int scrambleWord(char wordThing){

return;
}

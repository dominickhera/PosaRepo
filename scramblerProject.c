#include<stdio.h>
#include<string.h>
#include<time.h>

<<<<<<< HEAD
/*
int getFileName(char docName[]) {
=======
/*int getFileName(char docName) {
>>>>>>> 33dfb783d74c6031d44e85e71a188fa7c6d2b90f
FILE *ifp;

printf("enter name of document to scramble: \n");
scanf("%s", docName);

ifp = fopen(docName, "r");

if (ifp == NULL) {
printf("Sorry, that file does not exist.\n");
return 0;
}
}*/

int main(void) {
FILE *ifp;
<<<<<<< HEAD
char docName[50];

printf("enter name of document to scramble: \n");
scanf("%s", docName);

ifp = fopen(docName, "r");

if (ifp == NULL) {
printf("Sorry, that file does not exist.\n");
return 0;
}
=======
srand (time(NULL));
int randomNumber = 0;
char docOpen[50];
int wordLen;
char word[30];
int charTotal = 0;
int i = 0;

printf("enter name of document to scramble: \n");
scanf("%s", docOpen);

ifp = fopen(docOpen, "r");

if (ifp == NULL) {
printf("Sorry, that files does not exist.\n");
return 0;
}

while (fscanf(ifp, "%s", word) != EOF) {
wordLen = strlen(word);
charTotal = wordLen + charTotal;
if (wordLen < 3) {
printf("%s ", word);
} else {
for (i = 0; i < wordLen; i++) {
randomNumber = (rand() % wordLen);
strcpy(word[i], word[randomNumber]);
}
//printf("%s = %d characters \n", word, wordLen);
}
}
printf("the character total is %d\n", charTotal);
>>>>>>> 33dfb783d74c6031d44e85e71a188fa7c6d2b90f
//getFileName(docOpen);

return 0;
}

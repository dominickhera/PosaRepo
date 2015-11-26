#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int main(void) {
int wordLen;
char word[30];
char scramble[30];
char fileName[30];
int i;
srand (time(NULL));
int randomNumber = 0;
FILE *ifp;

printf("enter file name\n");
scanf("%s", fileName);

ifp = fopen(fileName, "r");

if (ifp == NULL) {
printf("Sorry, file does not exist");
return 0;
}

while (fscanf(ifp, "%s", word) != EOF){
wordLen = strlen(word);
randomNumber = (rand() % wordLen);
if (wordLen <= 3) {
printf("%s ", word);
} else {
for (i = 0; i < wordLen; i++) {
if (i == 0 || i == wordLen) {
printf("%c", word[i]);
} else {
printf("%c", word[randomNumber]);
}
}
printf(" ");
}
}
printf("\n");
return 0;
}

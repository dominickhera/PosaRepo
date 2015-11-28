#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int main(void) {
int wordLen;
char word[30];
char scramble[30];
char fileName[30];
int i, j;
srand (time(NULL));
int randomNumber = 0;
int randomThing = 0;
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
if (wordLen <= 3) {
printf("%s ", word);
} else {
    printf("%c", word[0]);
    for (i = 1; i < (wordLen - 2); i++) {
//	printf("%c", word[i]);
//	} else {
 //      if (i > 0 && i < wordLen) {
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

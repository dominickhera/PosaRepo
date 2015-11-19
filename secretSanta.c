#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
int main(void) {

srand(time(NULL));
int i = 0;
int randomNumber = 0;
int numberPeople;

printf("how many people will there be?\n");
scanf("%d", &numberPeople);
char peopleArray[numberPeople];
char secondArray[numberPeople];

for (i = 0; i < numberPeople; i++) {
printf("input persons name: ");
scanf("%s", peopleArray);
strcpy(peopleArray, secondArray);
}
printf("alright, next lets find you your secret santa is!\n");

for (i = 0; i < numberPeople; i++) {
printf("enter your name: ");
scanf("%s", secondArray);
randomNumber = ((rand() % numberPeople) + 1);
printf("%s", peopleArray[randomNumber]);
/*
if (secondArray == people Array) {

} else {
}*/
}
return 0;
}

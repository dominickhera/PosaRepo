#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
int main(void) {

srand(time(NULL));
int i = 0;
int randomNumber = 0;
int personFind = 0;
int numberPeople;

//sets size of array
printf("how many people will there be?\n");
scanf("%d", &numberPeople);
char *peopleArray[numberPeople];
char *secondArray[numberPeople];

//SHOULD assign names to each number in array
for (i = 0; i < numberPeople; i++) {
printf("input persons name: ");
scanf("%s", peopleArray[i]);
}

//transition phrase w000000
printf("alright, next lets find you your secret santa is!\n");


//hypothetically should match users who enter their name with another person//
//in the list and then prevent that person from picking the same person or //
//being picked again.//
for (i = 0; i < numberPeople; i++) {
printf("enter your name: ");
scanf("%s", secondArray);
randomNumber = ((rand() % numberPeople) + 1);
personFind = randomNumber - 1;
printf("%d", randomNumber);
printf("%s", peopleArray[personFind]);
/*
if (secondArray == people Array) {

} else {
}*/
}
return 0;
}

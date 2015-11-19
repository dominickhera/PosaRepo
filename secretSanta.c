#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
int main(void) {

srand(time(NULL));
int i = 0;
int randomNumber = 0;
int personFind = 0;
int numberPeople = 100;

//sets size of array
printf("how many people will there be?\n");
scanf("%d", &numberPeople);
char peopleArray[numberPeople];
char secondArray[numberPeople];

//SHOULD assign names to each number in array
for (i = 0; i < numberPeople; i++) {
printf("input persons name: ");
scanf("%s", &peopleArray[i]);
}

//transition phrase w000000
printf("alright, next lets find you your secret santa is!\n");

//hypothetically should match users who enter their name with another person//
//in the list and then prevent that person from picking the same person or //
//being picked again.//
for (i = 0; i < numberPeople; i++) {
printf("enter your name: ");
scanf("%s", &secondArray[i]);
randomNumber = ((rand() % numberPeople) + 1);
if (secondArray[i] == peopleArray[randomNumber]) {
printf("you are secret santa for: %s\n", &peopleArray[randomNumber]);
} else {
printf("you are secret santa for: %s\n", &peopleArray[randomNumber]);
}
}
return 0;
}

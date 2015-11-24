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

//assigns names to each number in array
for (i = 0; i < numberPeople; i++) {
printf("input persons name: ");
scanf("%s", &peopleArray[i]);
printf("%s \n", peopleArray);
}

for (i = 0; i < numberPeople; i++) {
printf("%s, ", &peopleArray[i]);
}
printf("\n");

//transition phrase w000000
printf("alright, next lets find you your secret santa is!\n");

//hypothetically should mantch users who enter their name with another person//
//in the list and then prevent that person from picking the same person or //
//being picked again.//

for (i = 0; i < numberPeople; i++) {
printf("enter your name: ");
scanf("%s", &secondArray[i]);
randomNumber = ((rand() % numberPeople) + 1);
if (strcmp(secondArray[i], peopleArray[randomNumber]) == 0) {
printf("ay lmao");
} else {
printf("you are secret santa for: %s\n", &peopleArray[randomNumber]);
}
}
return 0;
}

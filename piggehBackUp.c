// Weo weo Dominick Hera  weo Weo//
// Weo weo    CIS1500     weo Weo//
// Weo weo  Assignment 1  weo Weo//
// Weo weo a game of pigs weo Weo//

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void) {

srand ((int)time(0));
int answer;
char charAnswer;
char rollAnswer;
int gameTotal;
int playerOneTotal = 0;
int playerTwoTotal = 0;

printf("\nwelcome to a game  of pigthrones\n");
printf("---------------------------\n");
printf("  made by dominick hera   \n");
printf("\ndo you and your friend want to play a game? (y/n) :");
scanf("%c", &charAnswer);

if (charAnswer == 'y') {
printf("please set the game total: \n");
scanf("%d", &gameTotal);
}

printf("do you want to (r)oll or (h)old? : \n");
scanf("%c", &rollAnswer);

if (rollAnswer == 'r') {

printf("%d\n", ((rand() % 6) + 1));

}
if (rollAnswer == 'h') {
printf("hi");

}

return 0;

}

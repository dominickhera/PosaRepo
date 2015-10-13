// Weo weo Dominick Hera  weo Weo//
// Weo weo    CIS1500     weo Weo//
// Weo weo  Assignment 1  weo Weo//
// Weo weo a game of pigs weo Weo//

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void) {

srand ((int)time(0));
char charAnswer = 'x' ;
char rollAnswer =  'x' ;
int gameTotal = 0;
int playerTurn = 1;
int playerOneTotal = 0;
int playerTwoTotal = 0;
int randomNumber = 0;

printf("\nwelcome to a game  of pigthrones\n");
printf("---------------------------\n");
printf("  made by dominick hera   \n");
printf("\ndo you and your friend want to play a game? (y/n) :");
scanf("%c", &charAnswer);

if (charAnswer == 'y') {
printf("please set the game total: \n");
scanf("%d", &gameTotal);


while (playerOneTotal <= gameTotal || playerTwoTotal <= gameTotal ) {
printf("do you want to (r)oll or (h)old? : \n >");

scanf("\n%c", &rollAnswer);

if (rollAnswer == 'r') {

randomNumber = ((rand() % 6) + 1);
printf("%d\n", randomNumber);

switch (randomNumber) {
	case 0:
		printf("how the fuck did you even get here? Get the fuck out");
		return 0;
		break;

	case 1:
		printf("You rolled a %d\n", randomNumber);
		if (playerTurn == 1) {
		playerOneTotal = playerOneTotal + randomNumber;
		printf("Player %d Point Total: %d\n", playerTurn, playerOneTotal);
		} else {
		playerTwoTotal = playerTwoTotal + randomNumber;
		printf("Player %d Point Total: %d\n", playerTurn, playerTwoTotal);
		}
		if (playerOneTotal >= gameTotal) {
printf("Player one has won! weo weo weo\n");
return 0;
} else 
 if (playerTwoTotal >= gameTotal) {
printf("Player two has won! weo weo weo\n");
return 0;
}
		printf("Sorry, you lose a turn\n");
		if (playerTurn == 1) {
		playerTurn = 2;
		printf("it is now Player  %d's turn\n", playerTurn);
		} else {
		playerTurn = 1;
		printf("it is now Player %d's turn\n", playerTurn);
		}
		break;


	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		printf("You rolled %d\n", randomNumber);
		if (playerTurn == 1) {
		playerOneTotal = playerOneTotal + randomNumber;
		printf("Player %d Point Total: %d\n", playerTurn, playerOneTotal);
		} else {
		playerTwoTotal = playerTwoTotal + randomNumber;
		printf("Player %d Point Total %d\n", playerTurn, playerTwoTotal);
		}
		break;

	default:
		printf("default answer");
		break;}
} else
 if (rollAnswer == 'h') {
if (playerOneTotal >= gameTotal) {
printf("Player one wins! weo weo weo \n");
return 0;
} else
 if (playerTwoTotal >= gameTotal) {
printf("Player two wins! weo weo weo \n");
return 0;
} else {
printf("it's now the next players turn");
}
}
}
}
return 0;

}

// Weo weo Dominick Hera  weo Weo//
// Weo weo    CIS1500     weo Weo//
// Weo weo  Assignment 1  weo Weo//
// Weo weo a game of pigs weo Weo//

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void showDice(int num) {
switch(num) {
	case 0:
		printf("how about no");
		break;	

	case 1:
		printf("+-------+\n");
		printf("|       |\n");
		printf("|   o   |\n");
		printf("|       |\n");
		printf("+-------+\n");
		break;
	case 2:
		printf("+-------+\n");
                printf("|       |\n");
                printf("| o   o |\n");
                printf("|       |\n");
                printf("+-------+\n");
		break;
	case 3:
		printf("+-------+\n");
                printf("| o     |\n");
                printf("|   o   |\n");
                printf("|     o |\n");
                printf("+-------+\n");
                break;

	case 4:
		printf("+-------+\n");
                printf("| o   o |\n");
                printf("|       |\n");
                printf("| o   o |\n");
                printf("+-------+\n");
                break;

	case 5:
		printf("+-------+\n");
                printf("| o   o |\n");
                printf("|   o   |\n");
                printf("| o   o |\n");
                printf("+-------+\n");
                break;
	case 6:
		printf("+-------+\n");
                printf("| o   o |\n");
                printf("| o   o |\n");
                printf("| o   o |\n");
                printf("+-------+\n");
                break;

	default:
		printf("default answer");
		break;
}
}

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
printf("================================\n");
printf("  made by dominick hera   \n");
printf("\ndo you and your friend want to play a game? (y/n) \n > ");
scanf("%c", &charAnswer);

if (charAnswer == 'y') {
printf("please set the game total: \n >");
scanf("%d", &gameTotal);


while ((playerOneTotal < (gameTotal - 1)) || (playerTwoTotal < (gameTotal - 1))) {
printf("do you want to (r)oll or (h)old? : \n > ");

scanf("\n%c", &rollAnswer);

if (rollAnswer == 'r') {

randomNumber = ((rand() % 6) + 1);

switch (randomNumber) {
	case 0:
		printf("how the fuck did you even get here? Get the fuck out");
		return 0;
		break;

	case 1:
		printf("You rolled a %d\n", randomNumber);
		printf("--------------------\n");
		showDice(randomNumber);
		printf("--------------------\n");
		if (playerTurn == 1) {
		printf("Player %d Point Total: %d\n", playerTurn, playerOneTotal);
		printf("Player 2 Point Total: %d\n", playerTwoTotal);
		printf("Game Total: %d\n", gameTotal);
		} else {
		printf("Player 1 Point Total: %d\n", playerOneTotal);
		printf("Player %d Point Total: %d\n", playerTurn,  playerTwoTotal);
		printf("Game Total: %d\n", gameTotal);
		}
		if (playerOneTotal >= gameTotal) {
		printf("player one has won! weo weo weo\n");
		return 0;
		} else 
 		if (playerTwoTotal >= gameTotal) {
		printf("player two has won! weo weo weo\n");
		return 0;
		}
		printf("-------------------\n");
		printf("Sorry, you lose a turn\n");
		if (playerTurn == 1) {
		playerTurn = 2;
		printf("it is now Player  %d's turn\n", playerTurn);
		} else {
		playerTurn = 1;
		printf("it is now Player %d's turn\n", playerTurn);
		}
		printf("-----------------------\n");
		break;


	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		printf("You rolled %d\n", randomNumber);
		printf("-----------------------\n");
		showDice(randomNumber);
		printf("-----------------------\n");
		if (playerTurn == 1) {
		playerOneTotal = playerOneTotal + randomNumber;
		printf("Player %d Point Total: %d\n", playerTurn, playerOneTotal);
		printf("Player 2 Point Total: %d\n", playerTwoTotal);
		printf("Game Total: %d\n", gameTotal);
		printf("---------------------------\n");
		} else {
		playerTwoTotal = playerTwoTotal + randomNumber;
		printf("Player 1 Point Total %d\n", playerOneTotal);
		printf("Player %d  Point Total %d\n", playerTurn,  playerTwoTotal);
		printf("Game Total: %d\n", gameTotal);
		printf("---------------------------\n");
		if (playerOneTotal > (gameTotal - 1)) {
		printf("player one has won! weo weo weo\n");
		return 0;
		} else
		if (playerTwoTotal > (gameTotal - 1)) {
		printf("player two has won! weo weo weo\n");
		return 0;
		}
		}
		break;

	default:
		printf("default answer");
		break;}
} else
 if (rollAnswer == 'h') {
if (playerOneTotal >= gameTotal) {
printf("player one wins! weo weo weo \n");
return 0;
} else
 if (playerTwoTotal >= gameTotal) {
printf("player two wins! weo weo weo \n");
return 0;
} else {
if (playerTurn == 1) {
playerTurn = 2;
} else { 
playerTurn = 1;
}
printf("it's now players %d turn\n", playerTurn);
printf("---------------------------\n");
}
}
}
}
return 0;
}

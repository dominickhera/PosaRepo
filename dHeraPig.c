// Weo weo Dominick Hera  weo Weo//
// Weo weo    cis1500     weo Weo//
// Weo weo    16/10/15    weo Weo//
// Weo weo  assignment 1  weo Weo//
// Weo weo a game of pigs weo Weo//

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//dice display code switch case that displays a different character drawn dice based on the number the user rolls
void showDice(int num) 
{
	switch(num)
	 {
		case 1:
			printf("    +-------+\n");
			printf("    |       |\n"); 
			printf("    |   o   |\n");
			printf("    |       |\n");
			printf("    +-------+\n");
			break;
		case 2:
			printf("    +-------+\n");
       			printf("    |       |\n");
               	 	printf("    | o   o |\n");
               		printf("    |       |\n");
                	printf("    +-------+\n");
			break;
		case 3:
			printf("    +-------+\n");
                	printf("    | o     |\n");
                	printf("    |   o   |\n");
                	printf("    |     o |\n");
                	printf("    +-------+\n");
                	break;

		case 4:
			printf("    +-------+\n");
                	printf("    | o   o |\n");
                	printf("    |       |\n");
                	printf("    | o   o |\n");
                	printf("    +-------+\n");
                	break;

		case 5:
			printf("    +-------+\n");
                	printf("    | o   o |\n");
                	printf("    |   o   |\n");
                	printf("    | o   o |\n");
                	printf("    +-------+\n");
                	break;
		case 6:
			printf("    +-------+\n");
                	printf("    | o   o |\n");
                	printf("    | o   o |\n");
                	printf("    | o   o |\n");
                	printf("    +-------+\n");
                	break;

		default:
			printf("default answer");
			break;
	}
}

int main(void) 
{

//declaring all the variables needed as well as the random number generator
	srand (time(NULL));
	char charAnswer = 'x' ;
	char rollAnswer =  'x' ;
	int rollTotal = 0;
	int gameTotal = 0;
	int playerTurn = 1;
	int playerOneTotal = 0;
	int playerTwoTotal = 0;
	int randomNumber = 0;

//introductary welcome, also asks the user if they want to play a game, if they say n then the program ends otherwise it continues
	printf("\nwelcome to a game  of pigthrones\n");
	printf("================================\n");
	printf("  made by dominick hera   \n");
	printf("\ndo you and your friend want to play a game? (y/n) \n > ");
	scanf("%c", &charAnswer);

//sets the game total, the score that is trying to be reached
	if (charAnswer == 'y') 
	{
		printf("please set the game total \n > ");
		scanf("%d", &gameTotal);

//start of the major loop that controls the entire game. ends when one of the player totals is not less than the game total. 
		while ((playerOneTotal < (gameTotal - 1)) || (playerTwoTotal < (gameTotal - 1))) {
			printf("player %d, do you want to (r)oll or (h)old? : \n > ", playerTurn);

			scanf("\n%c", &rollAnswer);

			if (rollAnswer == 'r')
			 {

//calls the random number generator and assigns it to an integer for easier use throughout the code
			randomNumber = ((rand() % 6) + 1);


//starts the switch case using the random number generator for each of the cases
			switch (randomNumber) 
			{

//is the pig case that sets the roll total to 0, showing the die, the player totals as well and changes turns to the next player
			case 1:
				rollTotal = 0;
				printf("you rolled a %d\n", randomNumber);
				printf("--------------------\n");
				showDice(randomNumber);
				printf("--------------------\n");
				printf("player %d's roll total: %d\n", playerTurn, rollTotal);
				if (playerTurn == 1) 
				{
					printf("player %d point total: %d\n", playerTurn, playerOneTotal);
					printf("player 2 point total: %d\n", playerTwoTotal);
					printf("game total: %d\n", gameTotal);
				}
			 	else
		       	        {
					printf("player 1 point total: %d\n", playerOneTotal);
					printf("player %d point total: %d\n", playerTurn,  playerTwoTotal);
					printf("Game Total: %d\n", gameTotal);
				}
					printf("-------------------\n");
					printf("sorry, you lose a turn\n");
					if (playerTurn == 1)
					 {
						playerTurn = 2;
						printf("it is now player  %d's turn\n", playerTurn);
					}
					 else
				        {
						playerTurn = 1;
						printf("it is now player %d's turn\n", playerTurn);
					}
						printf("-----------------------\n");
						break;

//accommodates every other number besides 1/pig adds the random number to the roll total, shows the character die, the player totals
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				rollTotal = rollTotal + randomNumber;
				printf("you rolled %d\n", randomNumber);
				printf("-----------------------\n");
				showDice(randomNumber);
				printf("-----------------------\n");
				printf("player %d's roll total: %d\n", playerTurn, rollTotal);
					if (playerTurn == 1)
					 {
						printf(">>player %d point total: %d<<\n", playerTurn, playerOneTotal);
						printf("player 2 point total: %d\n", playerTwoTotal);
						printf("game total: %d\n", gameTotal);
						printf("---------------------------\n");
					}
				        else
				        {
						printf("player 1 point total %d\n", playerOneTotal);
						printf(">>player %d  point total %d<<\n", playerTurn,  playerTwoTotal);
						printf("game total: %d\n", gameTotal);
						printf("---------------------------\n");
					}
						break;

			default:
				printf("default answer");
				break;
				}
			}
			 else

//hold option, if it's player ones turn then it adds the roll total to the player one total
//sets the roll total back to 0 for the next turn
//and then proceeds to check to see if the players total
//is greater than or equal to the game total and if it's true then the game ends and prints that
//that player one and the amount of points they won with. , if the player doesnt win then it proceeds
//to change the player turn and loops back to the top.
 	if (rollAnswer == 'h')
	{		
		if (playerTurn == 1) 
		{	
			playerOneTotal = playerOneTotal + rollTotal;
			rollTotal = 0;
			if (playerOneTotal >= gameTotal)
			 {	
				printf("player one wins with %d points! weo weo weo \n", playerOneTotal);
				return 0;
				}
				 else 
				{
					playerTurn = 2;
					printf("--------------------------\n");
					printf("player 1 point total: %d\n",  playerOneTotal);
					printf("player 2 point total: %d\n", playerTwoTotal);
					printf("--------------------------\n");
					printf("it's now player %d's turn\n", playerTurn);
					printf("--------------------------\n");
					} 
				}
				 else 
				{
					playerTwoTotal = playerTwoTotal + rollTotal;
					rollTotal = 0;
					if (playerTwoTotal >= gameTotal)
					 {
						printf("player two wins with %d points! weo weo weo \n", playerTwoTotal);
						return 0;
					}
					 else
			                {
						playerTurn = 1;
						printf("---------------------------\n");
						printf("player 1 point total: %d\n",  playerOneTotal);
						printf("player 2 point total: %d\n", playerTwoTotal);
						printf("---------------------------\n");
						printf("it's now players %d turn\n", playerTurn);
						printf("---------------------------\n");
					}
				}
			}
		}
	}
return 0;
}

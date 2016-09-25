// #include <string.h>
// #include <stdlib.h>
// #include <stdio.h>
 #include "run.h"

int main(void)
{
	char str[] = "Carbon";
	int string = strlen(str);
	int userChoice = 0;
	int x, y;
	while (userChoice != 4)
	{
		printf("(1) carbon scramble\n(2) ackermann's function\n(3) newton's method\n(4) exit\nenter a number: ");
		scanf("%d", &userChoice);

		switch(userChoice)
		{
			case 1:
				switcharoni(str, 0, string-1);
				printf("\n");
				break;
			case 2:
				printf("please enter first number\n");
				scanf("%d", &x);
				printf("please enter second number\n");
				scanf("%d", &y);
				ackermanns(x,y);
				// printf("A(%d, %d)\n", x, y);
				break;
			case 3:
				printf("you picked 3\n");
				break;
			case 4:
				printf("goodbye\n");
				exit(1);
			default:
				printf("enter a number between 1-4\n");
				break;
		}
	}
		return 0;
}
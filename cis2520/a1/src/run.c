#include <stdio.h>

int main(void)
{
	int userChoice = 0;
	while (userChoice != 4)
	{
		printf("(1) carbon scamble\n(2) ackermann's function\n(3) newton's method\n(4) exit\nenter a number: ");
		scanf("%d", &userChoice);

		switch(userChoice)
		{
			case 1:
				printf("you picked 1\n");
				break;
			case 2:
				printf("you picked 2\n");
				break;
			case 3:
				printf("you picked 3\n");
				break;
			case 4:
				printf("goodbye\n");
				break;
			default:
				printf("enter a number between 1-4\n");
				break;
		}
	}
		return 0;
}
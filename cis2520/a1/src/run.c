 #include "run.h"

int main(void)
{
	int userChoice = 0;
	while (userChoice != 4)
	{
		printf("(1) carbon scramble\n(2) ackermann's function\n(3) newton's method\n(4) exit\nenter a number: ");
		scanf("%d", &userChoice);

		switch(userChoice)
		{
			case 1:
				carbonInit();
				printf("\n");
				break;
			case 2:
				ackermannInit();
				break;
			case 3:
				newtonInit();
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
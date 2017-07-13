#include "heap.h"
#include "functions.h"

int main(int argc, char* argv[])
{

	int choice = 0;
	char * fileName = argv[1];
	char line[256];
	FILE *fp;

	fp = fopen(fileName, "r");

	while(fgets(line, sizeof(line), fp) != NULL)
	{

		if(line[strlen(line) - 1] == '\n')
		{
			line[strlen(line) - 1] = '\0';
		}
		else
		{
			line[strlen(line)] = '\0';
		}
		
		printf("%s", line);
	}

	while(choice != 6)
	{

		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				// printf("num is 1\n");
				break;
			case 2:
				// printf("num is 2\n");
				break;
			case 3:
				// printf("num is 3\n");
				break;
			case 4:
				// printf("num is 4\n");
				break;
			case 5:
				// printf("num is 5\n");
				break;
			case 6:
				printf("Exiting...\n");
				exit(1);
			default:
				printf("enter a number between 1-6\n");
				break;

		} 
	}

	return 0;
}
